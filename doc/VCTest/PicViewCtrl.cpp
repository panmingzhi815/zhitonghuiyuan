#include "stdafx.h"
#include "PicViewCtrl.h"
#include <afxpriv.h>
#include "math.h"
#include "resource.h"
#include "Shlwapi.h"
//#include "ForGlobal.h"
#define IMAGEHEIGHT 576
#define IMAGEWIDTH  720

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPicViewCtrl

CPicViewCtrl::CPicViewCtrl()
: m_bDrawPlate(false)
{
	m_pPicture = NULL;
	m_bAutoFit = false;
	m_bStretch = true;
	m_bText=false;
	m_crText=::GetSysColor(COLOR_BTNFACE);
	m_crBackground = ::GetSysColor(COLOR_BTNFACE);
	m_nHeight = 26;
	m_nWidth = 12;

	m_bLine = false;

	m_nTop = 0;
	m_nLeft = 0;
	m_nRight = 0;
	m_nBottom = 0;
	m_hGlobal = NULL;

	m_ptOrg.x = 0,m_ptOrg.y = 0;
	CClientDC dc(FromHandle(this->m_hWnd));
	m_dcm.CreateCompatibleDC(&dc);
	m_bZoomOut = false;
	m_bShowCoorder = false;
	m_nILeft = m_nITop = 0;
	m_nIRight = IMAGEWIDTH;
	m_nIBottom = IMAGEHEIGHT;
	m_bdebug = false;
	m_nPlatePosL = 0;
	m_nPlatePosT = 0;
	m_nPlatePosR = 0;
	m_nPlatePosB = 0;

	m_nMaxWidth = 220;
	m_nMinWidth = 90;
	m_nDirectionFlag = NODIRECTION;
	m_bOSD = false;
	m_bReverse = false;
}

CPicViewCtrl::~CPicViewCtrl()
{
	if(m_hGlobal != NULL)
	{
		GlobalFree(m_hGlobal);
		m_hGlobal = NULL;
	}
	
	if(m_pPicture != NULL){
		m_pPicture->Release();
		m_pPicture = NULL;
	}

	if(m_Bmp.m_hObject != NULL)
		m_Bmp.DeleteObject();

	if(m_dcm.m_hDC != NULL)
		m_dcm.DeleteDC();
	
	m_ayZoomx.RemoveAll();
	m_ayZoomy.RemoveAll();
}

//-------------------------------------------------------------------
//	功能：
//		从文件中调入
//
//	返回：
//		成功(TRUE)或失败(FALSE)
//
//  参数：
//		LPCTSTR lpszFileName	文件名
//
//  说明：
//-------------------------------------------------------------------
BOOL CPicViewCtrl::LoadFromFile(LPCTSTR lpszFileName)
{
	if(m_pPicture != NULL){
		m_pPicture->Release();
		m_pPicture = NULL;
	}
	

	USES_CONVERSION;
	HRESULT hr = ::OleLoadPicturePath(
		const_cast<LPOLESTR>(T2COLE(lpszFileName)),
		NULL,
		0,
		0,
		IID_IPicture,
		reinterpret_cast<LPVOID *>(&m_pPicture)
		);

	if(GetSafeHwnd()) Invalidate();

	if (SUCCEEDED(hr) && m_pPicture != NULL)
		return TRUE;
	else
		return FALSE;
}

//-------------------------------------------------------------------
//	功能：
//		从图形中调入
//
//	返回：
//		成功(TRUE)或失败(FALSE)
//
//  参数：
//		LPPICTURE pPicture
//
//  说明：
//-------------------------------------------------------------------
BOOL CPicViewCtrl::LoadFromPicture(LPPICTURE pPicture)
{
	if(m_pPicture != pPicture)
	{
		if(m_pPicture != NULL)
		{
			m_pPicture->Release();
			m_pPicture = NULL;
		}

	
		m_pPicture = pPicture;
		if(m_pPicture != NULL) 
			m_pPicture->AddRef(); 

		if(GetSafeHwnd()) 
		{
			Invalidate();
		}
	}

	return TRUE;
}

//-------------------------------------------------------------------
//	功能：
//		从另一个图形显示控件中调入
//
//	返回：
//		成功(TRUE)或失败(FALSE)
//
//  参数：
//		CPicViewCtrl* pCtrl	图形显示控件
//
//  说明：
//-------------------------------------------------------------------
BOOL CPicViewCtrl::LoadFromControl(CPicViewCtrl* pCtrl)
{
	ASSERT(pCtrl != NULL);
	return LoadFromPicture(pCtrl->m_pPicture);
}

//-------------------------------------------------------------------
//	功能：
//		擦除显示
//
//	返回：
//		无
//
//  参数：
//		无
//
//  说明：
//-------------------------------------------------------------------
void CPicViewCtrl::Erase()
{
	if(m_pPicture != NULL)
	{
		m_pPicture->Release();
		m_pPicture = NULL;
	}

	if(GetSafeHwnd()) Invalidate();
}

