//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include <jpeg.hpp>
 

// 回调函数

// 设备信息回调函数
void CALLBACK DeviceInfoCallbackFuc(void *pUserData, DeviceInfo *pDeviceInfo)
{
    TForm1 *pThis = (TForm1 *)pUserData;
    
    String strIP, strMask, strGate, strMAC;
    strIP.sprintf("%s", pDeviceInfo->DeviceNetInfo.ucDeviceIP);
    strMask.sprintf("%s", pDeviceInfo->DeviceNetInfo.ucMaskIP);
    strGate.sprintf("%s", pDeviceInfo->DeviceNetInfo.ucGateIP);
    strMAC.sprintf("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", pDeviceInfo->ucMAC[0], pDeviceInfo->ucMAC[1], pDeviceInfo->ucMAC[2], pDeviceInfo->ucMAC[3], pDeviceInfo->ucMAC[4], pDeviceInfo->ucMAC[5]);

    int nCount = pThis->lvDevList->Items->Count;
    for(int i = 0; i < nCount; i++)
    {
        if(pThis->lvDevList->Items->Item[i]->Caption == strIP)
        {
            pThis->lvDevList->Items->Item[i]->SubItems->Add(strMask);
            pThis->lvDevList->Items->Item[i]->SubItems->Add(strGate);
            pThis->lvDevList->Items->Item[i]->SubItems->Add(strMAC);

            return;
        }
    }

    // 添加一列
    TListItem *item = pThis->lvDevList->Items->Add();
    item->Caption = strIP;
    item->SubItems->Add(strMask);
    item->SubItems->Add(strGate);
    item->SubItems->Add(strMAC);
}

// 设备状态回调函数
void CALLBACK DeviceStatusCallbackFuc(void *pUserData, DeviceStatus *pStatus)
{

}

// 抓拍数据
void CALLBACK VehicleDataCallbackFuc(void *pUserData, VehicleData *pData)
{
    TForm1 *pThis = (TForm1 *)pUserData;
    if(pThis->tvConnectDev->Selected == NULL) return;

    String strIP;
    bool bFlag = false;
    PDevInfo pDev = NULL;
    TTreeNodes *nodes = pThis->tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(pThis->tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
                String strViewIP = nodes->Item[i]->Text;

                // 只显示指定抓拍的设备数据
                strIP.sprintf("%s", pData->ucDeviceIP);
                if(strIP == strViewIP)
                {
                    bFlag = true;
                    break;
                }
            }
        }
    }

     if(!bFlag) return;


     int nColor = pData->PlateColor;
     TDateTime dataTime = Now();
     SYSTEMTIME tm;
     GetSystemTime(&tm);

     String strPlate = (char *)pData->ucPlate;

     String strPath;
     String strBigFile, strCifFile, strPlateFile, strPlateNoFile;
     int iFileHandle = 0;

     // 大图
     if(pData->pucBigImage != NULL && pData->uiBigImageLen > 0)
     {
        strPath = pThis->strImagePath + strIP + "\\大图\\" + FormatDateTime("yyyymmdd", dataTime) + "\\";
        pThis->CreateDirectoryRecurrent(strPath);
        strBigFile = Format("%s%s%03d(%s).jpg", ARRAYOFCONST((strPath, dataTime.FormatString("hhmmss"), tm.wMilliseconds, strPlate)));
        iFileHandle = FileCreate(strBigFile);
        if(iFileHandle != 0)
        {
            FileWrite(iFileHandle, pData->pucBigImage, pData->uiBigImageLen);
            FileClose(iFileHandle);

            if(FileExists(strBigFile))
            {
                pThis->imgBigImg->Picture->LoadFromFile(strBigFile);
            }
        }
     }

     // CIF图
     if(pData->pucCIFImage != NULL && pData->uiCIFImageLen > 0)
     {
        strPath = pThis->strImagePath + strIP + "\\CIF图\\" + dataTime.FormatString("yyyymmdd") + "\\";
        pThis->CreateDirectoryRecurrent(strPath);
        strCifFile = Format("%s%s%03d(%s).jpg", ARRAYOFCONST((strPath, dataTime.FormatString("hhmmss"), tm.wMilliseconds, strPlate)));
        iFileHandle = FileCreate(strCifFile);
        if(iFileHandle != 0)
        {
            FileWrite(iFileHandle, pData->pucCIFImage, pData->uiCIFImageLen);
            FileClose(iFileHandle);

            if(FileExists(strCifFile))
            {
                pThis->imgCIFImg->Picture->LoadFromFile(strCifFile);
            }
        }
     }
     // 车牌图
     if(pData->pucPlateImage != NULL && pData->uiPlateImageLen > 0)
     {
        strPath = pThis->strImagePath + strIP + "\\车牌图\\" + dataTime.FormatString("yyyymmdd") + "\\";
        pThis->CreateDirectoryRecurrent(strPath);
        strPlateFile = Format("%s%s%03d(%s).jpg", ARRAYOFCONST((strPath, dataTime.FormatString("hhmmss"), tm.wMilliseconds, strPlate)));
        iFileHandle = FileCreate(strPlateFile);
        if(iFileHandle != 0)
        {
            FileWrite(iFileHandle, pData->pucPlateImage, pData->uiPlateImageLen);
            FileClose(iFileHandle);
        }

        if(FileExists(strPlateFile))
        {
            pThis->imgPlateImg->Picture->LoadFromFile(strPlateFile);
        }
     }

     // 车牌号码
     pThis->ShowPlate(strPlate, nColor);

}

