// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <stdint.h>

#include <string>

#include <units/temperature.h>
#include <units/voltage.h>

namespace frc {

struct CANStatus {
  float percentBusUtilization;
  int busOffCount;
  int txFullCount;
  int receiveErrorCount;
  int transmitErrorCount;
};

class RobotController {
 public:
  RobotController() = delete;

  /**
   * Return the FPGA Version number.
   *
   * For now, expect this to be competition year.
   *
   * @return FPGA Version number.
   */
  static int GetFPGAVersion();

  /**
   * Return the FPGA Revision number.
   *
   * The format of the revision is 3 numbers. The 12 most significant bits are
   * the Major Revision. The next 8 bits are the Minor Revision. The 12 least
   * significant bits are the Build Number.
   *
   * @return FPGA Revision number.
   */
  static int64_t GetFPGARevision();

  /**
   * Return the serial number of the roboRIO.
   *
   * @return The serial number of the roboRIO.
   */
  static std::string GetSerialNumber();

  /**
   * Return the comments from the roboRIO web interface.
   *
   * The comments string is cached after the first call to this function on the
   * RoboRIO - restart the robot code to reload the comments string after
   * changing it in the web interface.
   *
   * @return The comments from the roboRIO web interface.
   */
  static std::string GetComments();

  /**
   * Returns the team number configured for the robot controller.
   *
   * @return team number, or 0 if not found.
   */
  static int32_t GetTeamNumber();

  /**
   * Read the microsecond-resolution timer on the FPGA.
   *
   * @return The current time in microseconds according to the FPGA (since FPGA
   *         reset).
   */
  static uint64_t GetFPGATime();

  /**
   * Get the state of the "USER" button on the roboRIO.
   *
   * @return True if the button is currently pressed down
   */
  static bool GetUserButton();

  /**
   * Read the battery voltage.
   *
   * @return The battery voltage in Volts.
   */
  static units::volt_t GetBatteryVoltage();

  /**
   * Check if the FPGA outputs are enabled.
   *
   * The outputs may be disabled if the robot is disabled or e-stopped, the
   * watchdog has expired, or if the roboRIO browns out.
   *
   * @return True if the FPGA outputs are enabled.
   */
  static bool IsSysActive();

  /**
   * Check if the system is browned out.
   *
   * @return True if the system is browned out
   */
  static bool IsBrownedOut();

  /**
   * Gets the current state of the Robot Signal Light (RSL)
   * @return The current state of the RSL- true if on, false if off
   */
  static bool GetRSLState();

  /**
   * Gets if the system time is valid.
   *
   * @return True if the system time is valid, false otherwise
   */
  static bool IsSystemTimeValid();

  /**
   * Get the input voltage to the robot controller.
   *
   * @return The controller input voltage value in Volts
   */
  static double GetInputVoltage();

  /**
   * Get the input current to the robot controller.
   *
   * @return The controller input current value in Amps
   */
  static double GetInputCurrent();

  /**
   * Get the voltage of the 3.3V rail.
   *
   * @return The controller 3.3V rail voltage value in Volts
   */
  static double GetVoltage3V3();

  /**
   * Get the current output of the 3.3V rail.
   *
   * @return The controller 3.3V rail output current value in Amps
   */
  static double GetCurrent3V3();

  /**
   * Enables or disables the 3.3V rail.
   *
   * @param enabled whether to enable the 3.3V rail.
   */
  static void SetEnabled3V3(bool enabled);

  /**
   * Get the enabled state of the 3.3V rail. The rail may be disabled due to
   * calling SetEnabled3V3(), a controller brownout, a short circuit on the
   * rail, or controller over-voltage.
   *
   * @return The controller 3.3V rail enabled value. True for enabled.
   */
  static bool GetEnabled3V3();

  /**
   * Get the count of the total current faults on the 3.3V rail since the
   * controller has booted.
   *
   * @return The number of faults
   */
  static int GetFaultCount3V3();

  /**
   * Get the voltage of the 5V rail.
   *
   * @return The controller 5V rail voltage value in Volts
   */
  static double GetVoltage5V();

  /**
   * Get the current output of the 5V rail.
   *
   * @return The controller 5V rail output current value in Amps
   */
  static double GetCurrent5V();

  /**
   * Enables or disables the 5V rail.
   *
   * @param enabled whether to enable the 5V rail.
   */
  static void SetEnabled5V(bool enabled);

  /**
   * Get the enabled state of the 5V rail. The rail may be disabled due to
   * calling SetEnabled5V(), a controller brownout, a short circuit on the rail,
   * or controller over-voltage.
   *
   * @return The controller 5V rail enabled value. True for enabled.
   */
  static bool GetEnabled5V();

  /**
   * Get the count of the total current faults on the 5V rail since the
   * controller has booted.
   *
   * @return The number of faults
   */
  static int GetFaultCount5V();

  /**
   * Get the voltage of the 6V rail.
   *
   * @return The controller 6V rail voltage value in Volts
   */
  static double GetVoltage6V();

  /**
   * Get the current output of the 6V rail.
   *
   * @return The controller 6V rail output current value in Amps
   */
  static double GetCurrent6V();

  /**
   * Enables or disables the 6V rail.
   *
   * @param enabled whether to enable the 6V rail.
   */
  static void SetEnabled6V(bool enabled);

  /**
   * Get the enabled state of the 6V rail. The rail may be disabled due to
   * calling SetEnabled6V(), a controller brownout, a short circuit on the rail,
   * or controller over-voltage.
   *
   * @return The controller 6V rail enabled value. True for enabled.
   */
  static bool GetEnabled6V();

  /**
   * Get the count of the total current faults on the 6V rail since the
   * controller has booted.
   *
   * @return The number of faults.
   */
  static int GetFaultCount6V();

  /**
   * Get the current brownout voltage setting.
   *
   * @return The brownout voltage
   */
  static units::volt_t GetBrownoutVoltage();

  /**
   * Set the voltage the roboRIO will brownout and disable all outputs.
   *
   * Note that this only does anything on the roboRIO 2.
   * On the roboRIO it is a no-op.
   *
   * @param brownoutVoltage The brownout voltage
   */
  static void SetBrownoutVoltage(units::volt_t brownoutVoltage);

  /**
   * Get the current CPU temperature.
   *
   * @return current CPU temperature
   */
  static units::celsius_t GetCPUTemp();

  /**
   * Get the current status of the CAN bus.
   *
   * @return The status of the CAN bus
   */
  static CANStatus GetCANStatus();
};

}  // namespace frc
