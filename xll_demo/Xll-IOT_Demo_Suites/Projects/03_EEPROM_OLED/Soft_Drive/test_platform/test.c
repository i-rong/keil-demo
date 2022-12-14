#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "oled.h"
#include "at24cxx.h"
#include "i2c.h"
#include "bmp.h"
#include "test.h"
#include "systick.h"
#include <stdlib.h>

/* ϵͳ��ʼ�� */
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

uint8_t tab[] = "2022.11.26+yao";												//�������ں�������д
const uint8_t BUFFER_SIZE = sizeof(tab) / sizeof(uint8_t);
uint8_t ReadE2P[BUFFER_SIZE];
uint8_t res1 = '=';

uint8_t i2c_24c02_test(void) {
	uint8_t i;
	eeprom_buffer_write(tab, EEPROM_FIRST_PAGE, BUFFER_SIZE); // д��EEPROAM
	eeprom_buffer_read(ReadE2P, EEPROM_FIRST_PAGE, BUFFER_SIZE); // ��EEPROAM�ж���
	OLED_ShowString(0, 0, tab);
	OLED_ShowString(0, 4, ReadE2P);
	for(i = 0; i < BUFFER_SIZE; i++) 
		if(tab[i] != ReadE2P[i]) 
			return 0;
	return 1;
}

/*����ʵ��*/
void test1(void) {
	OLED_Clear();
	while(1) {
		if (i2c_24c02_test()) {
			gd_eval_led_on(LED1);
			OLED_ShowChar(0, 2, res1);		// ��ʾ=
			Uart0Printf("= \r\n");
		}
		else {
			gd_eval_led_on(LED2);
			OLED_ShowCHinese(0, 2, 0);		// ��ʾ��
			Uart0Printf("�� \r\n");
		}
		while(1){ }	
	}
}


/*����ʵ��*/
void test2() {
	uint8_t arr[] = {0x00, 0x01, 0x02, 0x03};
	const uint8_t ARR_SIZE = sizeof(arr) / sizeof(uint8_t);
	eeprom_buffer_write(arr, EEPROM_FIRST_PAGE, ARR_SIZE); // ��EEPRAOM�д�����
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

uint8_t is_match(uint8_t a[], uint8_t b[]) { // �ж����ַ����Ƿ����
	uint8_t i;
	for(i = 0; i < 3; i++) {
		if(a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

/*��չʵ��*/
void test3() {
	uint8_t chars[5][3] = {"abc", "bcd", "cde", "def", "efg"};
	uint8_t zero[2] = "\0";
	uint8_t i;
	uint8_t cnt = 5;
	uint8_t congra_string[] = "Congratulations!";
	uint8_t bingo_string[] = "Bingo!";
	uint8_t false_string[] = "False!";
	uint8_t left;
	uint8_t left_string[4];
	uint8_t right;
	uint8_t right_string[4];
	
	for(i = 0; i < 5; i++) { // �����д��
		eeprom_buffer_write(chars[i], EEPROM_FIRST_PAGE + i * 3, 3);
	}
	
	while(cnt) {
		left = rand() % 5;
		eeprom_buffer_read(left_string, EEPROM_FIRST_PAGE + left * 3, 3);
		if(left_string[0] == 0) continue;
		left_string[3] = 0;
		OLED_ShowString(0, 0, left_string); // �����д��
		for(i = 0; i < 5; i++) {
			right = rand() % 5;
			eeprom_buffer_read(right_string, EEPROM_FIRST_PAGE + right * 3, 3); // ���ѡȡһ��
			if(right_string[0] == 0) continue;
			right_string[3] = 0;
			OLED_ShowString(104, 0, right_string);
			if(is_match(left_string, right_string)) { // ���ƥ��  ֱ���˳�forѭ��
				cnt--;
				eeprom_buffer_write(zero, EEPROM_FIRST_PAGE + left * 3, 3);
				OLED_ShowString(0, 6, bingo_string);
				delay_1ms(1000);
				break; 
			} else { // �����ƥ��
				OLED_ShowString(0, 6, false_string);
				delay_1ms(1000);
			}
		}
	}
	OLED_Clear();
	OLED_ShowString(0, 6, congra_string);
	while(1) ;
}