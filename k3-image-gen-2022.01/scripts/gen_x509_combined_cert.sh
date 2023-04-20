#!/bin/bash
#
# Script to add x509 certificate to binary/ELF
#
# Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Variables
VALID_SHAS="sha256 sha384 sha512 sha224"
BUILD_DIR=${O:- .}
OUTPUT=$BUILD_DIR/x509-firmware.bin
TEMP_X509=$BUILD_DIR/x509-temp.cert
CERT=$BUILD_DIR/certificate.bin
RAND_KEY=$BUILD_DIR/eckey.pem
VALID_ROM_CORES="r5 m3"
VALID_DMSC_CORES="r5-00 r5-01 a53-00 a53-01 a53-10 a53-11"
SHA=sha512
CORE=m3
VALID_MASTERS="rom dmsc"

declare -A sha_oids
sha_oids["sha256"]=2.16.840.1.101.3.4.2.1
sha_oids["sha384"]=2.16.840.1.101.3.4.2.2
sha_oids["sha512"]=2.16.840.1.101.3.4.2.3
sha_oids["sha224"]=2.16.840.1.101.3.4.2.4

declare -A core_ids
core_ids["r5-00"]=0x01

gen_key() {
	openssl ecparam -out $RAND_KEY -name prime256v1 -genkey
	KEY=$RAND_KEY
}

declare -A options_help
usage() {
	if [ -n "$*" ]; then
		echo "ERROR: $*"
	fi
	echo -n "Usage: $0 "
	for option in "${!options_help[@]}"
	do
		arg=`echo ${options_help[$option]}|cut -d ':' -f1`
		if [ -n "$arg" ]; then
			arg=" $arg"
		fi
		echo -n "[-$option$arg] "
	done
	echo
	echo -e "\nWhere:"
	for option in "${!options_help[@]}"
	do
		arg=`echo ${options_help[$option]}|cut -d ':' -f1`
		txt=`echo ${options_help[$option]}|cut -d ':' -f2`
		tb="\t\t\t"
		if [ -n "$arg" ]; then
			arg=" $arg"
			tb="\t"
		fi
		echo -e "   -$option$arg:$tb$txt"
	done
	echo
	echo "Examples of usage:-"
	echo "# Example of generation a combined boot image"
	echo "    $0 -b u-boot-spl.bin -l 0x41c00000 -s ti-sci-firmware-j7200-gp-vlab.bin -m 0x40000 -d combined-cfg.bin -n 0x7f000 -o tiboot3.bin"
	echo
	echo "# Example of generation of a split boardcfg image for use with DM firmware"
	echo "    $0 -b u-boot-spl.bin -l 0x41c00000 -s ti-fs-firmware-j7200-gp.bin -m 0x40000 -d combined-tifs-cfg.bin -n 0x7f000 -t out/soc/j7200/evm/combined-dm-cfg.bin -y 0x41c80000 -k ti-degenerate-key.pem -o tiboot3.bin"
}

options_help[b]="Boot Loader:Bin file corresponding to boot loader on R5"
options_help[l]="SBL loadaddress: R5 Bootloader load address"
options_help[s]="SYSFW: Bin file corresponding to sysfw image"
options_help[m]="SYSFW loadaddress: SYSFW image load address"
options_help[d]="SYSFW_DATA: Bin file corresponding to combined board configurations"
options_help[n]="SYSFW_DATA loadaddr: Combine board configuration load address"
options_help[t]="DM_DATA: Bin file corresponding to combined board configurations for RM and PM. If this is used, RM and PM do not need to be provided as part of SYSFW_DATA. (OPTIONAL)"
options_help[y]="DM_DATA loadaddr: Combine RM and PM blob board configuration load address (OPTIONAL)"
options_help[k]="key_file:file with key inside it. If not provided script generates a raindom key."
options_help[r]="sw-rev: Software Revision other than 0. If not provided defaults to 0."
options_help[c]="SYSFW CERT: SYSFW Inner Certificate"

