// GeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxwin.h"
#include "Generator.h"
#include "GeneratorDlg.h"
#include "regexer.h"
#include "ModClassListDlg.h"
#include "GeneratorIniFile.h"
#include "hlinkctrl\hlinkctl.h"

#include ".\generatordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globals

int iRod;
CFont Font;

using namespace regex;
using namespace std;

extern class REParser REP;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CEdit	CAbout;
	CString	strAbout;
	CHLinkCtrl ctrlRTADS_hlink;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CHLinkCtrl ctrlGrAndreyEmail;
	CHLinkCtrl ctrlStasEmail;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	strAbout = "Советы по генерации падежных форм:\r\n\r\n\
В верхнее поле ввода даётся выражение. \
Если оно более одной буквы, то немедленно начнется обработка. \
Если вас не устраивает \
результат, то,  вероятно, Вам необходимо поменять пол или \
свойство одушевлённости объекта. В ином случае перейдите на \
соответствующее поле и наберите нужное значение. \
Как только Вы начнете работу со строкой, справа от неё снимется \
галочка, которая обозначает, что при изменении именительного \
падежа (верхняя строка) данная строка не будет меняться. \
Если необходимо чтобы все падежные формы выглядели \
одинаково, поставьте галочку напротив первой строки.\r\n\r\n\
Три галочки во втором столбце вызывают добавление \
дополнительного слова с пометкой для парсера (синтаксического \
анализатора), указывающей его как соответствующий падеж. \
Галочка напротив родительного падежа создают пометку \
родительного падежа  для всех слов, определённых после \
предлогов \"из\", \"для\", \"от\" и многих других. Это позволит парсеру \
(синтаксическому анализатору) узнавать определяющие слова после \
определяемого существительного. Например, чтобы был распознан объект \
\"посох ужаса\", нужно ввести его как \"посох для ужаса\" и \
включить пометку напротив родительного падежа. Если \
вам нужен \"ключ из золота\", то пометку делать не нужно. \
Т.е. галочка нужна только в случае отсутствия предлога.\r\n\r\n\
Алгоритм рассчитан на предложение из прилагательных и \
существительных. Вводить можно до 15 слов. \
Два и более существительных будут обрабатываться по одной \
схеме - одушевленность/пол. В сомнительных случаях алгоритм принимает \
первые слова за прилагательные, а последнее - за \
существительное, например, \"злой смешной ковбой\" будет \
обработан правильно, а \"ковбой злой\" - нет.\r\n\r\n\
У большинства элементов управления имеются всплывающие \
подсказки.\r\n\
";

	ctrlRTADS_hlink.SetHyperLink( _T("http://rtads.h-type.com/") );
	ctrlGrAndreyEmail.SetHyperLink( _T("mailto:grandrey@mail.ru") );
	ctrlStasEmail.SetHyperLink( _T("mailto:stas_@fromru.com") );

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EDIT1, CAbout);
	DDX_Text(pDX, IDC_EDIT1, strAbout);
	DDX_Control(pDX, IDC_STATIC_RTADS_HLINK, ctrlRTADS_hlink);
	DDX_Control(pDX, IDC_STATIC_GRANDREY_MAIL, ctrlGrAndreyEmail);
	DDX_Control(pDX, IDC_STATIC_STAS_MAIL, ctrlStasEmail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneratorDlg dialog

CGeneratorDlg::CGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneratorDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CGeneratorDlg)
	strDEdit = _T("");
	strVEdit = _T("");
	strTEdit = _T("");
	strTEdit2 = _T("");
	strPEdit = _T("");
	iCombo2 = -1;
	strCombo1 = _T("");
	strClass = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGeneratorDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneratorDlg)
	DDX_Control(pDX, IDC_CHANGE_CLASS_LIST, ctrlChangeClassList);
	DDX_Control(pDX, IDC_CLASS, ctrlClass);
	DDX_Control(pDX, IDC_COMBO1, ctrlCombo1);
	DDX_Control(pDX, IDC_RESEDIT, ctrlResEdit);
	DDX_Control(pDX, IDC_REDIT, ctrlREdit);
	DDX_Control(pDX, IDC_IEDIT, ctrlIEdit);
	DDX_Control(pDX, IDC_CHISLO, ctrlChislo);
	DDX_Control(pDX, IDC_NOTSKLON, ctrlNotsklon);
	DDX_Control(pDX, IDC_PAUTO, ctrlPAuto);
	DDX_Control(pDX, IDC_DAUTO, ctrlDAuto);
	DDX_Control(pDX, IDC_VAUTO, ctrlVAuto);
	DDX_Control(pDX, IDC_TAUTO, ctrlTAuto);
	DDX_Control(pDX, IDC_TAUTO2, ctrlTAuto2);
	DDX_Control(pDX, IDC_RAUTO, ctrlRAuto);
	DDX_Text(pDX, IDC_DEDIT, strDEdit);
	DDX_Text(pDX, IDC_VEDIT, strVEdit);
	DDX_Text(pDX, IDC_TEDIT, strTEdit);
	DDX_Text(pDX, IDC_TEDIT2, strTEdit2);	
	DDX_Text(pDX, IDC_PEDIT, strPEdit);
	DDX_CBIndex(pDX, IDC_COMBO2, iCombo2);
	DDX_CBString(pDX, IDC_COMBO1, strCombo1);
	DDV_MaxChars(pDX, strCombo1, 2);
	DDX_CBString(pDX, IDC_CLASS, strClass);

	DDX_Text(pDX, IDC_IEDIT, strIEdit);
	DDX_Text(pDX, IDC_REDIT, strREdit);
	DDX_Text(pDX, IDC_RESEDIT, strResEdit);
	DDX_Control(pDX, IDC_ODUSH, ctrlOdush);
	DDX_Control(pDX, IDC_RADIO1, ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, ctrlRadio2);
	DDX_Control(pDX, IDC_RADIO3, ctrlRadio3);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT1, ctrlLexems);
	DDX_Control(pDX, IDC_BUTTON2, ctrlAddsynbtn);
	DDX_Control(pDX, IDC_BUTTON1, ctrlMakecodebtn);
	DDX_Control(pDX, IDC_EDIT2, ctrlAdjLex);
}