BEGIN_MESSAGE_MAP(CPicViewCtrl, CStatic)
	//{{AFX_MSG_MAP(CPicViewCtrl)
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_COMMAND(IDM_ZOOMVALID, OnZoomvalid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPicViewCtrl message handlers

void CPicViewCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	//绘图区域
	CRect rcClient;
	GetClientRect(&rcClient);
	if(m_bZoomOut)
	{
	
		CBitmap *pBmpOld = m_dcm.SelectObject(&m_Bmp);
		BOOL d=StretchBlt(dc.m_hDC,0,0,rcClient.Width(),rcClient.Height(),m_dcm.m_hDC,m_ptDown.x,m_ptDown.y,m_lWidth,m_lHeight,SRCCOPY);
		m_dcm.SelectObject(pBmpOld);
		return;
	}

	if(m_pPicture != NULL)
	{
				//涂上底色
		CBrush Brush;
		Brush.CreateSolidBrush(m_crBackground); 
		FillRect(m_dcm.m_hDC,&rcClient,Brush);
		Brush.DeleteObject();

		StretchBlt(dc.m_hDC,0,0,rcClient.Width(),rcClient.Height(),m_dcm.m_hDC,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);
		//获取调色板
		HPALETTE hPal;
		m_pPicture->get_hPal(reinterpret_cast<OLE_HANDLE *>(&hPal));

		//图像尺寸
		SIZE sizeHiMetric;
		m_pPicture->get_Width(reinterpret_cast<OLE_XSIZE_HIMETRIC *>(&sizeHiMetric.cx));
		m_pPicture->get_Height(reinterpret_cast<OLE_YSIZE_HIMETRIC *>(&sizeHiMetric.cy));

		//转换为像素单位
		const int HIMETRIC_PER_INCH = 2540;
		const int nPixelsPerInchX = ::GetDeviceCaps(dc.GetSafeHdc(), LOGPIXELSX);
		const int nPixelsPerInchY = ::GetDeviceCaps(dc.GetSafeHdc(), LOGPIXELSY);
		SIZE sizePixel;
		sizePixel.cx = (nPixelsPerInchX * sizeHiMetric.cx + HIMETRIC_PER_INCH / 2) / HIMETRIC_PER_INCH;
		sizePixel.cy = (nPixelsPerInchY * sizeHiMetric.cy + HIMETRIC_PER_INCH / 2) / HIMETRIC_PER_INCH;

		//设置调色板
		CPalette *pPalOld = NULL;
		if (hPal != NULL)
		{
			pPalOld = dc.SelectPalette(CPalette::FromHandle(hPal), FALSE);
			dc.RealizePalette();
		}

		//实际绘图区域
		CRect rcDraw = rcClient;
		//实际显示图形范围
		SIZE sizeGraphRegion = sizeHiMetric;

		//自造应?
		if(m_bAutoFit == TRUE)
		{
			int nDestWidth = rcClient.Width();
			int nDestHeight = rcClient.Height();
			if(sizePixel.cx < nDestWidth && sizePixel.cy < nDestHeight)
			{
				//图形宽高均小于绘图区宽高,则分别缩小绘图区域的宽高与图形一致
				rcDraw.DeflateRect(
					(nDestWidth - sizePixel.cx) / 2,
					(nDestHeight - sizePixel.cy) / 2
					);
			}
			else
			{
				//调整绘图区域与图形的宽之比与高之比相等
				double wR = (double)nDestWidth / (double)sizePixel.cx; 
				double hR = (double)nDestHeight / (double)sizePixel.cy;
				if(wR > hR)
				{
					//绘图区域与图形的宽之比大于高之比,则缩小绘图区域的宽度
					rcDraw.DeflateRect(
						(nDestWidth - int(sizePixel.cx*hR + 0.5)) / 2 ,
						0
						);
				}
				else if(wR < hR)
				{
					//绘图区域与图形的宽之比小于高之比,则缩小绘图区域的高度
					rcDraw.DeflateRect(
						0,
						(nDestHeight - int(sizePixel.cy*wR + 0.5)) / 2 
						);
				}
			}
		}

		//拉伸?
		if(m_bStretch == FALSE)
		{
			if(rcDraw.Width() < sizePixel.cx)
			{
				//如果绘图区域的宽小于图形的宽则缩小图形显示的宽度
				sizeGraphRegion.cx = (rcDraw.Width() * HIMETRIC_PER_INCH + nPixelsPerInchX / 2) / nPixelsPerInchX;
			}
			else if(rcDraw.Width() > sizePixel.cx && m_bAutoFit == FALSE)
			{
				//如果绘图区域的宽大于图形的宽且没有自动调整过则缩小绘图区域的宽度
				rcDraw.DeflateRect(
					(rcDraw.Width() - sizePixel.cx) / 2,
					0
					);
			}

			if(rcDraw.Height() < sizePixel.cy)
			{
				//如果绘图区域的高小于图形的高则缩小图形显示的高度
				sizeGraphRegion.cy = (rcDraw.Height() * HIMETRIC_PER_INCH + nPixelsPerInchY / 2) / nPixelsPerInchY;
			}
			else if(rcDraw.Height() > sizePixel.cy && m_bAutoFit == FALSE)
			{
				//如果绘图区域的高大于图形的高且没有自动调整过则缩小绘图区域的高度
				rcDraw.DeflateRect(
					0,
					(rcDraw.Height() - sizePixel.cy) / 2
					);
			}
		}

		//透明?
		DWORD dwAttr;
		if (FAILED(m_pPicture->get_Attributes(&dwAttr)) || (dwAttr & PICTURE_TRANSPARENT))
		{
			if(m_Bmp.m_hObject == NULL)
			{
				m_Bmp.CreateCompatibleBitmap(&dc,rcDraw.Width() ,rcDraw.Height() );  
			}

				CBitmap *pBmpOld = m_dcm.SelectObject(&m_Bmp);
			CPalette *pPalMemOld = NULL;
			if (hPal != NULL)
			{
				pPalMemOld = m_dcm.SelectPalette(CPalette::FromHandle(hPal), FALSE);
				m_dcm.RealizePalette();
			}

			CRect rc(0, 0, rcDraw.Width(), rcDraw.Height());  
			m_dcm.FillSolidRect(&rc, m_crBackground);

			//调用IPicture的Render在内存绘图
			m_pPicture->Render(
				m_dcm.GetSafeHdc(),
				0, 0, rc.Width(), rc.Height(),  
				0, sizeHiMetric.cy, sizeGraphRegion.cx, -sizeGraphRegion.cy,
				&rc
				);

			//从内存输出到绘图区
			dc.BitBlt(
				rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), 
				&m_dcm, 
				0, 0, 
				SRCCOPY
				);

			m_dcm.SelectObject(pBmpOld);

			if (pPalMemOld != NULL)
			{
				ASSERT(hPal != NULL);
				m_dcm.SelectPalette(pPalMemOld, FALSE);
			}
		}
		else
		{
			if(m_Bmp.m_hObject == NULL)
			{
				m_Bmp.CreateCompatibleBitmap(&dc,rcDraw.Width() ,rcDraw.Height() );  
			}
			

			CBitmap *pBmpOld = m_dcm.SelectObject(&m_Bmp);
				CRect rc(0, 0, rcDraw.Width(), rcDraw.Height());  
			m_dcm.FillSolidRect(&rc, m_crBackground);
			//调用IPicture的Render绘图
			m_pPicture->Render(
				 m_dcm.GetSafeHdc(),
				 rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
				 0, sizeHiMetric.cy, sizeGraphRegion.cx, -sizeGraphRegion.cy,
				 &rcDraw
				 );
				//从内存输出到绘图区
			dc.BitBlt(
				rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), 
				&m_dcm, 
				0, 0, 
				SRCCOPY
				);

			m_dcm.SelectObject(pBmpOld);
		}

		if (pPalOld != NULL)
		{
			ASSERT(hPal != NULL);
			m_dcm.SelectPalette(pPalOld, FALSE);
		}
