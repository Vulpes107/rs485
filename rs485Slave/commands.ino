int switchCommand(int commandSetting, int commandValue){
  switch(commandSetting){
    case(0): //for initialisation
    return 1;
    break;
    
    case(1): //turn a pin on or off based on commandValue sent
    digitalWrite(LED_PIN, commandValue);
    return 0;
    break;

    case(2): //send state of the pin
    return (digitalRead(LED_PIN));
    break;
    //....
  }
}
