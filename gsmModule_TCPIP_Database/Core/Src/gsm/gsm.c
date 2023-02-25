/*
 * gsm.c
 *
 *  Created on: 25 Şub 2023
 *      Author: abdul
 */
#include "gsm.h"


/*
Quectel_Ltd
Quectel_M66huartGSM
Revision: M66FARxxAxx
 * */
char ATI[3]="ATI";

/*
<sn> IMEI of the telephone
 * */
char imei[6]="AT+GSN";

/*
<mode>
0 PDU mode
1 Text mode
 * */
char SMSMessageFormat[9]="AT+CMGF=1"; // GSM Modülünü Metin Moduna ayarlar
char sendMessageNumber[23]="AT+CMGS=\"+905375950687\""; //Mesaj gönderilecek Cep telefon numaranizi girin
char sendMessageData[14]="abdullahYuksel";// Göndermek istediğiniz SMS metni

/*
<state> 0 No initialization
1 Ready to execute AT command
2 Phonebook has finished initialization
3 SMS has finished initialization
 * */
char QueryStateofInitialization[11]="AT+QINISTAT";// Başlatma Durumunu Sorgula

/*
<status> 255 Not ready to retrieve network status
0 Work in normal state
1 No available cell
2 Only limited service is available*/
char QueryGSMNetworkStatus[11]="AT+QNSTATUS";//GSM Şebeke Durumunu Sorgula

/*
<enable>
0 Disable to synchronize time from GSM network
1 Enable to synchronize time from GSM network
If the function is enabled, on receiving network time message, an unsolicited indication
is shown in the form: “+QNITZ: <time>,<ds>”

<time> String type value. Format is "yy/MM/dd,hh:mm:ss±zz,ds", where characters indicate year
(two last digits), month, day, hour, minutes, seconds and time zone (indicates the
difference, expressed in quarters of an hour, between the local time and GMT; range:
-47...+48). E.g. 6th of May 2004, 22:10:00 GMT+2 hours

*/
char NetworkTimeSynchronization[10]="AT+QNITZ=1";//Ağ Saati Senkronizasyonu
char LatestNetworkTimeSynchronized[9]="AT+QLTS=2";//Senkronize Edilen En Son Ağ Zamanını Elde Edin

/*
<enable>
Indicates whether to show an unsolicited event code that indicates whether the SIM has
been inserted or removed
 0 Switch off detecting SIM card
1 Switch on detecting SIM card

<insert_status>
Indicates whether SIM card has been inserted
0 Low level of pin indictes SIM card is present
0 High level of pin indictes SIM card is present
 * */
char SIMInsertedStatusActive[13]="AT+QSIMSTAT=1";//SIM Takılı Durum algılama aktifleştirme
char SIMInsertedStatusReporting[12]="AT+QSIMSTAT?";//SIM Takılı Durum Raporlama

/*
<n> 0 Disable network registration unsolicited result code
1 Enable network registration unsolicited result code +CGREG:<stat>
2 Enable network registration and location information unsolicited result code
+CGREG: <stat>[,<lac>,<ci>]
<stat> 0 Not registered, ME is not currently searching a new operator to register to
1 Registered, home network
2 Not registered, but ME is currently searching a new operator to register to
3 Registration denied
4 Unknown
5 Registered, roaming
<lac> String type; two byte location area code in hexadecimal format (e.g. "00C3" equals 195 in
decimal)
<ci> String type; two bytes cell ID in hexadecimal format
*/
char NetworkRegistrationL1[10]="AT+CGREG=2";//Ağ Kayıt Durumu
char NetworkRegistrationStatus[9]="AT+CGREG?";//Ağ Kayıt Durumu Sorgulama

/*
<stat> 0 Unknown
1 Operator available
2 Operator current
3 Operator forbidden

<oper> Operator in format as per <mode>

<mode> 0 Automatic mode; <oper> field is ignored
1 Manual operator selection; <oper> field shall be present
2 Manual deregister from network
3 Set only <format> (for read Command +COPS?) – not shown in Read Command
response
4 Manual/automatic selected; if manual selection fails, automatic mode
(<mode>=0) is entered

<format> 0 Long format alphanumeric <oper>;can be up to 16 characters long
1 Short format alphanumeric <oper>
2 Numeric <oper>; GSM Location Area Identification number
 * */
char OperatorSelection[8]="AT+COPS?";//Operator bilgisi

