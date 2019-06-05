// GeneratorDlg.h : header file
//

#if !defined(AFX_GENERATORDLG_H__D0E2C66D_FBF3_4A58_B2F7_835711AD7223__INCLUDED_)
#define AFX_GENERATORDLG_H__D0E2C66D_FBF3_4A58_B2F7_835711AD7223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined HLINK_NOOLE
#define HLINK_NOOLE
#endif

#include "greta/regexpr2.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CGeneratorDlg dialog

class CGeneratorDlg : public CDialog {
// Construction
public:
	CGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneratorDlg)
	enum { IDD = IDD_GENERATOR_DIALOG };
	CButton	ctrlChangeClassList;
	CComboBox	ctrlClass;
	CComboBox	ctrlCombo1;
	CEdit	ctrlResEdit;
	CEdit	ctrlREdit;
	CEdit	ctrlIEdit;
	CButton	ctrlChislo;
	CButton	ctrlNotsklon;
	CButton	ctrlPAuto;
	CButton	ctrlDAuto;
	CButton	ctrlVAuto;
	CButton	ctrlTAuto;
	CButton ctrlTAuto2;
	CButton	ctrlRAuto;
	CString	strDEdit;
	CString	strTEdit;
	CString	strVEdit;
	CString	strTEdit2;
	CString	strPEdit;
	CString strIEdit;
	CString strREdit;
	CString	strCombo1;
	CString strResEdit;
	int		iCombo2;
	CString	strClass;
	CButton ctrlOdush;
	CButton ctrlRadio1;
	CButton ctrlRadio2;
	CButton ctrlRadio3;	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON HIChangeClassList;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetfocusRedit();
	afx_msg void OnSetfocusDedit();
	afx_msg void OnSetfocusPedit();
	afx_msg void OnSetfocusTedit();
	afx_msg void OnSetfocusVedit();
	afx_msg void OnCopytoclipboard();
	afx_msg void OnBnClickedChislo();
	afx_msg void OnAbout();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedOdush();
	afx_msg void OnEnChangeIEdit();
	afx_msg void OnChangeRedit();
	afx_msg void OnChangeDedit();
	afx_msg void OnChangeVedit();
	afx_msg void OnChangeTedit();
	afx_msg void OnChangeTedit2();
	afx_msg void OnChangePedit();
	afx_msg void OnDcheck();
	afx_msg void OnTcheck();
	afx_msg void OnRcheck();
	afx_msg void OnNotsklon();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnSelchangeCombo2();

	afx_msg void OnRauto();
	afx_msg void OnDauto();
	afx_msg void OnVauto();
	afx_msg void OnTauto();
	afx_msg void OnPauto();
	afx_msg void OnChooseFont();
	afx_msg void OnSelchangeClass();
	afx_msg void OnKillfocusClass();
	afx_msg void OnChangeClassList();


	afx_msg void OnTcheck2();
	//}}AFX_MSG
	void OnGetMinMaxInfo( MINMAXINFO FAR * lpMMI );
	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	HBRUSH CGeneratorDlg::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT nCtlColor );

	bool bOldWindowRectSaved;
	CRect rectOldWindow;
	CRect rectOldResEdit;
	int iHeightBeforeMax;
	int iWidthBeforeMax;
	CBrush brushResEdit;
	DECLARE_MESSAGE_MAP()

public:
	int iCombo1;
	bool bChislo;
	bool bOdush;
	static int GenDet( char * str );
	void AddTabs( char * str, int iTabs, int iTabsOrSpaces );


	afx_msg void OnBnClickedCase();
	afx_msg void OnBnClickedCheck1();
	CEdit ctrlLexems;
	CButton ctrlAddsynbtn;
	CButton ctrlMakecodebtn;
	afx_msg void OnBnClickedButton2();
	CEdit ctrlAdjLex;
	afx_msg void OnBnClickedButton3();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATORDLG_H__D0E2C66D_FBF3_4A58_B2F7_835711AD7223__INCLUDED_)
