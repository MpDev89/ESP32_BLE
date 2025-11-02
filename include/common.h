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
 * @file digital_hal.h
 * @brief this file contain common macros
 *
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#ifndef __COMMON_H__
#define __COMMON_H__

#include "Arduino.h"

#ifndef SIZEOF
#define SIZEOF(x)   (sizeof(x)/sizeof(x[0]))
#endif

#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(x,...) if (DEBUG) { Serial.printf("[%lu ms]" x , millis(), ##__VA_ARGS__); }
#endif

#endif /* __COMMON_H__ */