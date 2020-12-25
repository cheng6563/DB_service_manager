// DB_service_manager.h : main header file for the DB_SERVICE_MANAGER application
//

#if !defined(AFX_DB_SERVICE_MANAGER_H__3B617592_739E_4110_8585_8867FA8CB596__INCLUDED_)
#define AFX_DB_SERVICE_MANAGER_H__3B617592_739E_4110_8585_8867FA8CB596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDB_service_managerApp:
// See DB_service_manager.cpp for the implementation of this class
//

class CDB_service_managerApp : public CWinApp
{
public:
	CDB_service_managerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDB_service_managerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDB_service_managerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB_SERVICE_MANAGER_H__3B617592_739E_4110_8585_8867FA8CB596__INCLUDED_)
