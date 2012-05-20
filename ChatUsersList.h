#pragma once
#include "FlistCtrl.h"

// CChatUsersList

class CChatUsersList : public CFListCtrl
{
	DECLARE_DYNAMIC(CChatUsersList)

public:
	CChatUsersList();
	virtual ~CChatUsersList();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


