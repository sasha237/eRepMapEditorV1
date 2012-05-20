// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "Resource.h"
#include "GdiPlusBitmap.h"
#include "ChatUsersView.h"
class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;

	void LoadBitmaps();
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	mibiMap m_mibiElBtimaps;
	CMFCRibbonEdit* m_WEdit;
	CMFCRibbonEdit* m_HEdit;
	CMFCRibbonEdit* m_SEdit;
	CMFCRibbonButton* m_BBridges;
	CMFCRibbonButton* m_Hospitals;
	CMFCRibbonButton* m_Defences;
	mibiMap m_mibiWaterBtimaps;
	mibiMap m_mibiBridgeBitmaps;
	CGdiPlusBitmapResource* m_pEmpty;
	CMFCRibbonButtonsGroup* m_BpGrp;
	CMFCRibbonButtonsGroup* m_DGrp;
	CMFCRibbonButtonsGroup* m_HGrp;
	CMFCRibbonCheckBox* m_pShowNumCh;
//	CChatUsersView m_wndUsersView;
	CMFCToolBarImages m_UserImages;
};



