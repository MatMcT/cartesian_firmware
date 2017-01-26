#include <AccelStepper.h>

#include "packets.h"
#include "motors.h"
#include "motor_params.h"
#include "DXL.h"

char msgBuffer[100];

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.setTimeout(200);
  init_motors();
  if(!DXLinit()) Serial.print("DXL failed to init");
//  //homeAxis(XAXIS);
//  //delay(5000);
  DXLdisable(2);


}

  double wristStates[] = {0,0,0,30,30,30};
  double wristStates2[] = {100,200,250,50,70,90};
  double currentState[6];
  
void loop() {
  
 if(Serial.available()){
  //int val = Serial.parseInt();
  processPacket();
 }

//  if(! (DXLisMoving(2) || DXLisMoving(3) || DXLisMoving(4)) ) {
//    DXLsetStates(wristStates);
//    delay(50);
//  }
//  
//  if(! (DXLisMoving(2) || DXLisMoving(3) || DXLisMoving(4)) ) {
//    DXLsetStates(wristStates2);
//    delay(50);
//  }

//  DXLgetStates(currentState);
//  sprintf(msgBuffer, "%f,%f,%f,%f,%f,%f", currentState[0], currentState[1], currentState[2], currentState[3], currentState[4], currentState[5], currentState[6]);
//  Serial.println(msgBuffer);
//  delay(100);
}















