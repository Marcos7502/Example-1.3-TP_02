/**
<<<<<<< HEAD
*  @file
*  Implementación en C y C++ del ejemplo 1.3 con compilación condicional.
*/
#include "mbed.h"
#include "arm_book_lib.h"
#include "main.h"



#ifdef C
/**
 * Mbed utiliza el HAL y las APIs de LL de STM32CubeF4 para manipular el
hardware de la placa NUCLEO-F429ZI.

   Este paquete se encuentra en la carpeta
./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver.

   Para utilizar solamente funciones de C en este ejemplo se utiliza el driver
genérico GPIO del HAL. Las funciones requeridas se encuentran declaradas en el
archivo de cabecera
./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.h

   Para utilizar el HAL se debe incluir el archivo stm32f4xx_hal.h e inicializar
el sistema invocando la función HAL_Init(), para más información ver el
documento de referencia [1].

   La configuración de los puertos se realiza con la función:
   HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);

   La escritura de los puertos se realiza con la función:
   HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState
PinState);

   La lectura de los puertos se realiza con la función:
   GPIO_PinState HAL_GPIO_ReadPin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin);
   
   Documentos de referencia:
   [1] ST user manual UM1725 - Description of STM32F4 HAL and low-layer drivers - Revision 8 [22-Mar-2023].
*/
#include "stm32f4xx_hal.h"

/**
 *  @brief Main program
 *  Implementado con funciones de C.
 */ 
int main(void)
    {

    GPIO_InitTypeDef GPIO_InitStruct ;
    
    HAL_Init() ;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();  
    __HAL_RCC_GPIOF_CLK_ENABLE();

    // Alarm LED output pin configuration  
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
    
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
    GPIO_InitStruct.Pull = GPIO_NOPULL ;
    GPIO_InitStruct.Pin  = ALARM_OFF_BUTTON_PIN ;
    
    HAL_GPIO_Init(ALARM_OFF_BUTTON_GPIO_PORT, &GPIO_InitStruct) ;
    
    int alarmState = 0 ;

    while (true) {
        
        if (HAL_GPIO_ReadPin(GAS_DETECTOR_GPIO_PORT, GAS_DETECTOR_PIN) || HAL_GPIO_ReadPin(OVERTEMPERATURE_DETECTOR_GPIO_PORT, OVERTEMPERATURE_DETECTOR_PIN)) {
            alarmState = 1 ;
            HAL_GPIO_WritePin(ALARM_LED_GPIO_PORT, ALARM_LED_PIN, GPIO_PIN_SET) ;
            printf("ALARM ON\r\n");
            printf("Gas Detector: %10d\r\n", HAL_GPIO_ReadPin(GAS_DETECTOR_GPIO_PORT, GAS_DETECTOR_PIN));
            printf("Overtemp Detector: %10d\r\n", HAL_GPIO_ReadPin(OVERTEMPERATURE_DETECTOR_GPIO_PORT, OVERTEMPERATURE_DETECTOR_PIN));
            printf("Alarm State: %10d\r\n", alarmState);
        }

        if (HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_GPIO_PORT, ALARM_OFF_BUTTON_PIN)) {
            alarmState = 0 ;
            HAL_GPIO_WritePin(ALARM_LED_GPIO_PORT, ALARM_LED_PIN, GPIO_PIN_RESET) ; 
            printf("ALARM OFF\r\n");
            printf("Gas Detector: %10d\r\n", HAL_GPIO_ReadPin(GAS_DETECTOR_GPIO_PORT, GAS_DETECTOR_PIN));
            printf("Overtemp Detector: %10d\r\n", HAL_GPIO_ReadPin(OVERTEMPERATURE_DETECTOR_GPIO_PORT, OVERTEMPERATURE_DETECTOR_PIN));
            printf("Alarm State: %10d\r\n", alarmState);               
        }

    }
    }

#endif


#ifdef CPLUSPLUS

    #include "mbed.h"
    #include "arm_book_lib.h"

    /**
    *  @brief Main program
    *  Implementado con funciones de C++.
    */ 
    int main(void)
    {

    DigitalIn gasDetector(D2) ;
    DigitalIn overTempDetector(D3) ;
    DigitalIn alarmOffButton(BUTTON1) ;

    DigitalOut alarmLed(LED1) ;

    gasDetector.mode(PullDown) ;
    overTempDetector.mode(PullDown) ;

    alarmLed = OFF ;

    bool alarmState = OFF ;

    while (true) {

        if ( gasDetector || overTempDetector ) {
        alarmState = ON ;
        }

        alarmLed = alarmState ;

        if ( alarmOffButton ) {
        alarmState = OFF ;
        }

        printf("Gas detector = %d | Overtemperature detector = %d | Alarm led = %d \n", gasDetector.read(), overTempDetector.read(), alarmLed.read()) ;
    }
    
    }

#endif

