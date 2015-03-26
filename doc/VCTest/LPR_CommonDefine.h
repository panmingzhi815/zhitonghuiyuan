//LPR_CommonDefine.hͷ�ļ�
//��������ӿ����õ��ĺꡢö�١��ṹ������͵Ķ���
#pragma once

#define INVALID_HANLE	0	//��Ч���
#define IP_MAX_LEN	16	//IP��ַ�ַ�����󳤶�
#define MACADDR_LEN	6	//MAC��ַ
#define VERSION_LEN	255	//�汾����
#define MAX_PLATE_LEN	16	//���ƺ��볤��
#define MAX_TIME_LEN	8	//ʱ�䳤��
#define AUTHORINFO_LEN	100	//��Ȩ�����Ϣ����
#define SERIALNO_LEN	20	//���кų���
#define FEEKMSG_MAX_LEN	100	//����������Ϣ����
#define CMD_LEN 512 //�����

#define CMD_READ 0//��ָ��
#define CMD_WRITE 1//дָ��

#define ENABLE_FUNCTION 1//ĳ���ʹ��
#define DISABLE_FUNCTION 0//ĳ��ܲ�ʹ��



typedef void * PDEVICEHANDLE;

//��������ֵ
typedef enum
{
	RESULT_OK = 0,//ִ�гɹ�
	INIT_SUCCESS = 1,//�Ѿ���ʼ��
	NO_INIT = 2,   //δ��ʼ��
	PARAMS_ERROR = 3,//��������ȷ
	SOCKET_NULL = 4,//SOCKET���ΪNULL
	THREAD_FAIL = 5,//�߳�ʧ��
	CREATE_FAIL = 6, //��������ʧ��
	SEND_FAIL = 7,//��������ʧ��
	NO_FIND_DEVICE = 8,//û�з����豸
	DEVICE_OPENED = 9,//�豸�Ѿ���
	DEVICE_DISCONNECT = 10,//���豸�����ӶϿ�
	CONTORL_NOCONNECTION = 11,//���ƶ˿�δ����
	NO_RECEIVED_DATA = 12,//��������û���յ�����
	OTHER_ERROR = 100,//��������
	TIME_OUT = 209//����ִ�г�ʱ
}FEEKBACK_TYPE;

//�豸״̬
typedef enum 
{
	CONNECT_SUCCESS = 0,//���ӳɹ�
	CREATE_ERROR = 1,//���ɾ������
	CONNECT_ERROR = 2,//���Ӵ���
	ABNORMALNET_ERROR = 3,//�����쳣����
	DEVICE_RESET = 4//�豸��λ

} DEVICE_STATUS;

//������ɫ
typedef enum 
{
	NON_PLATE = 0,//δ֪������ɫ
	BLUE_COLOR,//��ɫ
	WHITE_COLOR,//��ɫ
	BLACK_COLOR,//��ɫ
	YELLOW_COLOR//��ɫ
} PLATE_COLOR;
//��������
typedef enum
{
	UNKNOWN_TRIGGER_MODE = 0,//δ֪
	VIDEO_TRIGGER_MODE = 1,//��Ƶ
	LINE_TRIGGER_MODE = 2,//��Ȧ
	SOFT_TRIGGER_MODE//ģ��
}DEVICE_TRIGGERMODE;
typedef enum
{
	NORMAL_USER  = 0,// �����û�
	UNKNOWN_USER = 1//δ��Ȩ�û�

}USER_TYPE;

