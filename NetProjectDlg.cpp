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
	m_remote = _T("");
	m_EditRxData = _T("");
	m_edit_send = _T("");
	m_showhex = FALSE;
	m_sendhex = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetProjectDlg)
	DDX_Control(pDX, IDC_COMBO_NUMBIT, m_portnumbit);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_portbaud);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_portstopbit);
	DDX_Control(pDX, IDC_COMBO_CHECK, m_portcheck);
	DDX_Control(pDX, IDC_COMBO_PORTNUM, m_serial_port_num);
	DDX_Control(pDX, IDC_BUTTON_SERIAL_PORT, m_serial_port);
	DDX_Control(pDX, IDOK, m_connect);
	DDX_Control(pDX, IDC_EDIT_REMOTE, m_remote_editor);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type);
	DDX_Control(pDX, IDC_EDIT_SEND, m_info);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, m_name);
	DDX_Control(pDX, IDC_LIST_RECEIVE, m_list);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
	DDX_Text(pDX, IDC_EDIT_REMOTE, m_remote);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm1);
	DDX_LBString(pDX, IDC_LIST_RECEIVE, m_EditRxData);
	DDX_Text(pDX, IDC_EDIT_SEND, m_edit_send);
	DDX_Check(pDX, IDC_CHECK_SHOW, m_showhex);
	DDX_Check(pDX, IDC_CHECK_SEND, m_sendhex);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// �������Է���������Ϣ
void CNetProjectDlg::receiveData(){
 
	char buffer[1024];
	memset(buffer,'\0',sizeof(buffer));
	int num = recv(m_client,buffer,1024,0);
	if(num>=0){
	    buffer[num] = 0;
		UpdateData(true);
    		if(m_showhex){
				CString result;
				int i=0;
				while(buffer[i]!='\0'){
				    CString temp;
				    temp.Format("%02X ",(BYTE)buffer[i]);
					result+=temp;
					i++;
				}
				m_list.AddString(result);
			}else
		        m_list.AddString(buffer);
	}
}

void CNetProjectDlg::handleData(){
	sockaddr_in serveraddr;
	char buffer[1024];
	memset(buffer,'\0',sizeof(buffer));
	int len = sizeof(serveraddr);
	if(m_client == 0){
	    m_client = accept(m_server,(sockaddr*)&serveraddr,&len);
	}else{
		int num = recv(m_client,buffer,1024,0);
		UpdateData(true);
		if(num>=0){
		    buffer[num] = 0;
			if(m_showhex){
				CString result;
				int i=0;
				while(buffer[i]!='\0'){
				    CString temp;
				    temp.Format("%02X ",(BYTE)buffer[i]);
					result+=temp;
					i++;
				}
				m_list.AddString(result);
			}else
		        m_list.AddString(buffer);
		}
	}

}

