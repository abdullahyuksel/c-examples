/*
 * sensor.h
 *
 *  Created on: 26 Şub 2023
 *      Author: abdul
 */

#ifndef SRC_SENSOR_SENSOR_H_
#define SRC_SENSOR_SENSOR_H_

#include "main.h"
#include "gsm.h"

typedef struct{
char DeviceID[15];
char Name[16];
char Date[12];
char Time[12];
long LogType;
float VL1;
float VL2;
float VL3;
float IL1;
float IL2;
float IL3;
float P1;
float P2;
float P3;
float FreqL1;
float Rezerve1;
float Rezerve2;
float Temperature;
float Hummudity;
float Smoke;
float GyroX;
float GyroY;
float GyroZ;
float AccX;
float AccY;
float AccZ;
float Longitude;
float Latitude;
float Status;
float PowerSupply;
}sensorPacket_t;

extern void gsm_timeDate_parse( gsm_t *gsm, sensorPacket_t *sensorPacket);
extern void gsm_imei_parse(gsm_t *gsm, sensorPacket_t *sensorPacket);


#endif /* SRC_SENSOR_SENSOR_H_ */
