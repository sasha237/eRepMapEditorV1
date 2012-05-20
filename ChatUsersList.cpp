// ChatUsersList.cpp : implementation file
//

#include "stdafx.h"
#include "eRepMapEditor.h"
#include "ChatUsersList.h"


// CChatUsersList

IMPLEMENT_DYNAMIC(CChatUsersList, CListCtrl)

CChatUsersList::CChatUsersList()
{

}

CChatUsersList::~CChatUsersList()
{
}


BEGIN_MESSAGE_MAP(CChatUsersList, CListCtrl)
END_MESSAGE_MAP()



// CChatUsersList message handlers



BOOL CChatUsersList::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bRes = CListCtrl::OnNotify(wParam, lParam, pResult);
	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}
