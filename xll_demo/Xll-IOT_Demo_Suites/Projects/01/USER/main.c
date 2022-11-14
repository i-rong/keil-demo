#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "systick.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>


char TCP_Server_IP[]  = "47.99.144.16";	
char TCP_Server_COM[] = "8051";					


u8  res   = 1;			
u8 NET_flag   = 2;	

char *tab = "gd30f407 + rongrong + 22920202204632";

int main(void)
{  
	systick_config();
	gd_XII_systeminit();
	usart0Init(EVAL_COM0, 115200u);
//	init_4g();
	
	gd_eval_led_on(LED1); 
	gd_eval_led_on(LED2);
	gd_eval_led_on(LED3);
	//json_student_imformation01("gd32f407", "rongrong", "22920202204632");
	//Uart0Printf("My tab is: %s\r\n", tab);
	while(1){ 
	}			
}
