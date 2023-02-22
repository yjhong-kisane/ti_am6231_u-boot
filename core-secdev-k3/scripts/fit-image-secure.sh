#!/bin/bash
#
# Script to run secure-binary-image.sh on binaries in a FIT image
#
# Note: This script is not very efficient resource-wise. This could
#       have been a C program for which the author is much more well-
#       versed. The reason for doing this as a shell script is to
#       remove the need to have a compiler on the machine doing the
#       signing, which may be a very miminal HSM. I'm almost certain
#       this could be done better even as a shell script, if you have
#       any suggestions or improvments, please feel free to email the
#       author below.
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

# Check for mkimage
if ! [ -x "$(command -v mkimage)" ]
then
	echo "Error: mkimage is not installed, install u-boot-tools package"
	exit 1
fi

# Check for dumpimage
if ! [ -x "$(command -v dumpimage)" ]
then
	echo "Error: dumpimage is not installed, install u-boot-tools package"
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
IMAGES_START="	images {"
CONFIG_START="	configurations {"
IMAGE_REGEXP="^		[[:print:]]+ \{$"

PROCESSING_IMAGES=0
IMAGE_COUNT=0

FIT_OUTPUT=$(mktemp) || exit 1

while IFS= read -r line
do
	if [[ "$line" == ${IMAGES_START} && ${PROCESSING_IMAGES} -eq 0 ]]
	then
		PROCESSING_IMAGES=1
	elif [[ "$line" == ${CONFIG_START} && ${PROCESSING_IMAGES} -eq 1 ]]
	then
		PROCESSING_IMAGES=0
	elif [[ "$line" =~ $IMAGE_REGEXP && ${PROCESSING_IMAGES} -eq 1 ]]
	then
		TMPBIN=$(mktemp) || exit 1
		dumpimage -T flat_dt ${INPUT_FILE} -p ${IMAGE_COUNT} -o ${TMPBIN} >/dev/null
		IMAGE_COUNT=$((IMAGE_COUNT+1))
	elif [[ "$line" = $DATA_BRACKET_START* || "$line" = $DATA_ALLIGATOR_START* || "$line" = $DATA_SIZE_START* ]]
	then
		if [ -z ${TMPBIN} ]
		then
			echo "Found data tag outside of images node"
			exit 1
		fi
		TMPBIN_SIGNED=$(mktemp) || exit 1
		${SIGN_SCRIPT} ${TMPBIN} ${TMPBIN_SIGNED}
		TMPBIN=""
		printf "\t\t\tdata = /incbin/(\"${TMPBIN_SIGNED}\");\n" >> ${FIT_OUTPUT}
		continue
	elif [[ "$line" = $DATA_OFFSET_START* ]]
	then
		continue
	fi
	echo "$line" >> ${FIT_OUTPUT}
done < ${FIT_SOURCE}

mkimage -f ${FIT_OUTPUT} -E ${OUTPUT_FILE} >/dev/null
