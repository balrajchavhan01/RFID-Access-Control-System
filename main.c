#include "header.h"
int main() {
    char tag[11], timebuf[9],datebuf[11];
	int user_index=-1;

	const char* valid_tag[] = {"1234567890","210056789A","1122334455"}; // Sample valid tag
const char* user_names[] ={"Balraj","AMIT","RIYA"};
    IO0DIR |= LCD_RS | LCD_EN | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7 ;
	IODIR0 |= SERVO_PIN;
	IODIR0 |= BUZZER_PIN;  // Set buzzer pin as output


    lcd_init(); uart0_init(); i2c_init();
	servo_lock();
    lcd_str("Scan RFID Card");
	uart0_init();
	uart0_print("System Ready:\r\n");
	
	

    while (1) {
			int i=0;
        for (i = 0; i < 10; i++){
           tag[i] = uart0_getchar();			// Read 10 chars from RFID
        uart0_putchar(tag[i]);
				}
			tag[10] = '\0';
				uart0_print("\n");
				uart0_print("\nTag: ");
				uart0_print(tag);
				uart0_print("\r\n");
				
				user_index=-1;
				for(i=0;i<3;i++){
					if(strcmp(tag, valid_tag[i])==0){
						user_index=i;
						break;
					}
				}
				

			
        lcd_cmd(0x01);
        if (user_index != -1) {
					
					//rtc_get_time(timebuf);
					//rtc_get_date(datebuf);
           // lcd_str("Access Granted");
					//delay_ms(2000);
					lcd_cmd(0x80);
					lcd_str("Access Granted");
					delay_ms(1000);
					lcd_cmd(0xc0);
					lcd_str(user_names[user_index]);
					
					//Uart logging 
					uart0_print("Name: ");
					uart0_print(user_names[user_index]);
					uart0_print("| Tag: ");
					uart0_print(tag);
					//uart0_print(timebuf);
					//uart0_print(" | Date: ");
					uart0_print(datebuf);
					uart0_print(" | Access : GRANTED\r\n");
					
					servo_unlock();
					delay_ms(3000);
					servo_lock();
           
        } else {
					lcd_cmd(0x80);
            lcd_str("Access Denied");
					delay_ms(1000);
					lcd_cmd(0xC0);
					lcd_str("locked...");
					uart0_print("Unknow Tag: ");
					uart0_print(tag);
					uart0_print(" | Access : DENIED\r\n");
				buzzer_beep(500);
				delay_ms(1000);

        }

        lcd_cmd(0x01);
        lcd_str("Scan RFID Card");
				
    }
}
