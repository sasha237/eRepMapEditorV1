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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "eRepMapEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
	while(m_mibiElBtimaps.size())
	{
		delete m_mibiElBtimaps.begin()->second;
		m_mibiElBtimaps.erase(m_mibiElBtimaps.begin());
	}
	while(m_mibiWaterBtimaps.size())
	{
		delete m_mibiWaterBtimaps.begin()->second;
		m_mibiWaterBtimaps.erase(m_mibiWaterBtimaps.begin());
	}
	while(m_mibiBridgeBitmaps.size())
	{
		delete m_mibiBridgeBitmaps.begin()->second;
		m_mibiBridgeBitmaps.erase(m_mibiBridgeBitmaps.begin());
	}
	while(m_mibiUnits.size())
	{
		delete m_mibiUnits.begin()->second;
		m_mibiUnits.erase(m_mibiUnits.begin());
	}

	delete m_pEmpty;
	m_pEmpty = NULL;

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	LoadBitmaps();
	InitializeRibbon();
	

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
//	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, _T("x=0 y=0"), TRUE), _T("x=0 y=0"));

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

 	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}


	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// Load panel images:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// Init main button:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);
	
	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, strTemp, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, strTemp, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, strTemp, 3, 3));

	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS_PICTURE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS_PICTURE, strTemp, 8, 8));

	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

	
	CMFCRibbonCategory* pCategoryHome = NULL;
	CMFCRibbonButton* pBtnWindows = NULL;
	CMFCRibbonPanel* pPanelWindow = NULL;
	CMFCRibbonButton* pSub = NULL;


	bNameValid = strTemp.LoadString(IDS_RIBBON_PAINT);
	ASSERT(bNameValid);
	pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_MAINTOOLBAR_SMALL, IDB_MAINTOOLBAR);

	bNameValid = strTemp.LoadString(IDS_RIBBON_ELEMENTS);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_PLAIN);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_PLAIN, strTemp, 2, 2));

	bNameValid = strTemp.LoadString(IDS_RIBBON_HILL);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_HILL, strTemp, 4, 4));

	bNameValid = strTemp.LoadString(IDS_RIBBON_MOUNTAIN);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_MOUNTAIN, strTemp, 5, 5));

	bNameValid = strTemp.LoadString(IDS_RIBBON_FOREST);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_FOREST, strTemp, 6, 6));

	bNameValid = strTemp.LoadString(IDS_RIBBON_WATER);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_WATER, strTemp, 3, 3));


	pPanelWindow->SetJustifyColumns(TRUE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_BRIDGE);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);


	bNameValid = strTemp.LoadString(IDS_RIBBON_BRIDGE);
	ASSERT(bNameValid);
	m_BBridges = new CMFCRibbonButton(ID_BRIDGE, strTemp, 1,1);
	pPanelWindow->Add(m_BBridges);
	m_BpGrp = new CMFCRibbonButtonsGroup();

	CMFCToolBarImages images;
	images.SetImageSize(CSize(32, 32));
	images.SetTransparentColor(RGB(0,0,0));
	if(images.Load(IDB_MAINTOOLBAR))
		m_BpGrp->SetImages(&images, NULL, NULL);
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE001001, _T(""), 9,9));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE001001, _T(""), 9,9));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE001010, _T(""), 10,10));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE001010, _T(""), 10,10));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE010001, _T(""), 11,11));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE010001, _T(""), 11,11));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE010010, _T(""), 12,12));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE010010, _T(""), 12,12));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE011000, _T(""), 13,13));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE011000, _T(""), 13,13));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE011011, _T(""), 14,14));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE011011, _T(""), 14,14));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE000011, _T(""), 15,15));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE000011, _T(""), 15,15));

	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE000101, _T(""), 16,16));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE000101, _T(""), 16,16));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE010100, _T(""), 17,17));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE010100, _T(""), 17,17));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE010101, _T(""), 18,18));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE010101, _T(""), 18,18));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE100010, _T(""), 19,19));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE100010, _T(""), 19,19));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE100100, _T(""), 20,20));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE100100, _T(""), 20,20));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE101000, _T(""), 21,21));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE101000, _T(""), 21,21));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE101010, _T(""), 22,22));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE101010, _T(""), 22,22));
	m_BpGrp->AddButton(new CMFCRibbonButton(ID_BRIDGE111111, _T(""), 23,23));
	m_BBridges->AddSubItem(new CMFCRibbonButton(ID_BRIDGE111111, _T(""), 23,23));

	bNameValid = strTemp.LoadString(IDS_RIBBON_BRIDGE);
	m_wndStatusBar.AddElement(m_BpGrp,strTemp);
	m_BpGrp->SetVisible(FALSE);
	
	bNameValid = strTemp.LoadString(IDS_RIBBON_BUILDINGS);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_BIG_CITY);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_BIG_CITY, strTemp, 27,27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_SMALL_CITY);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_SMALL_CITY, strTemp, 28,28));

	m_HGrp = new CMFCRibbonButtonsGroup();
	m_HGrp->SetImages(&images,NULL,NULL);
	bNameValid = strTemp.LoadString(IDS_RIBBON_HOSPITALS);
	m_Hospitals = new CMFCRibbonButton(ID_HOSPITALS, strTemp, 29,29);
	pPanelWindow->Add(m_Hospitals);
	m_Hospitals->AddSubItem(new CMFCRibbonButton(ID_H1, _T(""), 29,29));
	m_HGrp->AddButton(new CMFCRibbonButton(ID_H1, _T(""), 29,29));
	m_Hospitals->AddSubItem(new CMFCRibbonButton(ID_H2, _T(""), 30,30));
	m_HGrp->AddButton(new CMFCRibbonButton(ID_H2, _T(""), 30,30));
	m_Hospitals->AddSubItem(new CMFCRibbonButton(ID_H3, _T(""), 31,31));
	m_HGrp->AddButton(new CMFCRibbonButton(ID_H3, _T(""), 31,31));
	m_Hospitals->AddSubItem(new CMFCRibbonButton(ID_H4, _T(""), 32,32));
	m_HGrp->AddButton(new CMFCRibbonButton(ID_H4, _T(""), 32,32));
	m_Hospitals->AddSubItem(new CMFCRibbonButton(ID_H5, _T(""), 33,33));
	m_HGrp->AddButton(new CMFCRibbonButton(ID_H5, _T(""), 33,33));
	bNameValid = strTemp.LoadString(IDS_RIBBON_HOSPITALS);
	m_wndStatusBar.AddElement(m_HGrp,strTemp);
	m_HGrp->SetVisible(FALSE);

	m_DGrp = new CMFCRibbonButtonsGroup();
	m_DGrp->SetImages(&images,NULL,NULL);
	bNameValid = strTemp.LoadString(IDS_RIBBON_DEFENCES);
	m_Defences = new CMFCRibbonButton(ID_DEFENCES, strTemp, 34,34);
	pPanelWindow->Add(m_Defences);
	m_Defences->AddSubItem(new CMFCRibbonButton(ID_D1, _T(""), 34,34));
	m_DGrp->AddButton(new CMFCRibbonButton(ID_D1, _T(""), 34,34));
	m_Defences->AddSubItem(new CMFCRibbonButton(ID_D2, _T(""), 35,35));
	m_DGrp->AddButton(new CMFCRibbonButton(ID_D2, _T(""), 35,35));
	m_Defences->AddSubItem(new CMFCRibbonButton(ID_D3, _T(""), 36,36));
	m_DGrp->AddButton(new CMFCRibbonButton(ID_D3, _T(""), 36,36));
	m_Defences->AddSubItem(new CMFCRibbonButton(ID_D4, _T(""), 37,37));
	m_DGrp->AddButton(new CMFCRibbonButton(ID_D4, _T(""), 37,37));
	m_Defences->AddSubItem(new CMFCRibbonButton(ID_D5, _T(""), 38,38));
	m_DGrp->AddButton(new CMFCRibbonButton(ID_D5, _T(""), 38,38));
	bNameValid = strTemp.LoadString(IDS_RIBBON_DEFENCES);
	m_wndStatusBar.AddElement(m_DGrp,strTemp);
	m_DGrp->SetVisible(FALSE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_UNITS);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);

	m_UGrp = new CMFCRibbonButtonsGroup();
	m_UGrp->SetImages(&images,NULL,NULL);
	bNameValid = strTemp.LoadString(IDS_RIBBON_UNITS);
	m_Units = new CMFCRibbonButton(ID_UNITS, strTemp, 39,39);

	bNameValid = strTemp.LoadString(IDS_RIBBON_CURSOR);
	ASSERT(bNameValid);
	pPanelWindow->Add(new CMFCRibbonButton(ID_CURSOR_ELEMENT, strTemp, 7, 7));

	pPanelWindow->Add(m_Units);
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_RECRUIT, _T(""), 39,39));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_RECRUIT, _T(""), 39,39));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_MUSQUETIER, _T(""), 40,40));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_MUSQUETIER, _T(""), 40,40));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_HUSSAR, _T(""), 41,41));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_HUSSAR, _T(""), 41,41));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_GRENADIER, _T(""), 42,42));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_GRENADIER, _T(""), 42,42));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_GAUBICA, _T(""), 43,43));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_GAUBICA, _T(""), 43,43));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_EGER, _T(""), 44,44));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_EGER, _T(""), 44,44));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_DRAGOON, _T(""), 45,45));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_DRAGOON, _T(""), 45,45));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_CUIRASSIER, _T(""), 46,46));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_CUIRASSIER, _T(""), 46,46));
	m_Units->AddSubItem(new CMFCRibbonButton	(ID_CANNON, _T(""), 47,47));
	m_UGrp->AddButton(new CMFCRibbonButton		(ID_CANNON, _T(""), 47,47));
  	pBtnWindows = new CMFCRibbonButton			(ID_AREAS, "Area", 48,48);
  	pPanelWindow->Add(pBtnWindows);

	bNameValid = strTemp.LoadString(IDS_RIBBON_UNITS);
	m_wndStatusBar.AddElement(m_UGrp,strTemp);
	m_UGrp->SetVisible(FALSE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_UNITS);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_ALL_FILTERS);
	ASSERT(bNameValid);
	m_pAllFilters = new CMFCRibbonCheckBox(ID_ALL_FILTERS,strTemp);
	pPanelWindow->Add(m_pAllFilters);

	m_pColorFilter = new CMFCRibbonColorButton(ID_FILTER_COLOR,_T("Filter color"),-1,RGB(255, 255, 255));
	m_pColorFilter->EnableAutomaticButton(_T("Neutral"), RGB(255, 255, 255));
	m_pColorFilter->EnableOtherButton(_T("Other..."));
	pPanelWindow->Add(m_pColorFilter);

