#ifndef _TEST_H
#define _TEST_H

#include "gd32f4xx.h"

#define EEPROM_FIRST_PAGE           0x00						//EEPROMÆðÊ¼µØÖ·

void systemInit();
void test1();
void test2();
void test3();
uint8_t i2c_24c02_test();
#endif  
