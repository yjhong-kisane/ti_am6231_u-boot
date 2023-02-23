/*
 * System Firmware Source File
 *
 * Host IDs for J784S4 device
 *
 * Data version: 220615_194547
 *
 * Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef J784S4_HOSTS_H
#define J784S4_HOSTS_H

/** TIFS(Secure): Security Controller */
#define HOST_ID_TIFS (0U)
/** DM(Non Secure): Device Management */
#define HOST_ID_DM (254U)
/** MCU_0_R5_0(Non Secure): Cortex R5 context 0 on MCU island */
#define HOST_ID_MCU_0_R5_0 (3U)
/** MCU_0_R5_1(Secure): Cortex R5 context 1 on MCU island(Boot) */
#define HOST_ID_MCU_0_R5_1 (4U)
/** MCU_0_R5_2(Non Secure): Cortex R5 context 2 on MCU island */
#define HOST_ID_MCU_0_R5_2 (5U)
/** MCU_0_R5_3(Secure): Cortex R5 context 3 on MCU island */
#define HOST_ID_MCU_0_R5_3 (6U)
/** A72_0(Secure): Cortex A72 context 0 on Main island */
#define HOST_ID_A72_0 (10U)
/** A72_1(Secure): Cortex A72 context 1 on Main island */
#define HOST_ID_A72_1 (11U)
/** A72_2(Non Secure): Cortex A72 context 2 on Main island */
#define HOST_ID_A72_2 (12U)
/** A72_3(Non Secure): Cortex A72 context 3 on Main island */
#define HOST_ID_A72_3 (13U)
/** A72_4(Non Secure): Cortex A72 context 4 on Main island */
#define HOST_ID_A72_4 (14U)
/** A72_5(Non Secure): Cortex A72 context 5 on Main island */
#define HOST_ID_A72_5 (15U)
/** A72_6(Non Secure): Cortex A72 context 6 on Main island */
#define HOST_ID_A72_6 (16U)
/** A72_7(Non Secure): Cortex A72 context 7 on Main island */
#define HOST_ID_A72_7 (17U)
/** C7X_0_0(Secure): C7x_0 Context 0 on Main island */
#define HOST_ID_C7X_0_0 (20U)
/** C7X_0_1(Non Secure): C7x_0 context 1 on Main island */
#define HOST_ID_C7X_0_1 (21U)
/** C7X_1_0(Secure): C7x_1 Context 0 on Main island */
#define HOST_ID_C7X_1_0 (22U)
/** C7X_1_1(Non Secure): C7x_1 context 1 on Main island */
#define HOST_ID_C7X_1_1 (23U)
/** C7X_2_0(Secure): C7x_2 Context 0 on Main island */
#define HOST_ID_C7X_2_0 (24U)
/** C7X_2_1(Non Secure): C7x_2 context 1 on Main island */
#define HOST_ID_C7X_2_1 (25U)
/** C7X_3_0(Secure): C7x_2 Context 0 on Main island */
#define HOST_ID_C7X_3_0 (26U)
/** C7X_3_1(Non Secure): C7x_3 context 1 on Main island */
#define HOST_ID_C7X_3_1 (27U)
/** GPU_0(Non Secure): BXS context 0 on Main island */
#define HOST_ID_GPU_0 (30U)
/** MAIN_0_R5_0(Non Secure): Cortex R5_0 context 0 on Main island */
#define HOST_ID_MAIN_0_R5_0 (35U)
/** MAIN_0_R5_1(Secure): Cortex R5_0 context 1 on Main island */
#define HOST_ID_MAIN_0_R5_1 (36U)
/** MAIN_0_R5_2(Non Secure): Cortex R5_0 context 2 on Main island */
#define HOST_ID_MAIN_0_R5_2 (37U)
/** MAIN_0_R5_3(Secure): Cortex R5_0 context 3 on MCU island */
#define HOST_ID_MAIN_0_R5_3 (38U)
/** MAIN_1_R5_0(Non Secure): Cortex R5_1 context 0 on Main island */
#define HOST_ID_MAIN_1_R5_0 (40U)
/** MAIN_1_R5_1(Secure): Cortex R5_1 context 1 on Main island */
#define HOST_ID_MAIN_1_R5_1 (41U)
/** MAIN_1_R5_2(Non Secure): Cortex R5_1 context 2 on Main island */
#define HOST_ID_MAIN_1_R5_2 (42U)
/** MAIN_1_R5_3(Secure): Cortex R5_1 context 3 on MCU island */
#define HOST_ID_MAIN_1_R5_3 (43U)
/** MAIN_2_R5_0(Non Secure): Cortex R5_2 context 0 on Main island */
#define HOST_ID_MAIN_2_R5_0 (45U)
/** MAIN_2_R5_1(Secure): Cortex R5_2 context 1 on Main island */
#define HOST_ID_MAIN_2_R5_1 (46U)
/** MAIN_2_R5_2(Non Secure): Cortex R5_2 context 2 on Main island */
#define HOST_ID_MAIN_2_R5_2 (47U)
/** MAIN_2_R5_3(Secure): Cortex R5_2 context 3 on MCU island */
#define HOST_ID_MAIN_2_R5_3 (48U)
/** DM2TIFS(Secure): DM to TIFS communication */
#define HOST_ID_DM2TIFS (250U)
/** TIFS2DM(Non Secure): TIFS to DM communication */
#define HOST_ID_TIFS2DM (251U)
/** HSM(Secure): HSM Controller */
#define HOST_ID_HSM (253U)

/**
 * Host catch all. Used in board configuration resource assignments to define
 * resource ranges useable by all hosts. Cannot be used
 */
#define HOST_ID_ALL (128U)

/** Number of unique hosts on the SoC */
#define HOST_ID_CNT (38U)

#endif /* J784S4_HOSTS_H */
