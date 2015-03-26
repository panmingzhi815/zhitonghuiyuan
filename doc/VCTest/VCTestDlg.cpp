// VCTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VCTest.h"
#include "VCTestDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCTestDlg dialog

CVCTestDlg::CVCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVCTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCTestDlg)
	DDX_Control(pDX, IDC_CHECK_HIGHT, m_hight);
	DDX_Control(pDX, IDC_TREE_DEVICE, m_treeDevice);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_lsDevice);
	DDX_Control(pDX, IDC_STATIC_BIGIMAGE,m_picBigImage);
	DDX_Control(pDX, IDC_STATIC_PLATEIMAGE,m_picPlateImage);
	DDX_Control(pDX, IDC_STATIC_CIFIMAGE,m_picCifImage);
	DDX_Control(pDX, IDC_STATIC_PLATE,m_picPlate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCTestDlg, CDialog)
	//{{AFX_MSG_MAP(CVCTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCAN, OnButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, OnButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_VERIFYTIME, OnButtonVerifytime)
	ON_BN_CLICKED(IDC_CHECK_NTP, OnCheckNtp)
	ON_BN_CLICKED(IDC_BUTTON_SETNETPARAMS, OnButtonSetnetparams)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_CHECK_TIMER, OnCheckTimer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GETPARAMS, OnButtonGetparams)
	ON_BN_CLICKED(IDC_BUTTON_GETVERSION, OnButtonGetversion)
	ON_BN_CLICKED(IDC_BUTTON_GETALGPARAMS, OnButtonGetalgparams)
	ON_BN_CLICKED(IDC_CHECK_HIGHT, OnCheckHight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCTestDlg message handlers
/*******************************************************************
函数说明:设备信息回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pDeviceInfo 见DeviceInfo结构体定义
**********************************************************************/
void CALLBACK DeviceInfoFuc(void *pUserData, DeviceInfo *pDeviceInfo)
{
	CVCTestDlg *pDlg = (CVCTestDlg *)pUserData;
	if(pDlg == NULL)
		return;

	for(int i = 0;i<pDlg->m_lsDevice.GetItemCount();i++)
	{
		
		if((CString)pDeviceInfo->DeviceNetInfo.ucDeviceIP == pDlg->m_lsDevice.GetItemText(i,0))
		{
			pDlg->m_lsDevice.SetItemText(i,1,(CString)pDeviceInfo->ucDeviceVersion);
			pDlg->m_lsDevice.SetItemText(i,2,(CString)pDeviceInfo->DeviceNetInfo.ucGateIP);
			pDlg->m_lsDevice.SetItemText(i,3,(CString)pDeviceInfo->DeviceNetInfo.ucMaskIP);
			CString strMAC;
			strMAC.Format("%02X %02X %02X %02X %02X %02X",pDeviceInfo->ucMAC[0],pDeviceInfo->ucMAC[1],
				pDeviceInfo->ucMAC[2],
				pDeviceInfo->ucMAC[3],pDeviceInfo->ucMAC[4],pDeviceInfo->ucMAC[5]);
			pDlg->m_lsDevice.SetItemText(i,4,strMAC);
			return;
		}
	}
	pDlg->m_lsDevice.InsertItem(0,(CString)pDeviceInfo->DeviceNetInfo.ucDeviceIP);
	pDlg->m_lsDevice.SetItemText(0,1,(CString)pDeviceInfo->ucDeviceVersion);
	pDlg->m_lsDevice.SetItemText(0,2,(CString)pDeviceInfo->DeviceNetInfo.ucGateIP);
	pDlg->m_lsDevice.SetItemText(0,3,(CString)pDeviceInfo->DeviceNetInfo.ucMaskIP);
	CString strMAC;
	strMAC.Format("%02X %02X %02X %02X %02X %02X",pDeviceInfo->ucMAC[0],pDeviceInfo->ucMAC[1],
		pDeviceInfo->ucMAC[2],
		pDeviceInfo->ucMAC[3],pDeviceInfo->ucMAC[4],pDeviceInfo->ucMAC[5]);
	pDlg->m_lsDevice.SetItemText(0,4,strMAC);
}
/*******************************************************************
函数说明:设备信息回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pStatus 见DeviceStatus结构体定义
**********************************************************************/
 void CALLBACK  DeviceStatusFuc(void *pUserData, DeviceStatus *pStatus)
{

}
/*******************************************************************
函数说明:抓拍数据回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pData 见VehicleData结构体定义
**********************************************************************/
void CALLBACK VehicleDataFuc(void *pUserData, VehicleData *pData)
{
	CVCTestDlg *pDlg = (CVCTestDlg *)pUserData;
	if(pDlg == NULL)
		return;


	PDEVICEHANDLE handle = NULL;
	CString strIP;
	for(int i = 0;i < pDlg->m_lsDevice.GetItemCount();i++)
	{
		if(pDlg->m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			strIP = pDlg->m_lsDevice.GetItemText(i,0);
			if(strIP == (CString)pData->ucDeviceIP)
			{
				pDlg->m_picBigImage.LoadFromPicture(NULL);
				pDlg->m_picPlateImage.LoadFromPicture(NULL);
				pDlg->m_picPlate.LoadFromPicture(NULL);
				pDlg->m_picBigImage.LoadFromMemory(pData->pucBigImage,pData->uiBigImageLen);
				
				pDlg->m_picCifImage.LoadFromMemory(pData->pucCIFImage,pData->uiCIFImageLen);
				pDlg->m_picPlateImage.LoadFromMemory(pData->pucPlateImage,pData->uiPlateImageLen);
				pDlg->m_picPlate.IsText(true);
				switch(pData->PlateColor)
				{
				case BLUE_COLOR:
					{
						pDlg->m_picPlate.SetBackgroundColor(RGB(0,0,255));
						pDlg->m_picPlate.SetText(pData->ucPlate,RGB(255,255,255));
					}
					break;
				case YELLOW_COLOR:
					{
						pDlg->m_picPlate.SetBackgroundColor(RGB(255,255,0));
						pDlg->m_picPlate.SetText(pData->ucPlate,RGB(0,0,0));
					}
					break;
				case WHITE_COLOR:
					{
						pDlg->m_picPlate.SetBackgroundColor(RGB(255,255,255));
						pDlg->m_picPlate.SetText(pData->ucPlate,RGB(0,0,0));
					}
					break;
				case BLACK_COLOR:
					{
						pDlg->m_picPlate.SetBackgroundColor(RGB(0,0,0));
						pDlg->m_picPlate.SetText(pData->ucPlate,RGB(255,255,255));
					}
					break;
				default:
					{
						pDlg->m_picPlate.SetBackgroundColor(RGB(255,255,255));
						pDlg->m_picPlate.SetText(pData->ucPlate,RGB(0,0,0));
					}
					break;
				}
				break;
			}
		}
	}





	char chFileName[256] = {0x00};
	CString strPlateColor;
				switch(pData->PlateColor)
				{
				case YELLOW_COLOR:
					strPlateColor = "黄";
					
					break;
				case BLUE_COLOR:
					strPlateColor = "蓝";
					
					break;
				case WHITE_COLOR:
					strPlateColor = "白";
					
					break;
				case BLACK_COLOR:
					strPlateColor = "黑";
					
					break;
				case NON_PLATE:
					strPlateColor = "其他";
					
					break;
				}

			

	sprintf(chFileName,"%06d-%04d%02d%02d%02d%02d%02d-%03d-(%s%s)-big.jpg",pData->usSerialNO,
		pData->ucTime[0] + 2000,pData->ucTime[1],
		pData->ucTime[2],pData->ucTime[3],
		pData->ucTime[4],pData->ucTime[5],
		*((unsigned short *)(pData->ucTime + 6)),strPlateColor,
									pData->ucPlate);

	pDlg->SaveData(pData->ucTime,chFileName,(CString)pData->ucDeviceIP,pData->pucBigImage,pData->uiBigImageLen);
	

	sprintf(chFileName,"%06d-%04d%02d%02d%02d%02d%02d-%03d-(%s%s)-cif.jpg",pData->usSerialNO,
		pData->ucTime[0] + 2000,pData->ucTime[1],
		pData->ucTime[2],pData->ucTime[3],
		pData->ucTime[4],pData->ucTime[5],
		*((unsigned short *)(pData->ucTime + 6)),strPlateColor,
		pData->ucPlate);
	
	pDlg->SaveData(pData->ucTime,chFileName,(CString)pData->ucDeviceIP,pData->pucCIFImage,pData->uiCIFImageLen);
	


	sprintf(chFileName,"%06d-%04d%02d%02d%02d%02d%02d-%03d-(%s%s)-plate.jpg",pData->usSerialNO,
		pData->ucTime[0] + 2000,pData->ucTime[1],
		pData->ucTime[2],pData->ucTime[3],
		pData->ucTime[4],pData->ucTime[5],
		*((unsigned short *)(pData->ucTime + 6)),strPlateColor,
		pData->ucPlate);
	
	pDlg->SaveData(pData->ucTime,chFileName,(CString)pData->ucDeviceIP,pData->pucPlateImage,pData->uiPlateImageLen);
	


	CFile fl;
	CString strFile;
	strFile.Format("%s%s\\%04d%02d%02d.txt",pDlg->m_strAppPath,pData->ucDeviceIP,pData->ucTime[0] + 2000,pData->ucTime[1],pData->ucTime[2]);
				
	if(fl.Open(strFile,CFile::modeCreate | CFile::modeReadWrite  | CFile::modeNoTruncate))
	{
		CString strPlate = (CString)pData->ucPlate;
		CString strTemp;
					
					
		strTemp.Format("%s%s\r\n",strPlate,strPlateColor);
		fl.SeekToEnd();
		fl.Write(strTemp,strTemp.GetLength());
		fl.Flush();
		fl.Close();
	}

}




/*******************************************************************
函数说明:实时JPG流回调函数
参数说明：
pUserData 用户设置回调函数传入的用户数据
pJPGData见JPGData结构体定义
**********************************************************************/
void CALLBACK JPGStreamFuc(void *pUserData, JPGData *pJPGData)
{
	CVCTestDlg *pDlg = (CVCTestDlg *)pUserData;
	if(pDlg == NULL)
		return;

}
BOOL CVCTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	double d = 62322.95 * 25 / (440 * 0.00706);
	double m = (sqrt(d*d - 6000 * 6000)) / 1000;
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_lsDevice.InsertColumn(0,"IP",LVCFMT_CENTER,100);
	m_lsDevice.InsertColumn(1,"版本",LVCFMT_CENTER,100);
	m_lsDevice.InsertColumn(2,"网关",LVCFMT_CENTER,100);
	m_lsDevice.InsertColumn(3,"掩码",LVCFMT_CENTER,100);
	m_lsDevice.InsertColumn(4,"MAC地址",LVCFMT_CENTER,100);
	m_lsDevice.InsertColumn(5,"状态",LVCFMT_CENTER,100);
	
	ListView_SetExtendedListViewStyle
		(m_lsDevice.m_hWnd, LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT);

	char ch[MAX_PATH];
	ZeroMemory(ch,MAX_PATH);
	GetModuleFileName(AfxGetApp()->m_hInstance,ch,MAX_PATH);
	CString str=ch;
	m_strAppPath=str.Left(str.ReverseFind('\\')+1);
	

	LPR_Init(this->m_hWnd,this,DeviceInfoFuc,DeviceStatusFuc,VehicleDataFuc,JPGStreamFuc);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVCTestDlg::OnButtonScan() 
{
	// TODO: Add your control notification handler code here
	m_lsDevice.DeleteAllItems();
	LPR_ScanDevice();
}

void CVCTestDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here

	PDEVICEHANDLE handle = NULL;
	CString strIP;
	for(int i = 0;i < m_lsDevice.GetItemCount();i++)
	{
		if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			strIP = m_lsDevice.GetItemText(i,0);
			if(LPR_ConnectCamera(strIP.GetBuffer(strIP.GetLength()),&handle) == RESULT_OK)
			{
			
				m_treeDevice.InsertItem(strIP,TVI_ROOT,TVI_LAST);
				EquipmentInfo *pInfo = new EquipmentInfo();
				pInfo->handle = handle;
				StrCpy(pInfo->ucIP,strIP);
				m_lsEquipment.push_back(pInfo);
			}
			strIP.ReleaseBuffer();
			break;
		}
	}

	
}


