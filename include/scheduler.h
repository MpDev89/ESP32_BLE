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
 * @file scheduler.h
 * @brief this file contain the functions prototype to manage the scheduler
 *
 * The following functions will be implemented:
 * - scheduler_init() to initialize the scheduler
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "common.h"
#include "HAL/task_hal.h"

#define TASK1_ch 0
#define TASK1_PRIO 1
#define TASK1_TIME 100
#define TASK2_ch 1
#define TASK2_PRIO 2
#define TASK2_TIME 500

/**
 * @brief Initialize scheduler
 *
 * Initialize scheduler to manage tasks and their execution.
 *
 * NO parameters are required for this function.
 *
 * @return void
 */
void scheduler_init();

#endif /* __PERIPHERAL_H__ */