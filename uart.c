#include "header.h"

void uart0_init(void) {
    PINSEL0 |= 0x00000005;   // Enable TxD0 (P0.0), RxD0 (P0.1) as UART
    U0LCR = 0x83;            // 8-bit data, 1 stop bit, no parity, Enable DLAB
    U0DLL = 97;              // Set baud rate to 9600 (PCLK = 15 MHz)
    U0DLM = 0;
    U0LCR = 0x03;            // Clear DLAB after setting DLL & DLM
}

char uart0_getchar(void) {
    while (!(U0LSR & 0x01)); // Wait until data is received
    return U0RBR;            // Return received char
}

void uart0_putchar(char ch) {
    while (!(U0LSR & 0x20)); // Wait until THR is empty
    U0THR = ch;
}

void uart0_print(const char *str) {
    while (*str) {
        uart0_putchar(*str++);
    }
}