// 视频流数据
void CALLBACK JPGStreamCallBackFuc(void *pUserData, JPGData *pJPGData)
{

}



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


// 创建目录
bool TForm1::CreateDirectoryRecurrent(String path)
{
    bool nRes = false;

    if(!DirectoryExists(path))
      {
          int nLen = strlen(path.c_str());
          char *chPath = new char[nLen + 2];
          for(int i = 1; i <= nLen; i++)
          {
              if(path[i] == '\\')
              {
                  memset(chPath, 0, nLen);
                  strncpy(chPath, path.c_str(), i);
                  if(!DirectoryExists(chPath))
                  {
                      memset(chPath, 0, nLen);
                      strncpy(chPath, path.c_str(), i);
                      nRes = CreateDirectory(chPath, NULL);
                  }
              }
          }
          if(chPath != NULL)
          {
              delete chPath;
              chPath = NULL;
          }
      }

	return nRes;
}

//显示车牌号及其颜色
void TForm1::ShowPlate(String strPlate, int nColor)
{
    pnlPlateNo->Caption = strPlate;
     switch(nColor)
     {
        case 0:
            pnlPlateNo->Color = clBtnFace;
            pnlPlateNo->Font->Color = clBlack;
            break;
        case 1:
            pnlPlateNo->Color = clBlue;
            pnlPlateNo->Font->Color = clWhite;
            break;
        case 2:
            pnlPlateNo->Color = clWhite;
            pnlPlateNo->Font->Color = clBlack;
            break;
        case 3:
            pnlPlateNo->Color = clWhite;
            pnlPlateNo->Font->Color = clWhite;
            break;
        case 4:
            pnlPlateNo->Color = clYellow;
            pnlPlateNo->Font->Color = clBlack;
            break;
        default:
            pnlPlateNo->Color = clBtnFace;
            pnlPlateNo->Font->Color = clBlack;
            break;
     }
}



