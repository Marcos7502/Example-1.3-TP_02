/**
   Mbed utiliza el HAL y las APIs de LL de STM32CubeF4 para manipular el hardware de la placa NUCLEO-F429ZI.

   Este paquete se encuentra en la carpeta ./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver.

   Para utilizar solamente funciones de C en este ejemplo se utilizan el driver genérico GPIO del HAL. Las funciones requeridas se encuentran declaradas en el archivo de cabecera ./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.h

   Para utilizar el HAL se debe incluir el archivo stm32f4xx_hal.h e inicializar el sistema invocando la función HAL_Init(), para más información ver el documento de referencia [1].

   Documentos de referencia:
   [1] ST user manual UM1725 - Description of STM32F4 HAL and low-layer drivers - Revision 8 [22-Mar-2023].
*/

#include "stm32f4xx_hal.h"

/*
#define ALARM_LED_PIN GPIO_PIN_1
#define GAS_DETECTOR_PIN GPIO_PIN_2
#define OVERTEMP_DETECTOR_PIN GPIO_PIN_3
#define ALARM_OFF_BUTTON_PIN GPIO_PIN_1

#define ALARM_LED_PORT GPIOD
#define GAS_DETECTOR_PORT GPIOD
#define OVERTEMP_DETECTOR_PORT GPIOD
#define ALARM_OFF_BUTTON_PORT GPIOA
*/

int main(void)
{

  GPIO_InitTypeDef GPIO_InitStruct ;
  
  HAL_Init() ;
  
  // Alarm LED output pin configuration
  __HAL_RCC_GPIOB_CLK_ENABLE() ;
  
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP ;
  GPIO_InitStruct.Pull  = GPIO_PULLUP ;
  GPIO_InitStruct.Pin   = GPIO_PIN_0 ;
  
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct) ;


  // Gas detector input pin configuration
  __HAL_RCC_GPIOC_CLK_ENABLE() ;
  
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  GPIO_InitStruct.Pull = GPIO_NOPULL ;
  GPIO_InitStruct.Pin  = GPIO_PIN_13 ;
  
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct) ;
  
  // Overtemperature detector input pin configuration
   
  /*
  // Configuración del pin del LED como salida
  GPIO_InitStruct.Pin = ALARM_LED_PIN; // Se configura el pin de salida del LED
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Se pone en modo de salida
  GPIO_InitStruct.Pull = GPIO_NOPULL; // Se pone en modo de no pull
  HAL_GPIO_Init(ALARM_LED_PORT, &GPIO_InitStruct);

  // Configuración del detector de gas como entrada
  GPIO_InitStruct.Pin = GAS_DETECTOR_PIN; // Se configura el pin de entrada del detector
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Se pone en modo input
  GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Se pone en modo de pull down
  HAL_GPIO_Init(GAS_DETECTOR_PORT, &GPIO_InitStruct);

  // Configuración del detector de sobretemperatura como entrada
  GPIO_InitStruct.Pin = OVERTEMP_DETECTOR_PIN; // Se configura el pin de entrada del detector
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Se pone en modo input
  GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Se pone en modo de pull down
  HAL_GPIO_Init(OVERTEMP_DETECTOR_PORT, &GPIO_InitStruct);


  // Configuracion del boton de apagado de la alarma
  GPIO_InitStruct.Pin = ALARM_OFF_BUTTON_PIN; // Se configura el pin de la alarma
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Se pone en modo de entrada
  HAL_GPIO_Init(ALARM_OFF_BUTTON_PORT, &GPIO_InitStruct);

  int alarmState = 0 ;
  */

  while (true) {
    
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET) ;
    } else {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET) ;
    }
    
    /*
    // Se leen los valores del gas detector y del overtemp detector
    if (HAL_GPIO_ReadPin(GAS_DETECTOR_PORT, GAS_DETECTOR_PIN) || HAL_GPIO_ReadPin(OVERTEMP_DETECTOR_PORT, OVERTEMP_DETECTOR_PIN)) {
    alarmState = 1;
    HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_SET);  // Encender el LED
    }

    // Se leen los valores del gas detector y del overtemp detector
    if (HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN)) {
    alarmState = 0;
    HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_RESET);  // Apagar el LED
    */
  }
  
}
