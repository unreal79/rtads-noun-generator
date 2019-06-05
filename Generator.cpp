// Generator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Generator.h"
#include "GeneratorDlg.h"
#include "regexer.h"
#include "GeneratorIniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

REParser REP;

// globals:

structIniFile IniFile;
CString strGeneratorIniPath;
int old_IniFile_ChosenClasses_iNumberOfChosenClasses;


/////////////////////////////////////////////////////////////////////////////
// CGeneratorApp

BEGIN_MESSAGE_MAP(CGeneratorApp, CWinApp)
	//{{AFX_MSG_MAP(CGeneratorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp) помощь не нужна
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneratorApp construction

CGeneratorApp::CGeneratorApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGeneratorApp object

CGeneratorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGeneratorApp initialization

BOOL CGeneratorApp::InitInstance() {
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CGeneratorIniFile::OpenGeneratorIniFile();

	REP.init();
	REP.readrules(RULES_PATH);

	CGeneratorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
	} else if (nResponse == IDCANCEL) {	}

	CGeneratorIniFile::SaveGeneratorIniFile( );

	return FALSE;
}
