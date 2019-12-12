/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* This function is executed in the context of the daemon task. */
static void vDeferredHandlingFunction( void *pvParameter1, uint32_t ulParameter2 );

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{

}

static void vDeferredHandlingFunction( void *pvParameter1, uint32_t ulParameter2 )
{
    printf( "Handler function - Processing event: %d\r\n ", ulParameter2 );
}

/* interrupt callback functions */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static uint32_t ulParameterValue = 0;
    BaseType_t xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;

    /* Send a pointer to the interrupt's deferred handling function to the daemon task.*/
    xTimerPendFunctionCallFromISR(vDeferredHandlingFunction,
				NULL,
				ulParameterValue,
				&xHigherPriorityTaskWoken );
    ulParameterValue++;

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
