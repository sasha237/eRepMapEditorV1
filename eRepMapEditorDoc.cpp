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

// eRepMapEditorDoc.cpp : implementation of the CeRepMapEditorDoc class
//

#include "stdafx.h"
#include "eRepMapEditor.h"

#include "eRepMapEditorDoc.h"
#include "MainFrm.h"
#include "eRepMapEditorView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeRepMapEditorDoc

IMPLEMENT_DYNCREATE(CeRepMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CeRepMapEditorDoc, CDocument)
	ON_COMMAND(ID_BRIDGE, &CeRepMapEditorDoc::OnBridge)
	ON_COMMAND(ID_BRIDGE001001, &CeRepMapEditorDoc::OnBridge001001)
	ON_COMMAND(ID_BRIDGE001010, &CeRepMapEditorDoc::OnBridge001010)
	ON_COMMAND(ID_BRIDGE010001, &CeRepMapEditorDoc::OnBridge010001)
	ON_COMMAND(ID_BRIDGE010010, &CeRepMapEditorDoc::OnBridge010010)
	ON_COMMAND(ID_BRIDGE011000, &CeRepMapEditorDoc::OnBridge011000)
	ON_COMMAND(ID_BRIDGE011011, &CeRepMapEditorDoc::OnBridge011011)
	ON_COMMAND(ID_BRIDGE000011, &CeRepMapEditorDoc::OnBridge000011)

	ON_COMMAND(ID_BRIDGE000101, &CeRepMapEditorDoc::OnBridge000101)
	ON_COMMAND(ID_BRIDGE010100, &CeRepMapEditorDoc::OnBridge010100)
	ON_COMMAND(ID_BRIDGE010101, &CeRepMapEditorDoc::OnBridge010101)
	ON_COMMAND(ID_BRIDGE100010, &CeRepMapEditorDoc::OnBridge100010)
	ON_COMMAND(ID_BRIDGE100100, &CeRepMapEditorDoc::OnBridge100100)
	ON_COMMAND(ID_BRIDGE101000, &CeRepMapEditorDoc::OnBridge101000)
	ON_COMMAND(ID_BRIDGE101010, &CeRepMapEditorDoc::OnBridge101010)
	ON_COMMAND(ID_BRIDGE111111, &CeRepMapEditorDoc::OnBridge111111)

	ON_UPDATE_COMMAND_UI(ID_BRIDGE, &CeRepMapEditorDoc::OnUpdateBridge)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE001001, &CeRepMapEditorDoc::OnUpdateBridge001001)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE001010, &CeRepMapEditorDoc::OnUpdateBridge001010)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE010001, &CeRepMapEditorDoc::OnUpdateBridge010001)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE010010, &CeRepMapEditorDoc::OnUpdateBridge010010)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE011000, &CeRepMapEditorDoc::OnUpdateBridge011000)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE011011, &CeRepMapEditorDoc::OnUpdateBridge011011)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE000011, &CeRepMapEditorDoc::OnUpdateBridge000011)

	ON_UPDATE_COMMAND_UI(ID_BRIDGE000101, &CeRepMapEditorDoc::OnUpdateBridge000101)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE010100, &CeRepMapEditorDoc::OnUpdateBridge010100)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE010101, &CeRepMapEditorDoc::OnUpdateBridge010101)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE100010, &CeRepMapEditorDoc::OnUpdateBridge100010)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE100100, &CeRepMapEditorDoc::OnUpdateBridge100100)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE101000, &CeRepMapEditorDoc::OnUpdateBridge101000)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE101010, &CeRepMapEditorDoc::OnUpdateBridge101010)
	ON_UPDATE_COMMAND_UI(ID_BRIDGE111111, &CeRepMapEditorDoc::OnUpdateBridge111111)

	ON_COMMAND(ID_FOREST, &CeRepMapEditorDoc::OnForest)
	ON_UPDATE_COMMAND_UI(ID_FOREST, &CeRepMapEditorDoc::OnUpdateForest)
	ON_COMMAND(ID_HILL, &CeRepMapEditorDoc::OnHill)
	ON_UPDATE_COMMAND_UI(ID_HILL, &CeRepMapEditorDoc::OnUpdateHill)
	ON_COMMAND(ID_MOUNTAIN, &CeRepMapEditorDoc::OnMountain)
	ON_UPDATE_COMMAND_UI(ID_MOUNTAIN, &CeRepMapEditorDoc::OnUpdateMountain)
	ON_COMMAND(ID_PLAIN, &CeRepMapEditorDoc::OnPlain)
	ON_UPDATE_COMMAND_UI(ID_PLAIN, &CeRepMapEditorDoc::OnUpdatePlain)
	ON_COMMAND(ID_WATER, &CeRepMapEditorDoc::OnWater)
	ON_UPDATE_COMMAND_UI(ID_WATER, &CeRepMapEditorDoc::OnUpdateWater)
	ON_COMMAND(ID_CURSOR_ELEMENT, &CeRepMapEditorDoc::OnCursorElement)
	ON_UPDATE_COMMAND_UI(ID_CURSOR_ELEMENT, &CeRepMapEditorDoc::OnUpdateCursorElement)
	ON_COMMAND(ID_RESIZE_SIZE, &CeRepMapEditorDoc::OnResizeElement)
	ON_UPDATE_COMMAND_UI(ID_RESIZE_SIZE, &CeRepMapEditorDoc::OnUpdateResizeElement)
	ON_UPDATE_COMMAND_UI(ID_WIDTH, &CeRepMapEditorDoc::OnUpdateWidth)
	ON_UPDATE_COMMAND_UI(ID_HEIGHT, &CeRepMapEditorDoc::OnUpdateHeight)

	ON_COMMAND(ID_BIG_CITY  				, &CeRepMapEditorDoc::OnBigCity)
	ON_COMMAND(ID_D1        				, &CeRepMapEditorDoc::OnDefence1)
	ON_COMMAND(ID_D2        				, &CeRepMapEditorDoc::OnDefence2)
	ON_COMMAND(ID_D3        				, &CeRepMapEditorDoc::OnDefence3)
	ON_COMMAND(ID_D4        				, &CeRepMapEditorDoc::OnDefence4)
	ON_COMMAND(ID_D5        				, &CeRepMapEditorDoc::OnDefence5)
	ON_COMMAND(ID_H1        				, &CeRepMapEditorDoc::OnHospital1)
	ON_COMMAND(ID_H2        				, &CeRepMapEditorDoc::OnHospital2)
	ON_COMMAND(ID_H3        				, &CeRepMapEditorDoc::OnHospital3)
	ON_COMMAND(ID_H4        				, &CeRepMapEditorDoc::OnHospital4)
	ON_COMMAND(ID_H5        				, &CeRepMapEditorDoc::OnHospital5)
	ON_COMMAND(ID_SMALL_CITY				, &CeRepMapEditorDoc::OnSmallCity)
	ON_COMMAND(ID_ZOOMIN_SCALE				, &CeRepMapEditorDoc::OnZoomIn)
	ON_COMMAND(ID_ZOOMOUT_SCALE				, &CeRepMapEditorDoc::OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_BIG_CITY  		, &CeRepMapEditorDoc::OnUpdateBigCity)
	ON_UPDATE_COMMAND_UI(ID_D1        		, &CeRepMapEditorDoc::OnUpdateDefence1)
	ON_UPDATE_COMMAND_UI(ID_D2        		, &CeRepMapEditorDoc::OnUpdateDefence2)
	ON_UPDATE_COMMAND_UI(ID_D3        		, &CeRepMapEditorDoc::OnUpdateDefence3)
	ON_UPDATE_COMMAND_UI(ID_D4        		, &CeRepMapEditorDoc::OnUpdateDefence4)
	ON_UPDATE_COMMAND_UI(ID_D5        		, &CeRepMapEditorDoc::OnUpdateDefence5)
	ON_UPDATE_COMMAND_UI(ID_H1        		, &CeRepMapEditorDoc::OnUpdateHospital1)
	ON_UPDATE_COMMAND_UI(ID_H2        		, &CeRepMapEditorDoc::OnUpdateHospital2)
	ON_UPDATE_COMMAND_UI(ID_H3        		, &CeRepMapEditorDoc::OnUpdateHospital3)
	ON_UPDATE_COMMAND_UI(ID_H4        		, &CeRepMapEditorDoc::OnUpdateHospital4)
	ON_UPDATE_COMMAND_UI(ID_H5        		, &CeRepMapEditorDoc::OnUpdateHospital5)
	ON_UPDATE_COMMAND_UI(ID_SMALL_CITY		, &CeRepMapEditorDoc::OnUpdateSmallCity)
	ON_UPDATE_COMMAND_UI(ID_ZOOMIN_SCALE	, &CeRepMapEditorDoc::OnUpdateZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOMOUT_SCALE	, &CeRepMapEditorDoc::OnUpdateZoomOut)


	ON_COMMAND(ID_RIBBON_SHOW_NUMBERS, &CeRepMapEditorDoc::OnRibbonShowNumbers)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_SHOW_NUMBERS, &CeRepMapEditorDoc::OnUpdateRibbonShowNumbers)
	ON_COMMAND(ID_HOSPITALS, &CeRepMapEditorDoc::OnHospitals)
	ON_UPDATE_COMMAND_UI(ID_HOSPITALS, &CeRepMapEditorDoc::OnUpdateHospitals)
	ON_COMMAND(ID_DEFENCES, &CeRepMapEditorDoc::OnDefences)
	ON_UPDATE_COMMAND_UI(ID_DEFENCES, &CeRepMapEditorDoc::OnUpdateDefences)
