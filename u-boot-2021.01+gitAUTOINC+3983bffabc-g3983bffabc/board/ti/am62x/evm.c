// SPDX-License-Identifier: GPL-2.0+
/*
 * Board specific initialization for AM62x platforms
 *
 * Copyright (C) 2020-2022 Texas Instruments Incorporated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 *
 */

#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <dm/uclass.h>
#include <k3-ddrss.h>
#include <fdt_support.h>
#include <asm/arch/hardware.h>
#include <asm/arch/sys_proto.h>
#include <env.h>

#include <asm/gpio.h>		// gpio_request
#include <linux/delay.h>	// udelay

#include "../common/board_detect.h"

#define board_is_am62x_skevm()		board_ti_k3_is("AM62-SKEVM")
#define board_is_am62x_lp_skevm()	board_ti_k3_is("AM62-LP-SKEVM")

DECLARE_GLOBAL_DATA_PTR;


void swap1(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap1(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}

char* itoa(int value, char* buffer, int base)
{
    // �߸��� �Է�
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // ������ ���밪�� ���
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // ���ڰ� 0�� ���
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // ���� 10�̰� ���� �����̸� ��� ���ڿ�
    // ���̳ʽ� ��ȣ(-)�� �տ� �ɴϴ�.
    // �ٸ� ������ ����ϸ� ���� �׻� ��ȣ ���� ������ ���ֵ˴ϴ�.
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null ���� ���ڿ�
 
    // ���ڿ��� �ݴ�� �Ͽ� ��ȯ
    return reverse(buffer, 0, i - 1);
}

static void gpio_test(void)
{
	char TmpBuf[33] = {0, };
	char StrBuf[128] = {0, };

	int nCnt = 0;
	int nErr = 0;
    int nPinNum = 0;
    for (nPinNum = 0 ; nPinNum < 512 ; nPinNum++)
    {
		if(nCnt > 2) {
			break;
		}

		memset(TmpBuf, 0, 33);
		itoa(nPinNum, TmpBuf, 10);

		memset(StrBuf, 0, 128);
		snprintf(StrBuf, 5 + strlen(TmpBuf) + 1, "gpio_%s\n", TmpBuf);

        nErr = gpio_request(nPinNum, StrBuf);
        if (nErr) {
            printf("[%s:%4d:%s] Failed to request gpio#%d\n", 
                __FILE__, __LINE__, __FUNCTION__, nPinNum);
			nCnt++;
            continue;
        }
        else
        {
			gpio_direction_output(nPinNum, 0);
			mdelay(10);
            printf("[%s:%4d:%s] GPIO-%d (%s) Value: %d \n", 
                    __FILE__, __LINE__, __FUNCTION__, nPinNum, StrBuf, gpio_get_value(nPinNum));

            gpio_set_value(nPinNum, 1);
            mdelay(10);
            printf("[%s:%4d:%s] GPIO-%d (%s) Value: %d \n", 
                    __FILE__, __LINE__, __FUNCTION__, nPinNum, StrBuf, gpio_get_value(nPinNum));
        }
    }
}

static void gpio_set_out_hi(int nGpioNum)
{
	// GPIO # as output
	u32 ret = gpio_request(nGpioNum, "");
	if (ret < 0) {
		printf("Unable to request GPIO %d\n", nGpioNum);
	}
	ret = gpio_direction_output(nGpioNum, 0);
	if (ret < 0) {
		printf("Unable to config GPIO %d\n", nGpioNum);
	}

	// Set 1 to output
	printf("Setting GPIO %d to 1\n", nGpioNum);
	ret = gpio_set_value(nGpioNum, 1);
	if (ret < 0) {
		printf("Unable to set GPIO %d\n", nGpioNum);
	}
	else
	{
		udelay(10000);
		printf("Getting GPIO %d => %d\n", nGpioNum, gpio_get_value(nGpioNum));
	}

	// Set 0 to output
	printf("Setting GPIO %d to 0\n", nGpioNum);
	ret = gpio_set_value(nGpioNum, 0);
	if (ret < 0) {
		printf("Unable to clear GPIO %d\n", nGpioNum);
	}
	else
	{
		udelay(10000);
		printf("Getting GPIO %d => %d\n", nGpioNum, gpio_get_value(nGpioNum));
	}
}


static void reset_phy_lan8710(int nGpioNum)
{
	u32 ret = gpio_request(nGpioNum, "Reset_LAN8710");
	if (ret < 0) {
		printf("Unable to request GPIO %d for LAN8710\n", nGpioNum);
	}
	ret = gpio_direction_output(nGpioNum, 1);	// Output, HI
	if (ret < 0) {
		printf("Unable to config GPIO %d for LAN8710\n", nGpioNum);
	}
	
	// Set 0 to output
	printf("Setting GPIO %d to 0 for LAN8710\n", nGpioNum);
	ret = gpio_set_value(nGpioNum, 0);
	if (ret < 0) {
		printf("Unable to clear GPIO %d for LAN8710\n", nGpioNum);
	}
	else
	{
		mdelay(10);
		printf("Getting GPIO %d => %d\n", nGpioNum, gpio_get_value(nGpioNum));
	}

	// Set 1 to output
	printf("Setting GPIO %d to 1 for LAN8710\n", nGpioNum);
	ret = gpio_set_value(nGpioNum, 1);
	if (ret < 0) {
		printf("Unable to set GPIO %d for LAN8710\n", nGpioNum);
	}
	else
	{
		mdelay(10);
		printf("Getting GPIO %d => %d\n", nGpioNum, gpio_get_value(nGpioNum));
	}
}


int board_init(void)
{
	return 0;
}

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

#if defined(CONFIG_SPL_LOAD_FIT)
int board_fit_config_name_match(const char *name)
{
	bool eeprom_read = board_ti_was_eeprom_read();

	if (!eeprom_read)
		return -1;

	if (board_is_am62x_lp_skevm()) {
		if (!strcmp(name, "k3-am62x-r5-lp-sk") || !strcmp(name, "k3-am62x-lp-sk"))
			return 0;
	} else if (board_is_am62x_skevm()) {
		if (!strcmp(name, "k3-am625-r5-sk") || !strcmp(name, "k3-am625-sk"))
			return 0;
	}

	return -1;
}
#endif

#if defined(CONFIG_SPL_BUILD)
#if defined(CONFIG_K3_AM64_DDRSS)
static void fixup_ddr_driver_for_ecc(struct spl_image_info *spl_image)
{
	struct udevice *dev;
	int ret;

	dram_init_banksize();

	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret)
		panic("Cannot get RAM device for ddr size fixup: %d\n", ret);

	ret = k3_ddrss_ddr_fdt_fixup(dev, spl_image->fdt_addr, gd->bd);
	if (ret)
		printf("Error fixing up ddr node for ECC use! %d\n", ret);
}
#else
static void fixup_memory_node(struct spl_image_info *spl_image)
{
	u64 start[CONFIG_NR_DRAM_BANKS];
	u64 size[CONFIG_NR_DRAM_BANKS];
	int bank;
	int ret;

	dram_init();
	dram_init_banksize();

	for (bank = 0; bank < CONFIG_NR_DRAM_BANKS; bank++) {
		start[bank] =  gd->bd->bi_dram[bank].start;
		size[bank] = gd->bd->bi_dram[bank].size;
	}

	/* dram_init functions use SPL fdt, and we must fixup u-boot fdt */
	ret = fdt_fixup_memory_banks(spl_image->fdt_addr,
				     start, size, CONFIG_NR_DRAM_BANKS);
	if (ret)
		printf("Error fixing up memory node! %d\n", ret);
}
#endif

