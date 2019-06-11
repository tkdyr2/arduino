
#include "HX711.h" //HX711로드셀 엠프 관련함수 호출
#include <Wire.h>
#include "Timer.h"
#define calibration_factor -7050.0 // 로드셀 스케일 값 선언
<<<<<<< HEAD
#define DOUT  A1 //엠프 데이터 아웃 핀 넘버 선언
#define CLK  A0  //엠프 클락 핀 넘버 
HX711 scale(DOUT, CLK); //엠프 핀 선언 
int buttonApin = 5; //세탁기1 버튼1
int buttonBpin = 6; //세탁기1 버튼2
int buttonCpin = 7; //세탁기1 버튼3

int state = 1; //세탁기1 상태 0..고장 1..사용가능 2..사용중
int rg = 0; //세탁기1 예약 0..예약안됨 1..예약 중
Timer t;
int pin = 13; //타이머 설정 핀
int lefttime = 1;  //세탁기1 남은빨래시간 가정
int mode = 0; //세탁기 빨래 모드 0..저 1..중 2..고(가정)
=======
#define DOUT1  A1 //세탁기1 엠프 데이터 아웃 핀 넘버 선언
#define CLK1  A0  //세탁기1 엠프 클락 핀 넘버 
#define DOUT2 A3 //세탁기2 엠프 데이터 아웃 핀 넘버 선언
#define CLK2 A2 //세탁기2 엠프 클락 핀 넘버

HX711 scale1(DOUT1, CLK1); //세탁기1 엠프 핀 선언
HX711 scale2(DOUT2, CLK2); //세탁기2 엠프 핀 선언 

int buttonApin1 = 5; //세탁기1 버튼1
int buttonBpin1 = 6; //세탁기1 버튼2
int buttonCpin1 = 7; //세탁기1 버튼3
int buttonApin2 = 8; //세탁기2 버튼1
int buttonBpin2 = 9; //세탁기2 버튼2
int buttonCpin2 = 10; //세탁기2 버튼3


int state1 = 1; //세탁기1 상태 0..고장 1..사용가능 2..사용중
int rg1 = 0; //세탁기1 예약 0..예약안됨 1..예약 중
int state2 = 1; //세탁기2 상태 
int rg2 = 0; //세탁기2 예약 
Timer t1;
Timer t2;
int pin = 13; //타이머 설정 핀
int mode1 = 0; //세탁기1 빨래 모드 0..저 1..중 2..고(가정)
int mode2 = 0; //세탁기2 빨래 모드
>>>>>>> 0589a4ba8a251749993a820fe08224b2e239baec

void setup() {
  Serial.begin(9600);  // 시리얼 통신 개방  
  scale.set_scale(calibration_factor);  //스케일 지정 
  scale.tare();  //스케일 설정
  Serial.println("Readings:");
<<<<<<< HEAD
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
=======
  pinMode(buttonApin1, INPUT_PULLUP);
  pinMode(buttonBpin1, INPUT_PULLUP);
  pinMode(buttonCpin1, INPUT_PULLUP);
  pinMode(buttonApin2, INPUT_PULLUP);
  pinMode(buttonBpin2, INPUT_PULLUP);
  pinMode(buttonCpin2, INPUT_PULLUP);
>>>>>>> 0589a4ba8a251749993a820fe08224b2e239baec
  pinMode(pin,OUTPUT);
  t.pulse(pin,lefttime1*60*1000,HIGH);
}

void loop() {
  Serial.print("Reading wm1: ");
  Serial.print(scale1.get_units(), 1);  //세탁기1 무게 출력 
  Serial.print(" lbs"); //단위
  Serial.println(); 
  Serial.print("Reading wm2: ");
  Serial.print(scale2.get_units(), 1);  //세탁기2 무게 출력 
  Serial.print(" lbs"); //단위
  Serial.println(); 
  t.update();
  if(state == 1){
   if (digitalRead(buttonApin1) == LOW)
    {
      if(mode == 0){
      
<<<<<<< HEAD
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
   if (digitalRead(buttonBpin1) == LOW)
    {
     if(mode == 2){
      
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
=======
    }
    else{
      mode1--;//세탁모드 내림
      if(mode1 == 0){
        Serial.println("세탁기1 세탁모드 저");
       }
       if(mode1 == 1){
        Serial.println("세탁기1 세탁모드 중");
       }
       if(mode1 == 2){
        Serial.println("세탁기1 세탁모드 고");
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
        Serial.println("세탁기1 세탁모드 저");
       }
       if(mode1 == 1){
        Serial.println("세탁기1 세탁모드 중");
       }
       if(mode1 == 2){
        Serial.println("세탁기1 세탁모드 고");
       }
    }
>>>>>>> 0589a4ba8a251749993a820fe08224b2e239baec
  }
    if (digitalRead(buttonCpin1) == LOW)
   {
     if(state == 0){
        Serial.println("세탁기 고장");
     }
    if(state == 1){
      state = 2; //사용 시작
      if(state == 2){
       Serial.println("세탁기1 사용 시작");
      }
      
    }
    else if(state == 2){
      state = 1; //사용 종료
      if(state == 1){
       Serial.println("세탁기1 사용 종료");
      }
    }
  }
  if (digitalRead(buttonApin2) == LOW)
  {
    if(mode2 == 0){
      
    }
    else{
      mode2--;//세탁모드 내림
      if(mode2 == 0){
        Serial.println("세탁기2 세탁모드 저");
       }
       if(mode2 == 1){
        Serial.println("세탁기2 세탁모드 중");
       }
       if(mode2 == 2){
        Serial.println("세탁기2 세탁모드 고");
       }
    }
  }
  if (digitalRead(buttonBpin2) == LOW)
  {
    if(mode2 == 2){
      
    }
    else{
      mode2++;//세탁모드 올림
       if(mode2 == 0){
        Serial.println("세탁모드 저");
       }
       if(mode2 == 1){
        Serial.println("세탁모드 중");
       }
       if(mode2 == 2){
        Serial.println("세탁모드 고");
       }
    }
  }
  
  if (digitalRead(buttonCpin2) == LOW)
  {
    if(state2 == 1){
      state2 = 2; //사용 시작
      if(state2 == 2){
       Serial.println("세탁기1 사용 시작");
      }
      
    }
    else if(state2 == 2){
      state2 = 1; //사용 종료
      if(state2 == 1){
       Serial.println("세탁기1 사용 종료");
      }
    }
  }

}
