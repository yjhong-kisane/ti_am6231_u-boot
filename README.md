# ti_am6231_u-boot

## SDK 정보

https://www.ti.com/tool/PROCESSOR-SDK-AM62X

ti-processor-sdk-linux-am62xx-evm-08.05.00.21 기반



## 참고 링크

https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/08_05_00_21/exports/docs/linux/Overview_Building_the_SDK.html




## 의존성 패키지 설치

sudo apt-get install build-essential autoconf automake bison flex libssl-dev bc u-boot-tools python diffstat texinfo gawk chrpath dos2unix wget unzip socat doxygen libc6:i386 libncurses5:i386 libstdc++6:i386 libz1:i386 g++-multilib git python3-distutils python3-apt


## 빌드 방법

SDK 설치 경로의 Makefile 과 Rules.make 파일을 참조


빌드 방법 #1
```cpp
yjhong@ubuntu18:~/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21$ make u-boot-a53
===================================
Building U-boot for A53
===================================

make -j 2 -C /home/yjhong/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21/board-support/u-boot-* CROSS_COMPILE=/home/yjhong/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/aarch64-none-linux-gnu- \
     am62x_evm_a53_defconfig O=/home/yjhong/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21/board-support/u-boot_build/a53
make[1]: 디렉터리 '/home/yjhong/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21/board-support/u-boot-2021.01+gitAUTOINC+3983bffabc-g3983bffabc' 들어감
make[2]: 디렉터리 '/home/yjhong/kisan/TI_AM6231/ti-processor-sdk-linux-am62xx-evm-08.05.00.21/board-support/u-boot_build/a53' 들어감
  GEN     ./Makefile
  HOSTCC  scripts/basic/fixdep
...
```


빌드 방법 #2
```cpp
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01/configs$ ls -al
...
-rw-r--r-- 1 yjhong yjhong 2799 12월 14 20:42 am62ax_evm_a53_defconfig
-rw-r--r-- 1 yjhong yjhong 2465 12월 14 20:42 am62ax_evm_r5_defconfig
-rw-r--r-- 1 yjhong yjhong 4756 12월 14 20:42 am62x_evm_a53_defconfig
-rw-r--r-- 1 yjhong yjhong 3375 12월 14 20:42 am62x_evm_r5_defconfig
-rw-r--r-- 1 yjhong yjhong 2986 12월 14 20:42 am62x_evm_r5_ethboot_defconfig
-rw-r--r-- 1 yjhong yjhong 3480 12월 14 20:42 am62x_evm_r5_usbdfu_defconfig
-rw-r--r-- 1 yjhong yjhong 4645 12월 14 20:42 am62x_lpsk_a53_defconfig
-rw-r--r-- 1 yjhong yjhong 3009 12월 14 20:42 am62x_lpsk_r5_defconfig
-rw-r--r-- 1 yjhong yjhong 5484 12월 14 20:42 am64x_evm_a53_defconfig
-rw-r--r-- 1 yjhong yjhong 4718 12월 14 20:42 am64x_evm_r5_defconfig
-rw-r--r-- 1 yjhong yjhong 5094 12월 14 20:42 am65x_evm_a53_defconfig
-rw-r--r-- 1 yjhong yjhong 3562 12월 14 20:42 am65x_evm_r5_defconfig
-rw-r--r-- 1 yjhong yjhong 3146 12월 14 20:42 am65x_evm_r5_usbdfu_defconfig
-rw-r--r-- 1 yjhong yjhong 3054 12월 14 20:42 am65x_evm_r5_usbmsc_defconfig
-rw-r--r-- 1 yjhong yjhong 4873 12월 14 20:42 am65x_hs_evm_a53_defconfig
-rw-r--r-- 1 yjhong yjhong 3624 12월 14 20:42 am65x_hs_evm_r5_defconfig
...
```

```cpp
R5 용 컴파일러
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01$ export TOOLCHAIN_PATH_ARMV7=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf

A53용 컴파일러
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01$ export TOOLCHAIN_PATH_ARMV8=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu
```

```cpp
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk$ git clone https://git.ti.com/git/security-development-tools/core-secdev-k3.git -b master
'core-secdev-k3'에 복제합니다...
remote: Enumerating objects: 43, done.
remote: Counting objects: 100% (43/43), done.
remote: Compressing objects: 100% (41/41), done.
remote: Total 43 (delta 13), reused 0 (delta 0), pack-reused 0
오브젝트 묶음 푸는 중: 100% (43/43), 완료.
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk$ ll
합계 24
drwxrwxr-x  5 yjhong yjhong 4096  2월 22 17:38 ./
drwxrwxr-x  3 yjhong yjhong 4096  2월 22 14:26 ../
drwxrwxr-x  8 yjhong yjhong 4096  2월 22 14:29 .git/
-rw-rw-r--  1 yjhong yjhong   18  2월 22 14:22 README.md
drwxrwxr-x  6 yjhong yjhong 4096  2월 22 17:38 core-secdev-k3/
lrwxrwxrwx  1 yjhong yjhong   48  2월 22 14:26 u-boot-2021.01 -> u-boot-2021.01+gitAUTOINC+3983bffabc-g3983bffabc/
drwxr-xr-x 24 yjhong yjhong 4096  2월 22 17:23 u-boot-2021.01+gitAUTOINC+3983bffabc-g3983bffabc/

yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01$ export TI_SECURE_DEV_PKG=/home/yjhong/kisan/TI_AM6231/u-boot/trunk/core-secdev-k3
```


