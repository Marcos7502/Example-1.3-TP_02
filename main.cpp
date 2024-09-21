#include "mbed.h"
#include "arm_book_lib.h"

#include "stm32f4xx_hal.h"

#define  Cplusplus 

/* 

Mbed utiliza el HAL y las APIs de LL de STM32CubeF4 para manipular el hardware de la placa NUCLEO-F429ZI.

Este paquete se encuentra en la carpeta ./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver.

Para utilizar solamente funciones de C en este ejemplo se utilizan el driver genérico GPIO del HAL. Las funciones requeridas se encuentran declaradas en el archivo de cabecera ./mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.h

Para utilizar el HAL se debe incluir el archivo stm32f4xx_hal.h e inicializar el sistema invocando la función HAL_Init(), para más información ver el documento de referencia [1].

Documentos de referencia:
[1] ST user manual UM1725 - Description of STM32F4 HAL and low-layer drivers - Revision 8 [22-Mar-2023].


Las funciones esenciales son:
HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

La declaracion de variables como GPIO_InitTypeDef y GPIO_TypeDef esta descripta en el archivo mencionado
*/
// Alarm led GPIO address PA_3
#define ALARM_LED_PIN GPIO_PIN_3
#define ALARM_LED_PORT GPIOA

// Gas detector GPIO address D0 =PG_9
#define GAS_DETECTOR_PIN GPIO_PIN_9
#define GAS_DETECTOR_PORT GPIOG

// Overtem detector GPIO address D1 =PG_14
#define OVERTEMP_DETECTOR_PIN GPIO_PIN_14
#define OVERTEMP_DETECTOR_PORT GPIOG

// Alarmoff D2 = PF_15
#define ALARM_OFF_BUTTON_PIN GPIO_PIN_15
#define ALARM_OFF_BUTTON_PORT GPIOF


int main(void)
{   
    #ifdef C
    HAL_Init() ;
  
    // Alarm LED output pin configuration
    __HAL_RCC_GPIOD_CLK_ENABLE() ;
    GPIO_InitTypeDef GPIO_InitStruct; // Inicializamos el gpio struct para cargar las estructuras

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
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Se pone en modo de pull down
    HAL_GPIO_Init(ALARM_OFF_BUTTON_PORT, &GPIO_InitStruct);
    #endif

    #ifdef Cplusplus
    gpio_init()
    gpio_dir()
    gpio_read()
    DigitalIn gasDetector(D2);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);

    alarmLed = OFF;
    
    
    #endif

    int alarmState = 0;

    while (true) {
        // Se leen los valores del gas detector y del overtemp detector
        // if (HAL_GPIO_ReadPin(GAS_DETECTOR_PORT, GAS_DETECTOR_PIN) || HAL_GPIO_ReadPin(OVERTEMP_DETECTOR_PORT, OVERTEMP_DETECTOR_PIN)) {
        //     alarmState = 1;
        //     HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_SET);  // Encender el LED
        //     printf("Gas Detector: %10d\n", HAL_GPIO_ReadPin(GAS_DETECTOR_PORT, GAS_DETECTOR_PIN));
        //     printf("Overtemp Detector: %10d\n", HAL_GPIO_ReadPin(OVERTEMP_DETECTOR_PORT, OVERTEMP_DETECTOR_PIN));
        //     printf("Alarm State: %10d\n", HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN));
        // }
        #ifdef Cplusplus
        if ( gasDetector == ON ) {
        alarmLed = ON;
        }
            
        if ( gasDetector == OFF ) {
        alarmLed = OFF;
        }

        #endif

        #ifdef C
        printf("Gas Detector: %10d\n", HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0));
        if (HAL_GPIO_ReadPin(GAS_DETECTOR_PORT, GAS_DETECTOR_PIN)) {
            alarmState = 1;
            HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_SET);  // Encender el LED
            
            printf("Overtemp Detector: %10d\n", HAL_GPIO_ReadPin(OVERTEMP_DETECTOR_PORT, OVERTEMP_DETECTOR_PIN));
            printf("Alarm State: %10d\n", HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN));
        }

        // Se leen los valores del gas detector y del overtemp detector
        if (HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN)) {
            alarmState = 0;
            HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_RESET);  // Apagar el LED
            printf("Gas Detector: %10d\n", HAL_GPIO_ReadPin(GAS_DETECTOR_PORT, GAS_DETECTOR_PIN));
            printf("Overtemp Detector: %10d\n", HAL_GPIO_ReadPin(OVERTEMP_DETECTOR_PORT, OVERTEMP_DETECTOR_PIN));
            printf("Alarm State: %10d\n", HAL_GPIO_ReadPin(ALARM_OFF_BUTTON_PORT, ALARM_OFF_BUTTON_PIN));
        
        }
        #endif
    }
}

/*
Ventajas de usar C sobre C++
Es más preciso que inicializar objetos en C++, donde se pueden inicializar un montón de 
parámetros y de métodos que después no se usan.
Esto puede hacerlo más rápido que con C++.

Desventajas de usar C sobre C++
El código es más largo que con C++, porque requiere más detalle.
El código pierde fácil interpretación por ser más largo y complicado.
*/