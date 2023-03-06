#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "pwm.h"
#include "test.h"
#include "systick.h"
#include "oled.h"
#include "user.h"

volatile uint16_t tim3_count;
volatile uint8_t motor_speed = 3;
volatile uint8_t mode_select;
char dir[] = "xxxxxxxxxx"; // �����ת����
char pos[] = "Positive";
char rev[] = "Reverse";
char sto[] = "stop";

typedef enum {
	forward = 0,
	reverse = 1,
	stop = 2
}motor_mode;

//��ʼ�� ʱ�ӡ�xll�����gpio��oled������
void system_init(void)
{
	usart0Init(EVAL_COM0, 115200U);
	USART2_Init(115200U);
	systick_config();
	gd_XII_systeminit();
	motor_gpio_config();
	TIM3_Init(500, 500);
	OLED_Gpio_Init(); // OLED��ʼ��
	OLED_Init();
	gd_eval_key_init(USER1_KEY, KEY_MODE_EXTI);
	gd_eval_key_init(USER2_KEY, KEY_MODE_EXTI);
}

//���� ���ת��
void test1(void)
{
	uint8_t speed = 5;
	gpio_bit_reset(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_reset(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_reset(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_reset(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
}

void motor_fanz(uint8_t speed) {
	gpio_bit_reset(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_reset(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_reset(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_reset(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
}

void motor_zhez(uint8_t speed) {
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_reset(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_reset(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_set(GPIOC, GPIO_PIN_6);
	gpio_bit_reset(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
	gpio_bit_reset(GPIOC, GPIO_PIN_6);
	gpio_bit_set(GPIOC, GPIO_PIN_7);
	gpio_bit_set(GPIOC, GPIO_PIN_8);
	gpio_bit_set(GPIOC, GPIO_PIN_9);
	delay_1ms(speed);
}

//���� �������Ƶ��ת�١�ת��
void test2() {
	uint16_t i;
	if(gpio_input_bit_get(DIP4_GPIO_PORT, DIP4_PIN) == RESET) { // ���뿪�عر� ���õ����ת�ٺͷ���
		char str[4];
		sprintf(str, "%d.00", motor_speed); // ��ȫ��motor_speedת��Ϊ�ַ���
		OLED_ShowString(0, 0, "speed:");
		OLED_ShowString(64, 0, str);
		
		if(mode_select == forward) { // �������ת OLED����ʾPositive
			OLED_ShowString(0, 2, "Positive  ");
			for(i = 0; i < 15; i++) {
				dir[i] = pos[i];
			}
		} else if(mode_select == reverse){ // ��ת ��ʾReverse
			OLED_ShowString(0, 2, "Reverse   ");
			for(i = 0; i < 15; i++) {
				dir[i] = rev[i];
			}
		} else {
			OLED_ShowString(0, 2, "Stop      "); // ֹͣ ��ʾStop
			for(i = 0; i < 15; i++) {
				dir[i] = sto[i];
			}
		}
	} else if(gpio_input_bit_get(DIP4_GPIO_PORT, DIP4_PIN) == SET) { // ���뿪�ؿ���
		if(mode_select == forward) { // ѡ��ͬ��ģʽ����
			motor_zhez(motor_speed);
		} else if(mode_select == reverse) {
			motor_fanz(motor_speed);
		} else if(mode_select == stop) {
			motor_stop();
		}
	}
}

// ���°���1���ı�ת��
void EXTI2_IRQHandler(void) {
	if(exti_interrupt_flag_get(USER1_KEY_EXTI_LINE)) {
		if(motor_speed++ >= 10) {
			motor_speed = 3;
		}
		exti_interrupt_flag_clear(USER1_KEY_EXTI_LINE);  // ��ձ�־
	}
}
// ���°���2���ı�ת���ķ���
void EXTI3_IRQHandler(void) {
	if(exti_interrupt_flag_get(USER2_KEY_EXTI_LINE)) {
		if(mode_select++ >= 2) {
			mode_select = 0;
		}
		exti_interrupt_flag_clear(USER2_KEY_EXTI_LINE);  // ��ձ�־
	}
}