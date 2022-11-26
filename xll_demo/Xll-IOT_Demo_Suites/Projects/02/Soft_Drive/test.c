#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

void systeminit() {
	systick_config();
	gd_XII_systeminit(); /*init 8 led*/
	dipinit(); /*init 8 dial switch*/
	gd_eval_key_init(USER1_KEY, KEY_MODE_GPIO); /*init key1 to io mode*/
	gd_eval_key_init(USER2_KEY, KEY_MODE_EXTI); /*init key2 to interrupt mode*/
	gd_eval_key_init(USER3_KEY, KEY_MODE_EXTI); /*init key3 to interrupt mode*/
	gd_eval_key_init(USER4_KEY, KEY_MODE_GPIO); /*init key4 to io mode*/
	usart0Init(EVAL_COM0, 115200u);
	//init_4g(); /*init 4g*/
}

void test1_1() {
	gd_eval_led_on(LED1);
	gd_eval_led_on(LED2);
	gd_eval_led_on(LED3);
}

void test1_2() {
	if(gpio_input_bit_get(DIP1_GPIO_PORT, DIP1_PIN) == SET) gd_eval_led_on(LED1);
	else if(gpio_input_bit_get(DIP1_GPIO_PORT, DIP1_PIN) == RESET) gd_eval_led_off(LED1);
}

void test1_3() {
	while(1) {
		if(gd_eval_key_state_get(USER1_KEY) == RESET) {
			delay_1ms(100); // 防抖
			if(gd_eval_key_state_get(USER1_KEY) == RESET) {
				gd_eval_led_toggle(LED1);
			}
		}
		if(gd_eval_key_state_get(USER4_KEY) == RESET) {
			delay_1ms(100); // 防抖
			if(gd_eval_key_state_get(USER4_KEY) == RESET) {
				gd_eval_led_toggle(LED4);
			}
		}
	}
}

void test2_1() {
	if(gpio_input_bit_get(DIP1_GPIO_PORT, DIP1_PIN) == RESET) { // 如果DIP1是0  直接全部熄灭
		led_off_immediately();
	} else { // DIP是1
		if(gpio_input_bit_get(DIP2_GPIO_PORT, DIP2_PIN) == SET && gpio_input_bit_get(DIP3_GPIO_PORT, DIP3_PIN) == RESET) led_on_by_order();
		if(gpio_input_bit_get(DIP2_GPIO_PORT, DIP2_PIN) == RESET && gpio_input_bit_get(DIP3_GPIO_PORT, DIP3_PIN) == SET) led_off_by_order();
		if(gpio_input_bit_get(DIP2_GPIO_PORT, DIP2_PIN) == SET && gpio_input_bit_get(DIP3_GPIO_PORT, DIP3_PIN) == SET) led_on_immediately();
	}
}

void test2_2() {
	/*使用按键开关控制LED灯的亮灭*/
	uint8_t lightKey1Cnt = 0;
	uint8_t lightKey4Cnt = 0;
	
	
	while(1) {
		if(gd_eval_key_state_get(USER1_KEY) == RESET) {
			delay_1ms(50);
			if(gd_eval_key_state_get(USER1_KEY) == RESET) {
				if(gd_eval_key_state_get(USER1_KEY) == RESET && lightKey4Cnt == 0 && lightKey1Cnt == 0) {
					lightKey1Cnt = 1;
				}
				if(gd_eval_key_state_get(USER1_KEY) == RESET && lightKey4Cnt == 2) {
					lightKey1Cnt = 2;
				}
				delay_1ms(50);
			}	
		}
	
		if(gd_eval_key_state_get(USER4_KEY) == RESET) {
			delay_1ms(50);
			if(gd_eval_key_state_get(USER4_KEY) == RESET) {
				while(gd_eval_key_state_get(USER4_KEY) == RESET && lightKey1Cnt == 1 && lightKey4Cnt == 1) {
					led_on_immediately();
				}
				if(lightKey4Cnt == 1) lightKey4Cnt = 2;
				if(gd_eval_key_state_get(USER4_KEY) == RESET && lightKey4Cnt == 0) lightKey4Cnt = 1; // first
			}	
		}
		
		if(lightKey1Cnt == 1 && lightKey4Cnt == 0) {
			led_on_immediately();
		} else if(lightKey1Cnt == 1 && lightKey4Cnt == 1) {
			flashLED2_8();
		} else if(lightKey1Cnt == 1 && lightKey4Cnt == 2) {
			led_off_immediately();
			gd_eval_led_on(LED1);
		} else if(lightKey1Cnt == 2 && lightKey4Cnt == 2) {
			led_off_immediately();
			lightKey1Cnt = lightKey4Cnt = 0;
		}
	}
}
// 使用按键2中断控制LED3亮
void EXTI3_IRQHandler() {
	if(exti_interrupt_flag_get(USER2_KEY_EXTI_LINE) != RESET) {
		gd_eval_led_on(LED3);
			exti_interrupt_flag_clear(USER2_KEY_EXTI_LINE);
	}
}