//����ֵ
typedef enum 
{
	SHUTTER_50 = 6,//1/50
	SHUTTER_75,//1/75
	SHUTTER_100,//1/100
	SHUTTER_120,//1/120
	SHUTTER_150,//1/150
	SHUTTER_215,//1/215
	SHUTTER_300,//1/300
	SHUTTER_425,//1/425
	SHUTTER_600,//1/600
	SHUTTER_1000,//1/1000
	SHUTTER_1250,//1/1250
	SHUTTER_1750,//1/1750	
	SHUTTER_2500,//1/2500
	SHUTTER_3500,//1/3500
	SHUTTER_6000,//1/6000
	SHUTTER_10000 //1/10000
} SHUTTER_PARAMS;
//��ָ������
typedef enum
{
	SYSTEM_CMD = 0x00,//ϵͳָ��
	LIGHT_CMD = 0x20,//����ָ��
	OSD_CMD = 0x30,//����ָ��
	EPLD_CMD = 0x60,//��Ƭ��ָ��
	LED_CMD = 0x70,//����ָ��
	CAMERA_CMD = 0x71,//�������ָ��
	MOVE_CMD = 0x80,//����ָ��
	CAPTURE_DATA = 0xFF//ץ������
}MAIN_CMD;
//ϵͳָ������
typedef enum
{	
	HEART_CMD = 0x00,//����
	VERSION_INFO = 0x04,//�汾��Ϣ
	IMAGE_QUALITY = 0x05,//ͼ��ѹ����
	DEVICE_RESTART = 0x0C,//�Ƿ�����
	RESTART_TIME = 0x0D,//����ʱ��
	OCR_PARAMS = 0x16,//ʶ�����
	SERIRAL_NO = 0x18,//�豸���к�
	ALG_PARAMS = 0x1A,//�㷨����
	DEVICE_ID = 0x1B,//�豸���
	DEVICE_CODE = 0x1C,//������
	AUTHOR_INFO = 0x1D,//��Ȩ��
	AUTHOR_VALIDTIME = 0x23,//��Ȩ��ֹʱ��
	WORK_MODE = 0x1E,//����ģʽ��0������1�ع����ģʽ
	VERIFYTIME_MODE = 0x1F,//Уʱ��ʽ0 SDK 1 NTP
	NTP_SERVERIP = 0x20,//NTP����IP
	NTP_TIMEOUT = 0x21
}SYSTEM_SUBCMD;
//�汾����
typedef enum
{
	MAIN_VERSION = 0x00,//���汾
	DSP_SUBVERSION  = 0x01, //�ΰ汾
	MCU_VERSION  = 0x02, //MCU�汾
	ALG_VERSION = 0x03,//ʶ���㷨�汾
	JPG_VERSION = 0x04,//JPG�汾��Ϣ
	EEPROM_VERSION = 0x05//EEPROM�汾��
}VERSION_OBJECT;

//ͼ��ѹ����
typedef enum
{
	BIG_IMAGE_QUALITY = 0x00,//��ͼ
	CIF_IMAGE_QUALITY  = 0x01, //CIFͼ
	PLATE_IMAGE_QUALITY  = 0x02//����ͼ
}IMAGE_QUALITY_OBJECT;

//����ָ������
typedef enum
{	
	LIGHT_MODE = 0x00,//����ģʽ
	AUTOLIGHT_ENABLE = 0x01,//�Զ�����ʹ��
	SYSTEM_TIME= 0x02,//ϵͳʱ��
	LIGHT_PARAMS = 0x03,//���������������
	IMAGE_BRIGHTNESS = 0x07,//ͼƬ����
	CAMERA_CURSTATUS = 0x0A,//�����ǰ״̬
	CAMERA_PARAMS = 0x0B,//����ͷ����
	CUR_LIGHTBASE = 0x0D,//��ǰ�����׼
	LIGHT_VALIDNUM = 0x0E,//������Ч����
	DAY_EXPOSURE_COMPENSATION = 0x0F,//�����عⲹ��
	NIGHT_EXPOSURE_COMPENSATION = 0x10,//ҹ���عⲹ��
	REF_GAIN = 0x11,//�ο�����
	REF_BRIGHTNESS = 0x12//�ο�����

}LIGHT_SUBCMD;
//����ģʽֵ
typedef enum
{
	AUTO_LIGHT = 0x00,//�Զ�����
	MIXED_LIGHT = 0x01//��ϵ���
}LIGHT_MODE_VALUE;

//�����ǰ״̬����
typedef enum
{
	SHUTTER_VALUE = 0x00,//����
	APARTURE_VALUE = 0x01,//��Ȧ
	GAIN_VALUE = 0x02,//����
	VIEW_VALUE = 0x03,//��Ұ
	F_VALUE = 0x04,//����
	BRIGHT_NUM = 0x05,//����
	DARK_NUM = 0x06,//����
}CAMERA_CURSTATUS_PARAMS;

