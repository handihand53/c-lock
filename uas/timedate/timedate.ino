#include <WiFi.h>
#include "time.h"

const char* ssid       = "KeluargaHermawan";
const char* password   = "123123123";

const char* ntpServer = "id.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

//void printLocalTime()
//{
//  struct tm timeinfo;
//  if(!getLocalTime(&timeinfo)){
//    Serial.println("Failed to obtain time");
//    return;
//  }
//  Serial.println(&timeinfo, "%Y%m%e %H:%M:%S");
//}

void printLocalTime()
{
  time_t rawtime;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
   return;
  }
  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y%m%d %H:%M:%S", &timeinfo);
  //print like "const char*"
//  String asString(timeStringBuff);
  String s="";
  for(int i=0;i<50;i++) s+=timeStringBuff;
  
  String tgl = s.substring(0,8);
  String h = s.substring(9,11);
  int x = h.toInt();
  x+=6;
  String jam = x+s.substring(11,17);
  Serial.println(tgl);
  Serial.println(jam);
  Serial.println(timeStringBuff);

  //Optional: Construct String object 
  
}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
