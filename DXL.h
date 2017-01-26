#ifndef _DXL_H_
#define _DXL_H_

#include <DynamixelSDK.h>
#define flushSerial() Serial1.flush()

 //Handler Macros
//#define getBulkWriteHandler() dynamixel::GroupBulkWrite groupBulkWrite(portHandler, packetHandler )
//#define getBulkReadHandler() dynamixel::GroupBulkRead groupBulkRead(portHandler, packetHandler);
#define getHandlers() dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION)

// Control table address 
#define ADDR_PRO_TORQUE_ENABLE          24                 // Control table address is different in Dynamixel model
#define ADDR_PRO_GOAL_POSITION          30
#define ADDR_PRO_PRESENT_POSITION       36
#define ADDR_PRO_MOVING_SPEED           32
#define ADDR_PRO_PRESENT_SPEED          38
#define ADDR_PRO_MOVING                 46

// Data Byte Length
//#define LEN_PRO_LED_RED                 1
//#define LEN_PRO_GOAL_POSITION           4
//#define LEN_PRO_GOAL_SPEED              4
//#define LEN_PRO_PRESENT_POSITION        4
//#define LEN_PRO_PRESENT_SPEED           4

// CONTROL VALUES
#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque

// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel

// DEFAULT SETTINGS
#define ROLL_ID                          2                   
#define PITCH_ID                         3
#define YAW_ID                           4  
#define BAUDRATE                        1000000
#define DEVICENAME                      "COM10"          // redundant since controlling using teensy

#define ROLL_HOME_POS        0
#define ROLL_MAX_ANGLE       300.0
#define ROLL_MIN_ANGLE       0       

#define PITCH_HOME_POS       0
#define PITCH_MAX_ANGLE      300.0
#define PITCH_MIN_ANGLE      0
    
#define YAW_HOME_POS         0
#define YAW_MAX_ANGLE        300.0
#define YAW_MIN_ANGLE        0   
                                                            

#define COUNTS_PER_REV      1023 //207692
#define COUNTS_PER_DEG      (COUNTS_PER_REV/(300.0))

#define MAX_RPM             114.0
#define COUNTS_PER_RPM      (COUNTS_PER_REV/MAX_RPM)
#define RPM2COUNTS(rpm)     (rpm*COUNTS_PER_RPM)
#define COUNTS2RPM(cnts)    (cnts/COUNTS_PER_RPM)  

#define COUNTS2DEG(cnts)    (cnts/COUNTS_PER_DEG)
#define DEG2COUNTS(deg)     (COUNTS_PER_DEG*deg)

#define DEG2RAD(deg)        (deg*2*M_PI/360.0)
#define RAD2DEG(rad)        (rad*360.0/(2*M_PI))


int DXLinit();                  //init all DXLs
int DXLHome(uint8_t DXL_ID);
int DXLHomeAll();
int DXLenable(uint8_t DXL_ID);  //enable single DXL
int DXLenableAll();             //enable all DXLs

int DXLdisable(uint8_t DXL_ID); //disable single DXL
int DXLdisableAll();            //disable all DXLs
int DXLisMoving(uint8_t DXL_ID);

/* DXLsetLimits
 * sets max and min limits at specified units
 * INPUT: ID, minAngle, maxAngle, units
 * OUTPUT: Comm result SUCCESS or FAIL
 */
int DXLsetLimits(uint8_t DXL_ID, int minLimit, int maxLmit, uint8_t units);

/* DXLsetPos DXLsetSpeed
 * sets specified motor to desired angle or speed
 * INPUT: ID, desired angle/speed
 * OUTPUT: Comm result SUCCESSS or FAIL
 */
int DXLsetPos(uint8_t DXL_ID, double deg);
int DXLsetSpeed(uint8_t DXL_ID, double rpm);

/* DXLsetPos DXLsetSpeed
 * returns angle/speed of specified motor
 * INPUT: ID
 * OUTPUT: pos/speed
 */
double DXLgetPos(uint8_t DXL_ID);
double DXLgetSpeed(uint8_t DXL_ID);
 
/* DXLsetState
* Sets angles of all DXLs 
* INPUT: An array of size 6 of DXL positions and speeds in the following order: 
*        [roll, pitch, yaw, rollSpeet, yawSpeed, pitchSpeed]
*        eg states[6]: {rollAngle, pitchAngle, yawAngle, rollSpeed, pitchSpeed, yawSpeed}
*
* OUTPUT: Comm result SUCCESS or FAIL
*/
int DXLsetStates(double (&states)[6]);        //set angle/speed in DEGREES of all DXLs at specified units

/* DxlgetState
 * Gets the current state of DXLs at specified units
 * INPUT: A blank array of size 6 for the results to be placed
 *        eg. deg[6]: [roll, pitch, yaw, rollSpeet, yawSpeed, pitchSpeed]
 * OUTPUT: Comm results SUCCESS or FAIL
 */
int DXLgetStates(double (&states)[6]);
void makeWord(uint8_t (&param)[4], int value);

#endif
