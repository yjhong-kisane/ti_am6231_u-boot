/*
 * K3 System Firmware Resource Management Configuration Data
 * Auto generated from K3 Resource Partitioning tool
 *
 * Copyright (C) 2022 Texas Instruments Incorporated - https://www.ti.com/
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
#include <hosts.h>
#include <devices.h>
#include <resasg_types.h>

const struct boardcfg_rm_local am62a_boardcfg_rm_data = {
	.rm_boardcfg = {
		/* boardcfg_abi_rev */
		.rev = {
			.boardcfg_abi_maj = 0x0,
			.boardcfg_abi_min = 0x1,
		},

		/* boardcfg_rm_host_cfg */
		.host_cfg = {
			.subhdr = {
				.magic = BOARDCFG_RM_HOST_CFG_MAGIC_NUM,
				.size = sizeof (struct boardcfg_rm_host_cfg),
			},
			.host_cfg_entries = {
				{
					.host_id = HOST_ID_A53_2,
					.allowed_atype = 0b101010,
					.allowed_qos = 0xAAAA,
					.allowed_orderid = 0xAAAAAAAA,
					.allowed_priority = 0xAAAA,
					.allowed_sched_priority = 0xAA,
				},
				{
					.host_id = HOST_ID_MCU_0_R5_0,
					.allowed_atype = 0b101010,
					.allowed_qos = 0xAAAA,
					.allowed_orderid = 0xAAAAAAAA,
					.allowed_priority = 0xAAAA,
					.allowed_sched_priority = 0xAA,
				},
				{
					.host_id = HOST_ID_MAIN_0_R5_1,
					.allowed_atype = 0b101010,
					.allowed_qos = 0xAAAA,
					.allowed_orderid = 0xAAAAAAAA,
					.allowed_priority = 0xAAAA,
					.allowed_sched_priority = 0xAA,
				},
			}
		},

		/* boardcfg_rm_resasg */
		.resasg = {
			.subhdr = {
				.magic = BOARDCFG_RM_RESASG_MAGIC_NUM,
				.size = sizeof (struct boardcfg_rm_resasg),
			},
			.resasg_entries_size =
				BOARDCFG_RM_RESASG_ENTRIES *
				sizeof (struct boardcfg_rm_resasg_entry),
			.reserved = 0,
			/* .resasg_entries is set via boardcfg_rm_local */
		},
	},

	/* This is actually part of .resasg */
	.resasg_entries = {
		/* Compare event Interrupt Router */
		{
			.start_resource = 0,
			.num_resource = 16,
			.type = RESASG_UTYPE (AM62A_DEV_CMP_EVENT_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 16,
			.num_resource = 4,
			.type = RESASG_UTYPE (AM62A_DEV_CMP_EVENT_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 16,
			.num_resource = 4,
			.type = RESASG_UTYPE (AM62A_DEV_CMP_EVENT_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 20,
			.num_resource = 22,
			.type = RESASG_UTYPE (AM62A_DEV_CMP_EVENT_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* MAIN GPIO Interrupt Router */
		{
			.start_resource = 0,
			.num_resource = 16,
			.type = RESASG_UTYPE (AM62A_DEV_MAIN_GPIOMUX_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 34,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_MAIN_GPIOMUX_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* WKUP MCU GPIO Interrupt Router */
		{
			.start_resource = 0,
			.num_resource = 4,
			.type = RESASG_UTYPE (AM62A_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 4,
			.num_resource = 4,
			.type = RESASG_UTYPE (AM62A_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* Timesync Interrupt Router */
		{
			.start_resource = 0,
			.num_resource = 26,
			.type = RESASG_UTYPE (AM62A_DEV_TIMESYNC_EVENT_ROUTER0,
					RESASG_SUBTYPE_IR_OUTPUT),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Global event trigger */
		{
			.start_resource = 50176,
			.num_resource = 164,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_TRIGGER),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Global config */
		{
			.start_resource = 0,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_UDMAP_GLOBAL_CONFIG),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Rings for Block copy channel */
		{
			.start_resource = 0,
			.num_resource = 18,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 18,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 18,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 24,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 26,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Rings for Split TR Rx channel */
		{
			.start_resource = 54,
			.num_resource = 18,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 72,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 72,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 78,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 80,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Rings for Split TR Tx channel */
		{
			.start_resource = 32,
			.num_resource = 12,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 44,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 44,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 50,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 52,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Block copy channel */
		{
			.start_resource = 0,
			.num_resource = 18,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 18,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 18,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 24,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 26,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Split TR Rx channel */
		{
			.start_resource = 0,
			.num_resource = 18,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 18,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 18,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 24,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 26,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Split TR Tx channel */
		{
			.start_resource = 0,
			.num_resource = 12,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 12,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 12,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 18,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 20,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Interrupt aggregator Virtual interrupts */
		{
			.start_resource = 6,
			.num_resource = 34,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_VINT),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 44,
			.num_resource = 36,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_VINT),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 44,
			.num_resource = 36,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_VINT),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 168,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_VINT),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* DMASS Interrupt aggregator Global events */
		{
			.start_resource = 14,
			.num_resource = 512,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 526,
			.num_resource = 256,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 526,
			.num_resource = 256,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 782,
			.num_resource = 128,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 910,
			.num_resource = 626,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS timer manager event */
		{
			.start_resource = 0,
			.num_resource = 1024,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_TIMERMGR_EVT_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Tx channel error event */
		{
			.start_resource = 4096,
			.num_resource = 29,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_PKTDMA_TX_CHAN_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Tx flow completion event */
		{
			.start_resource = 4608,
			.num_resource = 99,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_PKTDMA_TX_FLOW_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Rx channel error event */
		{
			.start_resource = 5120,
			.num_resource = 24,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_PKTDMA_RX_CHAN_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Rx flow completion event */
		{
			.start_resource = 5632,
			.num_resource = 51,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Rx flow starvation event */
		{
			.start_resource = 6144,
			.num_resource = 51,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_STARVATION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Rx flow firewall event */
		{
			.start_resource = 6656,
			.num_resource = 51,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_FIREWALL_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA BC channel error event */
		{
			.start_resource = 8192,
			.num_resource = 32,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_CHAN_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA BC channel data completion event */
		{
			.start_resource = 8704,
			.num_resource = 32,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_CHAN_DATA_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA BC channel ring completion event */
		{
			.start_resource = 9216,
			.num_resource = 32,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_CHAN_RING_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA Tx channel error event */
		{
			.start_resource = 9728,
			.num_resource = 22,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA Tx channel data completion event */
		{
			.start_resource = 10240,
			.num_resource = 22,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_DATA_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA Tx channel ring completion event */
		{
			.start_resource = 10752,
			.num_resource = 22,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_RING_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA Rx channel error event */
		{
			.start_resource = 11264,
			.num_resource = 28,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA Rx channel data completion event */
		{
			.start_resource = 11776,
			.num_resource = 28,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_DATA_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA Rx channel ring completion event */
		{
			.start_resource = 12288,
			.num_resource = 28,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_RING_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS DMASS UDMA global config */
		{
			.start_resource = 0,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_UDMAP_GLOBAL_CONFIG),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Free rings for Tx channel */
		{
			.start_resource = 0,
			.num_resource = 10,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 13,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 16,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Rings for CPSW Tx channel */
		{
			.start_resource = 19,
			.num_resource = 64,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_CPSW_TX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 19,
			.num_resource = 64,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_CPSW_TX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* DMASS Packet DMA Rings for SA2UL Tx channel0 */
		{
			.start_resource = 83,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_0_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Rings for SA2UL Tx channel1 */
		{
			.start_resource = 91,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_1_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Free rings for Rx channel */
		{
			.start_resource = 99,
			.num_resource = 10,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 109,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 109,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 112,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 115,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Rings for CPSW Rx channel */
		{
			.start_resource = 118,
			.num_resource = 16,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_CPSW_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 118,
			.num_resource = 16,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_CPSW_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* DMASS Packet DMA Rings for SA2UL Rx channel0 */
		{
			.start_resource = 134,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_0_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Rings for SA2UL Rx channel1 */
		{
			.start_resource = 134,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_1_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Rings for SA2UL Rx channel2 */
		{
			.start_resource = 142,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_2_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Rings for SA2UL Rx channel3 */
		{
			.start_resource = 142,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_3_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Free Tx channel */
		{
			.start_resource = 0,
			.num_resource = 10,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 13,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 16,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA CPSW Tx channel */
		{
			.start_resource = 19,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_CPSW_TX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 19,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_CPSW_TX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* DMASS Packet DMA SA2UL Tx channel0 */
		{
			.start_resource = 27,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_SAUL_TX_0_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Tx channel1 */
		{
			.start_resource = 28,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_SAUL_TX_1_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Free Rx channel */
		{
			.start_resource = 0,
			.num_resource = 10,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 13,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 16,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA Free flows for Rx channel */
		{
			.start_resource = 0,
			.num_resource = 10,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_0,
		},
		{
			.start_resource = 10,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MAIN_0_R5_1,
		},
		{
			.start_resource = 13,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		{
			.start_resource = 16,
			.num_resource = 3,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA CPSW Rx channel */
		{
			.start_resource = 19,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_CPSW_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 19,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_CPSW_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* DMASS Packet DMA CPSW Rx flows */
		{
			.start_resource = 19,
			.num_resource = 16,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_CPSW_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		{
			.start_resource = 19,
			.num_resource = 16,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_CPSW_RX_CHAN),
			.host_id = HOST_ID_MCU_0_R5_0,
		},
		/* DMASS Packet DMA SA2UL Rx channel0 */
		{
			.start_resource = 20,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_SAUL_RX_0_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel0 flows */
		{
			.start_resource = 35,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_0_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel1 */
		{
			.start_resource = 21,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_SAUL_RX_1_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel1 flows */
		{
			.start_resource = 35,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_1_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel2 */
		{
			.start_resource = 22,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_SAUL_RX_2_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel2 flows */
		{
			.start_resource = 43,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_2_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel3 */
		{
			.start_resource = 23,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_SAUL_RX_3_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA SA2UL Rx channel3 flows */
		{
			.start_resource = 43,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_PKTDMA_0,
					RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_3_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS Packet DMA Ring accelerator error event */
		{
			.start_resource = 0,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_RINGACC_0,
					RESASG_SUBTYPE_RA_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* DMASS Packet DMA virt_id range */
		{
			.start_resource = 2,
			.num_resource = 2,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS0_RINGACC_0,
					RESASG_SUBTYPE_RA_VIRTID),
			.host_id = HOST_ID_A53_2,
		},
		/* Block Copy DMA DMASS1 Global event trigger */
		{
			.start_resource = 51200,
			.num_resource = 12,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_BCDMA_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_TRIGGER),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA DMASS1 Global config */
		{
			.start_resource = 0,
			.num_resource = 1,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_BCDMA_0,
					RESASG_SUBTYPE_UDMAP_GLOBAL_CONFIG),
			.host_id = HOST_ID_ALL,
		},
		/* Block Copy DMA Rings DMASS1 for Split TR Rx channel */
		{
			.start_resource = 0,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* Block Copy DMA DMASS1 Split TR Rx channel */
		{
			.start_resource = 0,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_BCDMA_0,
					RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS1 Interrupt aggregator Virtual interrupts */
		{
			.start_resource = 0,
			.num_resource = 8,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_INTAGGR_0,
					RESASG_SUBTYPE_IA_VINT),
			.host_id = HOST_ID_A53_2,
		},
		/* DMASS1 Interrupt aggregator Global events */
		{
			.start_resource = 12288,
			.num_resource = 128,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_INTAGGR_0,
					RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
			.host_id = HOST_ID_A53_2,
		},
		/* Block copy DMA DMASS1 Rx channel error event */
		{
			.start_resource = 3072,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_ERROR_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA DMASS1 Rx channel data completion event */
		{
			.start_resource = 3584,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_DATA_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
		/* Block copy DMA DMASS1 Rx channel ring completion event */
		{
			.start_resource = 4096,
			.num_resource = 6,
			.type = RESASG_UTYPE (AM62A_DEV_DMASS1_INTAGGR_0,
					RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_RING_COMPLETION_OES),
			.host_id = HOST_ID_ALL,
		},
	},
};
