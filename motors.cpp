#include "motors.h"
#include "motor_params.h"

//Declare encoders
//Encoder enc1(ENC1APIN, ENC1BPIN);
//Encoder enc2(ENC2APIN, ENC2BPIN);
//Encoder enc3(ENC3APIN, ENC3BPIN);

//Declare motors
AccelStepper mot1(AccelStepper::DRIVER, mot1_step_pin, mot1_dir_pin, true);
AccelStepper mot2(AccelStepper::DRIVER, mot2_step_pin, mot2_dir_pin, true);
AccelStepper mot3(AccelStepper::DRIVER, mot3_step_pin, mot3_dir_pin, true);
MultiStepper YZ;


void init_motors(){
  mot1.setAcceleration(init_accel);
  mot1.setMaxSpeed(init_speed);
  mot1.setEnablePin(mot1_enable_pin);
  mot1.setPinsInverted(false, true, true); //direction, step, enable
  mot1.setMinPulseWidth(30);
  mot1.enableOutputs(); 
  
  mot2.setAcceleration(init_accel);
  mot2.setMaxSpeed(init_speed);
  mot2.setPinsInverted(true, true, true); 
  mot2.setEnablePin(mot2_enable_pin);
  mot2.enableOutputs(); 

  mot3.setAcceleration(init_accel);
  mot3.setMaxSpeed(init_speed);
  mot3.setPinsInverted(true, true, true); 
  mot3.setEnablePin(mot3_enable_pin);

 // XYZ.addStepper(mot1);
  YZ.addStepper(mot2);
  YZ.addStepper(mot3);
}

void homeAxis(unsigned char axis){
  switch(axis){
    case XAXIS:
      Serial.println("Homing X Axis!");
      mot1.disableOutputs();
      delay(50);
      mot1.enableOutputs();
      Serial.println("Homing done!");
      break;
  }

  //Reset Encoders
//  enc1.write(0);
//  enc2.write(0);
//  enc3.write(0);
}


bool checkLimits(unsigned char axis, double position){
  bool good2Go = true;
    switch(axis){
      case XAXIS:
        if(position > XMAX || position < XMIN){
          Serial.println("X command out of bounds");
          good2Go = false;
        }
        break;

      case YAXIS:
        if(position > YMAX || position < YMIN){
          Serial.println("Y command out of bounds");
          good2Go = false;
        }
        break;

       case ZAXIS:
        if(position > ZMAX || position < ZMIN){
          Serial.println("Z command out of bounds");
          good2Go = false;
        }
        break;
    }
    
  return good2Go;
}

void runMotors(){
  mot1.run();
  mot2.run();
  mot3.run();
}

bool inMotion(){
  return (mot1.distanceToGo() != 0) || (mot2.distanceToGo() != 0) || (mot3.distanceToGo() != 0);
}


double getAxisPosition(uint8_t AXIS){
  switch(AXIS){
    case XAXIS:
      //return ENC2DIST(enc1.read());
      return step2dist(mot1.currentPosition());

    case YAXIS:
      //return YDIST(ENC2DIST(enc2.read()), ENC2DIST(enc3.read()));
      return YDIST( step2dist(mot2.currentPosition()), step2dist(mot3.currentPosition()) );

    case ZAXIS:
      //return ZDIST(ENC2DIST(enc2.read()), ENC2DIST(enc3.read()));
      return ZDIST( step2dist(mot2.currentPosition()), step2dist(mot3.currentPosition()) );

    default:
      return -1;
  }
  return -1;
}

double getAxisSpeed(uint8_t AXIS){
 
 
    switch(AXIS){
    case XAXIS:
      //return ENC2DIST(enc1.read());
      if(mot1.disdanceToGo() == 0) return 0;
      return step2dist(mot1.speed());

    case YAXIS:
      //return YDIST(ENC2DIST(enc2.read()), ENC2DIST(enc3.read()));
      if(mot2.disdanceToGo() == 0 && mot3.disdanceToGo() == 0) return 0;
      return YDIST( step2dist(mot2.speed()), step2dist(mot3.speed()) );

    case ZAXIS:
      //return ZDIST(ENC2DIST(enc2.read()), ENC2DIST(enc3.read()));
      if(mot2.disdanceToGo() == 0 && mot3.disdanceToGo() == 0) return 0;
      return ZDIST( step2dist(mot2.speed()), step2dist(mot3.speed()) );

    default:
      return -1;
  }
  return -1;
  
}

void setCartState(double motorCommand[]){
  //motorCommand should be in the form [x, y, z, dx, dy, dz]

  bool good2Go = checkLimits(XAXIS, motorCommand[0]) && checkLimits(YAXIS,  motorCommand[1]) && checkLimits(ZAXIS,  motorCommand[2]);
  long YZmove[2];
  float YZspeed[2];
  
  if(good2Go){
    YZmove[0] = (long)(steps_per_mm*D2(motorCommand[1], motorCommand[2]));
    YZmove[1] = (long)(steps_per_mm*D3(motorCommand[1], motorCommand[2]));

    YZspeed[1] = (float)(steps_per_mm * D3(motorCommand[4], motorCommand[5]));
    YZspeed[0] = YZspeed[1];   //(float)(steps_per_mm * D2(motorCommand[4], motorCommand[5]));
    
    mot1.setMaxSpeed( (float)(motorCommand[3]*steps_per_mm ) );
    mot1.moveTo( (long)(dist2step(motorCommand[0])) );
  
    mot2.setMaxSpeed( YZspeed[0] );
    mot2.moveTo( YZmove[0] );
    mot3.setMaxSpeed( YZspeed[1] );
    mot3.moveTo( YZmove[1] );

  }
}

void getCartState(double (&state)[6] ){
  //[x, y, z, dx, dy, dz]
  state[0] = getAxisPosition(XAXIS);
  state[1] = getAxisPosition(YAXIS);
  state[2] = getAxisPosition(ZAXIS);

  state[3] = getAxisSpeed(XAXIS);
  state[4] = getAxisSpeed(YAXIS);
  state[5] = getAxisSpeed(ZAXIS);
}
