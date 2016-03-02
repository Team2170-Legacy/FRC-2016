// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "../Commands/TankDriveTeleop.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include <RobotDrive.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    cANTalonRight = RobotMap::driveTrainCANTalonRight;
    cANTalonLeft = RobotMap::driveTrainCANTalonLeft;
    robotDrive = RobotMap::driveTrainRobotDrive;
    gyro = RobotMap::driveTrainGyro;
    maxSonarAI = RobotMap::driveTrainMaxSonarAI;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    FrontSonar.reset(new MaxSonarEZ1(maxSonarAI));
    RoboAccels.reset(new BuiltInAccelerometer());
}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TankDriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::ArcadeDriveWithJoysticks(float moveVal, float rotateVal) {
	robotDrive->ArcadeDrive(moveVal, rotateVal, true);
}

void DriveTrain::ResetChassisYaw() {
	gyro->Reset();
}

float DriveTrain::ReadChassisYaw() {
	return gyro->GetAngle();
}

void DriveTrain::DriveStraight(bool Backwards) {
	if (Backwards)
		{
			DriveStraight(-mAutoVelocity);
		}
		else
		{
			DriveStraight(mAutoVelocity);
		}
}


void DriveTrain::DriveStraight(float magnitude) {

		float ChassisAngle = ReadChassisYaw();

		if (magnitude > 0.0) {
			robotDrive->Drive(magnitude, mYawGain * ChassisAngle);
		}
		else {
			robotDrive->Drive(magnitude, -mYawGain * ChassisAngle);
		}
}

void DriveTrain::StopMotors(void) {

	robotDrive->StopMotor();

}

void DriveTrain::SetVoltagePercentMode() {
	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	SetBrakeMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	cANTalonLeft->SetVoltageRampRate(kDefaultVoltageRamp);
	cANTalonLeft->Set(0.0);
	cANTalonRight->SetVoltageRampRate(kDefaultVoltageRamp);
	cANTalonRight->Set(0.0);

}

void DriveTrain::TankDriveWithTriggers(float Left, float Right, float Trigger) {
	float newLeft = 0.0;
 	float newRight = 0.0;
 	float ProcessedLeft = Left;
 	float ProcessedRight = Right;
 	double fExponent = 1.0;

 	ProcessedLeft = DEADBAND(AxisPower(ProcessedLeft, fExponent), 0.15);


 	ProcessedRight = DEADBAND(AxisPower(ProcessedRight, fExponent), 0.15);


 	newLeft = fmax(fmin(ProcessedLeft + (Trigger * .8), 1.0), -1.0);
 	newRight = fmax(fmin(ProcessedRight + (Trigger * .8), 1.0), -1.0);


 	if ((ProcessedLeft == 0) && (ProcessedRight == 0)) {
 		if (!bDriveStraight || DEADBAND(Trigger, 0.15) == 0) {
 			ResetChassisYaw();
 		}
 		bDriveStraight = true;
 		DriveStraight(Trigger * 0.8f);
 	}
 	else {
 		bDriveStraight = false;
 		robotDrive->TankDrive(newLeft, newRight, true);
 	}
}

double DriveTrain::AxisPower(double axis, double exponent) {
	double retVal = 0.0;

	retVal = pow(fabs(axis), exponent);
	retVal = (axis < 0.0) ? -1.0 * retVal : retVal;

	return retVal;
}

void DriveTrain::SetClosedLoopMode() {

	SetMotorGains();

	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kPosition);
	cANTalonLeft->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonLeft->ConfigEncoderCodesPerRev(kCountsPerRev);

	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kPosition);
	cANTalonRight->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonRight->ConfigEncoderCodesPerRev(kCountsPerRev);

	cANTalonLeft->SetVoltageRampRate(0.0);
	cANTalonLeft->SetPosition(0.0);
	cANTalonLeft->SetSensorDirection(true);
	cANTalonLeft->EnableControl();
	cANTalonLeft->Set(0.0);

	cANTalonRight->SetVoltageRampRate(0.0);
	cANTalonRight->SetPosition(0.0);
	cANTalonRight->SetSensorDirection(true);
	cANTalonRight->EnableControl();
	cANTalonRight->Set(0.0);
}

