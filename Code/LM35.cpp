#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


// ADC 초기화
void ADC_Init() {
	// AVCC를 기준 전압으로 사용, PF4를 아날로그 입력으로 설정
	ADMUX = (1<<REFS0) | (1<<MUX2);
	// ADC Enable, 프리스케일러 64 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1);
}

// ADC 값 읽기
uint16_t ADC_Read() {
	// 변환 시작
	ADCSRA |= (1<<ADSC);
	// 변환 완료 대기
	while (ADCSRA & (1<<ADSC));
	// 변환 결과 반환
	return ADC;
}

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
// 메인 함수
int main(void) {
	// 시리얼 통신 초기화 (9600 Baud)
	USART_Init(103); // 16MHz 클럭 기준 9600 Baud
	// ADC 초기화
	ADC_Init();
	while (1) {
		// ADC 값 읽기
		uint16_t sensorValue = ADC_Read();
		// 값을 전압으로 변환 (10비트 ADC, 5V 기준)
		float voltage = sensorValue * (5.0 / 1023.0);
		// 전압을 온도로 변환 (LM35는 10mV/°C 비율)
		float temperature = sensorValue / 9.31;//voltage * 100.0 / 1024;
	
		// 온도를 문자열로 변환하여 시리얼 통신으로 전송
	
		if(temperature >= 16){ //17
			buzzer_on(128);
	
		}
		else{
		 buzzer_off();
		}
		// 1초 대기
		//_delay_ms(10);
	}
}
