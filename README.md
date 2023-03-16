# ti_am6231_u-boot

## SDK 정보

https://www.ti.com/tool/PROCESSOR-SDK-AM62X

ti-processor-sdk-linux-am62xx-evm-08.05.00.21 기반



## 참고 링크

https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/08_05_00_21/exports/docs/linux/Overview_Building_the_SDK.html

https://e2e.ti.com/support/processors-group/processors/f/processors-forum/1184048/tmds64evm-custom-build-tiboot3-bin-boot-failed

https://software-dl.ti.com/processor-sdk-linux/esd/AM64X/08_05_00_21/exports/docs/linux/Foundational_Components_Migration_Guide.html#k3-image-gen


"K3" Generation 이란 Texas Instrument’s K3 family of SoCs 을 의미.

https://u-boot.readthedocs.io/en/stable/board/ti/k3.html


"HS" platform 에서 HS 는 High Security 를 의미.

https://e2e.ti.com/support/processors-group/processors/f/processors-forum/1092354/tda4vm-what-is-the-difference-between-gp-and-hs-in-hardware

https://www.ti.com/lit/an/sprad04/sprad04.pdf?ts=1677060647496



## 의존성 패키지 설치

sudo apt-get install build-essential autoconf automake bison flex libssl-dev bc u-boot-tools python diffstat texinfo gawk chrpath dos2unix wget unzip socat doxygen libc6:i386 libncurses5:i386 libstdc++6:i386 libz1:i386 g++-multilib git python3-distutils python3-apt


## 툴체인

```bash
wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz
```


## 빌드 스크립트

SDK 설치 경로의 Makefile 과 Rules.make 파일을 참조하여 작성


```bash
#!/bin/bash

PATH_UBT=/home/yjhong/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01
PATH_IMG=/home/yjhong/kisan/TI_AM6231/image/mmcblk0p1
PATH_RFS=/home/yjhong/kisan/TI_AM6231/rootfs/trunk

CC_ARMV7=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-
CC_ARMV8=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
OBJ_DIR=am62x_evm

#Points to the root of the TI SDK
TI_SDK_PATH=/home/yjhong/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21

#u-boot machine
UBOOT_MACHINE_A53=am62x_evm_a53_defconfig
UBOOT_MACHINE_R5=am62x_evm_r5_config

UBOOT_ATF=${TI_SDK_PATH}/board-support/prebuilt-images/bl31.bin
UBOOT_TEE=${TI_SDK_PATH}/board-support/prebuilt-images/bl32.bin
#UBOOT_SYSFW=${TI_SDK_PATH}/board-support/prebuilt-images/sysfw.bin
UBOOT_DMFW=${TI_SDK_PATH}/board-support/prebuilt-images/ipc_echo_testb_mcu1_0_release_strip.xer5f


echo "### Start AM6231 Auto Making Script ###"

echo "### Checking permission"
AMIROOT=`whoami | awk {'print $1'}`
if [ "$AMIROOT" != "root" ] ; then
    echo "  **** Error *** must run script with sudo"
    echo ""
    exit
fi


export TI_SECURE_DEV_PKG=/home/yjhong/kisan/TI_AM6231/u-boot/trunk/core-secdev-k3
export TOOLCHAIN_PATH_ARMV7=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf
export TOOLCHAIN_PATH_ARMV8=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu



cd ${PATH_UBT}

echo "### Cleaning U-Boot"
make CROSS_COMPILE=${CC_ARMV8} distclean
make CROSS_COMPILE=${CC_ARMV7} distclean

rm -rf ${PATH_UBOOT}/${OBJ_DIR}
sync


echo "### Building U-Boot for A53"
make -j 2 CROSS_COMPILE=${CC_ARMV8} ${UBOOT_MACHINE_A53} ATF=${UBOOT_ATF} TEE=${UBOOT_TEE} DM=${UBOOT_DMFW} O=${OBJ_DIR}/a53 all
sync

echo "### Building U-Boot for R5"
make -j 2 CROSS_COMPILE=${CC_ARMV7} ${UBOOT_MACHINE_R5} O=${OBJ_DIR}/r5 all
make -j 2 CROSS_COMPILE=${CC_ARMV7} O=${OBJ_DIR}/r5 all
sync
cd ${PATH_UBT}/../k3-image-gen-2022.01
make SBL=${PATH_UBT}/${OBJ_DIR}/r5/spl/u-boot-spl.bin SYSFW_DL_URL="" SYSFW_HS_DL_URL="" SYSFW_HS_INNER_CERT_DL_URL="" SOC=am62x CONFIG=evm SYSFW_PATH=${TI_SDK_PATH}/board-support/prebuilt-images/ti-fs-firmware-am62x-gp.bin CROSS_COMPILE=${CC_ARMV7}
sync

echo "### Preparing SPL, Boot Partition Files (tispl.bin, u-boot.img)"
cd ${PATH_IMG}
rm -f tispl.bin
cp ${PATH_UBT}/${OBJ_DIR}/a53/tispl.bin .
#cp tispl /tftpboot

cd ${PATH_IMG}
rm -f u-boot.img
cp ${PATH_UBT}/${OBJ_DIR}/a53/u-boot.img .
#cp u-boot.img /tftpboot

cd ${PATH_IMG}
rm -f tiboot3.bin
cp ${PATH_UBT}/../k3-image-gen-2022.01/tiboot3-am62x-gp-evm.bin tiboot3.bin
#cp tiboot3.bin /tftpboot


#echo "### Copying uEnv.txt for NFS"
#cd ${PATH_IMG}
#cp -af uEnv_V2_NFS.txt /tftpboot

sync

echo "### End AM6231 Auto Maing Script ###"
```