SW_REV=0
while getopts "b:l:s:m:d:n:k:o:h:t:y:r:c:" opt
do
	case $opt in
	b)
		SBL=$OPTARG
	;;
	l)
		SBL_LOADADDR=$OPTARG
	;;
	s)
		SYSFW=$OPTARG
	;;
	m)
		SYSFW_LOADADDR=$OPTARG
	;;
	d)
		SYSFW_DATA=$OPTARG
	;;
	n)
		SYSFW_DATA_LOADADDR=$OPTARG
	;;
	t)
		DM_DATA=$OPTARG
	;;
	y)
		DM_DATA_LOADADDR=$OPTARG
	;;
	k)
		KEY=$OPTARG
	;;
	o)
		OUTPUT=$OPTARG
	;;
        r)
		SW_REV=$OPTARG
	;;
        c)
		SYSFW_INNER_CERT=$OPTARG
	;;
	h)
		usage
		exit 0
	;;
	\?)
		usage "Invalid Option '-$OPTARG'"
		exit 1
	;;
	:)
		usage "Option '-$OPTARG' Needs an argument."
		exit 1
	;;
	esac
done

if [ "$#" -eq 0 ]
then
	usage "Arguments missing"
	exit 1
fi

if [ -z "$SBL" -o -z "$SBL_LOADADDR" ]; then
	usage "Bootloader and its loadaddr are compulsory"
	exit 1
fi

if [ -z "$SYSFW" -o -z "$SYSFW_LOADADDR" ]; then
	usage "SYSFW and its loadaddr are compulsory"
	exit 1
fi

if [ -z "$SYSFW_DATA" -o -z "$SYSFW_DATA_LOADADDR" ]; then
	usage "SYSFW board configuration and its loadaddr are compulsory"
	exit 1
fi

# Generate random key if user doesn't provide a key
if [ -z "$KEY" ]; then
	gen_key
fi

SHA_OID=${sha_oids["$SHA"]}

SBL_SHA_VAL=`openssl dgst -$SHA -hex $SBL | sed -e "s/^.*= //g"`
SBL_SIZE=`cat $SBL | wc -c`
SBL_ADDR=`printf "%08x" $SBL_LOADADDR`

SYSFW_SHA_VAL=`openssl dgst -$SHA -hex $SYSFW | sed -e "s/^.*= //g"`
SYSFW_SIZE=`cat $SYSFW | wc -c`
SYSFW_ADDR=`printf "%08x" $SYSFW_LOADADDR`

SYSFW_DATA_SHA_VAL=`openssl dgst -$SHA -hex $SYSFW_DATA | sed -e "s/^.*= //g"`
SYSFW_DATA_SIZE=`cat $SYSFW_DATA | wc -c`
SYSFW_DATA_ADDR=`printf "%08x" $SYSFW_DATA_LOADADDR`

NUM_COMPS_COUNT=3

# Only process Inner Certificate if this variable is provided, or set size to 0 and num_comps to 3 for cert
if [ -n "$SYSFW_INNER_CERT" ]; then
       SYSFW_INNER_CERT_SHA_VAL=`openssl dgst -$SHA -hex $SYSFW_INNER_CERT | sed -e "s/^.*= //g"`
       SYSFW_INNER_CERT_SIZE=`cat $SYSFW_INNER_CERT | wc -c`
       NUM_COMPS_COUNT=$(expr $NUM_COMPS_COUNT + 1)
       SYSFW_INNER_CERT_EXT_BOOT_SEQUENCE_STRING="sysfw_inner_cert=SEQUENCE:sysfw_inner_cert"
read -r -d '' SYSFW_INNER_CERT_EXT_BOOT_BLOCK << EOM
\\
 [sysfw_inner_cert]\\
 compType = INTEGER:3\\
 bootCore = INTEGER:0\\
 compOpts = INTEGER:0\\
 destAddr = FORMAT:HEX,OCT:00000000\\
 compSize = INTEGER:SYSFW_INNER_CERT_IMAGE_SIZE\\
 shaType  = OID:SYSFW_INNER_CERT_SHA_OID\\
 shaValue = FORMAT:HEX,OCT:SYSFW_INNER_CERT_SHA_VAL
EOM
else
       SYSFW_INNER_CERT_SIZE=`printf "%08x" 0`
       SYSFW_INNER_CERT_EXT_BOOT_SEQUENCE_STRING=""
       SYSFW_INNER_CERT_EXT_BOOT_BLOCK=""
fi

# Only process DM_DATA is variable is provided, or set size to 0 and num_comps to 3 for cert
if [ -n "$DM_DATA" ]; then
	DM_DATA_SHA_VAL=`openssl dgst -$SHA -hex $DM_DATA | sed -e "s/^.*= //g"`
	DM_DATA_SIZE=`cat $DM_DATA | wc -c`
	DM_DATA_ADDR=`printf "%08x" $DM_DATA_LOADADDR`
	NUM_COMPS_COUNT=$(expr $NUM_COMPS_COUNT + 1)
	DM_DATA_EXT_BOOT_SEQUENCE_STRING="dm_data=SEQUENCE:dm_data"
