/**
  ******************************************************************************
  * File Name          : bmx280.h
  * Description        : This file provides headers for the code of the
  *                      configuration of the GPIO instances for a BMx280 sensor.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BMX280_H
#define __BMX280_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _BMX280REG_;


/* Private defines -----------------------------------------------------------*/
typedef enum {
  BMP280  = 0,
  BME280
} BMx280_SensorTypeDef;


/* BMX280 Registry Flags */



/* Exported functions prototypes ---------------------------------------------*/
void BMx280_Init(BMx280_SensorTypeDef sensorType);
void BMx280_Measurment(BMx280_SensorTypeDef sensorType);



#ifdef __cplusplus
}
#endif
#endif /*__BMX280_H */
