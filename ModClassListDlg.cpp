// ModClassListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Generator.h"
#include "ModClassListDlg.h"
#include "GeneratorIniFile.h"
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModClassListDlg dialog


CModClassListDlg::CModClassListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModClassListDlg::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CModClassListDlg)
	strEditaddcustom = _T("");
	//}}AFX_DATA_INIT
	bRunFirstTime = true;
}

void CModClassListDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.	Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CModClassListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModClassListDlg)
	DDX_Control(pDX, IDC_ADDCUSTOM, CAddcustom);
	DDX_Control(pDX, IDC_VIBRAN, CVibran);
	DDX_Control(pDX, IDC_DOSTUP, CDostup);
	DDX_Text(pDX, IDC_EDITADDCUSTOM, strEditaddcustom);
	//}}AFX_DATA_MAP
	if ( bRunFirstTime ) {
		int iCount = 0;
		CString DefaultClassesList[ 1000 ];
		CString str;

		bRunFirstTime = false;
		
		str.LoadString( IDS_CLASSSTRINGS );
		while( 1 ) {
			int itmp;
			itmp = str.Find( '\n' );
			if ( itmp == -1 )
				break;
			DefaultClassesList[ iCount ] = str.Left( itmp );
			str.Delete( 0, itmp + 1 );
			iCount++;
			if ( iCount > 999 ) {
				MessageBox( "Список не должен превышать 1000", "Ошибка" );
				break;
			}
		}
		for ( int i = 0; i < iCount; i++ )
			CDostup.AddString( DefaultClassesList[ i ] );

		for ( i = 0; i < IniFile.ChosenClasses.iNumberOfChosenClasses; i++ )
			CVibran.AddString( IniFile.ChosenClasses.strChosenClass[ i ] );

		SortList( &CDostup );
		SortList( &CVibran );

		CAddcustom.EnableWindow( FALSE );
	}
}


BEGIN_MESSAGE_MAP(CModClassListDlg, CDialog)
	//{{AFX_MSG_MAP(CModClassListDlg)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_EN_CHANGE(IDC_EDITADDCUSTOM, OnEnChangeEditaddcustom)
	ON_BN_CLICKED(IDC_ADDCUSTOM, OnBnClickedAddcustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CModClassListDlg, CDialog)
	//{{AFX_DISPATCH_MAP(CModClassListDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CModClassListDlg, CDialog)
	//{{AFX_INTERFACE_MAP(CModClassListDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_INTERFACE_MAP
END_INTERFACE_MAP()

// CModClassListDlg message handlers

void CModClassListDlg::SortList( CListBox * pCListBox ) {
	int iCount = pCListBox->GetCount();
	CString str;
	CString List[ 1000 ];

	if ( iCount < 2 || iCount > 999 )
		return;
	for ( int i = 0; i < iCount; i++)
		pCListBox->GetText( i, List[ i ] );
	for ( i = 0; i < iCount; i++ ) {
		for ( int j = i; j < iCount; j++ )
			if ( List[ i ].CompareNoCase( List[ j ] ) > 0 ) {
				str = List[ j ];
				List[ j ] = List[ i ];
				List[ i ] = str;
			}
	}

	// помечаем дубликаты
	for( i = 1; i < iCount; i++ )
		if ( List[ i ] == List[ i - 1 ] )
			List[ i ] = "Deleted\nItem";

	for ( i = 0; i < iCount; i++ )
		pCListBox->DeleteString( 0 );
	for ( i = 0; i < iCount; i++ )
		if ( List[ i ] != "Deleted\nItem" )
			pCListBox->AddString( List[ i ] );
}

void CModClassListDlg::OnBnClickedButton3() {
	int iCount = CVibran.GetCount();
	int iSelCount = CVibran.GetSelCount();
	CArray< int, int > aryVibranSel;
	CString str;

	if ( iSelCount == 0 )
		return;

	aryVibranSel.SetSize( iCount );
	CVibran.GetSelItems( iCount, aryVibranSel.GetData() );
/*	for ( int i = 0; i < iSelCount ; i++ ) {
		CVibran.GetText( aryVibranSel.GetAt( i ), str );
		CDostup.AddString( str );
	}
*/	for ( int i = 0; i < iSelCount ; i++ )
		CVibran.DeleteString( aryVibranSel.GetAt( i ) - i );
//	SortList( &CDostup );
	SortList( &CVibran );
}


void CModClassListDlg::OnBnClickedButton4() {
	int iCount = CVibran.GetCount();
	CString str;

/*	for ( int i = 0; i < iCount ; i++ ) {
		CVibran.GetText( i, str );
		CDostup.AddString( str );
	}
*/	for ( int i = 0; i < iCount ; i++ )
		CVibran.DeleteString( 0 );
//	SortList( &CDostup );
}

void CModClassListDlg::OnBnClickedButton5() {
	int iCount = CDostup.GetCount();
	int iSelCount = CDostup.GetSelCount();
	CArray< int, int > aryDostupSel;
	CString str;

	if ( iSelCount == 0 )
		return;

	if ( iCount + iSelCount > 999 ) {
		MessageBox( "Список не должен превышать 1000", "Ошибка" );
		return;
	}

	aryDostupSel.SetSize( iCount );
	CDostup.GetSelItems( iCount, aryDostupSel.GetData() );
	for ( int i = 0; i < iSelCount ; i++ ) {
		CDostup.GetText( aryDostupSel.GetAt( i ), str );
		CVibran.AddString( str );
	}
//	for ( int i = 0; i < iSelCount ; i++ )
//		CDostup.DeleteString( aryDostupSel.GetAt( i ) - i );
//	SortList( &CDostup );
	SortList( &CVibran );
}

void CModClassListDlg::OnBnClickedButton6() {
	int iCount = CDostup.GetCount();
	CString str;

	if ( iCount + CDostup.GetCount() > 999 ) {
		MessageBox( "Список не должен превышать 1000", "Ошибка" );
		return;
	}

	for ( int i = 0; i < iCount ; i++ ) {
		CDostup.GetText( i, str );
		CVibran.AddString( str );
	}
//	for ( int i = 0; i < iCount ; i++ )
//		CDostup.DeleteString( 0 );
	SortList( &CVibran );
}

void CModClassListDlg::OnEnChangeEditaddcustom() {
    UpdateData( TRUE );
    if ( strEditaddcustom != "" )
        CAddcustom.EnableWindow( TRUE );
    else
        CAddcustom.EnableWindow( FALSE );
//  UpdateData( FALSE );
}

void CModClassListDlg::OnBnClickedAddcustom() {
    UpdateData( TRUE );
    if ( strEditaddcustom != "" ) {
	    CVibran.AddString( strEditaddcustom );
		SortList( &CVibran );
	}
}

void CModClassListDlg::OnOK() {
	int iCount = CVibran.GetCount();
	CString str;

	for ( int i = 0; i < iCount; i++ ) {
		CVibran.GetText( i, str );
		IniFile.ChosenClasses.strChosenClass[ i ] = str;
	}
	IniFile.ChosenClasses.iNumberOfChosenClasses = iCount;
	
	CDialog::OnOK();
}
