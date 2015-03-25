#if !defined(AFX_PICVIEWCTRL_H__99632867_947C_435D_8915_565EB8C798DE__INCLUDED_)
#define AFX_PICVIEWCTRL_H__99632867_947C_435D_8915_565EB8C798DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define NODIRECTION 0
#define LEFTDIRECTION 1
#define RIGHTDIRECTION 2
#define LEFTORRIGHT 3
#define TOPDIRECTION 4
#define BOTTOMDIRECTION 5
#define TOPORBOTTOM 6
/////////////////////////////////////////////////////////////////////////////
// CPicViewCtrl window

class CPicViewCtrl : public CStatic
{
// Construction
public:
	CPicViewCtrl();
	CStringArray m_ayZoomx,m_ayZoomy; //保存每次的放大倍数
	bool		m_bZoomOut;//是否放大
	bool        m_bShowCoorder;//是否显示坐标
	CBitmap		m_Bmp;
	CPoint      m_ptOrg;
	int         m_lWidth,m_lHeight;
	CDC			m_dcm;
	CPoint      m_ptDown;
	CPoint      m_ptStart,m_ptEnd;
	CPoint      m_pt;
	unsigned short         m_nILeft,m_nITop,m_nIRight,m_nIBottom;//识别区域
	bool        m_bdebug;
	int         m_nPlatePosL,m_nPlatePosT,m_nPlatePosR,m_nPlatePosB;
	int  m_nMinWidth,m_nMaxWidth;
	int m_nDirectionFlag;
	bool m_bOSD;
	bool m_bReverse;
// Attributes
public:
	LPPICTURE	m_pPicture;		//IPicture

public:
	BOOL		m_bAutoFit;		//自适应
	BOOL		m_bStretch;		//拉伸
	COLORREF	m_crBackground;	//背景色
	COLORREF m_crText;
	BOOL m_bText;//是否是显示文本
	//字体大小
	int m_nHeight,m_nWidth;//字体高宽
	CString m_strText;
	bool m_bLine;//是否画网格
	int m_nTop,m_nLeft,m_nRight,m_nBottom;
	HGLOBAL m_hGlobal;
// Operations
public:
	BOOL GetAutoFit() const { return m_bAutoFit; }
	BOOL GetStretch() const { return m_bStretch; }
	COLORREF GetBackgroundColor() const { return m_crBackground; }
	void SetAutoFit(BOOL bAutoFit) { m_bAutoFit = bAutoFit; }
	void SetStretch(BOOL bStretch) { m_bStretch = bStretch; }
	void SetBackgroundColor(COLORREF cr) { m_crBackground = cr; }

public:
	//从文件中调入
	BOOL LoadFromFile(LPCTSTR lpszFileName);
	//从另一图形中调入
	BOOL LoadFromPicture(LPPICTURE pPicture);
	//从另一图形显示控件中调入
	BOOL LoadFromControl(CPicViewCtrl* pCtrl);
	//擦除显示
	void Erase();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicViewCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReCreate(CPicViewCtrl *pCtrl);
	void SetIdentiRange(int left, int top,int right,int bottom);
	void ResumeImage();
	void SetZoomParams(CPoint ptStart,float fZoomx,float fZoomy);
	void LoadFromMemory(LPBYTE lp,int nLen);
	void SetFontSize(int nWidth,int nHeight);
	void IsText(bool bText);
	
	void SetText(CString strText,COLORREF crText);
	BOOL LoadFromStream(HGLOBAL hGlobal,LONG lSize);
	virtual ~CPicViewCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPicViewCtrl)
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnZoomvalid();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	// 是否将车牌位置定位出
	bool m_bDrawPlate;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICVIEWCTRL_H__99632867_947C_435D_8915_565EB8C798DE__INCLUDED_)
