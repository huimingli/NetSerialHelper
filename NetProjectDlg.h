// NetProjectDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm1.h"
//}}AFX_INCLUDES

#if !defined(AFX_NETPROJECTDLG_H__B5DB9A01_1DAD_4E90_8A9B_C95D8BA4FD95__INCLUDED_)
#define AFX_NETPROJECTDLG_H__B5DB9A01_1DAD_4E90_8A9B_C95D8BA4FD95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNetProjectDlg dialog
 
class CNetProjectDlg : public CDialog
{
// Construction
public:
	CNetProjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNetProjectDlg)
	enum { IDD = IDD_NETPROJECT_DIALOG };
	CComboBox	m_portnumbit;
	CComboBox	m_portbaud;
	CComboBox	m_portstopbit;
	CComboBox	m_portcheck;
	CComboBox	m_serial_port_num;
	CButton	m_serial_port;
	CButton	m_connect;
	CEdit	m_remote_editor;
	CComboBox	m_type;
	CEdit	m_info;
	CEdit	m_name;
	CListBox	m_list;
	int		m_port;
	CString	m_IP;
	CString	m_remote;
	CMSComm	m_Comm1;
	CString	m_EditRxData;
	CString	m_edit_send;
	BOOL	m_showhex;
	BOOL	m_sendhex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetProjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	void receiveData();
	void handleData();
	BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetProjectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedConnect();
	afx_msg void OnButtonSend();
	afx_msg void OnClickedSerialPort();
	afx_msg void OnComm();
	afx_msg void OnClearSendArea();
	afx_msg void OnClearReceiveArea();
 
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SOCKET m_client,m_server;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETPROJECTDLG_H__B5DB9A01_1DAD_4E90_8A9B_C95D8BA4FD95__INCLUDED_)