BOOL CNetProjectDlg::PreTranslateMessage(MSG* pMsg){
	if(pMsg->message == 1000){
		receiveData();
		return CDialog::PreTranslateMessage(pMsg);
	}else if(pMsg->message == 20001){
		handleData();
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
	ON_BN_CLICKED(IDC_BUTTON_SERIAL_PORT, OnClickedSerialPort)
	ON_BN_CLICKED(IDC_BUTTON2, OnClearSendArea)
	ON_BN_CLICKED(IDC_BUTTON3, OnClearReceiveArea)
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
	m_client = NULL;
    m_server = NULL;
	UpdateData(true);
	m_IP = "127.0.0.1";
	m_port = 8080;
	UpdateData(false);
	//��������
	m_type.InsertString(0 ,_T("TCP client") );
    m_type.InsertString(1 ,_T("TCP server") );
    m_type.InsertString(2 ,_T("UDP") );
	m_type.SetCurSel(0); 

	//���ڶ˿ں�
	m_serial_port_num.InsertString(0 ,_T("COM1") );
	m_serial_port_num.InsertString(1 ,_T("COM2") );
	m_serial_port_num.InsertString(2 ,_T("COM3") );
	m_serial_port_num.InsertString(3 ,_T("COM4") );
	m_serial_port_num.SetCurSel(0); 

	//������
	m_portbaud.InsertString(0 ,_T("300") );
	m_portbaud.InsertString(1 ,_T("600") );
	m_portbaud.InsertString(2 ,_T("1200") );
	m_portbaud.InsertString(3 ,_T("2400") );
	m_portbaud.InsertString(4 ,_T("4800") );
	m_portbaud.InsertString(5 ,_T("9600") );
	m_portbaud.InsertString(6 ,_T("19200") );
	m_portbaud.InsertString(7 ,_T("38400") );
	m_portbaud.SetCurSel(5); 

	//У��λ
	m_portcheck.InsertString(0 ,_T("n") );
	m_portcheck.InsertString(1 ,_T("o") );
	m_portcheck.InsertString(2 ,_T("e") );
	m_portcheck.SetCurSel(0); 

	//����λ
	m_portnumbit.InsertString(0 ,_T("8") );
	m_portnumbit.InsertString(1 ,_T("7") );
	m_portnumbit.InsertString(2 ,_T("6") );
	m_portnumbit.SetCurSel(0); 

	//ֹͣλ
	m_portstopbit.InsertString(0 ,_T("1") );
	m_portstopbit.InsertString(1 ,_T("2") );
	m_portstopbit.SetCurSel(0); 

	m_remote_editor.EnableWindow(false);
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
	//tcp�ͻ���
	CString tmpButton;
	m_connect.GetWindowText(tmpButton);
	if(tmpButton == "����"){
		m_connect.SetWindowText(_T("�ر�����"));
		if(m_type.GetCurSel() == 0){
		    m_remote_editor.EnableWindow(false);
	        if(m_client == NULL){
		        m_client =  socket(AF_INET,SOCK_STREAM,0);
			}
        	sockaddr_in serveraddr;
        	UpdateData(true);
    	    serveraddr.sin_family = AF_INET;
        	serveraddr.sin_port = htons(m_port);
    	    serveraddr.sin_addr.S_un.S_addr = inet_addr(m_IP);
    	    if(connect(m_client,(sockaddr*)&serveraddr,sizeof(serveraddr))!=0){
	        	MessageBox("link error");
			    m_connect.SetWindowText(_T("����"));
	    	    return;
			}else{
	    	     MessageBox("link successfully");
			}
			m_serial_port.EnableWindow(false);

        	WSAAsyncSelect(m_client,m_hWnd,1000,FD_READ);

     
		}else if(m_type.GetCurSel() == 1){//tcp�����
	    	m_remote_editor.EnableWindow(false);
			m_server = socket(AF_INET,SOCK_STREAM,0);
        	WSAAsyncSelect(m_server,m_hWnd,20001,FD_WRITE|FD_READ|FD_ACCEPT);
        	m_client = 0;
			sockaddr_in serveraddr;
        	serveraddr.sin_family = AF_INET;
			serveraddr.sin_addr.S_un.S_addr = inet_addr(m_IP);
	        UpdateData(true);
	        serveraddr.sin_port = htons(m_port);
			m_serial_port.EnableWindow(false);
        	if(bind(m_server,(sockaddr*)&serveraddr,sizeof(serveraddr))){
	        	MessageBox("��ʧ��");
	        	return;
			}
			int len = sizeof(serveraddr);
        	listen(m_server,5);
		 

		}else{//udp
		    UpdateData(true);
	      	m_remote_editor.EnableWindow(true);
	 
		    UpdateData(false);
		    if(m_client == NULL){
		        m_client =  socket(AF_INET,SOCK_DGRAM,0);
			}
    	    sockaddr_in serveraddr;
    	    UpdateData(true);
         	serveraddr.sin_family = AF_INET;
    	    serveraddr.sin_port = htons(m_port);
    	    serveraddr.sin_addr.S_un.S_addr = inet_addr(m_IP);
		    if(bind(m_client,(sockaddr*)&serveraddr,sizeof(serveraddr)) == SOCKET_ERROR){
		    	MessageBox("link error");
	        	return;
			}
			m_serial_port.EnableWindow(false);
     
    	    WSAAsyncSelect(m_client,m_hWnd,1000,FD_READ);

		}


	}else{
		m_connect.SetWindowText(_T("����"));
		if(m_client!=NULL){
	    	closesocket(m_client);
	        m_client = NULL;
		}
	   if(m_server != NULL){
	    	closesocket(m_server);
	    	m_server = NULL;
	   }
	   m_serial_port.EnableWindow(true);
	}
}
//����һ�����ַ�ת��Ϊ��Ӧ��ʮ������ֵ�ĺ���
//���ܣ�������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
char ConvertHexChar(char ch) 
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);
}

int String2Hex(CString str, CByteArray &senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	
	senddata.SetSize(len/2);
	
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}

	senddata.SetSize(hexdatalen);
	return hexdatalen;
}



void CNetProjectDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	CString netState;
	m_connect.GetWindowText(netState);
	CString serialState;
	m_serial_port.GetWindowText(serialState);
	if(netState == "����"&&serialState == "�رմ���"){
		UpdateData(TRUE); //��ȡ�༭������
		CString m_EditTxData;
		m_info.GetWindowText(m_EditTxData);
		if(m_EditTxData.IsEmpty())
			return;
		CByteArray hexdata;
		int len=String2Hex(m_EditTxData ,hexdata);
		if(m_sendhex){
			m_Comm1.SetOutput(COleVariant(hexdata));//��������
		}else{
			m_Comm1.SetOutput(COleVariant(m_EditTxData));//��������
		}
	}else{

		CString str,name,info;
     	m_name.GetWindowText(name);
    	m_info.GetWindowText(str);
    	if(!str.IsEmpty()){
	    	info.Format("%s",str);
			if(m_type.GetCurSel() == 2){
				UpdateData(true);
				int n = m_remote.Find(":");
				CString tmpPort = m_remote.Mid(n+1,m_remote.GetLength()-n);
				CString tmpIP = m_remote.Left(n);
				sockaddr_in serveraddr;   	        
    	        serveraddr.sin_family = AF_INET;
             	serveraddr.sin_port = htons(atoi(tmpPort));
            	serveraddr.sin_addr.S_un.S_addr = inet_addr(tmpIP);
				UpdateData(false);
				sendto(m_client,info.GetBuffer(0),info.GetLength(),0,(sockaddr*)&serveraddr,sizeof(serveraddr));
			}else{
		        int i = send(m_client,info.GetBuffer(0),info.GetLength(),0);
			}
		}	
	}
}




void CNetProjectDlg::OnClickedSerialPort() 
{
	// TODO: Add your control notification handler code here
	CString tmpButton;
	m_serial_port.GetWindowText(tmpButton);
	if(tmpButton == "�򿪴���"){
		//if(m_Comm1.GetPortOpen())
			//m_Comm1.SetPortOpen(FALSE);
 

		int baudIndex = m_portbaud.GetCurSel();
		CString baud;
		m_portbaud.GetLBText( baudIndex, baud);

		int stopbitIndex = m_portstopbit.GetCurSel();
		CString stopbit;
		m_portstopbit.GetLBText( stopbitIndex, stopbit);

		int checkIndex = m_portcheck.GetCurSel();
		CString check;
		m_portcheck.GetLBText( checkIndex, check);

		int numbitIndex = m_portnumbit.GetCurSel();
		CString numbit;
		m_portnumbit.GetLBText( numbitIndex, numbit);
		  
         
		m_Comm1.SetCommPort(m_serial_port_num.GetCurSel()+1); //ѡ��com1���ɸ��ݾ����������
		m_Comm1.SetInBufferSize(1024); //�������뻺�����Ĵ�С��Bytes
		m_Comm1.SetOutBufferSize(1024); //�������뻺�����Ĵ�С��Bytes//
		m_Comm1.SetSettings(baud+check+numbit+","+stopbit); //������9600����У�飬8������λ��1��ֹͣλ
		m_Comm1.SetInputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ����
		m_Comm1.SetRThreshold(1); 
		//����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
		m_Comm1.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0
		if( !m_Comm1.GetPortOpen())
			m_Comm1.SetPortOpen(TRUE);//�򿪴���
		else{
			AfxMessageBox("cannot open serial port");
			m_serial_port.SetWindowText("�򿪴���");
		}
		m_Comm1.GetInput();//��Ԥ���������������������
		UpdateData(false);
		m_serial_port.SetWindowText("�رմ���");
		m_connect.EnableWindow(false);
	}else{
         m_Comm1.SetPortOpen(FALSE);
		 m_serial_port.SetWindowText("�򿪴���");
		 m_connect.EnableWindow(true);
	}
	
}

BEGIN_EVENTSINK_MAP(CNetProjectDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CNetProjectDlg)
	ON_EVENT(CNetProjectDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CNetProjectDlg::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.
    CString strtemp;
	CString sendTemp;
	UpdateData(true);
	memset(rxdata,0,sizeof(rxdata));
    if(m_Comm1.GetCommEvent()==2) //�¼�ֵΪ2��ʾ���ջ����������ַ�
    {             ////////��������Ը����Լ���ͨ��Э����봦�����
        variant_inp=m_Comm1.GetInput(); //��������
        safearray_inp=variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
        len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
        for(k=0;k<len;k++) //������ת��ΪCstring�ͱ���
        {
            BYTE bt=*(char*)(rxdata+k); //�ַ���
			if(m_showhex){
                strtemp.Format("%02X ",bt); //���ַ�������ʱ����strtemp���
			}else{
				strtemp.Format("%c",bt); //���ַ�������ʱ����strtemp���
			}
            m_EditRxData+=strtemp; //������ձ༭���Ӧ�ַ��� 
			sendTemp+=strtemp; 
        }
    }
    UpdateData(false); //���±༭������
	m_list.AddString(sendTemp);
}

//��շ������ݿ�
void CNetProjectDlg::OnClearSendArea() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_edit_send = "";
	UpdateData(false);

}

//��ս������ݿ�
void CNetProjectDlg::OnClearReceiveArea() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_list.ResetContent();
	UpdateData(false);
 
}

 