//LEDָ������
typedef enum
{	
	ENABLE_LED = 0x00,//ʹ��
	OPEN_CLOSE_BASE = 0x01,//���صƻ�׼
	LED_BRIGHTNESS = 0x02,//LED����
	LED_STATUS = 0x03,//LED״̬
	LED_DELAY = 0x04//LED�ӳ�
}LED_SUBCMD;
//OSD����ָ������
typedef enum
{	
	OSD_ENABLE = 0x0C,//ʹ�ܿ���
	OSD_INFO = 0x0D//��Ϣ����
}OSD_SUBCMD;

//�������ָ��
typedef enum
{
	POINT_EXPOSURE = 0x06,//���ع�
	CAMERA_PHASE = 0x07//�����λ

}CAMERA_CONTROL_CMD;



//����ʹ�ܿ��ƶ���
typedef enum
{	
	OSD_TIME_ENABLE = 0x00,//ʱ�����ʹ��
	OSD_INFO_ENABLE = 0x03,//�Զ�����Ϣ����ʹ��
	OSD_PLATE_ENABLE = 0x04//ʶ��������ʹ��

}OSD_ENABLE_OBJECT;


//EPLDָ������
typedef enum
{	
	LINE_POLARITY = 0x01,//��Ȧ��������
	CAMERA_MENU = 0x0A,//����˵�
	VIEW_F = 0x0B//��Ұ����
}EPLD_SUBCMD;


//��Ұ�������
typedef enum
{
	VIEW_OBJECT = 0x00,//��Ұ
	F_OBJECT = 0x01//����
}VIEW_F_OBJECT;

//���صƻ�׼����
typedef enum
{
	OPEN_BASE = 0x00,//���ƻ�׼
	CLOSE_BASE = 0x01//�صƻ�׼
}LED_STATUS_OBJECT;


//����ģʽ����ʹ��
typedef enum
{
	NORMAL_WORKMODE = 0,//��������ģʽ
	VIDEO_EXPOSURE = 1//��Ƶ�ع����ģʽ
}WORKMODE;
//�������
typedef struct tagNetParams
{
	unsigned char ucDeviceIP[IP_MAX_LEN];//�豸IP
	unsigned char ucMaskIP[IP_MAX_LEN];//�������� 
	unsigned char ucGateIP[IP_MAX_LEN];//����IP
	unsigned char ucMac[MACADDR_LEN];//MAC��ַ
}NetParams,*PNetParams;

//�豸������Ϣ
typedef struct tagDeviceInfo
{
	NetParams DeviceNetInfo;//�豸������Ϣ����
	unsigned char ucMAC[MACADDR_LEN];//MAC��ַ
	unsigned char ucDeviceVersion[VERSION_LEN];//�豸�汾��Ϣ
	unsigned char ucConnectNum;//�û�������
}DeviceInfo,*PDeviceInfo;

//�豸״̬
typedef struct tagDeviceStatus
{
	PDEVICEHANDLE pHandle;//�豸���
	unsigned char ucDeviceIP[IP_MAX_LEN];//�豸IP
	DEVICE_STATUS status;//�豸״̬

}DeviceStatus,*PDeviceStatus;
//�������
typedef struct tagOutputContent
{
	bool bOutputBigImage;//�Ƿ������ͼ
	bool bOutputCIFImage;//�Ƿ����CIFͼ
	bool bOutputPlateImage;//�Ƿ��������ͼ
}OutputContent,*POutputContent;

