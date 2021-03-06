#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte tank[] = {0x00, 0x0F, 0x08, 0x1E, 0x19, 0x1F, 0x1B, 0x1B};
byte obuz[] = {0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00};
byte target[] = {0x00, 0x04, 0x0E, 0x15, 0x1B, 0x15, 0x0E, 0x04};

void setup() {
  pinMode(A0, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, tank);
  lcd.createChar(1, obuz);
  lcd.createChar(2, target);
  Serial.begin(9600);
}

unsigned long timp = 0;
bool trage = false;
int tank_row = 0;
int obuz_col = 2;
int obuz_rand;
int target_row, target_col = 15;
int scor = 0;
bool gameOver = false;

void loop() {
  if ((millis() - timp >= 100) && (gameOver == false)) {
    timp = millis();
    int tasta = citesteTasta();
    if (tasta == 5 && trage == false) {
      trage = true;
      obuz_col = 2;
      obuz_rand = tank_row;
      Serial.println("fire");
    }
    if (tasta == 2 && tank_row == 1) //UP
    {
      lcd.setCursor(1, 1);
      lcd.print(" ");
      tank_row = 0;
    }
    if (tasta == 3 && tank_row == 0) //DOWN
    {
      lcd.setCursor(1, 0);
      lcd.print(" ");
      tank_row = 1;
    }
    if (trage == true) {
      lcd.setCursor(obuz_col, obuz_rand);
      lcd.print(" ");
      obuz_col++;
      if (obuz_col > 15)
        trage = false;
    }
    //modificare pozitie target
    lcd.setCursor(target_col, target_row);
    lcd.print(" ");
    target_col--;
    if (target_col < 0) {
      target_col = 15;
      target_row = random(0, 2);// 0 sau 1
    }
    //daca am nimerit tinta
    if (((target_col - obuz_col == 1) || (target_col == obuz_col)) && (target_row == obuz_rand)) {
      if (trage == true)
      { target_col = 15;
        target_row = random(0, 2);// 0 sau 1
        trage = false;
        scor++;
      }
    }

    //daca tinta atinge tancul
    if ((target_row == tank_row) && (target_col == 1)) {
      gameOver = true;
    }
  }
  afisare();
  if (gameOver == true) {
    int tasta = citesteTasta();
    if(tasta == 1){
      gameOver = false;
      trage = false;
      target_row = random(0, 2);
      target_col = 15;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game restarting");
      delay(2000);
      lcd.clear();
      scor = 0;
    }
  }
}

void afisare() {
  if (gameOver == false) {
    lcd.setCursor(1, tank_row);
    lcd.write((byte)0);//afisez tank
    if (trage == true) {
      lcd.setCursor(obuz_col, obuz_rand);
      lcd.write((byte)1);
    }
    lcd.setCursor(target_col, target_row);
    lcd.write((byte)2);//afisare target
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Game over!     ");
    lcd.setCursor(0, 1);
    lcd.print("Your score: ");
    lcd.print(scor);
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
