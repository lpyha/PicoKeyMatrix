// https://geekyfab.com/entry/2020/10/23/071000
#include <Arduino.h>

const int KEYIN[] = {16, 20, 28};
const int KEYOUT[] = {0, 2, 3, 4};

unsigned long previousMillis = 0;
const long interval = 50;
int columnNum=0;
int sw[4][3]={0};

void setup() {
  for(int i=0; i<3; i++){
    pinMode(KEYIN[i],INPUT);
  }
  for (int i = 0; i < 4; i++){
    pinMode(KEYOUT[i],OUTPUT);
    digitalWrite(KEYOUT[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(KEYOUT[columnNum], HIGH);
    for(int rowNum = 0; rowNum < 3; rowNum++){
      sw[columnNum][rowNum]=digitalRead(KEYIN[rowNum]);
      delay(10);
    }
    digitalWrite(KEYOUT[columnNum], LOW);
    columnNum++;
    columnNum &=3;
  }
  if(columnNum==3){
    for(int i=0; i<4; i++){
      for(int j=0; j<3; j++){
        Serial.print(sw[i][j]);
      }
      Serial.println();
    }
    Serial.println();
    Serial.println();
    delay(500);
  }
}