#include "IRremote.hpp"

#define LED_OFF 0
#define LED_ON 1
#define LIGHT_MAX 100
#define TIMEOUT 1800 // 1s*60*30 = 30 min

IRsend irsend;
// Pinout
const int pinPir = 2;  
const int pinIr = 24;  
const int pinRes = A0;   
const int pinRes2 = A1; // photorestor2 near IR module, check just light LED intensity

//Values  
int pirState = LOW;           
int lightValue, lightValue2, count = 0;                 
int state = LED_OFF;
//State flags
bool lightFlag, timeFlag = false;


void setup() 
{
  pinMode(pinPir, INPUT_PULLUP);
  IrSender.begin(pinIr);
  Serial.begin(9600);
}

void sendIR(){
  IrSender.sendNEC(0x0, 0x40, 0); //IR signal to power on/off the LEDs
  }

void readLight(){
  lightValue = analogRead(pinRes);
}

void readLightLED(){
  lightValue2 = analogRead(pinRes2);
}

void checkLight(){
  readLight();
  if(lightValue > LIGHT_MAX){
    lightFlag = true;
  }
  else{
    lightFlag = false;
  }
}

void checkMove(){
  int val = digitalRead(pinPir);

  if (val == HIGH)   //if activated
  { 
    if (pirState == LOW)  //if previously switched off
    {
      //Sensor on
      pirState = HIGH;
    }
  } 
  else //if deactivated
  {
    if (pirState == HIGH)  //if it was previously switched on
    {
      //Sensor off
      pirState = LOW;
    }
  }
}

void loop()
{
  checkLight(); // light measure to change state
  readLightLED();

  switch(state){

    /*Check LIGHT all the time, correct state and timeout, if true LEDs OFF..*/
    case LED_ON:
      state = LED_ON;
      delay(500); // delay 1s before count to reach to the timeout
      if((count == TIMEOUT) || lightFlag){
        count = 0;
        state = LED_OFF;
        sendIR();
        break;
      } 
      if (lightValue >= lightValue2){
        state = LED_OFF;
        count = 0;
        break;
      }
      count = count + 1;
      break;
      
    /*Check LIGHT all the time and correct state, if true there is light and there is move or wrong state, LEDs ON.*/
    case LED_OFF:
      state = LED_OFF;
      if(!lightFlag){
        checkMove();
        if(pirState == HIGH){
          sendIR();
          state = LED_ON;
          break;
        }
      }
      if (lightValue2 > lightValue){
        state = LED_ON;
        break;
      }
      break;
  }
  delay(500);
}

