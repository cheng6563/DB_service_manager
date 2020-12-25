// DB_service_managerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DB_service_manager.h"
#include "DB_service_managerDlg.h"
#include "Winsvc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDB_service_managerDlg dialog

CDB_service_managerDlg::CDB_service_managerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDB_service_managerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDB_service_managerDlg)
	m_ShowAll = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDB_service_managerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDB_service_managerDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Check(pDX, IDC_SHOWALL, m_ShowAll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDB_service_managerDlg, CDialog)
	//{{AFX_MSG_MAP(CDB_service_managerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENUITEM_START, OnMenuitemStart)
	ON_COMMAND(ID_MENUITEM_STOP, OnMenuitemStop)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM_AUTO, OnMenuitemAuto)
	ON_COMMAND(ID_MENUITEM_MANAGE, OnMenuitemManage)
	ON_COMMAND(ID_MENUITEM_DISABLED, OnMenuitemDisabled)
	ON_BN_CLICKED(IDC_SHOWALL, OnShowAll)
	ON_BN_CLICKED(IDC_REFILL, OnReFill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDB_service_managerDlg message handlers

BOOL CDB_service_managerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	DWORD dwStyle = ::GetWindowLong(m_list.m_hWnd, GWL_STYLE); 
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	SetWindowLong(m_list.m_hWnd, GWL_STYLE,dwStyle|LVS_REPORT|LVS_NOLABELWRAP|LVS_SHOWSELALWAYS|LVS_SINGLESEL);

	DWORD styles =LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, styles,styles );

	m_list.InsertColumn(0,"服务名称",LVCFMT_LEFT,234,-1);
	m_list.InsertColumn(1,"显示名称",LVCFMT_LEFT,234,-1);
	m_list.InsertColumn(2,"启动状态",LVCFMT_CENTER,70,-1);
	m_list.InsertColumn(3,"启动类别",LVCFMT_CENTER,70,-1);
	
	
	FillList();

	SetTimer(ID_TIMER,2000,NULL);

	this->SetDlgItemText(IDC_AUTOREFILLTIME,"2");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDB_service_managerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDB_service_managerDlg::OnPaint() 
{
	if (IsIconic())
	{
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
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDB_service_managerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDB_service_managerDlg::FillList()
{
	m_list.SetRedraw(FALSE);
	m_list.DeleteAllItems();

	LPQUERY_SERVICE_CONFIG ServicesInfo = NULL;
	LPENUM_SERVICE_STATUS lpServices = NULL; 

	DWORD nSize = 0; 
	DWORD n; 
	DWORD nResumeHandle = 0; 

	SC_HANDLE schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	lpServices = (LPENUM_SERVICE_STATUS) LocalAlloc(LPTR, 64*1024);
	EnumServicesStatus(schSCManager,
					   SERVICE_WIN32, 
					   SERVICE_STATE_ALL,
					   (LPENUM_SERVICE_STATUS) lpServices, 
					   64 * 1024, 
					   &nSize, 
					   &n, 
					   &nResumeHandle);

	for (unsigned long i = 0; i < n; i++)  
	{ 
		SC_HANDLE service = NULL;
		DWORD nResumeHandle = 0; 
		
		CString serName=lpServices[i].lpDisplayName;
		if(0==serName.Left(6).Compare("Oracle")||0==serName.Left(3).Compare("SQL")||m_ShowAll||0==serName.Left(5).Compare("MySQL")||0==serName.Left(5).Compare("mysql"))
		{
			service=OpenService(schSCManager,lpServices[i].lpServiceName,SERVICE_ALL_ACCESS);
			ServicesInfo = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 4*1024);
			int nListID=m_list.InsertItem(0,lpServices[i].lpServiceName);
			QueryServiceConfig(service,ServicesInfo,4*1024,&nResumeHandle);
			m_list.SetItemText(nListID,1,serName);

			switch(lpServices[i].ServiceStatus.dwCurrentState)
			{
			case SERVICE_RUNNING:
				m_list.SetItemText(nListID,2,"已启动");
				break;
			case SERVICE_STOPPED:
				m_list.SetItemText(nListID,2,"已停止");
				break;
			default:
				m_list.SetItemText(nListID,2,"操作中");
			}
			
			switch(ServicesInfo->dwStartType)
			{
			case SERVICE_AUTO_START:
				m_list.SetItemText(nListID,3,"自动");
				break;
			case SERVICE_DEMAND_START:
				m_list.SetItemText(nListID,3,"手动");
				break;
			case SERVICE_DISABLED:
				m_list.SetItemText(nListID,3,"已禁用");
			}
		}
	}
	m_list.SetRedraw(TRUE); 
	m_list.Invalidate(); 
	UpdateData(FALSE);
	m_list.UpdateWindow();
}

void CDB_service_managerDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (pWnd==&m_list&&m_list.GetSelectedCount()>0)
		{
		CMenu popMenu;
		VERIFY(popMenu.LoadMenu(IDR_RM));
		CMenu *p=popMenu.GetSubMenu(0);
		ASSERT(p!=NULL);
		p->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,AfxGetMainWnd());
	}
}

