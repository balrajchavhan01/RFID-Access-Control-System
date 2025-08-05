//#include <lpc21xx.h>     // Make sure this is first
#include "header.h"      // Optional: your own macros or extra functions


void i2c_init(void) {
    PINSEL0 |= 0x00000050; // P0.2 = SCL0, P0.3 = SDA0
    I2C0SCLH = 60;
    I2C0SCLL = 60;
    I2C0CONSET = 0x40; // Enable I2C
}

void i2c_start(void) {
    I2C0CONSET = 0x20; // STA
    while (!(I2C0CONSET & 0x08)); // SI set
    I2C0CONCLR = 0x28; // Clear STA & SI
}

void i2c_stop(void) {
    I2C0CONSET = 0x10; // STO
    I2C0CONCLR = 0x08; // Clear SI
}

void i2c_write(unsigned char data) {
    I2C0DAT = data;
    I2C0CONCLR = 0x08; // Clear SI
    while (!(I2C0CONSET & 0x08));
}

unsigned char i2c_read(void) {
    I2C0CONSET = 0x04; // AA
    I2C0CONCLR = 0x08;
    while (!(I2C0CONSET & 0x08));
    return I2C0DAT;
}

unsigned char bcd_to_ascii(unsigned char bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void rtc_get_time(char *buf) {
    unsigned char hr, min, sec;
    i2c_start();
    i2c_write(0xD0); // DS1307 Write Address
    i2c_write(0x00); // Start from seconds
    i2c_start();
    i2c_write(0xD1); // DS1307 Read Address
    sec = i2c_read();
    min = i2c_read();
    hr  = i2c_read();
    i2c_stop();

    sec = bcd_to_ascii(sec);
    min = bcd_to_ascii(min);
    hr  = bcd_to_ascii(hr);

    buf[0] = (hr / 10) + '0';
    buf[1] = (hr % 10) + '0';
    buf[2] = ':';
    buf[3] = (min / 10) + '0';
    buf[4] = (min % 10) + '0';
    buf[5] = ':';
    buf[6] = (sec / 10) + '0';
    buf[7] = (sec % 10) + '0';
    buf[8] = '\0';
}
