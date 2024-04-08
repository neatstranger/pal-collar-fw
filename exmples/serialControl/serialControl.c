#include <avr/io.h>

#define F_CPU 8000000UL  // Assuming a 16MHz clock
#define BAUD 9600
#define MY_UBRR F_CPU/8/BAUD-1

void USART_Init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8 data, 2 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

unsigned char USART_Receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));
    // Get and return received data from buffer
    return UDR0;
}

void setup() {
    // Set PB0 as an output
    DDRB |= (1 << PB0);
    // Initialize USART
    USART_Init(MY_UBRR);
}

int main(void) {
    setup();
    while (1) {
        unsigned char receivedByte = USART_Receive();
        if (receivedByte == '1') {
            // Turn PB0 on
            PORTB |= (1 << PB0);
        } else if (receivedByte == '0') {
            // Turn PB0 off
            PORTB &= ~(1 << PB0);
        }
    }
}