#pragma once
#include "MFCErepEditorPropertyGridCtrl.h"
#include "MapItem.h"
#include "MFCEditorPropertyGridProperty.h"
class CeRepMapEditorView;
class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();

// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CPropertiesToolBar m_wndToolBar;
	CMFCErepEditorPropertyGridCtrl m_wndPropList;

// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	CMFCEditorPropertyGridProperty* m_propType;
	CMFCEditorPropertyGridProperty* m_propName;
	CMFCEditorPropertyGridProperty* m_propCount;
	CMFCEditorPropertyGridProperty* m_propRotate;
	CMFCPropertyGridColorProperty* m_propColor;
	CUnitItem* m_pUnitItem;
	CeRepMapEditorView* m_pView;
public:
	CString GetName();
	int GetCount();
	bool GetRotate();
	COLORREF GetColor();
	int GetType();
	CUnitItem* GetUnitItem();

	void SetAllProps();
	void SetName(CString& sName);
	void SetCount(int iCount);
	void SetRotate(bool bRotate);
	void SetColor(COLORREF rfColor);
	void SetType(int iType);
	void SetUnitItem(CUnitItem* pUnitItem, CeRepMapEditorView* pView);

	void SetAllUnitProps(bool bRegen = true);
	void SetUnitName();
	void SetUnitCount();
	void SetUnitRotate();
	void SetUnitColor();
	void SetUnitType();		

	void ShowOnlyColor(bool bOnlyColor);

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


