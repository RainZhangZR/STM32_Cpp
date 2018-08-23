/**
  ******************************************************************************
  * @file    lyzkgpio.h
  * @author  Rain Zhang
  * @version V1.0
  * @date    12-July-2017
  * @brief   The class of LyzkGpio represents the peripheral of GPIO.
  * 		 The implemented function includes:
  *			 1. initialization;
  *			 2. setting the pin;
  *			 3. resetting the pin (2017.07.12).
  *          4. using the alernative function of the pin (2018.6.04).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 Luoyang Institute of Information 
  * Technology Industries</center></h2>
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LYZK_GPIO_H__
#define __LYZK_GPIO_H__

/* Includes ------------------------------------------------------------------*/
#include "lyzkerror.h"
#include "userdef.h"
#include "stm32f10x_gpio.h"

// Define the MACRO that judge whether the PERIPH and PIN is really existed 
// according to the device used.
#if defined (LYZK_STM32F10X_36PIN)	    // 36-pin devices
#define IS_GPIO_PERIPH (PERIPH) (((PERIPH) == GPIOA) || \
								 ((PERIPH) == GPIOB) || \
								 ((PERIPH) == GPIOD))

#define DOES_GPIO_PIN_EXIST(PERIPH,PIN)	((PERIPH == GPIOA) || \
										((PERIPH == GPIOB) && ((PIN == GPIO_Pin_0) || \
															   (PIN == GPIO_Pin_1) || \
															   (PIN == GPIO_Pin_2) || \
														       (PIN == GPIO_Pin_3) || \
														       (PIN == GPIO_Pin_4) || \
														       (PIN == GPIO_Pin_5) || \
														       (PIN == GPIO_Pin_6) || \
														       (PIN == GPIO_Pin_7))) ||
										((PERIPH == GPIOD) && ((PIN == GPIO_Pin_0) ||
														       (PIN == GPIO_Pin_1))))

#elif defined (LYZK_STM32F10X_48PIN)    // 48-pin devices
#define IS_GPIO_PERIPH (PERIPH) (((PERIPH) == GPIOA) || \
								 ((PERIPH) == GPIOB) || \
								 ((PERIPH) == GPIOC) || \
								 ((PERIPH) == GPIOD))

#define DOES_GPIO_PIN_EXIST(PERIPH,PIN) ((PERIPH == GPIOA) || \
										 (PERIPH == GPIOB) || \
										((PERIPH == GPIOC) && ((PIN == GPIO_Pin_13) || \
														       (PIN == GPIO_Pin_14) || \
														       (PIN == GPIO_Pin_15))) || \
										((PERIPH == GPIOD) && ((PIN == GPIO_Pin_0) || \
														       (PIN == GPIO_Pin_1))))

#elif defined (LYZK_STM32F10X_64PIN)    // 64-pin devices
#define IS_GPIO_PERIPH (PERIPH) (((PERIPH) == GPIOA) || \
								 ((PERIPH) == GPIOB) || \
								 ((PERIPH) == GPIOC) || \
								 ((PERIPH) == GPIOD))

#define DOES_GPIO_PIN_EXIST(PERIPH,PIN)	((PERIPH == GPIOA) || \
										 (PERIPH == GPIOB) || \
										 (PERIPH == GPIOC) || \
										((PERIPH == GPIOD) && ((PIN == GPIO_Pin_0) || \
															   (PIN == GPIO_Pin_1) || \
															   (PIN == GPIO_Pin_2))))

#elif defined (LYZK_STM32F10X_100PIN)   // 100-pin devices
#define IS_GPIO_PERIPH (PERIPH) (((PERIPH) == GPIOA) || \
								 ((PERIPH) == GPIOB) || \
								 ((PERIPH) == GPIOC) || \
								 ((PERIPH) == GPIOD) || \
								 ((PERIPH) == GPIOE)) 

#define DOES_GPIO_PIN_EXIST(PERIPH,PIN)	((PERIPH == GPIOA) || \
										 (PERIPH == GPIOB) || \
										 (PERIPH == GPIOC) || \
										 (PERIPH == GPIOD) || \
										 (PERIPH == GPIOE))

#else                                   // 144-pin devices
#define IS_GPIO_PERIPH (PERIPH) (((PERIPH) == GPIOA) || \
								 ((PERIPH) == GPIOB) || \
								 ((PERIPH) == GPIOC) || \
								 ((PERIPH) == GPIOD) || \
								 ((PERIPH) == GPIOE) || \
								 ((PERIPH) == GPIOF) || \
								 ((PERIPH) == GPIOG)) 

#define DOES_GPIO_PIN_EXIST(PERIPH,PIN)	((PERIPH == GPIOA) || \
										 (PERIPH == GPIOB) || \
										 (PERIPH == GPIOC) || \
										 (PERIPH == GPIOD) || \
										 (PERIPH == GPIOE) || \
										 (PERIPH == GPIOF) || \
										 (PERIPH == GPIOG))
#endif

/* Define the configuration parameters that used to initialize the GPIO pin */
struct GpioConfig
{
	GPIOMode_TypeDef	m_mode;
	GPIOSpeed_TypeDef	m_speed;
};

/* Define the GPIO port and its pin */
class LyzkGpio
{
public:
	LyzkGpio();                             // Constructor
	void SetGPIOx (GPIO_TypeDef* GPIOx);    // Set the GPIO peripheral that used
	void SetPin (uint16_t pin);             // Set the GPIO pin that used
	void ActivateAlternateFunction ();      // Activate the alternate function
                                            // of the GPIO pin

	LYZK_RETURN_CODE Init (GpioConfig cfg);  // Initialization
	LYZK_RETURN_CODE Set();                     // Set the GPIO pin
	LYZK_RETURN_CODE Reset ();                  // Reset the GPIO pin

private:	// Private operations
	
private:	// Private member variables
	GPIO_TypeDef*	m_GPIOx;                // The GPIO peripheral that used
	uint16_t		m_pin;                  // The GPIO pin that used
	bool			m_bAlternateFunction;	// Indicate whether active the alternate 
                                            // function of the GPIO pin
	bool			m_bInitialized;         // Indicate whether the pin is intialized
    GPIOMode_TypeDef    m_mode;             // Current mode
    GPIOSpeed_TypeDef   m_speed;            // Current speed
};

#endif /* __LYZK_GPIO_H__ */
