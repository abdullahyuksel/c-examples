/*
 * sensor.c
 *
 *  Created on: 26 Şub 2023
 *      Author: abdul
 */


#include "sensor.h"
sensorPacket_t sensorPacket;
void gsm_timeDate_parse( gsm_t *gsm, sensorPacket_t *sensorPacket);
void gsm_imei_parse(gsm_t *gsm, sensorPacket_t *sensorPacket);

void gsm_timeDate_parse( gsm_t *gsm, sensorPacket_t *sensorPacket)
{

    //	"AT+QLTS\r\r\n+QLTS\0 \"23/02/26,16\015:39+12,0\"\r"
	char *pkomut;
	char *pbilgi;
	char komut[20];
	char bilgi[80];
	pkomut = strtok (gsm->data,"\"");

	if(pkomut != NULL)
	{
		pkomut = strtok (NULL, "\"");
	}
	if(pkomut != NULL)
	{
		sprintf(bilgi,"%s",pkomut);
	}

	pbilgi = strtok (bilgi, ",");
	if(pbilgi != NULL)
	{
	  sprintf(sensorPacket->Date,"%s",pbilgi);
	  pbilgi = strtok (NULL, "+");
	}
	if(pbilgi != NULL)
	{
	  sprintf(sensorPacket->Time,"%s",pbilgi);
	}

}

void gsm_imei_parse(gsm_t *gsm, sensorPacket_t *sensorPacket)
{
	//"AT+GSN\r\r\n865733020395836\r"
	char *pkomut;
	char *pbilgi;
	char bilgi[80];
	pkomut = strtok (gsm->data,"\n");

	if(pkomut != NULL)
	{
		pkomut = strtok (NULL, "\r");
	}
	if(pkomut != NULL)
	{
		sprintf(sensorPacket->DeviceID,"%s",pkomut);
	}

}
