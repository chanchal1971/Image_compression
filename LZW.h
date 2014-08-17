// LZW.h : main header file for the LZW application
//

#if !defined(AFX_LZW_H__7AEB01EE_5827_417F_92EA_8343D93969E7__INCLUDED_)
#define AFX_LZW_H__7AEB01EE_5827_417F_92EA_8343D93969E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLZWApp:
// See LZW.cpp for the implementation of this class
//

class CLZWApp : public CWinApp
{
public:
	CLZWApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLZWApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLZWApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LZW_H__7AEB01EE_5827_417F_92EA_8343D93969E7__INCLUDED_)
