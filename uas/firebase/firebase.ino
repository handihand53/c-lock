#include <WiFi.h>
#include <FirebaseESP32.h>
#include "time.h"

#define FIREBASE_HOST "c-lock-iot.firebaseio.com"
#define FIREBASE_AUTH "O3nDMGOWrNoAilWP7zOEP9BPcqkGqC1SvIEF18NR"
#define WIFI_SSID "KeluargaHermawan"
#define WIFI_PASSWORD "123123123"

const char* ntpServer = "id.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

FirebaseData firebaseData;
FirebaseJson json;

String jam="";
String tgl="";
String id="";
String jamStart="";
String jamEnd="";
String Path="";
String token[3];
String waktu[3];


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

  String s="";
  for(int i=0;i<50;i++) s+=timeStringBuff;
  
  tgl = s.substring(0,8);
  String h = s.substring(9,11);
  int x = h.toInt();
  x+=6;
  String jamA=x+s.substring(11,17);;
  if(x<10)
    jam = "0" + jamA;
  else
    jam = jamA;

}


void printResult(FirebaseData &data);

void setup()
{
  Serial.begin(115200); 
  char compilationDate[] = __DATE__;
  char compilationTime[] = __TIME__;
  Serial.println("Compilation date:");
  Serial.println(compilationDate);
  Serial.println("Compilation time: ");
  Serial.println(compilationTime);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

void getDataFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

//  if (Firebase.getJSON(firebaseData, "/Booking/"+tgl+"/"))
//  {
//    //Success, then try to read the JSON payload value
//    Serial.println(firebaseData.jsonString());
//    id=firebaseData.jsonString().substring(2,18);    
//  }
//  else
//  {
//    //Failed to get JSON data at defined database path, print out the error reason
//    Serial.println(firebaseData.errorReason());
//  }

  if (Firebase.getJSON(firebaseData, "/Booking/20191202/"))
  {
    printResult(firebaseData);
    if(jam>"07:00:00" && jam<"10:30:00"){
      for(int i=0;i<3;i++){
        if(waktu[i]=="1"){
          id=token[i];
          break;
        }
      }
    }else if(jam>"10:30:00" && jam<"13:30:00"){
      for(int i=0;i<3;i++){
        if(waktu[i]=="2"){
          id=token[i];
          break;
        }
      }
    }else if(jam>"10:30:00" && jam<"13:30:00"){
      for(int i=0;i<3;i++){
        if(waktu[i]=="3"){
          id=token[i];
          break;
        }
      }
    }
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.getString(firebaseData, "/Booking/"+tgl+"/"+id+"/jamStart"))
  {
    Serial.print("Mulai dari jam: ");
    jamStart=firebaseData.stringData();
    Serial.println(firebaseData.stringData());    
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.getString(firebaseData, "/Booking/"+tgl+"/"+id+"/jamEnd"))
  {
    Serial.print("Berakhir jam: ");
    jamEnd=firebaseData.stringData();
    Serial.println(firebaseData.stringData());    
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
}

void printResult(FirebaseData &data)
{
    FirebaseJson &json = data.jsonObject();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    int jml=0;
    int jml2=0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      if (type == JSON_OBJECT)
      {
        if(key=="rid"){
          token[jml]=value;
          jml++;
        }

        if(key=="waktu"){
          waktu[jml2]=value;
          jml2++;
        }
      }
    }
    json.iteratorEnd();
}

void loop()
{
  delay(1000);
  printLocalTime();
  getDataFirebase();
  Serial.println(tgl);
  Serial.println(jam);
  Serial.println(id);
}
