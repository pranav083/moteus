// Copyright 2023 mjbots Robotic Systems, LLC.  info@mjbots.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// @startuml
// actor User
// User -> main: Open program
// ...
// @enduml
// 
#pragma once

#include "mbed.h"

#include "fw/millisecond_timer.h"

namespace moteus {

//////////////////////////////////////////
// The following "families" are supported:
//  moteus    - family 0
//  moteus_hp - family 1
//
// Each family has an independent hardware version timeline, and
// possibly a different mechanism for verifying hardware version
// compatibility.


// This structure is filled in once the family and hardware version
// are known.
/**
 * @brief this is moteus hardware pin function
 * @startuml
 * actor User
 *  User -> main: Open program
 * ...
 * @enduml
 *  
 */
struct MoteusHwPins {

  PinName pwm1 = PA_0_ALT0;
  PinName pwm2 = PA_1_ALT0;
  PinName pwm3 = PA_2_ALT0;

  PinName drv8323_enable = NC;
  PinName drv8323_hiz = NC;
  PinName drv8323_cs = NC;

  PinName drv8323_mosi = NC;
  PinName drv8323_miso = NC;
  PinName drv8323_sck = NC;
  PinName drv8323_fault = NC;

  PinName debug_led1 = NC;
  PinName power_led = NC;

  PinName current1 = NC;
  PinName current2 = NC;
  PinName current3 = NC;

  PinName vsense = NC;
  PinName tsense = PA_9;

  PinName msense = NC;

  float vsense_adc_scale = 0.0f;

  PinName uart_tx = NC;
  PinName uart_rx = NC;
  PinName uart_dir = NC;

  PinName as5047_cs = NC;

  PinName can_td = NC;
  PinName can_rd = NC;

  PinName debug1 = NC;
  PinName debug2 = NC;
  PinName debug_dac = PA_4;

  uint32_t model_number = 0;

  uint32_t firmware_version = 0x000105;
};


struct FamilyAndVersion {
  int family = 0;
  int hw_version = 0;
  int hw_pins = 0;
};

// Return what family we are executing on.
FamilyAndVersion DetectMoteusFamily(MillisecondTimer*);

MoteusHwPins FindHardwarePins(FamilyAndVersion);


// The "FIRMWARE_VERSION" is a misnomer.  It instead is the equivalent
// of an ABI version, and is incremented when configuration values
// change in a way that would not result in equivalent behavior across
// an upgrade/downgrade.

// Version history:

// # 0x0101 #
//
// * Fixed the calculation of feedforward voltage to have the correct
//   sign for the velocity component.  Previous firmwares,
//   inappropriately applied a negative feedforward term, which
//   counteracted rotation instead of being an actual feedforward.

// # 0x0102 #
//
// * Removed servo.feedforward_scale entirely

// # 0x0103 #
//
// * Added servo.pwm_scale, and for r4.8 boards changed the default
//   value of pwm_comp_off / pwm_comp_mag.

// # 0x0104 #
//
// * Added configurable PWM rates, which changed default values of
//   pwm_comp_mag and pwm_comp_off.

// # 0x0105 #
//
// * Switched to a new encoder and position subsystem.

#define MOTEUS_MODEL_NUMBER 0x0000
#define MOTEUS_FIRMWARE_VERSION 0x000105

extern MoteusHwPins g_hw_pins;

// Ensure the DRV8323 is turned off.
void MoteusEnsureOff();

}
