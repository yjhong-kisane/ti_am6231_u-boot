/*
 * K3 System Firmware Board Configuration Data
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/
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

const struct boardcfg am64x_boardcfg_data = {
	/* boardcfg_abi_rev */
	.rev = {
		.boardcfg_abi_maj = 0x0,
		.boardcfg_abi_min = 0x1,
	},

	/* boardcfg_control */
	.control = {
		.subhdr = {
			.magic = BOARDCFG_CONTROL_MAGIC_NUM,
			.size = sizeof(struct boardcfg_control),
		},
		.main_isolation_enable = 0x5A,
		.main_isolation_hostid = 0x2,
	},

	/* boardcfg sec_proxy */
	.secproxy = {
		.subhdr = {
			.magic = BOARDCFG_SECPROXY_MAGIC_NUM,
			.size = sizeof(struct boardcfg_secproxy),
		},
		.scaling_factor = 0x1,
		.scaling_profile = 0x1,
		.disable_main_nav_secure_proxy = 0,
	},

	/* boardcfg_msmc */
	.msmc = {
		.subhdr = {
			.magic = BOARDCFG_MSMC_MAGIC_NUM,
			.size = sizeof(struct boardcfg_msmc),
		},
		.msmc_cache_size = 0x0,
	},

	/* boardcfg_dbg_cfg */
	.debug_cfg = {
		.subhdr = {
			.magic = BOARDCFG_DBG_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_dbg_cfg),
		},
#ifdef ENABLE_TRACE
		.trace_dst_enables = BOARDCFG_TRACE_DST_UART0 |
				     BOARDCFG_TRACE_DST_ITM |
				     BOARDCFG_TRACE_DST_MEM,
		.trace_src_enables = BOARDCFG_TRACE_SRC_PM |
				     BOARDCFG_TRACE_SRC_RM |
				     BOARDCFG_TRACE_SRC_SEC |
				     BOARDCFG_TRACE_SRC_BASE |
				     BOARDCFG_TRACE_SRC_USER |
				     BOARDCFG_TRACE_SRC_SUPR,
#endif
	},
};
