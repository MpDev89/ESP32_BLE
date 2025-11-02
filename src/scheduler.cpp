/******************************************************************************
 *
 * Copyright (c) 2025 Marconatale Parise. All rights reserved.
 *
 * This file is part of proprietary software. Unauthorized copying, distribution,
 * or modification of this file, via any medium, is strictly prohibited without
 * prior written permission from the copyright holder.
 *
 *****************************************************************************/
/**
 * @file peripheral.c
 * @brief functions to manage scheduler
 *
 * This implementation file provides scheduler functions to manage tasks and their execution.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#include "scheduler.h"
#include "HAL/ble_hal.h"


extern Task_t task_a[NUM_TASKS];
float temperature = 0.0;
float humidity = 0.0;
float solar_intensity = 0.0;

void Task1(void *pvParameters) {
  const TickType_t interval = pdMS_TO_TICKS(TASK1_TIME); // 1s
  TickType_t xLastWakeTime = xTaskGetTickCount();
  static char inputBuffer[64];
  static int bufferIndex = 0;
  
   
  while (true) {
    while (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '#') {
        if (bufferIndex > 0) {
          inputBuffer[bufferIndex] = '\0';
          // Process the command
          char command[10], parameter[10];
          float value;
          if (sscanf(inputBuffer, "%s %s %f", command, parameter, &value) == 3) {
            //DEBUG_PRINT("Received command: %s, parameter: %s, value: %.2f\n", command, parameter, value);
            if (strcmp(command, "SET") == 0) {
              if (strcmp(parameter, "TEMP") == 0) {
                if( value < -40.0 || value > 125.0 ) {
                  DEBUG_PRINT("Temperature value out of range (-40 to 125)\n");
                } else {
                  temperature = value;
                  DEBUG_PRINT("Temperature set to: %.2f\n", value);
                }
              }
              else if (strcmp(parameter, "HUMID") == 0) {
                if( value < 0.0 || value > 100.0 ) {
                  DEBUG_PRINT("Humidity value out of range (0 to 100)\n");
                } else {
                  humidity = value;
                  DEBUG_PRINT("Humidity set to: %.2f\n", value);
                }
              }
              else if (strcmp(parameter, "SOLAR") == 0) {
                if (value < 0.0 || value > 1.0 ) {
                  DEBUG_PRINT("Solar value out of range (1 - OFF or 0 - ON)\n");
                }else{
                  solar_intensity = value;
                  DEBUG_PRINT("Solar intensity set to: %.2f\n", value);
                }
              }
              else {
                DEBUG_PRINT("Invalid parameter. Use: TEMP, HUMID, or SOLAR\n");
              }
            }
          }else {
            DEBUG_PRINT("Invalid command format. Use: SET <parameter> <value>\n");
          }
          bufferIndex = 0;
        }
      }
      else if (bufferIndex < sizeof(inputBuffer) - 1) {
        inputBuffer[bufferIndex++] = c;
      }
    }
    vTaskDelayUntil(&xLastWakeTime, interval);
  }
}

void Task2(void *pvParameters) {
  const TickType_t interval = pdMS_TO_TICKS(TASK2_TIME); // 3s
  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true) {
    //Serial.printf("%lu - Task 2 completed on core %d\n", millis(), xPortGetCoreID());
    if (deviceConnected) {
      ble_transmit_temp((uint16_t)temperature);
      ble_transmit_humidity((uint16_t)humidity);
      ble_transmit_slrrad((uint16_t)solar_intensity);
    }
    vTaskDelayUntil(&xLastWakeTime, interval);
  }
}


/***********************************************************
 Function Definitions
***********************************************************/
void scheduler_init() {
    // Initialize the digital array
    task_init(task_a, NUM_TASKS);
    // Set up tasks
    task_set_priority(task_a, TASK1_ch, TASK1_PRIO, NUM_TASKS); // Set priority for Task 1
    task_set_function(task_a, TASK1_ch, Task1, NUM_TASKS); // Set function for Task 1
    task_set_time(task_a, TASK1_ch, TASK1_TIME, NUM_TASKS); // Set time for Task 1
    task_set_priority(task_a, TASK2_ch, TASK2_PRIO, NUM_TASKS); // Set priority for Task 2
    task_set_function(task_a, TASK2_ch, Task2, NUM_TASKS); // Set function for Task 2
    task_set_time(task_a, TASK2_ch, TASK2_TIME, NUM_TASKS); // Set time for Task 2

    

    xTaskCreatePinnedToCore(Task1, "Task 1", 2048, NULL, BaseType_t(get_task_priority(task_a, TASK1_ch, NUM_TASKS)) , NULL, 1); //Core 1
    xTaskCreatePinnedToCore(Task2, "Task 2", 2048, NULL, BaseType_t(get_task_priority(task_a, TASK2_ch, NUM_TASKS)) , NULL, 1); //Core 1
}



