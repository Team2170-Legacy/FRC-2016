// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<CANTalon> RobotMap::driveTrainCANTalonRight;
std::shared_ptr<CANTalon> RobotMap::driveTrainCANTalonLeft;
std::shared_ptr<RobotDrive> RobotMap::driveTrainRobotDrive;
std::shared_ptr<AnalogGyro> RobotMap::driveTrainGyro;
std::shared_ptr<AnalogPotentiometer> RobotMap::shooterBallScrewPotentiometer;
std::shared_ptr<SpeedController> RobotMap::shooterBallScrewSpeedController;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    driveTrainCANTalonRight.reset(new CANTalon(1));
    lw->AddActuator("Drive Train", "CAN Talon Right", driveTrainCANTalonRight);
    
    driveTrainCANTalonLeft.reset(new CANTalon(2));
    lw->AddActuator("Drive Train", "CAN Talon Left", driveTrainCANTalonLeft);
    
    driveTrainRobotDrive.reset(new RobotDrive(driveTrainCANTalonLeft, driveTrainCANTalonRight));
    
    driveTrainRobotDrive->SetSafetyEnabled(true);
        driveTrainRobotDrive->SetExpiration(0.5);
        driveTrainRobotDrive->SetSensitivity(0.5);
        driveTrainRobotDrive->SetMaxOutput(1.0);

    driveTrainGyro.reset(new AnalogGyro(0));
    lw->AddSensor("Drive Train", "Gyro", driveTrainGyro);
    driveTrainGyro->SetSensitivity(0.007);
    shooterBallScrewPotentiometer.reset(new AnalogPotentiometer(1, 1.0, 0.0));
    lw->AddSensor("Shooter", "Ball Screw Potentiometer", shooterBallScrewPotentiometer);
    
    shooterBallScrewSpeedController.reset(new Talon(0));
    lw->AddActuator("Shooter", "Ball Screw Speed Controller", std::static_pointer_cast<Talon>(shooterBallScrewSpeedController));
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