END_MESSAGE_MAP()


// CeRepMapEditorDoc construction/destruction

CeRepMapEditorDoc::CeRepMapEditorDoc()
{
	m_iMode = MODE_CURSOR;
	m_scale = 1;
	m_bShowNumbers = true;
}

CeRepMapEditorDoc::~CeRepMapEditorDoc()
{
	ClearMap();
}

BOOL CeRepMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return FALSE;

	ClearMap();
	int i,j;
	m_piiSize.first = m_piiSize.second = 10;
	for(i=0;i<m_piiSize.first;i++)
		for(j=0;j<m_piiSize.second;j++)
		{
			piiPair pp = make_pair(i,j);
			CMapItem* item = new CMapItem;
			item->m_piiIndex = pp;
			item->m_iType = MODE_PLAIN;
			item->m_iSubType = 0;
			item->m_iBuilding = 0;
			m_Elements.insert(make_pair(pp,item));
		}
	CalcNeibs();
	CString sBuf;
	sBuf.Format(_T("%d"),m_piiSize.first);
	pFrame->m_WEdit->SetEditText(sBuf);
	sBuf.Format(_T("%d"),m_piiSize.second);
	pFrame->m_HEdit->SetEditText(sBuf);
	m_scale = 1;
	sBuf.Format(_T("%d %%"),int(m_scale*100));
	pFrame->m_SEdit->SetEditText(sBuf);

	return TRUE;
}




