
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "eRepMapEditor.h"
#include "eRepMapEditorView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_wndPropList.m_wndParent = this;
	m_pUnitItem = NULL;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb, rectClient.Width(), rectClient.Height() -(cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Properties"));


	CMFCEditorPropertyGridProperty* pType = new CMFCEditorPropertyGridProperty(_T("Type"), _T("Recruit"), _T("One of them"));
	pType->AddOption(_T("Recruit"));
	pType->AddOption(_T("Musqetier"));
	pType->AddOption(_T("Hussar"));
	pType->AddOption(_T("Grenadier"));
	pType->AddOption(_T("Gaubica"));
	pType->AddOption(_T("Eger"  ));
	pType->AddOption(_T("Dragoon"));
	pType->AddOption(_T("Cuirrasier"));
	pType->AddOption(_T("Cannon" ));
	pType->AllowEdit(FALSE);

	m_propType = pType;

	pGroup1->AddSubItem(pType);

	pGroup1->AddSubItem(m_propName = new CMFCEditorPropertyGridProperty(_T("Name"), (_variant_t) _T("Name1"), _T("Specifies the text that will be displayed in the unit's title bar")));

	pGroup1->AddSubItem(m_propCount = new CMFCEditorPropertyGridProperty(_T("Count"), (_variant_t) _T("100"), _T("Specifies the count that will be displayed in the unit's title bar")));

	CMFCEditorPropertyGridProperty* pProp = new CMFCEditorPropertyGridProperty(_T("Rotate"), _T("Left"), _T("One of: Left or Right"));
	pProp->AddOption(_T("Left"));
	pProp->AddOption(_T("Right"));
	pProp->AllowEdit(FALSE);

	m_propRotate = pProp;

	pGroup1->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Unit Color"), RGB(255, 255, 255), NULL, _T("Specifies the unit color"));
	pColorProp->EnableOtherButton(_T("Other..."));
	pColorProp->EnableAutomaticButton(_T("Neutral"), RGB(255, 255, 255));

	pGroup1->AddSubItem(pColorProp);
	m_propColor = pColorProp;

	m_wndPropList.AddProperty(pGroup1);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}

CString CPropertiesWnd::GetName()
{
	COleVariant var = m_propName->GetValue();
	CComBSTR bstr = var.bstrVal;
	CString sVal(bstr);
	return sVal;
}
int CPropertiesWnd::GetCount()
{
	COleVariant var = m_propCount->GetValue();
	CComBSTR bstr = var.bstrVal;
	CString sVal(bstr);
	return atoi(sVal);
}
bool CPropertiesWnd::GetRotate()
{
	COleVariant var = m_propRotate->GetValue();
	CComBSTR bstr = var.bstrVal;
	CString sVal(bstr);
	return sVal.CompareNoCase(_T("Left"));
}
COLORREF CPropertiesWnd::GetColor()
{
	return m_propColor->GetColor();
}
int CPropertiesWnd::GetType()
{
	COleVariant var = m_propType->GetValue();
	CComBSTR bstr = var.bstrVal;
	CString sVal(bstr);
	
	if (!sVal.CompareNoCase("Recruit"))		return 35;
	if (!sVal.CompareNoCase("Musqetier"))	return 36;
	if (!sVal.CompareNoCase("Hussar"))		return 37;
	if (!sVal.CompareNoCase("Grenadier"))	return 38;
	if (!sVal.CompareNoCase("Gaubica"))		return 39;
	if (!sVal.CompareNoCase("Eger"  ))		return 40;
	if (!sVal.CompareNoCase("Dragoon"))		return 41;
	if (!sVal.CompareNoCase("Cuirrasier"))	return 42;
	if (!sVal.CompareNoCase("Cannon" ))		return 43;
	return 0;
}
CUnitItem* CPropertiesWnd::GetUnitItem()
{
	return m_pUnitItem;
}

void CPropertiesWnd::SetAllProps()
{
	if (m_pUnitItem)
		m_propType->Show(TRUE);
	else
		m_propType->Show(FALSE);
	if (!m_pUnitItem)
		return;
	SetName(m_pUnitItem->m_sName);
	SetCount(m_pUnitItem->m_iCount);
	SetRotate(m_pUnitItem->m_bRotate);
	SetColor(m_pUnitItem->m_rgbColor);
	SetType(m_pUnitItem->m_iType);
}

void CPropertiesWnd::SetName(CString& sName)
{
	if (!m_pUnitItem)
		return;
	m_propName->SetValue(COleVariant(sName));
}
void CPropertiesWnd::SetCount(int iCount)
{
	if (!m_pUnitItem)
		return;
	CString sCount;
	sCount.Format("%d",iCount);
	m_propCount->SetValue(COleVariant(sCount));
}
void CPropertiesWnd::SetRotate(bool bRotate)
{
	if (!m_pUnitItem)
		return;
	CString sRotate = CString(bRotate?"Right":"Left");
	m_propRotate->SetValue(COleVariant(sRotate));
}
void CPropertiesWnd::SetColor(COLORREF rfColor)
{
	if (!m_pUnitItem)
		return;
	m_propColor->SetColor(rfColor);
}
void CPropertiesWnd::SetType(int iType)
{
	CString sType;
	switch (iType)
	{
		case 35: sType = "Recruit"; break;
		case 36: sType = "Musqetier"; break;
		case 37: sType = "Hussar"; break;
		case 38: sType = "Grenadier"; break;
		case 39: sType = "Gaubica"; break;
		case 40: sType = "Eger"  ; break;
		case 41: sType = "Dragoon"; break;
		case 42: sType = "Cuirrasier"; break;
		case 43: sType = "Cannon" ; break;
		default: break;
	}
	m_propType->SetValue(COleVariant(sType));
}
void CPropertiesWnd::SetUnitItem(CUnitItem* pUnitItem, CeRepMapEditorView* pView)
{
	m_pUnitItem = pUnitItem;
	m_pView = pView;
	SetAllProps();
}
void CPropertiesWnd::SetAllUnitProps(bool bRegen /*= true*/)
{

	if (!m_pUnitItem)
		return;

	SetUnitName();
	SetUnitCount();
	SetUnitRotate();
	SetUnitColor();
	SetUnitType();		
	if (bRegen)
	{
		m_pView->RegenUpper(m_pUnitItem->m_pMapItem->m_piiIndex);
	}
}
void CPropertiesWnd::SetUnitName()
{
	if (!m_pUnitItem)
		return;
	m_pUnitItem->m_sName = GetName();
}
void CPropertiesWnd::SetUnitCount()
{
	if (!m_pUnitItem)
		return;
	m_pUnitItem->m_iCount = GetCount();
}
void CPropertiesWnd::SetUnitRotate()
{
	if (!m_pUnitItem)
		return;
	m_pUnitItem->m_bRotate = GetRotate();
}
void CPropertiesWnd::SetUnitColor()
{
	if (!m_pUnitItem)
		return;
	m_pUnitItem->m_rgbColor = GetColor();
}
void CPropertiesWnd::SetUnitType()
{
	if (!m_pUnitItem)
		return;
	m_pUnitItem->m_iType = GetType();
}

void CPropertiesWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDockablePane::OnShowWindow(bShow, nStatus);
	if (m_pUnitItem)
		m_propType->Show(TRUE);
	else
		m_propType->Show(FALSE);

}

void CPropertiesWnd::ShowOnlyColor(bool bOnlyColor)
{
	m_propType->Show(!bOnlyColor);
	m_propName->Show(!bOnlyColor);
	m_propCount->Show(!bOnlyColor);
	m_propRotate->Show(!bOnlyColor);
}