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
 * @file task_hal.h
 * @brief this file contain the functions prototype to create an abstract interface 
 * to manage tasks based on FreeRTOS 
 *
 * The following functions will be implemented:
 * - task_init() to initialize the task data structure
 * - task_set_priority() to set the priority of a specific task
 * - task_set_function() to set the function pointer for a specific task
 * - task_set_time() to set the time for a specific task
 * - get_task_priority() to get the priority of a specific task
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#ifndef __TASK_HAL_H__
#define __TASK_HAL_H__

#include "common.h"

#define NUM_TASKS 2 // number of tasks

typedef struct
{
	uint16_t  time; // time in milliseconds
  uint8_t priority; // task priority
  bool 	is_active; // true if task is active, false otherwise
  void (*taskFunc)(void*); // function pointer to the task function
}Task_t;

/**
 * @brief Initialize task data structure
 *
 * Initialize task data structure with default values.
 *
 * @param t Task_t struct pointer   
 * @param size 8-bit value that indicate number of digital array 
 *
 * @return void
 */
void task_init(Task_t* t, uint8_t size);

/**
 * @brief Set priority for a specific task
 *
 * Set the priority for a specific task in the task data structure.
 *
 * @param t Task_t struct pointer
 * @param channel 8-bit value that indicate channel of task structure
 * @param prio 8-bit value that indicate priority of the task
 * @param size 8-bit value that indicate number of tasks
 *
 * @return void
 */
void task_set_priority(Task_t* t, uint8_t channel, uint8_t prio, uint8_t size);

/**
 * @brief Set function pointer for a specific task
 *
 * Set the function pointer for a specific task in the task data structure.
 *
 * @param t Task_t struct pointer
 * @param channel 8-bit value that indicate channel of task structure
 * @param taskFunc Function pointer to the task function
 * @param size 8-bit value that indicate number of tasks
 *
 * @return void
 */
void task_set_function(Task_t* t, uint8_t channel, void (*taskFunc)(void*), uint8_t size);

/**
 * @brief Set time for a specific task
 *
 * Set the time for a specific task in the task data structure.
 *
 * @param t Task_t struct pointer
 * @param channel 8-bit value that indicate channel of task structure
 * @param time Time in milliseconds for the task
 * @param size 8-bit value that indicate number of tasks
 *
 * @return void
 */
void task_set_time(Task_t* t, uint8_t channel, uint16_t time, uint8_t size);

/**
 * @brief Get priority of a specific task
 *
 * Get the priority of a specific task in the task data structure.
 *
 * @param t Task_t struct pointer
 * @param channel 8-bit value that indicate channel of task structure
 * @param size 8-bit value that indicate number of tasks
 *
 * @return 8-bit value that indicate priority of the task
 */
uint8_t get_task_priority(Task_t* t, uint8_t channel, uint8_t size);

#endif /* __digital_hal_H__ */










