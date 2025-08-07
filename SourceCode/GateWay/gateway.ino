#include <SoftwareSerial.h>
#include "SNIPE.h"

#define ATSerial Serial
#define TXpin 11
#define RXpin 10
// 16byte hex key
String lora_app_key = "11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 00";  

// LoRa 모듈과의 통신을 위해 SoftwareSerial은 더 이상 사용하지 않습니다.
SoftwareSerial DebugSerial(RXpin,TXpin);
SNIPE SNIPE(ATSerial);

int water_state = 0;
int gas_state = 0; 
int flame_state = 0;

void setup() {
  ATSerial.begin(115200);

  // put your setup code here, to run once:
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
}

void loop() {
  String receivedString = SNIPE.lora_recv();
  // 문자열 나누기
  int firstIndex = receivedString.indexOf(' '); // 첫 번째 공백의 위치 찾기
  int secondIndex = receivedString.indexOf(' ', firstIndex + 1);  // 두 번째 공백의 위치 찾기
  String first = receivedString.substring(0, firstIndex); // 첫 번째 문자열
  String second = receivedString.substring(firstIndex + 1, secondIndex); // 두 번째 문자열
  String third = receivedString.substring(secondIndex);

  water_state = first.toInt();  // 물 수위 상태값
  gas_state = second.toInt();  // 일산화탄소 상태값
  flame_state = third.toInt();  // 불꽃 감지 상태값

  if(water_state != 0 && gas_state != 0 || flame_state != 0)
    // 시리얼 모니터 출력 및 시리얼 통신
    Serial.println(String(water_state) + " " + String(gas_state) + " " +String(flame_state));
  delay(10);
}
