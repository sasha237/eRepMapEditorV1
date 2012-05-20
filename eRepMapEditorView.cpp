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

// eRepMapEditorView.cpp : implementation of the CeRepMapEditorView class
//

#include "stdafx.h"
#include "eRepMapEditor.h"

#include "eRepMapEditorDoc.h"
#include "eRepMapEditorView.h"
#include "MainFrm.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif


// CeRepMapEditorView

IMPLEMENT_DYNCREATE(CeRepMapEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CeRepMapEditorView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CeRepMapEditorView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_SAVE_AS_PICTURE, &CeRepMapEditorView::OnFileSaveAsPicture)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CeRepMapEditorView construction/destruction

CeRepMapEditorView::CeRepMapEditorView()
{
	m_BackBuffer = NULL;
	m_Temp = NULL;
}

CeRepMapEditorView::~CeRepMapEditorView()
{
	ClearDraw();
}

void CeRepMapEditorView::ClearDraw()
{
	if (m_Temp)
	{
		delete m_Temp;
		m_Temp = NULL;
	}
	if (m_BackBuffer)
	{
		delete m_BackBuffer;
		m_BackBuffer = NULL;
	}
}
BOOL CeRepMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CeRepMapEditorView drawing

void CeRepMapEditorView::DrawAll()
{
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int dx, dy;
	CClientDC dc(this);
	Gdiplus::Graphics graphics(dc);
	CRect rt;
	CRect rt1;
	GetWindowRect(&rt);
	GetWindowRect(&rt1);

	rt.right=rt.left+rt.Width()/pDoc->m_scale;
	rt.bottom=rt.top+rt.Height()/pDoc->m_scale;

	
	dy = GetScrollPos(SB_VERT)/pDoc->m_scale;
	dx = GetScrollPos(SB_HORZ)/pDoc->m_scale;

	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	
	
  	if (m_BackBuffer->GetWidth()*pDoc->m_scale<rt1.right)
  		graphics.FillRectangle(&whiteBrush,m_BackBuffer->GetWidth()*pDoc->m_scale,0,rt1.right-m_BackBuffer->GetWidth()*pDoc->m_scale,rt1.Height());
 	if (m_BackBuffer->GetHeight()*pDoc->m_scale<rt1.bottom)
 		graphics.FillRectangle(&whiteBrush,0,m_BackBuffer->GetHeight()*pDoc->m_scale,rt1.Width(),rt1.bottom-m_BackBuffer->GetHeight()*pDoc->m_scale);

	graphics.ScaleTransform(pDoc->m_scale,pDoc->m_scale);
	graphics.DrawImage(m_BackBuffer, 0, 0, dx, dy, 
		rt.right, rt.bottom, UnitPixel);

}

