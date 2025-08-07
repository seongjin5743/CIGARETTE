#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

String apiKey = "Your ThingSpeak apiKey";  // 여기에 API키값을 입력합니다.
const char* ssid = "Your WiFi Name"; // ESP8266이 연결되는 SSID 입니다.
const char* password = "Yout WiFi Password"; // 비번입니다.
const char* server = "api.thingspeak.com";
// 센서가 연결되는 핀번호입니다. Wemos에 맞게 해주세요
#define ATSerial Serial
#define TXpin 11
#define RXpin 10

WiFiClient client;

SoftwareSerial DebugSerial(RXpin, TXpin);

int water_state = 0;  // 물 수위 센서
int gas_state = 0;  // 가스 감지 센서
int flame_state = 0;  // 불꽃감지 센서

void setup() {
  Serial.begin(115200);
  delay(10);

  while (ATSerial.read() >= 0) {}
  while (!ATSerial);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("wait..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  // 시리얼 통신으로 데이터가 들어올 경우
  if (Serial.available() > 0) {
    Serial.flush();
    String receivedString = Serial.readStringUntil('\n');
    int firstIndex = receivedString.indexOf(' '); // 첫 번째 공백의 위치 찾기
    int secondIndex = receivedString.indexOf(' ', firstIndex + 1);  // 두 번째 공백의 위치 찾기
    String first = receivedString.substring(0, firstIndex); // 첫 번째 문자열
    String second = receivedString.substring(firstIndex + 1, secondIndex); // 두 번째 문자열
    String third = receivedString.substring(secondIndex);

    water_state = first.toInt(); // 물 수위 상태값
    gas_state = second.toInt(); // 일산화탄소 상태값
    flame_state = third.toInt();   // 불꽃 감지 상태값
  }


  if(water_state != 0 && gas_state != 0 || flame_state != 0) {
    if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
      String getStr = "GET /update?api_key=";
      getStr += apiKey;
      getStr += "&field1=";
      getStr += String(water_state);
      getStr += "&field2=";
      getStr += String(gas_state);
      getStr += "&field3=";
      getStr += String(flame_state);
      getStr += "\r\n\r\n";
      client.print(getStr + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
      Serial.println("물 상태: " + String(water_state) + ", 가스 상태: " + String(gas_state) + ", 불꽃 상태: " + String(flame_state));
    }
  }
  client.stop();
  delay(10);  // thing speak는 15초마다 데이터를 받음.여유있게 17초로..
}