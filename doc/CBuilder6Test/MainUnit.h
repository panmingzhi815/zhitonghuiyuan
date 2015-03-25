//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

    

#define IP_MAX_LEN 16
#define MACADDR_LEN 6
#define VERSION_LEN 255
#define MAX_TIME_LEN 8
#define MAX_PLATE_LEN 16

// �ṹ�嶨��

// �������
typedef struct tagNetParams
{
	unsigned char ucDeviceIP[IP_MAX_LEN];   // �豸IP
    unsigned char ucMaskIP[IP_MAX_LEN];     // ��������
	unsigned char ucGateIP[IP_MAX_LEN];     // ����IP
	unsigned char ucMac[MACADDR_LEN];       // MAC��ַ
} NetParams, *PNetParams;

// �豸��Ϣ
typedef struct tagDeviceInfo
{
	NetParams DeviceNetInfo;                        // �豸������Ϣ����
	unsigned char ucMAC[MACADDR_LEN];               // MAC��ַ
	unsigned char ucDeviceVersion[VERSION_LEN];     // �豸�汾��Ϣ
	unsigned char ucConnectNum;                     // �û�������
} DeviceInfo, *PDeviceInfo;

// ״̬����
typedef enum 
{
	CONNECT_SUCCESS = 0,        // ���ӳɹ�
	CREATE_ERROR = 1,           // ���ɾ������
	CONNECT_ERROR = 2,          // ���Ӵ���
	ABNORMALNET_ERROR = 3,      // �����쳣����
	DEVICE_RESET = 4            // �豸��λ

} DEVICE_STATUS;

// �豸״̬
typedef struct tagDeviceStatus
{
	void *pHandle;                              // �豸���
	unsigned char ucDeviceIP[IP_MAX_LEN];       // �豸IP
	DEVICE_STATUS status;                       // �豸״̬
} DeviceStatus,*PDeviceStatus;

// �û�����
typedef enum
{
	NORMAL_USER  = 0,       // �����û�
	UNKNOWN_USER = 1        // δ��Ȩ�û�
} USER_TYPE;

// ��������
typedef enum
{
	UNKNOWN_TRIGGER_MODE = 0,   // δ֪
	VIDEO_TRIGGER_MODE = 1,     // ��Ƶ
	LINE_TRIGGER_MODE = 2,      // ��Ȧ
	SOFT_TRIGGER_MODE           // ģ��
} DEVICE_TRIGGERMODE;

// ������ɫ
typedef enum 
{
	NON_PLATE = 0,      //δ֪������ɫ
	BLUE_COLOR,         //��ɫ
	WHITE_COLOR,        //��ɫ
	BLACK_COLOR,        //��ɫ
	YELLOW_COLOR        //��ɫ
} PLATE_COLOR;

