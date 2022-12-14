#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "74HC595_LED.h"
#include "timer.h"
#include "diwen.h"
#include "systick.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include "user.h"

/*
00000000
11111110
10010010
11111110
10010010
11111110
00000000
00000000  // 田
*/ 
uint8_t row_clear[]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};		      //8*8LED清屏
uint8_t cal_clear[]= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t row1[]     = {0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t core1[]    = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};				  /*田字第一笔画*/
uint8_t row2[]     = {0x3e,0x02,0x02,0x02,0x02,0x02,0x3e,0x00};
uint8_t core2[]    = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; 				/*田字第二笔画*/
uint8_t row3[]     = {0x3e,0x0a,0x0a,0x0a,0x0a,0x0a,0x3e,0x00};
uint8_t core3[]    = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; 				/*田字第三笔画*/
uint8_t row4[]     = {0x3e,0x0a,0x0a,0x3e,0x0a,0x0a,0x3e,0x00};
uint8_t core4[]    = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; 				/*田字第四笔画*/
uint8_t row5[]     = {0x3e,0x2a,0x2a,0x3e,0x2a,0x2a,0x3e,0x00};
uint8_t core5[]    = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; 				/*田字第五笔画*/



//系统初始化（systick、定时器、GD_XLL、HC595、DIWIN ）
void system_init(void) {
	systick_config();
	TIM3_Init(29999, 9999);
	gd_XII_systeminit();
	HC595_GPIO_Config();
	diwen_init();
	usart0Init(EVAL_COM0, 115200U);
}

//实验一 LED写汉字
void test1() {
	uint8_t i;
	if(tim3_count == 0) {
		for(i = 0; i < 8; i++) {
			HC595_Send_Byte(row1[i]);
			HC595_Send_Byte(core1[i]);
			HC595_CS();
		}
	}
	if(tim3_count == 1) {
		for(i = 0; i < 8; i++) {
			HC595_Send_Byte(row2[i]);
			HC595_Send_Byte(core2[i]);
			HC595_CS();
		}
	}
	if(tim3_count == 2) {
		for(i = 0; i < 8; i++) {
			HC595_Send_Byte(row3[i]);
			HC595_Send_Byte(core3[i]);
			HC595_CS();
		}
	}
	if(tim3_count == 3) {
		for(i = 0; i < 8; i++) {
			HC595_Send_Byte(row4[i]);
			HC595_Send_Byte(core4[i]);
			HC595_CS();
		}
	}
	if(tim3_count == 4) {
		for(i = 0; i < 8; i++) {
			HC595_Send_Byte(row5[i]);
			HC595_Send_Byte(core5[i]);
			HC595_CS();
		}
	}
	if(tim3_count == 5) {
		for(i = 0; i < 8; i++) {
			HC595_Send_Byte(row_clear[i]);
			HC595_Send_Byte(cal_clear[i]);
			HC595_CS();
		}
	}
	if(tim3_count == 6) tim3_count = 0;
}

//实验二 串口触摸屏控制LED

void test2(void) {
	while(uart5_rx_buffer[5] == 0x1A) {
		delay_1ms(100);
		while(uart5_rx_buffer[8] == 0x01) {
			gd_eval_led_on(LED1);
		}
		while(uart5_rx_buffer[8] == 0x00) {
			gd_eval_led_off(LED1);
		}
	}
	while(uart5_rx_buffer[5] == 0x11) {
		delay_1ms(100);
		while(uart5_rx_buffer[8] == 0x01) {
				gd_eval_led_on(LED2);
		}
		while(uart5_rx_buffer[8] == 0x00) {
			gd_eval_led_off(LED2);
		}
	}
	
	while(uart5_rx_buffer[5] == 0x12) {
		delay_1ms(100);
		while(uart5_rx_buffer[8] == 0x01) {
			gd_eval_led_on(LED3);
		}
		while(uart5_rx_buffer[8] == 0x00) {
			gd_eval_led_off(LED3);
		}
	}
	
	while(uart5_rx_buffer[5] == 0x13) {
		delay_1ms(100);
		while(uart5_rx_buffer[8] == 0x01) {
			gd_eval_led_on(LED4);
		}
		while(uart5_rx_buffer[8] == 0x00) {
			gd_eval_led_off(LED4);
		}
	}
	
	while(uart5_rx_buffer[5] == 0x14) {
		delay_1ms(100);
		while(uart5_rx_buffer[8] == 0x01) {
			gd_eval_led_on(LED5);
		}
		while(uart5_rx_buffer[8] == 0x00) {
			gd_eval_led_off(LED5);
		}
	}
}


