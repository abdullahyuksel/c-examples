/*
 * gsm.h
 *
 *  Created on: 25 Şub 2023
 *      Author: abdul
 */

#ifndef SRC_GSM_GSM_H_
#define SRC_GSM_GSM_H_

#include "main.h"

/*
Quectel_Ltd
Quectel_M66
Revision: M66FARxxAxx
 * */
extern char ATI[3];

/*
<sn> IMEI of the telephone
 * */
extern char imei[6];

/*
<mode>
0 PDU mode
1 Text mode
 * */
extern char SMSMessageFormat[9]; // GSM Modülünü Metin Moduna ayarlar
extern char sendMessageNumber[23]; //Mesaj gönderilecek Cep telefon numaranizi girin
extern char sendMessageData[14];// Göndermek istediğiniz SMS metni

/*
<state> 0 No initialization
1 Ready to execute AT command
2 Phonebook has finished initialization
3 SMS has finished initialization
 * */
extern char QueryStateofInitialization[11];// Başlatma Durumunu Sorgula

/*
<status> 255 Not ready to retrieve network status
0 Work in normal state
1 No available cell
2 Only limited service is available*/
extern char QueryGSMNetworkStatus[11];//GSM Şebeke Durumunu Sorgula

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
extern char NetworkTimeSynchronization[10];//Ağ Saati Senkronizasyonu
extern char LatestNetworkTimeSynchronized[9];//Senkronize Edilen En Son Ağ Zamanını Elde Edin

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
extern char SIMInsertedStatusActive[13];//SIM Takılı Durum algılama aktifleştirme
extern char SIMInsertedStatusReporting[12];//SIM Takılı Durum Raporlama

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
extern char NetworkRegistrationL1[10];//Ağ Kayıt Durumu
extern char NetworkRegistrationStatus[9];//Ağ Kayıt Durumu Sorgulama

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
extern char OperatorSelection[8];//Operator bilgisi

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
extern char OperatorSignal[8];//Operator sinyal


extern char Dial_Call[15];//ARAMA
extern char TerminateCall[4];//KAPATMA


extern uint8_t ctrl_z; // '26', 0x1A, '0x1A' (I have tried these 3 options also)

typedef enum
{
	RESULT_OK =1,
	RESULT_ERROR =2,
	RESULT_MESSAGE =3
}RESULTS_t;

typedef struct gsm {
  char data[100];
  char len;
  char trySended;
  char errorCode[4];
  RESULTS_t result;
}gsm_t;


extern void quectell_begin();
extern gsm_t quectell_message_data(char *num,char *message);
extern gsm_t quectell_ATcommand_data(char *request, uint8_t try);

#endif /* SRC_GSM_GSM_H_ */
