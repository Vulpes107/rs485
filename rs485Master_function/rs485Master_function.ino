void setup() {
  Serial.begin(115200);
  valveSetup();
}

int state=0, t;
void loop() {
  if (millis()-t > 500)
  {
    Serial.print("Return: ");
    Serial.println(valveCommand(1, 1, state));
    if (state == 0){
      state = 1;  
    }
    else{
      state = 0;
    }
    t = millis();
  }
}
