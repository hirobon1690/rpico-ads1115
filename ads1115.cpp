#include "ads1115.h"

adc::adc(pins _pin):pin((int)_pin){
    conf[1]|=(pin<<4);
    // printf("%d",conf[1]);
}

void adc::init(){
    i2c_init(i2c0, 100000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
}

int adc::read(){
    i2c.write(ADDR,conf,3);
    uint8_t result[2];
    uint8_t data=0b00000000;
    i2c_write_blocking(i2c0,ADDR,&data,1,true);
    i2c_read_blocking(i2c0,ADDR,result,2,true);
    return (result[0]<<4)|(result[1]>>4);
}
