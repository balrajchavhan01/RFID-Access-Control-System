#include "header.h"
int main() {
    char tag[11], timebuf[9];
	//char *p=tag;
    
	//char valid_tag[] ="123456789";
	const char valid_tag[] = "210056789A"; // Sample valid tag

    IO0DIR |= LCD_RS | LCD_EN | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7 ;
	IODIR0 |= SERVO_PIN;
	IODIR0 |= BUZZER_PIN;  // Set buzzer pin as output


    lcd_init(); uart0_init(); i2c_init();
    lcd_str("Scan RFID Card");
	uart0_init();
	uart0_print("System Ready:\r\n");
	
	

    while (1) {
			int i;
        for (i = 0; i < 10; i++){
           tag[i] = uart0_getchar();			// Read 10 chars from RFID
        uart0_putchar(tag[i]);
				}
			tag[i] = '\0';
				uart0_print("\nTag: ");
				uart0_print(tag);

			
        lcd_cmd(0x01);
        if (strcmp(tag, valid_tag) == 0) {
					servo_unlock();
			delay_ms(3000);
            lcd_str("Access Granted");
					delay_ms(2000);
					lcd_cmd(0xC0);
					lcd_str("UNLOCKING...");
					servo_lock();
            //rtc_get_time(timebuf);
            //lcd_cmd(0xC0); // Second line
            //lcd_str(timebuf);
            //delay_ms(3);
//servo_lock();
        } else {
					servo_lock();
			//delay_ms(30);
            lcd_str("Access Denied");
				buzzer_beep(500);
					delay_ms(1000);
					lcd_cmd(0xC0);
					lcd_str("LOCKED...");
           // delay_ms(2);
					//servo_lock();
        }

        lcd_cmd(0x01);
				//servo_lock();
        lcd_str("Scan RFID Card");
				
    }
}
