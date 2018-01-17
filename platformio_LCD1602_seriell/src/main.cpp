/********************************************************************
 * platformio_LCD1602_seriell
 * ESP32 -- funzt
 * alternative "LiquidCrystal_I2C.h" von "iotsharing dotcom" benutzen
 * "http://www.iotsharing.com/2017/05/how-to-use-arduino-esp32-to-display-i2c-lcd.html"
 * oder "https://github.com/nhatuan84/esp32-lcd"
 * *****************************************************************/

#include <Wire.h> 
//#include <esp32-hal.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2,LCD_5x8DOTS);//PCF8574-Addresseeinstellung beachten! 0x20 for LCD1602 
//LiquidCrystal_I2C lcd(0x27,20,4,LCD_5x8DOTS);//PCF8574-Addresseeinstellung beachten! 0x27 for LCD2004

void lcd_demo(void);

 int show = 0;
 //**************************************************************
void setup_LCD_ser(){ 
//  lcd.begin(32, 33);// initialize the lcd with SDA and SCL pins
  lcd.begin();    // initialize the lcd with SDA, SCL pins
  lcd.clear();
  lcd.cursor_off();
  lcd.blink_off();
  lcd.leftToRight();
  lcd.noDisplay();
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("0-Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("1-by EasyIoT");
  /*lcd.setCursor(0,2);
  lcd.print("2-Hallo Spandau!");*/
  lcd.setCursor(0,2);
  lcd.print("3-Software by Sy");
  lcd.setCursor(0,3);
  lcd.print("4-ende setup");
  lcd.backlight();
  lcd.display();
  delay(2000);
}
//***************************************************************
void setup(){ 
  setup_LCD_ser();
}
//###############################################################
void loop(){
  //show = 0;
  lcd_demo();
}
//###############################################################
void lcd_demo(void){
   if (show == 0) {
         lcd.clear();

    lcd.backlight();//on
    lcd.home(); lcd.clear();
    lcd.print("0 Hello LCD");
    delay(1000);

   // lcd.setBacklight(0);  //off
    delay(400);
    lcd.setBacklight(1);  //ist gleich : lcd.backlight();

  } else if (show == 1) {
    lcd.clear();
    lcd.print("1 Cursor On --");
    lcd.cursor();

  } else if (show == 2) {
    lcd.clear();
    lcd.print("2 Cursor Blink");
    lcd.blink();

  } else if (show == 3) {
    lcd.clear();
    lcd.print("3 Cursor OFF");
    lcd.noBlink();
    lcd.noCursor();

  } else if (show == 4) {
    lcd.clear();
    lcd.print("4 Display Off");
    delay(3000);
    lcd.noDisplay();

  } else if (show == 5) {
    lcd.clear();
    lcd.print("5 Display On");
    lcd.display();

  } else if (show == 7) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("7 *** first line.");
    lcd.setCursor(0, 1);
    lcd.print("7 *** second line.");

  } else if (show == 8) {
    lcd.scrollDisplayLeft();
  } else if (show == 9) {
    lcd.scrollDisplayLeft();
  } else if (show == 10) {
    lcd.scrollDisplayLeft();
  } else if (show == 11) {
    lcd.scrollDisplayRight();
  } // if

  delay(2000);
  show = (show + 1) % 12;
}//ende lcd_demo()
//***************************************************************

//eof