// ץ�����ݣ�ע��C++Builderö�����Ͳ�һ��4���ֽڣ���Ҫ�ڹ���->ѡ��->����->ѡ��Treat enum type as ints��ǿ�ƽ�ö��������Ϊ4�ֽ�
typedef struct tagVehicleData
{
	void *pDeviceHandle;                                // �豸���
	unsigned short usSerialNO;                          // ���к�
	unsigned char ucDeviceIP[IP_MAX_LEN];               // �豸IP
	unsigned int ui32DeviceID;							// �豸ID
	USER_TYPE ui32UserType;							    // ��ʾ�û�����:0 �����û���1 δ��Ȩ�û�������ֵ����
	unsigned int ui32Brightness;						// ����ֵ
	DEVICE_TRIGGERMODE triggermode;						// ��������:1 ��Ƶ 2 ��Ȧ 3 ģ�� 0 δ֪ ������ֵ����
	unsigned char ai8UserDefineInfo[VERSION_LEN];	    // �û��Զ�����Ϣ
	unsigned char ucTime[MAX_TIME_LEN];                 // ʱ�䣬�꣨���������ݣ����¡��ա�ʱ���֡��롢���루ռ�����ֽڣ�
	unsigned char ucPlate[MAX_PLATE_LEN];               // ���ƺ���
	PLATE_COLOR   PlateColor;                           // ������ɫ
	unsigned char *pucBigImage;                         // ץ�Ĵ�ͼ����
	unsigned int  uiBigImageLen;                        // ץ�Ĵ�ͼ���ݳ���
	unsigned short usBigImageWidth;                     // ץ�Ĵ�ͼ���
	unsigned short usBigImageHeight;                    // ץ�Ĵ�ͼ�߶�
	unsigned char *pucCIFImage;                         // ץ��CIFͼ����
	unsigned int  uiCIFImageLen;                        // ץ��CIFͼ���ݳ���
	unsigned short usCIFImageWidth;                     // ץ��CIFͼ���
	unsigned short usCIFImageHeight;                    // ץ��CIFͼ�߶�
	unsigned char *pucPlateImage;                       // ץ�ĳ���ͼ����
	unsigned int uiPlateImageLen;                       // ץ�ĳ���ͼ���ݳ���
	unsigned short usPlateImageWidth;                   // ץ�ĳ���ͼ���
	unsigned short usPlateImageHeight;                  // ץ�ĳ���ͼ�߶�
} VehicleData, *PVehicleData;

typedef struct tagJPGData
{
	void *pDeviceHandle;                    // �豸���
	unsigned char ucDeviceIP[IP_MAX_LEN];   // �豸IP
	unsigned char *pucImage;                // һ֡ʵʱJPG������
	unsigned int uiImageLen;                // һ֡ʵʱJPG�����ݳ���
	unsigned short usImageWidth;            // һ֡ʵʱJPG�����
	unsigned short usImageHeight;           // һ֡ʵʱJPG���߶�
	unsigned short usLeft;                  // �������ҡ��ϡ��µ�����꣬��ȷ������ͼ�ڴ�ͼ�е�λ��
	unsigned short usRight;
	unsigned short usTop;
	unsigned short usBottom;
} JPGData, *PJPGData;

// �豸�汾��Ϣ
typedef struct tagVersionInfo
{
	unsigned char ucMainVer[VERSION_LEN];   // ���汾
	unsigned char ucDSPVer[VERSION_LEN];    // �ΰ汾
	unsigned char ucMCUVer[VERSION_LEN];    // MCU�汾
	unsigned char ucOCRVer[VERSION_LEN];    // ʶ���㷨�汾
	unsigned char ucEPROMVer[VERSION_LEN];  // EEPROM�汾��
} VersionInfo, *PVersionInfo;


// �����豸IP��ָ��
typedef struct tagDevInfo
{
    unsigned char ucIP[IP_MAX_LEN];
    void *pHandle;
} DevInfo, *PDevInfo;



// ����ص���������
typedef void (CALLBACK *DeviceInfoCallback)(void *pUserData, DeviceInfo *pDeviceInfo);
typedef void (CALLBACK *DeviceStatusCallback)(void *pUserData, DeviceStatus *pStatus);
typedef void (CALLBACK *VehicleDataCallback)(void *pUserData, VehicleData *pData);
typedef void (CALLBACK *JPGStreamCallBack)(void *pUserData, JPGData *pJPGData);