void CVCTestDlg::OnButtonCapture() 
{
	// TODO: Add your control notification handler code here
	CString strIP;
	HTREEITEM hItem = m_treeDevice.GetRootItem();
	list <EquipmentInfo *>::const_iterator pos;
	//可以模拟触发多台设备
	while(NULL != hItem)
	{
		if(m_treeDevice.GetCheck(hItem))
		{
			strIP = m_treeDevice.GetItemText(hItem);
			for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
			{
				if((*pos)->ucIP == strIP)
				{
						LPR_Capture((*pos)->handle);
					break;
				}
			}
						
		}
		hItem = m_treeDevice.GetNextItem(hItem,TVGN_NEXT);
	}
	
	UpdateData(false);

}

void CVCTestDlg::OnButtonVerifytime() 
{
	// TODO: Add your control notification handler code here
	CString strIP;
	HTREEITEM hItem = m_treeDevice.GetRootItem();
	list <EquipmentInfo *>::const_iterator pos;
	//可以模拟触发多台设备
	while(NULL != hItem)
	{
		if(m_treeDevice.GetCheck(hItem))
		{
			strIP = m_treeDevice.GetItemText(hItem);
			for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
			{
				if((*pos)->ucIP == strIP)
				{
					LPR_AdjustTime((*pos)->handle,0);
					break;
				}
			}
			
		}
		hItem = m_treeDevice.GetNextItem(hItem,TVGN_NEXT);
	}
	

}

