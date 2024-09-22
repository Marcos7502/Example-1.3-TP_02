// Configure C or C++ functionality usage
// #define CPLUSPLUS  // Uncomment ONLY ONE to chose C++ or C 
#define C

#ifndef C
#define CPLUSPLUS
#endif

#ifndef CPLUSPLUS
#define C
#endif


#ifdef C

// Alarm led GPIO address
#define ALARM_LED_PIN       GPIO_PIN_0
#define ALARM_LED_GPIO_PORT GPIOB

// Gas detector GPIO address
#define GAS_DETECTOR_PIN       GPIO_PIN_15
#define GAS_DETECTOR_GPIO_PORT GPIOF

// Overtemperature detector GPIO address
#define OVERTEMPERATURE_DETECTOR_PIN       GPIO_PIN_13
#define OVERTEMPERATURE_DETECTOR_GPIO_PORT GPIOE

// Alarm off button GPIO address
#define ALARM_OFF_BUTTON_PIN       GPIO_PIN_13
#define ALARM_OFF_BUTTON_GPIO_PORT GPIOC

#endif
