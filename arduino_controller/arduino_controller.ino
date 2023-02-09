#include <ShiftRegister74HC595.h>
ShiftRegister74HC595<2> sr(6, 4, 5);

#define DATA1 9

#define LATCH1 8

#define CLOCK1 7
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>
#include <TM1637Display.h>


#define CLK 2
#define DIO 3


TM1637Display display(CLK, DIO);

const int SPEEDO_PIN     = A1;
const int RPM_PIN        = A0;
const int fuel_pin       = A2;
const int SOUND_SIGN     = A3;

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

  

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setSegments(data);
  delay(500);
  sr.setAllHigh(); // set all pins HIGH
  delay(500);
  
  sr.setAllLow(); // set all pins LOW
  delay(500); 

  digitalWrite(SOUND_SIGN, 0);
  delay(500);
  speedo.write(0);
  rpm.write(0);
  fuel.write(0);
  uint8_t  data2 [] = {0x40, 0x76, 0x06, 0x40}; // -HI-
  display.setSegments(data2);
 
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
 
  lcd.clear();
  lcd.print("Wait");
  // Wait a second to ensure serial data isn't from re-programming
  delay(500);
  lcd.clear();
  lcd.print("Ready");
 

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
  
  serial_byte = Serial.read();
  Show_Gear(serial_byte);
  

  // Truck lights byte
  byte num1 = Serial.read();
  byte num2  = Serial.read();
 uint8_t pinValues[] = { num1,num2 }; 
  sr.setAll(pinValues); 
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
