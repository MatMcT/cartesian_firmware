#ifndef MOTORS_H_
#define MOTORS_H_

#include <AccelStepper.h>
#include <MultiStepper.h>
#define ENCODER_USE_INTERRUPTS
//#include <Encoder.h>

/* some useful macros */
#define ROOT2 (1.41421356237)
#define ROOT2on2 (ROOT2/2.0)
#define D2(y, z) ( (y-z))
#define D3(y, z) ( (y+z))

#define YDIST(d2, d3) ((d2+d3)/2.0)
#define ZDIST(d2, d3) ((d3-d2)/2.0)


//Function Prototypes
bool checkLimits(unsigned char axis, long position);
bool inMotion();

int setAxisPosition(uint8_t AXIS, double pos);
int setAxisSpeed(uint8_t AXIS, double vel);

double getAxisPosition(uint8_t AXIS);
double getAxisSpeed(uint8_t AXIS);

int setAxisState(uint8_t AXIS);

void init_motors();
void homeAxis(unsigned char axis);
void setCartState(double motorCommand[] );
void getCartState(double (&state)[6] );
void runMotors();
void runDemo();



extern double CartStates[6];  //Cartesian states {x, y, z, vx, vy, vz};

#endif