void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Init = NULL;
    Quit = NULL;
    ScanDevice = NULL;
    ConnectCamera = NULL;
    DisconnectCamera = NULL;
    Capture = NULL;
    CaptureEx = NULL;
    CheckStatus = NULL;
    AdjustTime = NULL;
    GetAllVersion = NULL;
    IsWriteLog = NULL;
    NTPEnable = NULL;
    SetNetParams = NULL;

    hHandle = NULL;
    hHandle = LoadLibrary("LPRSDK.dll");

    if(hHandle != NULL)
    {
        Init = (LPR_Init)GetProcAddress(hHandle, "LPR_Init");
        Quit = (LPR_Quit)GetProcAddress(hHandle, "LPR_Quit");
        ScanDevice = (LPR_ScanDevice)GetProcAddress(hHandle, "LPR_ScanDevice");
        ConnectCamera = (LPR_ConnectCamera)GetProcAddress(hHandle, "LPR_ConnectCamera");
        DisconnectCamera = (LPR_DisconnectCamera)GetProcAddress(hHandle, "LPR_DisconnectCamera");
        Capture = (LPR_Capture)GetProcAddress(hHandle, "LPR_Capture");
        CaptureEx = (LPR_CaptureEx)GetProcAddress(hHandle, "LPR_CaptureEx");
        CheckStatus = (LPR_CheckStatus)GetProcAddress(hHandle, "LPR_CheckStatus");
        AdjustTime = (LPR_AdjustTime)GetProcAddress(hHandle, "LPR_AdjustTime");
        GetAllVersion = (LPR_GetAllVersion)GetProcAddress(hHandle, "LPR_GetAllVersion");
        IsWriteLog = (LPR_IsWriteLog)GetProcAddress(hHandle, "LPR_IsWriteLog");
        NTPEnable = (LPR_NTPEnable)GetProcAddress(hHandle, "LPR_NTPEnable");
        SetNetParams = (LPR_SetNetParams)GetProcAddress(hHandle, "LPR_SetNetParams");

        if(Init == NULL || Quit == NULL || ScanDevice == NULL || ConnectCamera == NULL
        || DisconnectCamera == NULL || Capture == NULL || CaptureEx == NULL || CheckStatus == NULL
        || AdjustTime == NULL || GetAllVersion == NULL || IsWriteLog == NULL || NTPEnable == NULL || SetNetParams == NULL
        )
        {
            ShowMessage("获取库接口指针失败，程序退出");
            Application->Terminate();
        }
    }
    else
    {
        ShowMessage("加载LPRSDK.dll失败，程序退出");
        Application->Terminate();
    }

    // 初始化设备列表
    lvDevList->Clear();
    lvDevList->Columns->Add();
    lvDevList->Columns->Add();
    lvDevList->Columns->Add();
    lvDevList->Columns->Add();
    lvDevList->Columns->Items[0]->Caption = "设备IP";
    lvDevList->Columns->Items[0]->Width = 100;
    lvDevList->Columns->Items[1]->Caption = "子网掩码";
    lvDevList->Columns->Items[1]->Width = 100;
    lvDevList->Columns->Items[2]->Caption = "默认网关";
    lvDevList->Columns->Items[2]->Width = 100;
    lvDevList->Columns->Items[3]->Caption = "MAC地址";
    lvDevList->Columns->Items[3]->Width = 200;
    lvDevList->ViewStyle = vsReport;
    lvDevList->GridLines = true;

    //设置树控件的复选框属性
    SetWindowLong(tvConnectDev->Handle, GWL_STYLE, GetWindowLong(tvConnectDev->Handle, GWL_STYLE) | TVS_CHECKBOXES);

    pDevList = new TList();

    // 获取应用程序路径名
    strImagePath = ExtractFilePath(Application->ExeName);
}
//---------------------------------------------------------------------------


