
#include "HX711.h" //HX711로드셀 엠프 관련함수 호출
#include <Wire.h>
#include "Timer.h"
#define calibration_factor -7050.0 // 로드셀 스케일 값 선언
#define DOUT  A1 //엠프 데이터 아웃 핀 넘버 선언
#define CLK  A0  //엠프 클락 핀 넘버 
HX711 scale(DOUT, CLK); //엠프 핀 선언 
int buttonApin1 = 5; //세탁기1 버튼1
int buttonBpin1 = 6; //세탁기1 버튼2
int buttonCpin1 = 7; //세탁기1 버튼3

int state1 = 1; //세탁기1 상태 0..고장 1..사용가능 2..사용중
int rg1 = 0; //세탁기1 예약 0..예약안됨 1..예약 중
Timer t;
int pin = 13; //타이머 설정 핀
int lefttime1 = 1;  //세탁기1 남은빨래시간 가정
int mode1 = 0; //세탁기 빨래 모드 0..저 1..중 2..고(가정)

void setup() {
  Serial.begin(9600);  // 시리얼 통신 개방
  Serial.println("HX711 scale TEST");  
  scale.set_scale(calibration_factor);  //스케일 지정 
  scale.tare();  //스케일 설정
  Serial.println("Readings:");
  pinMode(buttonApin1, INPUT_PULLUP);
  pinMode(buttonBpin1, INPUT_PULLUP);
  pinMode(buttonCpin1, INPUT_PULLUP);
  pinMode(pin,OUTPUT);
  t.pulse(pin,lefttime1*60*1000,HIGH);
}

void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);  //무제 출력 
  Serial.print(" lbs"); //단위
  Serial.println(); 
  t.update();

  if (digitalRead(buttonApin1) == LOW)
  {
    if(mode1 == 0){
      
    }
    else{
      mode1--;//세탁모드 내림
      if(mode1 == 0){
        Serial.println("세탁모드 저");
       }
       if(mode1 == 1){
        Serial.println("세탁모드 중");
       }
       if(mode1 == 2){
        Serial.println("세탁모드 고");
       }
    }
  }
  if (digitalRead(buttonBpin1) == LOW)
  {
    if(mode1 == 2){
      
    }
    else{
      mode1++;//세탁모드 올림
       if(mode1 == 0){
        Serial.println("세탁모드 저");
       }
       if(mode1 == 1){
        Serial.println("세탁모드 중");
       }
       if(mode1 == 2){
        Serial.println("세탁모드 고");
       }
    }
  }
  if (digitalRead(buttonCpin1) == LOW)
  {
    if(state1 == 1){
      state1 = 2; //사용 시작
      if(state1 == 2){
       Serial.println("세탁기1 사용 시작");
      }
      
    }
    else if(state1 == 2){
      state1 = 1; //사용 종료
      if(state1 == 1){
       Serial.println("세탁기1 사용 종료");
      }
    }
  }

}