read -r -d '' DM_DATA_EXT_BOOT_BLOCK << EOM
\\
 [dm_data]\\
 compType = INTEGER:17\\
 bootCore = INTEGER:16\\
 compOpts = INTEGER:0\\
 destAddr = FORMAT:HEX,OCT:DM_DATA_DEST_ADDR\\
 compSize = INTEGER:DM_DATA_IMAGE_SIZE\\
 shaType  = OID:DM_DATA_IMAGE_SHA_OID\\
 shaValue = FORMAT:HEX,OCT:DM_DATA_IMAGE_SHA_VAL
EOM
else
	DM_DATA_SIZE=`printf "%08x" 0`
	DM_DATA_EXT_BOOT_SEQUENCE_STRING=""
	DM_DATA_EXT_BOOT_BLOCK=""
fi

TOTAL_SIZE=$(expr $SBL_SIZE + $SYSFW_SIZE + $SYSFW_DATA_SIZE + $SYSFW_INNER_CERT_SIZE + $DM_DATA_SIZE)

# Generate x509 Template
gen_template() {
cat << 'EOF' > $TEMP_X509
 [ req ]
 distinguished_name     = req_distinguished_name
 x509_extensions        = v3_ca
 prompt                 = no
 dirstring_type         = nobmp

 [ req_distinguished_name ]
 C                      = US
 ST                     = TX
 L                      = Dallas
 O                      = Texas Instruments Incorporated
 OU                     = Processors
 CN                     = TI Support
 emailAddress           = support@ti.com


 [ v3_ca ]
 basicConstraints = CA:true
 1.3.6.1.4.1.294.1.3=ASN1:SEQUENCE:swrv
 1.3.6.1.4.1.294.1.9=ASN1:SEQUENCE:ext_boot_info

 [swrv]
 swrv=INTEGER:SW_REV

 [ext_boot_info]
 extImgSize=INTEGER:TOTAL_IMAGE_LENGTH
 numComp=INTEGER:NUM_COMPS_COUNT
 sbl=SEQUENCE:sbl
 sysfw=SEQUENCE:sysfw
 sysfw_data=SEQUENCE:sysfw_data
 SYSFW_INNER_CERT_EXT_BOOT_SEQUENCE_STRING
 DM_DATA_EXT_BOOT_SEQUENCE_STRING

 [sbl]
 compType = INTEGER:1
 bootCore = INTEGER:16
 compOpts = INTEGER:0
 destAddr = FORMAT:HEX,OCT:SBL_DEST_ADDR
 compSize = INTEGER:SBL_IMAGE_SIZE
 shaType  = OID:SBL_IMAGE_SHA_OID
 shaValue = FORMAT:HEX,OCT:SBL_IMAGE_SHA_VAL

 [sysfw]
 compType = INTEGER:2
 bootCore = INTEGER:0
 compOpts = INTEGER:0
 destAddr = FORMAT:HEX,OCT:SYSFW_DEST_ADDR
 compSize = INTEGER:SYSFW_IMAGE_SIZE
 shaType  = OID:SYSFW_IMAGE_SHA_OID
 shaValue = FORMAT:HEX,OCT:SYSFW_IMAGE_SHA_VAL

 [sysfw_data]
 compType = INTEGER:18
 bootCore = INTEGER:0
 compOpts = INTEGER:0
 destAddr = FORMAT:HEX,OCT:SYSFW_DATA_DEST_ADDR
 compSize = INTEGER:SYSFW_DATA_IMAGE_SIZE
 shaType  = OID:SYSFW_DATA_IMAGE_SHA_OID
 shaValue = FORMAT:HEX,OCT:SYSFW_DATA_IMAGE_SHA_VAL
 SYSFW_INNER_CERT_EXT_BOOT_BLOCK
 DM_DATA_EXT_BOOT_BLOCK
EOF
}

