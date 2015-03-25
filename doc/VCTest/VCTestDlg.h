// VCTestDlg.h : header file
//

#if !defined(AFX_VCTESTDLG_H__D7BD8904_B7F8_4910_85BF_CBFFBD60E68F__INCLUDED_)
#define AFX_VCTESTDLG_H__D7BD8904_B7F8_4910_85BF_CBFFBD60E68F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PicViewCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CVCTestDlg dialog
typedef struct tagEquipmentInfo
{
	PDEVICEHANDLE handle;
	char ucIP[IP_MAX_LEN];
	tagEquipmentInfo()
	{
		handle = 0;
		ZeroMemory(ucIP,IP_MAX_LEN);
	}
}EquipmentInfo,*PEquipmentInfo;

class CVCTestDlg : public CDialog
{
// Construction
public:
	CVCTestDlg(CWnd* pParent = NULL);	// standard constructor

	bool CreateDirectoryRecurrent(CString path);
	list <EquipmentInfo *>m_lsEquipment;
	//´æ´¢Êý¾Ý
	void SaveData(unsigned char chTime[8],char *chFileName,CString strIP,unsigned char *pchData,unsigned int nDataLen);
	BOOL StringHex(CString szSrc, LPBYTE& pData, int& nData);
	CString m_strAppPath;
// Dialog Data
	//{{AFX_DATA(CVCTestDlg)
	enum { IDD = IDD_VCTEST_DIALOG };
	CButton	m_hight;
	CTreeCtrl	m_treeDevice;
	CListCtrl	m_lsDevice;
	CPicViewCtrl    m_picBigImage;
	CPicViewCtrl    m_picPlateImage;
	CPicViewCtrl    m_picCifImage;
	CPicViewCtrl    m_picPlate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVCTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonScan();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonCapture();
	afx_msg void OnButtonVerifytime();
	afx_msg void OnCheckNtp();
	afx_msg void OnButtonSetnetparams();
	afx_msg void OnButtonDisconnect();
	afx_msg void OnCheckTimer();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonGetparams();
	afx_msg void OnButtonGetversion();
	afx_msg void OnButtonGetalgparams();
	afx_msg void OnCheckHight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCTESTDLG_H__D7BD8904_B7F8_4910_85BF_CBFFBD60E68F__INCLUDED_)
