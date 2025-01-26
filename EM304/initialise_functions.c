#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


void i2c_initialisation(i2c_inst_t *port,uint freq, int SDA_pin,int SCL_pin){
// I2C Initialisation. Using it at 400Khz.
    i2c_init(port, freq);
    gpio_set_function(SDA_pin, GPIO_FUNC_I2C);
    gpio_set_function(SCL_pin, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_pin);
    gpio_pull_up(SCL_pin);

int P;
    if (port==i2c0){
       P = 0;
    }
    if (port==i2c1){
       P = 1;
    }

    printf("I2C Initialised at %d on port %d with SDA on pin %d and SCL on pin %d!!", freq/1000, P,SDA_pin,SCL_pin);
// For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c
}