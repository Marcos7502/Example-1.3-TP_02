#include "mbed.h"
#include "arm_book_lib.h"

#include "stm32f4xx_hal.h"
#include "PinNames.h"
#include "gpio_api.h"
#define  C 

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

gpio_t gpio_led;
gpio_t gpio_gas_detector;
gpio_t gpio_overtemp_detector;
gpio_t gpio_alarm_off;

int main(void)
{   
    #ifdef C
   
 
    // Configuración del pin del LED como salida
    gpio_led.gpio = ALARM_LED_PORT;  
    gpio_init_out(&gpio_led, PA_3); 

    // Configuración del detector de gas como entrada
    gpio_gas_detector.gpio = GAS_DETECTOR_PORT;
    gpio_init_in(&gpio_gas_detector, PG_9);    
    gpio_mode(&gpio_gas_detector, PullDown);

    // Configuración del detector de sobretemperatura como entrada
    gpio_overtemp_detector.gpio = OVERTEMP_DETECTOR_PORT;
    gpio_init_in(&gpio_overtemp_detector, PG_14); 
    gpio_mode(&gpio_overtemp_detector, PullDown);

    // Configuración del detector de sobretemperatura como entrada
    gpio_alarm_off.gpio = OVERTEMP_DETECTOR_PORT;
    gpio_init_in(&gpio_alarm_off, PF_15); 
    gpio_mode(&gpio_alarm_off, PullDown);

    gpio_write(&gpio_led, 0);
    #endif

    #ifdef Cplusplus

    
    DigitalIn gasDetector(D2);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);

    alarmLed = OFF;
    
    
    #endif

    int alarmState = 0;

    while (true) {
    
        #ifdef Cplusplus
        if ( gasDetector == ON ) {
        alarmLed = ON;
        }
            
        if ( gasDetector == OFF ) {
        alarmLed = OFF;
        }
        printf("%s\n","Hello World");
        #endif

        #ifdef C
        
        if (gpio_read(&gpio_gas_detector)||gpio_read(&gpio_overtemp_detector)) {
            alarmState = 1;
            gpio_write(&gpio_led, 1); // Encender el LED
            printf("Gas Detector: %10d\n", gpio_read(&gpio_gas_detector));
            printf("Overtemp Detector: %10d\n", gpio_read(&gpio_overtemp_detector));
            printf("Alarm State: %10d\n", alarmState);
        }

        // Se leen los valores del gas detector y del overtemp detector
        if (gpio_read(&gpio_alarm_off)) {
            alarmState = 0;
            gpio_write(&gpio_led, 0);  // Apagar el LED
            printf("Gas Detector: %10d\n", gpio_read(&gpio_gas_detector));
            printf("Overtemp Detector: %10d\n", gpio_read(&gpio_overtemp_detector));
            printf("Alarm State: %10d\n", alarmState);
        
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