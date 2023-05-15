#ifndef __AD5693_H
#define __AD5693_H


#include "main.h"

#define AD5693_ADDR 0x4C << 1 


#define AD5693_ASYNCUPDATE 
//#define AD5693_SYNCUPDATE 
#define AD5693_HWLDAC
#define AD5693_HWRESET

#define AD5693_VREF 2.50

#define AD5693_GAIN_1 1
#define AD5693_GAIN_2 2

#define AD5693_MODE_Normal 0x00
#define AD5693_MODE_PD1K   0x01
#define AD5693_MODE_PD100K 0x02
#define AD5693_MODE_PDTS   0x03

#define AD5693_ENABLE_REF  0x00
#define AD5693_DISABLE_REF 0x01

#ifdef AD5693_HWLDAC
#define AD5693_LDAC_H   HAL_GPIO_WritePin(GPIOA,DAC_LDAC_Pin, GPIO_PIN_SET)
#define AD5693_LDAC_L   HAL_GPIO_WritePin(GPIOA,DAC_LDAC_Pin, GPIO_PIN_RESET)
#endif

#ifdef AD5693_HWRESET
#define AD5693_RESET_H   HAL_GPIO_WritePin(GPIOB,DAC_RESET_Pin, GPIO_PIN_SET)
#define AD5693_RESET_L   HAL_GPIO_WritePin(GPIOB,DAC_RESET_Pin, GPIO_PIN_RESET)
#endif

void AD5693_Control(uint8_t GAIN,uint8_t InternalREF,uint8_t MODE);
void AD5693_WriteVol(float voltage);
void AD5693_Init(uint8_t GAIN,uint8_t REF,uint8_t MODE);
//void AD5696_PowerDown(uint8_t MODE);
	

#endif