void DriveTrain::SetMotionProfileMode() {
	SetMotorGains();

	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kMotionProfile);
	cANTalonLeft->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonLeft->ConfigEncoderCodesPerRev(kCountsPerRev);
	cANTalonLeft->ChangeMotionControlFramePeriod(5);
	cANTalonLeft->SetPosition(0.0);
	cANTalonLeft->SetSensorDirection(true);
	cANTalonLeft->Set(CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonLeft->SetVoltageRampRate(0.0);

	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kMotionProfile);
	cANTalonRight->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonRight->ConfigEncoderCodesPerRev(kCountsPerRev);
	cANTalonRight->ChangeMotionControlFramePeriod(5);
	cANTalonRight->SetPosition(0.0);
	cANTalonRight->SetSensorDirection(true);
	cANTalonRight->Set(CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonRight->SetVoltageRampRate(0.0);

}

float DriveTrain::ReadChassisDistance() {
	return(FrontSonar->GetRangeInches());
}

void DriveTrain::Rotate(float rotateSpeed) {
	//if positive clockwise else counterclockwise
	//don't want squared value, for some reason
	robotDrive->TankDrive(rotateSpeed,-rotateSpeed,false);
}

void DriveTrain::CommandChassisPosition(float position) {
	if (cANTalonLeft->GetControlMode()==
			CANSpeedController::ControlMode::kPosition){
		cANTalonLeft->Set(position);
	}

	if (cANTalonRight->GetControlMode()==
			CANSpeedController::ControlMode::kPosition){
	cANTalonRight->Set(position);
	}
}

double DriveTrain::ReadPositionError() {
	return (cANTalonLeft->GetClosedLoopError()/kCountsPerRev);
}

void DriveTrain::SetVelocityMode() {
	SetMotorGains();
	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	cANTalonLeft->EnableControl();
	cANTalonLeft->Set(0.0);
	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	cANTalonRight->EnableControl();
	cANTalonRight->Set(0.0);
}

void DriveTrain::SetChassisVelocity(float vRPM) {
	if (cANTalonLeft->GetControlMode()
			== CANSpeedController::ControlMode::kSpeed) {
		cANTalonLeft->Set(vRPM);
	}

	if (cANTalonRight->GetControlMode()
			== CANSpeedController::ControlMode::kSpeed) {
		cANTalonRight->Set(-vRPM);
	}
}

void DriveTrain::SetChassisPosition(float position) {
	if (cANTalonLeft->GetControlMode()
			== CANSpeedController::ControlMode::kPosition) {
		cANTalonLeft->Set(position);
	}

	if (cANTalonRight->GetControlMode()
			== CANSpeedController::ControlMode::kPosition) {
		cANTalonRight->Set(-position);
	}
}

