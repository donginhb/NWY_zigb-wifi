#ifndef __DATATRANSFER_H_
#define __DATATRANSFER_H_

#include "Driver_USART.h"
#include "IO_Map.h"
#include "delay.h"

#include "stdio.h"
#include "string.h"
#include "stdarg.h"

#define WIFI_FRAME_HEAD		0x7F
#define ZIGB_FRAME_HEAD		0xFE

#define WIFI_MODE_AP_STA	0x0A
#define WIFI_MODE_AP		0x0B
#define WIFI_MODE_STA		0x0C

#define CONNECT0		0x01
#define CONNECT1		0x02
#define CONNECT2		0x04
#define CONNECT3		0x08
#define CONNECT4		0x10

#define DbugP1			Driver_USART1
#define DbugP2			Driver_USART2
#define DataTransP1		Driver_USART3
#define DataTransP2		Driver_USART4
#define DataTransP3		Driver_USART5

#define DbugP1TX		Driver_USART1.Send
#define DbugP1RX		Driver_USART1.Receive
#define DbugP2TX		Driver_USART2.Send
#define DbugP2RX		Driver_USART2.Receive
#define DataTransP1TX	Driver_USART3.Send
#define DataTransP1RX	Driver_USART3.Receive
#define DataTransP1TR	Driver_USART3.Transfer
#define DataTransP2TX	Driver_USART4.Send
#define DataTransP2RX	Driver_USART4.Receive
#define DataTransP2TR	Driver_USART4.Transfer
#define DataTransP3TX	Driver_USART5.Send
#define DataTransP3RX	Driver_USART5.Receive
#define DataTransP3TR	Driver_USART5.Transfer

#define DataTransP1_RST	PAout(1)
#define DataTransP2_RST	PEout(6)
#define DataTransP3_RST	PAout(12)

#define	FRAME_SIZEDbugP1	 	100
#define	FRAME_SIZEDbugP1	 	100
#define	FRAME_SIZEDataTransP1	100
#define	FRAME_SIZEDataTransP2	100
#define	FRAME_SIZEDataTransP3	100

#define comObj_DbugP1		0xA1
#define comObj_DbugP2		0xA2
#define comObj_DataTransP1	0xA3
#define comObj_DataTransP2	0xA4
#define comObj_DataTransP3	0xA5

typedef struct WIFI_Init_datsAttr{

	char *wifiInit_reqCMD;		//ATָ��
	char *wifiInit_REPLY[2];	//��Ӧָ��
	u8 	  REPLY_DATLENTAB[2];	//��Ӧָ���
	u16   timeTab_waitAnsr;		//�ȴ���Ӧʱ��
}datsAttr_wifiInit;

typedef enum datsWIFI_structType{

	wifiTP_NULL = 0,
	wifiTP_MSGCOMMING,
	wifiTP_ntCONNECT,
	wifiTP_ntDISCONNECT,
}datsWIFI_sttType;

typedef struct WIFI_datsTrans_datsAttr{

	datsWIFI_sttType datsType:5;
	
	u8	linkObj;
	u8	CMD[2];
	u8	dats[100];
	u8	datsLen;
}datsAttr_WIFITrans;

/*Zigbee�ڵ��豸��Ϣ�������ݽṹ*/
typedef struct ZigB_nwkState_Form{

	u16	nwkAddr;
	u8	psyAddr;
	u8	extAddr;
	u16	onlineDectect_LCount;
	
	struct ZigB_nwkState_Form *next;
}nwkStateAttr_Zigb;

typedef struct ZigB_Init_datsAttr{

	u8 	 zigbInit_reqCMD[2];	//����ָ��
	u8 	 zigbInit_reqDAT[150];	//��������
	u8	 reqDAT_num;			//�������ݳ���
	u8 	 zigbInit_REPLY[150];	//��Ӧ����
	u8 	 REPLY_num;				//��Ӧ�����ܳ���
	u16  timeTab_waitAnsr;		//�ȴ���Ӧʱ��
}datsAttr_ZigbInit;

typedef struct ZigB_datsRXAttr_typeMSG{

	bool ifBroadcast;	//�Ƿ�Ϊ�㲥
	u16	 Addr_from;		//����Դ��ַ��������
	u8	 srcEP;			//�����ն˵�
	u8	 dstEP;			//�ռ��ն˵�
	u16	 ClusterID;		//��ID
	u8	 LQI;			//��������
	u8 	 datsLen;		//���ݳ�
	u8	 dats[100];		//����
}datsAttr_ZigbRX_tpMSG;

typedef struct ZigB_datsRXAttr_typeONLINE{

	u16	 nwkAddr_fresh;		//�����߽ڵ�����̵�ַ
}datsAttr_ZigbRX_tpONLINE;

typedef union ZigB_datsRXAttr{

	datsAttr_ZigbRX_tpMSG 		stt_MSG;
	datsAttr_ZigbRX_tpONLINE	stt_ONLINE;
}ZigbAttr_datsZigbRX;

typedef enum datsZigb_structType{

	zigbTP_NULL = 0,
	zigbTP_MSGCOMMING,
	zigbTP_ntCONNECT,
}datsZigb_sttType;

typedef struct ZigBAttr_datsRX{

	datsZigb_sttType datsType:4;	//�������ͣ���Զ����Ϣ���ݻ���ϵͳ���ݵȣ�
	ZigbAttr_datsZigbRX datsSTT;
}datsAttr_ZigbTrans;

#define datsTransCMD_length	2
typedef struct STT_datsTrans_CMD{

	u8 datsCMDRX[datsTransCMD_length];
	u8 datsCMDTX[datsTransCMD_length];
}sttDatsTrans_CMD;

typedef struct STTthreadDatsPass_conv{	//�������ݴ�����������1�����������շ�

	u8	psyAddr;
	u8	extAddr;
	u8	dats[100];
	u8  datsLen;
}stt_threadDatsPass_conv;

typedef struct STTthreadDatsPass_devQuery{	//�������ݴ�����������2��zigbee�豸����ѯ

	u8	infoDevList[100];
	u8  infoLen;
}stt_threadDatsPass_devQuery;

typedef union STTthreadDatsPass_dats{	//�������ݴ����������͹�����

	stt_threadDatsPass_conv 	dats_conv;		//����1����
	stt_threadDatsPass_devQuery	dats_devQuery;	//����2����
}stt_threadDatsPass_dats;

typedef enum threadDatsPass_msgType{	//�������ݴ�����������ö��

	conventional = 0,
	listDev_query,
}threadDP_msgType;

typedef struct STTthreadDatsPass{	//ͨ�ý������ݴ���ṹ��

	threadDP_msgType msgType;		//����˵��
	stt_threadDatsPass_dats dats;	//����ʵ�壨��������������������ͣ����ν���������һ�֣�
}stt_threadDatsPass;

void USART1_DbugP1_Init(void);
void USART2_DbugP2_Init(void);
void USART3_DataTransP1_Init(void);
void USART3_DataTransP2_Init(void);
void USART5_DataTransP3_Init(void);

void msgQueueInit(void);
void osMemoryInit(void);

void com1DbugP1_Thread	(const void *argument);
void com2DbugP2_Thread	(const void *argument);
void com3DataTransP1_Thread	(const void *argument);
void com4DataTransP2_Thread	(const void *argument);
void com5DataTransP3_Thread	(const void *argument);

void TimerZigbDevManage_Callback(void const *arg);

void communicationActive(uint8_t comObj);

#endif
