#include "gd32f4xx.h"
#include "gd32f4xx_XII-IOT.h"
#include "systick.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

void systeminit();
void test1_1();
void test1_2(); 
void test1_3();
void test2_1();
void test2_2();

void led_on_immediately();
void led_off_by_order();
void led_on_by_order();
void led_off_immediately();
void resetLightKeyCnt();
void flashLED2_8();