void spl_perform_fixups(struct spl_image_info *spl_image)
{
#if defined(CONFIG_K3_AM64_DDRSS)
	fixup_ddr_driver_for_ecc(spl_image);
#else
	fixup_memory_node(spl_image);
#endif
}
#endif

#ifdef CONFIG_TI_I2C_BOARD_DETECT
int do_board_detect(void)
{
	int ret;

	ret = ti_i2c_eeprom_am6_get_base(CONFIG_EEPROM_BUS_ADDRESS,
					 CONFIG_EEPROM_CHIP_ADDRESS);
	if (ret) {
		printf("EEPROM not available at 0x%02x, trying to read at 0x%02x\n",
		       CONFIG_EEPROM_CHIP_ADDRESS, CONFIG_EEPROM_CHIP_ADDRESS + 1);
		ret = ti_i2c_eeprom_am6_get_base(CONFIG_EEPROM_BUS_ADDRESS,
						 CONFIG_EEPROM_CHIP_ADDRESS + 1);
		if (ret)
			pr_err("Reading on-board EEPROM at 0x%02x failed %d\n",
			       CONFIG_EEPROM_CHIP_ADDRESS + 1, ret);
	}

	return ret;
}

int checkboard(void)
{
	struct ti_am6_eeprom *ep = TI_AM6_EEPROM_DATA;

	if (!do_board_detect())
		printf("Board: %s rev %s\n", ep->name, ep->version);

	return 0;
}

