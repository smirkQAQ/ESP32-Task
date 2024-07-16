#include <U8g2lib.h>
#include "../include/oled.h"

#define OLED_MOSI  23
#define OLED_SDA   21 // I2C DATA
#define OLED_SCL   22 // I2C CLK
#define OLED_SCK   18 // SPI CLK
#define OLED_CS    14
#define OLED_DC    27
#define OLED_RESET 26

// #ifdef U8X8_HAVE_HW_I2C
// #include <Wire.h>
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
// #endif

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);
#endif


void drawLogo(void)
{
    u8g2.setFontMode(1); // Transparent
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb24_mf);
    u8g2.drawStr(0, 30, "U");
    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_inb30_mn);
    u8g2.drawStr(21,8,"8");
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb24_mf);
    u8g2.drawStr(51,30,"g");
    u8g2.drawStr(67,30,"\xb2");
    u8g2.drawHLine(2, 35, 47);
    u8g2.drawHLine(3, 36, 47);
    u8g2.drawVLine(45, 32, 12);
    u8g2.drawVLine(46, 33, 12);
}

void drawURL(void)
{
  u8g2.setFont(u8g2_font_4x6_tr);
  if ( u8g2.getDisplayHeight() < 59 )  {
    u8g2.drawStr(89,20,"github.com");
    u8g2.drawStr(73,29,"/olikraus/u8g2");
  }
  else  {
    u8g2.drawStr(1,54,"github.com/olikraus/u8g2");
  }
}

void gpio_init(void) {
  
}

void oled_init(void) {
  Serial.begin(115200);

  Serial.println();

  SPI.begin(); //SCLK, MISO, MOSI, SS
  u8g2.begin();
}

void run(void) {
  uint32_t st = millis();

  u8g2.clearBuffer();

  drawLogo();

  drawURL();

  u8g2.sendBuffer();

  Serial.println(millis()-st);

  delay(1000);
}
