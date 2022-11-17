#include "test.h"

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
}

void test1_2() {
	if(gpio_input_bit_get(DIP1_GPIO_PORT, DIP1_PIN) == SET) gd_eval_led_on(LED1);
	else if(gpio_input_bit_get(DIP1_GPIO_PORT, DIP1_PIN) == RESET) gd_eval_led_off(LED1);
}

void test1_3() {
	if(gd_eval_key_state_get(USER1_KEY) == RESET) {
		delay_1ms(10); // ����
		if(gd_eval_key_state_get(USER1_KEY) == RESET) {
			gd_eval_led_toggle(LED1);
		}
	}
}

void test2_1() {
	if(gpio_input_bit_get(DIP1_GPIO_PORT, DIP1_PIN) == RESET) { // ���DIP1��0  ֱ��ȫ��Ϩ��
		led_off_immediately();
	} else { // DIP��1
		if(gpio_input_bit_get(DIP2_GPIO_PORT, DIP2_PIN) == SET && gpio_input_bit_get(DIP3_GPIO_PORT, DIP3_PIN) == RESET) led_on_by_order();
		if(gpio_input_bit_get(DIP2_GPIO_PORT, DIP2_PIN) == RESET && gpio_input_bit_get(DIP3_GPIO_PORT, DIP3_PIN) == SET) led_off_by_order();
		if(gpio_input_bit_get(DIP2_GPIO_PORT, DIP2_PIN) == SET && gpio_input_bit_get(DIP3_GPIO_PORT, DIP3_PIN) == SET) led_on_immediately();
	}
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
