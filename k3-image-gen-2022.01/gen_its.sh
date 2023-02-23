#!/bin/sh
#
# Script to generate FIT image source for System Firmware (SYSFW) and
# associated configuration data based on a given SYSFW binary image plus
# multiple domain-specific fragments in binary format all specified via
# command line.
#
# Copyright (C) 2018-2019 Texas Instruments Incorporated - http://www.ti.com/
#	Andreas Dannenberg <dannenberg@ti.com>
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
# usage: $0 <soc_name> <soc_type> <config_name> <bin_name> [<bin_name> [<bin_name] ...]
#

SOC=$1
shift

SOC_TYPE=$1
shift

CONFIG=$1
shift

SYSFW_IMG_GEN_REV=`git describe --tags --abbrev=5 --dirty`

cat << __HEADER_EOF
/dts-v1/;

/ {
	description = "SYSFW and Config Fragments";
	#address-cells = <1>;

	creator = "SIG $SOC-$SOC_TYPE/$CONFIG-$SYSFW_IMG_GEN_REV";

	images {
__HEADER_EOF

for bin_name in $*
do
	cat << __CFG_IMAGE_EOF
		$(basename $bin_name ".${bin_name##*.}").bin {
			description = "$(basename $bin_name ".${bin_name##*.}")";
			data = /incbin/("$(basename $bin_name)");
			type = "firmware";
			arch = "arm";
			compression = "none";
		};
__CFG_IMAGE_EOF
done

cat << __ITS_EOF
	};
};
__ITS_EOF