/*
<rssi> 0 -113 dBm or less
1 -111 dBm
2...30 -109... -53 dBm
31 -51 dBm or greater
99 Not known or not detectable

<ber> (in percent):
0...7 As RXQUAL values in the table in GSM 05.08 subclause 8.2.4
99 Not known or not detectable
 * */
char OperatorSignal[8]="AT+CSQ";//Operator sinyal


char Dial_Call[15]="ATD05375950687;";//ARAMA
char TerminateCall[4]="ATH0";//KAPATMA


uint8_t ctrl_z= 26; // '26', 0x1A, '0x1A' (I have tried these 3 options also)

void quectell_begin();
gsm_t quectell_message_data(char *num,char *message);
gsm_t quectell_ATcommand_data(char *request, uint8_t try);

gsm_t quectell_ATcommand_data(char *request, uint8_t try)
{
	struct gsm Paket={"\0"};
    char *receive = malloc(200);
    char *sendreceive = malloc(200);
    int request_len = 1;

	while(try)
	{
		try--;
		Paket.trySended++;
		request_len = strlen(request);
		char fianlRequest[request_len+2];
		sprintf(fianlRequest,"%s\r\n",request);
		HAL_Delay(100);
		HAL_UART_ErrorCallback(&huart1);
		HAL_UART_Transmit(&huart1,(uint8_t*) fianlRequest, strlen(fianlRequest), 250);
		HAL_UART_ErrorCallback(&huart1);
		HAL_UART_Receive(&huart1,(uint8_t*) receive, 100, 3000);
		HAL_Delay(300);

		int receive_length = strlen(receive);

		while(receive_length)
		{
			if((receive[receive_length-5]=='\r')
				&& (receive[receive_length-4]=='\n')
				&& (receive[receive_length-3]=='O')
				&& (receive[receive_length-2]=='K')
				&& (receive[receive_length-1]=='\r')
				&& (receive[receive_length]=='\n')
				)
			{
				strncpy(&Paket.data[0],&receive[0],receive_length-6);
				Paket.len=receive_length-6;
				receive_length=0;
				Paket.result = RESULT_OK;
				try=0;
				return Paket;
			}
			else if((receive[receive_length-14]=='C')
				&& (receive[receive_length-13]=='M')
				&& (receive[receive_length-12]=='E')
				&& (receive[receive_length-11]==' ')
				&& (receive[receive_length-10]=='E')
				&& (receive[receive_length-9]=='R')
				&& (receive[receive_length-8]=='R')
				&& (receive[receive_length-7]=='O')
				&& (receive[receive_length-6]=='R')
				&& (receive[receive_length-5]==':')
				&& (receive[receive_length-4]==' ')
				)
			{
				strncpy(&Paket.errorCode[0],&receive[receive_length-3],4);
				Paket.len=receive_length-15;
				receive_length=0;
				Paket.result = RESULT_ERROR;
				try=0;
				return Paket;
			}
			else if((receive[receive_length-1]=='>')
				&& (receive[receive_length]==' ')
				)
			{
				Paket.len=receive_length-15;
				receive_length=0;
				Paket.result = RESULT_MESSAGE;
				try=0;
				return Paket;
			}
			else receive_length--;
		}
		Paket.result = ERROR;
	}

	return Paket;
}

gsm_t quectell_message_data(char *num,char *message)
{
	struct gsm messagePaket={"\0"};
	char msg_read1[] = "AT+CPMS=\"SM\",\"SM\",\"SM\"";

	messagePaket= quectell_ATcommand_data(msg_read1,10);

	HAL_Delay(1000);
	memset(&messagePaket, '\0', sizeof(messagePaket));
	messagePaket= quectell_ATcommand_data(SMSMessageFormat,10);

	HAL_Delay(1000);
	memset(&messagePaket, '\0', sizeof(messagePaket));
	messagePaket= quectell_ATcommand_data(num,10);

	if(messagePaket.result == RESULT_MESSAGE)
	{
		memset(&messagePaket, '\0', sizeof(messagePaket));
		messagePaket= quectell_ATcommand_data(message,10);
		memset(&messagePaket, '\0', sizeof(messagePaket));
		messagePaket= quectell_ATcommand_data((char*) &ctrl_z,10);
	}

	HAL_Delay(1000);

	return messagePaket;
}

void quectell_begin()
{
	HAL_GPIO_WritePin(GSM_POWER_GPIO_Port, GSM_POWER_Pin, GPIO_PIN_RESET);
 	HAL_Delay(2000);
	HAL_GPIO_WritePin(GSM_POWER_GPIO_Port, GSM_POWER_Pin, GPIO_PIN_SET);
 	HAL_Delay(5000);
}
