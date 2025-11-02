/******************************************************************************
 *
 * Copyright (c) 2025 Marconatale Parise. All rights reserved.
 *
 * This file is part of proprietary software. Unauthorized copying, distribution,
 * or modification of this file, via any medium, is strictly prohibited without
 * prior written permission from the copyright holder.
 *
 *****************************************************************************/


#include "scheduler.h"
#include "HAL/ble_hal.h"



void setup() {
  
  Serial.begin(115200);
  Serial.println("Enter commands in format: 'SET <parameter> <value>#'");
  Serial.println("Parameters: TEMP, HUMID, SOLAR");
  ble_init();
  scheduler_init();
  
}

void loop() {}