gen_cert() {
	echo "Certificate being generated :"
	#echo $SW_REV
	sed -i "s/SW_REV/$SW_REV/"  $TEMP_X509
	#echo $SBL_ADDR $SBL_SIZE $SBL_SHA_VAL
	sed -i "s/NUM_COMPS_COUNT/$NUM_COMPS_COUNT/"  $TEMP_X509
	sed -i "s/SBL_DEST_ADDR/$SBL_ADDR/"  $TEMP_X509
	sed -i "s/SBL_IMAGE_SIZE/$SBL_SIZE/" $TEMP_X509
	sed -i "s/SBL_IMAGE_SHA_OID/$SHA_OID/" $TEMP_X509
	sed -i "s/SBL_IMAGE_SHA_VAL/$SBL_SHA_VAL/" $TEMP_X509
	#echo $SYSFW_ADDR $SYSFW_SIZE $SYSFW_SHA_VAL
	sed -i "s/SYSFW_DEST_ADDR/$SYSFW_ADDR/" $TEMP_X509
	sed -i "s/SYSFW_IMAGE_SIZE/$SYSFW_SIZE/" $TEMP_X509
	sed -i "s/SYSFW_IMAGE_SHA_OID/$SHA_OID/" $TEMP_X509
	sed -i "s/SYSFW_IMAGE_SHA_VAL/$SYSFW_SHA_VAL/" $TEMP_X509
	#echo $SYSFW_DATA_ADDR $SYSFW_DATA_SIZE $SYSFW_DATA_SHA_VAL
	sed -i "s/SYSFW_DATA_DEST_ADDR/$SYSFW_DATA_ADDR/" $TEMP_X509
	sed -i "s/SYSFW_DATA_IMAGE_SIZE/$SYSFW_DATA_SIZE/" $TEMP_X509
	sed -i "s/SYSFW_DATA_IMAGE_SHA_OID/$SHA_OID/" $TEMP_X509
	sed -i "s/SYSFW_DATA_IMAGE_SHA_VAL/$SYSFW_DATA_SHA_VAL/" $TEMP_X509
	#echo $SYSFW_INNER_CERT_ADDR $SYSFW_INNER_CERT_SIZE $SYSFW_INNER_CERT_VAL
	sed -i "s/SYSFW_INNER_CERT_EXT_BOOT_BLOCK/$SYSFW_INNER_CERT_EXT_BOOT_BLOCK/" $TEMP_X509
	sed -i "s/SYSFW_INNER_CERT_EXT_BOOT_SEQUENCE_STRING/$SYSFW_INNER_CERT_EXT_BOOT_SEQUENCE_STRING/" $TEMP_X509
	sed -i "s/SYSFW_INNER_CERT_DEST_ADDR/$SYSFW_INNER_CERT_ADDR/" $TEMP_X509
	sed -i "s/SYSFW_INNER_CERT_IMAGE_SIZE/$SYSFW_INNER_CERT_SIZE/" $TEMP_X509
	sed -i "s/SYSFW_INNER_CERT_SHA_OID/$SHA_OID/" $TEMP_X509
	sed -i "s/SYSFW_INNER_CERT_SHA_VAL/$SYSFW_INNER_CERT_SHA_VAL/" $TEMP_X509
	#echo $DM_DATA_ADDR $DM_DATA_SIZE $DM_DATA_SHA_VAL
	sed -i "s/DM_DATA_EXT_BOOT_BLOCK/$DM_DATA_EXT_BOOT_BLOCK/" $TEMP_X509
	sed -i "s/DM_DATA_EXT_BOOT_SEQUENCE_STRING/$DM_DATA_EXT_BOOT_SEQUENCE_STRING/" $TEMP_X509
	sed -i "s/DM_DATA_DEST_ADDR/$DM_DATA_ADDR/" $TEMP_X509
	sed -i "s/DM_DATA_IMAGE_SIZE/$DM_DATA_SIZE/" $TEMP_X509
	sed -i "s/DM_DATA_IMAGE_SHA_OID/$SHA_OID/" $TEMP_X509
	sed -i "s/DM_DATA_IMAGE_SHA_VAL/$DM_DATA_SHA_VAL/" $TEMP_X509
	#echo $TOTAL_SIZE
	sed -i "s/TOTAL_IMAGE_LENGTH/$TOTAL_SIZE/" $TEMP_X509
	openssl req -new -x509 -key $KEY -nodes -outform DER -out $CERT -config $TEMP_X509 -$SHA
}

gen_template
gen_cert
cat $CERT $SBL $SYSFW $SYSFW_DATA $SYSFW_INNER_CERT $DM_DATA > $OUTPUT

echo "SUCCESS: Image $OUTPUT generated."

# Remove all intermediate files
rm $TEMP_X509 $CERT
if [ "$KEY" == "$RAND_KEY" ]; then
	rm $RAND_KEY
fi