void CVCTestDlg::OnCheckNtp() 
{
	// TODO: Add your control notification handler code here
	CButton *pBtn = (CButton *)GetDlgItem(IDC_CHECK_NTP);

	CString strIP;
	HTREEITEM hItem = m_treeDevice.GetRootItem();
	list <EquipmentInfo *>::const_iterator pos;
	//可以模拟触发多台设备
	while(NULL != hItem)
	{
		if(m_treeDevice.GetCheck(hItem))
		{
			strIP = m_treeDevice.GetItemText(hItem);
			for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
			{
				if((*pos)->ucIP == strIP)
				{
						if(pBtn->GetCheck())
				
							LPR_NTPEnable((*pos)->handle,true,"192.168.1.168");
						else
							LPR_NTPEnable((*pos)->handle,false,NULL);
					break;
				}
			}
			
		}
		hItem = m_treeDevice.GetNextItem(hItem,TVGN_NEXT);
	}

	
}

void CVCTestDlg::OnButtonSetnetparams() 
{
	// TODO: Add your control notification handler code here
	CString strMAC;
	CString strIP;
	for(int i = 0;i < m_lsDevice.GetItemCount();i++)
	{
		if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			strMAC = m_lsDevice.GetItemText(i,4);
			strIP = m_lsDevice.GetItemText(i,0);
			break;
		}
	}
	LPBYTE bytMAC = NULL;
	int nDataLen = 0;
	StringHex(strMAC,bytMAC,nDataLen);
	NetParams newParams;
	ZeroMemory(&newParams,sizeof(NetParams));
	//调用程序可根据自己实际情况设置
	StrCpy((char *)newParams.ucDeviceIP, "192.168.9.80");
	StrCpy((char *)newParams.ucGateIP, "192.168.9.251");
	StrCpy((char *)newParams.ucMaskIP, "255.255.255.0");
	CopyMemory(newParams.ucMac,bytMAC,nDataLen);
	delete []bytMAC;
	bytMAC = NULL;
	NetParams oldParams;
	ZeroMemory(&oldParams,sizeof(NetParams));
	CButton *pBtn = (CButton *)GetDlgItem(IDC_CHECK_TCP);
	if(pBtn->GetCheck())
	{
	
		list <EquipmentInfo *>::const_iterator pos;
		//只能设置一台设备IP
	
				
				for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
				{
					if((*pos)->ucIP == strIP)
					{
						
						if(LPR_SetNetParams((*pos)->handle, &oldParams, &newParams) == RESULT_OK)
							MessageBox("设置成功","提示",0);
						else
							MessageBox("设置失败","提示",0);
						return;
					}
				}
				
		
		
		MessageBox("设备未连接","提示",0);
	}

	else
	{
		for(int i = 0;i < m_lsDevice.GetItemCount();i++)
		{
			if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
			{
				
				StrCpy((char *)oldParams.ucDeviceIP, m_lsDevice.GetItemText(i,0));
				StrCpy((char *)oldParams.ucGateIP,m_lsDevice.GetItemText(i,3));
				StrCpy((char *)oldParams.ucMaskIP,m_lsDevice.GetItemText(i,4));
				if(LPR_SetNetParams(NULL, &oldParams, &newParams) == RESULT_OK)
						MessageBox("设置成功","提示",0);
				else
						MessageBox("设置失败","提示",0);
				break;
			}
		}
		
	}
}

