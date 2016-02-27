// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<Joystick> shooterJoystick;
	std::shared_ptr<JoystickButton> shooterPrematchPark;
	std::shared_ptr<JoystickButton> homeShooter;
	std::shared_ptr<JoystickButton> autoRaiseandClimb;
	std::shared_ptr<JoystickButton> manualLowerHook;
	std::shared_ptr<JoystickButton> manualRaiseHook;
	std::shared_ptr<JoystickButton> shootLow;
	std::shared_ptr<JoystickButton> shooterCollectBall;
	std::shared_ptr<JoystickButton> shootHigh;
	std::shared_ptr<Joystick> driveJoystick;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<Joystick> getDriveJoystick();
	std::shared_ptr<Joystick> getShooterJoystick();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
