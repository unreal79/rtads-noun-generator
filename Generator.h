// Generator.h : main header file for the GENERATOR application
//

#if !defined(AFX_GENERATOR_H__20905C7F_4AD4_4E2E_A55F_EDF78E7D25D5__INCLUDED_)
#define AFX_GENERATOR_H__20905C7F_4AD4_4E2E_A55F_EDF78E7D25D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define MAX_CLASSES 2000

struct structIniFile {
	struct structChosenClasses {
		int iNumberOfChosenClasses;
		CString strDefaultClass;
		CString (strChosenClass)[ MAX_CLASSES ];
	} ChosenClasses;
	struct structFont {
		LOGFONT logfontLogFont;
		COLORREF FontColor;
	} Font;
	struct structTabs {
		int iNumberOfTabs;
		int iTabsOrSpaces;
	} Tabs;
};


/////////////////////////////////////////////////////////////////////////////
// CGeneratorApp:
// See Generator.cpp for the implementation of this class
//

class CGeneratorApp : public CWinApp {
public:
	CGeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGeneratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATOR_H__20905C7F_4AD4_4E2E_A55F_EDF78E7D25D5__INCLUDED_)
