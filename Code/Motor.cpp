#include <avr/io.h>

void PWM_Init() {
// Initialize Timer/Counter1 and Timer/Counter3
DDRB |= (1 << PB5) | (1 << PB6); // Set OC1A and OC1B as outputs
TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10); // No prescaling
ICR1 = 15999; // Set TOP for 1kHz PWM frequency

// Timer/Counter3
DDRE |= (1 << PE3) | (1 << PE4); // Set OC3A and OC3B as outputs
TCCR3A = (1 << WGM31) | (1 << COM3A1) | (1 << COM3B1);
TCCR3B = (1 << WGM32) | (1 << WGM33) | (1 << CS30); // No prescaling
ICR3 = 15999; // Set TOP for 1kHz PWM frequency

// Set Duty Cycle to 80%
OCR1A = ICR1 * 0.8; // OC1A
OCR1B = ICR1 * 0.8; // OC1B
OCR3A = ICR3 * 0.8; // OC3A
OCR3B = ICR3 * 0.8; // OC3B
}
int main(void) {
	PWM_Init(); // Initialize PWM
	while (1) {
		// Main loop does nothing
	}
}
