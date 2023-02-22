#!/bin/bash
#
# Script to run secure-binary-image.sh on binaries in a FIT image
#
# Note: This version of this script does not have a dependency
#       on u-boot-tools, but it does run a bit slower and does not
#       handle re-generating the hash nodes correcty. Only use
#       this version if you do not have u-boot-tools installed.
#
# Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
#       Andrew Davis <afd@ti.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#   Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#
#   Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the
#   distribution.
#
#   Neither the name of Texas Instruments Incorporated nor the names of
#   its contributors may be used to endorse or promote products derived
#   from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

function fn_display_usage
{
	echo "Error: $1"
	echo ""
	echo "This script is used to secure a binary blobs in FIT images."
	echo ""
	echo "Usage: $0 <input-fit-name> <output-fit-name>"
	echo ""
	exit 1
}

# Validate input parameters
if [ $# -lt 2 ]
then
	fn_display_usage "missing parameter"
fi

# Check for device tree compiler
if ! [ -x "$(command -v dtc)" ]
then
	echo "Error: dtc is not installed, install device-tree-compiler package"
	exit 1
fi

# Check for xxd
if ! [ -x "$(command -v xxd)" ]
then
	echo "Error: xxd is not installed, install xxd package"
	exit 1
fi

# Check for awk
if ! [ -x "$(command -v awk)" ]
then
	echo "Error: awk is not installed, install awk package"
	exit 1
fi

# check where this tool is installed
SIGN_SCRIPT=$(dirname $0)/../scripts/secure-binary-image.sh
if [ ! -f ${SIGN_SCRIPT} ]
then
	SIGN_SCRIPT=${TI_SECURE_DEV_PKG}/scripts/secure-binary-image.sh
	if [ ! -f ${SIGN_SCRIPT} ]
	then
		fn_display_usage "Signing script cannot be found, correctly define TI_SECURE_DEV_PKG environment variable"
	fi
fi

# Parse input options
INPUT_FILE=$1
OUTPUT_FILE=$2

FDT_SIZE=$(dd if=${INPUT_FILE} ibs=1 skip=4 count=4 2>/dev/null | od --format=u4 --endian=big --address-radix=n)

# Decompile FIT image
FIT_SOURCE=$(mktemp) || exit 1
dtc -I dtb -O dts ${INPUT_FILE} > ${FIT_SOURCE}

# DTC outputs two formats for data based on the size of the
# blob, when divisible by 4 it uses <>, else [] format
#data_brackets_regexp="^[[:blank:]]*data = \[(.*)\];$"
#data_alligator_regexp="^[[:blank:]]*data = <(.*)>;$"
DATA_ALLIGATOR_START="			data = <"
DATA_BRACKET_START="			data = ["
DATA_SIZE_START="			data-size = <"
DATA_OFFSET_START="			data-offset = <"

AWK_EXAPNDER='
BEGIN { ORS=" "; }
{
	for (i = 1; i <= NF; ++i)
	{
		hex = substr($i, 3);
		printf("%.*s%s ", 8 - length(hex), "00000000", hex);
	}
}
'

HAVE_DATA_SIZE=0
HAVE_DATA_OFFSET=0

FIT_OUTPUT=$(mktemp) || exit 1

while IFS= read -r line
do
	if [[ "$line" = $DATA_BRACKET_START* ]]
	then
		TMPBIN=$(mktemp) || exit 1
		# The bracket style can be fed right into xxd
		echo "${line:${#DATA_BRACKET_START}:-2}" | xxd -r -p > ${TMPBIN}
	elif [[ "$line" = $DATA_ALLIGATOR_START* ]]
	then
		TMPBIN=$(mktemp) || exit 1
		# The alligator style is a bit more complex and needs fixed up before xxd
		echo "${line:${#DATA_BRACKET_START}:-2}" | \
		awk -e "${AWK_EXAPNDER}" | \
		xxd -r -p > ${TMPBIN}
	elif [[ "$line" = $DATA_SIZE_START* ]]
	then
		if [ ${HAVE_DATA_SIZE} -eq 1 ]
		then
			echo "Error: Extra data size tag detected"
			exit 1
		fi

		DATA_SIZE=${line:${#DATA_SIZE_START}:-2}
		HAVE_DATA_SIZE=1

		# If we don't have the other tag info then continue
		if [ ! ${HAVE_DATA_OFFSET} -eq 1 ]
		then
			continue
		fi

		TMPBIN=$(mktemp) || exit 1
		dd if=${INPUT_FILE} of=${TMPBIN} bs=1 skip=${DATA_OFFSET} count=$((${DATA_SIZE})) 2>/dev/null
		HAVE_DATA_SIZE=0
		HAVE_DATA_OFFSET=0

	elif [[ "$line" = $DATA_OFFSET_START* ]]
	then
		if [ ${HAVE_DATA_OFFSET} -eq 1 ]
		then
			echo "Error: Extra data offset tag detected"
			exit 1
		fi

		DATA_OFFSET=$((${line:${#DATA_OFFSET_START}:-2} + ${FDT_SIZE}))
		HAVE_DATA_OFFSET=1

		# If we don't have the other tag info then continue
		if [ ! ${HAVE_DATA_SIZE} -eq 1 ]
		then
			continue
		fi

		TMPBIN=$(mktemp) || exit 1
		dd if=${INPUT_FILE} of=${TMPBIN} bs=1 skip=${DATA_OFFSET} count=$((${DATA_SIZE})) 2>/dev/null
		HAVE_DATA_SIZE=0
		HAVE_DATA_OFFSET=0

	else
		echo "$line" >> ${FIT_OUTPUT}
		continue
	fi

	TMPBIN_SIGNED=$(mktemp) || exit 1
	${SIGN_SCRIPT} ${TMPBIN} ${TMPBIN_SIGNED}
	printf "\t\t\tdata = /incbin/(\"${TMPBIN_SIGNED}\");\n" >> ${FIT_OUTPUT}
done < ${FIT_SOURCE}

dtc -I dts -O dtb ${FIT_OUTPUT} > ${OUTPUT_FILE}
