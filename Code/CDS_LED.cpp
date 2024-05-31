#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#define NUM_SENSORS 4
#define THRESHOLD 512 // 예시 임계값, 필요에 따라 조정

void set_led(){
	// PB4 (OC0) 핀을 출력으로 설정
	DDRB |= (1 << PB4);
	
	// Timer 0을 Fast PWM 모드로 설정
	// COM01을 설정하여 비반전 모드로 하고, WGM01과 WGM00을 설정하여 Fast PWM 모드로 합니다.
	// CS01을 설정하여 클럭 소스로 CPU 클럭을 분주 없이 직접 사용합니다.
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
	
	// PWM 듀티 사이클을 0으로 초기화 (LED 끄기)
	OCR0 = 0;
}
void led(uint8_t dc) {
	// OCR0를 조절하여 듀티 사이클을 변경
	OCR0 = dc;
}

void ADC_init(void) {
	// Enable ADC, set prescaler
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	// Use AVCC as reference, set input to PF5
	ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);
}
uint16_t read_ADC(void) {
	// Start conversion
	ADCSRA |= (1<<ADSC);
	
	// Wait for conversion to complete
	while (ADCSRA & (1<<ADSC));
	
	// Return result
	return ADC;
}
uint8_t scale_ADC_value(uint16_t adc_value) {
	// 제곱근 스케일링을 사용하여 밝기 조절
	uint32_t scaled_value = sqrt(adc_value) * 255 / sqrt(1023);
	
	// PWM 값을 80% 더 높이기 위해 1.8을 곱합니다.
	// 단, 최대값을 255로 제한합니다.
	uint32_t pwm_value = scaled_value ;//* 1.8;
	
	if (pwm_value > 255) {
		pwm_value = 255; // 최대값을 초과하지 않도록 제한
	}
	if (pwm_value < 200) {
		pwm_value = 0;
	}
	
	return (uint8_t)pwm_value;
}

int main(void) {
	_delay_ms(1000);
	ADC_init();
	buzzer_on(128);
	set_led();
	_delay_ms(5000);
	buzzer_off();

while (1) {
	uint8_t pwm_value = scale_ADC_value(sensor_value); // Scale sensor value to PWM value
	led(pwm_value); // Adjust PWM signal to control LED brightness
	
	}
}
