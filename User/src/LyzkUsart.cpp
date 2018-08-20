/**
  ******************************************************************************
  * @file    lyzkusart.cpp
  * @author  Rain Zhang
  * @version V1.0
  * @date    12-July-2018
  * @brief   The class of LyzkUsart represents the peripheral of USART or UART.
  *			 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 Luoyang Institute of Information 
  * Technology Industries</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "LyzkUsart.h"
#include "stm32f10x_rcc.h"
#include "stdarg.h"
#include "stdio.h"
#include "stdint.h"

#define print_ch(ch) PutChar(ch)

LyzkUsart::LyzkUsart ()
{
    m_bInitialized = false;
}

void LyzkUsart::SetUSART (USART_TypeDef* USARTx)
{
    m_USARTx = USARTx;
}

LYZK_RETURN_CODE LyzkUsart::Init (USART_InitTypeDef* cfg)
{
    LYZK_RETURN_CODE ret = LYZK_FAILED;
    
    if (m_USARTx == USART1)
    {
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
        
        // Set Rx pin
        m_pinRx.SetGPIOx (GPIOA);
        m_pinRx.SetPin (GPIO_Pin_10);
        
        // Set Tx pin
        m_pinTx.SetGPIOx (GPIOA);
        m_pinTx.SetPin (GPIO_Pin_9);
    }
    else if (m_USARTx == USART2)
    {
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART2, ENABLE);
        
        // Set Rx pin
        m_pinRx.SetGPIOx (GPIOA);
        m_pinRx.SetPin (GPIO_Pin_3);
        
        // Set Tx pin
        m_pinTx.SetGPIOx (GPIOA);
        m_pinTx.SetPin (GPIO_Pin_2);
    }
    else
    {
    }
    
    // Set Rx pin's mode and speed
    GpioConfig gpio_cfg;
    gpio_cfg.m_mode     = GPIO_Mode_IN_FLOATING;
    gpio_cfg.m_speed    = GPIO_Speed_50MHz;
    ret = m_pinRx.Init (gpio_cfg);
    if (ret != LYZK_SUCCESSED)
    {
        return ret;
    }
    
    gpio_cfg.m_mode     = GPIO_Mode_AF_PP;
    ret = m_pinTx.Init (gpio_cfg);
    if (ret != LYZK_SUCCESSED)
    {
        return ret;
    }
    
    USART_Init (m_USARTx, cfg);
    
    USART_Cmd (m_USARTx, ENABLE);
    
    m_bInitialized = true;
    
    return LYZK_SUCCESSED;
}

bool LyzkUsart::IsInitialized ()
{
    return m_bInitialized;
}

void LyzkUsart::PutChar (const uint8_t ch)
{
    /* Solve the problem that the first char will be missed when you first
     * output messages. */
    //USART_ClearFlag (m_USARTx, USART_FLAG_TC);
    
    USART_SendData (m_USARTx, (uint16_t) ch);
    
    /* Waiting till the transmission completed */
    while (USART_GetFlagStatus (m_USARTx, USART_FLAG_TXE) == RESET);
}

uint8_t LyzkUsart::GetChar ()
{
    /* Waiting till the Received Data Register is not empty */
    while (USART_GetFlagStatus (m_USARTx, USART_FLAG_RXNE) == RESET);
    
    return ((uint8_t) USART_ReceiveData (m_USARTx));
}

int LyzkUsart::Printf (const char* strFmt, ...)
{
#define MAX_SIZE 400
    /* The number of charactersthat printed */
    int     iCnt = 0;
    
    /* The result string converted using snprintf () function in standard   *
     * library "stdio.h". */
    char    strRslt [MAX_SIZE] = {0};

    char    strTmp [17] = {0};
    int     iTmp;
    int     i;

    /* Arguments */
    uint64_t    varUint;
    int64_t     varInt;
    double      varDbl;
    char*       varStr;

    /* Declare a variable that will be refer to each argument in turn.      *
     * Type va_list is defined in "stdarg.h" file.                          */
    va_list varList;
    
    /* Macro va_start initializes "varList" to point to the first unnamed   *
     * argument. It must be called once before "varList" is used.           */
    va_start (varList, strFmt);

    while (*strFmt)
    {
        /* Begin to extract formatted string */
        if (*strFmt == '%')
        {
            i = 0;
            strTmp [i] = *strFmt;

            strFmt++;
            i++;
            
            /* Extracting formatted string ended */
            while (*strFmt  && (*strFmt != '%') && (*strFmt != 'c') 
                            && (*strFmt != 's') && (*strFmt != 'd')
                            && (*strFmt != 'i') && (*strFmt != 'o')
                            && (*strFmt != 'x') && (*strFmt != 'X')
                            && (*strFmt != 'u') && (*strFmt != 'f')
                            && (*strFmt != 'F') && (*strFmt != 'e')
                            && (*strFmt != 'E') && (*strFmt != 'g')
                            && (*strFmt != 'G') && (*strFmt != 'n')
                            && (*strFmt != 'p'))
            {
                strTmp [i] = *strFmt;
                strFmt++;
                i++;
            }

            strTmp [i] = *strFmt;

            switch (*strFmt)
            {
            /* Only to print character of '%' */
            case '%':
                print_ch ('%');
                iCnt++;
                strFmt++;
                break;
            
            /* Print string of string-type argument */
            case 's':
                varStr = va_arg (varList, char*);

                iTmp = snprintf (strRslt, MAX_SIZE, strTmp, varStr);
                
                for (i = 0; i < iTmp; i++)
                {
                    print_ch (strRslt [i]);
                    iCnt++;
                }

                strFmt++;
                break;

            /* Print string converted from integer-type argument */
            case 'c':
            case 'd':
            case 'i':
                varInt = va_arg (varList, int64_t);

                iTmp = snprintf (strRslt, 23, strTmp, varInt);

                for (i = 0; i < iTmp; i++)
                {
                    print_ch (strRslt [i]);
                    iCnt++;
                }

                strFmt++;
                break;

            /* Print string converted from unsinged-integer-type argument */
            case 'o':
            case 'x':
            case 'X':
            case 'u':
                varUint = va_arg (varList, uint64_t);

                iTmp = snprintf (strRslt, 23, strTmp, varUint);

                for (i = 0; i < iTmp; i++)
                {
                    print_ch (strRslt [i]);
                    iCnt++;
                }

                strFmt++;
                break;

            /* Print string converted from float-type argument */
            case 'f':
            case 'F':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
            varDbl = va_arg (varList, double);

            iTmp = snprintf (strRslt, MAX_SIZE, strTmp, varDbl);

            for (i = 0; i < iTmp; i++)
            {
                print_ch (strRslt [i]);
                iCnt++;
            }

                strFmt++;
                break;
            }
        }
        else
        {
            print_ch (*strFmt++);
            iCnt++;
        }
    }

    /* va_end does whatever clearup is necessary. It must be called before  *
     * the program returns.                                                 */
    va_end (varList);

    return iCnt;
}
