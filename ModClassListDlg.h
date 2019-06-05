#if !defined(AFX_MODCLASSLISTDLG_H__B6036A79_E2E8_4792_B0DA_030006BF025C__INCLUDED_)
#define AFX_MODCLASSLISTDLG_H__B6036A79_E2E8_4792_B0DA_030006BF025C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModClassListDlg.h : header file
//

extern structIniFile IniFile;

/////////////////////////////////////////////////////////////////////////////
// CModClassListDlg dialog

class CModClassListDlg : public CDialog {
// Construction
public:
	CModClassListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModClassListDlg)
	enum { IDD = IDD_MOD_CLASS_LIST };
	CButton	CAddcustom;
	CListBox	CVibran;
	CListBox	CDostup;
	CString	strEditaddcustom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModClassListDlg)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModClassListDlg)
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnEnChangeEditaddcustom();
	afx_msg void OnBnClickedAddcustom();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CModClassListDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	bool bRunFirstTime;
    void SortList( CListBox * pCListBox );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODCLASSLISTDLG_H__B6036A79_E2E8_4792_B0DA_030006BF025C__INCLUDED_)
