#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte tank[] = {0x00, 0x0F, 0x08, 0x1E, 0x19, 0x1F, 0x1B, 0x1B};
byte obuz[] = {0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00};

void setup() {
  pinMode(A0, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, tank);
  lcd.createChar(1, obuz);
  Serial.begin(9600);
}

unsigned long timp = 0;
bool trage = false;
int tank_rand = 0;
int obuz_col = 2;
void loop() {
  if (millis() - timp >= 50) {
    timp = millis();
    int tasta = citesteTasta();
    if (tasta == 5 && trage == false) {
      trage = true;
      obuz_col = 2;
      Serial.println("fire");
    }
    if (tasta == 2 && tank_rand == 1) //UP
    {
      lcd.setCursor(1, 1);
      lcd.print(" ");
      tank_rand = 0;
    }

    if (tasta == 3 && tank_rand == 0) //DOWN
    {
      lcd.setCursor(1, 0);
      lcd.print(" ");
      tank_rand = 1;
    }


    if (trage == true) {
      lcd.setCursor(obuz_col, tank_rand);
      lcd.print(" ");
      obuz_col++;
      if (obuz_col > 15)
        trage = false;
    }
  }
  afisare();
}

void afisare() {
  lcd.setCursor(1, tank_rand);
  lcd.write((byte)0);//afisez tank
  if (trage == true) {
    lcd.setCursor(obuz_col, tank_rand);
    lcd.write((byte)1);
  }
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
