void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  Serial1.begin(9600);
  Serial.begin(9600);

}

void loop() {
  if(digitalRead(0)==HIGH){
    delay(200);
    while(digitalRead(0)==HIGH){
      //do nothing
    }
    Serial1.write('U');
    Serial.write('U');
  }
  if(digitalRead(1)==HIGH){
    delay(200);
    while(digitalRead(1)==HIGH){
      //do nothing
    }
    Serial1.write('E');
    Serial.write('E');
  }
  if(digitalRead(2)==HIGH){
    delay(200);
    while(digitalRead(2)==HIGH){
      //do nothing
    }
    Serial1.write('D');
    Serial.write('D');
  }

}
