#include "header.h"

void buzzer_on(void) {
    IOSET0 = BUZZER_PIN;
}

void buzzer_off(void) {
    IOCLR0 = BUZZER_PIN;
}

void buzzer_beep(unsigned int duration_ms) {
    buzzer_on();
    delay_ms(duration_ms);
    buzzer_off();
}