void DriveTrain::FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel) {
	size_t i;
	CANTalon::TrajectoryPoint pt;

	pt.zeroPos = true;
	pt.isLastPoint = false;
	pt.profileSlotSelect = 0;
	pt.velocityOnly = false;

	cANTalonLeft->Set(CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonRight->Set(CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonLeft->ClearMotionProfileTrajectories();
	cANTalonLeft->ClearMotionProfileHasUnderrun();
	cANTalonRight->ClearMotionProfileTrajectories();
	cANTalonRight->ClearMotionProfileHasUnderrun();

	for (i = 0; i < LeftWheel->size(); i++) {
		// check if this is the last point
		if ((i+1) == LeftWheel->size()) {
			pt.isLastPoint = true;
		}

		pt.position = LeftWheel->at(i).at(0);
		pt.velocity = LeftWheel->at(i).at(1);
		pt.timeDurMs = LeftWheel->at(i).at(2);
		if (!cANTalonLeft->PushMotionProfileTrajectory(pt)) {
			printf("left can push failed\n");
		}

		// Negative position and velocity for right side
		pt.position = -pt.position;
		pt.velocity = -pt.velocity;
		if (!cANTalonRight->PushMotionProfileTrajectory(pt)) {
			printf("right can push failed\n");
		}
		pt.zeroPos = false;
	}

}

void DriveTrain::FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel,
		std::shared_ptr<const ProfileData> RightWheel) {
	size_t i;
	CANTalon::TrajectoryPoint pt;

	pt.zeroPos = true;
	pt.isLastPoint = false;
	pt.profileSlotSelect = 0;
	pt.velocityOnly = false;

	cANTalonLeft->Set(CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonRight->Set(CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonLeft->ClearMotionProfileTrajectories();
	cANTalonLeft->ClearMotionProfileHasUnderrun();
	cANTalonRight->ClearMotionProfileTrajectories();
	cANTalonRight->ClearMotionProfileHasUnderrun();

	for (i = 0; i < LeftWheel->size(); i++) {
		// check if this is the last point
		if ((i+1) == LeftWheel->size()) {
			pt.isLastPoint = true;
		}

		pt.position = LeftWheel->at(i).at(0);
		pt.velocity = LeftWheel->at(i).at(1);
		pt.timeDurMs = LeftWheel->at(i).at(2);
		cANTalonLeft->PushMotionProfileTrajectory(pt);

		// Use right wheel profile for right side
		pt.position = RightWheel->at(i).at(0);
		pt.velocity = RightWheel->at(i).at(1);
		pt.timeDurMs = RightWheel->at(i).at(2);
		cANTalonRight->PushMotionProfileTrajectory(pt);
		pt.zeroPos = false;
	}
}

void  DriveTrain::ServiceMotionProfile() {
	cANTalonLeft->ProcessMotionProfileBuffer();
	cANTalonRight->ProcessMotionProfileBuffer();
}

void DriveTrain::SetBrakeMode( CANSpeedController::NeutralMode Mode) {
	cANTalonLeft->ConfigNeutralMode(Mode);
	cANTalonRight->ConfigNeutralMode(Mode);
}

void DriveTrain::SetMotionProfileState(CANTalon::SetValueMotionProfile mode) {
	if (cANTalonLeft->GetControlMode()
			== CANSpeedController::ControlMode::kMotionProfile) {
		cANTalonLeft->Set(mode);
	}
	if (cANTalonLeft->GetControlMode()
			== CANSpeedController::ControlMode::kMotionProfile) {
		cANTalonRight->Set(mode);
	}
}

void DriveTrain::SetMotorGains() {

	cANTalonLeft->SelectProfileSlot(0);
	cANTalonLeft->SetP(kPorportionalGain);
	cANTalonLeft->SetD(kDerivativeGain);
	cANTalonLeft->SetF(kFeedForwardGain);

	cANTalonRight->SelectProfileSlot(0);
	cANTalonRight->SetP(kPorportionalGain);
	cANTalonRight->SetD(kDerivativeGain);
	cANTalonRight->SetF(kFeedForwardGain);

}

bool DriveTrain::MotionProfileComplete() {
	bool Complete = false;

	cANTalonLeft->GetMotionProfileStatus(LeftStatus);
	cANTalonRight->GetMotionProfileStatus(RightStatus);

	printf("Remaining top buffer points:  %d\n", LeftStatus.topBufferRem);
	printf("Bottom buffer count:  %d\n", LeftStatus.btmBufferCnt);
	printf("IsUnderrun status:  %d\n", LeftStatus.isUnderrun);

	// Start motion profile processing after 5 points are in talon buffer
	if ((!mMotionProcessingActive) && (LeftStatus.btmBufferCnt > 5)) {
		SetMotionProfileState(CANTalon::SetValueMotionProfile::SetValueMotionProfileEnable);
		mMotionProcessingActive = true;
		printf("Enabling motion processing\n");
	}

	if ((LeftStatus.activePointValid && LeftStatus.activePoint.isLastPoint) &&
			(RightStatus.activePointValid && RightStatus.activePoint.isLastPoint)) {
		Complete = true;
		mMotionProcessingActive = false;
		printf("Motion Profile Complete\n");
	}

	return Complete;
}

CANSpeedController::ControlMode DriveTrain::GetChassisMode() {
	return cANTalonLeft->GetControlMode();
}

void DriveTrain::SetChassisMode(CANSpeedController::ControlMode mode) {
	switch (mode) {
	case CANSpeedController::ControlMode::kMotionProfile:
		SetMotionProfileMode();
		break;
	case CANSpeedController::ControlMode::kPosition:
		SetClosedLoopMode();
		break;
	case CANSpeedController::ControlMode::kSpeed:
		SetVelocityMode();
		break;
	default:
		SetVoltagePercentMode();
		break;
	}
}
