//LPR_CommonDefine.h头文件
//声明对外接口中用到的宏、枚举、结构体等类型的定义
#pragma once

#define INVALID_HANLE	0	//无效句柄
#define IP_MAX_LEN	16	//IP地址字符串最大长度
#define MACADDR_LEN	6	//MAC地址
#define VERSION_LEN	255	//版本长度
#define MAX_PLATE_LEN	16	//车牌号码长度
#define MAX_TIME_LEN	8	//时间长度
#define AUTHORINFO_LEN	100	//授权相关信息长度
#define SERIALNO_LEN	20	//序列号长度
#define FEEKMSG_MAX_LEN	100	//反馈描述信息长度
#define CMD_LEN 512 //命令长度

#define CMD_READ 0//读指令
#define CMD_WRITE 1//写指令

#define ENABLE_FUNCTION 1//某项功能使能
#define DISABLE_FUNCTION 0//某项功能不使能



typedef void * PDEVICEHANDLE;

//函数返回值
typedef enum
{
	RESULT_OK = 0,//执行成功
	INIT_SUCCESS = 1,//已经初始化
	NO_INIT = 2,   //未初始化
	PARAMS_ERROR = 3,//参数不正确
	SOCKET_NULL = 4,//SOCKET句柄为NULL
	THREAD_FAIL = 5,//线程失败
	CREATE_FAIL = 6, //生成命令失败
	SEND_FAIL = 7,//发送命令失败
	NO_FIND_DEVICE = 8,//没有发现设备
	DEVICE_OPENED = 9,//设备已经打开
	DEVICE_DISCONNECT = 10,//和设备的连接断开
	CONTORL_NOCONNECTION = 11,//控制端口未连接
	NO_RECEIVED_DATA = 12,//阻塞触发没有收到数据
	OTHER_ERROR = 100,//其他错误
	TIME_OUT = 209//函数执行超时
}FEEKBACK_TYPE;

//设备状态
typedef enum 
{
	CONNECT_SUCCESS = 0,//连接成功
	CREATE_ERROR = 1,//生成句柄错误
	CONNECT_ERROR = 2,//连接错误
	ABNORMALNET_ERROR = 3,//网络异常错误
	DEVICE_RESET = 4//设备复位

} DEVICE_STATUS;

//车牌颜色
typedef enum 
{
	NON_PLATE = 0,//未知车牌颜色
	BLUE_COLOR,//蓝色
	WHITE_COLOR,//白色
	BLACK_COLOR,//黑色
	YELLOW_COLOR//黄色
} PLATE_COLOR;
//触发类型
typedef enum
{
	UNKNOWN_TRIGGER_MODE = 0,//未知
	VIDEO_TRIGGER_MODE = 1,//视频
	LINE_TRIGGER_MODE = 2,//线圈
	SOFT_TRIGGER_MODE//模拟
}DEVICE_TRIGGERMODE;
typedef enum
{
	NORMAL_USER  = 0,// 正常用户
	UNKNOWN_USER = 1//未授权用户

}USER_TYPE;

//快门值
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
//主指令类型
typedef enum
{
	SYSTEM_CMD = 0x00,//系统指令
	LIGHT_CMD = 0x20,//调光指令
	OSD_CMD = 0x30,//叠加指令
	EPLD_CMD = 0x60,//单片机指令
	LED_CMD = 0x70,//补光指令
	CAMERA_CMD = 0x71,//相机控制指令
	MOVE_CMD = 0x80,//动作指令
	CAPTURE_DATA = 0xFF//抓拍数据
}MAIN_CMD;
//系统指令子类
typedef enum
{	
	HEART_CMD = 0x00,//心跳
	VERSION_INFO = 0x04,//版本信息
	IMAGE_QUALITY = 0x05,//图像压缩比
	DEVICE_RESTART = 0x0C,//是否重启
	RESTART_TIME = 0x0D,//重启时间
	OCR_PARAMS = 0x16,//识别参数
	SERIRAL_NO = 0x18,//设备序列号
	ALG_PARAMS = 0x1A,//算法参数
	DEVICE_ID = 0x1B,//设备编号
	DEVICE_CODE = 0x1C,//机器码
	AUTHOR_INFO = 0x1D,//授权码
	AUTHOR_VALIDTIME = 0x23,//授权截止时间
	WORK_MODE = 0x1E,//工作模式，0正常，1曝光测试模式
	VERIFYTIME_MODE = 0x1F,//校时方式0 SDK 1 NTP
	NTP_SERVERIP = 0x20,//NTP服务IP
	NTP_TIMEOUT = 0x21
}SYSTEM_SUBCMD;
//版本对象
typedef enum
{
	MAIN_VERSION = 0x00,//主版本
	DSP_SUBVERSION  = 0x01, //次版本
	MCU_VERSION  = 0x02, //MCU版本
	ALG_VERSION = 0x03,//识别算法版本
	JPG_VERSION = 0x04,//JPG版本信息
	EEPROM_VERSION = 0x05//EEPROM版本号
}VERSION_OBJECT;

