// MFCEditorPropertyGridProperty.cpp : implementation file
//

#include "stdafx.h"
#include "eRepMapEditor.h"
#include "MFCEditorPropertyGridProperty.h"
#include "PropertiesWnd.h"


// CMFCEditorPropertyGridProperty

CMFCEditorPropertyGridProperty::CMFCEditorPropertyGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
	:CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{
}
CMFCEditorPropertyGridProperty::CMFCEditorPropertyGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
	:CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{
}
CMFCEditorPropertyGridProperty::~CMFCEditorPropertyGridProperty()
{
}

BOOL CMFCEditorPropertyGridProperty::OnEndEdit()
{
	CMFCPropertyGridProperty::OnEndEdit();
	CMFCErepEditorPropertyGridCtrl* pWnd = dynamic_cast<CMFCErepEditorPropertyGridCtrl*>(m_pWndList);
	if (!pWnd)
		return FALSE;
	if (pWnd->m_wndParent->GetUnitItem())
	{
		pWnd->m_wndParent->SetAllUnitProps();
	}
	return TRUE;
}
void CMFCEditorPropertyGridProperty::OnSelectCombo()
{
	CMFCPropertyGridProperty::OnSelectCombo();
	CMFCErepEditorPropertyGridCtrl* pWnd = dynamic_cast<CMFCErepEditorPropertyGridCtrl*>(m_pWndList);
	if (!pWnd)
		return;
	if (pWnd->m_wndParent->GetUnitItem())
	{
		pWnd->m_wndParent->SetAllUnitProps();
	}
}

// CMFCEditorPropertyGridProperty member functions