#ifdef CONFIG_BOARD_LATE_INIT
static void setup_board_eeprom_env(void)
{
	char *name = "am62x_skevm";

	if (do_board_detect())
		goto invalid_eeprom;

	if (board_is_am62x_skevm())
		name = "am62x_skevm";
	else if (board_is_am62x_lp_skevm())
		name = "am62x_lp_skevm";
	else
		printf("Unidentified board claims %s in eeprom header\n",
		       board_ti_get_name());

invalid_eeprom:
	set_board_info_env_am6(name);
}

static void setup_serial(void)
{
	struct ti_am6_eeprom *ep = TI_AM6_EEPROM_DATA;
	unsigned long board_serial;
	char *endp;
	char serial_string[17] = { 0 };

	if (env_get("serial#"))
		return;

	board_serial = simple_strtoul(ep->serial, &endp, 16);
	if (*endp != '\0') {
		pr_err("Error: Can't set serial# to %s\n", ep->serial);
		return;
	}

	snprintf(serial_string, sizeof(serial_string), "%016lx", board_serial);
	env_set("serial#", serial_string);
}
#endif
#endif

#ifdef CONFIG_BOARD_LATE_INIT
int board_late_init(void)
{
	printf("[%s:%s:%d] TRACE:********************\n", __FILE__, __FUNCTION__, __LINE__);
	//gpio_test();

	if (IS_ENABLED(CONFIG_TI_I2C_BOARD_DETECT)) {
		struct ti_am6_eeprom *ep = TI_AM6_EEPROM_DATA;

		setup_board_eeprom_env();
		setup_serial();
		/*
		 * The first MAC address for ethernet a.k.a. ethernet0 comes from
		 * efuse populated via the am654 gigabit eth switch subsystem driver.
		 * All the other ones are populated via EEPROM, hence continue with
		 * an index of 1.
		 */
		board_ti_am6_set_ethaddr(1, ep->mac_addr_cnt);
	}

	/* Default FIT boot on non-GP devices */
	if (get_device_type() != K3_DEVICE_TYPE_GP)
		env_set("boot_fit", "1");


	printf("[%s:%s:%d] TRACE:********************\n", __FILE__, __FUNCTION__, __LINE__);
	//gpio_set_out_hi(11);	// (F23) GPIO0_11 (AM6232_STATUS_LED1)
	//reset_phy_lan8710(91);	// (B24) GPIO0_68 (AM6232_PRU_STATUS -> LAN8710_RESET)

	return 0;
}
#endif

#define CTRLMMR_USB0_PHY_CTRL	0x43004008
#define CTRLMMR_USB1_PHY_CTRL	0x43004018
#define CORE_VOLTAGE		0x80000000

#ifdef CONFIG_SPL_BOARD_INIT
void spl_board_init(void)
{
	u32 val;

	printf("TI SDK Ver: %s\n", TI_SDK_VER);

	//gpio_test();
	//gpio_set_out_hi(11);	// (F23) GPIO0_11 (AM6232_STATUS_LED1)

#if 0
	/* Set USB0 PHY core voltage to 0.85V */
	val = readl(CTRLMMR_USB0_PHY_CTRL);
	val &= ~(CORE_VOLTAGE);
	writel(val, CTRLMMR_USB0_PHY_CTRL);

	/* Set USB1 PHY core voltage to 0.85V */
	val = readl(CTRLMMR_USB1_PHY_CTRL);
	val &= ~(CORE_VOLTAGE);
	writel(val, CTRLMMR_USB1_PHY_CTRL);

	/* We have 32k crystal, so lets enable it */
	val = readl(MCU_CTRL_LFXOSC_CTRL);
	val &= ~(MCU_CTRL_LFXOSC_32K_DISABLE_VAL);
	writel(val, MCU_CTRL_LFXOSC_CTRL);
	/* Add any TRIM needed for the crystal here.. */
	/* Make sure to mux up to take the SoC 32k from the crystal */
	writel(MCU_CTRL_DEVICE_CLKOUT_LFOSC_SELECT_VAL,
	       MCU_CTRL_DEVICE_CLKOUT_32K_CTRL);
#endif

	/* Init DRAM size for R5/A53 SPL */
	dram_init_banksize();
}
#endif
