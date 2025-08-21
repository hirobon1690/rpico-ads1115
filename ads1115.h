#pragma once
#include <hardware/gpio.h>
#include <hardware/i2c.h>

enum pins{
    A0=0b100,
    A1=0b101,
    A2=0b110,
    A3=0b111
};
class Ads1115{
    public:
        Ads1115(pins);
        void init();
        int read();
        int setCali(int);

    private:
        int pin;
        uint8_t conf[3]={0b00000001,0b10000010,0b10000011};
        const uint8_t ADDR=0x48;
        int cali=0;
};
