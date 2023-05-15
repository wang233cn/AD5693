#include "AD5693.h"
#include "i2c.h"
#include "string.h"

uint8_t AD5693_GAIN;

void AD5693_WriteData(uint8_t *dataarray,uint16_t size){
	HAL_I2C_Master_Transmit(&hi2c3,AD5693_ADDR,dataarray,size,HAL_MAX_DELAY);
}

void AD5693_Update(void){
#ifdef AD5693_HWLDAC
	AD5693_LDAC_H;
	//Delay_us(10);
	AD5693_LDAC_L;
	//Delay_us(10);
	AD5693_LDAC_H;
#else
	uint32_t data = 0x200000;
	AD5693_WriteData(&data,3);
#endif
}

void AD5693_Init(uint8_t GAIN,uint8_t REF,uint8_t MODE){
#ifdef AD5693_HWRESET
   AD5693_RESET_L;
	 HAL_Delay(9);
   AD5693_RESET_H;
#endif
	
#ifdef AD5693_SOFTRESET
#endif
	AD5693_GAIN = GAIN;
	uint8_t controlbit = MODE<<5 | REF<<4 | (GAIN-1) <<3;
	uint8_t data[3] = {0x40,controlbit,0x00};
	AD5693_WriteData(data,3);

}


void AD5693_WriteVol(float voltage){
	uint16_t Digitaldata = (voltage/(AD5693_GAIN*AD5693_VREF))*65536.0;
  
#ifdef AD5693_ASYNCUPDATE 
	uint8_t data[3] = {0x10,Digitaldata>>8,Digitaldata};
	AD5693_WriteData(data,3);
	AD5693_Update();
#endif

#ifdef AD5693_SYNCUPDATE
	uint8_t data[3] = {0x30,Digitaldata>>8,Digitaldata};
	AD5693_WriteData(data,3);
	AD5693_LDAC_L;
#endif

}

