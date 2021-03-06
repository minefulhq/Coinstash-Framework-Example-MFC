
// Coinstash-Framework-MFCDlg.h : header file
//

#pragma once


// CCoinstashFrameworkMFCDlg dialog
class CCoinstashFrameworkMFCDlg : public CDialogEx
{
// Construction
public:
	CCoinstashFrameworkMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COINSTASHFRAMEWORKMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cpulimitCombo;
	CComboBox m_portCombo;
	CComboBox m_currencyCombo;
	CComboBox m_minerCombo;
	afx_msg void onStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_hashrate;
	afx_msg void OnDestroy();
	CString m_cpuusage;
	CButton m_controlButton;
};
