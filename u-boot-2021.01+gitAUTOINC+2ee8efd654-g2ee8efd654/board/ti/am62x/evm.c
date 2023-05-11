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
#include <env.h>
#include <net.h>
#include <spl.h>
#include <dm/uclass.h>
#include <k3-ddrss.h>
#include <fdt_support.h>
#include <asm/arch/hardware.h>
#include <asm/arch/sys_proto.h>

#include <asm/gpio.h>		// gpio_request
#include <linux/delay.h>	// udelay

#include "../common/board_detect.h"

#define board_is_am62x_skevm()		board_ti_k3_is("AM62-SKEVM")
#define board_is_am62x_lp_skevm()	board_ti_k3_is("AM62-LP-SKEVM")

#define AM62X_MAX_DAUGHTER_CARDS	8

/* Daughter card presence detection signals */
enum {
	AM62X_LPSK_HSE_BRD_DET,
	AM62X_LPSK_BRD_DET_COUNT,
};

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_ARM64)
static struct gpio_desc board_det_gpios[AM62X_LPSK_BRD_DET_COUNT];
#endif

/* Max number of MAC addresses that are parsed/processed per daughter card */
#define DAUGHTER_CARD_NO_OF_MAC_ADDR	8

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
    // 잘못된 입력
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // 숫자의 절대값을 고려
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
 
    // 숫자가 0인 경우
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // 밑이 10이고 값이 음수이면 결과 문자열
    // 마이너스 기호(-)가 앞에 옵니다.
    // 다른 기준을 사용하면 값은 항상 부호 없는 것으로 간주됩니다.
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null 종료 문자열
 
    // 문자열을 반대로 하여 반환
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

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_ARM64)
static const char *k3_dtbo_list[AM62X_MAX_DAUGHTER_CARDS] = {NULL};

static int init_daughtercard_det_gpio(char *gpio_name, struct gpio_desc *desc)
{
	int ret;

	memset(desc, 0, sizeof(*desc));
	ret = dm_gpio_lookup_name(gpio_name, desc);
	if (ret < 0) {
		pr_err("Failed to lookup gpio %s: %d\n", gpio_name, ret);
		return ret;
	}

	/* Request GPIO, simply re-using the name as label */
	ret = dm_gpio_request(desc, gpio_name);
	if (ret < 0) {
		pr_err("Failed to request gpio %s: %d\n", gpio_name, ret);
		return ret;
	}

	return dm_gpio_set_dir_flags(desc, GPIOD_IS_IN);
}

static int probe_daughtercards(void)
{
	struct ti_am6_eeprom ep;
	char mac_addr[DAUGHTER_CARD_NO_OF_MAC_ADDR][TI_EEPROM_HDR_ETH_ALEN];
	u8 mac_addr_cnt;
	char name_overlays[1024] = { 0 };
	int i, nb_dtbos = 0;
	int ret;

	/*
	 * Daughter card presence detection signal name to GPIO (via I2C I/O
	 * expander @ address 0x53) name and EEPROM I2C address mapping.
	 */
	const struct {
		char *gpio_name;
		u8 i2c_addr;
	} slot_map[AM62X_LPSK_BRD_DET_COUNT] = {
		{ "gpio@22_2", 0x53, },	/* AM62X_LPSK_HSE_BRD_DET */
	};

	/* Declaration of daughtercards to probe */
	const struct {
		u8 slot_index;		/* Slot the card is installed */
		char *card_name;	/* EEPROM-programmed card name */
		char *dtbo_name;	/* Device tree overlay to apply */
		u8 eth_offset;		/* ethXaddr MAC address index offset */
	} cards[] = {
		{
			AM62X_LPSK_HSE_BRD_DET,
			"SK-NAND-DC01",
			"k3-am62x-lp-sk-nand.dtbo",
			0,
		},
	};

	/*
	 * Initialize GPIO used for daughtercard slot presence detection and
	 * keep the resulting handles in local array for easier access.
	 */
	for (i = 0; i < AM62X_LPSK_BRD_DET_COUNT; i++) {
		ret = init_daughtercard_det_gpio(slot_map[i].gpio_name,
						 &board_det_gpios[i]);
		if (ret < 0)
			return ret;
	}

	memset(k3_dtbo_list, 0, sizeof(k3_dtbo_list));
	for (i = 0; i < ARRAY_SIZE(cards); i++) {
		/* Obtain card-specific slot index and associated I2C address */
		u8 slot_index = cards[i].slot_index;
		u8 i2c_addr = slot_map[slot_index].i2c_addr;
		const char *dtboname;

		/*
		 * The presence detection signal is active-low, hence skip
		 * over this card slot if anything other than 0 is returned.
		 */
		ret = dm_gpio_get_value(&board_det_gpios[slot_index]);
		if (ret < 0)
			return ret;
		else if (ret)
			continue;

		/* Get and parse the daughter card EEPROM record */
		ret = ti_i2c_eeprom_am6_get(CONFIG_EEPROM_BUS_ADDRESS, i2c_addr,
					    &ep,
					    (char **)mac_addr,
					    DAUGHTER_CARD_NO_OF_MAC_ADDR,
					    &mac_addr_cnt);

		if (ret) {
			pr_err("Reading daughtercard EEPROM at 0x%02x failed %d\n",
			       i2c_addr, ret);
			/*
			 * Even this is pretty serious let's just skip over
			 * this particular daughtercard, rather than ending
			 * the probing process altogether.
			 */
			continue;
		}

		/* Only process the parsed data if we found a match */
		if (strncmp(ep.name, cards[i].card_name, sizeof(ep.name)))
			continue;
		printf("Detected: %s rev %s\n", ep.name, ep.version);

		int j;

		for (j = 0; j < mac_addr_cnt; j++) {
			if (!is_valid_ethaddr((u8 *)mac_addr[j]))
				continue;

			eth_env_set_enetaddr_by_index("eth",
						      cards[i].eth_offset + j,
						      (uchar *)mac_addr[j]);
		}
		/* Skip if no overlays are to be added */
		if (!strlen(cards[i].dtbo_name))
			continue;

		dtboname = cards[i].dtbo_name;
		k3_dtbo_list[nb_dtbos++] = dtboname;

		/*
		 * Make sure we are not running out of buffer space by checking
		 * if we can fit the new overlay, a trailing space to be used
		 * as a separator, plus the terminating zero.
		 */
		if (strlen(name_overlays) + strlen(dtboname) + 2 >
		    sizeof(name_overlays))
			return -ENOMEM;

		/* Append to our list of overlays */
		strcat(name_overlays, dtboname);
		strcat(name_overlays, " ");
	}
	/* Apply device tree overlay(s) to the U-Boot environment, if any */
	if (strlen(name_overlays))
		return env_set("name_overlays", name_overlays);
	return 0;
}
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

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_ARM64)
		/* Check for and probe any plugged-in daughtercards */
		if (board_is_am62x_lp_skevm())
			probe_daughtercards();
#endif
	}

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

//===============================================================================================================
	// NOTE::2023-05-11
	// LCD Display Always On
	// TRM.3648 (PADCFG_CRTL0_CFG0_PADCONFIG122)
	val = readl(0x000F41E8);
	printf("[%s:%s:%d] PADCFG_CRTL0_CFG0_PADCONFIG122: 0x%x", __FILE__, __FUNCTION__, __LINE__, val);
	if(val != 0x7) {
		writel(0x07, 0x000F41E8);
		printf(" -> 0x%x\n", readl(0x000F41E8));
	}
	else {
		printf("\n");
	}
//===============================================================================================================

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
