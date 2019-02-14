/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/PowerDistributionPanel.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>

/**
 * This is a sample program showing how to retrieve information from the Power
 * Distribution Panel via CAN. The information will be displayed under variables
 * through the SmartDashboard.
 */
class Robot : public frc::TimedRobot {
 public:

  void RobotInit() override {
//m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
//m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
//    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Position");
    m_chooser.AddOption("Left", Pos::LEFT);
    m_chooser.AddOption("Center", Pos::CENTER);
    m_chooser.AddOption("Right", Pos::RIGHT);
    m_chooser.SetDefaultOption("Left",Pos::LEFT);
//    tab.Add(m_chooser);
//    frc::SmartDashboard::PutData(&m_chooser);
    frc::SmartDashboard::PutData("Play", &m_chooser);

    m_destination.AddOption("Do Not Move", Dest::DONOTHING);
    m_destination.AddOption("Front Cargo", Dest::FRONTCARGO);
    m_destination.AddOption("Right Cargo", Dest::RIGHTCARGO);
    m_destination.AddOption("Left Cargo", Dest::LEFTCARGO);
    m_destination.AddOption("Right Rocket", Dest::RIGHTROCKET);
    m_destination.AddOption("Left Rocket", Dest::LEFTROCKET);
    m_destination.SetDefaultOption("Do Not Move", Dest::DONOTHING);

    frc::SmartDashboard::PutData("Destination", &m_destination);

  }

  void AutonomousInit() override {
    Pos startPosition = m_chooser.GetSelected();
    switch (startPosition) {
      case LEFT:
         printf("Left Selected\n");
         break;
      case CENTER:
         printf("Center Selected\n");
         break;
      case RIGHT:
         printf("Right Selected\n");
         break;
      default:
         printf("Default Selected\n");
         break;
    }

    Dest destination = m_destination.GetSelected();
    switch (destination) {
      case DONOTHING:
         printf("Do Not Move Selected\n");
         break;
      case FRONTCARGO:
         printf("Front Cargo Selected\n");
          break;
      case RIGHTCARGO:
          printf("Right Cargo Selected\n");
          break;
      case LEFTCARGO:
          printf("Left Cargo Selected\n");
          break;
      case RIGHTROCKET:
          printf("Right Rocket Selected\n");
          break;
      case LEFTROCKET:
          printf("Left Rocket Selected\n");
          break;
      default:
         printf("Default Selected\n");
         break;
    }
  }

  void TeleopPeriodic() override {
    /* Get the current going through channel 7, in Amperes. The PDP returns the
     * current in increments of 0.125A. At low currents the current readings
     * tend to be less accurate.
     */
    frc::SmartDashboard::PutNumber("Current Channel 7", m_pdp.GetCurrent(7));

    /* Get the voltage going into the PDP, in Volts. The PDP returns the voltage
     * in increments of 0.05 Volts.
     */
    frc::SmartDashboard::PutNumber("Voltage", m_pdp.GetVoltage());

    // Retrieves the temperature of the PDP, in degrees Celsius.
    frc::SmartDashboard::PutNumber("Temperature", m_pdp.GetTemperature());
  }

 private:
  // Object for dealing with the Power Distribution Panel (PDP).
  frc::PowerDistributionPanel m_pdp;
  enum Pos {LEFT, CENTER, RIGHT};
  frc::SendableChooser<Pos> m_chooser;

  enum Dest {DONOTHING, FRONTCARGO, RIGHTCARGO, LEFTCARGO, RIGHTROCKET, LEFTROCKET};
  frc::SendableChooser<Dest> m_destination;

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