void CeRepMapEditorView::OnDraw(CDC* pDC)
{
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	mpiimiMapIt itEls;
	mibiMapIt it;
	int dx, dy;

	int x;
	int y;

	CClientDC dc(this);
	bool bNew = false;
	Gdiplus::Graphics graphics(dc);
	CRect rt;
	GetWindowRect(&rt);

	rt.right=rt.left+rt.Width()/pDoc->m_scale;
	rt.bottom=rt.top+rt.Height()/pDoc->m_scale;

	CSize sizeTotal;
	sizeTotal.cx = STEP_X*pDoc->m_piiSize.first+100;
	sizeTotal.cy = STEP_Y*pDoc->m_piiSize.second+100;
	sizeTotal.cx*=pDoc->m_scale;
	sizeTotal.cy*=pDoc->m_scale;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
	if (!m_BackBuffer)
	{
		m_BackBuffer = new Bitmap(STEP_X*pDoc->m_piiSize.first+100, STEP_Y*pDoc->m_piiSize.second+100);
		bNew = true;
	}
	
	graphics.ScaleTransform(pDoc->m_scale,pDoc->m_scale);
	dy = GetScrollPos(SB_VERT)/pDoc->m_scale;
	dx = GetScrollPos(SB_HORZ)/pDoc->m_scale;

	if (!bNew)
	{
		DrawAll();
	}

	m_Coords.clear();
	if(bNew)
	{
		m_Temp = new Graphics(m_BackBuffer);
		SolidBrush whiteBrush(Color(255, 255, 255, 255));
		m_Temp->FillRectangle(&whiteBrush,0,0,STEP_X*pDoc->m_piiSize.first+100,STEP_Y*pDoc->m_piiSize.second+100);
	}


	for(itEls=pDoc->m_Elements.begin();itEls!=pDoc->m_Elements.end();++itEls)
	{
		CGdiPlusBitmapResource *pBmp = NULL;;
		ifend(it,pFrame->m_mibiElBtimaps,itEls->second->m_iType)
			continue;
		pBmp = it->second;
		if(itEls->second->m_iType==MODE_WATER)
		{
			CMapItem *pItem = itEls->second;
			int iMask = 0;
			int k;
			for (k=0;k<pItem->m_vmiNeibs.size();k++)
			{
				iMask<<=1;
				iMask+=(!pItem->m_vmiNeibs[k]||pItem->m_vmiNeibs[k]->m_iType==MODE_WATER)?1:0;
			}
			ifnend(it,pFrame->m_mibiWaterBtimaps,iMask)
			{
				pBmp = it->second;
				itEls->second->m_iSubType = iMask;
			}
		}
		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;
		if (!bNew)
		{
			if(x+STEP_X<0||x-STEP_X>rt.right||
				y+STEP_Y<0||y-STEP_Y>rt.bottom)
				continue;
		}


//		m_Temp->DrawImage(*pFrame->m_pEmpty,x,y-1);

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

		if (bNew)
			m_Temp->DrawImage(*pBmp, x, y);

		x*=pDoc->m_scale;
		y*=pDoc->m_scale;

		m_Coords.insert(make_pair(make_pair(STEP_X*itEls->first.first+84-dx,STEP_Y*itEls->first.second+50+(itEls->first.first%2?42:0)+42-dy),itEls->first));
		
		if (bNew)
		{		
			if(itEls->second->m_iType==MODE_WATER)
			{
				ifnend(it,pFrame->m_mibiBridgeBitmaps,itEls->second->m_iBuilding)
				{
					pBmp = it->second;
					
					x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50-dx;
					y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

					if(x+STEP_X*2>0&&x-STEP_X*2<rt.right*pDoc->m_scale&&
						y+STEP_Y*2>0&&y-STEP_Y*2<rt.bottom*pDoc->m_scale || bNew)
					{
						m_Temp->DrawImage(*pBmp, x, y);
					}
				}
			}
			x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
			y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

			if (pDoc->m_bShowNumbers)
			{
				WCHAR wss[1024];
				CString ss;
				int iLen;
				ss.Format("%d, %d",itEls->first.first+1,itEls->first.second+1);
				mbstowcs(wss,ss,ss.GetLength()+1);
				iLen = ss.GetLength();

				RectF bounds(x+STEP_X*2/3-iLen*8/2, y, iLen*8, 15);

				LinearGradientBrush brush(bounds, Color(255, 255, 255, 255), Color(255, 255, 255, 255), 
					LinearGradientModeBackwardDiagonal); 

				StringFormat format;
				format.SetAlignment(StringAlignmentCenter);
				format.SetLineAlignment(StringAlignmentNear);
				Gdiplus::Font font(L"Arial", 8, FontStyleBold);

				LinearGradientBrush blbrush(bounds, Color(75, 255, 0, 0), Color(75, 0, 0, 255), 
					LinearGradientModeBackwardDiagonal); 

				m_Temp->FillRectangle(&blbrush, bounds);


				m_Temp->DrawString(wss, -1, &font, bounds, &format, &brush);		
			}	
		}
	}

	if (bNew)
	{
		CString sBuf;

		sBuf.Format("!%d!\n",dy);
		TRACE(sBuf);

		graphics.DrawImage(m_BackBuffer, 0, 0, 0, 0, 
			rt.right, rt.bottom, UnitPixel);
	}
}


// CeRepMapEditorView printing


void CeRepMapEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CeRepMapEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CeRepMapEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CeRepMapEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CeRepMapEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CeRepMapEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CeRepMapEditorView diagnostics