void EXTI4_IRQHandler() {
	if(exti_interrupt_flag_get(USER3_KEY_EXTI_LINE) != RESET) {
		gd_eval_led_off(LED3);
			exti_interrupt_flag_clear(USER3_KEY_EXTI_LINE);
	}
}
void flashLED2_8() {
	gd_eval_led_on(LED2);
	delay_1ms(50);
	gd_eval_led_on(LED3);
	delay_1ms(50);
	gd_eval_led_on(LED4);
	delay_1ms(50);
	gd_eval_led_on(LED5);
	delay_1ms(50);
	gd_eval_led_on(LED6);
	delay_1ms(50);
	gd_eval_led_on(LED7);
	delay_1ms(50);
	gd_eval_led_on(LED8);
	delay_1ms(50);
	gd_eval_led_off(LED2);
	delay_1ms(50);
	gd_eval_led_off(LED3);
	delay_1ms(50);
	gd_eval_led_off(LED4);
	delay_1ms(50);
	gd_eval_led_off(LED5);
	delay_1ms(50);
	gd_eval_led_off(LED6);
	delay_1ms(50);
	gd_eval_led_off(LED7);
	delay_1ms(50);
	gd_eval_led_off(LED8);
	delay_1ms(50);
}

void resetLightKeyCnt() {
	uint8_t lightKey1Cnt = 0;
	uint8_t lightKey4Cnt = 0;
}

void led_on_by_order() {
	gd_eval_led_on(LED1);
	delay_1ms(100);
	gd_eval_led_on(LED2);
	delay_1ms(100);
	gd_eval_led_on(LED3);
	delay_1ms(100);
	gd_eval_led_on(LED4);
	delay_1ms(100);
	gd_eval_led_on(LED5);
	delay_1ms(100);
	gd_eval_led_on(LED6);
	delay_1ms(100);
	gd_eval_led_on(LED7);
	delay_1ms(100);
	gd_eval_led_on(LED8);
	delay_1ms(100);
}

void led_off_by_order() {
	gd_eval_led_off(LED1);
	delay_1ms(100);
	gd_eval_led_off(LED2);
	delay_1ms(100);
	gd_eval_led_off(LED3);
	delay_1ms(100);
	gd_eval_led_off(LED4);
	delay_1ms(100);
	gd_eval_led_off(LED5);
	delay_1ms(100);
	gd_eval_led_off(LED6);
	delay_1ms(100);
	gd_eval_led_off(LED7);
	delay_1ms(100);
	gd_eval_led_off(LED8);
	delay_1ms(100);
}

void led_on_immediately() {
	gd_eval_led_on(LED1);
	gd_eval_led_on(LED2);
	gd_eval_led_on(LED3);
	gd_eval_led_on(LED4);
	gd_eval_led_on(LED5);
	gd_eval_led_on(LED6);
	gd_eval_led_on(LED7);
	gd_eval_led_on(LED8);
}

void led_off_immediately() {
	gd_eval_led_off(LED1);
	gd_eval_led_off(LED2);
	gd_eval_led_off(LED3);
	gd_eval_led_off(LED4);
	gd_eval_led_off(LED5);
	gd_eval_led_off(LED6);
	gd_eval_led_off(LED7);
	gd_eval_led_off(LED8);
}
