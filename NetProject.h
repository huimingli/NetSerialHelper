// NetProject.h : main header file for the NETPROJECT application
//

#if !defined(AFX_NETPROJECT_H__31C49B50_ECAD_4001_B6B6_05BFCDD50BDB__INCLUDED_)
#define AFX_NETPROJECT_H__31C49B50_ECAD_4001_B6B6_05BFCDD50BDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetProjectApp:
// See NetProject.cpp for the implementation of this class
//

class CNetProjectApp : public CWinApp
{
public:
	CNetProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetProjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetProjectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETPROJECT_H__31C49B50_ECAD_4001_B6B6_05BFCDD50BDB__INCLUDED_)