void CDB_service_managerDlg::OnMenuitemStart() 
{
	EnablePriv();
	char SerName[100]="\0";
	m_list.GetItemText(m_list.GetSelectionMark(),0,SerName,100);
	if (SerName[0]=='\0')
	{
		return;
	}

	SC_HANDLE scm;
    SC_HANDLE service;
    SERVICE_STATUS status;
	
	
	scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	
    service=OpenService(scm,SerName,SERVICE_ALL_ACCESS);
	
    BOOL isSuccess=QueryServiceStatus(service,&status);

    if ( status.dwCurrentState==SERVICE_STOPPED )
	{
		isSuccess=::StartService(service,NULL,NULL);
		
		if (!isSuccess)
		{
			Msg("启动服务失败！");
		}
	}
	else
	{
		Msg("操作失败!");
	}
	
	CloseServiceHandle(service );
	CloseServiceHandle(scm);

	OnReFill();
}



BOOL CDB_service_managerDlg::EnablePriv()
{
	HANDLE hToken;
	if ( OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken) )
	{
		TOKEN_PRIVILEGES tkp;
		
		LookupPrivilegeValue( NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid );//修改进程权限
		tkp.PrivilegeCount=1;
		tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges( hToken,FALSE,&tkp,sizeof tkp,NULL,NULL );//通知系统修改进程权限
		
		return( (GetLastError()==ERROR_SUCCESS) );
	}
	return FALSE;
}

void CDB_service_managerDlg::OnMenuitemStop() 
{	
	EnablePriv();
	char SerName[100]="\0";
	m_list.GetItemText(m_list.GetSelectionMark(),0,SerName,100);
	if (SerName[0]=='\0')
	{
		return;
	}
	
	SC_HANDLE scm;
    SC_HANDLE service;
    SERVICE_STATUS status;
	
	
	scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	
    service=OpenService(scm,SerName,SERVICE_ALL_ACCESS);
	
    BOOL isSuccess=QueryServiceStatus(service,&status);
	
    if ( status.dwCurrentState==SERVICE_RUNNING )
	{
		isSuccess=::ControlService(service,SERVICE_CONTROL_STOP,&status);
		
		if (!isSuccess)
		{
			Msg("停止服务失败！");
		}
	}
	else
	{
		Msg("操作失败!");
	}
	
	CloseServiceHandle(service );
	CloseServiceHandle(scm);
	
	OnReFill();
}

void CDB_service_managerDlg::OnTimer(UINT nIDEvent) 
{
	if (!m_ShowAll)
	{
		OnReFill();
	}
	CDialog::OnTimer(nIDEvent);
}