// CeRepMapEditorDoc serialization

void CeRepMapEditorDoc::Serialize(CArchive& ar)
{
	mpiimiMapIt it;
	int i;
	if (ar.IsStoring())
	{
		ar<<m_piiSize.first<<m_piiSize.second<<m_Elements.size();
		forr(it,m_Elements)
		{
			ar<<it->first.first<<it->first.second;
			ar<<it->second->m_iType<<it->second->m_iSubType<<it->second->m_iBuilding;
		}
	}
	else
	{
		ClearMap();
		ar>>m_piiSize.first>>m_piiSize.second>>i;
		while (i!=m_Elements.size())
		{
			piiPair pp;
			CMapItem* item = new CMapItem;
			ar>>pp.first>>pp.second;
			item->m_piiIndex = pp;
			ar>>item->m_iType>>item->m_iSubType>>item->m_iBuilding;
			m_Elements.insert(make_pair(pp,item));
		}
		CalcNeibs();
	}
}

void CeRepMapEditorDoc::ClearMap()
{
	mpiimiMapIt it;
	forr(it,m_Elements)
		delete it->second;
	m_Elements.clear();
}
// CeRepMapEditorDoc diagnostics

#ifdef _DEBUG
void CeRepMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CeRepMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CeRepMapEditorDoc commands