void CVCTestDlg::OnButtonDisconnect() 
{
	// TODO: Add your control notification handler code here
	CString strIP;
	for(int i = 0;i < m_lsDevice.GetItemCount();i++)
	{
		if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			
			strIP = m_lsDevice.GetItemText(i,0);
			break;
		}
	}


	list <EquipmentInfo *>::const_iterator pos;

		
			for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
			{
				if((*pos)->ucIP == strIP)
				{
					
					if(LPR_DisconnectCamera((*pos)->handle) == RESULT_OK)
						MessageBox("断开成功","提示",0);
					else
						MessageBox("断开失败","提示",0);
					return;
				}
			}
			
	
		MessageBox("设备未连接","提示",0);
}
//生成路径
bool CVCTestDlg::CreateDirectoryRecurrent(CString path)
{
	if (GetFileAttributes((LPCTSTR)path)==0xFFFFFFFF)
	{
		for (int i = path.Find('\\', 0) ; i != -1 ; )
		{
			if (GetFileAttributes((LPCTSTR)path.Left(i))==0xFFFFFFFF)
			{
				if (!CreateDirectory((LPCTSTR)path.Left(i), NULL))
					return false;
				
			}
			i = path.Find('\\', i + 1);
		}
		if (GetFileAttributes((LPCTSTR)path)==0xFFFFFFFF)
			return (bool)(CreateDirectory((LPCTSTR)path, NULL));
	}
	return true;
}
//字符串转16进制
 BOOL CVCTestDlg::StringHex(CString szSrc, LPBYTE& pData, int& nData)
{
	pData = new BYTE[(szSrc.GetLength() + 1) / 2];
	BOOL bHigh = true;
	nData = 0;
	BYTE val = 0;
	for (int i = 0 ; i < szSrc.GetLength() ; i ++)
	{
		if (szSrc[i] >= '0' && szSrc[i] <= '9')
			val = szSrc[i] - '0';
		else if (szSrc[i] >= 'A' && szSrc[i] <= 'F')
			val = szSrc[i] - 'A' + 10;
		else if (szSrc[i] >= 'a' && szSrc[i] <= 'f')
			val = szSrc[i] - 'a' + 10;
		else
		{
			if (!bHigh)
			{
				pData[nData++] /= 0x10;
			}
			/*if (szSrc[i] != ' ')
			break;*/
			continue;
		}
		if (bHigh)
		{
			pData[nData] = val * 0x10;
			bHigh = false;
		}
		else
		{
			pData[nData++] += val;
			bHigh = true;
		}
	}
	if (!bHigh)
	{
		pData[nData++] /= 0x10;
	}
	return true;
}
//存储数据
void CVCTestDlg::SaveData(unsigned char chTime[8],char *chFileName,CString strIP,unsigned char *pchData,unsigned int nDataLen)
{
	//获取时间，创建目录
	
	CString strPath;
	strPath.Format("%s%s\\%04d%02d%02d\\%02d\\",m_strAppPath,strIP,chTime[0] + 2000,chTime[1],chTime[2],chTime[3]);
	CreateDirectoryRecurrent(strPath);
	CFile fl;
	CString strFile;
	strFile.Format("%s%s",strPath,chFileName);
	//TRACE("%s len = %d\r\n",strFile,nDataLen);
	if(fl.Open(strFile,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		fl.Write(pchData,nDataLen);
		fl.Flush();
		fl.Close();
	}
	
	
}

void CVCTestDlg::OnCheckTimer() 
{
	// TODO: Add your control notification handler code here
	CButton *btn = (CButton *)GetDlgItem(IDC_CHECK_TIMER);
	CString str;
	CEdit *pEt = (CEdit *)GetDlgItem(IDC_EDIT_TIMEOUT);
	pEt->GetWindowText(str);
	int nTimeout = atoi(str.GetBuffer(str.GetLength()));
	str.ReleaseBuffer();

	if(btn->GetCheck() == 1)
	{
		SetTimer(1,nTimeout,NULL);
	}
	else
	{
		KillTimer(1);
	}
}

void CVCTestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnButtonCapture();
	CDialog::OnTimer(nIDEvent);
}