void CDB_service_managerDlg::OnMenuitemAuto() 
{
	EnablePriv();
	char SerName[100]="\0";
	m_list.GetItemText(m_list.GetSelectionMark(),0,SerName,100);
	if (SerName[0]=='\0')
	{
		return;
	}
	SC_HANDLE scm;
    SC_HANDLE service;
	scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
    service=OpenService(scm,SerName,SERVICE_ALL_ACCESS);
    SC_LOCK sclLock; 
    DWORD  dwStartType; 
    sclLock = LockServiceDatabase(scm); 
    dwStartType = SERVICE_AUTO_START;
    if (! ChangeServiceConfig( 
        service,        // handle of service 
        SERVICE_NO_CHANGE, // service type: no change 
        dwStartType,       // change service start type 
        SERVICE_NO_CHANGE, // error control: no change 
        NULL,              // binary path: no change 
        NULL,              // load order group: no change 
        NULL,              // tag ID: no change 
        NULL,              // dependencies: no change 
        NULL,              // account name: no change
		NULL,				// password: no change
		NULL))				//displayname 
    {
        Msg("设置失败!"); 
    }
    UnlockServiceDatabase(sclLock); 
    CloseServiceHandle(service); 
	OnReFill();
}

void CDB_service_managerDlg::OnMenuitemManage() 
{
	EnablePriv();
	char SerName[100]="\0";
	m_list.GetItemText(m_list.GetSelectionMark(),0,SerName,100);
	if (SerName[0]=='\0')
	{
		return;
	}
	SC_HANDLE scm;
    SC_HANDLE service;
	scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
    service=OpenService(scm,SerName,SERVICE_ALL_ACCESS);
    SC_LOCK sclLock; 
    DWORD  dwStartType; 
    sclLock = LockServiceDatabase(scm); 
    dwStartType = SERVICE_DEMAND_START;
    if (! ChangeServiceConfig( 
        service,        // handle of service 
        SERVICE_NO_CHANGE, // service type: no change 
        dwStartType,       // change service start type 
        SERVICE_NO_CHANGE, // error control: no change 
        NULL,              // binary path: no change 
        NULL,              // load order group: no change 
        NULL,              // tag ID: no change 
        NULL,              // dependencies: no change 
        NULL,              // account name: no change
		NULL,				// password: no change
		NULL))				//displayname 
    {
        Msg("设置失败!"); 
    }
    UnlockServiceDatabase(sclLock); 
    CloseServiceHandle(service);
	OnReFill();
}

void CDB_service_managerDlg::OnMenuitemDisabled() 
{
	EnablePriv();
	char SerName[100]="\0";
	m_list.GetItemText(m_list.GetSelectionMark(),0,SerName,100);
	if (SerName[0]=='\0')
	{
		return;
	}
	SC_HANDLE scm;
    SC_HANDLE service;
	scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
    service=OpenService(scm,SerName,SERVICE_ALL_ACCESS);
    DWORD  dwStartType; 
	SC_LOCK sclLock; 
    sclLock=LockServiceDatabase(scm);
    dwStartType = SERVICE_DISABLED;
    if (! ChangeServiceConfig( 
        service,        // handle of service 
        SERVICE_NO_CHANGE, // service type: no change 
        dwStartType,       // change service start type 
        SERVICE_NO_CHANGE, // error control: no change 
        NULL,              // binary path: no change 
        NULL,              // load order group: no change 
        NULL,              // tag ID: no change 
        NULL,              // dependencies: no change 
        NULL,              // account name: no change
		NULL,				// password: no change
		NULL))				//displayname 
    {
        Msg("设置失败!"); 
    }
    UnlockServiceDatabase(sclLock); 
    CloseServiceHandle(service);
	OnReFill();
}

void CDB_service_managerDlg::Msg(LPCTSTR info)
{
	MessageBox(info,"提示",MB_OK);
}

void CDB_service_managerDlg::OnShowAll() 
{
	UpdateData();
	FillList();
}

void CDB_service_managerDlg::OnReFill() 
{
	BOOL Selected=(m_list.GetSelectedCount()>0);
	int SelectID=-1;
	if(Selected)
	{
		SelectID=m_list.GetSelectionMark();
	}
	FillList();
	if(Selected){
		m_list.SetSelectionMark(SelectID);
		m_list.SetItemState(SelectID,LVIS_SELECTED,LVIS_SELECTED);
		m_list.EnsureVisible(SelectID, FALSE);
	}
}


void CDB_service_managerDlg::OnOutofmemoryAutoReFillTimeAdd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
