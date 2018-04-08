// NetProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetProject.h"
#include "NetProjectDlg.h"

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
// CNetProjectDlg dialog

CNetProjectDlg::CNetProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetProjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetProjectDlg)
	m_port = 0;
	m_IP = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetProjectDlg)
	DDX_Control(pDX, IDC_EDIT_SEND, m_info);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, m_name);
	DDX_Control(pDX, IDC_LIST_RECEIVE, m_list);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// 接收来自服务器的消息
void CNetProjectDlg::receiveData(){

	char buffer[1024];
	int num = recv(m_client,buffer,1024,0);
	buffer[num] = 0;
	m_list.AddString(buffer);

}

BOOL CNetProjectDlg::PreTranslateMessage(MSG* pMsg){
	if(pMsg->message == 1000){
		receiveData();
		return CDialog::PreTranslateMessage(pMsg);
	}else{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

BEGIN_MESSAGE_MAP(CNetProjectDlg, CDialog)
	//{{AFX_MSG_MAP(CNetProjectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnClickedConnect)
	ON_BN_CLICKED(ID_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetProjectDlg message handlers

BOOL CNetProjectDlg::OnInitDialog()
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
	m_client = socket(AF_INET,SOCK_DGRAM,0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetProjectDlg::OnPaint() 
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
HCURSOR CNetProjectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetProjectDlg::OnClickedConnect() 
{
	// TODO: Add your control notification handler code here
	if(m_client == NULL){
		m_client  = socket(AF_INET,SOCK_DGRAM,0);
	}
	sockaddr_in serveraddr;
	UpdateData(true);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(m_port);
	serveraddr.sin_addr.S_un.S_addr = inet_addr(m_IP);
	if(connect(m_client,(sockaddr*)&serveraddr,sizeof(serveraddr))!=0){
		MessageBox("link error");
		return;
	}else{
		MessageBox("link successfully");
	}
	WSAAsyncSelect(m_client,m_hWnd,1000,FD_READ);
	CString str,info;
	m_name.GetWindowText(str);
	info.Format("%s---->%s",str,"进入聊天室");
	int i=send(m_client,info.GetBuffer(0),info.GetLength(),0);

	
}
 

 

void CNetProjectDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
		CString str,name,info;
	m_name.GetWindowText(name);
	m_info.GetWindowText(str);
	if(!name.IsEmpty()&&!str.IsEmpty()){
		info.Format("%s say:%s",name,str);
		int i = send(m_client,info.GetBuffer(0),info.GetLength(),0);
	}
}

void CNetProjectDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	closesocket(m_client);

	m_client = NULL;
}
