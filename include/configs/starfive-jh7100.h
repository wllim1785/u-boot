// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Shanghai StarFive Technology Co., Ltd.
 * Micheal Zhu <michael.zhu@starfivetech.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <version.h>
#include <linux/sizes.h>

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size */
#define CONFIG_SYS_BOOTM_LEN		(64 << 20) /* 64MB */

/*
 * Print Buffer Size
 */
#define CONFIG_SYS_PBSIZE	\
			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
/*
 * Boot Argument Buffer Size
 */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS		16

#define CONFIG_SYS_SDRAM_BASE		0x80000000
/* Init Stack Pointer */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_STANDALONE_LOAD_ADDR	(CONFIG_SYS_SDRAM_BASE + SZ_2M)

/*mac addr offset in otp*/
#define STARFIVE_OTP_MAC_OFFSET		0x28

/*
 * Ethernet
 */
#if CONFIG_IS_ENABLED(CMD_NET)
#define CONFIG_DW_ALTDESCRIPTOR
#define CONFIG_ARP_TIMEOUT		0x5000
#endif

/* HACK these should have '#if defined (stuff) around them like zynqp*/
#define BOOT_TARGET_DEVICES(func)	func(MMC, mmc, 0) \
					func(DHCP, dhcp, na)

#include <config_distro_bootcmd.h>

#include <environment/distro/sf.h>

#define STARLIGHT_FEDORA_BOOTENV \
	"bootdir=/boot\0" \
	"bootenv=uEnv.txt\0" \
	"mmcdev=0\0" \
	"mmcpart=3\0"

#define STARLIGHT_TEST_BOOTENV \
	"testpart=0:1\0" \
	"testenv=u74_uEnv.txt\0" \
	"mmcsetup=mmc part\0" \
	"fdtsetup=fdt addr ${fdtcontroladdr}\0" \
	"fatenv=fatload mmc ${testpart} ${loadaddr} ${testenv};" \
		"env import -t ${loadaddr} ${filesize}\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0xffffffffffffffff\0" \
	"initrd_high=0xffffffffffffffff\0" \
	"kernel_addr_r=0x84000000\0" \
	"kernel_comp_addr_r=0x90000000\0" \
	"kernel_comp_size=0x10000000\0" \
	"fdt_addr_r=0x88000000\0" \
	"scriptaddr=0x88100000\0" \
	"pxefile_addr_r=0x88200000\0" \
	"ramdisk_addr_r=0x88300000\0" \
	STARLIGHT_FEDORA_BOOTENV \
	"loadaddr=0xa0000000\0" \
	STARLIGHT_TEST_BOOTENV \
	"loadbootenv=fatload mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"ext4bootenv=ext4load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc${mmcdev} ...; " \
		"env import -t ${loadaddr} ${filesize}\0" \
	"mmcbootenv=setenv bootpart ${mmcdev}:${mmcpart}; " \
		"mmc dev ${mmcdev}; " \
		"if mmc rescan; then " \
			"run loadbootenv && run importbootenv; " \
			"run ext4bootenv && run importbootenv; " \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...; " \
				"run uenvcmd; " \
			"fi; " \
		"fi\0" \
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
  "nand_initialize=sspi 0:0.3 8 ff; sspi 0:0.3 24 1fa000; sspi 0:0.3 24 1fb000; sspi 0:0.3 24 1fc000\0" \
  "nand_init=for c in 1 2; do run nand_initialize; done\0" \
  "nand_status=sspi 0:0.3 24 0fa0; sspi 0:0.3 24 0fb0; sspi 0:0.3 24 0fc0\0" \
  "nand_erase=sspi 0:0.3 8 06; sspi 0:0.3 32 D8000000\0" \
  "nand_pp=sspi 0:0.3 8 06; sspi 0:0.3 2176 84000000000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff00000000ffffffff; sspi 0:0.3 32 10000000\0" \
  "nand_read=sspi 0:0.3 32 13000000; sspi 0:0.3 2176 03000000 1 1 1\0" \
  "nand_read_cycle=for c in 1 2 3 4 5 6 7 8 9 10; do run nand_read; done\0" \
  "nand_read_stress=for c in 1 2 3 4; do run nand_read_cycle; done\0" \
  "nand_pp_cycle=for c in 1 2 3 4 5 6 7 8 9 10; do run nand_pp; done\0" \
  "nand_pp_hundreds=for c in 1 2 3 4 5 6 7 8 9 10; do run nand_pp_cycle; done\0" \
  "nand_pp_thousands=for c in 1 2 3 4 5 6 7 8 9 10; do run nand_pp_hundreds; done\0" \
  "nand_pp_stress_8k=for c in 1 2 3 4 5 6 7 8; do run nand_pp_thousands; done\0" \
  "nand_pp_stress_5k=for c in 1 2 3 4 5; do run nand_pp_thousands; done\0" \
  "nand_pp_stress_2k=for c in 1 2; do run nand_pp_thousands; done\0" \
	BOOTENV \
	BOOTENV_SF

#define CONFIG_SYS_MAX_FLASH_SECT	0
#define CONFIG_SYS_MAX_FLASH_BANKS	0
#define __io

/*
 * QSPI support
 */
#ifdef CONFIG_OF_CONTROL		/* QSPI is controlled via DT */
#define CONFIG_CQSPI_REF_CLK		(250000000)
#endif

#ifdef CONFIG_ID_EEPROM		/* EEPROM for SN and MAC */
#define CONFIG_SYS_EEPROM_BUS_NUM		0

#define FORMAT_VERSION				0x1
#define PCB_VERSION				0x1
#define BOM_VERSION				'A'
/*
 * BYTES_PER_EEPROM_PAGE: the 24FC04H datasheet says that data can
 * only be written in page mode, which means 16 bytes at a time:
 * 16-Byte Page Write Buffer
 */
#define BYTES_PER_EEPROM_PAGE			16

/*
 * EEPROM_WRITE_DELAY_MS: the 24FC04H datasheet says it takes up to
 * 5ms to complete a given write:
 * Write Cycle Time (byte or page) ro Page Write Time 5 ms, Maximum
 */
#define EEPROM_WRITE_DELAY_MS			5000
/*
 * StarFive OUI. Registration Date is 20xx-xx-xx
 */
#define STARFIVE_OUI_PREFIX			"6C:CF:39:"
#define STARFIVE_DEFAULT_MAC			{0x6C, 0xCF, 0x39, 0x08, 0x08, 0x08}

/* Magic number at the first four bytes of EEPROM HATs */
#define STARFIVE_EEPROM_HATS_SIG	"SFVF" /* StarFive VisionFive */

#define STARFIVE_EEPROM_HATS_SIZE_MAX	128 /* Header + Atom1&4(v1) */
#define STARFIVE_EEPROM_WP_OFFSET	256 /* Read only field */
#define STARFIVE_EEPROM_ATOM1_PSTR	"VF7100A1-2201-D008E000-00000001\0"
#define STARFIVE_EEPROM_ATOM1_PSTR_SIZE	32
#define STARFIVE_EEPROM_ATOM1_SN_OFFSET	23
#define STARFIVE_EEPROM_ATOM1_VSTR	"StarFive Technology Co., Ltd.\0\0\0"
#define STARFIVE_EEPROM_ATOM1_VSTR_SIZE	32
#endif

#endif /* __CONFIG_H */