#ifdef _DEBUG
void CeRepMapEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CeRepMapEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CeRepMapEditorDoc* CeRepMapEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CeRepMapEditorDoc)));
	return (CeRepMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CeRepMapEditorView message handlers

void CeRepMapEditorView::OnMouseMove(UINT nFlags, CPoint point)
{

//	CScrollView::OnMouseMove(nFlags, point);
	HitDraw(nFlags, point);

	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CeRepMapEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	CString sBuf;
	sBuf.Format("%d",nFlags);
	TRACE(sBuf);
	if((nFlags&MK_CONTROL))		
	{
		CeRepMapEditorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return TRUE;
		CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		if (!pFrame)
			return TRUE;


		if (zDelta>0)
			pDoc->m_scale+=0.1;
		if (zDelta<0)
			pDoc->m_scale-=0.1;
		if (pDoc->m_scale<0.1)
			pDoc->m_scale = 0.1;
		if (pDoc->m_scale>10)
			pDoc->m_scale = 10;

		sBuf.Format("%0.0f %%",pDoc->m_scale*100);
		pFrame->m_SEdit->SetEditText(sBuf);

		Invalidate();
		return TRUE;
	}
	else
		return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CeRepMapEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	HitDraw(MK_LBUTTON, point);

	CScrollView::OnLButtonDown(nFlags, point);
}

void CeRepMapEditorView::RegenUpper(piiPair pp)
{
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	mpiimiMapIt itEls;
	mibiMapIt it;


	CRect rt;
	GetWindowRect(&rt);
	rt.right=rt.left+rt.Width()/pDoc->m_scale;
	rt.bottom=rt.top+rt.Height()/pDoc->m_scale;



	int dx, dy;
	dy = GetScrollPos(SB_VERT)/pDoc->m_scale;
	dx = GetScrollPos(SB_HORZ)/pDoc->m_scale;

	int x;
	int y;
	int i;
	int j;
	int x1;
	int y1;

	ifend(itEls,pDoc->m_Elements,pp)
		return;

	pDoc->SetModifiedFlag(TRUE);

	x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
	y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

	x-=STEP_X/4;
	y-=STEP_Y/4;

	CRect rtt;
	
	rtt.left = x;
	rtt.top = y;
	rtt.right = x+pFrame->m_pEmpty->m_pBitmap->GetWidth()+STEP_X/4;
	rtt.bottom = y+pFrame->m_pEmpty->m_pBitmap->GetHeight()+STEP_Y/4;

	CClientDC dc(this);
	CRgn rgn;
	x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
	y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

	x1 = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50;
	y1 = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);


	CPoint pps[18];
	PointF ppf[18];
	pps[0].x = x1+STEP_X*1/3-2; pps[0].y = y1-STEP_Y;
	pps[1].x = x1+STEP_X*3/3;   pps[1].y = y1-STEP_Y;
	pps[2].x = x1+STEP_X*4/3;   pps[2].y = y1-STEP_Y/2-1;
	pps[3].x = x1+STEP_X*6/3;   pps[3].y = y1-STEP_Y/2-1;
	pps[4].x = x1+STEP_X*7/3-1; pps[4].y = y1;
	pps[5].x = x1+STEP_X*6/3-1; pps[5].y = y1+STEP_Y/2;
	pps[6].x = x1+STEP_X*7/3-1; pps[6].y = y1+STEP_Y;
	pps[7].x = x1+STEP_X*6/3-1; pps[7].y = y1+STEP_Y*3/2;
	pps[8].x = x1+STEP_X*4/3-1; pps[8].y = y1+STEP_Y*3/2;
	pps[9].x = x1+STEP_X*3/3-1; pps[9].y = y1+STEP_Y*2;
	pps[10].x =x1+STEP_X*1/3-2; pps[10].y =y1+STEP_Y*2;
	pps[11].x =x1-2;			pps[11].y =y1+STEP_Y*3/2;
	pps[12].x =x1-STEP_X*2/3-2; pps[12].y =y1+STEP_Y*3/2;
	pps[13].x =x1-STEP_X*3/3-2; pps[13].y =y1+STEP_Y;
	pps[14].x =x1-STEP_X*2/3-2; pps[14].y =y1+STEP_Y/2;
	pps[15].x =x1-STEP_X*3/3-2; pps[15].y =y1;
	pps[16].x =x1-STEP_X*2/3-2; pps[16].y =y1-STEP_Y/2-1;
	pps[17].x =x1-2;			pps[17].y =y1-STEP_Y/2-1;
	
	for (i=0;i<18;i++)
	{
		ppf[i].X=pps[i].x;
		ppf[i].Y=pps[i].y;
		pps[i].x=(pps[i].x-dx)*pDoc->m_scale;
		pps[i].y=(pps[i].y-dy)*pDoc->m_scale;
	}

	GraphicsPath gPath;
	gPath.AddPolygon(ppf,18);
	rgn.CreatePolygonRgn(pps,18,WINDING);
 	dc.SelectClipRgn(&rgn);
	Gdiplus::Graphics graphics(dc);
	Bitmap backBuffer(rt.right, rt.bottom, &graphics);
	Graphics temp(&backBuffer);
	graphics.ScaleTransform(pDoc->m_scale,pDoc->m_scale);
	
  	SolidBrush whiteBrush(Color(255, 255, 255, 255));
  	temp.FillRectangle(&whiteBrush,x-STEP_X*2,y-STEP_Y*2,pFrame->m_pEmpty->m_pBitmap->GetWidth()+STEP_X*4,pFrame->m_pEmpty->m_pBitmap->GetHeight()+STEP_Y*4);
	m_Temp->FillPath(&whiteBrush,&gPath);
	m_Temp->SetClip(&gPath);
//	m_Temp->FillRectangle(&whiteBrush,x-STEP_X*2,y-STEP_Y*2,pFrame->m_pEmpty->m_pBitmap->GetWidth()+STEP_X*4,pFrame->m_pEmpty->m_pBitmap->GetHeight()+STEP_Y*4);

	mpiimiMap pElemets;
	pElemets.insert(make_pair(itEls->first,itEls->second));
	for (i=0;i<itEls->second->m_vmiNeibs.size();++i)
	{
		CMapItem * pItem = itEls->second->m_vmiNeibs[i];
		if(!pItem)
			continue;
		pElemets.insert(make_pair(pItem->m_piiIndex,pItem));
		for(j=0;j<pItem->m_vmiNeibs.size();j++)
		{
			if (!pItem->m_vmiNeibs[j])
				continue;
			pElemets.insert(make_pair(pItem->m_vmiNeibs[j]->m_piiIndex,pItem->m_vmiNeibs[j]));
		}
	}

	for(itEls=pElemets.begin();itEls!=pElemets.end();++itEls)
	{
		CGdiPlusBitmapResource *pBmp = NULL;;
		ifend(it,pFrame->m_mibiElBtimaps,itEls->second->m_iType)
			continue;
		pBmp = it->second;
		if(itEls->second->m_iType==MODE_WATER)
		{
			CMapItem *pItem = itEls->second;
			int iMask = 0;
			int k;
			for (k=0;k<pItem->m_vmiNeibs.size();k++)
			{
				iMask<<=1;
				iMask+=(!pItem->m_vmiNeibs[k]||pItem->m_vmiNeibs[k]->m_iType==MODE_WATER)?1:0;
			}
			ifnend(it,pFrame->m_mibiWaterBtimaps,iMask)
			{
				pBmp = it->second;
				itEls->second->m_iSubType = iMask;
			}
		}

		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

		if(x+STEP_X*2<0||x-STEP_X*2>rt.right||
			y+STEP_Y*2<0||y-STEP_Y*2>rt.bottom)
			continue;

//		temp.DrawImage(*pFrame->m_pEmpty,x,y-1);

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50;
		y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);

		
 		temp.DrawImage(*pBmp, x, y);
 		m_Temp->DrawImage(*pBmp, x1, y1);

		x*=pDoc->m_scale;
		y*=pDoc->m_scale;

		m_Coords.insert(make_pair(make_pair(STEP_X*itEls->first.first+84-dx,STEP_Y*itEls->first.second+50+(itEls->first.first%2?42:0)+42-dy),itEls->first));


		if(itEls->second->m_iType==MODE_WATER)
		{
			ifnend(it,pFrame->m_mibiBridgeBitmaps,itEls->second->m_iBuilding)
			{
				pBmp = it->second;

				x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50-dx;
				y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

				x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50;
				y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);

				if(x+STEP_X*2>0&&x-STEP_X*2<rt.right*pDoc->m_scale&&
					y+STEP_Y*2>0&&y-STEP_Y*2<rt.bottom*pDoc->m_scale)
				{
					temp.DrawImage(*pBmp, x, y);
				}
				m_Temp->DrawImage(*pBmp, x1, y1);
			}
		}


		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50;
		y1 = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);


		if (pDoc->m_bShowNumbers)
		{
			WCHAR wss[1024];
			CString ss;
			int iLen;
			ss.Format("%d, %d",itEls->first.first+1,itEls->first.second+1);
			mbstowcs(wss,ss,ss.GetLength()+1);
			iLen = ss.GetLength();

			RectF bounds(x+STEP_X*2/3-iLen*8/2, y, iLen*8, 15);
			RectF bounds1(x1+STEP_X*2/3-iLen*8/2, y1, iLen*8, 15);

			LinearGradientBrush brush(bounds, Color(255, 255, 255, 255), Color(255, 255, 255, 255), 
				LinearGradientModeBackwardDiagonal); 

			LinearGradientBrush brush1(bounds1, Color(255, 255, 255, 255), Color(255, 255, 255, 255), 
				LinearGradientModeBackwardDiagonal); 

			StringFormat format;
			format.SetAlignment(StringAlignmentCenter);
			format.SetLineAlignment(StringAlignmentNear);
			Gdiplus::Font font(L"Arial", 8, FontStyleBold);

			LinearGradientBrush blbrush(bounds, Color(75, 255, 0, 0), Color(75, 0, 0, 255), 
				LinearGradientModeBackwardDiagonal); 

			temp.FillRectangle(&blbrush, bounds);
			temp.DrawString(wss, -1, &font, bounds, &format, &brush);		
			m_Temp->FillRectangle(&blbrush, bounds1);
			m_Temp->DrawString(wss, -1, &font, bounds1, &format, &brush1);		
		}
	}
	
	graphics.DrawImage(&backBuffer, 0, 0, 0, 0, 
		rt.right, rt.bottom, UnitPixel);
}

