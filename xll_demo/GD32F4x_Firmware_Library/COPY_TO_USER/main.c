#include "user.h"
#include "test.h"

char TCP_Server_IP[]  = "47.99.144.16";	//芯力量服务器IP
char TCP_Server_COM[] = "8051";			//芯力量服务器端口

u8  res   = 1;//用于4G模块自检
u8 NET_flag   = 2;	//0表示TCP服务器已断开，1表示连接

int main(void)
{ 
	systeminit();
	int type = 4;
	while(1){ 
		switch (type) {
			case 0: test1_1(); break;
			case 1: test1_2(); break;
			case 2: test1_3(); break;
			case 3: test2_1(); break;
			case 4: test2_2(); break;
			default: break;
		}
	}			
}
