#include <avr/io.h>
#include <util/delay.h>

void init_pwm(void) {
	// 타이머/카운터3을 고속 PWM 모드로 설정
	TCCR3A |= (1 << WGM31) | (1 << COM3C1);
	TCCR3B |= (1 << WGM32) | (1 << WGM33) | (1 << CS31); // 분주비를 8로 설정
	// ICR3에 PWM 주기를 설정 (16MHz / 8 분주비 / 50Hz)
	ICR3 = 39999;
	// PE5 핀을 출력으로 설정
	DDRE |= (1 << PE5);
}

void set_servo_angle(unsigned char angle) {
	// 각도를 PWM 듀티 사이클로 변환 (1000us ~ 2000us 범위)
	// 예: 0도 -> 1000, 180도 -> 2000
	unsigned int pulse_width = ((angle * 1000) / 180) + 1000;
	// OCR3C에 듀티 사이클을 설정 (16MHz / 8 분주비 / 50Hz = 40000 ticks per period)
	OCR3C = (pulse_width * 4); // (pulse_width / 20000) * 40000
}

int main(void) {
	init_pwm();
	while (1) {
		set_servo_angle(90); // 예시로 90도로 설정
		_delay_ms(10000);
		set_servo_angle(180);
		_delay_ms(10000);
	}
}