BEGIN_MESSAGE_MAP(CGeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CGeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_SETFOCUS(IDC_REDIT, OnSetfocusRedit)
	ON_EN_SETFOCUS(IDC_DEDIT, OnSetfocusDedit)
	ON_EN_SETFOCUS(IDC_PEDIT, OnSetfocusPedit)
	ON_EN_SETFOCUS(IDC_TEDIT, OnSetfocusTedit)
	ON_EN_SETFOCUS(IDC_VEDIT, OnSetfocusVedit)
	ON_BN_CLICKED(IDC_COPYTOCLIPBOARD, OnCopytoclipboard)
	ON_BN_CLICKED(IDC_CHISLO, OnBnClickedChislo)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_ODUSH, OnBnClickedOdush)
	ON_EN_CHANGE(IDC_IEDIT, OnEnChangeIEdit)
	ON_EN_CHANGE(IDC_REDIT, OnChangeRedit)
	ON_EN_CHANGE(IDC_DEDIT, OnChangeDedit)
	ON_EN_CHANGE(IDC_VEDIT, OnChangeVedit)
	ON_EN_CHANGE(IDC_TEDIT, OnChangeTedit)
	ON_EN_CHANGE(IDC_PEDIT, OnChangePedit)
	ON_BN_CLICKED(IDC_NOTSKLON, OnNotsklon)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_RAUTO, OnRauto)
	ON_BN_CLICKED(IDC_DAUTO, OnDauto)
	ON_BN_CLICKED(IDC_VAUTO, OnVauto)
	ON_BN_CLICKED(IDC_TAUTO, OnTauto)
	ON_BN_CLICKED(IDC_PAUTO, OnPauto)
	ON_BN_CLICKED(IDC_CHOOSEFONT, OnChooseFont)
	ON_CBN_SELCHANGE(IDC_CLASS, OnSelchangeClass)
	ON_CBN_KILLFOCUS(IDC_CLASS, OnKillfocusClass)
	ON_BN_CLICKED(IDC_CHANGE_CLASS_LIST, OnChangeClassList)
	ON_WM_GETMINMAXINFO() // контроль за размером окна
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio1)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotify) // tool tips
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneratorDlg message handlers