void CVCTestDlg::OnButtonGetparams() 
{
	// TODO: Add your control notification handler code here
	CString strIP;
	for(int i = 0;i < m_lsDevice.GetItemCount();i++)
	{
		if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			
			strIP = m_lsDevice.GetItemText(i,0);
			break;
		}
	}
	
	list <EquipmentInfo *>::const_iterator pos;
	
	for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
	{
		if((*pos)->ucIP == strIP)
		{
				ParamsInfo par;
				ZeroMemory(&par,sizeof(ParamsInfo));

				//图像压缩比获取
			/*	par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = IMAGE_QUALITY;
				par.bHasObject = TRUE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = BIG_IMAGE_QUALITY;*/

				//是否重启

// 				par.ucMainCmd = SYSTEM_CMD;
// 				par.ucSubCmd = DEVICE_RESTART;
// 				par.bHasObject = FALSE;
// 				par.ucCmdType = CMD_READ;
// 				par.usCmdLen = 0;
// 				par.ucObject = 0;

				//重启时间
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = RESTART_TIME;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

					//设备序列号
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = SERIRAL_NO;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				//设备编号

				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = DEVICE_ID;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				//机器码
				
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = DEVICE_CODE;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;
				//授权码
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = AUTHOR_INFO;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				//授权截止时间
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = AUTHOR_VALIDTIME;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				//授权方式
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = VERIFYTIME_MODE;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;
				//NIP服务IP
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = NTP_SERVERIP;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				//时间间隔
				par.ucMainCmd = SYSTEM_CMD;
				par.ucSubCmd = NTP_TIMEOUT;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				//调光模式
				par.ucMainCmd = LIGHT_CMD;
				par.ucSubCmd = LIGHT_MODE;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;


				//调光参数表
				par.ucMainCmd = LIGHT_CMD;
				par.ucSubCmd = LIGHT_PARAMS;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_READ;
				par.usCmdLen = 0;
				par.ucObject = 0;

				if(LPR_ControlParams((*pos)->handle,&par,500) == RESULT_OK)
				{
					MessageBox("控制参数成功","提示",0);
				}
				else
				{
					MessageBox("控制参数失败","提示",0);
				}

			return;
		}
	}
	
	
	
	MessageBox("设备未连接","提示",0);


}

