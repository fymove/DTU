/**************************Copyright (c)****************************
**                            
**                                      
**                                 
**
**--------------File Info-------------------------------------------
** File name:               SPIFlashPin.h
** Last modified Date:      2017-06-30
** Last Version:            0.9.0
** Descriptions:            SPI Flash管脚相关宏定义头文件
**							
**------------------------------------------------------------------
** Created by:              chb
** Created date:            2017-06-30
** Version:                 0.9.0
** Descriptions:            SPI Flash管脚相关宏定义头文件
**							
**------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*******************************************************************/
#ifndef _SPI_FLASH_PIN_H_
#define _SPI_FLASH_PIN_H_

/*******************************************************************
**  SPI flash管脚宏定义
*******************************************************************/
#define FLASH_CS_PORT           GPIOB
#define FLASH_CS_PIN            GPIO_Pin_0

#define FLASH_SCK_PORT          GPIOA
#define FLASH_SCK_PIN           GPIO_Pin_5

#define FLASH_MOSI_PORT         GPIOA
#define FLASH_MOSI_PIN          GPIO_Pin_7

#define FLASH_MISO_PORT         GPIOA
#define FLASH_MISO_PIN          GPIO_Pin_6

#define FLASH_GPIO_RCC          (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB)


/*******************************************************************
**  SPI宏定义
*******************************************************************/
#define FLASH_SPI_IDX           SPI1
#define FLASH_SPI_RCC           RCC_APB2Periph_SPI1


#endif

