#include <WiFi.h>
#include <FirebaseESP32.h>
#include "time.h"
#include <HCSR04.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define FIREBASE_HOST "c-lock-iot.firebaseio.com"
#define FIREBASE_AUTH "O3nDMGOWrNoAilWP7zOEP9BPcqkGqC1SvIEF18NR"
#define WIFI_SSID "KeluargaHermawan"
#define WIFI_PASSWORD "123123123"

#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include "qrcode.h"

#define TFT_RST 26  // IO 26
#define TFT_RS  25  // IO 25
#define TFT_CLK 14  // HSPI-SCK
//#define TFT_SDO 12  // HSPI-MISO
#define TFT_SDI 13  // HSPI-MOSI
#define TFT_CS  15  // HSPI-SS0
#define TFT_LED 0   // 0 if wired to +5V directly
SPIClass hspi(HSPI);

#define TFT_BRIGHTNESS 200 
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);
const char* ntpServer = "id.pool.ntp.org";

UltraSonicDistanceSensor distanceSensor(4, 5);  // trigger, echo
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

FirebaseData firebaseData;
FirebaseJson json;

int pin = 2;
String jam="";
String tgl="";
String id="";
String jamStart="";
String jamEnd="";
String Path="";
String token[3];
String waktu[3];
String stats[3];
String lab[3];

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

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

void printQRCode();
void printResult(FirebaseData &data);

void setup()
{
  hspi.begin();
  tft.begin(hspi);
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
  pinMode(pin, OUTPUT);

  //display lcd
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
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

  if (Firebase.getJSON(firebaseData, "/Booking/"+tgl+"/"))
  {
    printResult(firebaseData);
    if(jam>"07:00:00" && jam<"10:30:00"){
      for(int i=0;i<3;i++){
        if(waktu[i]=="1" && lab[i]=="a"){
          id=token[i];
          Serial.println(stats[i]);
          if(stats[i]=="1"){
            digitalWrite(pin,HIGH);
            lcd.clear();
            //DISPLAY LCD
            lcd.setCursor(1,0);
            lcd.print("SILAHKAN MASUK");
            if(distanceSensor.measureDistanceCm()>=15){
              Firebase.setString(firebaseData, "/Booking/"+tgl+"/"+id+"/pintu", "Terbuka");
              Serial.println("terbuka gitu");
              lcd.setCursor(1,1);
              lcd.print("Pintu Terbuka");
            }
            else if(distanceSensor.measureDistanceCm()<15){
//              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Pintu Tertutup");
            }
          }else if(stats[i]=="0"){
            digitalWrite(pin,LOW);
            lcd.clear();
            //DISPLAY LCD
            lcd.setCursor(1,0);
            lcd.print("SUDAH KELUAR");
            lcd.setCursor(1,1);
            lcd.print("C-Lock");
          }
          break;
        }
      }
    }else if(jam>"10:30:00" && jam<"13:30:00"){
      for(int i=0;i<3;i++){
        if(waktu[i]=="2" && lab[i]=="a"){
          id=token[i];
          if(stats[i]=="1"){
            digitalWrite(pin,HIGH);
            lcd.clear();
            //DISPLAY LCD
            lcd.setCursor(1,0);
            lcd.print("SILAHKAN MASUK");
            if(distanceSensor.measureDistanceCm()>=15){
              Firebase.setString(firebaseData, "/Booking/"+tgl+"/"+id+"/pintu", "Terbuka");
              Serial.println("terbuka gitu");
              lcd.setCursor(1,1);
              lcd.print("Pintu Terbuka");
            }
            else if(distanceSensor.measureDistanceCm()<15){
//              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Pintu Tertutup");
            }
          }else if(stats[i]=="0"){
            digitalWrite(pin,LOW);
            lcd.clear();
            //DISPLAY LCD
            lcd.setCursor(1,0);
            lcd.print("SUDAH KELUAR");
            lcd.setCursor(1,1);
            lcd.print("C-Lock");
          }
          break;
        }
      }
    }else if(jam>"13:30:00" && jam<"17:30:00"){
      for(int i=0;i<3;i++){
        if(waktu[i]=="3" && lab[i]=="a"){
          id=token[i];
          Serial.println(stats[i]);
          if(stats[i]=="1"){
            digitalWrite(pin,HIGH);
            lcd.clear();
            //DISPLAY LCD
            lcd.setCursor(1,0);
            lcd.print("SILAHKAN MASUK");
            if(distanceSensor.measureDistanceCm()>=15){
              Firebase.setString(firebaseData, "/Booking/"+tgl+"/"+id+"/pintu", "Terbuka");
              Serial.println("terbuka gitu");
//              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Pintu Terbuka");
            }
            else if(distanceSensor.measureDistanceCm()<15){
//              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Pintu Tertutup");
            }
          }else if(stats[i]=="0"){
            digitalWrite(pin,LOW);
            lcd.clear();
            //DISPLAY LCD
            lcd.setCursor(1,0);
            lcd.print("SUDAH KELUAR");
            lcd.setCursor(1,1);
            lcd.print("C-Lock");
          }
          break;
        }
      }
    }else{
      id="";
    }
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }

//  if (Firebase.getString(firebaseData, "/Booking/"+tgl+"/"+id+"/jamStart"))
//  {
//    Serial.print("Mulai dari jam: ");
//    jamStart=firebaseData.stringData();
//    Serial.println(firebaseData.stringData());    
//  }
//  else
//  {
//    Serial.println(firebaseData.errorReason());
//  }
//
//  if (Firebase.getString(firebaseData, "/Booking/"+tgl+"/"+id+"/jamEnd"))
//  {
//    Serial.print("Berakhir jam: ");
//    jamEnd=firebaseData.stringData();
//    Serial.println(firebaseData.stringData());    
//  }
//  else
//  {
//    Serial.println(firebaseData.errorReason());
//  }
}

