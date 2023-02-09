#include <ShiftRegister74HC595.h>
ShiftRegister74HC595<2> sr(6, 4, 5);
//#define DATA 6
//
//#define LATCH 5
//
//#define CLOCK 4
#define DATA1 9

#define LATCH1 8

#define CLOCK1 7
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
//#include <Adafruit_GFX.h>  // Include core graphics library for the display
//#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
//Adafruit_SSD1306 display;  // Create display
//#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

TM1637Display display(CLK, DIO);

const int SPEEDO_PIN     = A1;
const int RPM_PIN        = A0;
const int fuel_pin       = A2;
const int SOUND_SIGN     = A3;
//const int LEFT_SIGN      = 2;
//const int RIGHT_SIGN     = 3;
//const int HIGHT_BEEM     = 4;
//const int LOW_BEEM       = 5;
//const int LOW_FUEL       = 6;
//const int BREAK          = 7;
//
//const int LOI            = 12;
//const int W_SPEED        = 11;
//const int W_RPM          = 13;
// Servo variables
Servo speedo;
Servo rpm;
Servo fuel;


#define PACKET_SYNC 0xFF
#define PACKET_VER 2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true
const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
int serial_byte;

LiquidCrystal_I2C lcd(0x27, 16, 2);
byte xang[] = {
  B11111,
  B10001,
  B11111,
  B01110,
  B01110,
  B01110,
  B01110,
  B11111
};
byte canso[] = {
  B10101,
  B10101,
  B10101,
  B10101,
  B11111,
  B10100,
  B10100,
  B10100
};
byte tocdo[] = {
  B00001,
  B00010,
  B01110,
  B01010,
  B01010,
  B01110,
  B01000,
  B10000
};
void setup() {
  Serial.begin(115200);
  display.setBrightness(0x0f);
  lcd.init();
  lcd.begin(16, 2);  //IGNORE THIS LINE
  lcd.backlight();
  lcd.print("Self Test");
  lcd.createChar(0, xang);
  lcd.createChar(1, canso);
  lcd.createChar(2, tocdo);
  // Initialise servos
  speedo.attach(SPEEDO_PIN);
  speedo.write(180);
  fuel.attach(fuel_pin);

  fuel.write(100);

  rpm.attach(RPM_PIN);
  rpm.write(180);
  // Initialise LEDs
  //  pinMode(LEFT_SIGN, OUTPUT);
  //  pinMode(RIGHT_SIGN, OUTPUT);
  //  pinMode(HIGHT_BEEM, OUTPUT);
  //  pinMode(LOW_BEEM, OUTPUT);
  //  pinMode(LOW_FUEL, OUTPUT);
  //  pinMode(BREAK, OUTPUT);

//  pinMode(LATCH, OUTPUT);
//
//  pinMode(CLOCK, OUTPUT);
//
//  pinMode(DATA, OUTPUT);
    pinMode(LATCH1, OUTPUT);

  pinMode(CLOCK1, OUTPUT);

  pinMode(DATA1, OUTPUT);

//  pinMode(LOI, OUTPUT);
  pinMode(SOUND_SIGN, OUTPUT);

 sr.setAllHigh(); // set all pins HIGH
  delay(500);
  
  sr.setAllLow(); // set all pins LOW
  delay(500); 
  
  
  
  // set all pins at once
  uint8_t pinValues[] = { B10101010 }; 
  sr.setAll(pinValues); 
  delay(2000);
uint8_t pinValues1[] = { B00000001,B00000001 }; 
  sr.setAll(pinValues1); 
  delay(2000);

  
//  pinMode(W_SPEED, OUTPUT);
//  pinMode(W_RPM, OUTPUT);
  //  digitalWrite(LEFT_SIGN, 0);
  //  digitalWrite(RIGHT_SIGN, 0);
  //  digitalWrite(HIGHT_BEEM, 0);
  //  digitalWrite(LOW_BEEM, 0);
  //  digitalWrite(LOW_FUEL, 0);
  //  digitalWrite(BREAK, 0);
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setSegments(data);
  delay(500);
  sr.setAllHigh(); // set all pins HIGH
  delay(500);
  
  sr.setAllLow(); // set all pins LOW
  delay(500); 
//  digitalWrite(LATCH, LOW);
//
//  shiftOut(DATA, CLOCK, LSBFIRST, 0b11111111);
//
//  digitalWrite(LATCH, HIGH);
//
//  delay(200);
//  digitalWrite(LATCH, LOW);
//
//  shiftOut(DATA, CLOCK, LSBFIRST, 0b00000000);
//
//  digitalWrite(LATCH, HIGH);
//
//  delay(200);
//  digitalWrite(LATCH, LOW);
//
//  shiftOut(DATA, CLOCK, LSBFIRST, 0b11111111);
//
//  digitalWrite(LATCH, HIGH);
//
//  delay(200);
//  digitalWrite(LATCH, LOW);
//
//  shiftOut(DATA, CLOCK, LSBFIRST, 0b00000000);
//
//  digitalWrite(LATCH, HIGH);
//
//  delay(200);
//  for (int i = 1; i < 256; i = i << 1)
//
//  {
//
//    digitalWrite(LATCH, LOW);
//
//    shiftOut(DATA, CLOCK, LSBFIRST, i);
//
//    digitalWrite(LATCH, HIGH);
//
//    delay(200);
//
//  }
//  for (int i = 256; i > 0; i = i >> 1)
//
//  {
//
//    digitalWrite(LATCH, LOW);
//
//    shiftOut(DATA, CLOCK, LSBFIRST, i);
//
//    digitalWrite(LATCH, HIGH);
//
//    delay(200);
//
//  }
//  digitalWrite(LATCH, LOW);
//
//  shiftOut(DATA, CLOCK, LSBFIRST,  0b00000000);
//
//  digitalWrite(LATCH, HIGH);
//  delay(1000);  digitalWrite(LATCH1, LOW);
//
//  shiftOut(DATA1, CLOCK1, LSBFIRST,  0b00000000);
//
//  digitalWrite(LATCH1, HIGH);
  //  digitalWrite(LOI, 0);
  digitalWrite(SOUND_SIGN, 0);
  delay(500);
  speedo.write(0);
  rpm.write(0);
  fuel.write(0);
  uint8_t  data2 [] = {0x40, 0x76, 0x06, 0x40}; // -HI-
  display.setSegments(data2);
  //  digitalWrite(LEFT_SIGN, 1);
  //  digitalWrite(RIGHT_SIGN, 1);
  //  digitalWrite(HIGHT_BEEM, 1);
  //  digitalWrite(LOW_BEEM, 1);
  //  digitalWrite(LOW_FUEL, 1);
  //  digitalWrite(BREAK, 1);
  //
  //  digitalWrite(LOI, 1);
  //  digitalWrite(SOUND_SIGN, 0);
  delay(500);
  for (int i = 0; i <= 180; i++) {
    speedo.write(i);
    delay(3);
  }

  for (int i = 0; i <= 180; i++) {
    rpm.write(i);
    delay(3);
  }
  fuel.write(100);
  //  digitalWrite(LEFT_SIGN, 0);
  //  digitalWrite(RIGHT_SIGN, 0);
  //  digitalWrite(HIGHT_BEEM, 0);
  //  digitalWrite(LOW_BEEM, 0);
  //  digitalWrite(LOW_FUEL, 0);
  //  digitalWrite(BREAK, 0);
  //
  //  digitalWrite(LOI, 0);
  //  digitalWrite(SOUND_SIGN, 0);
  lcd.clear();
  lcd.print("Wait");
  // Wait a second to ensure serial data isn't from re-programming
  delay(500);
  lcd.clear();
  lcd.print("Ready");
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
  //  display.clearDisplay();  // Clear the buffer
  //  display.setTextColor(WHITE);  // Set color of the text
  //  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
  //  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  //                               // To override this behavior (so text will run off the right side of the display - useful for
  //                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
  //                               // with setTextWrap(true).
  //  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)


  display.clear();
  uint8_t data3 [] = {0x40, 0x3d, 0x3f, 0x40};
  display.setSegments(data3);

}