void CeRepMapEditorDoc::OnBridge()
{
	
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	if(m_iMode==MODE_BRIDGE001001) {m_iMode = MODE_BRIDGE001010; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE001010) {m_iMode = MODE_BRIDGE010001; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE010001) {m_iMode = MODE_BRIDGE010010; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE010010) {m_iMode = MODE_BRIDGE011000; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE011000) {m_iMode = MODE_BRIDGE011011; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE011011) {m_iMode = MODE_BRIDGE000011; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE000011) {m_iMode = MODE_BRIDGE000101; pFrame->m_BBridges->Redraw();return;}
														 
	if(m_iMode==MODE_BRIDGE000101) {m_iMode = MODE_BRIDGE010100; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE010100) {m_iMode = MODE_BRIDGE010101; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE010101) {m_iMode = MODE_BRIDGE100010; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE100010) {m_iMode = MODE_BRIDGE100100; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE100100) {m_iMode = MODE_BRIDGE101000; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE101000) {m_iMode = MODE_BRIDGE101010; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE101010) {m_iMode = MODE_BRIDGE111111; pFrame->m_BBridges->Redraw();return;}
	if(m_iMode==MODE_BRIDGE111111) {m_iMode = MODE_BRIDGE001001; pFrame->m_BBridges->Redraw();return;}

	m_iMode = MODE_BRIDGE001001;
}

void CeRepMapEditorDoc::OnUpdateBridge(CCmdUI *pCmdUI)
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;
	BOOL b = m_iMode == MODE_BRIDGE001001||
		m_iMode == MODE_BRIDGE001010||
		m_iMode == MODE_BRIDGE010001||
		m_iMode == MODE_BRIDGE010010||
		m_iMode == MODE_BRIDGE011000||
		m_iMode == MODE_BRIDGE011011||
		m_iMode == MODE_BRIDGE000011||
		m_iMode == MODE_BRIDGE000101||
		m_iMode == MODE_BRIDGE010100||
		m_iMode == MODE_BRIDGE010101||
		m_iMode == MODE_BRIDGE100010||
		m_iMode == MODE_BRIDGE100100||
		m_iMode == MODE_BRIDGE101000||
		m_iMode == MODE_BRIDGE101010||
		m_iMode == MODE_BRIDGE111111;
	pCmdUI->SetCheck(b);
	pFrame->m_BpGrp->SetVisible(b);
	pFrame->m_wndStatusBar.RecalcLayout();
	pFrame->m_wndStatusBar.RedrawWindow();

 	if (m_iMode>=MODE_BRIDGE001001&&m_iMode<=MODE_BRIDGE111111)
 		pFrame->m_BBridges->SetImageIndex(m_iMode-MODE_BRIDGE001001+9,TRUE);
 	else
 		pFrame->m_BBridges->SetImageIndex(1,TRUE);
	pFrame->m_wndRibbonBar.RecalcLayout();
	pFrame->m_wndRibbonBar.RedrawWindow();
	
}

void CeRepMapEditorDoc::OnForest()
{
	m_iMode = MODE_FOREST;
}

void CeRepMapEditorDoc::OnUpdateForest(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_iMode == MODE_FOREST);
}

