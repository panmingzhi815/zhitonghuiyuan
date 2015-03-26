//LPR_Interface.hͷ�ļ�
//�ӿں����ͻص�����������
#pragma once

#ifdef LPR_API

#else

#define LPR_API extern "C" __declspec (dllimport)

#endif

#include "LPR_CommonDefine.h"

/*******************************************************************
����˵��:�豸��Ϣ�ص�����
����˵����
pUserData �û����ûص�����������û�����
pDeviceInfo ��DeviceInfo�ṹ�嶨��
**********************************************************************/
typedef void(CALLBACK * DeviceInfoCallback)(void *pUserData, DeviceInfo *pDeviceInfo);



/*******************************************************************
����˵��:�豸��Ϣ�ص�����
����˵����
pUserData �û����ûص�����������û�����
pStatus ��DeviceStatus�ṹ�嶨��
**********************************************************************/
typedef void(CALLBACK * DeviceStatusCallback)(void *pUserData, DeviceStatus *pStatus);



/*******************************************************************
����˵��:ץ�����ݻص�����
����˵����
pUserData �û����ûص�����������û�����
pData ��VehicleData�ṹ�嶨��
**********************************************************************/
typedef void(CALLBACK * VehicleDataCallback)(void *pUserData, VehicleData *pData);



/*******************************************************************
����˵��:ʵʱJPG���ص�����
����˵����
pUserData �û����ûص�����������û�����
pJPGData��JPGData�ṹ�嶨��
**********************************************************************/
typedef void(CALLBACK * JPGStreamCallBack)(void *pUserData, JPGData *pJPGData);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_IsWriteLog(bool bWriteLog);
��������: LPR_IsWriteLog
		  ����˵�����Ƿ��¼��̬����־����־�ļ��Զ������ڵ��ó�������Ŀ¼�£��Զ�����LPRLog�ļ��У�Ȼ����־������ʱ���������磺��20110101.log��
		  ����˵����
		  bWriteLog true��¼��־��false����¼��־
		  ����ֵ��
		  RESULT_OK��ʾ�ɹ������򷵻ش������
**********************************************************************/
LPR_API unsigned int __stdcall LPR_IsWriteLog(bool bWriteLog);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_GetErrorMsg(FEEKBACK_TYPE  FeekCode,char *pchErrMsg);
��������: LPR_GetErrorMsg
����˵������ȡ����ֵ��Ӧ���������� 
����˵����
FeekCode�����룬���ӿں�������ֵ
pchErrMsg ���������Ӧ����������������ռ��СΪFEEKMSG_MAX_LEN
����ֵ��
RESULT_OK��ʾ�ɹ������򷵻ش������

**********************************************************************/
LPR_API unsigned int __stdcall LPR_GetErrorMsg(FEEKBACK_TYPE  FeekCode,char *pchErrMsg);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_Init(HWND hWnd,DeviceInfoCallback fucDeviceInfo,DeviceStatusCallback fucStatus,VehicleDataCallback fucVehicleData,JPGStreamCallBack fucJPGStream)  
��������: LPR_Init
����˵�������ûص�����
����˵����
hWnd   ���ֵΪNULL����ص������ڶ�̬���������߳�����Ӧ����֮���ڸþ�������߳���Ӧ
pUserData �û����ݣ��ڻص�������Ӧʱ����
fucDeviceInfo �豸��Ϣ�ص���������DeviceInfoCallback��������
fucStatus �豸״̬�ص���������DeviceStatusCallback����
fucVehicleData ץ�����ݻص���������VehicleDataCallback��������
fucJPGStream  ʵʱJPG���ص���������JPGStreamCallBack��������
����ֵ��
RESULT_OK��ʾ�ɹ������򷵻ش������

**********************************************************************/
LPR_API unsigned int __stdcall LPR_Init(HWND hWnd,void *pUserData,DeviceInfoCallback fucDeviceInfo,DeviceStatusCallback fucStatus,VehicleDataCallback fucVehicleData,JPGStreamCallBack fucJPGStream);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_Quit ()  
��������: LPR_Quit
	  ����˵�����ͷŶ�̬��������Դ
	  ����˵����

	  ����ֵ��
	  RESULT_OK��ʾ�ɹ������򷵻ش������
**********************************************************************/
LPR_API unsigned __stdcall WINAPI LPR_Quit ();



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_ScanDevice();
�������ƣ�HWTC_ ScanDevice
����˵����ͨ��UDP�������ͬһ����IP��Ӧ���豸
����ֵ��
RESULT_OK��ʾ�ɹ������򷵻ش������
��ע��ִ�иú���������ɨ�赽�豸����������Ӧ�豸��Ϣ�ص�����


**********************************************************************/
LPR_API unsigned int __stdcall LPR_ScanDevice();



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_SetNetParams(PDEVICEHANDLE pHandle,NetParams *pOldParams,NetParams *pNewParams);
��������: LPR _ConnectCamera
		  ����˵���������������
		  ����˵����pHandle�������UDP��ʽ���ã���ò�����0����֮TCPʱ��ָͨ��LPR _ConnectCamera��ȡ
		  pOldParams �豸ԭʼ���������UDP����ʱ����Ҫ
		  pNewParams �豸�����õĲ���
		  ����ֵ��
		  ����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������
