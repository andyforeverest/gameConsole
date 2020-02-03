void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int tasta = citesteTasta();
  if (tasta == 5)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  delay(100);
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
