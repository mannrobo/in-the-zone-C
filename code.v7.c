#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  LSbumper,       sensorTouch)
#pragma config(Motor,  port2,           rightBack,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightLS,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftLS,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rightCone,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           leftCone,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           cone,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"


int threshold = 10;
int LSMAX = 1000;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(){
	SensorValue(rightEncoder) = 0;
	SensorValue(leftEncoder) = 0;

  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void autoLS() {
		if(SensorValue(LSbumper) == 1) {
				//check quadencoders
				motor[rightLS] = 90;
				motor[leftLS] = 80;
				wait1Msec(30);
				motor[rightLS] = 0;
				motor[leftLS] = 0;
		}
}

void stopDrive() {
		motor[rightBack] = 0;
		motor[leftBack] = 0;
}

void autoRight180Turn() {
		motor[rightBack] = 75;
		motor[leftBack] = -75;
		wait1Msec(50);
		stopDrive();
}

void autoLeft180Turn() {
		motor[rightBack] = -75;
		motor[leftBack] = 75;
		wait1Msec(50);
		stopDrive();
}

void autoLeft90Turn() {
		motor[rightBack] = -75;
		motor[leftBack] = 75;
		wait1Msec(25);
		stopDrive();
}

void autoShortForward() {
		motor[rightBack] = -75;
		motor[leftBack] = -75;
		wait1Msec(30);
		motor[rightBack] = 0;
		motor[leftBack] = 0;
}

void autoLongForward() {
		motor[rightBack] = -75;
		motor[leftBack] = -75;
		wait1Msec(60);
		motor[rightBack] = 0;
		motor[leftBack] = 0;
}

void autoShortBackward() {
		motor[rightBack] = 75;
		motor[leftBack] = 75;
		wait1Msec(30);
		motor[rightBack] = 0;
		motor[leftBack] = 0;
}

void shortAuto() {
		//pseudocode, because this has not been tested yet
		//drive forward, pick up a mobile goal, 180 right, drive forward and place it in the 10 point zone
		autoShortForward();
		autoLS();
		autoRight180Turn();
		autoShortForward();
}

void longAuto() {
		shortAuto();
		autoShortBackward();
		autoLeft180Turn();
		autoLongForward();
		autoLS();
		autoShortForward();
}

void oneMinute() {
		//drive forward, pick up mobile goal, 180 drive forward and place it in the 10 point zone
		//back up, 180, drive forward, pick up mobile goal, place it in the opposite 10 point zone
		//back up, 90 left, forward, 90 left, drive forward, pick up mobile goal, 180 drive forward and place it in the 10 point zone
		//back up, 180, drive forward, pick up mobile goal, place it in the opposite 10 point zone
		longAuto();
		autoShortBackward();
		autoLeft90Turn();
		autoShortForward();
		autoLeft90Turn();
		longAuto();
}


task autonomous(){
  	shortAuto();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void drive(int x, int y) {
	//positive drive values = backwards
			if(abs(x) > threshold) {
					motor[rightBack] = x;
					motor[leftBack] = -x;
			}
			else if(abs(y) > threshold) {
					motor[rightBack] = -y;
					motor[leftBack] = -y;
			} else {
					stopDrive();
			}
}

void LS(int extend, int retract) {
	//positive LS moves backward
				if(extend == 1) {
						//if(abs(SensorValue(rightEncoder)) < LSMAX && abs(SensorValue(leftEncoder)) < LSMAX) {
								motor[rightLS] = 90;
								motor[leftLS] = 80;
						//}
				}
				else if(retract == 1) {
						motor[rightLS] = -90;
						motor[leftLS] = -80;
				}
				else {
						motor[rightLS] = 0;
						motor[leftLS] = 0;
				}
}

void claw(int open, int close) {
	if(open == 1) {
			motor[cone] = 45;
	}
  else if(close == 1) {
			motor[cone] = -45;
	}
	else {
		motor[cone] = 0;
	}
}

void clawRotate(int clockwise, int counterclockwise) {
	//trigger 8U counter clockwise if looking from the right side of the robot
	//trigger 8D clockwise if looking from the right side of the robot
		if(clockwise == 1) {
				motor[rightCone] = 100;
				motor[leftCone] = 100;
		}
		else if(counterclockwise == 1) {
				motor[rightCone] = -100;
				motor[leftCone] = -100;
		}
		else {
				motor[rightCone] = 0;
				motor[leftCone] = 0;
		}
}

int hold = 0;
void rotateStop(int button) {
		if(button == 1) {
			hold = 1;
		}

}

void Riley() {
	drive(vexRT[Ch1], vexRT[Ch3]);
	//for claw
			//trigger 5U is claw open
			//trigger 5D is claw close
	claw(vexRT[Btn5U], vexRT[Btn5D]);
	//for LS
			//right trigger, button 6D extends
			//right trigger, button 6U retracts
	LS(vexRT[Btn6D], vexRT[Btn6U]);
	clawRotate(vexRT[Btn8D], vexRT[Btn8U]);
}

void Emily() {
	//Ch1 right and left, Ch3 forward and backward
	drive(vexRT[Ch1], vexRT[Ch3]);
	//5U opens, 5D closes
	claw(vexRT[Btn5U], vexRT[Btn5D]);
	//6U goes out, 6D comes in
	LS(vexRT[Btn6U], vexRT[Btn6D]);
}

task usercontrol() {

		  while(true) {
		  		Riley();
		  }

}