BOOL CeRepMapEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
// 	switch(GetDocument()->m_iMode)
// 	{
// 	case MODE_CURSOR:
// 		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
// 		return TRUE;
// 	case MODE_PLAIN:
// 		break;
// 	case MODE_BRIDGE:
// 		break;
// 	case MODE_HILL:
// 		break;
// 	case MODE_WATER:
// 		break;
// 	case MODE_MOUNTAIN:
// 		break;
// 	case MODE_FOREST:
// 		break;
// 	}

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}


void CeRepMapEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view

	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	sizeTotal.cx = STEP_X*pDoc->m_piiSize.first+100;
 	sizeTotal.cy = STEP_Y*pDoc->m_piiSize.second+100;
	sizeTotal.cx*=pDoc->m_scale;
	sizeTotal.cy*=pDoc->m_scale;
 	SetScrollSizes(MM_TEXT, sizeTotal);
	ShowScrollBar(SB_BOTH); 
}

void CeRepMapEditorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CeRepMapEditorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CeRepMapEditorView::DrawElement(piiPair pp)
{
	mpiimiMapIt itEls;
	mibiMapIt itEl;
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	mibiMapIt it;
	CClientDC dc(this);
	Gdiplus::Graphics graphics(dc);
	graphics.ScaleTransform(pDoc->m_scale,pDoc->m_scale);
	ifend(itEls,pDoc->m_Elements,pp)
		return;

	
	int dx, dy;
	int x;
	int y;
	int x1;
	int y1;

	dy = GetScrollPos(SB_VERT)/pDoc->m_scale;
	dx = GetScrollPos(SB_HORZ)/pDoc->m_scale;

	CGdiPlusBitmapResource *pBmp = NULL;;
	if( pDoc->m_iMode!=MODE_BRIDGE001001&&
		pDoc->m_iMode!=MODE_BRIDGE001010&&
		pDoc->m_iMode!=MODE_BRIDGE010001&&
		pDoc->m_iMode!=MODE_BRIDGE010010&&
		pDoc->m_iMode!=MODE_BRIDGE011000&&
		pDoc->m_iMode!=MODE_BRIDGE011011&&
		pDoc->m_iMode!=MODE_BRIDGE000011&&
		pDoc->m_iMode!=MODE_BRIDGE000101&&
		pDoc->m_iMode!=MODE_BRIDGE010100&&
		pDoc->m_iMode!=MODE_BRIDGE010101&&
		pDoc->m_iMode!=MODE_BRIDGE100010&&
		pDoc->m_iMode!=MODE_BRIDGE100100&&
		pDoc->m_iMode!=MODE_BRIDGE101000&&
		pDoc->m_iMode!=MODE_BRIDGE101010&&
		pDoc->m_iMode!=MODE_BRIDGE111111)
	{
		ifend(itEl,pFrame->m_mibiElBtimaps,pDoc->m_iMode)
			return;

		if(itEls->second->m_iType == pDoc->m_iMode||
			itEls->second->m_iSubType == pDoc->m_iMode||
			itEls->second->m_iBuilding == pDoc->m_iMode)
			return;
		pBmp = itEl->second;

		if(pDoc->m_iMode==MODE_WATER)
		{
			CMapItem *pItem = itEls->second;
			int iMask = 0;
			int k;
			for (k=0;k<pItem->m_vmiNeibs.size();k++)
			{
				iMask<<=1;
				iMask+=(!pItem->m_vmiNeibs[k]||pItem->m_vmiNeibs[k]->m_iType==MODE_WATER)?1:0;
			}
			ifnend(it,pFrame->m_mibiWaterBtimaps,iMask)
			{
				pBmp = it->second;
				itEls->second->m_iSubType = iMask;
			}
		}
		else
		{
			itEls->second->m_iBuilding = NULL;
		}

		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;


//		graphics.DrawImage(*pFrame->m_pEmpty,x,y-1);

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50;
		y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);


		graphics.DrawImage(*pBmp, x, y);
		m_Temp->DrawImage(*pBmp, x1, y1);

		itEls->second->m_iType = pDoc->m_iMode;

		x*=pDoc->m_scale;
		y*=pDoc->m_scale;

		m_Coords.insert(make_pair(make_pair(STEP_X*itEls->first.first+84-dx,STEP_Y*itEls->first.second+50+(itEls->first.first%2?42:0)+42-dy),itEls->first));
	}

	if((itEls->second->m_iType==MODE_WATER)&&
	  ( pDoc->m_iMode==MODE_BRIDGE001001||
		pDoc->m_iMode==MODE_BRIDGE001010||
		pDoc->m_iMode==MODE_BRIDGE010001||
		pDoc->m_iMode==MODE_BRIDGE010010||
		pDoc->m_iMode==MODE_BRIDGE011000||
		pDoc->m_iMode==MODE_BRIDGE011011||
		pDoc->m_iMode==MODE_BRIDGE000011||
		pDoc->m_iMode==MODE_BRIDGE000101||
		pDoc->m_iMode==MODE_BRIDGE010100||
		pDoc->m_iMode==MODE_BRIDGE010101||
		pDoc->m_iMode==MODE_BRIDGE100010||
		pDoc->m_iMode==MODE_BRIDGE100100||
		pDoc->m_iMode==MODE_BRIDGE101000||
		pDoc->m_iMode==MODE_BRIDGE101010||
		pDoc->m_iMode==MODE_BRIDGE111111))
	{
		ifnend(it,pFrame->m_mibiBridgeBitmaps,pDoc->m_iMode)
		{
			pBmp = it->second;
			x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50-dx;
			y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0)-dy;

			x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50;
			y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);

			graphics.DrawImage(*pBmp, x, y);
			m_Temp->DrawImage(*pBmp, x1, y1);
			itEls->second->m_iBuilding = pDoc->m_iMode;
		}
	}

	RegenUpper(pp);


}
void CeRepMapEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CScrollView::OnLButtonUp(nFlags, point);
}

