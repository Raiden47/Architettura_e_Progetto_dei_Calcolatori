/**
  ******************************************************************************
  * @file           : infr.h
  * @brief          : Header for infr.c file.
  *                   This file contains the common defines of the infrared management.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef __INFR__
#define __INFR__

// To Tweek after testing
#define MAX_RANGE 600 //centimeter
#define MED_RANGE 300 //centimeter
#define MIN_RANGE 50 //centimeter

static void max_range(void);

static void med_range(void);

static void min_range(void);

static void check_range(void);

#endif //__INFR__











