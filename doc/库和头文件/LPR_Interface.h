//LPR_Interface.h头文件
//接口函数和回调函数的声明
#pragma once

#ifdef LPR_API

#else

#define LPR_API extern "C" __declspec (dllimport)

#endif

#include "LPR_CommonDefine.h"

/*******************************************************************
函数说明:设备信息回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pDeviceInfo 见DeviceInfo结构体定义
**********************************************************************/
typedef void(CALLBACK * DeviceInfoCallback)(void *pUserData, DeviceInfo *pDeviceInfo);



/*******************************************************************
函数说明:设备信息回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pStatus 见DeviceStatus结构体定义
**********************************************************************/
typedef void(CALLBACK * DeviceStatusCallback)(void *pUserData, DeviceStatus *pStatus);



/*******************************************************************
函数说明:抓拍数据回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pData 见VehicleData结构体定义
**********************************************************************/
typedef void(CALLBACK * VehicleDataCallback)(void *pUserData, VehicleData *pData);



/*******************************************************************
函数说明:实时JPG流回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pJPGData见JPGData结构体定义
**********************************************************************/
typedef void(CALLBACK * JPGStreamCallBack)(void *pUserData, JPGData *pJPGData);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_IsWriteLog(bool bWriteLog);
函数名称: LPR_IsWriteLog
		  函数说明：是否记录动态库日志。日志文件自动生成在调用程序所在目录下，自动建立LPRLog文件夹，然后日志名称以时间命名，如：“20110101.log”
		  参数说明：
		  bWriteLog true记录日志，false不记录日志
		  返回值：
		  RESULT_OK表示成功，否则返回错误代码
**********************************************************************/
LPR_API unsigned int __stdcall LPR_IsWriteLog(bool bWriteLog);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_GetErrorMsg(FEEKBACK_TYPE  FeekCode,char *pchErrMsg);
函数名称: LPR_GetErrorMsg
函数说明：获取反馈值对应的文字描述 
参数说明：
FeekCode反馈码，即接口函数返回值
pchErrMsg 反馈代码对应的文字描述，分配空间大小为FEEKMSG_MAX_LEN
返回值：
RESULT_OK表示成功，否则返回错误代码

**********************************************************************/
LPR_API unsigned int __stdcall LPR_GetErrorMsg(FEEKBACK_TYPE  FeekCode,char *pchErrMsg);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_Init(HWND hWnd,DeviceInfoCallback fucDeviceInfo,DeviceStatusCallback fucStatus,VehicleDataCallback fucVehicleData,JPGStreamCallBack fucJPGStream)  
函数名称: LPR_Init
函数说明：设置回调函数
参数说明：
hWnd   如此值为NULL，则回调函数在动态库所建立线程中响应；反之，在该句柄所在线程响应
pUserData 用户数据，在回调函数响应时传出
fucDeviceInfo 设备信息回调函数，见DeviceInfoCallback函数定义
fucStatus 设备状态回调函数，见DeviceStatusCallback定义
fucVehicleData 抓拍数据回调函数，见VehicleDataCallback函数定义
fucJPGStream  实时JPG流回调函数，见JPGStreamCallBack函数定义
返回值：
RESULT_OK表示成功，否则返回错误代码

**********************************************************************/
LPR_API unsigned int __stdcall LPR_Init(HWND hWnd,void *pUserData,DeviceInfoCallback fucDeviceInfo,DeviceStatusCallback fucStatus,VehicleDataCallback fucVehicleData,JPGStreamCallBack fucJPGStream);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_Quit ()  
函数名称: LPR_Quit
	  函数说明：释放动态库所有资源
	  参数说明：

	  返回值：
	  RESULT_OK表示成功，否则返回错误代码
**********************************************************************/
LPR_API unsigned __stdcall WINAPI LPR_Quit ();



/*******************************************************************
函数实体：unsigned int WINAPI LPR_ScanDevice();
函数名称：HWTC_ ScanDevice
函数说明：通过UDP命令，查找同一网段IP对应的设备
返回值：
RESULT_OK表示成功，否则返回错误代码
备注：执行该函数后，如有扫描到设备，会立即响应设备信息回调函数


**********************************************************************/
LPR_API unsigned int __stdcall LPR_ScanDevice();



/*******************************************************************
函数实体：unsigned int WINAPI LPR_SetNetParams(PDEVICEHANDLE pHandle,NetParams *pOldParams,NetParams *pNewParams);
函数名称: LPR _ConnectCamera
		  函数说明：网络参数设置
		  参数说明：pHandle，如果是UDP方式设置，则该参数是0；反之TCP时，指通过LPR _ConnectCamera获取
		  pOldParams 设备原始网络参数，UDP设置时，需要
		  pNewParams 设备新设置的参数
		  返回值：
		  返回值是RESULT_OK表示成功，否则返回错误代码
**********************************************************************/
LPR_API unsigned int __stdcall LPR_SetNetParams(PDEVICEHANDLE pHandle,NetParams *pOldParams,NetParams *pNewParams);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_ControlContent(OutputContent *pContent);
函数名称: LPR_ControlContent
		  函数说明：控制传输内容
		  参数说明：
			pContent 见OutputContent结构体定义
		  返回值：
		  返回值是RESULT_OK表示成功，否则返回错误代码
