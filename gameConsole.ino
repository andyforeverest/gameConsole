#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

byte backCar[] = {0x00, 0x00, 0x03, 0x06, 0x1C, 0x1F, 0x06, 0x00};
byte frontCar[] = {0x00, 0x00, 0x10, 0x08, 0x07, 0x1F, 0x0C, 0x00};

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.print("   Game console");
  delay(3000);
  lcd.clear();
  lcd.createChar(0, backCar);
  lcd.createChar(1, frontCar);
}
int carRow = 0;
unsigned long timp = 0;
void loop() {
  if (millis() - timp >= 100) {
    timp = millis();
    int tasta = citesteTasta();
    if (tasta == 2 && carRow != 0) {
      lcd.setCursor(1, carRow);
      lcd.print("  ");
      carRow = 0;
    }
    if (tasta == 3 && carRow != 1) {
      lcd.setCursor(1, carRow);
      lcd.print("  ");
      carRow = 1;
    }
  }
  afisare();
}

void afisare() {
  lcd.setCursor(1, carRow);
  lcd.write((byte)0);
  lcd.write((byte)1);
}

int citesteTasta() {
  int valoare = analogRead(A0);
  if (valoare < 450 && valoare > 400) {
    //Serial.println("SELECT"); //SW5
    return 5;
  }
  else if (valoare < 250 && valoare > 200) {
    //Serial.println("RIGHT"); //SW4
    return 4;
  }
  else if (valoare < 150 && valoare > 100) {
    //Serial.println("DOWN"); //SW3
    return 3;
  }
  else if (valoare < 30 && valoare > 5) {
    //Serial.println("LEFT"); //SW1
    return 1;
  }
  else if (valoare < 90 && valoare > 40) {
    //Serial.println("UP");//sw2
    return 2;
  }
  else if (valoare > 1010) {
    //Serial.println("NONE");
    return 0;
  }
  else {
    //Serial.println("UNDEFINED");
    return -1;
  }
}
