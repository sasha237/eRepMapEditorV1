#pragma once
#include "afxwin.h"



// CChatFormView form view

class CChatFormView : public CFormView
{
	DECLARE_DYNCREATE(CChatFormView)

public:
	CChatFormView();           // protected constructor used by dynamic creation
	virtual ~CChatFormView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendMessageButton();
	CEdit m_all_messages_edit;
	CEdit m_write_message_edit;
	CListBox m_users_list;
	CButton m_send_button;
	CStatic m_status_static;
	CStatic m_users_static;
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AdjustLayout();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedOk();
};


