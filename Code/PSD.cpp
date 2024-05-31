#include <avr/io.h>

#define NUM_SENSORS 4
#define THRESHOLD 512 // 예시 임계값, 필요에 따라 조정

void adc_init() {
	ADMUX = (1<<REFS0); // AVCC를 기준 전압으로 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // ADC 활성화 및 분주비 설정
}

uint16_t adc_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // 채널 선택
	ADCSRA |= (1<<ADSC); // 변환 시작
	while (ADCSRA & (1<<ADSC)); // 변환 완료 대기
	return ADC; // 결과 반환
}

void buzzer_init() {
	DDRB |= (1<<PB7); // PB7을 출력으로 설정
}

void buzzer_on() {
	PORTB |= (1<<PB7); // PB7에 HIGH 신호를 보내 부저를 켬
}

void buzzer_off() {
	PORTB &= ~(1<<PB7); // PB7에 LOW 신호를 보내 부저를 끔
}

int main(void) {
	uint16_t sensor_values[NUM_SENSORS];
	uint8_t i;
	
	adc_init(); // ADC 초기화
	buzzer_init(); // 부저 초기화
	
	while (1) {
		for (i = 0; i < NUM_SENSORS; i++) {
			sensor_values[i] = adc_read(i); // 센서 값 읽기
			if (sensor_values[i] > THRESHOLD) { // 임계값 검사
				buzzer_on(); // 부저 켜기
				break; // 하나라도 임계값을 넘으면 루프 탈출
			}
		}
		if (i == NUM_SENSORS) { // 모든 센서가 임계값 미만인 경우
			buzzer_off(); // 부저 끄기
		}
	}
	
	return 0;
}
