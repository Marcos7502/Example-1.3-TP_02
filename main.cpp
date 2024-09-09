/**
   Mbed utiliza el HAL y las APIs de LL de STM32CubeF4 para manipular el hardware de la placa NUCLEO-F429ZI.

   Este paquete se encuentra en la carpeta ./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver.

   Para utilizar solamente funciones de C en este ejemplo se utilizan el driver genérico GPIO del HAL. Las funciones requeridas se encuentran declaradas en el archivo de cabecera ./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.h

   Para utilizar el HAL se debe incluir el archivo stm32f4xx_hal.h e inicializar el sistema invocando la función HAL_Init(), para más información ver el documento de referencia [1].

   Documentos de referencia:
   [1] ST user manual UM1725 - Description of STM32F4 HAL and low-layer drivers - Revision 8 [22-Mar-2023].
*/

#include "stm32f4xx_hal.h"

// Alarm led GPIO address
#define ALARM_LED_PIN        GPIO_PIN_0
#define ALARM_LED_GPIO_PORT  GPIOB

// Gas detector GPIO address
#define GAS_DETECTOR_PIN        GPIO_PIN_15
#define GAS_DETECTOR_GPIO_PORT  GPIOF

// Overtemperature detector GPIO address
#define OVERTEMPERATURE_DETECTOR_PIN        GPIO_PIN_13
#define OVERTEMPERATURE_DETECTOR_GPIO_PORT  GPIOE

// Alarm off button GPIO address
#define ALARM_OFF_BUTTON_PIN        GPIO_PIN13
#define ALARM_OFF_BUTTON_GPIO_PORT  GPIOC


/**
 *  \brief Main program
 */ 
int main(void)
{

  GPIO_InitTypeDef GPIO_InitStruct ;
  
  HAL_Init() ;
  
  // Alarm LED output pin configuration
  __HAL_RCC_GPIOB_CLK_ENABLE() ;
  
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP ;
  GPIO_InitStruct.Pull  = GPIO_NOPULL ;
  GPIO_InitStruct.Pin   = ALARM_LED_PIN ;
  
  HAL_GPIO_Init(ALARM_LED_GPIO_PORT, &GPIO_InitStruct) ;

  // Gas detector input pin configuration
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN ;
  GPIO_InitStruct.Pin  = GAS_DETECTOR_PIN ;

  HAL_GPIO_Init(GAS_DETECTOR_GPIO_PORT, &GPIO_InitStruct) ;
  
  // Overtemperature detector input pin configuration  
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN ;
  GPIO_InitStruct.Pin  = OVERTEMPERATURE_DETECTOR_PIN ;

  HAL_GPIO_Init(OVERTEMPERATURE_DETECTOR_GPIO_PORT, &GPIO_InitStruct) ;
  
  // Alarm off button pin configuration
  __HAL_RCC_GPIOC_CLK_ENABLE() ;
  
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  GPIO_InitStruct.Pull = GPIO_NOPULL ;
  GPIO_InitStruct.Pin  = ALARM_OFF_BUTTON_PIN ;
  
  HAL_GPIO_Init(ALARM_OFF_BUTTON_GPIO_PORT, &GPIO_InitStruct) ;
   
  int alarmState = 0 ;

  while (true) {
    
    if (HAL_GPIO_ReadPin(GAS_DETECTOR_GPIO_PORT, GAS_DETECTOR_PIN) || HAL_GPIO_ReadPin(OVERTEMPERATURE_DETECTOR_GPIO_PORT, OVERTEMPERATURE_DETECTOR_PIN)) {
      alarmState = 1 ;
      HAL_GPIO_WritePin(ALARM_LED_GPIO_PORT, ALARM_LED_PIN, GPIO_PIN_SET) ;
    }

    if (HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN)) {
      alarmState = 0 ;
      HAL_GPIO_WritePin(ALARM_LED_GPIO_PORT, ALARM_LED_PIN, GPIO_PIN_RESET) ;                
    }
    
  }
  
}