void CeRepMapEditorDoc::OnHill()
{
	m_iMode = MODE_HILL;
}

void CeRepMapEditorDoc::OnUpdateHill(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_iMode == MODE_HILL);
}

void CeRepMapEditorDoc::OnMountain()
{
	m_iMode = MODE_MOUNTAIN;
}

void CeRepMapEditorDoc::OnUpdateMountain(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_iMode == MODE_MOUNTAIN);
}

void CeRepMapEditorDoc::OnPlain()
{
	m_iMode = MODE_PLAIN;
}

void CeRepMapEditorDoc::OnUpdatePlain(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_iMode == MODE_PLAIN);
}

void CeRepMapEditorDoc::OnWater()
{
	m_iMode = MODE_WATER;
}

void CeRepMapEditorDoc::OnUpdateWater(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_iMode == MODE_WATER);
}

void CeRepMapEditorDoc::OnCursorElement()
{
	m_iMode = MODE_CURSOR;
}

void CeRepMapEditorDoc::OnUpdateCursorElement(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_iMode == MODE_CURSOR);
}
void  CeRepMapEditorDoc::OnResizeElement()
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;
	CeRepMapEditorView* pView = dynamic_cast<CeRepMapEditorView*>(GetRoutingView());
	if (pView)
	{
		pView->ClearDraw();
		pView->SetScrollPos(SB_VERT,0,FALSE);
		pView->SetScrollPos(SB_VERT,0,FALSE);
	}
	mpiimiMapIt it;
	int i,j;
 	m_piiSize.first = atoi(pFrame->m_WEdit->GetEditText());
 	m_piiSize.second = atoi(pFrame->m_HEdit->GetEditText());
	
	for(it=m_Elements.begin();it!=m_Elements.end();)
	{
		if(it->first.first>=m_piiSize.first)
		{
			delete it->second;
			it = m_Elements.erase(it);
			continue;
		}
		if(it->first.second>=m_piiSize.second)
		{
			delete it->second;
			it = m_Elements.erase(it);
			continue;
		}
		++it;
	}
	
	for(i=0;i<m_piiSize.first;i++)
		for(j=0;j<m_piiSize.second;j++)
		{
			piiPair pp = make_pair(i,j);
			if (m_Elements.find(pp)!=m_Elements.end())
				continue;
			CMapItem* item = new CMapItem;
			item->m_piiIndex = pp;
			item->m_iType = MODE_PLAIN;
			item->m_iSubType = 0;
			item->m_iBuilding = 0;
			m_Elements.insert(make_pair(pp,item));
		}
		CalcNeibs();
		UpdateAllViews(NULL);
}
void  CeRepMapEditorDoc::OnUpdateResizeElement(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void  CeRepMapEditorDoc::OnZoomIn()
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;
	if(m_scale==MAX_SCALE)
		return;
	CString sBuf;
	m_scale+=0.1;
	if (m_scale>MAX_SCALE)
		m_scale = MAX_SCALE;
	sBuf.Format("%0.0f %%",m_scale*100);
	pFrame->m_SEdit->SetEditText(sBuf);
	pFrame->m_SEdit->Redraw();
	UpdateAllViews(NULL);
}
void  CeRepMapEditorDoc::OnUpdateZoomIn(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void  CeRepMapEditorDoc::OnZoomOut()
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;
	if(m_scale==MIN_SCALE)
		return;

	CString sBuf;
	m_scale-=0.1;
	if (m_scale<MIN_SCALE)
		m_scale = MIN_SCALE;
	sBuf.Format("%0.0f %%",m_scale*100);
	pFrame->m_SEdit->SetEditText(sBuf);
	pFrame->m_SEdit->Redraw();
	UpdateAllViews(NULL);
}
void  CeRepMapEditorDoc::OnUpdateZoomOut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CeRepMapEditorDoc::OnUpdateWidth(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CeRepMapEditorDoc::OnUpdateHeight(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CeRepMapEditorDoc::OnCloseDocument()
{
	CDocument::OnCloseDocument();

	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	CString sBuf;
	sBuf.Format(_T("%d"),m_piiSize.first);
	pFrame->m_WEdit->SetEditText(sBuf);
	sBuf.Format(_T("%d"),m_piiSize.second);
	pFrame->m_HEdit->SetEditText(sBuf);

}

BOOL CeRepMapEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return CDocument::OnSaveDocument(lpszPathName);
}

BOOL CeRepMapEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return TRUE;
	
	m_scale = 1;
	CString sBuf;
	sBuf.Format(_T("%d"),m_piiSize.first);
	pFrame->m_WEdit->SetEditText(sBuf);
	sBuf.Format(_T("%d"),m_piiSize.second);
	pFrame->m_HEdit->SetEditText(sBuf);
	sBuf.Format(_T("%d %%"),int(m_scale*100));
	pFrame->m_SEdit->SetEditText(sBuf);

	return TRUE;
}

