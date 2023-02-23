/*
 * K3 System Firmware Board Configuration Data Structures
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 *	Andreas Dannenberg <dannenberg@ti.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef COMMON_H
#define COMMON_H

#include <sysfw_img_cfg.h>
#include <devices.h>
#include <hosts.h>
#include <resasg_types.h>

/**
 * Standard Linux Kernel integer types
 */
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

/**
 * Fault tolerant boolean type (specific to SYSFW)
 */
typedef u8 ftbool;

/**
 * Basic bit operations
 */
#define BIT(n)		(1UL << (n))

/**
 * Various definitions as expected by the 'struct' declarations below
 */
#define BOARDCFG_RM_HOST_CFG_MAGIC_NUM		0x4C41
#define BOARDCFG_RM_RESASG_MAGIC_NUM		0x7B25
#define BOARDCFG_CONTROL_MAGIC_NUM		0xC1D3
#define BOARDCFG_SECPROXY_MAGIC_NUM		0x1207
#define BOARDCFG_MSMC_MAGIC_NUM			0xA5C3
#define BOARDCFG_PROC_ACL_MAGIC_NUM		0xF1EA
#define BOARDCFG_HOST_HIERARCHY_MAGIC_NUM       0x8D27
#define BOARDCFG_RESASG_MAGIC_NUM		0x4C41
#define BOARDCFG_DBG_CFG_MAGIC_NUM		0x020C
#define BOARDCFG_PMIC_CFG_MAGIC_NUM		0x3172
#define BOARDCFG_OTP_CFG_MAGIC_NUM		0x4081
#define BOARDCFG_DKEK_CFG_MAGIC_NUM		0x5170
#define BOARDCFG_SA2UL_CFG_MAGIC_NUM_RSVD	0x23BE
#define BOARDCFG_SEC_DBG_CTRL_MAGIC_NUM		0x42AF
#define BOARDCFG_SEC_HANDOVER_CFG_MAGIC_NUM	0x608F

struct boardcfg_substructure_header {
	u16	magic;
	u16	size;
} __attribute__((__packed__));

struct boardcfg_abi_rev {
	u8	boardcfg_abi_maj;
	u8	boardcfg_abi_min;
} __attribute__((__packed__));

/**
 * Definitions, types, etc. as used for general board configuration
 */
struct boardcfg_control {
	struct boardcfg_substructure_header	subhdr;
	ftbool					main_isolation_enable;
	u16					main_isolation_hostid;
} __attribute__((__packed__));

struct boardcfg_secproxy {
	struct boardcfg_substructure_header	subhdr;
	u8					scaling_factor;
	u8					scaling_profile;
	u8					disable_main_nav_secure_proxy;
} __attribute__((__packed__));

struct boardcfg_msmc {
	struct boardcfg_substructure_header	subhdr;
	u8					msmc_cache_size;
} __attribute__((__packed__));


#define BOARDCFG_TRACE_DST_UART0                BIT(0)
#define BOARDCFG_TRACE_DST_ITM                  BIT(2)
#define BOARDCFG_TRACE_DST_MEM                  BIT(3)

#define BOARDCFG_TRACE_SRC_PM                   BIT(0)
#define BOARDCFG_TRACE_SRC_RM                   BIT(1)
#define BOARDCFG_TRACE_SRC_SEC                  BIT(2)
#define BOARDCFG_TRACE_SRC_BASE                 BIT(3)
#define BOARDCFG_TRACE_SRC_USER                 BIT(4)
#define BOARDCFG_TRACE_SRC_SUPR                 BIT(5)

struct boardcfg_dbg_cfg {
	struct boardcfg_substructure_header	subhdr;
	u16					trace_dst_enables;
	u16					trace_src_enables;
} __attribute__((__packed__));

struct boardcfg {
	struct boardcfg_abi_rev			rev;
	struct boardcfg_control			control;
	struct boardcfg_secproxy		secproxy;
	struct boardcfg_msmc			msmc;
	struct boardcfg_dbg_cfg			debug_cfg;
} __attribute__((__packed__));

struct boardcfg_rm_host_cfg_entry {
	u8	host_id;
	u8	allowed_atype;
	u16	allowed_qos;
	u32	allowed_orderid;
	u16	allowed_priority;
	u8	allowed_sched_priority;
} __attribute__((__packed__));

#define BOARDCFG_RM_HOST_CFG_ENTRIES (32U)

struct boardcfg_rm_host_cfg {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_rm_host_cfg_entry
				 host_cfg_entries[BOARDCFG_RM_HOST_CFG_ENTRIES];
};

struct boardcfg_rm_resasg_entry {
	u16					start_resource;
	u16					num_resource;
	u16					type;
	u8					host_id;
	u8					reserved;
};