**********************************************************************/
LPR_API unsigned int __stdcall LPR_SetNetParams(PDEVICEHANDLE pHandle,NetParams *pOldParams,NetParams *pNewParams);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_ControlContent(OutputContent *pContent);
��������: LPR_ControlContent
		  ����˵�������ƴ�������
		  ����˵����
			pContent ��OutputContent�ṹ�嶨��
		  ����ֵ��
		  ����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������
**********************************************************************/
LPR_API unsigned int __stdcall LPR_ControlContent(OutputContent *pContent);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_ConnectCamera(char *pchDeviceIP, PDEVICEHANDLE *pHandle);
��������: LPR _ConnectCamera
����˵������ָ��IP�豸������
����˵����pchDeviceIP�����ӵ��豸IP��ַ
			pHandleִ�гɹ��󣬷����豸���������ΪINVALID_HANLE
����ֵ��
				����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������

**********************************************************************/
LPR_API unsigned int __stdcall LPR_ConnectCamera(char *pchDeviceIP, PDEVICEHANDLE *pHandle);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR _DisconnectCamera(PDEVICEHANDLE pHandle);
��������: LPR _DisconnectCamera
����˵�����Ͽ�ָ���豸������
����˵����
pHandle �豸�����ͨ��LPR _ConnectCamera��ȡ
����ֵ��
����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������


**********************************************************************/
LPR_API unsigned int __stdcall LPR_DisconnectCamera(PDEVICEHANDLE pHandle);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR _Capture(PDEVICEHANDLE pHandle)
�������ƣ�LPR _ Capture
����˵����ǿ��ץ�ģ����豸����ץ������豸ץ��ͼ��Ͳɼ���Ϣ�����ϴ����ú���ֻ��֤�����·��ɹ����������أ��������豸�Ƿ�ִ�и�����
����˵��:
pHandle����������LPR _ConnectCamera��ȡ
����ֵ��
����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������
**********************************************************************/
LPR_API unsigned int __stdcall LPR_Capture(PDEVICEHANDLE pHandle);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_CaptureEx(PDEVICEHANDLE pHandle,unsigned int nTimeout)
�������ƣ�LPR _ CaptureEx
����˵����ǿ��ץ�ģ����豸����ץ������豸ץ��ͼ��Ͳɼ���Ϣ�����ϴ����ú����·�����󣬵ȴ��豸��Ӧ��ֱ���յ��豸��������Ϣ���߳�ʱʱ�䵽���ŷ��ء�
����˵��:
pHandle����������LPR _ConnectCamera��ȡ
nTimeout ������ʱʱ�䣬��msΪ��λ
����ֵ��
����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������

**********************************************************************/
LPR_API unsigned int __stdcall LPR_CaptureEx(PDEVICEHANDLE pHandle,unsigned int nTimeout);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_CheckStatus(PDEVICEHANDLE pHandle , DEVICE_STATUS *pConnStatus)
		�������ƣ�LPR _CheckStatus
		����˵�������״̬
		����˵��:
pHandle����������LPR _ConnectCamera��ȡ
				pConnStatus��״̬��ǣ���DEVICE _STATUSö��
		����ֵ��
		����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������


**********************************************************************/
LPR_API unsigned int __stdcall LPR_CheckStatus(PDEVICEHANDLE pHandle , DEVICE_STATUS *pConnStatus);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR _AdjustTime(PDEVICEHANDLE pHandle, unsigned __int64 dwTimeMs = 0)
		�������ƣ�LPR _AdjustTime
����˵�������豸Уʱ
		����˵��:
pHandle����������LPR _ConnectCamera��ȡ
ʱ��ֵ��(1900-1-1 0:0:0����������)��64λ������Ĭ��Ϊ0����Ϊ0ʱ��ֱ�ӻ�ȡ��ǰϵͳʱ�䣬����Уʱ
		����ֵ��
		����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������



**********************************************************************/
LPR_API unsigned int __stdcall LPR_AdjustTime(PDEVICEHANDLE pHandle, unsigned __int64 dwTimeMs);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR_NTPEnable (PDEVICEHANDLE pHandle,bool bNTP,char *pchNTPSeverIP)
�������ƣ�LPR_NTPEnable
����˵�����Ƿ�����NTPУʱ���������NTPУʱ����LPR_AdjustTime����ִ����Ч
����˵��:
pHandle����������LPR _ConnectCamera��ȡ
bNTP  true ��ʾ���ã�false��ʾ������
pchNTPSeverIP �����ã�����Ҫ����NTP��������IP��ַ
����ֵ��
����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������
**********************************************************************/
LPR_API unsigned int __stdcall LPR_NTPEnable (PDEVICEHANDLE pHandle,bool bNTP,char *pchNTPSeverIP);



/*******************************************************************
����ʵ�壺unsigned int WINAPI LPR _GetAllVersion(PDEVICEHANDLE pHandle , VersionInfo *pVerInfo)
		�������ƣ�LPR _ GetAllVersion
		����˵������ȡ�豸���а汾��Ϣ
		����˵��:
pHandle����������LPR _ConnectCamera��ȡ
				pVerInfo���豸��ϸ�汾��Ϣ����VersionInfo����
		����ֵ��
		����ֵ��RESULT_OK��ʾ�ɹ������򷵻ش������

**********************************************************************/
LPR_API unsigned int __stdcall LPR_GetAllVersion(PDEVICEHANDLE pHandle , VersionInfo *pVerInfo);

