// DB_service_managerDlg.h : header file
//

#if !defined(AFX_DB_SERVICE_MANAGERDLG_H__FB537038_AD9D_480C_B2C4_AA20138926CB__INCLUDED_)
#define AFX_DB_SERVICE_MANAGERDLG_H__FB537038_AD9D_480C_B2C4_AA20138926CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDB_service_managerDlg dialog

class CDB_service_managerDlg : public CDialog
{
// Construction
public:
	CDB_service_managerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDB_service_managerDlg)
	enum { IDD = IDD_DB_SERVICE_MANAGER_DIALOG };
	CListCtrl	m_list;
	BOOL	m_ShowAll;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDB_service_managerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDB_service_managerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuitemStart();
	afx_msg void OnMenuitemStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuitemAuto();
	afx_msg void OnMenuitemManage();
	afx_msg void OnMenuitemDisabled();
	afx_msg void OnShowAll();
	afx_msg void OnReFill();
	afx_msg void OnOutofmemoryAutoReFillTimeAdd(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strUsingService;
	void Msg(LPCTSTR);
	BOOL EnablePriv();
	void FillList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB_SERVICE_MANAGERDLG_H__FB537038_AD9D_480C_B2C4_AA20138926CB__INCLUDED_)
