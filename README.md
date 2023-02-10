# CatTowerIot-Capstone-design-grand-prize-project

## 캣타워 조직도
### -시제품 단계이므로 현재는 어플의 블루투스 통신으로 캣타워 IOT에 접속이 가능합니다.
### -실시간 반려동물의 생체정보 및 반려동물의 CCTV를 실시간으로 확인할 수 있습니다.

![image](https://user-images.githubusercontent.com/58325946/199742046-0ff5da96-e917-4e7a-aee4-311ad8c245b7.png)
![image](https://user-images.githubusercontent.com/58325946/199742882-79062269-0b5f-4434-a2f2-28faa4b37db4.png)

## 개선된 사항들
### -버전 1.0v에서의 어플 디자인이 시각화적으로 예쁘지 않았다는 점, 단순화되지 않았다는 점을 고려하여 HTML을 이용한 도넛형태의 차트 데이터로 변경하였습니다.
### -소리센서의 무분별한 데이터 수집을 막기위하여 소리 데이터를 PID제어와 비슷한 방식으로 평균화하여 코드 수정을 통한 노이즈 필터링 기능 추가, 3미터 반경에서 100데시벨 이상의 소음이 발생하여도 노이즈를 필터링하여 1분 단위의 호흡수 데이터를 수집합니다.
### -무게센서의 오차를 여러번의 코드 수정을 통해 그람수까지 정밀하게 개선하였습니다.

## 차후 개선사항
### -라즈베리파이에서 WIFI의 포트포워딩 or VPN을 통해 외부에서 어플로 접속이 가능합니다.
### -만능기판에서 PCB제작을 통한 제품 소형화 및 재료 절감이 가능합니다.
### -앱인벤터로 제작하여 안드로이드 9.0버전 이상의 API변경 이슈를 해결하지 못하였으나, 추후에 Android Studio 앱 개발을 통한 API문제 해결가능.

![image](https://user-images.githubusercontent.com/58325946/216480279-606f5f38-0ead-43e2-914e-90360d437953.png)

![image](https://user-images.githubusercontent.com/58325946/217686138-7151c0ce-3a88-4792-84f9-aad3b24d39e2.png)