void CeRepMapEditorDoc::CalcNeibs()
{
	mpiimiMapIt it;
	mpiimiMapIt bufit;
	forr(it,m_Elements)
	{
		piiPair pp;
		it->second->m_vmiNeibs.resize(6,NULL);
		it->second->m_vmiNeibs[0]=NULL;
		it->second->m_vmiNeibs[1]=NULL;
		it->second->m_vmiNeibs[2]=NULL;
		it->second->m_vmiNeibs[3]=NULL;
		it->second->m_vmiNeibs[4]=NULL;
		it->second->m_vmiNeibs[5]=NULL;

		//++
		pp = make_pair(it->first.first,it->first.second-1);
		ifnend(bufit,m_Elements,pp)
			it->second->m_vmiNeibs[0]=bufit->second;

		//++
		pp = make_pair(it->first.first+1,  it->first.second+it->first.first%2-1);
		ifnend(bufit,m_Elements,pp)
			it->second->m_vmiNeibs[1]=bufit->second;

		//++		
		pp = make_pair(it->first.first+1,  it->first.second+it->first.first%2);
		ifnend(bufit,m_Elements,pp)
			it->second->m_vmiNeibs[2]=bufit->second;

		//++
		pp = make_pair(it->first.first,it->first.second+1);
		ifnend(bufit,m_Elements,pp)
			it->second->m_vmiNeibs[3]=bufit->second;

		//++
		pp = make_pair(it->first.first-1,  it->first.second+it->first.first%2);
		ifnend(bufit,m_Elements,pp)
			it->second->m_vmiNeibs[4]=bufit->second;

		//++
		pp = make_pair(it->first.first-1,  it->first.second+it->first.first%2-1);
		ifnend(bufit,m_Elements,pp)
			it->second->m_vmiNeibs[5]=bufit->second;
	}
}

void CeRepMapEditorDoc::OnBridge001001(){	m_iMode = MODE_BRIDGE001001;}
void CeRepMapEditorDoc::OnBridge001010(){	m_iMode = MODE_BRIDGE001010;}
void CeRepMapEditorDoc::OnBridge010001(){	m_iMode = MODE_BRIDGE010001;}
void CeRepMapEditorDoc::OnBridge010010(){	m_iMode = MODE_BRIDGE010010;}
void CeRepMapEditorDoc::OnBridge011000(){	m_iMode = MODE_BRIDGE011000;}
void CeRepMapEditorDoc::OnBridge011011(){	m_iMode = MODE_BRIDGE011011;}
void CeRepMapEditorDoc::OnBridge000011(){	m_iMode = MODE_BRIDGE000011;}