//将车牌位置定位出
		if(m_bDrawPlate)
		{
			//画坐标
		
			
			int nW = m_nPlatePosR - m_nPlatePosL;
			int nH = m_nPlatePosB - m_nPlatePosT;

			if(nW != 0 && nH != 0)
			{
				COLORREF cl;
				
				
				if(nW <= m_nMaxWidth && nW >= m_nMinWidth)
					cl = RGB(0,255,0);
				else if(nW > m_nMaxWidth)
					cl = RGB(255,0,0);
				else if(nW < m_nMinWidth)
					cl = RGB(255,255,0);
				CPen pen1(PS_SOLID,3,cl);
				CPen *pOldPen = dc.SelectObject(&pen1);
				float x = (float)IMAGEWIDTH/(float)rcClient.Width();
				float y = (float)IMAGEHEIGHT/(float)rcClient.Height();
				int nLeft,nTop,nRight,nBottom;


				nLeft = (int)(m_nPlatePosL/x);
				nTop = (int)(m_nPlatePosT/y);
				nRight = (int)(m_nPlatePosR/x);
				nBottom = (int)(m_nPlatePosB/y);

				CRect rc(nLeft,nTop,nRight,nBottom);
				dc.MoveTo(nLeft,nTop);
				dc.LineTo(nRight,nTop);
				dc.LineTo(nRight,nBottom);
				dc.LineTo(nLeft,nBottom);
				dc.LineTo(nLeft,nTop);

// 				CFont ft;
// 				LOGFONT lf;
// 				::GetObject(::GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
// 				StrCpy(lf.lfFaceName, "宋体");
// 				lf.lfHeight = 12;
// 				lf.lfWidth = 10;
// 				ft.CreateFontIndirect(&lf);
// 				CFont *pOldFont=dc.SelectObject(&ft);
// 				
// 				CString str;
// 				str.Format("(%d,%d)",nW - 60,nH);
// 				dc.TextOut(nRight+2,nBottom,str);
// 				
// 				dc.SelectObject(pOldFont);
// 				
// 				dc.SelectObject(pOldPen);

			}
			
			
		}
		if(m_bLine)
		{
			
			//画坐标
			CRect rc;
			GetClientRect(&rc);
			CPen pen(PS_SOLID,0,RGB(0,147,73));
			CPen *pOldPen = dc.SelectObject(&pen);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(0,147,73));
			
			CFont ft;
			LOGFONT lf;
			::GetObject(::GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
			StrCpy(lf.lfFaceName, "宋体");
			lf.lfHeight = 8;
			lf.lfWidth = 6;
			ft.CreateFontIndirect(&lf);
			CFont *pOldFont=dc.SelectObject(&ft);
			int i = 0;
			CString str;
			for(i=0;i<=(int)(IMAGEHEIGHT/50);i++)
			{
				dc.MoveTo(0,i*50*rc.bottom/IMAGEHEIGHT);
				dc.LineTo(rc.right,i*50*rc.bottom/IMAGEHEIGHT);
				if(i>0)
				{
					str.Format("%d",i*50);
					
					dc.TextOut(0,(i-1)*50*rc.bottom/IMAGEHEIGHT+15,str);
					
				}
			}
			
			for(i=0;i<=(int)(IMAGEWIDTH/50);i++)
			{
				dc.MoveTo(i*50*rc.right/IMAGEWIDTH,0);
				dc.LineTo(i*50*rc.right/IMAGEWIDTH,rc.bottom);
				
				if(i>0)
				{
					str.Format("%d",i*50);
					if(i>1)
						dc.TextOut((i-1)*50*rc.right/IMAGEWIDTH+10,0,str);
					else
						dc.TextOut((i-1)*50*rc.right/IMAGEWIDTH+16,0,str);
				}
			}
			dc.TextOut(0,0,"0");
			dc.SelectObject(pOldPen);
			CPen pen1(PS_SOLID,0,RGB(255,0,0));
			
			pOldPen = dc.SelectObject(&pen1);
			dc.MoveTo(rc.right*m_nLeft/IMAGEWIDTH,rc.bottom*m_nTop/IMAGEHEIGHT);
			dc.LineTo(rc.right*m_nLeft/IMAGEWIDTH,rc.bottom*m_nBottom/IMAGEHEIGHT);
			dc.LineTo(rc.right*m_nRight/IMAGEWIDTH,rc.bottom*m_nBottom/IMAGEHEIGHT);
			dc.LineTo(rc.right*m_nRight/IMAGEWIDTH,rc.bottom*m_nTop/IMAGEHEIGHT);
			dc.LineTo(rc.right*m_nLeft/IMAGEWIDTH,rc.bottom*m_nTop/IMAGEHEIGHT);
			
			dc.SelectObject(pOldPen);
			
			dc.SelectObject(pOldFont);
			
			
		}
		if(m_bOSD)
		{
			CFont ft;
			LOGFONT lf;
			::GetObject(::GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
			StrCpy(lf.lfFaceName, "宋体");
			lf.lfHeight = 12;
			lf.lfWidth = 10;
			ft.CreateFontIndirect(&lf);
			CFont *pOldFont=dc.SelectObject(&ft);

			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOut(0,0,m_strText);
			dc.SelectObject(pOldFont);


			POINT pt[4];
			CPen pen(PS_SOLID, 2, RGB(255, 255, 0));
			CPen* pOldPen = dc.SelectObject(&pen);

			// and a solid red brush
			CBrush brush(RGB(255, 255, 255));
			CBrush* pOldBrush = dc.SelectObject(&brush);

			//显示方向
			switch(m_nDirectionFlag)
			{
			case LEFTDIRECTION:
				{
					pt[0].x = rcClient.right - 45;
					pt[0].y = rcClient.top + 20;
					pt[1].x = rcClient.right - 30;
					pt[1].y = rcClient.top + 10;
					pt[2].x = rcClient.right - 35;
					pt[2].y = rcClient.top + 20;
					pt[3].x = rcClient.right - 30;
					pt[3].y = rcClient.top + 30;
					dc.Polygon(pt,4);

					if(m_bReverse)
					{
						//逆行
						pt[0].x = rcClient.right - 10;
						pt[0].y = rcClient.top + 20;
						pt[1].x = rcClient.right - 25;
						pt[1].y = rcClient.top + 10;
						pt[2].x = rcClient.right - 20;
						pt[2].y = rcClient.top + 20;
						pt[3].x = rcClient.right - 25;
						pt[3].y = rcClient.top + 30;
						dc.MoveTo(pt[0].x,pt[0].y);
						dc.LineTo(pt[1].x,pt[1].y);
						dc.LineTo(pt[2].x,pt[2].y);
						dc.LineTo(pt[3].x,pt[3].y);
						dc.LineTo(pt[0].x,pt[0].y);
					}
				}
				
				break;
			case RIGHTDIRECTION:
				{
					pt[0].x = rcClient.right - 10;
					pt[0].y = rcClient.top + 20;
					pt[1].x = rcClient.right - 25;
					pt[1].y = rcClient.top + 10;
					pt[2].x = rcClient.right - 20;
					pt[2].y = rcClient.top + 20;
					pt[3].x = rcClient.right - 25;
					pt[3].y = rcClient.top + 30;
					dc.Polygon(pt,4);

					if(m_bReverse)
					{
						//逆行
						pt[0].x = rcClient.right - 45;
						pt[0].y = rcClient.top + 20;
						pt[1].x = rcClient.right - 30;
						pt[1].y = rcClient.top + 10;
						pt[2].x = rcClient.right - 35;
						pt[2].y = rcClient.top + 20;
						pt[3].x = rcClient.right - 30;
						pt[3].y = rcClient.top + 30;
						dc.MoveTo(pt[0].x,pt[0].y);
						dc.LineTo(pt[1].x,pt[1].y);
						dc.LineTo(pt[2].x,pt[2].y);
						dc.LineTo(pt[3].x,pt[3].y);
						dc.LineTo(pt[0].x,pt[0].y);
					}
				}
				break;
			case TOPDIRECTION:
				{
					pt[0].x = rcClient.right - 20;
					pt[0].y = rcClient.top + 5;
					pt[1].x = rcClient.right - 30;
					pt[1].y = rcClient.top + 25;
					pt[2].x = rcClient.right - 20;
					pt[2].y = rcClient.top + 20;
					pt[3].x = rcClient.right - 10;
					pt[3].y = rcClient.top + 25;
					dc.Polygon(pt,4);

					if(m_bReverse)
					{
						//逆行
						pt[0].x = rcClient.right - 20;
						pt[0].y = rcClient.top + 35;
						pt[1].x = rcClient.right - 30;
						pt[1].y = rcClient.top + 30;
						pt[2].x = rcClient.right - 20;
						pt[2].y = rcClient.top + 50;
						pt[3].x = rcClient.right - 10;
						pt[3].y = rcClient.top + 30;
						dc.MoveTo(pt[0].x,pt[0].y);
						dc.LineTo(pt[1].x,pt[1].y);
						dc.LineTo(pt[2].x,pt[2].y);
						dc.LineTo(pt[3].x,pt[3].y);
						dc.LineTo(pt[0].x,pt[0].y);
					}
				}
				break;
			case BOTTOMDIRECTION:
				{
					//逆行
					pt[0].x = rcClient.right - 20;
					pt[0].y = rcClient.top + 35;
					pt[1].x = rcClient.right - 30;
					pt[1].y = rcClient.top + 30;
					pt[2].x = rcClient.right - 20;
					pt[2].y = rcClient.top + 50;
					pt[3].x = rcClient.right - 10;
					pt[3].y = rcClient.top + 30;
					dc.Polygon(pt,4);

					if(m_bReverse)
					{
						pt[0].x = rcClient.right - 20;
						pt[0].y = rcClient.top + 5;
						pt[1].x = rcClient.right - 30;
						pt[1].y = rcClient.top + 25;
						pt[2].x = rcClient.right - 20;
						pt[2].y = rcClient.top + 20;
						pt[3].x = rcClient.right - 10;
						pt[3].y = rcClient.top + 25;
						dc.MoveTo(pt[0].x,pt[0].y);
						dc.LineTo(pt[1].x,pt[1].y);
						dc.LineTo(pt[2].x,pt[2].y);
						dc.LineTo(pt[3].x,pt[3].y);
						dc.LineTo(pt[0].x,pt[0].y);
					}
				}
				break;
			default:
				break;
			}
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);

		}
		//话区域坐标
		if(m_bShowCoorder)
		{
				//画坐标
			
			/*CFont ft;
			LOGFONT lf;
			::GetObject(::GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
			StrCpy(lf.lfFaceName, "宋体");
			lf.lfHeight = 8;
			lf.lfWidth = 6;
			ft.CreateFontIndirect(&lf);
			CFont *pOldFont=dc.SelectObject(&ft);

			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(0,147,73));*/

			CPen pen1(PS_SOLID,2,RGB(0,0,255));
			
			CPen *pOldPen = dc.SelectObject(&pen1);
			int nLeft,nTop,nRight,nBottom;
			float x = (float)IMAGEWIDTH/(float)rcClient.Width();
			float y = (float)IMAGEHEIGHT/(float)rcClient.Height();
			nLeft = (int)(m_nILeft/x);
			nTop = (int)(m_nITop/y);
			nRight = (int)(m_nIRight/x);
			nBottom = (int)(m_nIBottom/y);

			CRect rc(nLeft,nTop,nRight,nBottom);
			dc.MoveTo(nLeft,nTop);
			dc.LineTo(nRight,nTop);
			dc.LineTo(nRight,nBottom);
			dc.LineTo(nLeft,nBottom);
			dc.LineTo(nLeft,nTop);
			dc.SelectObject(pOldPen);
			
			/*CString str;
			str.Format("%d,%d",m_nILeft,m_nITop);
			dc.TextOut(nLeft,nTop-10,str);

			str.Format("%d,%d",m_nIRight,m_nIBottom);
			dc.TextOut(nRight-100,nBottom-10,str);
			
			dc.SelectObject(pOldFont);*/
		}
	}
	
	else if(m_bText)
	{
		//涂上底色
		CBrush Brush;
		Brush.CreateSolidBrush(m_crBackground); 
		dc.FillRect(&rcClient, &Brush); 
		Brush.DeleteObject();
		
		CFont ft;
		LOGFONT lf;
		::GetObject(::GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
		StrCpy(lf.lfFaceName, "宋体");
		lf.lfHeight = m_nHeight;
		lf.lfWidth = m_nWidth;
		ft.CreateFontIndirect(&lf);
		
		CFont *pOldFont=dc.SelectObject(&ft);
		dc.SetTextColor(m_crText);
		dc.SetBkMode(TRANSPARENT);
		CRect rc1=rcClient;
		rcClient.left+=1;
		rcClient.top+=1;
		rcClient.right-=1;
		rcClient.bottom-=1;
		dc.DrawText(m_strText,&rcClient,DT_CENTER|DT_WORDBREAK|DT_CALCRECT|DT_END_ELLIPSIS);
		//重新定位文字区，使文字在文字区的中间显示
		rcClient.OffsetRect((rc1.Width()-rcClient.Width())/2-1,(rc1.Height()-rcClient.Height())/2-1);
		dc.DrawText(m_strText,&rcClient,DT_CENTER|DT_WORDBREAK|DT_END_ELLIPSIS);
		dc.SelectObject(pOldFont);
		//CStatic::OnPaint();
	}
	else if(m_pPicture==NULL)
	{
		//涂上底色
		 
		HDC hMemDC = CreateCompatibleDC(dc.m_hDC);
		CDC dcm;
		dcm.Attach(hMemDC);

		CBitmap Bmp;
		Bmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());  
		
		CBitmap *pBmpOld = dcm.SelectObject(&Bmp);
		CRect rc(0, 0, rcClient.Width(), rcClient.Height());  
		dcm.FillSolidRect(&rcClient,m_crBackground);
	
		
		BOOL d=StretchBlt(dc.m_hDC,0,0,rcClient.Width(),rcClient.Height(),hMemDC,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);
		dcm.SelectObject(pBmpOld);
		dcm.Detach();
		DeleteDC(hMemDC);
		 
	}

	// Do not call CStatic::OnPaint() for painting messages
}