void printResult(FirebaseData &data)
{
    FirebaseJson &json = data.jsonObject();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    int jml=0;
    int jml2=0;
    int jml3=0;
    int jml4=0;
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
        if(key=="status"){
          stats[jml3]=value;
          jml3++;
        }
        if(key=="lab"){
          lab[jml4]=value;
          jml4++;
        }
      }
    }
    json.iteratorEnd();
}

void loop()
{
  delay(200);
  printLocalTime();
  getDataFirebase();
  Serial.println(tgl);
  Serial.println(jam);
  Serial.println(id);
  Serial.println(distanceSensor.measureDistanceCm());
}

void printQRCode(){
  tft.clear();
  if(id!=""){
    uint16_t x, y;
    boolean flag = false;
    uint8_t PROGMEM code[5060];
    int count =0;
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    const char* tokenId = id.c_str();
    qrcode_initText(&qrcode, qrcodeData, 1, 0, tokenId);
  
     for (uint8_t y = 0; y < qrcode.size; y++) {
      for(int i=0;i<8;i++){
        for (uint8_t x = 0; x < qrcode.size; x++) {
          qrcode_getModule(&qrcode, x, y) ? code[count]=0x0 : code[count]=0xff;
          count++;
        }
      }
    }
  
    for(int i=0;i<1000;i++){
      code[count]=0xff;
      count++;
    }
    Serial.print("wait");
    tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
    tft.drawRectangle(1, 1, tft.maxX() - 2, tft.maxY() - 2, COLOR_WHITE);
    tft.drawRectangle(2, 2, tft.maxX() - 3, tft.maxY() - 3, COLOR_WHITE);
    tft.drawRectangle(3, 3, tft.maxX() - 4, tft.maxY() - 4, COLOR_WHITE);
  
    tft.drawBitmap(4, 4, code, 168, 220, COLOR_WHITE);
  }
}