void CeRepMapEditorView::OnActivateView(BOOL bActivate, CScrollView* pActivateView, CScrollView* pDeactiveView)
{
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	CString sBuf;
	sBuf.Format(_T("%d"),pDoc->m_piiSize.first);
	pFrame->m_WEdit->SetEditText(sBuf);
	sBuf.Format(_T("%d"),pDoc->m_piiSize.second);
	pFrame->m_HEdit->SetEditText(sBuf);
	
}

void CeRepMapEditorView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CSize sizeTotal;
	sizeTotal.cx = STEP_X*pDoc->m_piiSize.first+100;
	sizeTotal.cy = STEP_Y*pDoc->m_piiSize.second+100;
	sizeTotal.cx*=pDoc->m_scale;
	sizeTotal.cy*=pDoc->m_scale;
	SetScrollSizes(MM_TEXT, sizeTotal);
	Invalidate(TRUE);
}

void CeRepMapEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;				
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	
	if( pDoc->m_iMode==MODE_BRIDGE001001) {pDoc->m_iMode = MODE_BRIDGE001010;   OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE001010) {pDoc->m_iMode = MODE_BRIDGE010001;   OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE010001) {pDoc->m_iMode = MODE_BRIDGE010010;   OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE010010) {pDoc->m_iMode = MODE_BRIDGE011000;   OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE011000) {pDoc->m_iMode = MODE_BRIDGE011011;   OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE011011) {pDoc->m_iMode = MODE_BRIDGE000011;   OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE000011) { pDoc->m_iMode = MODE_BRIDGE000101;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}

	if( pDoc->m_iMode==MODE_BRIDGE000101) { pDoc->m_iMode = MODE_BRIDGE010100;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE010100) { pDoc->m_iMode = MODE_BRIDGE010101;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE010101) { pDoc->m_iMode = MODE_BRIDGE100010;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE100010) { pDoc->m_iMode = MODE_BRIDGE100100;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE100100) { pDoc->m_iMode = MODE_BRIDGE101000;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE101000) { pDoc->m_iMode = MODE_BRIDGE101010;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE101010) { pDoc->m_iMode = MODE_BRIDGE111111;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}
	if( pDoc->m_iMode==MODE_BRIDGE111111) { pDoc->m_iMode = MODE_BRIDGE001001;  OnLButtonDown(nFlags, point);pFrame->m_BBridges->Redraw();return;}

	if(pDoc->m_iMode==MODE_H1) {pDoc->m_iMode = MODE_H2; pFrame->m_Hospitals->Redraw();return;}
	if(pDoc->m_iMode==MODE_H2) {pDoc->m_iMode = MODE_H3; pFrame->m_Hospitals->Redraw();return;}
	if(pDoc->m_iMode==MODE_H3) {pDoc->m_iMode = MODE_H4; pFrame->m_Hospitals->Redraw();return;}
	if(pDoc->m_iMode==MODE_H4) {pDoc->m_iMode = MODE_H5; pFrame->m_Hospitals->Redraw();return;}
	if(pDoc->m_iMode==MODE_H5) {pDoc->m_iMode = MODE_H1; pFrame->m_Hospitals->Redraw();return;}

	if(pDoc->m_iMode==MODE_D1) {pDoc->m_iMode = MODE_D2; pFrame->m_Defences->Redraw();return;}
	if(pDoc->m_iMode==MODE_D2) {pDoc->m_iMode = MODE_D3; pFrame->m_Defences->Redraw();return;}
	if(pDoc->m_iMode==MODE_D3) {pDoc->m_iMode = MODE_D4; pFrame->m_Defences->Redraw();return;}
	if(pDoc->m_iMode==MODE_D4) {pDoc->m_iMode = MODE_D5; pFrame->m_Defences->Redraw();return;}
	if(pDoc->m_iMode==MODE_D5) {pDoc->m_iMode = MODE_D1; pFrame->m_Defences->Redraw();return;}

	CScrollView::OnLButtonDblClk(nFlags, point);
}

