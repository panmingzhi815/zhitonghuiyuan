// VCTest.h : main header file for the VCTEST application
//

#if !defined(AFX_VCTEST_H__571E0FFD_008F_4626_B85C_8D6DADC58D9B__INCLUDED_)
#define AFX_VCTEST_H__571E0FFD_008F_4626_B85C_8D6DADC58D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVCTestApp:
// See VCTest.cpp for the implementation of this class
//

class CVCTestApp : public CWinApp
{
public:
	CVCTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVCTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCTEST_H__571E0FFD_008F_4626_B85C_8D6DADC58D9B__INCLUDED_)