// 释放动态库
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    DevInfo *pDev;
    for(int i = 0; i < pDevList->Count; i++)
    {
        pDev = PDevInfo(pDevList->Items[i]);
        if(pDev != NULL)
        {

            if(pDev->pHandle != NULL)
            {
                int nRes = DisconnectCamera(pDev->pHandle);
                if(pDev != NULL)
                {
                    delete pDev;
                    pDev = NULL;
                }
                pDevList->Delete(i);
                tvConnectDev->Items->Delete(tvConnectDev->Selections[i]);
            }
        }
    }
    if(pDevList != NULL)
    {
        delete pDevList;
        pDevList = NULL;
    }

    if(hHandle != NULL)
    {
        FreeLibrary(hHandle);
        hHandle = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnInitClick(TObject *Sender)
{
    int nValue = 0;
    void *hWnd = NULL;
    nValue = Init(hWnd, this, DeviceInfoCallbackFuc, DeviceStatusCallbackFuc, VehicleDataCallbackFuc, JPGStreamCallBackFuc);
    if(nValue == 0)
    {
         ShowMessage("初始化成功");
    }
    else
    {
         ShowMessage("初始化失败，返回值 = " + IntToStr(nValue));
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnQuitClick(TObject *Sender)
{
    int nRes = 0;
    // 释放设备列表
    DevInfo *pDev;
    for(int i = 0; i < pDevList->Count; i++)
    {
        pDev = PDevInfo(pDevList->Items[i]);
        if(pDev != NULL)
        {

            if(pDev->pHandle != NULL)
            {
                int nRes = DisconnectCamera(pDev->pHandle);
                if(pDev != NULL)
                {
                    delete pDev;
                    pDev = NULL;
                }
                pDevList->Delete(i);
                tvConnectDev->Items->Delete(tvConnectDev->Selections[i]);
            }
        }
    }

    // 释放动态库
    nRes = Quit();
    if(nRes == 0) ShowMessage("退出成功");
    else ShowMessage("退出失败，返回值 = " + IntToStr(nRes));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnScanDevClick(TObject *Sender)
{
    lvDevList->Clear();
    int nRes = 0;

    // 释放动态库
    nRes = ScanDevice();
      if(nRes != 0) ShowMessage("扫描失败，返回值 = " + IntToStr(nRes));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnConnClick(TObject *Sender)
{
    if(lvDevList->SelCount <= 0) return;

    String strIP;
    strIP = lvDevList->Selected->Caption;

    void *pCamHandle = NULL;
    int nRes = 0;
    nRes = ConnectCamera(strIP.c_str(), &pCamHandle);
    if(nRes != 0)
    {
        ShowMessage("连接失败，返回值 = " + IntToStr(nRes));
    }
    else
    {
        PDevInfo pDev = new DevInfo();
        StrCopy(pDev->ucIP, strIP.c_str());
        pDev->pHandle = pCamHandle;
        pDevList->Add(pDev);

        tvConnectDev->Items->Add(NULL, strIP);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDisConnClick(TObject *Sender)
{
    int nItem = 0;
    // 获取当前选中项IP
    nItem = tvConnectDev->SelectionCount;
    String strIP;
    String strDevListIP;
    PDevInfo pDev = NULL;
    for(int i = 0; i < nItem; i++)
    {
        strIP = tvConnectDev->Selections[i]->Text;
        for(int j = 0; j < pDevList->Count; j++)
        {
            pDev = PDevInfo(pDevList->Items[j]);
            if(pDev != NULL)
            {
                strDevListIP.sprintf("%s", pDev->ucIP);
                if(strDevListIP == strIP)
                {   if(pDev->pHandle != NULL)
                    {
                        int nRes = DisconnectCamera(pDev->pHandle);
                        if(nRes != 0) ShowMessage("断开失败，返回值 = " + IntToStr(nRes));
                        else
                        {
                            if(pDev != NULL)
                            {
                                delete pDev;
                                pDev = NULL;
                            }

                            pDevList->Delete(j);
                            tvConnectDev->Items->Delete(tvConnectDev->Selections[i]);
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnTriggerClick(TObject *Sender)
{
      if(tvConnectDev->Selected == NULL) return;
      PDevInfo pDev = NULL;
      TTreeNodes *nodes = tvConnectDev->Items;
      if(nodes != NULL)
      {
          for(int i = 0; i < nodes->Count; i++)
          {
              if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
              {
                String strViewIP = nodes->Item[i]->Text;

                  for(int j = 0; j < pDevList->Count; j++)
                  {
                      pDev = PDevInfo(pDevList->Items[j]);
                      if(pDev != NULL)
                      {
                          String strDevListIP;
                          strDevListIP.sprintf("%s", pDev->ucIP);
                          if(strDevListIP == strViewIP)
                          {   if(pDev->pHandle != NULL)
                              {
                                  int nRes = Capture(pDev->pHandle);
                                  if(nRes != 0) ShowMessage("模拟触发失败，返回值 = " + IntToStr(nRes));
                                  return;
                              }
                          }
                      }
                  }
              }
          }
      }
}


//---------------------------------------------------------------------------




void __fastcall TForm1::btnBlockTriggerClick(TObject *Sender)
{
    if(tvConnectDev->Selected == NULL) return;

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
              String strViewIP = nodes->Item[i]->Text;

                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                int nRes = CaptureEx(pDev->pHandle, 800);
                                if(nRes != 0) ShowMessage("阻塞模拟触发失败，返回值 = " + IntToStr(nRes));
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnStatusClick(TObject *Sender)
{
    edtStatus->Text = "";
    if(tvConnectDev->Selected == NULL) return;
    DEVICE_STATUS devStatusInfo;
    String strInfo;

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
              String strViewIP = nodes->Item[i]->Text;

                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                int nRes = CheckStatus(pDev->pHandle, &devStatusInfo);
                                if(nRes != 0) ShowMessage(strDevListIP + "检测状态失败，返回值 = " + IntToStr(nRes));
                                else
                                {
                                    if(devStatusInfo == CONNECT_SUCCESS)  strInfo = "连接成功";
                                    else if(devStatusInfo == CREATE_ERROR) strInfo == "生成句柄错误";
                                    else if(devStatusInfo == CONNECT_ERROR) strInfo == "连接错误";
                                    else if(devStatusInfo == ABNORMALNET_ERROR) strInfo == "网络异常错误";
                                    else if(devStatusInfo == DEVICE_RESET) strInfo == "设备复位";

                                    edtStatus->Text = strInfo;
                                }
                                
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnNativeJustTimeClick(TObject *Sender)
{
    if(tvConnectDev->Selected == NULL) return;
    DEVICE_STATUS devStatusInfo;
    String strInfo;

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
              String strViewIP = nodes->Item[i]->Text;

                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                int nRes = AdjustTime(pDev->pHandle, 0);
                                if(nRes != 0) ShowMessage("使用本地系统时间校时失败，返回值 = " + IntToStr(nRes));
                                else ShowMessage("校时成功");

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnGetVersionInfoClick(TObject *Sender)
{
    if(tvConnectDev->Selected == NULL) return;
    DEVICE_STATUS devStatusInfo;
    String strInfo;
    VersionInfo versionInfo;

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
              String strViewIP = nodes->Item[i]->Text;

                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                int nRes = GetAllVersion(pDev->pHandle, &versionInfo);
                                if(nRes != 0) ShowMessage("获取版本信息失败，返回值 = " + IntToStr(nRes));

                                String strInfo;
                                strInfo.sprintf("DSP主版本(%s)DSP子版本(%s)单片机版本(%s)识别库版本(%s)EEPROM版本(%s)", versionInfo.ucMainVer, versionInfo.ucDSPVer, versionInfo.ucMCUVer, versionInfo.ucOCRVer, versionInfo.ucEPROMVer);
                                edtVersionInfo->Text = strInfo;

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chkWriteLogClick(TObject *Sender)
{
    int nRes = 0;
    if(chkWriteLog->Checked)
    {
        nRes = IsWriteLog(true);
        if(nRes != 0) ShowMessage("启用写日志失败，返回值 = " + IntToStr(nRes));
    }
    else
    {
        nRes = IsWriteLog(false);
        if(nRes != 0) ShowMessage("启用写日志失败，返回值 = " + IntToStr(nRes));
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chkNTPJustTimeClick(TObject *Sender)
{
    if(tvConnectDev->Selected == NULL) return;
    DEVICE_STATUS devStatusInfo;
    String strInfo;
    VersionInfo versionInfo;

    if(edtNTPIP->Text.IsEmpty())
    {
        ShowMessage("NTP服务器IP非法");
        return;
    }

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
              String strViewIP = nodes->Item[i]->Text;

                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                if(chkNTPJustTime->Checked)
                                {
                                    int nRes = NTPEnable(pDev->pHandle, true, edtNTPIP->Text.c_str());
                                    if(nRes != 0) ShowMessage("设置启用NTP校时失败，返回值 = " + IntToStr(nRes));
                                    else ShowMessage("设置启用NPT校时成功");
                                }
                                else
                                {
                                    int nRes = NTPEnable(pDev->pHandle, false, edtNTPIP->Text.c_str());
                                    if(nRes != 0) ShowMessage("设置禁用用NTP校时失败，返回值 = " + IntToStr(nRes));
                                    else ShowMessage("设置禁用NPT校时成功");
                                }

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnModifyClick(TObject *Sender)
{
if(tvConnectDev->Selected == NULL) return;
    DEVICE_STATUS devStatusInfo;
    String strInfo;
    VersionInfo versionInfo;
    NetParams oldParams, newParams;

    String strIP, strMask, strGate, strMAC;
    strIP = edtDevIP->Text;
    strMask = edtMask->Text;
    strGate = edtGate->Text;
    //strMAC = edtMAC->Text;

    memset(newParams.ucDeviceIP, 0, 16);
    memcpy(newParams.ucDeviceIP, strIP.c_str(), strIP.Length());

    memset(newParams.ucMaskIP, 0, 16);
    memcpy(newParams.ucMaskIP, strMask.c_str(), strMask.Length());

    memset(newParams.ucGateIP, 0, 16);
    memcpy(newParams.ucGateIP, strGate.c_str(), strGate.Length());

    //strMAC.Delete(3 ,1);
    //strMAC.Delete(5 ,1);
    //strMAC.Delete(7 ,1);
    //strMAC.Delete(9 ,1);
    //strMAC.Delete(11 ,1);
    //memset(newParams.ucMac, 0, 6);
    //HexToBin(strMAC.c_str(), newParams.ucMac, 6);

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
                String strViewIP = nodes->Item[i]->Text;
                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                int nRes = SetNetParams(pDev->pHandle, &oldParams, &newParams);
                                if(nRes != 0) ShowMessage("修改网络参数失败，返回值 = " + IntToStr(nRes));
                                else ShowMessage("修改网络参数成功");

                                return;
                            }
                        }
                    }
                }

                
            }
            else
            {
                edtDevIP->Text = "";
                edtMask->Text = "";
                edtGate->Text = "";
                //edtMAC->Text = "";
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tvConnectDevClick(TObject *Sender)
{
    if(tvConnectDev->Selected == NULL) return;

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
                String strViewIP = nodes->Item[i]->Text;

                int nCount = lvDevList->Items->Count;
                for(int i = 0; i < nCount; i++)
                {
                    if(strViewIP == lvDevList->Items->Item[i]->Caption)
                    {
                        edtDevIP->Text = strViewIP;
                        edtMask->Text = lvDevList->Items->Item[i]->SubItems->Strings[0];
                        edtGate->Text = lvDevList->Items->Item[i]->SubItems->Strings[1];
                        //edtMAC->Text = lvDevList->Items->Item[i]->SubItems->Strings[2];
                    }
                }
            }
            else
            {
                edtDevIP->Text = "";
                edtMask->Text = "";
                edtGate->Text = "";
                //edtMAC->Text = "";
            }
        }
    }
}
//---------------------------------------------------------------------------

