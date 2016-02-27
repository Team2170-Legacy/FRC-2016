// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/ShooterJoystickControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    elevationMotor = RobotMap::shooterElevationMotor;
    flyWheelMotor = RobotMap::shooterFlyWheelMotor;
    hookMotor = RobotMap::shooterHookMotor;
    elevationEncoder = RobotMap::shooterElevationEncoder;
    elevationHome = RobotMap::shooterElevationHome;
    elevationMax = RobotMap::shooterElevationMax;
    hookHome = RobotMap::shooterHookHome;
    hookMax = RobotMap::shooterHookMax;
    ballKicker = RobotMap::shooterBallKicker;
    ballKickSensor = RobotMap::shooterBallKickSensor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ShooterJoystickControl());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Shooter::FlyWheelReverse() {
	flyWheelMotor->Set(kFlyWheelReverseSpeed);
}

void Shooter::FlyWheelStop() {
	flyWheelMotor->Set(kFlyWheelStop);
}

void Shooter::FlyWheelHighSpeed() {
	flyWheelMotor->Set(kFlyWheelHighSpeed);
}

void Shooter::FlyWheelLowSpeed() {
	flyWheelMotor->Set(kFlyWheelLowSpeed);
}

void Shooter::KickerExtend() {
	ballKicker->Set(kKickerExtendSpeed);
}

void Shooter::KickerRetract() {
	ballKicker->Set(kKickerRetractSpeed);
}

bool Shooter::KickerDetect() {
	return !ballKickSensor->Get();		// Normally open switch need to invert
}

void Shooter::ShooterElevate() {
	if (!ShooterAtMax()) {
		elevationMotor->Set(kShooterElevateSpeed);
	}
	else {
		elevationMotor->Set(kShooterStop);
	}
}

void Shooter::ShooterLower() {
	if (!ShooterIsHome()) {
		elevationMotor->Set(kShooterLowerSpeed);
	}
	else {
		elevationMotor->Set(kShooterStop);
	}
}

bool Shooter::ShooterIsHome() {
	bool Home = elevationHome->Get();

	if (Home) {
		elevationEncoder->Reset();
		mShooterHomed = true;
	}
	return Home;
}

bool Shooter::ShooterAtMax() {
	return elevationMax->Get();
}

float Shooter::GetShooterElevation() {
	return elevationEncoder->GetDistance();
}

void Shooter::HookRaise() {
	hookMotor->Set(kHookRaiseSpeed);
}

void Shooter::HookLower() {
	hookMotor->Set(kHookLowerSpeed);
}

bool Shooter::HookIsHome() {
	return hookHome->Get();
}

void Shooter::ShooterStop() {
	elevationMotor->Set(kShooterStop);
}

void Shooter::HookStop() {
	hookMotor->Set(kHookStop);
}

void Shooter::KickerStop() {
	ballKicker->Set(kKickerStop);
}

bool Shooter::HookAtMax() {
	return hookMax->Get();
}

void Shooter::ShooterAim(float ElevationCmd) {
	ElevationCmd = -ElevationCmd;
	ElevationCmd = DEADBAND_SHOOTER(ElevationCmd, 0.15);

	if ((ElevationCmd > 0.0) && ShooterAtMax()) {
		ElevationCmd = 0.0;
	}

	if ((ElevationCmd < 0.0) && ShooterIsHome()) {
		ElevationCmd = 0.0;
	}

	elevationMotor->Set(ElevationCmd);
}

void Shooter::EncoderReset() {
	elevationEncoder->Reset();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

