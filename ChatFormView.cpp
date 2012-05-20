// ChatFormView.cpp : implementation file
//

#include "stdafx.h"
#include "eRepMapEditor.h"
#include "ChatFormView.h"


// CChatFormView

IMPLEMENT_DYNCREATE(CChatFormView, CFormView)

CChatFormView::CChatFormView()
	: CFormView(CChatFormView::IDD)
{

}

CChatFormView::~CChatFormView()
{
}

void CChatFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALL_MESSAGES_EDIT, m_all_messages_edit);
	DDX_Control(pDX, IDC_WRITE_MESSAGE_EDIT, m_write_message_edit);
	DDX_Control(pDX, IDC_USERS_LIST, m_users_list);
	DDX_Control(pDX, IDC_SEND_MESSAGE_BUTTON, m_send_button);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_status_static);
	DDX_Control(pDX, IDC_MEMBERS_STATIC, m_users_static);
}

BEGIN_MESSAGE_MAP(CChatFormView, CFormView)
	ON_BN_CLICKED(IDC_SEND_MESSAGE_BUTTON, &CChatFormView::OnBnClickedSendMessageButton)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDOK, &CChatFormView::OnBnClickedOk)
END_MESSAGE_MAP()


// CChatFormView diagnostics

#ifdef _DEBUG
void CChatFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChatFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChatFormView message handlers

void CChatFormView::OnBnClickedSendMessageButton()
{
	CString sBuf1, sBuf2;
	m_all_messages_edit.GetWindowText(sBuf1);
	m_send_button.GetWindowText(sBuf2);
	sBuf2.Trim();
	if (sBuf2.IsEmpty())
		return;
	sBuf1.Append(sBuf2);
	m_all_messages_edit.SetWindowText(sBuf1);
}

BOOL CChatFormView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CChatFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CChatFormView::AdjustLayout()
{
	if (!m_all_messages_edit)
	{
		return;
	}
	CRect rectClient;
	CRect rt;
	CRect rt1;
	GetClientRect(rectClient);

	m_status_static.GetWindowRect(rt);

 	m_status_static.MoveWindow(rectClient.left,rectClient.top,(rectClient.Width()-4)*3/4,rt.Height());
 	m_users_static.MoveWindow(rectClient.left+(rectClient.Width()-4)*3/4+4,rectClient.top,(rectClient.Width()-4)*1/4,rt.Height());
 	m_all_messages_edit.MoveWindow(rectClient.left, rectClient.top + rt.Height() +4, (rectClient.Width() - 4)*3/4, (rectClient.Height() - rt.Height() - 4)*4/5);
 	m_users_list.MoveWindow(rectClient.left+(rectClient.Width()-4)*3/4+4, rectClient.top + rt.Height() +4, (rectClient.Width()-4)*1/4, (rectClient.Height() - rt.Height() - 4)*4/5);
 	m_users_list.GetWindowRect(rt1);
 	m_write_message_edit.MoveWindow(rectClient.left, rectClient.top + rt.Height() +4 + rt1.Height()+4, (rectClient.Width() - 4)*3/4, (rectClient.Height() - rt.Height() - 4)*1/5-4);
 	m_send_button.MoveWindow(rectClient.left+(rectClient.Width()-4)*3/4+4, rectClient.top + rt.Height() +4 + rt1.Height()+4, (rectClient.Width()-4)*1/4, (rectClient.Height() - rt.Height() - 4)*1/5-4);
}
void CChatFormView::OnMove(int x, int y)
{
	CFormView::OnMove(x, y);

	AdjustLayout();
}

void CChatFormView::OnBnClickedOk()
{
	OnBnClickedSendMessageButton();
}
