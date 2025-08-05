#include "header.h"
void lcd_enable(void) {
    IO0SET = LCD_EN;
    delay_ms(2);
    IO0CLR = LCD_EN;
    delay_ms(2);
}

void lcd_cmd(unsigned char cmd) {
    IO0CLR = LCD_RS;

    IO0CLR = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    if (cmd & 0x10) IO0SET |= LCD_D4;
    if (cmd & 0x20) IO0SET |= LCD_D5;
    if (cmd & 0x40) IO0SET |= LCD_D6;
    if (cmd & 0x80) IO0SET |= LCD_D7;
    lcd_enable();

    IO0CLR = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    if (cmd & 0x01) IO0SET |= LCD_D4;
    if (cmd & 0x02) IO0SET |= LCD_D5;
    if (cmd & 0x04) IO0SET |= LCD_D6;
    if (cmd & 0x08) IO0SET |= LCD_D7;
    lcd_enable();
}

void lcd_data(unsigned char data) {
    IO0SET = LCD_RS;

    IO0CLR = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    if (data & 0x10) IO0SET |= LCD_D4;
    if (data & 0x20) IO0SET |= LCD_D5;
    if (data & 0x40) IO0SET |= LCD_D6;
    if (data & 0x80) IO0SET |= LCD_D7;
    lcd_enable();

    IO0CLR = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    if (data & 0x01) IO0SET |= LCD_D4;
    if (data & 0x02) IO0SET |= LCD_D5;
    if (data & 0x04) IO0SET |= LCD_D6;
    if (data & 0x08) IO0SET |= LCD_D7;
    lcd_enable();
}

void lcd_init(void) {
    delay_ms(20);
    lcd_cmd(0x02);  // 4-bit
    lcd_cmd(0x28);  // 2 lines, 5x7
    lcd_cmd(0x0C);  // Display ON
    lcd_cmd(0x06);  // Auto-increment
    lcd_cmd(0x01);  // Clear
}

void lcd_str(char *str) {
    while (*str) lcd_data(*str++);
}
