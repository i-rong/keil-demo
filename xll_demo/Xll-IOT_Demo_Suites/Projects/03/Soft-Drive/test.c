#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "oled.h"
#include "I2C.h"
#include "test.h"
#include "systick.h"
#include <stdlib.h>
#include "user.h"

void systeminit() {
	systick_config();
	gd_XII_systeminit();
	dipinit();
	OLED_Gpio_Init();
	OLED_Init();
}

char tab[] = "2022-11-21 huaiyuyao 22920202204632\0";
const  uint16_t buf_size = sizeof(tab) / sizeof(char);
uint16_t i2c_buffer_write[buf_size];
uint16_t i2c_buffer_read[buf_size];

//对写入EEPROM的数据进行核对
uint8_t i2c_24c02_test(void) {
		uint16_t i;
		for(i = 0; tab[i]!='\0' ;i++) { 
				i2c_buffer_write[i] = tab[i];			
		}
		OLED_ShowString(0,0,tab);								//将tab字符串显示到OLED中
}