//图像压缩比
typedef enum
{
	BIG_IMAGE_QUALITY = 0x00,//大图
	CIF_IMAGE_QUALITY  = 0x01, //CIF图
	PLATE_IMAGE_QUALITY  = 0x02//车牌图
}IMAGE_QUALITY_OBJECT;

//调光指令子类
typedef enum
{	
	LIGHT_MODE = 0x00,//调光模式
	AUTOLIGHT_ENABLE = 0x01,//自动调光使能
	SYSTEM_TIME= 0x02,//系统时间
	LIGHT_PARAMS = 0x03,//调光参数表，分四套
	IMAGE_BRIGHTNESS = 0x07,//图片亮度
	CAMERA_CURSTATUS = 0x0A,//相机当前状态
	CAMERA_PARAMS = 0x0B,//摄像头参数
	CUR_LIGHTBASE = 0x0D,//当前调光基准
	LIGHT_VALIDNUM = 0x0E,//调光有效次数
	DAY_EXPOSURE_COMPENSATION = 0x0F,//白天曝光补偿
	NIGHT_EXPOSURE_COMPENSATION = 0x10,//夜间曝光补偿
	REF_GAIN = 0x11,//参考增益
	REF_BRIGHTNESS = 0x12//参考亮度

}LIGHT_SUBCMD;
//调光模式值
typedef enum
{
	AUTO_LIGHT = 0x00,//自动调光
	MIXED_LIGHT = 0x01//混合调光
}LIGHT_MODE_VALUE;

//相机当前状态对象
typedef enum
{
	SHUTTER_VALUE = 0x00,//快门
	APARTURE_VALUE = 0x01,//光圈
	GAIN_VALUE = 0x02,//增益
	VIEW_VALUE = 0x03,//视野
	F_VALUE = 0x04,//焦距
	BRIGHT_NUM = 0x05,//调亮
	DARK_NUM = 0x06,//调暗
}CAMERA_CURSTATUS_PARAMS;

//LED指令子类
typedef enum
{	
	ENABLE_LED = 0x00,//使能
	OPEN_CLOSE_BASE = 0x01,//开关灯基准
	LED_BRIGHTNESS = 0x02,//LED亮度
	LED_STATUS = 0x03,//LED状态
	LED_DELAY = 0x04//LED延迟
}LED_SUBCMD;
//OSD叠加指令子类
typedef enum
{	
	OSD_ENABLE = 0x0C,//使能控制
	OSD_INFO = 0x0D//信息内容
}OSD_SUBCMD;

//相机控制指令
typedef enum
{
	POINT_EXPOSURE = 0x06,//点曝光
	CAMERA_PHASE = 0x07//相机相位

}CAMERA_CONTROL_CMD;



//叠加使能控制对象
typedef enum
{	
	OSD_TIME_ENABLE = 0x00,//时间叠加使能
	OSD_INFO_ENABLE = 0x03,//自定义信息叠加使能
	OSD_PLATE_ENABLE = 0x04//识别结果叠加使能

}OSD_ENABLE_OBJECT;


//EPLD指令子类
typedef enum
{	
	LINE_POLARITY = 0x01,//线圈触发极性
	CAMERA_MENU = 0x0A,//相机菜单
	VIEW_F = 0x0B//视野焦距
}EPLD_SUBCMD;


//视野焦距对象
typedef enum
{
	VIEW_OBJECT = 0x00,//视野
	F_OBJECT = 0x01//焦距
}VIEW_F_OBJECT;

//开关灯基准对象
typedef enum
{
	OPEN_BASE = 0x00,//开灯基准
	CLOSE_BASE = 0x01//关灯基准
}LED_STATUS_OBJECT;


//工作模式测试使用
typedef enum
{
	NORMAL_WORKMODE = 0,//正常工作模式
	VIDEO_EXPOSURE = 1//视频曝光测试模式
}WORKMODE;
//网络参数
typedef struct tagNetParams
{
	unsigned char ucDeviceIP[IP_MAX_LEN];//设备IP
	unsigned char ucMaskIP[IP_MAX_LEN];//子网掩码 
	unsigned char ucGateIP[IP_MAX_LEN];//网关IP
	unsigned char ucMac[MACADDR_LEN];//MAC地址
}NetParams,*PNetParams;

//设备基本信息
typedef struct tagDeviceInfo
{
	NetParams DeviceNetInfo;//设备网络信息参数
	unsigned char ucMAC[MACADDR_LEN];//MAC地址
	unsigned char ucDeviceVersion[VERSION_LEN];//设备版本信息
	unsigned char ucConnectNum;//用户连接数
}DeviceInfo,*PDeviceInfo;