BOOL CPicViewCtrl::LoadFromStream(HGLOBAL hGlobal,LONG lSize)
{
	if(m_pPicture != NULL){
		m_pPicture->Release();
		m_pPicture = NULL;
	}


	IStream *pStream; 

	CreateStreamOnHGlobal(hGlobal,TRUE,&pStream);
	if(pStream)
	{
		/*ULONG uwrite = 0;
		pStream->Write(p, lSize,&uwrite);
		if(uwrite==lSize)
		{
			ULARGE_INTEGER    pSeek;
			LARGE_INTEGER  dlibMove ={ 0 } ;
			pStream->Seek(dlibMove,STREAM_SEEK_SET ,&pSeek);*/

			
			HRESULT hr=OleLoadPicture(pStream,lSize,TRUE,IID_IPicture,(LPVOID*)&m_pPicture);
			if(GetSafeHwnd()) Invalidate();
			pStream->Release();
			
			if (SUCCEEDED(hr) && m_pPicture != NULL)
				return TRUE;
		//}
		
	}
	return FALSE;
}

void CPicViewCtrl::SetText(CString strText,COLORREF crText)
{
	m_strText=strText;
	m_crText=crText;
	Invalidate();
}

void CPicViewCtrl::IsText(bool bText)
{
	m_bText=bText;
}

