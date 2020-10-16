void setup() {
  Serial.begin(115200);
  valveSetup();
}

int state=0;
void loop() {
  Serial.print("Return: ");
  Serial.println(valveCommand(1, 1, state));
  if (state == 0){
    state = 1;  
  }
  else{
    state = 0;
  }
  delay(500);
}
