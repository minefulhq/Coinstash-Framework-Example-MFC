
// Coinstash-Framework-MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Coinstash-Framework-MFC.h"
#include "Coinstash-Framework-MFCDlg.h"
#include "afxdialogex.h"
#include "Header.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Coinstash_Windows;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCoinstashFrameworkMFCDlg dialog



CCoinstashFrameworkMFCDlg::CCoinstashFrameworkMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COINSTASHFRAMEWORKMFC_DIALOG, pParent)
	, m_hashrate(_T(""))
	, m_cpuusage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoinstashFrameworkMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CPULIMIT_COMBO, m_cpulimitCombo);
	DDX_Control(pDX, IDC_PORT_COMBO, m_portCombo);
	DDX_Control(pDX, IDC_CURRENCY_COMBO, m_currencyCombo);
	DDX_Control(pDX, IDC_MINER_COMBO, m_minerCombo);
	DDX_Text(pDX, IDC_HASH_LABEL, m_hashrate);
	DDX_Text(pDX, IDC_CPU_LABEL, m_cpuusage);
	DDX_Control(pDX, IDC_CONTROL_BUTTON, m_controlButton);
}

BEGIN_MESSAGE_MAP(CCoinstashFrameworkMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONTROL_BUTTON, &CCoinstashFrameworkMFCDlg::onStart)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCoinstashFrameworkMFCDlg message handlers

BOOL CCoinstashFrameworkMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_portCombo.AddString(CString("3333"));
	m_portCombo.AddString(CString("5555"));
	m_portCombo.AddString(CString("7777"));
	m_portCombo.SetCurSel(0);

	m_currencyCombo.AddString(CString("Monero7"));
	m_currencyCombo.AddString(CString("Graft"));
	m_currencyCombo.AddString(CString("Electroneum"));
	m_currencyCombo.AddString(CString("Sumokoin"));
	m_currencyCombo.AddString(CString("Karbo"));
	m_currencyCombo.AddString(CString("Intense"));
	m_currencyCombo.SetCurSel(0);

	m_minerCombo.AddString(CString("xmr-stak"));
	m_minerCombo.AddString(CString("xmrig"));
	m_minerCombo.AddString(CString("cn-cpu-miner"));
	m_minerCombo.SetCurSel(0);

	for (int i = 0; i <= 100; i++)
		m_cpulimitCombo.AddString(CString(i.ToString()));
	m_cpulimitCombo.SetCurSel(50);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCoinstashFrameworkMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCoinstashFrameworkMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCoinstashFrameworkMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCoinstashFrameworkMFCDlg::onStart()
{
	// TODO: Add your control notification handler code here
	if (!Coinstash::currentMinerStatus())                // Coinstash isn't working
	{
		if (m_minerCombo.GetCurSel() == 0)
		{
			Coinstash::setMinerType(Coinstash::MinerType::XMRSTAK);
		}
		else if (m_minerCombo.GetCurSel() == 1)
		{
			Coinstash::setMinerType(Coinstash::MinerType::XMRIG);
		}
		else
		{
			Coinstash::setMinerType(Coinstash::MinerType::CNCPUMINER);
		}

		Coinstash::setApplicationInfo(UID, SECRET);
		Coinstash::setCPULimit(m_cpulimitCombo.GetCurSel());

		CString port;
		m_portCombo.GetLBText(m_portCombo.GetCurSel(), port);

		CString currency;
		m_currencyCombo.GetLBText(m_currencyCombo.GetCurSel(), currency);


		Coinstash::startMining(
			_ttoi(port),               // port number
			"x",                                        // password
			SystemInfo::logicalCores() / 2,              // number of cores
			"always",                                     // slow memory option
			gcnew System::String(currency),                    // currency
			"none",                                     // gpu mode
			AUTHCODE                        // authorization code
		);

		m_controlButton.SetWindowTextW(CString("Stop"));

		SetTimer(1, 1000, NULL);
	}
	else
	{
		m_controlButton.SetWindowTextW(CString("Start"));

		Coinstash::stopMining();
	}
}


void CCoinstashFrameworkMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_hashrate = CString(Coinstash::getHashRate().ToString()) + CString(" Hash/S\n") + 
		CString(Coinstash::getAccepted().ToString());
	m_cpuusage = CString(SystemInfo::cpuUsage().ToString()) + CString( " %");
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CCoinstashFrameworkMFCDlg::OnDestroy()
{
	Coinstash::stopMining();
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}
