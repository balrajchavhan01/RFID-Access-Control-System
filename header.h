#include <lpc21xx.h>
#include <string.h>
extern unsigned char valid_tag;

#define LCD_RS (1<<4)   // P0.4
#define LCD_EN (1<<5)   // P0.5
#define LCD_D4 (1<<6)   // P0.6
#define LCD_D5 (1<<7)   // P0.7
#define LCD_D6 (1<<8)   // P0.8
#define LCD_D7 (1<<9)   // P0.9
#define SERVO_PIN (1<<10) // P0.10

#define I2C0CONSET  (*((volatile unsigned long *) 0xE001C000))
#define I2C0STAT    (*((volatile unsigned long *) 0xE001C004))
#define I2C0DAT     (*((volatile unsigned long *) 0xE001C008))
#define I2C0ADR     (*((volatile unsigned long *) 0xE001C00C))
#define I2C0SCLH    (*((volatile unsigned long *) 0xE001C010))
#define I2C0SCLL    (*((volatile unsigned long *) 0xE001C014))
#define I2C0CONCLR  (*((volatile unsigned long *) 0xE001C018))


// Only declaration

void delay_ms(unsigned int ms);
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_str(char *s);

void uart0_init(void);
char uart0_getchar(void);

void i2c_init(void);
void rtc_get_time(char *buf);
void servo_unlock(void);
void servo_lock(void);
void uart0_putchar(char );
void uart0_print(const char *);
// Dummy RFID database (for demo)
//extern unsigned char valid_tag = "210056789A"; // Example 10-digit ASCII ID
