/*
 * SPDX-FileCopyrightText: Copyright 2023 Arm Limited and/or its
 * affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BoardInit.hpp"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

#include "RTE_Components.h"
#include "RTE_Device.h"
#include CMSIS_device_header
#include "Driver_GPIO.h"
#include "pinconf.h"
#include "Driver_Common.h"
#include "ethosu_driver.h"
#include "uart_stdout.h"
#include <stdio.h>

#define LOCAL_PERIPHERAL_BASE     (0x40000000UL)

static struct ethosu_driver npuDriver;
static void npu_irq_handler(void)
{
    ethosu_irq_handler(&npuDriver);
}

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

bool NpuInit()
{
    /* Base address is 0x4000E1000; interrupt number is 55. */
    constexpr uint32_t npuBaseOffset = 0xE1000;
    const void *npuBaseAddr = reinterpret_cast<void*>(LOCAL_PERIPHERAL_BASE + npuBaseOffset);

    /*  Initialize Ethos-U NPU driver. */
    if (ethosu_init(&npuDriver, /* Arm Ethos-U device driver pointer  */
                    npuBaseAddr, /* Base address for the Arm Ethos-U device */
                    0, /* Cache memory pointer (not applicable for U55) */
                    0, /* Cache memory size */
                    1, /* Secure */
                    1) /* Privileged */ ) {
        printf("Failed to initialize Arm Ethos-U driver");
        return false;
    }

#if defined (M55_HP)
    NVIC_SetVector(NPU_HP_IRQ_IRQn, (uint32_t) &npu_irq_handler);
    NVIC_EnableIRQ(NPU_HP_IRQ_IRQn);
#elif defined(M55_HE)
    NVIC_SetVector(NPU_HE_IRQ_IRQn, (uint32_t) &npu_irq_handler);
    NVIC_EnableIRQ(NPU_HE_IRQ_IRQn);
#endif

    return true;
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CpuCacheEnable(void)
{
    /* Enable I-Cache */
    SCB_EnableICache();
 
    /* Enable D-Cache */
    SCB_EnableDCache();
}

#if defined (M55_HP)

static int I3CPinsInit(void)
{
    /* Configure GPIO Pin : P1_2 as I3C_SDA_B */
    /* Pin-Pad P1_2 as I3C_SDA_B
     * Pad function: PAD_FUNCTION_READ_ENABLE |
     *  PAD_FUNCTION_DRIVER_DISABLE_STATE_WITH_PULL_UP |
     *  PAD_FUNCTION_DRIVER_OPEN_DRAIN
     */
    int ret = pinconf_set(PORT_1, PIN_2, PINMUX_ALTERNATE_FUNCTION_3, PADCTRL_READ_ENABLE | PADCTRL_DRIVER_DISABLED_PULL_UP | PADCTRL_DRIVER_OPEN_DRAIN);
    if(ret != ARM_DRIVER_OK) {
        return ret;
    }

    /* Configure GPIO Pin : P1_3 as I3C_SCL_B */       
    /* Pin-Pad P1_3 as I3C_SCL_B
     * Pad function: PAD_FUNCTION_READ_ENABLE |
     *  PAD_FUNCTION_DRIVER_DISABLE_STATE_WITH_PULL_UP |
     *  PAD_FUNCTION_DRIVER_OPEN_DRAIN
     */
    ret = pinconf_set(PORT_1, PIN_3, PINMUX_ALTERNATE_FUNCTION_3, PADCTRL_READ_ENABLE | PADCTRL_DRIVER_DISABLED_PULL_UP | PADCTRL_DRIVER_OPEN_DRAIN);
    if(ret != ARM_DRIVER_OK) {
        return ret;
    }
    return 0;
}

static int CameraPinsInit(void)
{
    /* @Note: Below GPIO pins are configured for Camera.
     *
     *         For ASIC A1 CPU Board
     *         - P2_7 as CAM_XVCLK_B
     */
#if RTE_SILICON_REV_A1

    /* Configure GPIO Pin : P2_7 as CAM_XVCLK_B */
    int ret = PINMUX_Config(PORT_NUMBER_2, PIN_NUMBER_7, PINMUX_ALTERNATE_FUNCTION_6);

    if(ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif /* RTE_SILICON_REV_A1 */

    return 0;
}

#endif /* defined (M55_HP) */

void BoardInit(void)
{
#if !defined(SEMIHOSTING)
    UartStdOutInit();
#endif /* defined(SEMIHOSTING) */

#if defined (M55_HP)
    /* Initialise the I3C and camera pins for the High performance core. */
    if (ARM_DRIVER_OK != I3CPinsInit()) {
        printf("I3CPinsInit failed\n");
        return;
    }
    if (ARM_DRIVER_OK != CameraPinsInit()) {
        printf("CameraPinsInit failed\n");
        return;
    }
#endif /* defined (M55_HP) */

#if defined(ETHOSU_ARCH) && (ETHOSU_ARCH==u55)
    if (!NpuInit()) {
        return;
    }
#endif

    /* Enable the CPU Cache */
    CpuCacheEnable();
    return;
}
