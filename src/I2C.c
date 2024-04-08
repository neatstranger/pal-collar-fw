#include <avr/io.h>


#define RTC_ADDRESS 0x64

#define F_CPU 8000000UL  // Assuming an 8MHz CPU frequency
#define F_SCL 100000UL   // Desired SCL frequency of 100kHz

// Register addresses
#define TIMER_COUNTER_0 0x0B
#define TIMER_COUNTER_1 0x0C
#define EXTENSION_REG 0x0D
#define CONTROL_REG 0x0F



void i2c_init(void) {
    // Set bit rate
    TWBR = ((F_CPU / F_SCL) - 16) / 2;

    // Enable TWI
    TWCR = (1 << TWEN);
}

void i2c_start(void) {
    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void) {
    // Send STOP condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_send_address(uint8_t address) {
    TWDR = address;  // Load address into the data register
    TWCR = (1 << TWINT) | (1 << TWEN);  // Start transmission
    while (!(TWCR & (1 << TWINT)));  // Wait for transmission to complete
}

int main(void) {
    i2c_init();      // Initialize I2C
    i2c_start();     // Send START condition
    i2c_send_address(0x64 << 1);  // Send device address with write operation
    // ... continue with data transmission or reception ...
    i2c_stop();      // Send STOP condition

    return 0;
}
