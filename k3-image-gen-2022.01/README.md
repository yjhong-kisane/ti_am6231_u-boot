System Firmware (SYSFW) and Configuration Image Generator TI K3 Family SoCs
===========================================================================

Overview
--------
This tool is intended to be a simple solution to allow users to create an image
tree blob (a.k.a. FIT image) comprising a signed System Firmware image as well
as the binary configuration artifacts needed to bring up SYSFW as part of the
U-Boot SPL startup. Note that the final SYSFW configuration itself is expected
to be performed by the end user by directly modifying different C source files
included into this project as needed for an application and board-specific use
case. The domain-specific configuration artifacts to be tailored are:

* *board-cfg.c* contains the general board configuration
* *pm-cfg.c* contains the power management / clock related configuration
* *rm-cfg.c* contains the resource management / allocation related configuration
* *sec-cfg.c* contains the security configuration
* *tifs-rm-cfg.c* contains stripped down version of resource management related
configuration

These files exist under {srcroot}/soc/{soc}/{configuration}/ folders, Where:
* srcroot - Is the root folder of source code
* soc - Is one of the supported SoCs. Example: am65x
* configuration - This is one of the supported configurations for various
  resource division desired. Example: evm

NOTE: The definitions for the same are available under
{srcroot}/include/soc/{soc} folder

The build process consumes a raw (unsigned) SYSFW binary image as released by
the SYSFW development team and signs it by adding an X.509 certificate using a
random key.

The signed SYSFW image as well as the configuration artifacts will then all get
build into an ITB blob (FIT image) named **sysfw-{soc}-{configuration}.itb**
ready for consumption by U-Boot SPL.


Building SYSFW Image and Configuration Data
-------------------------------------------
First, ensure you have a current mkimage tool and ARMv7 cross toolchain
installed. The SYSFW configuration generator was developed and tested using...

    $ mkimage -V
    mkimage version 2013.10

    $ arm-linux-gnueabihf-gcc --version
    arm-linux-gnueabihf-gcc (Linaro GCC 7.2-2017.11) 7.2.1 20171011
    Copyright (C) 2017 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Also make sure to have a proper unsigned SYSFW image populated at the root of
this project, otherwise a version specified in the Makefile via Git commit hash
will be downloaded from the TI SYSFW release URL (see download location below).

The default SYSFW image consumed by the build process is called
**ti-sci-firmware-{soc}-gp.bin** however this may be overwritten and customized
using the **SYSFW_PATH** make variable. The build process will fail if the
image can't be downloaded to {srcroot} or no such file has gotten populated into
that folder by other means.

Further note by default the SYSFW image for use with general purpose (GP) devices
(as opposed to high security devices) is signed with the TI degenerate key to
optimize boot time (less processing time needed by ROM) but can also be signed
with a random cryptoraphic key or another user-provided key. This signing behavior
is controlled through the **KEY** make variable. Not explicitly setting **KEY**
will result in the use of the TI degenerate key. To use a custom key populate the
**KEY** variable to point to the key to get used. By clearing the default key
setting by passing in **KEY=""** a random key will get generated and used during
the build process.

In order to download the SYSFW release image (if needed) and build the final
**sysfw-{soc}-{configuration}.itb** for consumption by U-Boot SPL simply by
perform a make.

    $ make

Note that in case of filesystem-based boot such as booting from SD card
**sysfw-{soc}-{configuration}.itb** needs to be manually renamed to
**syswfw.itb** before populating it to the (SD card) boot media as this is the
file name U-Boot SPL will be trying to load early during the boot process. This
renaming step is not necessary for RAW boot modes such as eMMC (in RAW mode),
(x)SPI, and others.

    $ mv sysfw-{soc}-{configuration}.itb syswfw.itb

To extract and show the release version of the SYSFW image being used...

    $ make sysfw_version
    SYSFW Version: v2018.08a (Curious Crow)

To extract the 'creator' information from the final generated
**sysfw-{soc}-{configuration}.itb** image tree blob...

    $ fdtget sysfw-am65x-evm.itb / creator
    SIG am65x/evm-ti2019.01-14-g47b8d

The workspace can be cleaned up by doing...

    $ make clean

To also remove the SYSFW image do this...

    $ make mrproper

The following flags further modify the build steps:
* SOC - Choose one of the supported SoCs (see folder name under {srcroot}/soc).
  Defaults to am65x
* CONFIG - Choose of various configurations supported (see folder name under
  {srcroot}/soc/{soc}). Defaults to evm
* O - Choose where the intermediate build files need to be located
* BIN_DIR - Choose where the final output sysfw-{soc}-{configuration}.itb needs
  to be generated to.
* KEY - Choose key to use for the signing system firmware image
* ENABLE_TRACE=1 - Choose to enable sysfw traces while booting.


Building SYSFW Image for High-Security(HS) devices
--------------------------------------------------
The process for building an image suitable for use with HS devices is similar
to the above process with the following differences:

The make commands should be appended with `SOC_TYPE=<hs,hs-fs>`,

    $ make SOC_TYPE=hs

The environment variable **TI_SECURE_DEV_PKG** should be defined to point to
the TI Secure Development Tools package. This will be used for setting the
**KEY** and **SW_REV** values. These can also be set explicitly if other
values are needed,

    $ make SW_REV=2

There are two images downloaded and consumed by the build process.

    * ti-sci-firmware-{soc}-hs-enc.bin: Encrypted HS SYSFW image
    * ti-sci-firmware-{soc}-hs-cert.bin: Inner-certificate for HS SYSFW image

The inner-certificate is signed by the key provided by the **TI_SECURE_DEV_PKG**
path producing an outer-certificate. These images are then appended to produce
the final **sysfw-{soc}-{configuration}.bin** which is then bundled with the
configuration data exactly as in the non-HS version above.


Important Notes
---------------
* There is a strong dependency of the used System Firmware release version and
how the board configuration data needs to be structured and/or filled in. Using
config data that is not compatible with a given SYSFW release may lead to
failures during loading of the data by U-Boot SPL, or failures later downstream
in U-Boot or during Linux boot.

It is strongly recommended to review System Firmware release documentation in
great detail(!) to make sure suitable board configuration is provided. Common
pitfalls preventing proper system operation include but are not limited to using
an unsuitable or invalid resource management configuration.

* J784S4 uses split resource management configuration for TIFS (tifs-rm-cfg.c) and
DM (rm-cfg.c). tifs-rm-cfg.c is a stripped down version of rm-cfg.c containing
entries only for TIFS consumption.

References
----------
* [Latest SYSFW Release Documentation](http://software-dl.ti.com/tisci/esd/latest/)
* [Official SYSFW Release Download Location](https://git.ti.com/processor-firmware/ti-linux-firmware/trees/ti-linux-firmware/ti-sysfw)
* [TI Secure Development Tools package](https://git.ti.com/cgit/security-development-tools/core-secdev-k3/)