## SD 카드 부팅 체크


```bash
U-Boot SPL 2021.01 (Feb 23 2023 - 13:18:40 +0900)
SYSFW ABI: 3.1 (firmware rev 0x0008 '8.5.3--v08.05.03 (Chill Capybar')
SPL initial stack usage: 13424 bytes
Trying to boot from MMC2
Warning: Detected image signing certificate on GP device. Skipping certificate to prevent boot failure. This will fail if the image was also encrypted
Warning: Detected image signing certificate on GP device. Skipping certificate to prevent boot failure. This will fail if the image was also encrypted
Loading Environment from MMC... *** Warning - No MMC card found, using default environment

Starting ATF on ARM64 core...

NOTICE:  BL31: v2.7(release):v2.7.0-359-g1309c6c805-dirty
NOTICE:  BL31: Built : 11:48:12, Dec 14 2022
I/TC:
I/TC: OP-TEE version: 3.19.0-15-gd6c5d0037 (gcc version 9.2.1 20191025 (GNU Toolchain for the A-profile Architecture 9.2-2019.12 (arm-9.10))) #1 Wed Dec 14 11:52:03 UTC 2022 aarch64
I/TC: WARNING: This OP-TEE configuration might be insecure!
I/TC: WARNING: Please check https://optee.readthedocs.io/en/latest/architecture/porting_guidelines.html
I/TC: Primary CPU initializing
I/TC: SYSFW ABI: 3.1 (firmware rev 0x0008 '8.5.3--v08.05.03 (Chill Capybar')
I/TC: HUK Initialized
I/TC: Activated SA2UL device
I/TC: Fixing SA2UL firewall owner for GP device
I/TC: Enabled firewalls for SA2UL TRNG device
I/TC: SA2UL TRNG initialized
I/TC: SA2UL Drivers initialized
I/TC: Primary CPU switching to normal world boot

U-Boot SPL 2021.01 (Feb 22 2023 - 20:13:40 +0900)
SYSFW ABI: 3.1 (firmware rev 0x0008 '8.5.3--v08.05.03 (Chill Capybar')
Trying to boot from MMC2


U-Boot 2021.01 (Feb 22 2023 - 20:13:40 +0900)

SoC:   AM62X SR1.0 GP
Model: Texas Instruments AM625 SK
EEPROM not available at 0x50, trying to read at 0x51
Board: AM62-SKEVM rev E3
DRAM:  2 GiB
MMC:   mmc@fa10000: 0, mmc@fa00000: 1, mmc@fa20000: 2
Loading Environment from MMC... OK
In:    serial@2800000
Out:   serial@2800000
Err:   serial@2800000
Net:   eth0: ethernet@8000000port@1
Hit any key to stop autoboot:  0
switch to partitions #0, OK
mmc1(part 0) is current device
SD/MMC found on device 1
Failed to load 'boot.scr'
1490 bytes read in 2 ms (727.5 KiB/s)
Loaded env from uEnv.txt
Importing environment from mmc1 ...
Running uenvcmd ...
1 bytes read in 2 ms (0 Bytes/s)
Already setup.
18608640 bytes read in 734 ms (24.2 MiB/s)
55468 bytes read in 5 ms (10.6 MiB/s)
## Flattened Device Tree blob at 88000000
   Booting using the fdt blob at 0x88000000
   Loading Device Tree to 000000008feef000, end 000000008fffffff ... OK

Starting kernel ...

```



