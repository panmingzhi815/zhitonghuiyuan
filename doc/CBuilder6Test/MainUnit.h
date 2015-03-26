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

// 结构体定义

// 网络参数
typedef struct tagNetParams
{
	unsigned char ucDeviceIP[IP_MAX_LEN];   // 设备IP
    unsigned char ucMaskIP[IP_MAX_LEN];     // 子网掩码
	unsigned char ucGateIP[IP_MAX_LEN];     // 网关IP
	unsigned char ucMac[MACADDR_LEN];       // MAC地址
} NetParams, *PNetParams;

// 设备信息
typedef struct tagDeviceInfo
{
	NetParams DeviceNetInfo;                        // 设备网络信息参数
	unsigned char ucMAC[MACADDR_LEN];               // MAC地址
	unsigned char ucDeviceVersion[VERSION_LEN];     // 设备版本信息
	unsigned char ucConnectNum;                     // 用户连接数
} DeviceInfo, *PDeviceInfo;

// 状态含义
typedef enum 
{
	CONNECT_SUCCESS = 0,        // 连接成功
	CREATE_ERROR = 1,           // 生成句柄错误
	CONNECT_ERROR = 2,          // 连接错误
	ABNORMALNET_ERROR = 3,      // 网络异常错误
	DEVICE_RESET = 4            // 设备复位

} DEVICE_STATUS;

// 设备状态
typedef struct tagDeviceStatus
{
	void *pHandle;                              // 设备句柄
	unsigned char ucDeviceIP[IP_MAX_LEN];       // 设备IP
	DEVICE_STATUS status;                       // 设备状态
} DeviceStatus,*PDeviceStatus;

// 用户类型
typedef enum
{
	NORMAL_USER  = 0,       // 正常用户
	UNKNOWN_USER = 1        // 未授权用户
} USER_TYPE;

// 触发类型
typedef enum
{
	UNKNOWN_TRIGGER_MODE = 0,   // 未知
	VIDEO_TRIGGER_MODE = 1,     // 视频
	LINE_TRIGGER_MODE = 2,      // 线圈
	SOFT_TRIGGER_MODE           // 模拟
} DEVICE_TRIGGERMODE;

// 车牌颜色
typedef enum 
{
	NON_PLATE = 0,      //未知车牌颜色
	BLUE_COLOR,         //蓝色
	WHITE_COLOR,        //白色
	BLACK_COLOR,        //黑色
	YELLOW_COLOR        //黄色
} PLATE_COLOR;

// 抓拍数据，注意C++Builder枚举类型不一定4个字节，需要在工程->选项->编译->选择Treat enum type as ints，强制将枚举类型视为4字节
typedef struct tagVehicleData
{
	void *pDeviceHandle;                                // 设备句柄
	unsigned short usSerialNO;                          // 序列号
	unsigned char ucDeviceIP[IP_MAX_LEN];               // 设备IP
	unsigned int ui32DeviceID;							// 设备ID
	USER_TYPE ui32UserType;							    // 表示用户类型:0 正常用户，1 未授权用户，其他值保留
	unsigned int ui32Brightness;						// 亮度值
	DEVICE_TRIGGERMODE triggermode;						// 触发类型:1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
	unsigned char ai8UserDefineInfo[VERSION_LEN];	    // 用户自定义信息
	unsigned char ucTime[MAX_TIME_LEN];                 // 时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
	unsigned char ucPlate[MAX_PLATE_LEN];               // 车牌号码
	PLATE_COLOR   PlateColor;                           // 车牌颜色
	unsigned char *pucBigImage;                         // 抓拍大图数据
	unsigned int  uiBigImageLen;                        // 抓拍大图数据长度
	unsigned short usBigImageWidth;                     // 抓拍大图宽度
	unsigned short usBigImageHeight;                    // 抓拍大图高度
	unsigned char *pucCIFImage;                         // 抓拍CIF图数据
	unsigned int  uiCIFImageLen;                        // 抓拍CIF图数据长度
	unsigned short usCIFImageWidth;                     // 抓拍CIF图宽度
	unsigned short usCIFImageHeight;                    // 抓拍CIF图高度
	unsigned char *pucPlateImage;                       // 抓拍车牌图数据
	unsigned int uiPlateImageLen;                       // 抓拍车牌图数据长度
	unsigned short usPlateImageWidth;                   // 抓拍车牌图宽度
	unsigned short usPlateImageHeight;                  // 抓拍车牌图高度
} VehicleData, *PVehicleData;

typedef struct tagJPGData
{
	void *pDeviceHandle;                    // 设备句柄
	unsigned char ucDeviceIP[IP_MAX_LEN];   // 设备IP
	unsigned char *pucImage;                // 一帧实时JPG流数据
	unsigned int uiImageLen;                // 一帧实时JPG流数据长度
	unsigned short usImageWidth;            // 一帧实时JPG流宽度
	unsigned short usImageHeight;           // 一帧实时JPG流高度
	unsigned short usLeft;                  // 车牌左、右、上、下点的坐标，可确定车牌图在大图中的位置
	unsigned short usRight;
	unsigned short usTop;
	unsigned short usBottom;
} JPGData, *PJPGData;

// 设备版本信息
typedef struct tagVersionInfo
{
	unsigned char ucMainVer[VERSION_LEN];   // 主版本
	unsigned char ucDSPVer[VERSION_LEN];    // 次版本
	unsigned char ucMCUVer[VERSION_LEN];    // MCU版本
	unsigned char ucOCRVer[VERSION_LEN];    // 识别算法版本
	unsigned char ucEPROMVer[VERSION_LEN];  // EEPROM版本号
} VersionInfo, *PVersionInfo;


// 关联设备IP和指针
typedef struct tagDevInfo
{
    unsigned char ucIP[IP_MAX_LEN];
    void *pHandle;
} DevInfo, *PDevInfo;



// 定义回调函数类型
typedef void (CALLBACK *DeviceInfoCallback)(void *pUserData, DeviceInfo *pDeviceInfo);
typedef void (CALLBACK *DeviceStatusCallback)(void *pUserData, DeviceStatus *pStatus);
typedef void (CALLBACK *VehicleDataCallback)(void *pUserData, VehicleData *pData);
typedef void (CALLBACK *JPGStreamCallBack)(void *pUserData, JPGData *pJPGData);


// 定义函数类型
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
    // 大图
    unsigned char byteBigImage[102400];
    // CIF图
    unsigned char byteCifImage[102400];
    // 车牌图
    unsigned char bytePlateImage[5120];
    // 车牌
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