void CeRepMapEditorDoc::OnBridge000101(){	m_iMode = MODE_BRIDGE000101;}
void CeRepMapEditorDoc::OnBridge010100(){	m_iMode = MODE_BRIDGE010100;}
void CeRepMapEditorDoc::OnBridge010101(){	m_iMode = MODE_BRIDGE010101;}
void CeRepMapEditorDoc::OnBridge100010(){	m_iMode = MODE_BRIDGE100010;}
void CeRepMapEditorDoc::OnBridge100100(){	m_iMode = MODE_BRIDGE100100;}
void CeRepMapEditorDoc::OnBridge101000(){	m_iMode = MODE_BRIDGE101000;}
void CeRepMapEditorDoc::OnBridge101010(){	m_iMode = MODE_BRIDGE101010;}
void CeRepMapEditorDoc::OnBridge111111(){	m_iMode = MODE_BRIDGE111111;}

void CeRepMapEditorDoc::OnUpdateBridge001001(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE001001);}
void CeRepMapEditorDoc::OnUpdateBridge001010(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE001010);}
void CeRepMapEditorDoc::OnUpdateBridge010001(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE010001);}
void CeRepMapEditorDoc::OnUpdateBridge010010(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE010010);}
void CeRepMapEditorDoc::OnUpdateBridge011000(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE011000);}
void CeRepMapEditorDoc::OnUpdateBridge011011(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE011011);}
void CeRepMapEditorDoc::OnUpdateBridge000011(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE000011);}

void CeRepMapEditorDoc::OnUpdateBridge000101(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE000101);}
void CeRepMapEditorDoc::OnUpdateBridge010100(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE010100);}
void CeRepMapEditorDoc::OnUpdateBridge010101(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE010101);}
void CeRepMapEditorDoc::OnUpdateBridge100010(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE100010);}
void CeRepMapEditorDoc::OnUpdateBridge100100(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE100100);}
void CeRepMapEditorDoc::OnUpdateBridge101000(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE101000);}
void CeRepMapEditorDoc::OnUpdateBridge101010(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE101010);}
void CeRepMapEditorDoc::OnUpdateBridge111111(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BRIDGE111111);}

void CeRepMapEditorDoc::OnBigCity(){	m_iMode = MODE_BIG_CITY	;}
void CeRepMapEditorDoc::OnDefence1(){	m_iMode = MODE_D1			;}
void CeRepMapEditorDoc::OnDefence2(){	m_iMode = MODE_D2			;}
void CeRepMapEditorDoc::OnDefence3(){	m_iMode = MODE_D3			;}
void CeRepMapEditorDoc::OnDefence4(){	m_iMode = MODE_D4			;}
void CeRepMapEditorDoc::OnDefence5(){	m_iMode = MODE_D5			;}
void CeRepMapEditorDoc::OnHospital1(){	m_iMode = MODE_H1			;}
void CeRepMapEditorDoc::OnHospital2(){	m_iMode = MODE_H2			;}
void CeRepMapEditorDoc::OnHospital3(){	m_iMode = MODE_H3			;}
void CeRepMapEditorDoc::OnHospital4(){	m_iMode = MODE_H4			;}
void CeRepMapEditorDoc::OnHospital5(){	m_iMode = MODE_H5			;}
void CeRepMapEditorDoc::OnSmallCity(){	m_iMode = MODE_SMALL_CITY	;}
void CeRepMapEditorDoc::OnUpdateBigCity(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_BIG_CITY	);}
void CeRepMapEditorDoc::OnUpdateDefence1(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_D1			);}
void CeRepMapEditorDoc::OnUpdateDefence2(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_D2			);}
void CeRepMapEditorDoc::OnUpdateDefence3(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_D3			);}
void CeRepMapEditorDoc::OnUpdateDefence4(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_D4			);}
void CeRepMapEditorDoc::OnUpdateDefence5(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_D5			);}
void CeRepMapEditorDoc::OnUpdateHospital1(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_H1			);}
void CeRepMapEditorDoc::OnUpdateHospital2(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_H2			);}
void CeRepMapEditorDoc::OnUpdateHospital3(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_H3			);}
void CeRepMapEditorDoc::OnUpdateHospital4(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_H4			);}
void CeRepMapEditorDoc::OnUpdateHospital5(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_H5			);}
void CeRepMapEditorDoc::OnUpdateSmallCity(CCmdUI *pCmdUI){	pCmdUI->SetCheck(m_iMode == MODE_SMALL_CITY	);}
void CeRepMapEditorDoc::OnRibbonShowNumbers()
{
	m_bShowNumbers=!m_bShowNumbers;
	UpdateAllViews(NULL);
}