struct boardcfg_rm_resasg {
	struct boardcfg_substructure_header	subhdr;
	u16					resasg_entries_size;
	u16					reserved;
	struct boardcfg_rm_resasg_entry		resasg_entries[];
} __attribute__((__packed__));

struct boardcfg_rm {
	struct boardcfg_abi_rev			rev;
	struct boardcfg_rm_host_cfg		host_cfg;
	struct boardcfg_rm_resasg		resasg;
} __attribute__((__packed__));

/*
 * This is essentially 'struct boardcfg_rm', but modified to pull
 * .resasg_entries which is a member of 'struct boardcfg_rm_resasg' into
 * the outer structure for easier explicit initialization.
 */
struct boardcfg_rm_local {
	struct boardcfg_rm			rm_boardcfg;
	struct boardcfg_rm_resasg_entry
				resasg_entries[BOARDCFG_RM_RESASG_ENTRIES];
} __attribute__((__packed__));

#ifndef BOARDCFG_TIFS_RM_RESASG_ENTRIES
#define BOARDCFG_TIFS_RM_RESASG_ENTRIES		BOARDCFG_RM_RESASG_ENTRIES
#endif

struct boardcfg_tifs_rm_local {
	struct boardcfg_rm			rm_boardcfg;
	struct boardcfg_rm_resasg_entry
				resasg_entries[BOARDCFG_TIFS_RM_RESASG_ENTRIES];
} __attribute__((__packed__));
/**
 * Definitions, types, etc. as used for the security configuration
 */
#define PROCESSOR_ACL_SECONDARY_MASTERS_MAX	3

struct boardcfg_proc_acl_entry {
	u8					processor_id;
	u8					proc_access_master;
	u8	     proc_access_secondary[PROCESSOR_ACL_SECONDARY_MASTERS_MAX];
} __attribute__((__packed__));

#define PROCESSOR_ACL_ENTRIES			32

struct boardcfg_proc_acl {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_proc_acl_entry  proc_acl_entries[PROCESSOR_ACL_ENTRIES];
} __attribute__((__packed__));

struct boardcfg_host_hierarchy_entry {
	u8					host_id;
	u8					supervisor_host_id;
} __attribute__((__packed__));

#define HOST_HIERARCHY_ENTRIES			32

struct boardcfg_host_hierarchy {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_host_hierarchy_entry
				 host_hierarchy_entries[HOST_HIERARCHY_ENTRIES];
} __attribute__((__packed__));

struct boardcfg_extended_otp_entry {
	u8	host_id;
	u8	host_perms;
} __attribute__((__packed__));

#define MAX_NUM_EXT_OTP_MMRS			32

struct boardcfg_extended_otp {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_extended_otp_entry	otp_entry[MAX_NUM_EXT_OTP_MMRS];
	u8					write_host_id;
} __attribute__((__packed__));

#define MAX_NUM_DKEK_ALLOWED_HOSTS		4

struct boardcfg_dkek {
	struct boardcfg_substructure_header	subhdr;
	u8					allowed_hosts[MAX_NUM_DKEK_ALLOWED_HOSTS];
	u8					allow_dkek_export_tisci;
	u8					rsvd[3];
} __attribute__((__packed__));

struct boardcfg_sa2ul_cfg {
	struct boardcfg_substructure_header	subhdr;
	u8					auth_resource_owner;
	ftbool					enable_saul_psil_global_config_writes;
	u8					rsvd[2];
};

#define BOARDCFG_SEC_MAX_NUM_JTAG_UNLOCK_HOSTS	4

struct boardcfg_secure_debug_config {
	struct boardcfg_substructure_header	subhdr;
	u8					allow_jtag_unlock;
	u8					allow_wildcard_unlock;
	u8					allowed_debug_level_rsvd;
	u8					rsvd;
	u32					min_cert_rev;
	u8					jtag_unlock_hosts[BOARDCFG_SEC_MAX_NUM_JTAG_UNLOCK_HOSTS];
} __attribute__((__packed__));

struct boardcfg_sec_handover {
	struct boardcfg_substructure_header	subhdr;
	u8					handover_msg_sender;
	u8					handover_to_host_id;
	u8					rsvd[4];
};

struct boardcfg_security {
	struct boardcfg_abi_rev			rev;
	struct boardcfg_proc_acl		processor_acl_list;
	struct boardcfg_host_hierarchy		host_hierarchy;
	struct boardcfg_extended_otp		otp_config;
	struct boardcfg_dkek			dkek_config;
	struct boardcfg_sa2ul_cfg		sa2ul_cfg;
	struct boardcfg_secure_debug_config	sec_dbg_config;
	struct boardcfg_sec_handover		sec_handover_cfg;
} __attribute__((__packed__));

/**
 * Definitions, types, etc. as used for PM configuration
 */
struct boardcfg_pm {
	struct boardcfg_abi_rev			rev;
} __attribute__((__packed__));

#endif /* COMMON_H */