//设备状态
typedef struct tagDeviceStatus
{
	PDEVICEHANDLE pHandle;//设备句柄
	unsigned char ucDeviceIP[IP_MAX_LEN];//设备IP
	DEVICE_STATUS status;//设备状态

}DeviceStatus,*PDeviceStatus;
//输出内容
typedef struct tagOutputContent
{
	bool bOutputBigImage;//是否输出大图
	bool bOutputCIFImage;//是否输出CIF图
	bool bOutputPlateImage;//是否输出车牌图
}OutputContent,*POutputContent;

//抓拍数据
typedef struct tagVehicleData
{
	PDEVICEHANDLE pDeviceHandle;//设备句柄
	unsigned short usSerialNO;//序列号
	unsigned char ucDeviceIP[IP_MAX_LEN];//设备IP
	unsigned int ui32DeviceID;							//设备ID
	USER_TYPE ui32UserType;							//表示用户类型:0 正常用户，1 未授权用户，其他值保留
	unsigned int ui32Brightness;						//亮度值
	DEVICE_TRIGGERMODE triggermode;						//触发类型:1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
	unsigned char ai8UserDefineInfo[VERSION_LEN];	//用户自定义信息
	unsigned char ucTime[MAX_TIME_LEN];//时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
	unsigned char ucPlate[MAX_PLATE_LEN];//车牌号码
	PLATE_COLOR   PlateColor;//车牌颜色
	unsigned char *pucBigImage;//抓拍大图数据
	unsigned int  uiBigImageLen;//抓拍大图数据长度
	unsigned short usBigImageWidth;//抓拍大图宽度
	unsigned short usBigImageHeight;//抓拍大图高度
	unsigned char *pucCIFImage;//抓拍CIF图数据
	unsigned int  uiCIFImageLen;//抓拍CIF图数据长度
	unsigned short usCIFImageWidth;//抓拍CIF图宽度
	unsigned short usCIFImageHeight;//抓拍CIF图高度

	unsigned char *pucPlateImage;//抓拍车牌图数据
	unsigned int  uiPlateImageLen;//抓拍车牌图数据长度
	unsigned short usPlateImageWidth;//抓拍车牌图宽度
	unsigned short usPlateImageHeight;//抓拍车牌图高度
}VehicleData,*PVehicleData;



//实时JPG流
typedef struct tagJPGData
{
	PDEVICEHANDLE pDeviceHandle;//设备句柄
	unsigned char ucDeviceIP[IP_MAX_LEN];//设备IP
	unsigned char *pucImage;//一帧实时JPG流数据
	unsigned int  uiImageLen;// 一帧实时JPG流数据长度
	unsigned short usImageWidth;// 一帧实时JPG流宽度
	unsigned short usImageHeight;// 一帧实时JPG流高度
	unsigned short usLeft;
	unsigned short usRight;
	unsigned short usTop;
	unsigned short usBottom;
}JPGData,*PJPGData;

//设备版本信息
typedef struct tagVersionInfo
{
	unsigned char ucMainVer[VERSION_LEN];//主版本
	unsigned char ucDSPVer[VERSION_LEN];//次版本
	unsigned char ucMCUVer[VERSION_LEN];//MCU版本
	unsigned char ucOCRVer[VERSION_LEN];//识别算法版本
	unsigned char ucEPROMVer[VERSION_LEN];//EEPROM版本号
}VersionInfo,*PVersionInfo;

//参数结构体
typedef struct tagParamsInfo
{
	unsigned char ucMainCmd;//主指令
	unsigned char ucSubCmd;//次指令
	bool          bHasObject;//是否有对象号
	unsigned char ucObject;//对象号
	unsigned char ucCmdType;//命令类型，读或者写
	unsigned short usCmdLen;//命令长度
	unsigned char ucCmd[CMD_LEN];//命令内容
}ParamsInfo,*PParamsInfo;

//算法参数
//主行方向
typedef enum 
{
	LEFT_TOP = 0,//左上行驶
	LEFT_BOTTOM,//左下行驶
	RIGHT_TOP,	//右上行驶
	RIGHT_BOTTOM,//右上行驶
	UNDECIDED	//不确定
}MAINDIRECT;

//触发方式
typedef enum  
{
		LINE_TRIGGER = 0,	// 线圈触发
		VIDEO_TRIGGER = 2   //视频触发
}TRIGGER_MODE;


typedef struct tagAlgParams
{
	TRIGGER_MODE TriggerMode;		// 线圈触发或视频触发
	unsigned short usLeft;			//检测区域左边界
	unsigned short usTop;			//检测区域上边界
	unsigned short usRight;			//检测区域右边界
	unsigned short usBottom;		//检测区域下边界
	MAINDIRECT MainDirect;			// 主行方向：左上，左下，右上，右下
	bool bGetOppEn;					// 是否抓拍逆行
}AlgParams,*PAlgParams;