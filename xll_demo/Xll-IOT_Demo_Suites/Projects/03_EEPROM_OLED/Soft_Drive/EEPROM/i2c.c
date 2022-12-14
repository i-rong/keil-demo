#include "gd32f4xx.h"
#include "i2c.h"
#include <stdio.h>

/*    EEPROM接线定义
			PB10   ---    IIC1_SCL	
			PB11   ---    IIC1_SDA   
*/

/*!
    \brief      configure the GPIO ports
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_gpio_config(void) {
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_I2C1);
	  gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_10);
		gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_11);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
}

/*!
    \brief      configure the I2C0 interfaces
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_config(void) {
    rcu_periph_clock_enable(RCU_I2C1);
    i2c_clock_config(I2C1,I2C1_SPEED,I2C_DTCY_2);
    i2c_mode_addr_config(I2C1,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,I2C1_SLAVE_ADDRESS7);
    i2c_enable(I2C1);
    i2c_ack_config(I2C1,I2C_ACK_ENABLE);
}





