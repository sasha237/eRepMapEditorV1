#pragma once
#include "ChatFormView.h"

// CChatUsersView

class CChatUsersView : public CDockablePane
{
	DECLARE_DYNAMIC(CChatUsersView)

public:
	CChatUsersView();
	virtual ~CChatUsersView();

protected:
	DECLARE_MESSAGE_MAP()
	void AdjustLayout();
	void FillView();
	CChatFormView* m_wndUsers;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMove(int x, int y);
};