//ץ������
typedef struct tagVehicleData
{
	PDEVICEHANDLE pDeviceHandle;//�豸���
	unsigned short usSerialNO;//���к�
	unsigned char ucDeviceIP[IP_MAX_LEN];//�豸IP
	unsigned int ui32DeviceID;							//�豸ID
	USER_TYPE ui32UserType;							//��ʾ�û�����:0 �����û���1 δ��Ȩ�û�������ֵ����
	unsigned int ui32Brightness;						//����ֵ
	DEVICE_TRIGGERMODE triggermode;						//��������:1 ��Ƶ 2 ��Ȧ 3 ģ�� 0 δ֪ ������ֵ����
	unsigned char ai8UserDefineInfo[VERSION_LEN];	//�û��Զ�����Ϣ
	unsigned char ucTime[MAX_TIME_LEN];//ʱ�䣬�꣨���������ݣ����¡��ա�ʱ���֡��롢���루ռ�����ֽڣ�
	unsigned char ucPlate[MAX_PLATE_LEN];//���ƺ���
	PLATE_COLOR   PlateColor;//������ɫ
	unsigned char *pucBigImage;//ץ�Ĵ�ͼ����
	unsigned int  uiBigImageLen;//ץ�Ĵ�ͼ���ݳ���
	unsigned short usBigImageWidth;//ץ�Ĵ�ͼ���
	unsigned short usBigImageHeight;//ץ�Ĵ�ͼ�߶�
	unsigned char *pucCIFImage;//ץ��CIFͼ����
	unsigned int  uiCIFImageLen;//ץ��CIFͼ���ݳ���
	unsigned short usCIFImageWidth;//ץ��CIFͼ���
	unsigned short usCIFImageHeight;//ץ��CIFͼ�߶�

	unsigned char *pucPlateImage;//ץ�ĳ���ͼ����
	unsigned int  uiPlateImageLen;//ץ�ĳ���ͼ���ݳ���
	unsigned short usPlateImageWidth;//ץ�ĳ���ͼ���
	unsigned short usPlateImageHeight;//ץ�ĳ���ͼ�߶�
}VehicleData,*PVehicleData;



//ʵʱJPG��
typedef struct tagJPGData
{
	PDEVICEHANDLE pDeviceHandle;//�豸���
	unsigned char ucDeviceIP[IP_MAX_LEN];//�豸IP
	unsigned char *pucImage;//һ֡ʵʱJPG������
	unsigned int  uiImageLen;// һ֡ʵʱJPG�����ݳ���
	unsigned short usImageWidth;// һ֡ʵʱJPG�����
	unsigned short usImageHeight;// һ֡ʵʱJPG���߶�
	unsigned short usLeft;
	unsigned short usRight;
	unsigned short usTop;
	unsigned short usBottom;
}JPGData,*PJPGData;

//�豸�汾��Ϣ
typedef struct tagVersionInfo
{
	unsigned char ucMainVer[VERSION_LEN];//���汾
	unsigned char ucDSPVer[VERSION_LEN];//�ΰ汾
	unsigned char ucMCUVer[VERSION_LEN];//MCU�汾
	unsigned char ucOCRVer[VERSION_LEN];//ʶ���㷨�汾
	unsigned char ucEPROMVer[VERSION_LEN];//EEPROM�汾��
}VersionInfo,*PVersionInfo;

//�����ṹ��
typedef struct tagParamsInfo
{
	unsigned char ucMainCmd;//��ָ��
	unsigned char ucSubCmd;//��ָ��
	bool          bHasObject;//�Ƿ��ж����
	unsigned char ucObject;//�����
	unsigned char ucCmdType;//�������ͣ�������д
	unsigned short usCmdLen;//�����
	unsigned char ucCmd[CMD_LEN];//��������
}ParamsInfo,*PParamsInfo;

//�㷨����
//���з���
typedef enum 
{
	LEFT_TOP = 0,//������ʻ
	LEFT_BOTTOM,//������ʻ
	RIGHT_TOP,	//������ʻ
	RIGHT_BOTTOM,//������ʻ
	UNDECIDED	//��ȷ��
}MAINDIRECT;

//������ʽ
typedef enum  
{
		LINE_TRIGGER = 0,	// ��Ȧ����
		VIDEO_TRIGGER = 2   //��Ƶ����
}TRIGGER_MODE;


typedef struct tagAlgParams
{
	TRIGGER_MODE TriggerMode;		// ��Ȧ��������Ƶ����
	unsigned short usLeft;			//���������߽�
	unsigned short usTop;			//��������ϱ߽�
	unsigned short usRight;			//��������ұ߽�
	unsigned short usBottom;		//��������±߽�
	MAINDIRECT MainDirect;			// ���з������ϣ����£����ϣ�����
	bool bGetOppEn;					// �Ƿ�ץ������
}AlgParams,*PAlgParams;