#include "ads1115.h"

Ads1115::Ads1115(pins _pin):pin((int)_pin){
    conf[1] &= ~(0b111 << 4);
    conf[1] |= ((pin & 0b111) << 4);
    conf[1] &= ~(1 << 0);              // Configビット8=MODE（MSBバイトのbit0）

    // DR = 860SPS（最速）。他のDRにしたい場合は値を変えてください。
    conf[2] &= ~(0b111 << 5);          // DR[2:0]をクリア
    conf[2] |=  (0b111 << 5);          // 111b = 860SPS
    // printf("%d",conf[1]);
}

void Ads1115::init(){
    i2c_init(i2c0, 100000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
}

int Ads1115::read(){
    i2c_write_blocking(i2c0,ADDR,conf,3,true);
    uint8_t result[2];
    uint8_t data=0b00000000;
    i2c_write_blocking(i2c0,ADDR,&data,1,true);
    sleep_ms(5);
    i2c_read_blocking(i2c0,ADDR,result,2,true);
    int raw =  (int16_t)((result[0] << 8) | result[1]);
    return raw + cali;
}

int Ads1115::setCali(int cali){
    this->cali = cali;
}