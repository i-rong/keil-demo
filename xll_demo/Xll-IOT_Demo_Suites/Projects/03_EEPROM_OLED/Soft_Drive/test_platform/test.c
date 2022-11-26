#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "oled.h"
#include "at24cxx.h"
#include "i2c.h"
#include "bmp.h"
#include "test.h"
#include "systick.h"
#include <stdlib.h>

/* 系统初始化 */
void systemInit(void) {
	systick_config();
	gd_XII_systeminit();
	OLED_Gpio_Init();
	OLED_Init();
	i2c_gpio_config();
	i2c_config();
	i2c_eeprom_init();
	usart0Init(EVAL_COM0, 115200U);
}

uint8_t tab[] = "2022.01.01+name";												//定义日期和姓名缩写
const uint8_t BUFFER_SIZE = sizeof(tab) / sizeof(uint8_t);
uint8_t ReadE2P[BUFFER_SIZE];
uint8_t res1 = '=';

uint8_t i2c_24c02_test(void) {
	uint8_t i;
	eeprom_buffer_write(tab, EEPROAM_FIRST_PAGE, BUFFER_SIZE); // 写进EEPROAM
	eeprom_buffer_read(ReadE2P, EEPROAM_FIRST_PAGE, BUFFER_SIZE); // 从EEPROAM中读出
	OLED_ShowString(0, 0, tab);
	OLED_ShowString(0, 4, ReadE2P);
	for(i = 0; i < BUFFER_SIZE; i++) 
		if(tab[i] != ReadE2P[i]) 
			return 0;
	return 1;
}

/*基础实验*/
void test1(void) {
	OLED_Clear();
	while(1) {
		if (i2c_24c02_test()) {
			gd_eval_led_on(LED1);
			OLED_ShowChar(0, 2, res1);		// 显示=
			Uart0Printf("= \r\n");
		}
		else {
			gd_eval_led_on(LED2);
			OLED_ShowCHinese(0, 2, 0);		// 显示≠
			Uart0Printf("≠ \r\n");
		}
		while(1){ }	
	}
}


/*进阶实验*/
void test2() {
	uint8_t arr[] = {0x00, 0x01, 0x02, 0x03};
	const uint8_t ARR_SIZE = sizeof(arr) / sizeof(uint8_t);
	eeprom_buffer_write(arr, EEPROAM_FIRST_PAGE, ARR_SIZE); // 往EEPRAOM中存数字
	while(1) {
		OLED_DrawBMP(0, 0, 127, 7, BMP1);
		delay_1ms(3000);
		OLED_Clear();
		OLED_DrawBMP(0, 0, 127, 7, BMP2);
		delay_1ms(3000);
		OLED_Clear();
		OLED_DrawBMP(0, 0, 127, 7, img1);
		delay_1ms(3000);
		OLED_Clear();
		OLED_DrawBMP(0, 0, 127, 7, img2);
		delay_1ms(3000);
		OLED_Clear();
	}
} 

/*扩展实验*/
void test3() {
	
}
