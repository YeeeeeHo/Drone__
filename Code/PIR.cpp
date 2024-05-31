#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz

void buzzer_on(int a){
	// PB7을 출력으로 설정
	DDRB |= (1 << PB7);
	// 타이머2를 Fast PWM 모드로 설정
	TCCR2 |= (1 << WGM20) | (1 << WGM21);
	
	// 비반전 모드 설정: COM21:0 = 2 -> OC2 클리어 시 비교 일치, BOTTOM에서 OC2 설정
	TCCR2 |= (1 << COM21);
	
	// 분주비 설정 (예: 클럭/64)
	TCCR2 |= (1 << CS22);
	
	// PWM 듀티 사이클 설정 (0 ~ 255 사이 값으로 듀티 사이클 조절)
	OCR2 = a; // 예시로 50% 듀티 사이클로 설정
}
void buzzer_off(){
	// PWM 출력을 중지하기 위해, 비교 출력 모드를 0으로 설정
	TCCR2 &= ~(1 << COM21);
}
int main(void) {
	// PD2(아두이노의 2번 핀에 해당)를 입력으로 설정
	DDRD &= ~(1 << DDD7);
	while (1) {
		if (PIND & (1 << PIND7)) { // PD2에서 입력을 읽음
			buzzer_on(125);
			_delay_ms(2000);
			buzzer_off();
			_delay_ms(1000);
			}
			else {
			buzzer_off();
		}
		_delay_ms(10); // 10ms 지연
	}
}
