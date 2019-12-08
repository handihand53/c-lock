// Include application, user and local libraries
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

uint16_t x, y;
boolean flag = false;

static uint8_t PROGMEM code[5060];

// Setup
void setup() {
  hspi.begin();
  tft.begin(hspi);
  Serial.begin(115200);
}
int count =0;

void loop() {
  tft.clear();
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 1, 0, "ajkjkQWEIROOIads");

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
  while(true);
}