**********************************************************************/
LPR_API unsigned int __stdcall LPR_ControlContent(OutputContent *pContent);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_ConnectCamera(char *pchDeviceIP, PDEVICEHANDLE *pHandle);
函数名称: LPR _ConnectCamera
函数说明：打开指定IP设备的连接
参数说明：pchDeviceIP待连接的设备IP地址
			pHandle执行成功后，返回设备句柄；否则为INVALID_HANLE
返回值：
				返回值是RESULT_OK表示成功，否则返回错误代码

**********************************************************************/
LPR_API unsigned int __stdcall LPR_ConnectCamera(char *pchDeviceIP, PDEVICEHANDLE *pHandle);



/*******************************************************************
函数实体：unsigned int WINAPI LPR _DisconnectCamera(PDEVICEHANDLE pHandle);
函数名称: LPR _DisconnectCamera
函数说明：断开指定设备的连接
参数说明：
pHandle 设备句柄，通过LPR _ConnectCamera获取
返回值：
返回值是RESULT_OK表示成功，否则返回错误代码


**********************************************************************/
LPR_API unsigned int __stdcall LPR_DisconnectCamera(PDEVICEHANDLE pHandle);



/*******************************************************************
函数实体：unsigned int WINAPI LPR _Capture(PDEVICEHANDLE pHandle)
函数名称：LPR _ Capture
函数说明：强制抓拍，向设备发送抓拍命令，设备抓拍图像和采集信息，并上传。该函数只保证参数下发成功后立即返回，不考虑设备是否执行该命令
参数说明:
pHandle相机句柄，由LPR _ConnectCamera获取
返回值：
返回值是RESULT_OK表示成功，否则返回错误代码
**********************************************************************/
LPR_API unsigned int __stdcall LPR_Capture(PDEVICEHANDLE pHandle);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_CaptureEx(PDEVICEHANDLE pHandle,unsigned int nTimeout)
函数名称：LPR _ CaptureEx
函数说明：强制抓拍，向设备发送抓拍命令，设备抓拍图像和采集信息，并上传。该函数下发命令后，等待设备响应，直到收到设备传出的信息或者超时时间到，才返回。
参数说明:
pHandle相机句柄，由LPR _ConnectCamera获取
nTimeout 阻塞超时时间，以ms为单位
返回值：
返回值是RESULT_OK表示成功，否则返回错误代码

**********************************************************************/
LPR_API unsigned int __stdcall LPR_CaptureEx(PDEVICEHANDLE pHandle,unsigned int nTimeout);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_CheckStatus(PDEVICEHANDLE pHandle , DEVICE_STATUS *pConnStatus)
		函数名称：LPR _CheckStatus
		函数说明：检测状态
		参数说明:
pHandle相机句柄，由LPR _ConnectCamera获取
				pConnStatus：状态标记，见DEVICE _STATUS枚举
		返回值：
		返回值是RESULT_OK表示成功，否则返回错误代码


**********************************************************************/
LPR_API unsigned int __stdcall LPR_CheckStatus(PDEVICEHANDLE pHandle , DEVICE_STATUS *pConnStatus);



/*******************************************************************
函数实体：unsigned int WINAPI LPR _AdjustTime(PDEVICEHANDLE pHandle, unsigned __int64 dwTimeMs = 0)
		函数名称：LPR _AdjustTime
函数说明：给设备校时
		参数说明:
pHandle相机句柄，由LPR _ConnectCamera获取
时间值，(1900-1-1 0:0:0以来的秒数)，64位整数；默认为0，当为0时，直接获取当前系统时间，进行校时
		返回值：
		返回值是RESULT_OK表示成功，否则返回错误代码



**********************************************************************/
LPR_API unsigned int __stdcall LPR_AdjustTime(PDEVICEHANDLE pHandle, unsigned __int64 dwTimeMs);



/*******************************************************************
函数实体：unsigned int WINAPI LPR_NTPEnable (PDEVICEHANDLE pHandle,bool bNTP,char *pchNTPSeverIP)
函数名称：LPR_NTPEnable
函数说明：是否启用NTP校时，如果启用NTP校时，则LPR_AdjustTime函数执行无效
参数说明:
pHandle相机句柄，由LPR _ConnectCamera获取
bNTP  true 表示启用；false表示不启用
pchNTPSeverIP 如启用，则需要设置NTP服务器的IP地址
返回值：
返回值是RESULT_OK表示成功，否则返回错误代码
**********************************************************************/
LPR_API unsigned int __stdcall LPR_NTPEnable (PDEVICEHANDLE pHandle,bool bNTP,char *pchNTPSeverIP);



/*******************************************************************
函数实体：unsigned int WINAPI LPR _GetAllVersion(PDEVICEHANDLE pHandle , VersionInfo *pVerInfo)
		函数名称：LPR _ GetAllVersion
		函数说明：获取设备所有版本信息
		参数说明:
pHandle相机句柄，由LPR _ConnectCamera获取
				pVerInfo：设备详细版本信息，见VersionInfo定义
		返回值：
		返回值是RESULT_OK表示成功，否则返回错误代码

**********************************************************************/
LPR_API unsigned int __stdcall LPR_GetAllVersion(PDEVICEHANDLE pHandle , VersionInfo *pVerInfo);