BOOL CeRepMapEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	return CScrollView::OnEraseBkgnd(pDC);
}

void CeRepMapEditorView::HitDraw(UINT nFlags, CPoint point)
{
	
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	

	mpiipiiMapIt it;
	CMFCRibbonStatusBarPane* pBase = dynamic_cast<CMFCRibbonStatusBarPane*>(pFrame->m_wndStatusBar.GetExElement(0));

	double dMin;
	piiPair pp = m_Coords.begin()->second;
	int dx, dy;
	dy = GetScrollPos(SB_VERT)/pDoc->m_scale;
	dx = GetScrollPos(SB_HORZ)/pDoc->m_scale;
	it = m_Coords.begin();
	dx=dy=0;
	int x,y;
	piiPair ppCoords = it->first;
	x = point.x+dx;
	y = point.y+dy;
	ppCoords.first*=pDoc->m_scale;
	ppCoords.second*=pDoc->m_scale;
	dMin = (x-ppCoords.first)*(x-ppCoords.first)*0.64*0.64+
		(y-ppCoords.second)*(y-ppCoords.second);
	forr(it,m_Coords)
	{
		piiPair ppCoords = it->first;
		ppCoords.first*=pDoc->m_scale;
		ppCoords.second*=pDoc->m_scale;
		double dBuf = (x-ppCoords.first)*(x-ppCoords.first)*0.64*0.64+
			(y-ppCoords.second)*(y-ppCoords.second);
		if(dBuf<dMin)
		{
			dMin = dBuf;
			pp=it->second;
		}
	}
	if(nFlags & MK_LBUTTON)
		DrawElement(pp);
	if(nFlags & MK_RBUTTON)
	{
		int iOldMode = pDoc->m_iMode;

		mpiimiMapIt itEls;
		ifend(itEls,pDoc->m_Elements,pp)
			return;

		if( itEls->second->m_iBuilding<MODE_BRIDGE001001||
			itEls->second->m_iBuilding>MODE_BRIDGE111111)
		{
			pDoc->m_iMode = MODE_PLAIN;
			DrawElement(pp);
			pDoc->m_iMode = iOldMode;
		}
		else
		{
			pDoc->m_iMode = MODE_PLAIN;
			DrawElement(pp);
			pDoc->m_iMode = MODE_WATER;
			DrawElement(pp);
			pDoc->m_iMode = iOldMode;
		}
	}

	CString sBuf;
	sBuf.Format(_T("x=%d y=%d (%d,%d)"),point.x, point.y, pp.first+1, pp.second+1);
	TRACE(sBuf+_T("\n"));
	pBase->SetText(sBuf);
	pFrame->m_wndStatusBar.RecalcLayout();
	pFrame->m_wndStatusBar.RedrawWindow();

}