// ���庯������
typedef unsigned int (__stdcall *LPR_Init)(void *hWnd, void *pUserData, DeviceInfoCallback fucDeviceInfo, DeviceStatusCallback fucStatus, VehicleDataCallback fucVehicleData, JPGStreamCallBack fucJPGStream);
typedef unsigned int (__stdcall *LPR_Quit)();
typedef unsigned int (__stdcall *LPR_ScanDevice)();
typedef unsigned int (__stdcall *LPR_ConnectCamera)(char *pchDeviceIP, void *pHandle);
typedef unsigned int (__stdcall *LPR_DisconnectCamera)(void *pHandle);
typedef unsigned int (__stdcall *LPR_Capture)(void *pHandle);
typedef unsigned int (__stdcall *LPR_CaptureEx)(void *pHandle, unsigned int nTimeout);
typedef unsigned int (__stdcall *LPR_CheckStatus)(void *pHandle, DEVICE_STATUS *pConnStatus);
typedef unsigned int (__stdcall *LPR_AdjustTime)(void *pHandle, __int64 dwTimeMs);
typedef unsigned int (__stdcall *LPR_GetAllVersion)(void *pHandle, VersionInfo *pVerInfo);
typedef unsigned int (__stdcall *LPR_IsWriteLog)(bool bWriteLog);
typedef unsigned int (__stdcall *LPR_NTPEnable)(void *pHandle,bool bNTP, char *pchNTPSeverIP);
typedef unsigned int (__stdcall *LPR_SetNetParams)(void *pHandle, NetParams *OldParams, NetParams *NewParams);



class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox4;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox6;
    TButton *btnInit;
    TButton *btnQuit;
    TButton *btnScanDev;
    TButton *btnConn;
    TButton *btnDisConn;
    TButton *btnTrigger;
    TButton *btnBlockTrigger;
    TButton *btnStatus;
    TButton *btnNativeJustTime;
    TEdit *edtStatus;
    TCheckBox *chkWriteLog;
    TCheckBox *chkNTPJustTime;
    TButton *btnGetVersionInfo;
    TEdit *edtVersionInfo;
    TEdit *edtMask;
    TLabel *lbl1;
    TLabel *lbl2;
    TLabel *lbl3;
    TEdit *edtDevIP;
    TEdit *edtGate;
    TButton *btnModify;
    TImage *imgBigImg;
    TImage *imgCIFImg;
    TImage *imgPlateImg;
    TPanel *pnlPlateNo;
    TListView *lvDevList;
    TTreeView *tvConnectDev;
    TEdit *edtNTPIP;
    TLabel *Label1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnInitClick(TObject *Sender);
    void __fastcall btnQuitClick(TObject *Sender);
    void __fastcall btnScanDevClick(TObject *Sender);
    void __fastcall btnConnClick(TObject *Sender);
    void __fastcall btnDisConnClick(TObject *Sender);
    void __fastcall btnTriggerClick(TObject *Sender);
    void __fastcall btnBlockTriggerClick(TObject *Sender);
    void __fastcall btnStatusClick(TObject *Sender);
    void __fastcall btnNativeJustTimeClick(TObject *Sender);
    void __fastcall btnGetVersionInfoClick(TObject *Sender);
    void __fastcall chkWriteLogClick(TObject *Sender);
    void __fastcall chkNTPJustTimeClick(TObject *Sender);
    void __fastcall btnModifyClick(TObject *Sender);
    void __fastcall tvConnectDevClick(TObject *Sender);

private:	// User declarations
    LPR_Init Init;
    LPR_Quit Quit;
    LPR_ScanDevice ScanDevice;
    LPR_ConnectCamera ConnectCamera;
    LPR_DisconnectCamera DisconnectCamera;
    LPR_Capture Capture;
    LPR_CaptureEx CaptureEx;
    LPR_CheckStatus CheckStatus;
    LPR_AdjustTime AdjustTime;
    LPR_GetAllVersion GetAllVersion;
    LPR_IsWriteLog IsWriteLog;
    LPR_NTPEnable NTPEnable;
    LPR_SetNetParams SetNetParams;


    void *hHandle;
    TList *pDevList;

public:
    String strImagePath;
    // ��ͼ
    unsigned char byteBigImage[102400];
    // CIFͼ
    unsigned char byteCifImage[102400];
    // ����ͼ
    unsigned char bytePlateImage[5120];
    // ����
    char cPlate[64];


    bool CreateDirectoryRecurrent(String path);
    void ShowPlate(String strPlate, int nColor);






public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
