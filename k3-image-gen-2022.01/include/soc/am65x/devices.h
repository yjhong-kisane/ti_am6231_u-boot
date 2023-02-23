/*
 * K3 System Firmware Board Configuration Data Definitions
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef SOC_AM6_DEVICES_H
#define SOC_AM6_DEVICES_H

#define AM6_DEV_MCU_ADC0 0
#define AM6_DEV_MCU_ADC1 1
#define AM6_DEV_CAL0 2
#define AM6_DEV_CMPEVENT_INTRTR0 3
#define AM6_DEV_MCU_CPSW0 5
#define AM6_DEV_CPT2_AGGR0 6
#define AM6_DEV_MCU_CPT2_AGGR0 7
#define AM6_DEV_STM0 8
#define AM6_DEV_DCC0 9
#define AM6_DEV_DCC1 10
#define AM6_DEV_DCC2 11
#define AM6_DEV_DCC3 12
#define AM6_DEV_DCC4 13
#define AM6_DEV_DCC5 14
#define AM6_DEV_DCC6 15
#define AM6_DEV_DCC7 16
#define AM6_DEV_MCU_DCC0 17
#define AM6_DEV_MCU_DCC1 18
#define AM6_DEV_MCU_DCC2 19
#define AM6_DEV_DDRSS0 20
#define AM6_DEV_DEBUGSS_WRAP0 21
#define AM6_DEV_WKUP_DMSC0 22
#define AM6_DEV_TIMER0 23
#define AM6_DEV_TIMER1 24
#define AM6_DEV_TIMER10 25
#define AM6_DEV_TIMER11 26
#define AM6_DEV_TIMER2 27
#define AM6_DEV_TIMER3 28
#define AM6_DEV_TIMER4 29
#define AM6_DEV_TIMER5 30
#define AM6_DEV_TIMER6 31
#define AM6_DEV_TIMER7 32
#define AM6_DEV_TIMER8 33
#define AM6_DEV_TIMER9 34
#define AM6_DEV_MCU_TIMER0 35
#define AM6_DEV_MCU_TIMER1 36
#define AM6_DEV_MCU_TIMER2 37
#define AM6_DEV_MCU_TIMER3 38
#define AM6_DEV_ECAP0 39
#define AM6_DEV_EHRPWM0 40
#define AM6_DEV_EHRPWM1 41
#define AM6_DEV_EHRPWM2 42
#define AM6_DEV_EHRPWM3 43
#define AM6_DEV_EHRPWM4 44
#define AM6_DEV_EHRPWM5 45
#define AM6_DEV_ELM0 46
#define AM6_DEV_MMCSD0 47
#define AM6_DEV_MMCSD1 48
#define AM6_DEV_EQEP0 49
#define AM6_DEV_EQEP1 50
#define AM6_DEV_EQEP2 51
#define AM6_DEV_ESM0 52
#define AM6_DEV_MCU_ESM0 53
#define AM6_DEV_WKUP_ESM0 54
#define AM6_DEV_GIC0 56
#define AM6_DEV_GPIO0 57
#define AM6_DEV_GPIO1 58
#define AM6_DEV_WKUP_GPIO0 59
#define AM6_DEV_GPMC0 60
#define AM6_DEV_GTC0 61
#define AM6_DEV_PRU_ICSSG0 62
#define AM6_DEV_PRU_ICSSG1 63
#define AM6_DEV_PRU_ICSSG2 64
#define AM6_DEV_GPU0 65
#define AM6_DEV_CCDEBUGSS0 66
#define AM6_DEV_DSS0 67
#define AM6_DEV_DEBUGSS0 68
#define AM6_DEV_EFUSE0 69
#define AM6_DEV_PSC0 70
#define AM6_DEV_MCU_DEBUGSS0 71
#define AM6_DEV_MCU_EFUSE0 72
#define AM6_DEV_PBIST0 73
#define AM6_DEV_PBIST1 74
#define AM6_DEV_MCU_PBIST0 75
#define AM6_DEV_PLLCTRL0 76
#define AM6_DEV_WKUP_PLLCTRL0 77
#define AM6_DEV_MCU_ROM0 78
#define AM6_DEV_WKUP_PSC0 79
#define AM6_DEV_WKUP_VTM0 80
#define AM6_DEV_DEBUGSUSPENDRTR0 81
#define AM6_DEV_CBASS0 82
#define AM6_DEV_CBASS_DEBUG0 83
#define AM6_DEV_CBASS_FW0 84
#define AM6_DEV_CBASS_INFRA0 85
#define AM6_DEV_ECC_AGGR0 86
#define AM6_DEV_ECC_AGGR1 87
#define AM6_DEV_ECC_AGGR2 88
#define AM6_DEV_MCU_CBASS0 89
#define AM6_DEV_MCU_CBASS_DEBUG0 90
#define AM6_DEV_MCU_CBASS_FW0 91
#define AM6_DEV_MCU_ECC_AGGR0 92
#define AM6_DEV_MCU_ECC_AGGR1 93
#define AM6_DEV_WKUP_CBASS0 94
#define AM6_DEV_WKUP_ECC_AGGR0 95
#define AM6_DEV_WKUP_CBASS_FW0 96
#define AM6_DEV_MAIN2MCU_LVL_INTRTR0 97
#define AM6_DEV_MAIN2MCU_PLS_INTRTR0 98
#define AM6_DEV_CTRL_MMR0 99
#define AM6_DEV_GPIOMUX_INTRTR0 100
#define AM6_DEV_PLL_MMR0 101
#define AM6_DEV_MCU_MCAN0 102
#define AM6_DEV_MCU_MCAN1 103
#define AM6_DEV_MCASP0 104
#define AM6_DEV_MCASP1 105
#define AM6_DEV_MCASP2 106
#define AM6_DEV_MCU_CTRL_MMR0 107
#define AM6_DEV_MCU_PLL_MMR0 108
#define AM6_DEV_MCU_SEC_MMR0 109
#define AM6_DEV_I2C0 110
#define AM6_DEV_I2C1 111
#define AM6_DEV_I2C2 112
#define AM6_DEV_I2C3 113
#define AM6_DEV_MCU_I2C0 114
#define AM6_DEV_WKUP_I2C0 115
#define AM6_DEV_MCU_MSRAM0 116
#define AM6_DEV_DFTSS0 117
#define AM6_DEV_NAVSS0 118
#define AM6_DEV_MCU_NAVSS0 119
#define AM6_DEV_PCIE0 120
#define AM6_DEV_PCIE1 121
#define AM6_DEV_PDMA_DEBUG0 122
#define AM6_DEV_PDMA0 123
#define AM6_DEV_PDMA1 124
#define AM6_DEV_MCU_PDMA0 125
#define AM6_DEV_MCU_PDMA1 126
#define AM6_DEV_MCU_PSRAM0 127
#define AM6_DEV_PSRAMECC0 128
#define AM6_DEV_MCU_ARMSS0 129
#define AM6_DEV_RTI0 130
#define AM6_DEV_RTI1 131
#define AM6_DEV_RTI2 132
#define AM6_DEV_RTI3 133
#define AM6_DEV_MCU_RTI0 134
#define AM6_DEV_MCU_RTI1 135
#define AM6_DEV_SA2_UL0 136
#define AM6_DEV_MCSPI0 137
#define AM6_DEV_MCSPI1 138
#define AM6_DEV_MCSPI2 139
#define AM6_DEV_MCSPI3 140
#define AM6_DEV_MCSPI4 141
#define AM6_DEV_MCU_MCSPI0 142
#define AM6_DEV_MCU_MCSPI1 143
#define AM6_DEV_MCU_MCSPI2 144
#define AM6_DEV_TIMESYNC_INTRTR0 145
#define AM6_DEV_UART0 146
#define AM6_DEV_UART1 147
#define AM6_DEV_UART2 148
#define AM6_DEV_MCU_UART0 149
#define AM6_DEV_WKUP_UART0 150
#define AM6_DEV_USB3SS0 151
#define AM6_DEV_USB3SS1 152
#define AM6_DEV_SERDES0 153
#define AM6_DEV_SERDES1 154
#define AM6_DEV_WKUP_CTRL_MMR0 155
#define AM6_DEV_WKUP_GPIOMUX_INTRTR0 156
#define AM6_DEV_BOARD0 157
#define AM6_DEV_MCU_ARMSS0_CPU0 159
#define AM6_DEV_WKUP_DMSC0_CORTEX_M3_0 161
#define AM6_DEV_NAVSS0_CPTS0 163
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER0 164
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER1 165
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER2 166
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER3 167
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER4 168
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER5 169
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER6 170
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER7 171
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER8 172
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER9 173
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER10 174
#define AM6_DEV_NAVSS0_MAILBOX0_CLUSTER11 175
#define AM6_DEV_NAVSS0_MCRC0 176
#define AM6_DEV_NAVSS0_PVU0 177
#define AM6_DEV_NAVSS0_PVU1 178
#define AM6_DEV_NAVSS0_UDMASS_INTA0 179
#define AM6_DEV_NAVSS0_MODSS_INTA0 180
#define AM6_DEV_NAVSS0_MODSS_INTA1 181
#define AM6_DEV_NAVSS0_INTR_ROUTER_0 182
#define AM6_DEV_NAVSS0_TIMER_MGR0 183
#define AM6_DEV_NAVSS0_TIMER_MGR1 184
#define AM6_DEV_NAVSS0_PROXY0 185
#define AM6_DEV_NAVSS0_RINGACC0 187
#define AM6_DEV_NAVSS0_UDMAP0 188
#define AM6_DEV_MCU_NAVSS0_INTR_AGGR_0 189
#define AM6_DEV_MCU_NAVSS0_INTR_ROUTER_0 190
#define AM6_DEV_MCU_NAVSS0_PROXY0 191
#define AM6_DEV_MCU_NAVSS0_MCRC0 193
#define AM6_DEV_MCU_NAVSS0_UDMAP0 194
#define AM6_DEV_MCU_NAVSS0_RINGACC0 195
#define AM6_DEV_COMPUTE_CLUSTER_MSMC0 196
#define AM6_DEV_COMPUTE_CLUSTER_PBIST0 197
#define AM6_DEV_COMPUTE_CLUSTER_CPAC0 198
#define AM6_DEV_COMPUTE_CLUSTER_CPAC_PBIST0 199
#define AM6_DEV_COMPUTE_CLUSTER_CPAC1 200
#define AM6_DEV_COMPUTE_CLUSTER_CPAC_PBIST1 201
#define AM6_DEV_COMPUTE_CLUSTER_A53_0 202
#define AM6_DEV_COMPUTE_CLUSTER_A53_1 203
#define AM6_DEV_COMPUTE_CLUSTER_A53_2 204
#define AM6_DEV_COMPUTE_CLUSTER_A53_3 205
#define AM6_DEV_CPT2_PROBE_VBUSM_MAIN_NAVSRAMLO_4 206
#define AM6_DEV_CPT2_PROBE_VBUSM_MCU_FSS_S1_3 207
#define AM6_DEV_CPT2_PROBE_VBUSM_MCU_EXPORT_SLV_0 208
#define AM6_DEV_CPT2_PROBE_VBUSM_MAIN_NAVSRAMHI_3 209
#define AM6_DEV_CPT2_PROBE_VBUSM_MCU_SRAM_SLV_1 210
#define AM6_DEV_CPT2_PROBE_VBUSM_MAIN_NAVDDRHI_5 211
#define AM6_DEV_CPT2_PROBE_VBUSM_MAIN_NAVDDRLO_6 212
#define AM6_DEV_CPT2_PROBE_VBUSM_MAIN_CAL0_0 213
#define AM6_DEV_CPT2_PROBE_VBUSM_MAIN_DSS_2 214
#define AM6_DEV_CPT2_PROBE_VBUSM_MCU_FSS_S0_2 215
#define AM6_DEV_OLDI_TX_CORE_MAIN_0 216
#define AM6_DEV_K3_ARM_ATB_FUNNEL_3_32_MCU_0 217
#define AM6_DEV_ICEMELTER_WKUP_0 218
#define AM6_DEV_K3_LED_MAIN_0 219
#define AM6_DEV_VDC_DATA_VBUSM_32B_REF_WKUP2MCU 220
#define AM6_DEV_VDC_DATA_VBUSM_32B_REF_MCU2WKUP 221
#define AM6_DEV_VDC_DATA_VBUSM_64B_REF_MAIN2MCU 222
#define AM6_DEV_VDC_DATA_VBUSM_64B_REF_MCU2MAIN 223
#define AM6_DEV_VDC_DMSC_DBG_VBUSP_32B_REF_DBG2DMSC 224
#define AM6_DEV_VDC_INFRA_VBUSP_32B_REF_WKUP2MAIN_INFRA 225
#define AM6_DEV_VDC_INFRA_VBUSP_32B_REF_MCU2MAIN_INFRA 226
#define AM6_DEV_VDC_SOC_FW_VBUSP_32B_REF_FWWKUP2MCU 227
#define AM6_DEV_VDC_SOC_FW_VBUSP_32B_REF_FWMCU2MAIN 228
#define AM6_DEV_VDC_MCU_DBG_VBUSP_32B_REF_DBGMAIN2MCU 229
#define AM6_DEV_VDC_NAV_PSIL_128B_REF_MAIN2MCU 230
#define AM6_DEV_GS80PRG_SOC_WRAP_WKUP_0 231
#define AM6_DEV_GS80PRG_MCU_WRAP_WKUP_0 232
#define AM6_DEV_MX_WAKEUP_RESET_SYNC_WKUP_0 233
#define AM6_DEV_MX_EFUSE_MAIN_CHAIN_MAIN_0 234
#define AM6_DEV_MX_EFUSE_MCU_CHAIN_MCU_0 235
#define AM6_DEV_DUMMY_IP_LPSC_WKUP2MCU_VD 236
#define AM6_DEV_DUMMY_IP_LPSC_WKUP2MAIN_INFRA_VD 237
#define AM6_DEV_DUMMY_IP_LPSC_DEBUG2DMSC_VD 238
#define AM6_DEV_DUMMY_IP_LPSC_DMSC_VD 239
#define AM6_DEV_DUMMY_IP_LPSC_MCU2MAIN_INFRA_VD 240
#define AM6_DEV_DUMMY_IP_LPSC_MCU2MAIN_VD 241
#define AM6_DEV_DUMMY_IP_LPSC_MCU2WKUP_VD 242
#define AM6_DEV_DUMMY_IP_LPSC_MAIN2MCU_VD 243
#define AM6_DEV_DUMMY_IP_LPSC_EMIF_DATA_VD 244
#define AM6_DEV_MCU_ARMSS0_CPU1 245
#define AM6_DEV_MCU_FSS0_FSAS_0 246
#define AM6_DEV_MCU_FSS0_HYPERBUS0 247
#define AM6_DEV_MCU_FSS0_OSPI_0 248
#define AM6_DEV_MCU_FSS0_OSPI_1 249

#endif /* SOC_AM6_DEVICES_H */
