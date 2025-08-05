void delay_ms(unsigned int ms) {
	unsigned int i;
    for (i = 0; i < ms * 10000; i++);
}
