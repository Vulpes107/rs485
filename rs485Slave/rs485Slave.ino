#include "RS485_protocol.h"
#define RXD2 16
#define TXD2 17
#define enPin 21

#define LED_PIN LED_BUILTIN

#define deviceID 1 //0-master, 1,2..-slaves

//***********callback routines***********
void fWrite (const byte what)
  {
  Serial1.write (what);  
  }
  
int fAvailable ()
  {
  return Serial1.available ();  
  }

int fRead ()
  {
  return Serial1.read ();  
  }


//***********SETUP**************
void setup()
{
  Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  pinMode (enPin, OUTPUT);  // driver output enable
  digitalWrite (enPin, LOW);
  
  pinMode (LED_PIN, OUTPUT);  // built-in LED
}

//***********LOOP**************
int t=0;
void loop()
{
  byte buf [10];
  byte received = recvMsg (fAvailable, fRead, buf, sizeof buf);
  

  //parsing recieved message
  if (received)
    {
      if (buf [0] != deviceID)
        return;  // not my device
         
      int returnValue = switchCommand(buf[1], buf[2]); //Sends command setting value to be processed and carried out (returns a message for master)
      int recievingDeviceID = 0;//sending to master
      int commandSetting = buf[1];
      
      //message to respond
      byte msg [] = {
         recievingDeviceID,    //id of the device we are sending to
         commandSetting,       //command selection (you can choose what this does in the code of the recieving device)
         returnValue,         //command (on or off, true or false)
      };
      
      delay (1);  // give the master a moment to prepare to receive
      digitalWrite (enPin, HIGH);  // enable sending
      sendMsg (fWrite, msg, sizeof msg);
      delay(1);
      digitalWrite (enPin, LOW);  // disable sending
   }  // end if something received
}  // end of loop
