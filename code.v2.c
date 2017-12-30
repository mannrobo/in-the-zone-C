#pragma config(Motor,  port2,           rightBack,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           rightLS,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftLS,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightCone,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftCone,      tmotorVex393_MC29, openLoop)
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

task autonomous(){
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
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

void drive() {

	//forward
		if(vexRT[Ch3] > threshold) {
				motor[rightBack] = 127;
				motor[leftBack] = 127;
		}

		//backward
		if(vexRT[Ch3] < threshold) {
				motor[rightBack] = -127;
				motor[leftBack] = -127;
		}

		//right
		if(vexRT[Ch1] > threshold) {
				motor[rightBack] = 127;
				motor[leftBack] = -127;
		}

		//left
		if(vexRT[Ch1] < threshold) {
				motor[rightBack] = -127;
				motor[leftBack] = 127;
		}

		motor[rightBack] = 0;
		motor[leftBack] = 0;
}

void setDrive(int x, int y){
	motor[rightBack] = x;
	motor[leftBack] = y;
}

void LS() {
	//right trigger, button 6D extends out
		if(vexRT[Btn6D] == 1) {
				motor[rightLS] = 75;
				motor[leftLS] = 75;
		}
		//right trigger, button 6U brings in
		if(vexRT[Btn6U] == 1) {
				motor[rightLS] = -75;
				motor[leftLS] = -75;
		}

		motor[rightLS] = 0;
		motor[leftLS] = 0;
}

void coneLift() {
		//claw open button 5U
		if(vexRT[Btn5U] == 1) {
				motor[cone] = 100;
		}
		//claw close button 5D
		if(vexRT[Btn5D] == 1) {
				motor[cone] = -100;
		}


		//claw lift up = 8U
		if(vexRT[Btn8U] == 1) {
				motor[rightCone] = 100;
				motor[leftCone] = 100;
		}
		//claw down = 8D
		if(vexRT[Btn8D] == 1) {
				motor[rightCone] = -100;
				motor[leftCone] = -100;
		}

		motor[rightCone] = 0;
		motor[leftCone] = 0;
}

task usercontrol() {
		  while (true){
		  		//setDrive(vexRT[Ch3], vexRT[Ch1]);
		    	drive();
		    	LS();
		    	coneLift();
		  }
}
