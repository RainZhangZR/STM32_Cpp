/**
  ******************************************************************************
  * @file    lyzkusart.h
  * @author  Rain Zhang
  * @version V1.0
  * @date    12-July-2018
  * @brief   The class of LyzkUsart represents the peripheral of USART or UART.
  * 		 The implemented function includes:
  *			 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 Luoyang Institute of Information 
  * Technology Industries</center></h2>
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __LYZK_USART_H__
#define __LYZK_USART_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"
#include "LyzkGpio.h"

/* Define the MACRO that judge whether the PERIPH is a valid USART according  *
 * to the STM32 device used.                                                  *
 * STM32 Low-density devices and STM32 Low-density Value Line devices         */
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_LD)
  #define IS_USART_PERIPHERAL(PERIPH) (((PERIPH) == USART1) || \
									   ((PERIPH) == USART2))

/* STM32 Medium-density Value Line devices                                    */
#elif defined (STM32F10X_MD_VL)
  #define IS_USART_PERIPHERAL(PERIPH) (((PERIPH) == USART1) || \
									   ((PERIPH) == USART2) || \
									   ((PERIPH) == USART3))

/* STM32 Medium-density devices                                               */
#elif defined (STM32F10X_MD)
  #if defined (LYZK_STM32F10X_36PIN)    /* 36-pin package devices */
    #define IS_USART_PERIPHERAL(PERIPH) (((PERIPH) == USART1) || \
									     ((PERIPH) == USART2))
  #else                 /* 48-pin, 64-pin, 100-pin package devices */
    #define IS_USART_PERIPHERAL(PERIPH) (((PERIPH) == USART1) || \
                                         ((PERIPH) == USART2) || \
                                         ((PERIPH) == USART3))
  #endif /* LYZK_STM32F10X_36PIN */

/* Others (include STM32 High-density, High-density Value Line, XL-density,   *
 * and Connectivity Line devices).                                            */
#else
  #define IS_USART_PERIPHERAL(PERIPH) (((PERIPH) == USART1) || \
									   ((PERIPH) == USART2) || \
									   ((PERIPH) == USART3) || \
									   ((PERIPH) == UART4)  || \
									   ((PERIPH) == UART5))

#endif /* IS_USART_PERIPHERAL (PERIPH) */

class LyzkUsart
{
public:
    LyzkUsart ();

    void SetUSART (USART_TypeDef* USARTx);

    LYZK_RETURN_CODE    Init (USART_InitTypeDef* cfg);
    bool                IsInitialized ();

    void    PutChar (const uint8_t ch);
    uint8_t GetChar ();
    
    int Printf (const char *strFmt, ...);

private:
    USART_TypeDef*          m_USARTx;
    bool                    m_bInitialized;
    
    LyzkGpio                m_pinRx;
    LyzkGpio                m_pinTx;
};

#endif /* __LYZK_USART_H__ */
