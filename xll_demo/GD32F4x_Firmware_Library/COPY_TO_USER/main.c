#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "systick.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

char TCP_Server_IP[]  = "47.99.144.16";	//о����������IP
char TCP_Server_COM[] = "8051";			//о�����������˿�

u8  res   = 1;//����4Gģ���Լ�
u8 NET_flag   = 2;	//0��ʾTCP�������ѶϿ���1��ʾ����

int main(void)
{ 
	systeminit();
	int type = 3;
	while(1){ 
		switch (type) {
			case 0: test1_1(); break;
			case 1: test1_2(); break;
			case 2: test1_3(); break;
			case 3: test2_1(); break;
			default: break;
		}
	}			
}
