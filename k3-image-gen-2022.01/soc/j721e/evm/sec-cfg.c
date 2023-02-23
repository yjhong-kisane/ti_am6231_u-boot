/*
 * K3 System Firmware Security Configuration Data
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
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

#include "common.h"

const struct boardcfg_security j721e_boardcfg_security_data = {
	/* boardcfg_abi_rev */
	.rev = {
		.boardcfg_abi_maj = 0x0,
		.boardcfg_abi_min = 0x1,
	},

	/* boardcfg_proc_acl */
	.processor_acl_list = {
		.subhdr = {
			.magic = BOARDCFG_PROC_ACL_MAGIC_NUM,
			.size = sizeof(struct boardcfg_proc_acl),
		},
		.proc_acl_entries = {{ 0 } },
	},

	/* boardcfg_host_hierarchy */
	.host_hierarchy = {
			.subhdr = {
				.magic = BOARDCFG_HOST_HIERARCHY_MAGIC_NUM,
				.size = sizeof(struct boardcfg_host_hierarchy),
			},
			.host_hierarchy_entries = {{ 0 } },
	},

	/* OTP access configuration */
	.otp_config = {
		.subhdr = {
			.magic = BOARDCFG_OTP_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_extended_otp),
		},
		/* Host ID 0 is DMSC. This means no host has write access to OTP array */
		.write_host_id = 0,
		/* This is an array with 32 entries */
		.otp_entry = {{ 0 } },
	},

	/* DKEK configuration */
	.dkek_config = {
		.subhdr = {
			.magic = BOARDCFG_DKEK_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_dkek),
		},
		.allowed_hosts = { HOST_ID_ALL, 0, 0, 0 },
		.allow_dkek_export_tisci = 0x5A,
		.rsvd = {0, 0, 0},
	},

	/* SA2UL configuration */
	.sa2ul_cfg = {
		.subhdr = {
			.magic = BOARDCFG_SA2UL_CFG_MAGIC_NUM_RSVD,
			.size = 0,
		},
		.auth_resource_owner = 0,
		.enable_saul_psil_global_config_writes = 0,
		.rsvd = {0, 0},
	},

	/* Secure JTAG Unlock Configuration */
	.sec_dbg_config = {
		.subhdr = {
			.magic = BOARDCFG_SEC_DBG_CTRL_MAGIC_NUM,
			.size = sizeof(struct boardcfg_secure_debug_config),
		},
		.allow_jtag_unlock = 0x5A,
		.allow_wildcard_unlock = 0x5A,
		.min_cert_rev = 0x0,
		.jtag_unlock_hosts = {0, 0, 0, 0},
	},

	/* Secure Handover Configuration */
	.sec_handover_cfg = {
		.subhdr = {
			.magic = BOARDCFG_SEC_HANDOVER_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_sec_handover),
		},
		.handover_msg_sender = 0,
		.handover_to_host_id = 0,
		.rsvd = {0,0,0,0},
	},
};
