#include <reg51.h>

void UART_init(void)
{
    SCON = 0x50;  // Set UART in mode 1 (8-bit UART), enable reception
    TMOD = 0x20;  // Timer 1 in mode 2 (8-bit auto-reload)
    TH1 = 0xFD;   // Baud rate 9600 (for 11.0592 MHz crystal)
    TR1 = 1;      // Start Timer 1
}

void send_char(unsigned char c)
{
    SBUF = c;
    while (TI == 0);  // Wait for transmission to complete
    TI = 0;           // Clear transmit interrupt flag
}

void send(unsigned char *str)
{
    while (*str)
    {
        send_char(*str);  // Send each character in the string
        str++;
    }
}

void delay(unsigned int time)  // Delay function for hardware timing
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1275; j++);
}

void main()
{
		UART_init();
		while(1)
		{
			send("HI");
			delay(10);
		}
}