void read_serial_byte_set_servo(Servo& servo, bool invert) {
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180 : serial_byte);
  if (invert)
    servo.write(180 - serial_byte);
  else
    servo.write(serial_byte);
}
void read_serial_byte_set_servo_fuel(Servo& servo, bool invert) {
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180 : serial_byte);
  if (invert)
    servo.write(100 - serial_byte);  //set lower than the tach and speedo to limit movement.
  else
    servo.write(serial_byte);
}
void skip_serial_byte() {
  (void)Serial.read();
}

void digitalWriteFromBit(int port, int value, int shift) {
  digitalWrite(port, (value >> shift) & 0x01);
}
void digitalWriteFromBit_sound(int port, int value) {
  int left_val = (value >> 5) & 0x01;
  int right_val = (value >> 4) & 0x01;
  int sound_val = left_val | right_val;
  digitalWrite(port, sound_val);
}
void Show_Gear(int value) {
  uint8_t gear [4];

  if (value > 0 && value < 10)
  {

    gear[0] = 0x5e;
    gear[1] = 0x40;
    gear[2] = 0x40;
    gear[3] = display.encodeDigit(value);
  }
  if (value >= 10 && value < 49)
  {

    gear[0] = 0x5e;
    gear[1] = 0x40;
    gear[2] = display.encodeDigit(value / 10);
    gear[3] = display.encodeDigit(value % 10);
  }
  if (value > 49)
  {
    value = value / 50;
    gear[0] = 0x40;
    gear[1] = 0x50;
    gear[2] = display.encodeDigit(value);;
    gear[3] = 0x40;
  }
  if (value == 0) {
    gear[0] = 0x40;
    gear[1] = 0x40;
    gear[2] = 0x37;
    gear[3] = 0x40;
  }
  display.setSegments(gear);
}
//void OLED() {
// serial_byte = Serial.read();
//  display.clearDisplay();  // Clear the display so we can refresh
//  display.setFont(&FreeMono9pt7b);  // Set a custom font
//  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
//  // Print text:
//  display.setCursor(0, 10);  // (x,y)
//  display.println("Hello");  // Text or value to print
//display.println(serial_byte);
//}
void loop() {

  if (Serial.available() < 16)
    return;

  serial_byte = Serial.read();
  if (serial_byte != PACKET_SYNC)
    return;

  serial_byte = Serial.read();
  if (serial_byte != PACKET_VER) {
    lcd.clear();
    lcd.print("PROTOCOL VERSION ERROR");
    return;
  }

  read_serial_byte_set_servo(speedo, SERVO_DIR_INVERT);  // Speed
  read_serial_byte_set_servo(rpm, SERVO_DIR_INVERT);     // RPM

  skip_serial_byte();                                       // Brake air pressure
  skip_serial_byte();                                       // Brake temperature
  read_serial_byte_set_servo_fuel(fuel, SERVO_DIR_INVERT);  // Fuel ratio
  skip_serial_byte();                                       // Oil pressure
  skip_serial_byte();                                       // Oil temperature
  skip_serial_byte();                                       // Water temperature
  skip_serial_byte();
  // Battery voltage
  serial_byte = Serial.read();
  Show_Gear(serial_byte);
  //skip_serial_byte();                                       //SHOW_GEAR

  // Truck lights byte
  byte num1 = Serial.read();

//  digitalWrite(LATCH, LOW);
//  shiftOut(DATA, CLOCK, LSBFIRST,  serial_byte);
//  digitalWrite(LATCH, HIGH);

byte num2  = Serial.read();
 uint8_t pinValues[] = { num1,num2 }; 
  sr.setAll(pinValues); 
//  digitalWrite(LATCH1, LOW);
//  shiftOut(DATA1, CLOCK1, LSBFIRST,  serial_byte);
//  digitalWrite(LATCH1, HIGH);
//  serial_byte = Serial.read();
//  digitalWriteFromBit_sound(A2, serial_byte);

  // Warning lights bytes

  skip_serial_byte();

  // Enabled flags
  serial_byte = Serial.read();

  // Text length
  int text_len = Serial.read();

  // Followed by text
  if (0 < text_len && text_len < 127) {
    lcd.clear();
    for (int i = 0; i < text_len; ++i) {
      while (Serial.available() == 0)  // Wait for data if slow
      {
        delay(2);
      }
      serial_byte = Serial.read();
      if (serial_byte < 0 && serial_byte > 127)
        return;

      if (serial_byte == '\n')
        lcd.setCursor(0, 1);
      else if (serial_byte == 'w')
        lcd.print(char(0));
      else if (serial_byte == 'q')
        lcd.print(char(1));
      else if (serial_byte == 'z')
        lcd.print(char(2));
      else
        lcd.print(char(serial_byte));
      //delay(2);
    }
  }
}