BOOL CGeneratorDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	EnableTrackingToolTips(TRUE);   // enable tool tips for view

	strREdit = "Родительный падеж";
	strDEdit = "Дательный падеж";
	strVEdit = "Винительный падеж";
	strTEdit = "Творительный падеж";
	strTEdit2 = "Дополнительный творительный падеж";
	strPEdit = "Предложный падеж";

	ctrlRAuto.SetCheck( TRUE );
	ctrlDAuto.SetCheck( TRUE );
	ctrlVAuto.SetCheck( TRUE );
	ctrlTAuto.SetCheck( TRUE );
	ctrlTAuto2.SetCheck( TRUE );
	ctrlPAuto.SetCheck( TRUE );

	ctrlRadio1.SetCheck( TRUE );

	strCombo1.Format( "%d", IniFile.Tabs.iNumberOfTabs ) ;
	iCombo1 = IniFile.Tabs.iNumberOfTabs;
	iCombo2 = IniFile.Tabs.iTabsOrSpaces;

	// ????????? ?????? ???????
	for ( int i = 0; i < IniFile.ChosenClasses.iNumberOfChosenClasses; i++ )
		ctrlClass.AddString( IniFile.ChosenClasses.strChosenClass[ i ] );
	strClass = IniFile.ChosenClasses.strDefaultClass;

	UpdateData( FALSE );

	bOdush = false;
	bChislo = true;
	iRod = 0;
	bOldWindowRectSaved = false;

	// ???????? ?????
	Font.CreateFontIndirect( &IniFile.Font.logfontLogFont );
	ctrlResEdit.SetFont( &Font );

	brushResEdit.CreateSysColorBrush( COLOR_WINDOW );

	HIChangeClassList = AfxGetApp()->LoadIcon( IDI_CHANGE_CLASS_LIST );
	ctrlChangeClassList.SetIcon( HIChangeClassList );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//TollTip notification handler
BOOL CGeneratorDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult) {
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA * pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW * pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	if ( pNMHDR->code == TTN_NEEDTEXTA && ( pTTTA->uFlags & TTF_IDISHWND ) ||
			pNMHDR->code == TTN_NEEDTEXTW && ( pTTTW->uFlags & TTF_IDISHWND ) ) {
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID( (HWND)nID );
	}

	switch ( nID ) {
		case IDC_IEDIT:
			strTipText = "Кто? Что?  (Именительный падеж)";
			break;
		case IDC_REDIT:
			strTipText = "Нет кого? чего?  (Родительный падеж)";
			break;
		case IDC_DEDIT:
			strTipText = "Рад кому? чему?  (Дательный падеж)";
			break;
		case IDC_VEDIT:
			strTipText = "Вижу кого? что?  (Винительный падеж)";
			break;
		case IDC_TEDIT:
			strTipText = "Любуюсь кем? чем?  (Творительный падеж)";
			break;
		case IDC_TEDIT2:
			strTipText = "Творительный падеж - альтернативная форма";
			break;
		case IDC_PEDIT:
			strTipText = "Говорю о ком? о чем?  (Предложный падеж)";
			break;
		case IDC_ODUSH:
			if ( bOdush )
				strTipText = "Объект является одушевленным";
			else
				strTipText = "Объект является неодушевленным";
			break;
		case IDC_CHISLO:
			if ( bChislo )
				strTipText = "Объект имеет единственное число";
			else
				strTipText = "Объект имеет множественное число";
			break;
		case IDC_ABOUT:
			strTipText = "Справка о программе";
			break;
		case IDC_RADIO1:
			strTipText = "Объект мужского рода";
			break;
		case IDC_RADIO2:
			strTipText = "Объект женского рода";
			break;
		case IDC_RADIO3:
			strTipText = "Объект среднего рода";
			break;
		case IDC_NOTSKLON:
			strTipText = "Не склонять слово, только создать код";
			break;
		case IDC_RAUTO:
			strTipText = "Разрешить автоматическое заполнение данной строки";
			break;
		case IDC_DAUTO:
			strTipText = "Разрешить автоматическое заполнение данной строки";
			break;
		case IDC_VAUTO:
			strTipText = "Разрешить автоматическое заполнение данной строки";
			break;
		case IDC_TAUTO:
			strTipText = "Разрешить автоматическое заполнение данной строки";
			break;
		case IDC_PAUTO:
			strTipText = "Разрешить автоматическое заполнение данной строки";
			break;
		case IDC_RESEDIT:
			strTipText = "Слова для поиска";
			break;
		case IDC_BUTTON1:
			strTipText = "Очистить список поиска";
			break;
		default:
			strTipText = "";
	}

	if ( pNMHDR->code == TTN_NEEDTEXTA )
		lstrcpyn( pTTTA->szText, strTipText, sizeof(pTTTA->szText) );
	else
		_mbstowcsz( pTTTW->szText, strTipText, sizeof(pTTTW->szText) );
	*pResult = 0;

	return TRUE;	// message was handled
}

void CGeneratorDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) { // контроль размеров окна
	CRect rectWindow; 
	GetWindowRect( &rectWindow );
	
	lpMMI->ptMinTrackSize.x = 500;//rectOldWindow.Width(); // максимальные/минимальные размеры окна
	lpMMI->ptMinTrackSize.y = 140;//rectOldWindow.Height(); // закомментированное почему-то глючит в Win32 Release (VC6)
	lpMMI->ptMaxTrackSize.x = 99999;
	lpMMI->ptMaxTrackSize.y = 99999;

	// соответственно увеличиваем IDC_RESEDIT
	CEdit * pResEdit;
	pResEdit = (CEdit *) GetDlgItem( IDC_RESEDIT );

	if ( pResEdit != NULL ) {
		UpdateData( TRUE );

		int iY = 0;
		int iX = 0;
		if ( IsZoomed() ) { // maximized
			iY = rectOldResEdit.Height() - rectOldWindow.Height() +
					GetSystemMetrics( SM_CYMAXIMIZED );
			iX = rectOldResEdit.Width() - rectOldWindow.Width() +
					GetSystemMetrics( SM_CXMAXIMIZED );
		} else if ( IsIconic() ) {
		} else {
			iY = rectOldResEdit.Height() - rectOldWindow.Height() +
					iHeightBeforeMax;
			iX = rectOldResEdit.Width() - rectOldWindow.Width() +
					iWidthBeforeMax;
			if ( rectWindow.Height() != GetSystemMetrics( SM_CYMAXIMIZED ) &&
					rectWindow.Width() != GetSystemMetrics( SM_CXMAXIMIZED ) && // если не возвратились из maximized
					rectWindow.left > 0 && rectWindow.top > 0 ) { // предотвращаем bug: min, restore, min, restore -- IDC_RESEDIT исчезает
				iHeightBeforeMax = rectWindow.Height();
				iWidthBeforeMax = rectWindow.Width();
			}
		}
		pResEdit->SetWindowPos( &wndTop, 0, 0, iX, iY,
				SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | 
				SWP_NOSENDCHANGING | SWP_NOZORDER );
		UpdateData( FALSE );
	}
} 

void CGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		EnableTrackingToolTips( FALSE );
		dlgAbout.DoModal();
		EnableTrackingToolTips( TRUE );
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CGeneratorDlg::OnDestroy() {
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGeneratorDlg::OnPaint() {
	if (IsIconic())	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		// запоминаем первоначальные размеры окна и IDC_RESEDIT
		if ( !bOldWindowRectSaved ) {
			bOldWindowRectSaved = true;
			GetWindowRect( &rectOldWindow );
			iHeightBeforeMax = rectOldWindow.Height();
			iWidthBeforeMax = rectOldWindow.Width();
			ctrlResEdit.GetRect( &rectOldResEdit );
			rectOldResEdit.bottom = rectOldWindow.Height() - 254 -
					2 * GetSystemMetrics( SM_CXBORDER ) -
					GetSystemMetrics( SM_CYSIZE ) -
					2 * GetSystemMetrics( SM_CXEDGE );
			rectOldResEdit.right = rectOldWindow.Width() - 6 -
					2 * GetSystemMetrics( SM_CXEDGE ) -
					2 * GetSystemMetrics( SM_CXBORDER );
			int iY = rectOldResEdit.Height();
			int iX = rectOldResEdit.Width();
			ctrlResEdit.SetWindowPos( &wndTop, 0, 0, iX, iY, SWP_DRAWFRAME |
					SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | 
					SWP_NOSENDCHANGING | SWP_NOZORDER );
		}
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGeneratorDlg::OnQueryDragIcon() {
	return (HCURSOR) m_hIcon;
}


void CGeneratorDlg::OnEnChangeIEdit() {

	string text,nslv,a;
	int mode, dopoln=false;

	UpdateData( TRUE );	

	// не даем ввести слишком много слов
	if ( StrCount( nslv ) > 15 ) {
		strIEdit = strIEdit.Left( strIEdit.GetLength() - 1 );
		UpdateData( FALSE );
		MessageBox( "Превышено максимально возможное количество слов", "Ошибка" );
		return;
	}

    text = strIEdit;

	// определяем свойства главного слова
	mode = (bChislo?SINGL:PLURAL);
	if (iRod==0) mode|=MALE;
	else if (iRod==1) mode|=FEMALE;
	else mode|=NEUTER;

	CString	*CStrs[6] = {&strREdit, &strDEdit, &strVEdit, &strTEdit, &strTEdit2, &strPEdit};
	CButton	*ctrlAutos[6] = {&ctrlRAuto, &ctrlDAuto, &ctrlVAuto, &ctrlTAuto, &ctrlTAuto2, &ctrlPAuto};

	// приступаем к обработке
	if ( ctrlNotsklon.GetCheck() ) 
	{
		for ( int cnt=0; cnt<6; cnt++ )	if (ctrlAutos[cnt]->GetCheck()) *(CStrs[cnt]) = strIEdit; 

	} else {
		for (int i=1; i <= StrCount( text ); i++ )
		{
			// добавляем пробел перед новым словом
			if (i>1) 
			{
				for ( int cnt=0; cnt<6; cnt++ )	if (ctrlAutos[cnt]->GetCheck()) *(CStrs[cnt])+=" "; 
			}
			else
			{
				for ( int cnt=0; cnt<6; cnt++ )	if (ctrlAutos[cnt]->GetCheck()) CStrs[cnt]->Empty();
			}

			// берем слово
			nslv = TakeWord( i, text );

			int placeForNoun = StrCount1( text );

			if (i==placeForNoun)
			{
				mode^=ADJ;
				mode|=NOUN;
			}
			else	mode|=ADJ;

			// при нахождении предлога, меняем режим
			
			// обработка режима после предлога
			if (i>placeForNoun)
			{	
				for ( int cnt=0; cnt<6; cnt++ )
					if (ctrlAutos[cnt]->GetCheck()) *(CStrs[cnt])+=nslv.c_str();
			}
			// обычный режим
			else
			{
				if ( ctrlRAuto.GetCheck() ) {
					strREdit +=  REP.TakePad( nslv, mode|GENITIVE).c_str();
				}
				if ( ctrlDAuto.GetCheck() ) {
					strDEdit += REP.TakePad( nslv, mode|DATIVE).c_str();
				}
				if ( ctrlVAuto.GetCheck() ) {
					strVEdit += REP.TakePad( nslv, mode|ACCUSATIVE).c_str();
				}
				if ( ctrlTAuto.GetCheck() ) {
					strTEdit += REP.TakePad( nslv, mode|INSTRUMENTAL).c_str();
				}
				if ( ctrlTAuto2.GetCheck() ) {
					strTEdit2 += REP.TakePad( nslv, mode|INSTRUMENTAL2).c_str();
				}
				if ( ctrlPAuto.GetCheck() ) {
					strPEdit += REP.TakePad( nslv, mode|PREPOSITIONAL).c_str();
				}
			}
		}
	}

	UpdateData( FALSE );
}

//---------------------------------------------------------------------------
void CGeneratorDlg::OnBnClickedRadio1() {
	UpdateData( TRUE );

	if ( ctrlRadio1.GetCheck() )
		iRod = 0;
	else if ( ctrlRadio2.GetCheck() )
		iRod = 1;
	else if ( ctrlRadio3.GetCheck() )
		iRod = 2;

	OnEnChangeIEdit();
}

//---------------------------------------------------------------------------
int CGeneratorDlg::GenDet( char * str ) {
	if ( strlen( str ) > 1 ) {
		switch ( str[ strlen( str ) - 1 ] ) {         // Автоопределение пола
			case 'й': 
				return 0;
			case 'о': 
				return 2;  
			case 'е': 
				return 2;  
			case 'ё': 
				return 2;  
		}
	}
		
	return iRod;
}

void CGeneratorDlg::OnBnClickedOdush() {
	EnableTrackingToolTips( FALSE );
	if ( bOdush ) {
		bOdush = false;
		ctrlOdush.SetWindowText( "Не&одушевленный" );
	} else {
		bOdush = true;
		ctrlOdush.SetWindowText( "&Одушевленный" );
	}
	OnEnChangeIEdit();
	EnableTrackingToolTips( TRUE );
}

void CGeneratorDlg::OnBnClickedChislo() {
	EnableTrackingToolTips( FALSE );
	if ( bChislo ) {
		bChislo = false;
		ctrlChislo.SetWindowText( "М&ножественный" );
	} else {
		bChislo = true;
		ctrlChislo.SetWindowText( "Еди&нственный" );
	}
	OnEnChangeIEdit();
	EnableTrackingToolTips( TRUE );
}

void CGeneratorDlg::OnSetfocusRedit() {
	if ( strREdit == "Родительный падеж" ) {
		strREdit = "";
		UpdateData( FALSE );
	}
}

void CGeneratorDlg::OnSetfocusDedit() {
	if ( strDEdit == "Дательный падеж" ) {
		strDEdit = "";
		UpdateData( FALSE );
	}
}

void CGeneratorDlg::OnSetfocusVedit() {
	if ( strVEdit == "Винительный падеж" ) {
		strVEdit = "";
		UpdateData( FALSE );
	}
}

void CGeneratorDlg::OnSetfocusTedit() {
	if ( strTEdit == "Творительный падеж" ) {
		strTEdit = "";
		UpdateData( FALSE );
	}
}

void CGeneratorDlg::OnSetfocusPedit() {
	if ( strPEdit == "Предложный падеж" ) {
		strPEdit = "";
		UpdateData( FALSE );
	}
}

void CAboutDlg::OnUpdateEdit1() {
	UpdateData( FALSE );
}


void CGeneratorDlg::OnAbout() {
	CAboutDlg dlgAbout;

	EnableTrackingToolTips( FALSE );
	dlgAbout.DoModal();
	EnableTrackingToolTips( TRUE );
}

void CGeneratorDlg::OnChangeRedit() {
	ctrlRAuto.SetCheck( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnChangeDedit() {
	ctrlDAuto.SetCheck( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnChangeVedit() {
	ctrlVAuto.SetCheck( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnChangeTedit() {
	ctrlTAuto.SetCheck( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnChangeTedit2() {
	ctrlTAuto.SetCheck( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnChangePedit() {
	ctrlPAuto.SetCheck( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnDcheck() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnTcheck() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnTcheck2() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnRcheck() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnRauto() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnDauto() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnVauto() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnTauto() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnPauto() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnNotsklon() {
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnBnClickedCheck1()
{
	OnEnChangeIEdit();
}

// готовим строки для поиска
/*
void CGeneratorDlg::OnBnClickedReady()
{
	// режим 1: задаем падежные формы в прямом виде
	CString	*CStrs[7] = {&strIEdit, &strREdit, &strDEdit, &strVEdit, &strTEdit, &strTEdit2, &strPEdit};
	vector<int> ignore;
	string result="";

	if (ctrlSoglas.GetCheck()) 
	{
		// ищем клонов
		for (int i=0; i<7; i++ )
			for (int j=i+1; j<7; j++ )
			{
				if ((*CStrs[i])==(*CStrs[j]))
					ignore.push_back(j);
			}
		
		for	(int i=0; i<7; i++)
		{
			bool found = false;

			// проверяем наличие клона
			for (int j=0; j<ignore.size(); j++)
			{
				if ((ignore[j])==i)	found = true;
			}

			// если нет клона - пишем
			if (!found && (*CStrs[i]).GetLength()!=0)	
			{
				if (result.size()>0) result+="|";
				result+=(*CStrs[i]);
			}
		}
			strResEdit+=result.c_str();
			strResEdit+="\r\n";
	}
	// режим №2
	else
	{
		vector<string> words;
		string str, tmpstr;

		//берем все слова всех падежей
		for (int i=0; i<7; i++ )	
		{
            str = (*CStrs[i]);
			for (int i=1; i <= StrCount( str ); i++ )
			{
				tmpstr = TakeWord( i, str );
				words.push_back( tmpstr );
			}
		}

		int count=0;
		while (count<words.size())
		{
			for (int j=count+1; j<words.size(); j++)
				if (!strcmp(words[count].c_str(),words[j].c_str())) 
			{
				vector<string>::iterator Iter;	int k;
				for ( Iter = words.begin(), k=0 ;  j != k ; Iter++, k++ ) {};
				words.erase(Iter);
				j--;
			}
			count++;
		}

		while (!words.empty())
		{
			int prevbaslen=0, i=1;
			bool noDelim=false;

			// сравниваем первое слово с остальными
			while (i<words.size())
			{
				int len1 = words[0].size();
				int len2 = words[i].size();
				string str = words[i];
				int minlen = (len1>len2)?i:0;
				int interlen = strcmpe(words[0],words[i]);

				if (interlen>1 && interlen>=(words[minlen].size()/2) && (!prevbaslen || interlen==prevbaslen))
				{

					if (!prevbaslen)
					{
						prevbaslen=interlen;
						strResEdit += words[0].substr(0,interlen).c_str();
						strResEdit += "(";
						if (words[0].size()!=interlen)
						strResEdit += words[0].substr(interlen,words[0].size()-interlen).c_str();
						else noDelim=true;
					}
                    if (noDelim) noDelim=false;
					else strResEdit += "|";
                    strResEdit += words[i].substr(prevbaslen,words[i].size()-prevbaslen).c_str();

					vector<string>::iterator Iter;	int j;
					for ( Iter = words.begin(), j=0 ;  j != i ; Iter++, j++ ) {};
					words.erase(Iter);
					i--;
				}
				i++;
			}

			// если ничего не нашли
			if (!prevbaslen)
				strResEdit += words[0].c_str();
			else strResEdit += ")";

			words.erase(words.begin());

			strResEdit += "\r\n";
		}
	}
	
	UpdateData( FALSE );
}
*/

void CGeneratorDlg::OnChooseFont() {
	CFont * curfont = ctrlResEdit.GetFont();
	LOGFONT curlf;
	curfont->GetLogFont( &curlf );
	CFontDialog dlg( &curlf );

	dlg.m_cf.rgbColors = IniFile.Font.FontColor;

	if ( dlg.DoModal() == IDOK ) {
		Font.DeleteObject();
		VERIFY( Font.CreateFontIndirect( &curlf ) );
		ctrlResEdit.SetFont( &Font );
		IniFile.Font.FontColor = dlg.GetColor();
	}
}


void CGeneratorDlg::OnEditchangeCombo1() {
	char str[20];
	
	UpdateData( TRUE );
	
	iCombo1 = atoi( strCombo1 );
	if ( iCombo1 < 0 )
		iCombo1	= 0;
	itoa( iCombo1, str, 10 );
	if ( strCombo1 != "" )
		strCombo1 = str;
	IniFile.Tabs.iNumberOfTabs = iCombo1;

	UpdateData( FALSE );
	OnEnChangeIEdit();
}


void CGeneratorDlg::OnSelchangeCombo1() {
	char str[20];

	UpdateData( TRUE );
	
	iCombo1 = ctrlCombo1.GetCurSel();
	itoa( iCombo1, str, 10 );
	strCombo1 = str;
	IniFile.Tabs.iNumberOfTabs = iCombo1;

	UpdateData( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnKillfocusCombo1() {
	char str[20];

	itoa( iCombo1, str, 10 );
	strCombo1 = str;
	IniFile.Tabs.iNumberOfTabs = iCombo1;

	UpdateData( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnSelchangeCombo2() {
	OnEnChangeIEdit();
	IniFile.Tabs.iTabsOrSpaces = iCombo2;
}


void CGeneratorDlg::OnSelchangeClass() {
	UpdateData( TRUE );

	int iIndex = ctrlClass.GetCurSel();

	if ( iIndex != -1 )
		ctrlClass.GetLBText( iIndex, strClass );

	UpdateData( FALSE );
	OnEnChangeIEdit();
}

void CGeneratorDlg::OnKillfocusClass() {
	CGeneratorDlg::OnSelchangeClass();
}

void CGeneratorDlg::OnChangeClassList() {
	CModClassListDlg dlgModClassList;

	EnableTrackingToolTips( FALSE );

	int nResponse = dlgModClassList.DoModal();
	if ( nResponse == IDOK ) {
		for ( int i = 0; ctrlClass.GetCount(); i++ )
			ctrlClass.DeleteString( 0 );

		for ( i = 0; i < IniFile.ChosenClasses.iNumberOfChosenClasses; i++ )
			ctrlClass.AddString( IniFile.ChosenClasses.strChosenClass[ i ] );

		UpdateData( FALSE );
	} else if ( nResponse == IDCANCEL ) {
	}

	EnableTrackingToolTips( TRUE );
}

HBRUSH CGeneratorDlg::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT nCtlColor ) {
	// установка цвета
	HBRUSH hbr = CDialog::OnCtlColor( pDC, pWnd, nCtlColor );
	
	switch ( pWnd->GetDlgCtrlID() ) {
		case IDC_RESEDIT:
			pDC->SetTextColor( IniFile.Font.FontColor );
			hbr = (HBRUSH)( brushResEdit.GetSafeHandle() );
		default:
			break;
	}
	return hbr;
}

void CGeneratorDlg::OnCopytoclipboard() {
	ctrlResEdit.SetSel( 0, -1, TRUE );
	ctrlResEdit.Copy();
	ctrlResEdit.SetSel( 0, 0, TRUE );
}


// Добавление лексем
void CGeneratorDlg::OnBnClickedButton2()
{
	CString	*CStrs[7] = {&strIEdit, &strREdit, &strDEdit, &strVEdit, &strTEdit, &strTEdit2, &strPEdit};

	vector<string> lexems;
	string str, tmpstr;

	//берем все слова всех падежей
	for (int i=0; i<7; i++ )	
	{
        str = (*CStrs[i]);
		int noun = StrCount1(str);

		tmpstr = TakeWord( noun, str );
		lexems.push_back( tmpstr );
	}   

	// ищем клонов
	for ( i=0; i<lexems.size(); i++ )
		for (int j=i+1; j<lexems.size(); j++ )
			if (lexems[i]==lexems[j])	lexems.erase(lexems.begin()+j);

	// выводим
	tmpstr="";
	for ( i=0; i<lexems.size(); i++ ) 
	{
		tmpstr+="\'";
		tmpstr+=lexems[i];
		tmpstr+="\' ";
	}
		ctrlLexems.SetWindowText(tmpstr.c_str());
	UpdateData(FALSE);

}


void CGeneratorDlg::OnBnClickedButton3()
{
	CString	*CStrs[7] = {&strIEdit, &strREdit, &strDEdit, &strVEdit, &strTEdit, &strTEdit2, &strPEdit};

	typedef vector<string> strvec;
	strvec lexems[6];
	string str, tmpstr;

	//берем все слова всех падежей
	for (int i=0; i<7; i++ )	
	{
        str = (*CStrs[i]);
		int strlen = StrCount(str);
		int noun = StrCount1(str);

		for (int j=1; j<=strlen; j++)
		{
			tmpstr = TakeWord( j, str );
			if (j>(noun+1))
				lexems[1].push_back( tmpstr );
			else
            if (j!=noun && j!=(noun+1))
			{
				if (i<5) lexems[i].push_back( tmpstr );		//Объединяем два творительных
				else lexems[i-1].push_back( tmpstr );
			}
		}
	}   

	// ищем клонов	
	for ( i=0; i<6; i++ )
		for (int j=0; j<lexems[i].size(); j++ )
			for (int k=j+1; k<lexems[i].size(); k++ )
				if (lexems[i][j]==lexems[i][k])	lexems[i].erase(lexems[i].begin()+k);

	for ( i=0; i<6; i++ )
		for (int j=i+1; j<6; j++ )
			for (int k=0; k<lexems[i].size(); k++ )
				for (int l=0; l<lexems[j].size(); l++ )
				if (lexems[i][k]==lexems[j][l])	lexems[j].erase(lexems[j].begin()+l); //TODO: приоритет флажков


	tmpstr="";
	for ( i=0; i<6; i++ )
	for (int j=0; j<lexems[i].size(); j++) 
	{
		tmpstr+="\'";
		tmpstr+=lexems[i][j];
		tmpstr+="\' ";
	}
		ctrlLexems.SetWindowText(tmpstr.c_str());

	UpdateData(FALSE);


}
