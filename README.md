# CIGARETTE

CIGARETTE는 불꽃·이산화탄소 센서를 활용하여 초기 화재 징후를 감지하고, LoRa 통신을 통해 데이터를 전송한 뒤, 자동 소화장치로 즉시 대응할 수 있는 스마트 화재 감시 시스템입니다.

---

## 주요 기능

- **실시간 화재 감지**
  - 불꽃 감지 센서, 일산화탄소 센서 등 여러 센서를 Arduino에 연결하여 데이터 수집
  - 센서 민감도 및 임계값 조정으로 오작동 최소화
  - 화재 감지 시 릴레이를 통해 자동 소화 장치 작동

- **원거리 데이터 전송**
  - LoRa 모듈을 활용하여 센서 데이터를 원거리 게이트웨이로 전송
  - 저전력, 광역 통신 환경 구현
  - 산불 감시 등 확장 가능

- **실시간 데이터 모니터링**
  - ThingSpeak 플랫폼과 연동하여 데이터 실시간 업로드 및 저장
  - 업로드된 데이터를 대시보드에서 시각화
  - 경고 임계값 설정 및 알림 기능 제공

---

## 사용 기술

- **Embedded Platform:** Arduino UNO / Mega  
- **Sensors:** 불꽃 감지 센서, 일산화탄소 감지 센서, 물수위 센서  
- **Communication Module:** LoRa  
- **Database / Visualization:** ThingSpeak  

---

## 시스템 구조

1. Arduino 기반 센서 데이터 수집 및 임베디드 시스템 개발  
2. LoRa 통신 모듈을 활용한 안정적인 원거리 데이터 전송  
3. ThingSpeak API를 통한 실시간 데이터 업로드 및 시각화  
4. 화재 감지 시 자동 소화 장치 즉시 작동  

---

## 프로젝트 효과

- 초기 화재 징후를 빠르게 감지하여 피해 최소화  
- 원거리 통신으로 광역 화재 모니터링 가능  
- 실시간 데이터 모니터링으로 관리자 대응 효율 향상  

---

Hardware Structure

![Hardware Structure](https://github.com/HS-Donguk/IoT-CommunicationSystem-Project/assets/145684303/827ffc23-c100-4493-a25e-18a88cab2512)

Communication Structure

![Communication Structure](https://github.com/HS-Donguk/IoT-CommunicationSystem-Project/assets/145684303/d5f0a187-498f-4812-a7cd-1b9010dee2c9)

Total Structure

![Total Structure](https://github.com/HS-Donguk/IoT-CommunicationSystem-Project/assets/145684303/a95204b6-f86a-4c67-a1e8-8d6aab22b9dc)

---

## 시스템 시연 영상

[불꽃센서로 인해 물 자동 분사되는 영상](https://www.youtube.com/watch?v=tGuDu_nD8B4)

[가스센서로 인해 물 자동 분사되는 영상](https://www.youtube.com/watch?v=M8j3APLQdoY)

---
