
/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 * 
 * This example is for FirebaseESP32 Arduino library v 3.5.0 and later
 *
*/

//This example shows how to read, store and update database using get, set, push and update functions.

#include <WiFi.h>
#include <FirebaseESP32.h>


#define FIREBASE_HOST "c-lock-iot.firebaseio.com"
#define FIREBASE_AUTH "O3nDMGOWrNoAilWP7zOEP9BPcqkGqC1SvIEF18NR"
#define WIFI_SSID "KeluargaHermawan"
#define WIFI_PASSWORD "123123123"

//Define FirebaseESP32 data object
FirebaseData firebaseData;

FirebaseJson json;

void printResult(FirebaseData &data);

void setup()
{
  String id="";
  String jamStart="";
  String jamEnd="";
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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  if (Firebase.getJSON(firebaseData, "/Booking/2019122/"))
  {
    //Success, then try to read the JSON payload value
    Serial.println(firebaseData.jsonString());
    id=firebaseData.jsonString().substring(2,18);    
  }
  else
  {
    //Failed to get JSON data at defined database path, print out the error reason
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.getString(firebaseData, "/Booking/2019122/"+id+"/jamStart"))
  {
    //Success, then try to read the JSON payload value
    Serial.print("Mulai dari jam: ");
    jamStart=firebaseData.stringData();
    Serial.println(firebaseData.stringData());    
  }
  else
  {
    //Failed to get JSON data at defined database path, print out the error reason
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.getString(firebaseData, "/Booking/2019122/"+id+"/jamEnd"))
  {
    //Success, then try to read the JSON payload value
    Serial.print("Berakhir jam: ");
    jamEnd=firebaseData.stringData();
    Serial.println(firebaseData.stringData());    
  }
  else
  {
    //Failed to get JSON data at defined database path, print out the error reason
    Serial.println(firebaseData.errorReason());
  }
   
}

void printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson &json = data.jsonObject();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == JSON_OBJECT ? "object" : "array");
      if (type == JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json.iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray &arr = data.jsonArray();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData &jsonData = data.jsonData();
      //Get the result data from FirebaseJsonArray object
      arr.get(jsonData, i);
      if (jsonData.typeNum == JSON_BOOL)
        Serial.println(jsonData.boolValue ? "true" : "false");
      else if (jsonData.typeNum == JSON_INT)
        Serial.println(jsonData.intValue);
      else if (jsonData.typeNum == JSON_DOUBLE)
        printf("%.9lf\n", jsonData.doubleValue);
      else if (jsonData.typeNum == JSON_STRING ||
               jsonData.typeNum == JSON_NULL ||
               jsonData.typeNum == JSON_OBJECT ||
               jsonData.typeNum == JSON_ARRAY)
        Serial.println(jsonData.stringValue);
    }
  }
}

void loop()
{
}
