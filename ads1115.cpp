#include "ads1115.h"

adc::adc(pins _pin):pin((int)_pin){
    conf[1]|=(pin<<4);
    printf("%d",conf[1]);
}

void adc::init(){

}

int adc::read(){
    i2c.write(ADDR,conf,3);
    uint8_t result[2];
    uint8_t data=0b00000000;
    i2c.write(ADDR,&data,1);
    i2c.read(ADDR,result,2);
    return (result[0]<<4)|(result[1]>>4);
}
