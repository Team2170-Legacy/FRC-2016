// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../MaxSonarEZ1.h"
#include "../ProfileData.h"
#include <cmath>

#define DEADBAND(val, limit)	((fabs(val) < limit) ? 0.0 : val)

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public Subsystem {
private:
	const unsigned short int kCountsPerRev = 360;	// 360 count encoder, x4 sampling
	const double kDefaultVoltageRamp = 36.0;		// 100% in 0.375 seconds
	float mAutoVelocity = 0.5;
	float mYawGain = -0.10;
	bool bDriveStraight = false;

	bool mMotionProcessingActive = false;

	Preferences *prefs;

	const double kProportionalGain = 0.75;
	const double kDerivativeGain = 2.5;
	const double kFeedForwardGain = 0.75;

	void SetVelocityMode();
	void SetClosedLoopMode();
	void SetMotionProfileMode();

	double AxisPower(double axis, double exponent);
	void InitTalons(void);
	void SetRampRate(double ramp);
	void SetMotorGains();

	float accel_angle_x;
	float accel_angle_y;
	float chassis_pitch = 0.0;

	CANTalon::MotionProfileStatus LeftStatus;
	CANTalon::MotionProfileStatus RightStatus;

	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> cANTalonRight;
	std::shared_ptr<CANTalon> cANTalonLeft;
	std::shared_ptr<RobotDrive> robotDrive;
	std::shared_ptr<AnalogGyro> gyro;
	std::shared_ptr<AnalogInput> maxSonarAI;
	std::shared_ptr<CANTalon> cANTalonSlaveRight;
	std::shared_ptr<CANTalon> cANTalonSlaveLeft;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<MaxSonarEZ1> FrontSonar;
	std::shared_ptr<BuiltInAccelerometer> RoboAccels;
	const size_t kBufferSize = 10;
	CircularBuffer<float> AccelBufferX;
	CircularBuffer<float> AccelBufferY;
	CircularBuffer<float> AccelBufferZ;

public:
	DriveTrain();

	void InitDefaultCommand();
	void SetChassisPosition(float position);
	void SetChassisVelocity(float velocity);
	void FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel);
	void FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel,
			std::shared_ptr<const ProfileData> RightWheel);
	void ServiceMotionProfile();
	bool MotionProfileComplete();
	CANTalon::ControlMode GetChassisMode();
	void SetChassisMode(CANTalon::ControlMode mode);
	double GetChassisPosition();
	void UpdateChassisPitch();
	float GetChassisPitch();

	void ArcadeDriveWithJoysticks(float moveVal, float rotateVal);
	void TankDriveWithTriggers(float Left, float Right, float Trigger);
	void DriveStraight(bool Backwards = false);
	void DriveStraight(float magnitude);

	void Rotate(float position);

	void ResetChassisYaw();
	float ReadChassisYaw();
	float ReadChassisDistance();
	void StopMotors();
	void SetBrakeMode( CANSpeedController::NeutralMode);
	void SetMotionProfileState(CANTalon::SetValueMotionProfile mode);

	double ReadPositionError();

	const double InchesPerRotation = 8.0 * 3.14159265;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void setAutoVelocity(float autoVelocity = 0.5) {
		mAutoVelocity = autoVelocity;
	}

	void SetVoltagePercentMode();

};

#endif
