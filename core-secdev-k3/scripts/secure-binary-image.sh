#!/bin/bash
#
# Script to add x509 certificate to binary for K3
#
# Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
#       Andrew F. Davis <afd@ti.com>
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

function fn_display_usage {
	echo "Error: $1"
	echo ""
	echo "This script is used to secure a binary blob for the K3 platform."
	echo ""
	echo "Usage: secure-binary-image.sh <input-file-name> <output-file-name>"
	echo ""
	exit 1
}

# check where this tool is installed
PREFIX=$(dirname $0)/..
CUSTOMERKEY=${PREFIX}/keys/custMpk.pem
if [ ! -f ${CUSTOMERKEY} ]; then
	CUSTOMERKEY=${TI_SECURE_DEV_PKG}/keys/custMpk.pem
	if [ ! -f ${CUSTOMERKEY} ]; then
		fn_display_usage "Customer key cannot be found, correctly define TI_SECURE_DEV_PKG environment variable"
	fi
	PREFIX=${TI_SECURE_DEV_PKG}
fi

# Validate input parameters
if [ $# -lt 2 ]
then
	fn_display_usage "missing parameter"
fi

# Parse input options
INPUT_FILE=$1
OUTPUT_FILE=$2

# Get input file info
HS_SHA_VALUE=$(openssl dgst -sha512 -hex $INPUT_FILE | sed -e "s/^.*= //g")
HS_IMAGE_SIZE=$(cat $INPUT_FILE | wc -c)

# Get software revision info
HS_SWRV=$(cat ${PREFIX}/keys/swrv.txt)

# Parameters to get populated into the x509 template
HS_SED_OPTS="-e s/TEST_IMAGE_LENGTH/${HS_IMAGE_SIZE}/ "
HS_SED_OPTS+="-e s/TEST_IMAGE_SHA_VAL/${HS_SHA_VALUE}/ "
HS_SED_OPTS+="-e s/TEST_SWRV/${HS_SWRV}/ "
TMPX509=$(mktemp) || exit 1
cat ${PREFIX}/scripts/x509-template.txt | sed ${HS_SED_OPTS} > ${TMPX509}

# Generate x509 certificate
TMPCERT=$(mktemp) || exit 1

openssl req -new -x509 -key ${PREFIX}/keys/custMpk.pem -nodes -outform DER -out ${TMPCERT} -config ${TMPX509} -sha512

# Append x509 certificate
cat ${TMPCERT} $INPUT_FILE > $OUTPUT_FILE

# Cleanup
rm -f ${TMPX509} ${TMPCERT}
