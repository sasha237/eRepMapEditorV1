// MFCEditPropertyGridColorProperty.cpp : implementation file
//

#include "stdafx.h"
#include "eRepMapEditor.h"
#include "MFCEditPropertyGridColorProperty.h"
#include "PropertiesWnd.h"


// CMFCEditPropertyGridColorProperty

CMFCEditPropertyGridColorProperty::CMFCEditPropertyGridColorProperty(const CString& strName, const COLORREF& color, CPalette* pPalette /*= NULL*/, LPCTSTR lpszDescr /*= NULL*/, DWORD_PTR dwData /*= 0*/):
CMFCPropertyGridColorProperty(strName, color, pPalette, lpszDescr, dwData)
{
}

CMFCEditPropertyGridColorProperty::~CMFCEditPropertyGridColorProperty()
{
}


// CMFCEditPropertyGridColorProperty member functions
BOOL CMFCEditPropertyGridColorProperty::OnEndEdit()
{
	CMFCPropertyGridColorProperty::OnEndEdit();
	CMFCErepEditorPropertyGridCtrl* pWnd = dynamic_cast<CMFCErepEditorPropertyGridCtrl*>(m_pWndList);
	if (!pWnd)
		return FALSE;
	if (pWnd->m_wndParent->GetUnitItem())
	{
		pWnd->m_wndParent->SetAllUnitProps();
	}
	return TRUE;
}