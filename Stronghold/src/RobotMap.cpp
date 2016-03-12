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
std::shared_ptr<AnalogInput> RobotMap::driveTrainMaxSonarAI;
std::shared_ptr<CANTalon> RobotMap::driveTrainCANTalonSlaveRight;
std::shared_ptr<CANTalon> RobotMap::driveTrainCANTalonSlaveLeft;
std::shared_ptr<SpeedController> RobotMap::shooterElevationMotor;
std::shared_ptr<SpeedController> RobotMap::shooterFlyWheelMotor;
std::shared_ptr<SpeedController> RobotMap::shooterHookMotor;
std::shared_ptr<Encoder> RobotMap::shooterElevationEncoder;
std::shared_ptr<DigitalInput> RobotMap::shooterElevationHome;
std::shared_ptr<DigitalInput> RobotMap::shooterElevationMax;
std::shared_ptr<DigitalInput> RobotMap::shooterHookHome;
std::shared_ptr<DigitalInput> RobotMap::shooterHookMax;
std::shared_ptr<SpeedController> RobotMap::shooterBallKicker;
std::shared_ptr<DigitalInput> RobotMap::shooterBallKickSensor;
std::shared_ptr<DigitalInput> RobotMap::shooterHookRearMax;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    driveTrainCANTalonRight.reset(new CANTalon(2));
    lw->AddActuator("Drive Train", "CAN Talon Right", driveTrainCANTalonRight);
    
    driveTrainCANTalonLeft.reset(new CANTalon(1));
    lw->AddActuator("Drive Train", "CAN Talon Left", driveTrainCANTalonLeft);
    
    driveTrainRobotDrive.reset(new RobotDrive(driveTrainCANTalonLeft, driveTrainCANTalonRight));
    
    driveTrainRobotDrive->SetSafetyEnabled(false);
        driveTrainRobotDrive->SetExpiration(0.5);
        driveTrainRobotDrive->SetSensitivity(0.5);
        driveTrainRobotDrive->SetMaxOutput(1.0);

    driveTrainGyro.reset(new AnalogGyro(0));
    lw->AddSensor("Drive Train", "Gyro", driveTrainGyro);
    driveTrainGyro->SetSensitivity(0.007);
    driveTrainMaxSonarAI.reset(new AnalogInput(2));
    lw->AddSensor("Drive Train", "Max Sonar AI", driveTrainMaxSonarAI);
    
    driveTrainCANTalonSlaveRight.reset(new CANTalon(3));
    lw->AddActuator("Drive Train", "CAN Talon Slave Right", driveTrainCANTalonSlaveRight);
    
    driveTrainCANTalonSlaveLeft.reset(new CANTalon(4));
    lw->AddActuator("Drive Train", "CAN Talon Slave Left", driveTrainCANTalonSlaveLeft);
    
    shooterElevationMotor.reset(new Talon(1));
    lw->AddActuator("Shooter", "Elevation Motor", std::static_pointer_cast<Talon>(shooterElevationMotor));
    
    shooterFlyWheelMotor.reset(new Talon(0));
    lw->AddActuator("Shooter", "Fly Wheel Motor", std::static_pointer_cast<Talon>(shooterFlyWheelMotor));
    
    shooterHookMotor.reset(new Talon(3));
    lw->AddActuator("Shooter", "Hook Motor", std::static_pointer_cast<Talon>(shooterHookMotor));
    
    shooterElevationEncoder.reset(new Encoder(2, 3, false, Encoder::k4X));
    lw->AddSensor("Shooter", "Elevation Encoder", shooterElevationEncoder);
    shooterElevationEncoder->SetDistancePerPulse(1.0);
    shooterElevationEncoder->SetPIDSourceType(PIDSourceType::kRate);
    shooterElevationHome.reset(new DigitalInput(0));
    lw->AddSensor("Shooter", "Elevation Home", shooterElevationHome);
    
    shooterElevationMax.reset(new DigitalInput(1));
    lw->AddSensor("Shooter", "Elevation Max", shooterElevationMax);
    
    shooterHookHome.reset(new DigitalInput(5));
    lw->AddSensor("Shooter", "Hook Home", shooterHookHome);
    
    shooterHookMax.reset(new DigitalInput(6));
    lw->AddSensor("Shooter", "Hook Max", shooterHookMax);
    
    shooterBallKicker.reset(new Talon(2));
    lw->AddActuator("Shooter", "Ball Kicker", std::static_pointer_cast<Talon>(shooterBallKicker));
    
    shooterBallKickSensor.reset(new DigitalInput(4));
    lw->AddSensor("Shooter", "Ball Kick Sensor", shooterBallKickSensor);
    
    shooterHookRearMax.reset(new DigitalInput(7));
    lw->AddSensor("Shooter", "Hook Rear Max", shooterHookRearMax);
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
