/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
--------------------------
RobotControl.h
Updated on 11/03/2017
--------------------------
Description:
Made for RCJ Soccer Open
League.
This library is meant to
control the robot
movement.
--------------------------
Constant values:

MA-B-C-D constant values
that determine the motors
that are being used.
Example: MA+MB+MC given as
an argument for mts in
function setMotors will
only act on motors A,B
& C from the robot.
(See default motor
assignment order from line
71 thru 82.)
--------------------------
*/
#ifndef RobotControl_h
#define RobotControl_h
#define MA 1
#define MB 2
#define MC 3
#define MD 4
#include "Arduino.h"
class VNHMotor{
	private:
		bool inv;
		int pwPort;
		int port1;
		int port2;
		int enPort;
		int maxPw;
	public:
		// Constructor method: "motorPort1" and "motorPort2" are the direction control ports in the VNH
		// series motor controllers, "power" is the PWM input port from the motor controller,
		// "enablePort" is the value for the pin connected to the EN input port on the motor controller,
		// "max power" (ranged from 0-255) will be the maximum power at which the motors will be able to run,
		// & "inverted" allows to invert the use of the digital ports set by "motorPort1" & "motorPort2"
		// (for which you may also swap their values if you wish to have the same effect).
		VNHMotor(int powerPort,int motorPort1,int motorPort2,int enablePort,int maxPower,bool inverted);
		VNHMotor(int powerPort,int motorPort1,int motorPort2,int maxPower,bool inverted);
		
		// void set: Void sets the motor's power to the one specified in argument "power" (scaled from
		// -100.0 to 100.0 using the max power attribute in the constructor method.)
		void set(double power);
		
		// void setupMotors: "setupMotors" will set all pins specified in the constructor method to output
		// mode. This simplifies the lines of code required to set the modes each pin to OUTPUT.
		void setupMotor();

		// Sets the motor's power to 0.
		void stopMotor();
};
/*
Default motor assignment order:
	 
	 Frontal field of view
		\     ^     /
		 \   /|\   /
		  \ / | \ /
		   \  |  /
		    _ O _
		   /C\_/A\
Robot	  |---O---|
		   \D_|_B/
*/
class RobotControl{
	private:
		VNHMotor** motors;
		double degreesToRadians(double degrees);
		double toBoundAngle(double angle);
	public:
		// Constructor method(1): "motorA,B,C,& D" are the pointers for the instances of "VNHMotor"s in the specified
		// order of assignment described from line 71 thru 82
		RobotControl(VNHMotor* motorA,VNHMotor* motorB,VNHMotor* motorC,VNHMotor* motorD);

		// void setMotors: Sets the motors specified on "mts" to the scaled power from -100.0 to 100.0 given to "power".
		// To set multiple motors to the same power output, you can use the constants MA,B,C,& D like so:
		// MA+MB as an expresion given to argument "mts" will set both motor A & B to the same power.
		// (robot.setMotors(MA+MB, 100.0))
		void setMotors(unsigned int mts,double power);
		
		// void stopRobot: Sets all robot motors to power 0.0 (setMotors(MA+MB+MC+MD,0.0) will have the same effect)
		void stopRobot();


		/*
		For both "vectorMove" methods:
			
			Frontal field of view

					X axis

			        0 degr
				\     ^     /
				 \   /|\   /
				  \ / | \ /
				   \  |  /
			        _ O _
			Robot  /C\_/A\
	      270 degr|---O---|90 degr -----> Y axis
			       \D_|_B/		
			      180 degr
		*/
		// void vectorMove: Calling fucntion "vectorMove" will move the robot to the specified direction on argument "movementAngle" (in degrees)
		// at the power specified on argument "power" and rotating by the use of rotation gain.
		void vectorMove(double movementAngle,double power,double rotationGain);

		void axisMove(double powerX,double powerY,double rotationGain);
		// void vectorMoveTime: Calling fucntion "vectorMoveTime" will move the robot to the specified direction on argument "movementAngle" (in degrees)
		// at the power specified on argument "power" and rotating by the use of rotation gain for the ammount of time specified
		// by argument "ms" (in milliseconds).
		void vectorMoveTime(double movementAngle,double power,double rotationGain,unsigned int ms);
		
		
		// void moveFwd: equivalent to vectorMove(0.0, 'power', 0.0).
		void moveFwd(double power);
		// void moveRev: equivalent to vectorMove(180.0, 'power',0.0).
		void moveRev(double power);
		// void moveRight(1): equivalent to vectorMove(90.0, 'power',0.0).
		void moveRight(double power);
		// void moveLeft(1): equivalent to vectorMove(270.0, 'power',0.0).
		void moveLeft(double power);
};
#endif
