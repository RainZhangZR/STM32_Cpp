
/* Includes ------------------------------------------------------------------*/
#include "lyzkgpio.h"
#include "stm32f10x_rcc.h"

LyzkGpio::LyzkGpio ()
{
	m_bAlternateFunction 	= false;
	m_bInitialized 			= false;
}

void LyzkGpio::SetGPIOx (GPIO_TypeDef* GPIOx)
{
	m_GPIOx	= GPIOx;
}

void LyzkGpio::SetPin (uint16_t pin)
{
	m_pin	= pin;
}

void LyzkGpio::ActivateAlternateFunction ()
{
	m_bAlternateFunction = true;
}

LYZK_RETURN_CODE LyzkGpio::Init (GpioConfig cfg)
{
	/* If m_GPIOx, m_pin, m_mode, m_speed is undefined, returned false */
	if (!IS_GPIO_MODE (cfg.m_mode))
		return LYZK_GPIO_MODE_ERR;
	
	if (!IS_GPIO_SPEED (cfg.m_speed))
		return LYZK_GPIO_SPEED_ERR;
	
	if (!DOES_GPIO_PIN_EXIST (m_GPIOx, m_pin))
		return LYZK_GPIO_ERR;
	
	if (m_GPIOx == GPIOA) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
	} 
    else if (m_GPIOx == GPIOB) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	} 
    else if (m_GPIOx == GPIOC) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	} 
    else if (m_GPIOx == GPIOD) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOD, ENABLE);
	} 
    else if (m_GPIOx == GPIOE) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOE, ENABLE);
	} 
    else if (m_GPIOx == GPIOF) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOF, ENABLE);
	} 
    else if (m_GPIOx == GPIOG) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOG, ENABLE);
	} 
    else 
    {
		return LYZK_GPIO_ERR;
	}
	
	if (m_bAlternateFunction) 
    {
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);
	}	
	
	GPIO_InitTypeDef initStruct;	
	initStruct.GPIO_Pin		= m_pin;
	initStruct.GPIO_Mode	= cfg.m_mode;
	initStruct.GPIO_Speed	= cfg.m_speed;
	GPIO_Init (m_GPIOx, &initStruct);
	
	m_bInitialized = true;
	
	return LYZK_SUCCESSED;
}

LYZK_RETURN_CODE LyzkGpio::Set ()
{
	if (!m_bInitialized)
    {
		return LYZK_GPIO_INIT_ERR;
	}
		
	GPIO_SetBits (m_GPIOx, m_pin);
	
	return LYZK_SUCCESSED;
}

LYZK_RETURN_CODE LyzkGpio::Reset ()
{
	if (!m_bInitialized)
    {
		return LYZK_GPIO_INIT_ERR;
	}
		
	GPIO_ResetBits (m_GPIOx, m_pin);
	
	return LYZK_SUCCESSED;
}
