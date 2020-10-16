#include "RS485_protocol.h"
#define RXD2 16
#define TXD2 17
#define enPin 21

#define deviceID 0 //0-master, 1,2..-slaves

//*********callback routines*********
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
void valveSetup()
{
  //Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  pinMode (enPin, OUTPUT);  // driver output enable
  digitalWrite (enPin, LOW);
}

//***********MAIN FUNCTION**************
int valveCommand(int recievingDeviceID, int commandSetting, int commandValue)
{
  delay(1); //give slaves a moment to do their stuff if master is sending messages in succesion
  //message to send
  byte msg [] = { 
     recievingDeviceID,    //id of the device we are sending to
     commandSetting,       //command selection (you can choose what this does in the code of the recieving device)
     commandValue,         //command (on or off, true or false)
  };

  // send to slave
  digitalWrite (enPin, HIGH);  // enable sending
  sendMsg (fWrite, msg, sizeof msg);
  delay(1);
  digitalWrite (enPin, LOW);  // disable sending

  // receive response  
  byte buf [10];
  byte received = recvMsg (fAvailable, fRead, buf, sizeof buf);
  
  //parsing recieved message
  if (received)
  {
    if (buf [0] != deviceID){
      return 11;  // wrong device ID error
    }
    return buf[2];
  }
  else  
  {
    return 10; //timeout error
  }
}  // end of loop
