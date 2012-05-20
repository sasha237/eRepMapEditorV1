// ChatUsersView.cpp : implementation file
//

#include "stdafx.h"
#include "eRepMapEditor.h"
#include "ChatUsersView.h"


// CChatUsersView

IMPLEMENT_DYNAMIC(CChatUsersView, CDockablePane)

CChatUsersView::CChatUsersView()
{
//	m_wndUsers = NULL;
	m_wndUsers = new CChatFormView;
}

CChatUsersView::~CChatUsersView()
{
}


BEGIN_MESSAGE_MAP(CChatUsersView, CDockablePane)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_MOVE()
END_MESSAGE_MAP()



void CChatUsersView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
	if (!m_wndUsers)
		return;
	m_wndUsers->MoveWindow(rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2);

}



void CChatUsersView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CChatUsersView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (!m_wndUsers)
		return;
	CSize sz;
	CRect rect;
	GetClientRect(rect);
	m_wndUsers->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CChatUsersView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	if (!m_wndUsers)
		return;

	m_wndUsers->SetFocus();
}



int CChatUsersView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect rectDummy(0,0,0,0);

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wndUsers)
		return 0;
	CCreateContext Context;
	Context.m_pNewViewClass = RUNTIME_CLASS(CChatFormView);
	if (!m_wndUsers->Create(RUNTIME_CLASS(CChatFormView)->m_lpszClassName,"ChatUsers",dwViewStyle, rectDummy, this, ID_CHAT_USERS,&Context))
	{
		TRACE0("Failed to create View\n");
		return -1;      // fail to create
	}

	m_wndUsers->SetOwner(this);
	// Load images:

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillView();

	return 0;
}
void CChatUsersView::FillView()
{

}
void CChatUsersView::OnMove(int x, int y)
{
	CDockablePane::OnMove(x, y);

	AdjustLayout();
}