// 	bNameValid = strTemp.LoadString(IDS_FILTER_BY_FOREST);
// 	ASSERT(bNameValid);
// 	m_pForestFilter = new CMFCRibbonCheckBox(ID_FILTER_BY_FOREST,strTemp);
// 	pPanelWindow->Add(m_pForestFilter);

	pPanelWindow->SetJustifyColumns(TRUE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_SIZE);
	ASSERT(bNameValid);
	pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_MAINTOOLBAR_SMALL, IDB_MAINTOOLBAR);


	bNameValid = strTemp.LoadString(IDS_RIBBON_SIZE);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_WIDTH);
	m_WEdit = new CMFCRibbonEdit(ID_WIDTH, 60, strTemp);
	m_WEdit->SetToolTipText(strTemp);
	pPanelWindow->Add(m_WEdit);

	bNameValid = strTemp.LoadString(IDS_RIBBON_HEIGHT);
	m_HEdit = new CMFCRibbonEdit(ID_HEIGHT, 60, strTemp);
	m_HEdit->SetToolTipText(strTemp);
	pPanelWindow->Add(m_HEdit);

	bNameValid = strTemp.LoadString(IDS_RIBBON_RESIZE);
	pBtnWindows = new CMFCRibbonButton(ID_RESIZE_SIZE, strTemp, -1, -1);
	pBtnWindows->SetToolTipText(strTemp);
	pPanelWindow->Add(pBtnWindows);

	pPanelWindow->SetJustifyColumns(TRUE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_SCALE);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_SCALE);
	m_SEdit = new CMFCRibbonEdit(ID_SCALE, 60, strTemp);
	m_SEdit->SetToolTipText(strTemp);
	pPanelWindow->Add(m_SEdit);

	bNameValid = strTemp.LoadString(IDS_RIBBON_ZOOMIN);
	pBtnWindows = new CMFCRibbonButton(ID_ZOOMIN_SCALE, strTemp, 25, 25);
	pBtnWindows->SetToolTipText(strTemp);
	pPanelWindow->Add(pBtnWindows);

	bNameValid = strTemp.LoadString(IDS_RIBBON_ZOOMOUT);
	pBtnWindows = new CMFCRibbonButton(ID_ZOOMOUT_SCALE, strTemp, 26, 26);
	pBtnWindows->SetToolTipText(strTemp);
	pPanelWindow->Add(pBtnWindows);

	pPanelWindow->SetJustifyColumns(TRUE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_WINDOW);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));

	bNameValid = strTemp.LoadString(IDS_RIBBON_WINDOWS);
	ASSERT(bNameValid);
	pBtnWindows = new CMFCRibbonButton(ID_WINDOW_MANAGER, strTemp, -1, 8);
	pBtnWindows->SetMenu(IDR_WINDOWS_MENU, TRUE);
	pPanelWindow->Add(pBtnWindows);

	bNameValid = strTemp.LoadString(IDS_RIBBON_SHOW_NUMBERS);
	ASSERT(bNameValid);
	pPanelWindow = pCategoryHome->AddPanel(strTemp);
	m_pShowNumCh = new CMFCRibbonCheckBox(ID_RIBBON_SHOW_NUMBERS,strTemp);
	pPanelWindow->Add(m_pShowNumCh);

	// Add elements to the right side of tabs:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* No default command */, TRUE /* Right align */);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// Add quick access toolbar commands:
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
//	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);

	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::LoadBitmaps()
{
	CGdiPlusBitmapResource* cb = NULL;
	cb = new CGdiPlusBitmapResource;
	cb->Load(_T("IDB_PLAIN"), _T("PNG"));
	m_mibiElBtimaps.insert(make_pair(MODE_PLAIN,cb));
	cb = new CGdiPlusBitmapResource;
	cb->Load(_T("IDB_HILL"), _T("PNG"));
	m_mibiElBtimaps.insert(make_pair(MODE_HILL,cb));
	cb = new CGdiPlusBitmapResource;
	cb->Load(_T("IDB_WATER"), _T("PNG"));
	m_mibiElBtimaps.insert(make_pair(MODE_WATER,cb));
	cb = new CGdiPlusBitmapResource;
	cb->Load(_T("IDB_MOUNTAIN"), _T("PNG"));
	m_mibiElBtimaps.insert(make_pair(MODE_MOUNTAIN,cb));
	cb = new CGdiPlusBitmapResource;
	cb->Load(_T("IDB_BRIDGE"), _T("PNG"));
	m_mibiElBtimaps.insert(make_pair(MODE_BRIDGE,cb));
	cb = new CGdiPlusBitmapResource;
	cb->Load(_T("IDB_FOREST"), _T("PNG"));
	m_mibiElBtimaps.insert(make_pair(MODE_FOREST,cb));

	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGBIG_CITY"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_BIG_CITY	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGD1"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_D1	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGD2"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_D2	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGD3"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_D3	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGD4"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_D4	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGD5"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_D5	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGH1"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_H1	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGH2"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_H2	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGH3"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_H3	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGH4"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_H4	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGH5"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_H5	,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGSMALL_CITY"), _T("PNG"));m_mibiElBtimaps.insert(make_pair(MODE_SMALL_CITY	,cb));

	int i;
	CStringArray sBufArr;
	sBufArr.Add("IDB_PNG000000");
	sBufArr.Add("IDB_PNG000001");
	sBufArr.Add("IDB_PNG000010");
	sBufArr.Add("IDB_PNG000011");
	sBufArr.Add("IDB_PNG000100");
	sBufArr.Add("IDB_PNG000101");
	sBufArr.Add("IDB_PNG000110");
	sBufArr.Add("IDB_PNG000111");
	sBufArr.Add("IDB_PNG001000");
	sBufArr.Add("IDB_PNG001001");
	sBufArr.Add("IDB_PNG001010");
	sBufArr.Add("IDB_PNG001011");
	sBufArr.Add("IDB_PNG001100");
	sBufArr.Add("IDB_PNG001101");
	sBufArr.Add("IDB_PNG001110");
	sBufArr.Add("IDB_PNG001111");
	sBufArr.Add("IDB_PNG010000");
	sBufArr.Add("IDB_PNG010001");
	sBufArr.Add("IDB_PNG010010");
	sBufArr.Add("IDB_PNG010011");
	sBufArr.Add("IDB_PNG010100");
	sBufArr.Add("IDB_PNG010101");
	sBufArr.Add("IDB_PNG010110");
	sBufArr.Add("IDB_PNG010111");
	sBufArr.Add("IDB_PNG011000");	
	sBufArr.Add("IDB_PNG011001");
	sBufArr.Add("IDB_PNG011010");
	sBufArr.Add("IDB_PNG011011");
	sBufArr.Add("IDB_PNG011100");
	sBufArr.Add("IDB_PNG011101");
	sBufArr.Add("IDB_PNG011110");
	sBufArr.Add("IDB_PNG011111");
	sBufArr.Add("IDB_PNG100000");
	sBufArr.Add("IDB_PNG100001");
	sBufArr.Add("IDB_PNG100010");
	sBufArr.Add("IDB_PNG100011");
	sBufArr.Add("IDB_PNG100100");
	sBufArr.Add("IDB_PNG100101");
	sBufArr.Add("IDB_PNG100110");
	sBufArr.Add("IDB_PNG100111");
	sBufArr.Add("IDB_PNG101000");
	sBufArr.Add("IDB_PNG101001");
	sBufArr.Add("IDB_PNG101010");
	sBufArr.Add("IDB_PNG101011");
	sBufArr.Add("IDB_PNG101100");
	sBufArr.Add("IDB_PNG101101");
	sBufArr.Add("IDB_PNG101110");
	sBufArr.Add("IDB_PNG101111");
	sBufArr.Add("IDB_PNG110000");
	sBufArr.Add("IDB_PNG110001");
	sBufArr.Add("IDB_PNG110010");
	sBufArr.Add("IDB_PNG110011");
	sBufArr.Add("IDB_PNG110100");
	sBufArr.Add("IDB_PNG110101");
	sBufArr.Add("IDB_PNG110110");
	sBufArr.Add("IDB_PNG110111");
	sBufArr.Add("IDB_PNG111000");
	sBufArr.Add("IDB_PNG111001");
	sBufArr.Add("IDB_PNG111010");
	sBufArr.Add("IDB_PNG111011");
	sBufArr.Add("IDB_PNG111100");
	sBufArr.Add("IDB_PNG111101");
	sBufArr.Add("IDB_PNG111110");
	sBufArr.Add("IDB_PNG111111");

	int k=0;
	for (i=0;i<sBufArr.GetSize();i++)
	{
		cb = new CGdiPlusBitmapResource;
		cb->Load(sBufArr.GetAt(i), _T("PNG"));
		int iMask = 0;
		for (k=7;k<sBufArr.GetAt(i).GetLength();k++)
		{
			iMask<<=1;
			CString sBuf;
			sBuf.Format("%c",sBufArr.GetAt(i).GetAt(k));
			iMask+=atoi(sBuf);
		}
		m_mibiWaterBtimaps.insert(make_pair(iMask,cb));
	}
	sBufArr.RemoveAll();
	sBufArr.Add("IDB_PNGB000011");
	sBufArr.Add("IDB_PNGB001001");
	sBufArr.Add("IDB_PNGB001010");
	sBufArr.Add("IDB_PNGB010001");
	sBufArr.Add("IDB_PNGB010010");
	sBufArr.Add("IDB_PNGB011000");
	sBufArr.Add("IDB_PNGB011011");

	sBufArr.Add("IDB_PNGB000101");
	sBufArr.Add("IDB_PNGB010100");
	sBufArr.Add("IDB_PNGB010101");
	sBufArr.Add("IDB_PNGB100010");
	sBufArr.Add("IDB_PNGB100100");
	sBufArr.Add("IDB_PNGB101000");
	sBufArr.Add("IDB_PNGB101010");
	sBufArr.Add("IDB_PNGB111111");


	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB000011"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE000011,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB001001"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE001001,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB001010"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE001010,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB010001"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE010001,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB010010"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE010010,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB011000"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE011000,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB011011"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE011011,cb));

	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB000101"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE000101,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB010100"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE010100,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB010101"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE010101,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB100010"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE100010,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB100100"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE100100,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB101000"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE101000,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB101010"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE101010,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGB111111"), _T("PNG")); m_mibiBridgeBitmaps.insert(make_pair(MODE_BRIDGE111111,cb));


	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGRECRUIT"),		_T("PNG")); m_mibiUnits.insert(make_pair(MODE_RECRUIT    ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGMUSQUETIER"),	_T("PNG")); m_mibiUnits.insert(make_pair(MODE_MUSQUETIER,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGHUSSAR"),		_T("PNG")); m_mibiUnits.insert(make_pair(MODE_HUSSAR     ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGGRENADIER"),	_T("PNG")); m_mibiUnits.insert(make_pair(MODE_GRENADIER  ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGGAUBICA"),		_T("PNG")); m_mibiUnits.insert(make_pair(MODE_GAUBICA    ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGEGER"),		_T("PNG")); m_mibiUnits.insert(make_pair(MODE_EGER       ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGDRAGOON"),		_T("PNG")); m_mibiUnits.insert(make_pair(MODE_DRAGOON    ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGCUIRASSIER"),	_T("PNG")); m_mibiUnits.insert(make_pair(MODE_CUIRASSIER ,cb));
	cb = new CGdiPlusBitmapResource; cb->Load(_T("IDB_PNGCANNON"),		_T("PNG")); m_mibiUnits.insert(make_pair(MODE_CANNON     ,cb));


	m_pEmpty = new CGdiPlusBitmapResource; 
	m_pEmpty->Load(_T("IDB_EMPTY"), _T("PNG"));
}


BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

//	ShowPane(&m_wndProperties,!m_wndProperties.IsVisible(),FALSE,TRUE);

	UpdateMDITabbedBarsIcons();
}