void CeRepMapEditorDoc::OnUpdateRibbonShowNumbers(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowNumbers);
}

void CeRepMapEditorDoc::OnHospitals()
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	if(m_iMode==MODE_H1) {m_iMode = MODE_H2; pFrame->m_Hospitals->Redraw();return;}
	if(m_iMode==MODE_H2) {m_iMode = MODE_H3; pFrame->m_Hospitals->Redraw();return;}
	if(m_iMode==MODE_H3) {m_iMode = MODE_H4; pFrame->m_Hospitals->Redraw();return;}
	if(m_iMode==MODE_H4) {m_iMode = MODE_H5; pFrame->m_Hospitals->Redraw();return;}
	if(m_iMode==MODE_H5) {m_iMode = MODE_H1; pFrame->m_Hospitals->Redraw();return;}

	m_iMode = MODE_H1;
}

void CeRepMapEditorDoc::OnUpdateHospitals(CCmdUI *pCmdUI)
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;
	BOOL b = m_iMode == MODE_H1||
		m_iMode == MODE_H2||
		m_iMode == MODE_H3||
		m_iMode == MODE_H4||
		m_iMode == MODE_H5;
	pCmdUI->SetCheck(b);
	pFrame->m_HGrp->SetVisible(b);
	pFrame->m_wndStatusBar.RecalcLayout();
	pFrame->m_wndStatusBar.RedrawWindow();

	if (m_iMode>=MODE_H1&&m_iMode<=MODE_H5)
		pFrame->m_Hospitals->SetImageIndex(m_iMode-MODE_H1+29,TRUE);
	else
		pFrame->m_Hospitals->SetImageIndex(29,TRUE);
	pFrame->m_wndRibbonBar.RecalcLayout();
	pFrame->m_wndRibbonBar.RedrawWindow();
}

void CeRepMapEditorDoc::OnDefences()
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	if(m_iMode==MODE_D1) {m_iMode = MODE_D2; pFrame->m_Defences->Redraw();return;}
	if(m_iMode==MODE_D2) {m_iMode = MODE_D3; pFrame->m_Defences->Redraw();return;}
	if(m_iMode==MODE_D3) {m_iMode = MODE_D4; pFrame->m_Defences->Redraw();return;}
	if(m_iMode==MODE_D4) {m_iMode = MODE_D5; pFrame->m_Defences->Redraw();return;}
	if(m_iMode==MODE_D5) {m_iMode = MODE_D1; pFrame->m_Defences->Redraw();return;}
 
	m_iMode = MODE_D1;
}

void CeRepMapEditorDoc::OnUpdateDefences(CCmdUI *pCmdUI)
{
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;
	BOOL b = m_iMode == MODE_D1||
		m_iMode == MODE_D2||
		m_iMode == MODE_D3||
		m_iMode == MODE_D4||
		m_iMode == MODE_D5;
	pCmdUI->SetCheck(b);
	pFrame->m_DGrp->SetVisible(b);
	pFrame->m_wndStatusBar.RecalcLayout();
	pFrame->m_wndStatusBar.RedrawWindow();

	if (m_iMode>=MODE_D1&&m_iMode<=MODE_D5)
		pFrame->m_Defences->SetImageIndex(m_iMode-MODE_D1+34,TRUE);
	else
		pFrame->m_Defences->SetImageIndex(34,TRUE);
	pFrame->m_wndRibbonBar.RecalcLayout();
	pFrame->m_wndRibbonBar.RedrawWindow();

}