void CVCTestDlg::OnButtonGetversion() 
{
	// TODO: Add your control notification handler code here
	CString strIP;
	for(int i = 0;i < m_lsDevice.GetItemCount();i++)
	{
		if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			
			strIP = m_lsDevice.GetItemText(i,0);
			break;
		}
	}

	list <EquipmentInfo *>::const_iterator pos;

			for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
			{
				if((*pos)->ucIP == strIP)
				{
					VersionInfo info;
					ZeroMemory(&info,sizeof(VersionInfo));
					if(LPR_GetAllVersion((*pos)->handle,&info) == RESULT_OK)
						MessageBox("获取版本信息成功","提示",0);
					else
						MessageBox("获取版本信息失败","提示",0);
					return;
				}
			}
			

	
		MessageBox("设备未连接","提示",0);
}

void CVCTestDlg::OnButtonGetalgparams() 
{
	// TODO: Add your control notification handler code here
		CString strIP;
	for(int i = 0;i < m_lsDevice.GetItemCount();i++)
	{
		if(m_lsDevice.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			
			strIP = m_lsDevice.GetItemText(i,0);
			break;
		}
	}
	
	list <EquipmentInfo *>::const_iterator pos;
	
	for(pos = m_lsEquipment.begin();pos != m_lsEquipment.end();pos++)
	{
		if((*pos)->ucIP == strIP)
		{
				AlgParams par;
				ZeroMemory(&par,sizeof(AlgParams));

			

				if(LPR_GetAlgParams((*pos)->handle,&par,500) == RESULT_OK)
				{
					MessageBox("控制参数成功","提示",0);
				}
				else
				{
					MessageBox("控制参数失败","提示",0);
				}

			return;
		}
	}
	
	
	
	MessageBox("设备未连接","提示",0);
}

void CVCTestDlg::OnCheckHight() 
{
	// TODO: Add your control notification handler code here

	CString strIP;
	for(int i = 0; i < m_lsDevice.GetItemCount(); i++)
	{
		if(m_lsDevice.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			
			strIP = m_lsDevice.GetItemText(i,0);
			break;
		}
	}
	
	list <EquipmentInfo *>::const_iterator pos;
	for(pos = m_lsEquipment.begin(); pos != m_lsEquipment.end(); pos++)
	{
		if((*pos)->ucIP == strIP)
		{
				ParamsInfo par;
				ZeroMemory(&par, sizeof(ParamsInfo));
				par.ucMainCmd = CAMERA_CMD;
				par.ucSubCmd = 0x08;
				par.bHasObject = FALSE;
				par.ucCmdType = CMD_WRITE;
				par.usCmdLen = 1;

				unsigned char ucValue = m_hight.GetCheck();
				CopyMemory(par.ucCmd, &ucValue, 1);

				if(LPR_ControlParams((*pos)->handle, &par, 500) == RESULT_OK)
				{
					MessageBox("设置成功","提示",0);
				}
				else
				{
					MessageBox("设置失败","提示",0);
				}

			return;
		}
	}
}
