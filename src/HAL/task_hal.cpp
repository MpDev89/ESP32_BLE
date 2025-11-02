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
 * @file task_hal.c
 * @brief Abstraction of task management interface
 *
 * This implementation file provides an abstraction of task management using FreeRTOS function.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#include "HAL/task_hal.h"


Task_t task_a[NUM_TASKS] = {};

/***********************************************************
 Function Definitions
***********************************************************/
void task_init(Task_t* t, uint8_t size){
  for (int i = 0; i < size; i++){
    t[i].priority = 0;
    t[i].time = 0;
    t[i].is_active = true;
    t[i].taskFunc = NULL; // Initialize function pointer to NULL
  }
}

void task_set_priority(Task_t* t, uint8_t channel, uint8_t prio, uint8_t size){
	if(channel < size){
    if(t[channel].is_active){ 
      t[channel].priority = prio;
    }	
	}
}

void task_set_function(Task_t* t, uint8_t channel, void (*taskFunc)(void*), uint8_t size){
  if(channel < size){
    if(t[channel].is_active){ 
      t[channel].taskFunc = taskFunc;
    }	
  }
}

void task_set_time(Task_t* t, uint8_t channel, uint16_t time, uint8_t size){
  if(channel < size){
    if(t[channel].is_active){ 
      t[channel].time = time;
    }	
  }
}

uint8_t get_task_priority(Task_t* t, uint8_t channel, uint8_t size){
  if(channel < size){
    if(t[channel].is_active){ 
      return t[channel].priority;
    }else{
      return 0; // If task is not active, return 0
    }
  }else{
    return 0; // If channel is out of bounds, return 0
  }
}

