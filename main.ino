#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
#define TFT_CS         14
#define TFT_RST        15
#define TFT_DC         32

#elif defined(ESP8266)
#define TFT_CS         0
#define TFT_RST        2
#define TFT_DC         15

#else
// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
#endif
//------------------------------
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);
  #define RGB(r, g, b) ((( r & 0xF8 ) << 8)|(( g & 0xFC ) << 3 )|( b >> 3 ))


  #define BLACK       RGB(  0,   0,   0)
  #define AQUAMARINE  RGB(127, 255, 212)
  #define GREY        RGB(128, 128, 128)
  #define DARKGREY    RGB(169, 169, 169)
  #define LIGHTGREY   RGB(211, 211, 211)
  #define TURQUOISE   RGB( 64, 224, 208)
  #define PINK        RGB(255, 128, 192)
  #define OLIVE       RGB(128, 128,   0)
  #define PURPLE      RGB(128,   0, 128)
  #define AZURE       RGB(  0, 128, 255)
  #define ORANGE      RGB(255, 128,  64)
  #define CYAN        RGB(  0, 255, 255)
  #define DARKCYAN    RGB(  0, 139, 139)
  #define RED         RGB(255,   0,   0)
  #define YELLOW      RGB(255, 255,   0)
  #define WHITE       RGB(255, 255, 255)
  #define BLUE        RGB(  0,   0, 255)
  #define GREEN       RGB(  0, 255,   0)
}

void loop() {
  tft.setRotation(1);     
  tft.fillScreen(BLACK);                           // blanking display
  tft.drawRect(0, 0, tft.width(), 76, WHITE);      // draw rectangle (x, y, w, h, color)
  tft.fillRect(0, 0, 16, 76, WHITE);
  tft.fillRect(3, 12, 10, 52, BLACK);
  tft.setTextSize(1);                              // text size = 1
  tft.setTextColor(CYAN, BLACK);                   // set text color to cyan and black background
  tft.setCursor(5, 14);                            // move cursor to position (5, 14) pixel
  tft.print( "T" );
  tft.setCursor(5, 24);                            // move cursor to position (5, 24) pixel
  tft.print( "E" );
  tft.setCursor(5, 34);                            // move cursor to position (5, 34) pixel
  tft.print( "M" );
  tft.setCursor(5, 44);                            // move cursor to position (5, 44) pixel
  tft.print( "P" );
  tft.setCursor(5, 54);                            // move cursor to position (5, 54) pixel
  tft.print( "E" );
  main_part();
}
void main_part() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  tft.setTextSize(3);                                // text size = 3
  tft.setCursor(26, 49);                             // move cursor to position (26, 49) pixel
  tft.setTextColor(LIGHTGREY, BLACK);                // set text color to lightgrey and black background
  tft.print(temp.temperature);
  delay(500);
}
