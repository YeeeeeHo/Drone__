#include <avr/io.h>

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
	PWM_Init();
	while (1) {
	// 무한 루프 내에서 필요한 작업 수행
	// 여기서는 PWM이 자동으로 생성되므로 별도의 코드가 필요 없음
	}
}