int CeRepMapEditorView::GetEncoderClsid(LPCWSTR lpFormat,CLSID * pClsid)
{
	UINT num = 0;
	UINT size = 0;
	ImageCodecInfo * pImageCodecInfo = NULL;

	GetImageEncodersSize(&num,&size);
	if(size == 0) return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL) return -1;

	GetImageEncoders(num,size,pImageCodecInfo);

	for(UINT j=0;j<num;++j)
	{
		if (!wcscmp(pImageCodecInfo[j].MimeType,lpFormat))
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1;
}

void CeRepMapEditorView::OnFileSaveAsPicture()
{
	CFileDialog dlg(FALSE,"jpg",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Файл изображений (*.jpg)|*.jpg|",this);
	if(dlg.DoModal()!=IDOK)
		return;
	CString sPath = dlg.GetPathName();
	CLSID jpgClsid;

	GetEncoderClsid(L"image/jpeg", &jpgClsid);

	CeRepMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (!pFrame)
		return;

	mpiimiMapIt itEls;
	mibiMapIt it;

	int x;
	int y;

	CClientDC dc(this);
	Gdiplus::Graphics graphics(dc);
	CRect rt;
	rt.top = 0;
	rt.left = 0;
	rt.right = pDoc->m_piiSize.first*STEP_X+100;
	rt.bottom = pDoc->m_piiSize.second*STEP_Y+100;

	Bitmap backBuffer(rt.right, rt.bottom, &graphics);
	Graphics temp(&backBuffer);

	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	temp.FillRectangle(&whiteBrush,rt.left,rt.top,rt.Width(),rt.Height());

	for(itEls=pDoc->m_Elements.begin();itEls!=pDoc->m_Elements.end();++itEls)
	{
		CGdiPlusBitmapResource *pBmp = NULL;;
		ifend(it,pFrame->m_mibiElBtimaps,itEls->second->m_iType)
			continue;
		pBmp = it->second;
		if(itEls->second->m_iType==MODE_WATER)
		{
			CMapItem *pItem = itEls->second;
			int iMask = 0;
			int k;
			for (k=0;k<pItem->m_vmiNeibs.size();k++)
			{
				iMask<<=1;
				iMask+=(!pItem->m_vmiNeibs[k]||pItem->m_vmiNeibs[k]->m_iType==MODE_WATER)?1:0;
			}
			ifnend(it,pFrame->m_mibiWaterBtimaps,iMask)
			{
				pBmp = it->second;
				itEls->second->m_iSubType = iMask;
			}
		}

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);

		temp.DrawImage(*pBmp, x, y);


		if(itEls->second->m_iType==MODE_WATER)
		{
			ifnend(it,pFrame->m_mibiBridgeBitmaps,itEls->second->m_iBuilding)
			{
				pBmp = it->second;

				x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()+50;
				y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()+50+(itEls->first.first%2?42:0);
				temp.DrawImage(*pBmp, x, y);
			}
		}
		if (pDoc->m_bShowNumbers)
		{
			WCHAR wss[1024];
			CString ss;
			int iLen;
			ss.Format("%d, %d",itEls->first.first+1,itEls->first.second+1);
			mbstowcs(wss,ss,ss.GetLength()+1);
			iLen = ss.GetLength();

			RectF bounds(x+STEP_X*2/3-iLen*8/2, y, iLen*8, 15);

			LinearGradientBrush brush(bounds, Color(255, 255, 255, 255), Color(255, 255, 255, 255), 
				LinearGradientModeBackwardDiagonal); 

			StringFormat format;
			format.SetAlignment(StringAlignmentCenter);
			format.SetLineAlignment(StringAlignmentNear);
			Gdiplus::Font font(L"Arial", 8, FontStyleBold);

			LinearGradientBrush blbrush(bounds, Color(75, 255, 0, 0), Color(75, 0, 0, 255), 
				LinearGradientModeBackwardDiagonal); 

			temp.FillRectangle(&blbrush, bounds);


			temp.DrawString(wss, -1, &font, bounds, &format, &brush);		
		}
	}
	WCHAR ss[1024];
	mbstowcs(ss,sPath,sPath.GetLength()+1);
	backBuffer.Save(ss,&jpgClsid);
}



void CeRepMapEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	HitDraw(MK_RBUTTON, point);	

	CScrollView::OnRButtonDown(nFlags, point);
}