void CPicViewCtrl::SetFontSize(int nWidth, int nHeight)
{
	m_nHeight = nHeight;
	m_nWidth = nWidth;
}

void CPicViewCtrl::LoadFromMemory(LPBYTE lp, int nLen)
{
	if(nLen == 0)
		return;
	if(m_hGlobal != NULL)
	{
		GlobalFree(m_hGlobal);
		m_hGlobal = NULL;
	}
	m_hGlobal = GlobalAlloc(GMEM_MOVEABLE,nLen);
 	LPVOID pvData1=NULL;
	if(m_hGlobal!=NULL)
	{
		if((pvData1=GlobalLock(m_hGlobal))!=NULL)
		{
		
			CopyMemory(pvData1,lp,nLen);
			GlobalUnlock(m_hGlobal);
			LoadFromStream(m_hGlobal,nLen);
		}	
		
	}
}
//设置放大参数
void CPicViewCtrl::SetZoomParams(CPoint ptStart,float fZoomx,float fZoomy)
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//绘图区域
	CRect rcClient;
	GetClientRect(&rcClient);
	m_pt = ptStart;

	CPoint ptViewOrg;
	CSize szView,szWindow;

	//设置放大映射区域
	ptViewOrg.x=ptViewOrg.y=0;
	szWindow.cx=m_lWidth;
	szWindow.cy=m_lHeight;
	szView.cx=rcClient.Width();
	szView.cy=rcClient.Height();
	
	m_dcm.SetMapMode(MM_ANISOTROPIC);
	m_dcm.SetWindowOrg(m_ptOrg);
	m_dcm.SetWindowExt(szWindow);
	m_dcm.SetViewportOrg(ptViewOrg);
	m_dcm.SetViewportExt(szView);

	//获取原始的坐标原点，即开始放大的位置
	m_dcm.DPtoLP(&ptStart);
	m_ptDown = ptStart;
	m_ptOrg = m_ptDown;

	//原始的放大区域
	
	m_lWidth=(long)(rcClient.Width()/fZoomx);
	m_lHeight=(long)(rcClient.Height()/fZoomy);

	//恢复放大映射区域参数

	ptViewOrg.x=ptViewOrg.y=0;
	szWindow.cx=rcClient.Width();
	szWindow.cy=rcClient.Height();
	szView.cx=rcClient.Width();
	szView.cy=rcClient.Height();
	
	m_dcm.SetMapMode(MM_ANISOTROPIC);
	m_dcm.SetWindowOrg(ptViewOrg);
	m_dcm.SetWindowExt(szWindow);
	m_dcm.SetViewportOrg(ptViewOrg);
	m_dcm.SetViewportExt(szView);
	Invalidate();
}
//恢复原始图形显示
void CPicViewCtrl::ResumeImage()
{
		
	CRect rc;
	this->GetClientRect(&rc);
	m_ptDown.x = 0;
	m_ptDown.y = 0;
	
	m_lWidth = rc.Width();
	m_lHeight = rc.Height();

	m_ayZoomx.RemoveAll();
	m_ayZoomy.RemoveAll();

	m_ptOrg = m_ptDown;

	m_bZoomOut = false;
	Invalidate();
}

void CPicViewCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
		
	if (point.x == -1 && point.y == -1){
		//keystroke invocation
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_PICMENU));
	
	 CMenu *pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if(m_bZoomOut)
	{
		pPopup->CheckMenuItem(IDM_ZOOMVALID,MF_CHECKED);
	}
	else
	{
		pPopup->CheckMenuItem(IDM_ZOOMVALID,MF_UNCHECKED);
	}

	
	CWnd* pWndPopupOwner = this;
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_NONOTIFY , point.x, point.y,
		pWndPopupOwner);
}

void CPicViewCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(NULL == m_pPicture || !m_bZoomOut)
		return;
	m_ptStart = point;
	m_ptEnd = point;
	CStatic::OnLButtonDown(nFlags, point);
}

void CPicViewCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(NULL == m_pPicture || !m_bZoomOut)
		return;
	if(m_ptStart.x < 0 && m_ptStart.y < 0)
	{
		return;
	}
	
	CRect rcClient;
	GetClientRect(&rcClient);
	float fZoomx;
	float fZoomy;
	CPoint pt;
	if(point.x>m_ptStart.x && point.y>m_ptStart.y)
		pt=m_ptStart;
	
	else if(point.x>m_ptStart.x && point.y<m_ptStart.y)
	{
		pt.x=m_ptStart.x;
		pt.y=point.y;
	}
	else if(point.x<m_ptStart.x && point.y<m_ptStart.y)
		pt=point;
	
	else if(point.x<m_ptStart.x && point.y>m_ptStart.y)
	{
		pt.x=point.x;
		pt.y=m_ptStart.y;
	}
	
	fZoomx = (float)rcClient.Width()/(float)abs(point.x - m_ptStart.x );
	fZoomy = (float)rcClient.Height()/(float)abs(point.y - m_ptStart.y );
	CString strZommx,strZoomy;
	if(m_ayZoomx.GetSize() > 0)
	{
		CString strZoom = m_ayZoomx.GetAt(m_ayZoomx.GetSize()-1);
		fZoomx = fZoomx * (float)atof(strZoom);
		strZoom = m_ayZoomy.GetAt(m_ayZoomy.GetSize()-1);
		fZoomy = fZoomy * (float)atof(strZoom);
	}
	strZommx.Format("%.4f",fZoomx);
	strZoomy.Format("%.4f",fZoomy);
	m_ayZoomx.Add(strZommx);
	m_ayZoomy.Add(strZoomy);	
	SetZoomParams(pt,fZoomx,fZoomy);
	CStatic::OnLButtonUp(nFlags, point);
}

void CPicViewCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(NULL == m_pPicture || !m_bZoomOut)
		return;

	if(nFlags==MK_LBUTTON)
	{
		//画矩形
		if(m_ptEnd!=point)
		{
			CDC *pDC=GetDC();
			int nMode=pDC->GetROP2();
			
			pDC->SelectStockObject(NULL_BRUSH);
			pDC->SetROP2(R2_NOT);
			CPen pen(PS_SOLID,2,RGB(255,0,0));
			CPen *pOldPen;
			pOldPen=pDC->SelectObject(&pen);
			pDC->Rectangle(m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y);
			pDC->SelectObject(pOldPen);
			//重新绘制新的矩形
			m_ptEnd=point;
			pOldPen=pDC->SelectObject(&pen);
			pDC->Rectangle(m_ptStart.x,m_ptStart.y,point.x,point.y);
			pDC->SelectObject(pOldPen);
			pDC->SetROP2(nMode);
			ReleaseDC(pDC);
		}
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CPicViewCtrl::OnZoomvalid() 
{
	// TODO: Add your command handler code here
	if(m_bZoomOut)
	{
		if(m_Bmp.m_hObject != NULL)
			m_Bmp.DeleteObject();
		ResumeImage();
		
	}
	else
	{
		ResumeImage();
		m_bZoomOut = true;
	}
}



//设置识别区域
void CPicViewCtrl::SetIdentiRange(int left, int top, int right, int bottom)
{
	m_nILeft = left;
	m_nITop = top;
	m_nIRight = right;
	m_nIBottom = bottom;
}
//重新生成位图
void CPicViewCtrl::ReCreate(CPicViewCtrl *pCtrl)
{
	if(m_pPicture != pCtrl->m_pPicture)
	{
		if(m_pPicture != NULL)
		{
			m_pPicture->Release();
			m_pPicture = NULL;
		}
		
		
		m_pPicture = pCtrl->m_pPicture;
		if(m_pPicture != NULL) 
			m_pPicture->AddRef(); 
		if(m_pPicture == NULL)
			return;
		
		if(GetSafeHwnd()) 
		{
			CPaintDC dc(this); // device context for painting
			
			// TODO: Add your message handler code here
			
			//绘图区域
			CRect rcClient;
			GetClientRect(&rcClient);
			//涂上底色
			CBrush Brush;
			Brush.CreateSolidBrush(m_crBackground); 
			FillRect(m_dcm.m_hDC,&rcClient,Brush);
			Brush.DeleteObject();
			
			StretchBlt(dc.m_hDC,0,0,rcClient.Width(),rcClient.Height(),m_dcm.m_hDC,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);
			//获取调色板
			HPALETTE hPal;
			m_pPicture->get_hPal(reinterpret_cast<OLE_HANDLE *>(&hPal));
			
			//图像尺寸
			SIZE sizeHiMetric;
			m_pPicture->get_Width(reinterpret_cast<OLE_XSIZE_HIMETRIC *>(&sizeHiMetric.cx));
			m_pPicture->get_Height(reinterpret_cast<OLE_YSIZE_HIMETRIC *>(&sizeHiMetric.cy));
			
			//转换为像素单位
			const int HIMETRIC_PER_INCH = 2540;
			const int nPixelsPerInchX = ::GetDeviceCaps(dc.GetSafeHdc(), LOGPIXELSX);
			const int nPixelsPerInchY = ::GetDeviceCaps(dc.GetSafeHdc(), LOGPIXELSY);
			SIZE sizePixel;
			sizePixel.cx = (nPixelsPerInchX * sizeHiMetric.cx + HIMETRIC_PER_INCH / 2) / HIMETRIC_PER_INCH;
			sizePixel.cy = (nPixelsPerInchY * sizeHiMetric.cy + HIMETRIC_PER_INCH / 2) / HIMETRIC_PER_INCH;
			
			//设置调色板
			CPalette *pPalOld = NULL;
			if (hPal != NULL)
			{
				pPalOld = dc.SelectPalette(CPalette::FromHandle(hPal), FALSE);
				dc.RealizePalette();
			}
			
			//实际绘图区域
			CRect rcDraw = rcClient;
			//实际显示图形范围
			SIZE sizeGraphRegion = sizeHiMetric;
			
			//自造应?
			if(m_bAutoFit == TRUE)
			{
				int nDestWidth = rcClient.Width();
				int nDestHeight = rcClient.Height();
				if(sizePixel.cx < nDestWidth && sizePixel.cy < nDestHeight)
				{
					//图形宽高均小于绘图区宽高,则分别缩小绘图区域的宽高与图形一致
					rcDraw.DeflateRect(
						(nDestWidth - sizePixel.cx) / 2,
						(nDestHeight - sizePixel.cy) / 2
						);
				}
				else
				{
					//调整绘图区域与图形的宽之比与高之比相等
					double wR = (double)nDestWidth / (double)sizePixel.cx; 
					double hR = (double)nDestHeight / (double)sizePixel.cy;
					if(wR > hR)
					{
						//绘图区域与图形的宽之比大于高之比,则缩小绘图区域的宽度
						rcDraw.DeflateRect(
							(nDestWidth - int(sizePixel.cx*hR + 0.5)) / 2 ,
							0
							);
					}
					else if(wR < hR)
					{
						//绘图区域与图形的宽之比小于高之比,则缩小绘图区域的高度
						rcDraw.DeflateRect(
							0,
							(nDestHeight - int(sizePixel.cy*wR + 0.5)) / 2 
							);
					}
				}
			}
			
			//拉伸?
			if(m_bStretch == FALSE)
			{
				if(rcDraw.Width() < sizePixel.cx)
				{
					//如果绘图区域的宽小于图形的宽则缩小图形显示的宽度
					sizeGraphRegion.cx = (rcDraw.Width() * HIMETRIC_PER_INCH + nPixelsPerInchX / 2) / nPixelsPerInchX;
				}
				else if(rcDraw.Width() > sizePixel.cx && m_bAutoFit == FALSE)
				{
					//如果绘图区域的宽大于图形的宽且没有自动调整过则缩小绘图区域的宽度
					rcDraw.DeflateRect(
						(rcDraw.Width() - sizePixel.cx) / 2,
						0
						);
				}
				
				if(rcDraw.Height() < sizePixel.cy)
				{
					//如果绘图区域的高小于图形的高则缩小图形显示的高度
					sizeGraphRegion.cy = (rcDraw.Height() * HIMETRIC_PER_INCH + nPixelsPerInchY / 2) / nPixelsPerInchY;
				}
				else if(rcDraw.Height() > sizePixel.cy && m_bAutoFit == FALSE)
				{
					//如果绘图区域的高大于图形的高且没有自动调整过则缩小绘图区域的高度
					rcDraw.DeflateRect(
						0,
						(rcDraw.Height() - sizePixel.cy) / 2
						);
				}
			}
			
			//透明?
			DWORD dwAttr;
			if (FAILED(m_pPicture->get_Attributes(&dwAttr)) || (dwAttr & PICTURE_TRANSPARENT))
			{
				if(m_Bmp.m_hObject == NULL)
				{
					m_Bmp.CreateCompatibleBitmap(&dc,rcDraw.Width() ,rcDraw.Height() );  
				}
				
				CBitmap *pBmpOld = m_dcm.SelectObject(&m_Bmp);
				CPalette *pPalMemOld = NULL;
				if (hPal != NULL)
				{
					pPalMemOld = m_dcm.SelectPalette(CPalette::FromHandle(hPal), FALSE);
					m_dcm.RealizePalette();
				}
				
				CRect rc(0, 0, rcDraw.Width(), rcDraw.Height());  
				m_dcm.FillSolidRect(&rc, m_crBackground);
				
				//调用IPicture的Render在内存绘图
				m_pPicture->Render(
					m_dcm.GetSafeHdc(),
					0, 0, rc.Width(), rc.Height(),  
					0, sizeHiMetric.cy, sizeGraphRegion.cx, -sizeGraphRegion.cy,
					&rc
					);
				
				//从内存输出到绘图区
				dc.BitBlt(
					rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), 
					&m_dcm, 
					0, 0, 
					SRCCOPY
					);
				
				m_dcm.SelectObject(pBmpOld);
				
				if (pPalMemOld != NULL)
				{
					ASSERT(hPal != NULL);
					m_dcm.SelectPalette(pPalMemOld, FALSE);
				}
			}
			else
			{
				if(m_Bmp.m_hObject == NULL)
				{
					m_Bmp.CreateCompatibleBitmap(&dc,rcDraw.Width() ,rcDraw.Height() );  
				}
				
				
				CBitmap *pBmpOld = m_dcm.SelectObject(&m_Bmp);
				CRect rc(0, 0, rcDraw.Width(), rcDraw.Height());  
				m_dcm.FillSolidRect(&rc, m_crBackground);
				//调用IPicture的Render绘图
				m_pPicture->Render(
					m_dcm.GetSafeHdc(),
					rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
					0, sizeHiMetric.cy, sizeGraphRegion.cx, -sizeGraphRegion.cy,
					&rcDraw
					);
// 				//从内存输出到绘图区
// 				dc.BitBlt(
// 					rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), 
// 					&m_dcm, 
// 					0, 0, 
// 					SRCCOPY
// 					);
				
				m_dcm.SelectObject(pBmpOld);
			}
			
			if (pPalOld != NULL)
			{
				ASSERT(hPal != NULL);
				m_dcm.SelectPalette(pPalOld, FALSE);
			}
		}
	}
	
}

