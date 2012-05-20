// MFCErepEditorPropertyGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "eRepMapEditor.h"
#include "MFCErepEditorPropertyGridCtrl.h"
#include "PropertiesWnd.h"

// CMFCErepEditorPropertyGridCtrl

IMPLEMENT_DYNAMIC(CMFCErepEditorPropertyGridCtrl, CMFCPropertyGridCtrl)

CMFCErepEditorPropertyGridCtrl::CMFCErepEditorPropertyGridCtrl()
{

}

CMFCErepEditorPropertyGridCtrl::~CMFCErepEditorPropertyGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CMFCErepEditorPropertyGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


BOOL CMFCErepEditorPropertyGridCtrl::EndEditItem(BOOL bUpdateData/* = TRUE*/)
{
	if (m_wndParent->GetUnitItem())
	{
		m_wndParent->SetAllUnitProps();
	}
	return CMFCPropertyGridCtrl::EndEditItem(bUpdateData);
}
// CMFCErepEditorPropertyGridCtrl message handlers


