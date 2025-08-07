#include <SoftwareSerial.h>
#include "SNIPE.h"

#define PING 1
#define PONG 2
#define CODE PING
#define ATSerial Serial

#define TXpin 11
#define RXpin 10
#define WATER_LIMIT 200
#define GAS_LIMIT 260


//16byte hex key
String lora_app_key = "11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 00";  

SoftwareSerial DebugSerial(RXpin,TXpin);
SNIPE SNIPE(ATSerial);

int A1A = 5;
int A1B = 6;
void waterPumper_activate();

void setup() {
  ATSerial.begin(115200);

  while(ATSerial.read()>= 0) {}
  while(!ATSerial);

  DebugSerial.begin(115200);

  /* SNIPE LoRa Initialization */
  if (!SNIPE.lora_init()) {
    DebugSerial.println("SNIPE LoRa Initialization Fail!");
    while (1);
  }

  /* SNIPE LoRa Set Appkey */
  if (!SNIPE.lora_setAppKey(lora_app_key)) {
    DebugSerial.println("SNIPE LoRa app key value has not been changed");
  }
  
  /* SNIPE LoRa Set Frequency */
  if (!SNIPE.lora_setFreq(LORA_CH_1)) {
    DebugSerial.println("SNIPE LoRa Frequency value has not been changed");
  }

  /* SNIPE LoRa Set Spreading Factor */
  if (!SNIPE.lora_setSf(LORA_SF_7)) {
    DebugSerial.println("SNIPE LoRa Sf value has not been changed");
  }

  /* SNIPE LoRa Set Rx Timeout 
   * If you select LORA_SF_12, 
   * RX Timout use a value greater than 5000  
  */
  if (!SNIPE.lora_setRxtout(5000)) {
    DebugSerial.println("SNIPE LoRa Rx Timout value has not been changed");
  }  
    
  DebugSerial.println("SNIPE LoRa PingPong Test");
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);

  DebugSerial.println("Start");

}
// <수신측>
void loop() {
  int water_state = 0;
  int gas_state = 0; 
  int flame_state = 0;
  
  if (Serial.available() > 0) {
      Serial.flush();
      String receivedString = Serial.readStringUntil('\n');
    
      int firstIndex = receivedString.indexOf(' '); // 첫 번째 공백의 위치 찾기
      int secondIndex = receivedString.indexOf(' ', firstIndex + 1);  // 두 번째 공백의 위치 찾기
      String first = receivedString.substring(0, firstIndex); // 첫 번째 문자열
      String second = receivedString.substring(firstIndex + 1, secondIndex); // 두 번째 문자열
      String third = receivedString.substring(secondIndex);

      int water_state = first.toInt(); // 물 수위 상태값
      int gas_state = second.toInt(); // 일산화탄소 상태값
      int flame_state = third.toInt();   // 불꽃 감지 상태값

      if((gas_state >= GAS_LIMIT)&&(flame_state == 1)){
        waterPumper_activate();
        delay(3000);
        DebugSerial.println("water state = " + String(water_state) + "   gas state = " + String(gas_state) + "   flame state = " + String(flame_state));
      }
      else{
        delay(5000);
        DebugSerial.println("water state = " + String(water_state) + "   gas state = " + String(gas_state) + "   flame state = " + String(flame_state));
      }

      if(SNIPE.lora_send(receivedString)){
        // DebugSerial.println("send success");
        // String ver = SNIPE.lora_recv();
        // Serial.println(ver);
      }
      Serial.flush();
      
  }
}

void waterPumper_activate(){
  digitalWrite(A1A, HIGH);  // 정방향으로 모터 회전
  digitalWrite(A1B, LOW);
  delay(2000);  // 5초동안 상태 유지(1000ms = 5s)
 
  digitalWrite(A1A, LOW);  // 모터 정지
  digitalWrite(A1B, LOW);
  //delay(500);  // 5초동안 상태 유지(1000ms = 5s)
}