```cpp
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01$ make mrproper
  CLEAN   scripts/basic
  CLEAN   scripts/kconfig
  CLEAN   .config
```

```cpp
UBOOT_ATF=${TI_SDK_PATH}/board-support/prebuilt-images/bl31.bin
UBOOT_TEE=${TI_SDK_PATH}/board-support/prebuilt-images/bl32.bin
UBOOT_SYSFW=${TI_SDK_PATH}/board-support/prebuilt-images/sysfw.bin
UBOOT_DMFW=${TI_SDK_PATH}/board-support/prebuilt-images/ipc_echo_testb_mcu1_0_release_strip.xer5f
```

```cpp
yjhong@ubuntu18:~/kisan/TI_AM6231/u-boot/trunk/u-boot-2021.01$ make -j2 CROSS_COMPILE=/home/yjhong/kisan/TI_AM6231/toolchain/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu- ATF=${UBOOT_ATF} TEE=${UBOOT_TEE} DM=${UBOOT_DMFW} O=am62x_evm am62x_evm_a53_defconfig all
make[1]: 디렉터리 '/home/yjhong/kisan/TI_AM6231/u-boot/ti_am6231_u-boot/u-boot-2021.01+gitAUTOINC+3983bffabc-g3983bffabc/am62x_evm' 들어감
  GEN     ./Makefile
#
# configuration written to .config
#
  GEN     ./Makefile
scripts/kconfig/conf  --syncconfig Kconfig
  CFG     u-boot.cfg
  GEN     include/autoconf.mk
  GEN     include/autoconf.mk.dep
  CFG     spl/u-boot.cfg
  GEN     spl/include/autoconf.mk
===================== WARNING ======================
This board uses CONFIG_SPL_FIT_GENERATOR. Please migrate
to binman instead, to avoid the proliferation of
arch-specific scripts with no tests.
====================================================
  CFGCHK  u-boot.cfg
  Using .. as source for U-Boot
  GEN     ./Makefile
  UPD     include/generated/timestamp_autogenerated.h
  HOSTCC  tools/mkenvimage.o
  HOSTLD  tools/mkenvimage
  HOSTCC  tools/fit_image.o
  HOSTCC  tools/image-host.o
  HOSTCC  tools/dumpimage.o
  HOSTLD  tools/dumpimage
  HOSTCC  tools/mkimage.o
  HOSTLD  tools/mkimage
  CC      arch/arm/cpu/armv8/fwcall.o
  LD      arch/arm/cpu/armv8/built-in.o
  CC      cmd/version.o
  LD      cmd/built-in.o
  CC      common/main.o
  LD      common/built-in.o
  CC      drivers/fastboot/fb_getvar.o
  LD      drivers/fastboot/built-in.o
  LD      drivers/built-in.o
  CC      lib/smbios.o
  CC      lib/display_options.o
  LD      lib/built-in.o
  LD      u-boot
  OBJCOPY u-boot-nodtb.bin
  RELOC   u-boot-nodtb.bin
  SECURE  u-boot-nodtb.bin_HS
  DTC     arch/arm/dts/k3-am625-sk.dtb
  DTC     arch/arm/dts/k3-am625-r5-sk.dtb
  DTC     arch/arm/dts/k3-am62x-lp-sk.dtb
  DTC     arch/arm/dts/k3-am62x-r5-lp-sk.dtb
  SHIPPED dts/dt.dtb
  FDTGREP dts/dt-spl.dtb
  MKIMAGE u-boot.img
  SECURE  arch/arm/dts/k3-am625-sk.dtb_HS
  MKIMAGE u-boot.img_HS
  OBJCOPY u-boot.srec
  MKIMAGE fit-dtb.blob
  CAT     u-boot-fit-dtb.bin
  COPY    u-boot.bin
  SYM     u-boot.sym
  CC      spl/arch/arm/cpu/armv8/fwcall.o
  LD      spl/arch/arm/cpu/armv8/built-in.o
  CC      spl/common/spl/spl.o
  LD      spl/common/spl/built-in.o
  CC      spl/lib/display_options.o
  LD      spl/lib/built-in.o
  LD      spl/u-boot-spl
  OBJCOPY spl/u-boot-spl-nodtb.bin
  SECURE  spl/u-boot-spl-nodtb.bin_HS
  DTC     arch/arm/dts/k3-am625-sk.dtb
  DTC     arch/arm/dts/k3-am625-r5-sk.dtb
  DTC     arch/arm/dts/k3-am62x-lp-sk.dtb
  DTC     arch/arm/dts/k3-am62x-r5-lp-sk.dtb
  SHIPPED dts/dt.dtb
  FDTGREP dts/dt-spl.dtb
  FDTGREP spl/dts/k3-am625-sk.dtb
  SECURE  spl/dts/k3-am625-sk.dtb_HS
  MKITS   u-boot-spl-k3_HS.its
WARNING ATF file bl31.bin NOT found, resulting binary is non-functional
WARNING OPTEE file bl32.bin NOT found, resulting might be non-functional
  MKIMAGE tispl.bin_HS
FIT description: Configuration to load ATF and SPL
Created:         Wed Feb 22 17:42:18 2023
Image 0 (atf)
  Description:  ARM Trusted Firmware
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Firmware
  Compression:  uncompressed
  Data Size:    0 Bytes = 0.00 KiB = 0.00 MiB
  Architecture: AArch64
  OS:           ARM Trusted Firmware
  Load Address: 0x9e780000
Image 1 (tee)
  Description:  OPTEE
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Trusted Execution Environment Image
  Compression:  uncompressed
  Data Size:    0 Bytes = 0.00 KiB = 0.00 MiB
Image 2 (dm)
  Description:  DM binary
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Firmware
  Compression:  uncompressed
  Data Size:    0 Bytes = 0.00 KiB = 0.00 MiB
  Architecture: Unknown Architecture
  OS:           Unknown OS
  Load Address: 0x89000000
Image 3 (spl)
  Description:  SPL (64-bit)
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Standalone Program
  Compression:  uncompressed
  Data Size:    315673 Bytes = 308.27 KiB = 0.30 MiB
  Architecture: AArch64
  Load Address: 0x80080000
  Entry Point:  0x80080000
Image 4 (k3-am625-sk.dtb)
  Description:  k3-am625-sk
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Flat Device Tree
  Compression:  uncompressed
  Data Size:    20389 Bytes = 19.91 KiB = 0.02 MiB
  Architecture: ARM
Default Configuration: 'k3-am625-sk.dtb'
Configuration 0 (k3-am625-sk.dtb)
  Description:  k3-am625-sk
  Kernel:       unavailable
  Firmware:     atf
  FDT:          k3-am625-sk.dtb
  Loadables:    tee
                dm
                spl
  MKIMAGE tispl.bin
FIT description: Configuration to load ATF and SPL
Created:         Wed Feb 22 17:42:18 2023
Image 0 (atf)
  Description:  ARM Trusted Firmware
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Firmware
  Compression:  uncompressed
  Data Size:    0 Bytes = 0.00 KiB = 0.00 MiB
  Architecture: AArch64
  OS:           ARM Trusted Firmware
  Load Address: 0x9e780000
Image 1 (tee)
  Description:  OPTEE
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Trusted Execution Environment Image
  Compression:  uncompressed
  Data Size:    0 Bytes = 0.00 KiB = 0.00 MiB
Image 2 (dm)
  Description:  DM binary
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Firmware
  Compression:  uncompressed
  Data Size:    0 Bytes = 0.00 KiB = 0.00 MiB
  Architecture: Unknown Architecture
  OS:           Unknown OS
  Load Address: 0x89000000
Image 3 (spl)
  Description:  SPL (64-bit)
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Standalone Program
  Compression:  uncompressed
  Data Size:    315673 Bytes = 308.27 KiB = 0.30 MiB
  Architecture: AArch64
  Load Address: 0x80080000
  Entry Point:  0x80080000
Image 4 (k3-am625-sk.dtb)
  Description:  k3-am625-sk
  Created:      Wed Feb 22 17:42:18 2023
  Type:         Flat Device Tree
  Compression:  uncompressed
  Data Size:    20389 Bytes = 19.91 KiB = 0.02 MiB
  Architecture: ARM
Default Configuration: 'k3-am625-sk.dtb'
Configuration 0 (k3-am625-sk.dtb)
  Description:  k3-am625-sk
  Kernel:       unavailable
  Firmware:     atf
  FDT:          k3-am625-sk.dtb
  Loadables:    tee
                dm
                spl
  MKIMAGE spl/u-boot-spl.multidtb.fit
  CAT     spl/u-boot-spl-dtb.bin
  COPY    spl/u-boot-spl.bin
  SYM     spl/u-boot-spl.sym
  COPY    u-boot.dtb
  MKIMAGE u-boot-dtb.img
make[1]: 디렉터리 '/home/yjhong/kisan/TI_AM6231/u-boot/ti_am6231_u-boot/u-boot-2021.01+gitAUTOINC+3983bffabc-g3983bffabc/am62x_evm' 나감
```






