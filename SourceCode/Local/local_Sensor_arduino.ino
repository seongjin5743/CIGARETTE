//물감지 아두이노
#include <SoftwareSerial.h>

#define WATER_LIMIT 200
#define GAS_LIMIT 300
#define TXpin 1
#define RXpin -1
int water_PIN = A2;
int flame_PIN = 4;
int gas_PIN = A0;
int buzzer_PIN = 3;

int A1A = 5;int A1B = 6;  // Water pump
int waterfunc();
int gasfunc();
boolean flamefunc();
// SoftwareSerial DebugSerial(RXpin, TXpin);
boolean fire_sensor;
void waterPumper_activate();
void setup() {
  pinMode(water_PIN ,INPUT);
  pinMode(gas_PIN ,INPUT);
  pinMode(flame_PIN, INPUT);
  pinMode(buzzer_PIN, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  Serial.begin(115200); 
}

void loop() {
  int water_main = waterfunc();
  int gas_main= gasfunc();
  boolean flame_main = flamefunc();
  
  //Boozer condition(물 수위 270 이하면 부저 울림)
  if (water_main <= 270){
    digitalWrite(buzzer_PIN, HIGH);
    delay(1000);
    digitalWrite(buzzer_PIN, LOW);
  }
  // water pump condition (가스 265 이상 또는 불꽃 감지하면 워터펌프 동작)
  if(gas_main >= 265 || flame_main == 1){
    waterPumper_activate();
  }

  String temp = String(water_main)+ " "+String(gas_main)+ " "+ String(flame_main);
  Serial.println(temp);
  
  delay(500);
}


int waterfunc(){
  int water_level = analogRead(water_PIN);
  return water_level;
}

int gasfunc(){
  int gas = analogRead(gas_PIN);
  return gas;
}

boolean flamefunc(){
  int flame = digitalRead(flame_PIN);
  if (flame == LOW) {
    return true;
  }
  else {
    return false;
  }
}

void waterPumper_activate(){
  digitalWrite(A1A, HIGH);  // 정방향으로 모터 회전
  digitalWrite(A1B, LOW);
  delay(500);  // 5초동안 상태 유지(1000ms = 5s)
 
  digitalWrite(A1A, LOW);  // 모터 정지
  digitalWrite(A1B, LOW);
  //delay(500);  // 5초동안 상태 유지(1000ms = 5s)
}
