/*
 * 2015.08.04 최종버전
 * multiwii 보드와 통신하는 최신버전
 */
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "AndroidHotspot1623";
const char* password = "sh606204";
const char* ServerIp = "192.168.43.247";
const int ServerPort = 7775;


//static uint8_t inBuf[64];

//시리얼 버퍼 초기화
char inData[128]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
int SerialBufferCnt = 0; // Index into array; where to store the character
unsigned int localUdpPort = 7777;
int i = 0;

WiFiUDP udp;

String jsondata ="";
static uint8_t offset;
static uint8_t dataSize;

void setup()
{
  
  //시리얼 통신 초기화
  Serial.begin(115200);//시리얼 통신속도

  WiFi.begin(ssid, password);
  udp.begin(localUdpPort);
}
void loop() 
{
  while(Serial.available() > 0)
  {
      delayMicroseconds(100);
      inData[SerialBufferCnt] = Serial.read(); //시리얼 데이터를 버퍼에 넣는다
      SerialBufferCnt++; // 버퍼카운터 증가
      if(SerialBufferCnt >= 256) SerialBufferCnt = 0; //버퍼가 128개가 넘어가면 버퍼카운터 초기화
  }

  //시리얼 수신버퍼에 데이터가 있으면
  if(SerialBufferCnt > 0)
  {
      udp.beginPacket(ServerIp,ServerPort); //192.168.4.2는 휴대폰의 IP, 포트는 입력받은 포트
      for (int i=0;i<SerialBufferCnt;i++)
      {
        Serial.write(inData[i]);
          udp.write(inData[i]); //시리얼 -> udp 로 전송
      }
      udp.endPacket();
      
      SerialBufferCnt = 0; //버퍼 카운터 초기화
  }
}
/*
void loop() 
{
  if(Serial.available() > 0)
  {
   jsondata = Serial.readString();
   udp.beginPacket(ServerIp,ServerPort);
   jsondata.toCharArray(inData,128);
   udp.write(inData,strlen(inData));
   //udp.write(inData,1024);
   udp.endPacket();
   jsondata = "";
  }
}*/
