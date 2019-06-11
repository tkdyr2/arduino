
#include "HX711.h" //HX711로드셀 엠프 관련함수 호출
#include <Wire.h>
#include "Timer.h"
#define calibration_factor -7050.0 // 로드셀 스케일 값 선언
#define DOUT  A1 //엠프 데이터 아웃 핀 넘버 선언
#define CLK  A0  //엠프 클락 핀 넘버 
HX711 scale(DOUT, CLK); //엠프 핀 선언 
int buttonApin = 5; //세탁기2 버튼1
int buttonBpin = 6; //세탁기2 버튼2
int buttonCpin = 7; //세탁기2 버튼3
int red = 8;  //빨간색 LED
int white = 9; //하얀색 LED
int blue = 10; //파란색 LED

int state = 1; //세탁기2 상태 0..고장 1..사용가능 2..사용중
int rg = 0; //세탁기2 예약 0..예약안됨 1..예약 중
Timer t;
int pin = 13; //타이머 설정 핀
int lefttime = 1;  //세탁기2 남은빨래시간 가정
int mode = 0; //세탁기 빨래 모드 0..저 1..중 2..고(가정)

void setup() {
  Serial.begin(9600);  // 시리얼 통신 개방
  scale.set_scale(calibration_factor);  //스케일 지정 
  scale.tare();  //스케일 설정
  Serial.println("Readings:");
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  pinMode(pin,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(white,OUTPUT);
  pinMode(blue,OUTPUT);
}

void loop() {
  t.update();
  if(state == 0){  //사용불가 빨간LED 
    digitalWrite(red,HIGH);
    digitalWrite(white,LOW);
    digitalWrite(blue,LOW);
  }
   if(state == 1){  //사용가능 파란LED
    digitalWrite(red,LOW);
    digitalWrite(white,LOW);
    digitalWrite(blue,HIGH);
  }
   if(state == 2){  //사용중 하양LED
    digitalWrite(red,LOW);
    digitalWrite(white,HIGH);
    digitalWrite(blue,LOW);
  }

  if(state == 2){ //세탁기 사용 후 무게를 재어 사용 가능여부 판단
    delay(5000);
    if(scale.get_units() < (-0.2)){
    }
    else{
      state = 1;
    }
  }
  
   if (digitalRead(buttonApin) == LOW)
    {
      if(mode == 0){  
        Serial.println("세탁모드 저");
      }
     else{
       mode--;//세탁모드 내림
       if(mode == 0){
          Serial.println("세탁모드 저");
        }
         if(mode == 1){
          Serial.println("세탁모드 중");
        }  
        if(mode == 2){
         Serial.println("세탁모드 고");
        }
      }
   }
   if (digitalRead(buttonBpin) == LOW)
    {
     if(mode == 2){
      Serial.println("세탁모드 고");
     }
     else{
        mode++;//세탁모드 올림
         if(mode == 0){
         Serial.println("세탁모드 저");
         }
         if(mode == 1){
         Serial.println("세탁모드 중");
         }  
         if(mode == 2){
          Serial.println("세탁모드 고");
         }
      }
   }
    if(digitalRead(buttonCpin) == LOW)
   {
     if(state == 0){  //세탁기 고장 상태 
        Serial.println("세탁기2 고장");
     }
    if(state == 1){
      state = 2; //사용 시작
      if(state == 2){
       Serial.println("세탁기2 사용 시작");
      }
      
    }
    else if(state == 2){
      state = 1; //사용 종료
      if(state == 1){
       Serial.println("세탁기2 사용 종료");
      }
    }
  }

}
