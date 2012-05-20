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

	m_bFilterOn = false;
	m_rgbFilter = RGB(255,255,255);

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
	sizeTotal.cx = STEP_X*pDoc->m_piiSize.first+100/STEP_CH_X;
	sizeTotal.cy = STEP_Y*pDoc->m_piiSize.second+100/STEP_CH_Y;
	sizeTotal.cx*=pDoc->m_scale;
	sizeTotal.cy*=pDoc->m_scale;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
	if (!m_BackBuffer)
	{
		m_BackBuffer = new Bitmap(STEP_X*pDoc->m_piiSize.first+100/STEP_CH_X, STEP_Y*pDoc->m_piiSize.second+100/STEP_CH_Y);
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
		CScrollView::OnEraseBkgnd(pDC);
		m_Temp = new Graphics(m_BackBuffer);
		SolidBrush whiteBrush(Color(255, 255, 255, 255));
		m_Temp->FillRectangle(&whiteBrush,0,0,STEP_X*pDoc->m_piiSize.first+100/STEP_CH_X,STEP_Y*pDoc->m_piiSize.second+100/STEP_CH_Y);
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
		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;
		if (!bNew)
		{
			if(x+STEP_X<0||x-STEP_X>rt.right||
				y+STEP_Y<0||y-STEP_Y>rt.bottom)
				continue;
		}


//		m_Temp->DrawImage(*pFrame->m_pEmpty,x,y-1);

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

		if (bNew)
			m_Temp->DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);

		x*=pDoc->m_scale;
		y*=pDoc->m_scale;

		m_Coords.insert(make_pair(make_pair(STEP_X*itEls->first.first+84/STEP_CH_X-dx,STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)+42/STEP_CH_Y-dy),itEls->first));
		
		if (bNew)
		{		
			if(itEls->second->m_iType==MODE_WATER)
			{
				ifnend(it,pFrame->m_mibiBridgeBitmaps,itEls->second->m_iBuilding)
				{
					pBmp = it->second;
					
					x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
					y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

					if(x+STEP_X*2>0&&x-STEP_X*2<rt.right*pDoc->m_scale&&
						y+STEP_Y*2>0&&y-STEP_Y*2<rt.bottom*pDoc->m_scale || bNew)
					{
						m_Temp->DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
					}
				}
			}
			x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
			y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

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

			if (itEls->second->m_rgbColor!=RGB(255,255,255))
			{
				int iXs[6];
				int iYs[6];

				x = STEP_X*itEls->first.first+STEP_X/2;
				y = STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);

				iXs[0] = x + STEP_X * 0 / 4 + 2; iYs[0] = y + STEP_Y * 0 / 2 + 0;
				iXs[1] = x + STEP_X * 5 / 8 + 8; iYs[1] = y + STEP_Y * 0 / 2 + 0;
				iXs[2] = x + STEP_X * 4 / 4 + 2; iYs[2] = y + STEP_Y * 1 / 2;
				iXs[3] = x + STEP_X * 5 / 8 + 8; iYs[3] = y + STEP_Y * 2 / 2;
				iXs[4] = x + STEP_X * 0 / 4 + 2; iYs[4] = y + STEP_Y * 2 / 2;
				iXs[5] = x - STEP_X * 1 / 4 - 12; iYs[5] = y + STEP_Y * 1 / 2; 

				PointF ppf[6];

				COLORREF rgb = itEls->second->m_rgbColor;
				SolidBrush colorBrush(Color(30,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));
				Pen colorPen(Color(255,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)),7);
				int i;
				for (i=0;i<6;i++)
				{
					ppf[i].X = iXs[i];
					ppf[i].Y = iYs[i];
				}

				m_Temp->DrawPolygon(&colorPen,ppf,6);
				m_Temp->FillPolygon(&colorBrush,ppf,6);
			}
			if (itEls->second->m_bHasUnit)
			{
				if (m_bFilterOn)
				{
					if (m_rgbFilter != RGB(255,255,255))
					{
						if(itEls->second->m_pUnitItem->m_rgbColor!=m_rgbFilter&&itEls->second->m_iType == MODE_FOREST)
							continue;
					}
					else
						if(itEls->second->m_iType == MODE_FOREST)
							continue;

				}
				ifnend(it,pFrame->m_mibiUnits,itEls->second->m_pUnitItem->m_iType)
				{
					pBmp = it->second;
					if (itEls->second->m_pUnitItem->m_bRotate)
					{
						pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
					}

					x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*2/3-dx;
					y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y+(itEls->first.first%2?STEP_Y/2:0)-dy;

					x-=2;
					Gdiplus::RectF bufRt(x+20,y,STEP_X-40,STEP_X);
					Gdiplus::RectF bufRt0 = bufRt;

					bufRt0.X-=5;
					bufRt0.Y+=15;
					bufRt0.Width+=10;
					bufRt0.Height-=30;

					COLORREF rgb = itEls->second->m_pUnitItem->m_rgbColor;
					SolidBrush colorBrush(Color(30,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));
					Pen colorPen(Color(255,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)),3);
					GraphicsPath gp1;
					Region oldReg;
					Region bufReg;

					WCHAR wsName[1024], wsCount[1024];
					CString sName = itEls->second->m_pUnitItem->m_sName;
					CString sCount;
					sCount.Format("%d", itEls->second->m_pUnitItem->m_iCount);
					mbstowcs(wsName,sName,sName.GetLength()+1);
					mbstowcs(wsCount,sCount,sCount.GetLength()+1);
					StringFormat format;
					format.SetAlignment(StringAlignmentCenter);
					format.SetLineAlignment(StringAlignmentCenter);
					Gdiplus::Font font(L"Arial", 10, FontStyleBold);

					SolidBrush fontBrush(Color(255, 255, 255, 255)); 

					gp1.AddRectangle(bufRt0);

					m_Temp->GetClip(&oldReg);
					m_Temp->GetClip(&bufReg);
					bufReg.Intersect(&gp1);
					m_Temp->SetClip(&bufReg);
					m_Temp->FillEllipse(&colorBrush,bufRt);
					m_Temp->DrawEllipse(&colorPen,bufRt);
					m_Temp->SetClip(&oldReg);
					RectF boundsName(x+20,y-15,STEP_X-40,30);
					RectF boundsCount(x+20,y+STEP_Y*3/4-15,STEP_X-40,30);
					DrawFillRoundRect(*m_Temp,colorPen,colorBrush,x+20,y-15,STEP_X-40,30,5);
					m_Temp->DrawString(wsName, -1, &font, boundsName, &format, &fontBrush);		
					DrawFillRoundRect(*m_Temp,colorPen,colorBrush,x+20,y+STEP_Y*3/4-15,STEP_X-40,30,5);
					m_Temp->DrawString(wsCount, -1, &font, boundsCount, &format, &fontBrush);		
					m_Temp->DrawImage(*pBmp, x+5, y,pBmp->m_pBitmap->GetWidth(),pBmp->m_pBitmap->GetHeight());
					if (itEls->second->m_pUnitItem->m_bRotate)
					{
						pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
					}

				}
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

	x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
	y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

	x-=STEP_X/4;
	y-=STEP_Y/4;

	CRect rtt;

	rtt.left = x;
	rtt.top = y;
	rtt.right = x+pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/4;
	rtt.bottom = y+pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y/4;

	CClientDC dc(this);
	CRgn rgn;
	x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
	y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

	x1 = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
	y1 = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);


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
	temp.FillRectangle(&whiteBrush,x-STEP_X*2,y-STEP_Y*2,pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*4,pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y*4);
	m_Temp->FillPath(&whiteBrush,&gPath);
	m_Temp->SetClip(&gPath);
	m_Temp->FillRectangle(&whiteBrush,x-STEP_X*2,y-STEP_Y*2,pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*4,pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y*4);
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

		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

		if(x+STEP_X*2<0||x-STEP_X*2>rt.right||
			y+STEP_Y*2<0||y-STEP_Y*2>rt.bottom)
			continue;

		//		temp.DrawImage(*pFrame->m_pEmpty,x,y-1);

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
		y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);


		temp.DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
		m_Temp->DrawImage(*pBmp, x1, y1,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);

		x*=pDoc->m_scale;
		y*=pDoc->m_scale;

		m_Coords.insert(make_pair(make_pair(STEP_X*itEls->first.first+84/STEP_CH_X-dx,STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)+42/STEP_CH_Y-dy),itEls->first));


		if(itEls->second->m_iType==MODE_WATER)
		{
			ifnend(it,pFrame->m_mibiBridgeBitmaps,itEls->second->m_iBuilding)
			{
				pBmp = it->second;

				x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
				y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

				x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
				y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);

				if(x+STEP_X*2>0&&x-STEP_X*2<rt.right*pDoc->m_scale&&
					y+STEP_Y*2>0&&y-STEP_Y*2<rt.bottom*pDoc->m_scale)
				{
					temp.DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
				}
				m_Temp->DrawImage(*pBmp, x1, y1,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
			}
		}


		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
		y1 = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);


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
		if (itEls->second->m_rgbColor!=RGB(255,255,255))
		{
			int iXs[6];
			int iYs[6];
			int iXs1[6];
			int iYs1[6];

			x = STEP_X*itEls->first.first+STEP_X/2-dx;
			y = STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

			x1 = STEP_X*itEls->first.first+STEP_X/2;
			y1 = STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);

			iXs[0] = x + STEP_X * 0 / 4 + 2; iYs[0] = y + STEP_Y * 0 / 2 + 0;
			iXs[1] = x + STEP_X * 5 / 8 + 8; iYs[1] = y + STEP_Y * 0 / 2 + 0;
			iXs[2] = x + STEP_X * 4 / 4 + 2; iYs[2] = y + STEP_Y * 1 / 2;
			iXs[3] = x + STEP_X * 5 / 8 + 8; iYs[3] = y + STEP_Y * 2 / 2;
			iXs[4] = x + STEP_X * 0 / 4 + 2; iYs[4] = y + STEP_Y * 2 / 2;
			iXs[5] = x - STEP_X * 1 / 4 - 12; iYs[5] = y + STEP_Y * 1 / 2; 

			iXs1[0] = x1 + STEP_X * 0 / 4 + 2; iYs1[0] = y1 + STEP_Y * 0 / 2 + 0;
			iXs1[1] = x1 + STEP_X * 5 / 8 + 8; iYs1[1] = y1 + STEP_Y * 0 / 2 + 0;
			iXs1[2] = x1 + STEP_X * 4 / 4 + 2; iYs1[2] = y1 + STEP_Y * 1 / 2;
			iXs1[3] = x1 + STEP_X * 5 / 8 + 8; iYs1[3] = y1 + STEP_Y * 2 / 2;
			iXs1[4] = x1 + STEP_X * 0 / 4 + 2; iYs1[4] = y1 + STEP_Y * 2 / 2;
			iXs1[5] = x1 - STEP_X * 1 / 4 - 12; iYs1[5] = y1 + STEP_Y * 1 / 2; 

			PointF ppf[6];
			PointF ppf1[6];

			COLORREF rgb = itEls->second->m_rgbColor;
			SolidBrush colorBrush(Color(30,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));
			Pen colorPen(Color(255,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)),7);

			for (i=0;i<6;i++)
			{
				ppf[i].X = iXs[i];
				ppf[i].Y = iYs[i];

				ppf1[i].X = iXs1[i];
				ppf1[i].Y = iYs1[i];
			}

 			temp.DrawPolygon(&colorPen,ppf,6);
 			temp.FillPolygon(&colorBrush,ppf,6);

			m_Temp->DrawPolygon(&colorPen,ppf1,6);
			m_Temp->FillPolygon(&colorBrush,ppf1,6);
		}

		if (itEls->second->m_bHasUnit)
		{
			ifnend(it,pFrame->m_mibiUnits,itEls->second->m_pUnitItem->m_iType)
			{
				pBmp = it->second;
				if (itEls->second->m_pUnitItem->m_bRotate)
				{
					pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
				}
				
				x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*2/3-dx;
				y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y+(itEls->first.first%2?STEP_Y/2:0)-dy;

				x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*2/3;
				y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y+(itEls->first.first%2?STEP_Y/2:0);
				x-=2;
				x1-=2;
				Gdiplus::RectF bufRt(x+20,y,STEP_X-40,STEP_X);
				Gdiplus::RectF bufRt1(x1+20,y1,STEP_X-40,STEP_X);
				Gdiplus::RectF bufRt0 = bufRt;
				Gdiplus::RectF bufRt01 = bufRt1;

				bufRt0.X-=5;
				bufRt0.Y+=15;
				bufRt0.Width+=10;
				bufRt0.Height-=30;

				bufRt01.X-=5;
				bufRt01.Y+=15;
				bufRt01.Width+=10;
				bufRt01.Height-=30;

				COLORREF rgb = itEls->second->m_pUnitItem->m_rgbColor;
				SolidBrush colorBrush(Color(30,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));
				Pen colorPen(Color(255,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)),3);
				GraphicsPath gp1, gp2;
				Region oldReg;
				Region bufReg;

				WCHAR wsName[1024], wsCount[1024];
				CString sName = itEls->second->m_pUnitItem->m_sName;
				CString sCount;
				sCount.Format("%d", itEls->second->m_pUnitItem->m_iCount);
				mbstowcs(wsName,sName,sName.GetLength()+1);
				mbstowcs(wsCount,sCount,sCount.GetLength()+1);
				StringFormat format;
				format.SetAlignment(StringAlignmentCenter);
				format.SetLineAlignment(StringAlignmentCenter);
				Gdiplus::Font font(L"Arial", 10, FontStyleBold);

				SolidBrush fontBrush(Color(255, 255, 255, 255)); 

				gp1.AddRectangle(bufRt0);
				gp2.AddRectangle(bufRt01);

				if(x+STEP_X*2>0&&x-STEP_X*2<rt.right*pDoc->m_scale&&
					y+STEP_Y*2>0&&y-STEP_Y*2<rt.bottom*pDoc->m_scale)
				{
					temp.GetClip(&oldReg);
					temp.GetClip(&bufReg);
					bufReg.Intersect(&gp1);
					temp.SetClip(&bufReg);
					temp.FillEllipse(&colorBrush,bufRt);
					temp.DrawEllipse(&colorPen,bufRt);
					temp.SetClip(&oldReg);
					RectF boundsName(x+20,y-15,STEP_X-40,30);
					RectF boundsCount(x+20,y+STEP_Y*3/4-15,STEP_X-40,30);
					DrawFillRoundRect(temp,colorPen,colorBrush,x+20,y-15,STEP_X-40,30,5);
					temp.DrawString(wsName, -1, &font, boundsName, &format, &fontBrush);		
					DrawFillRoundRect(temp,colorPen,colorBrush,x+20,y+STEP_Y*3/4-15,STEP_X-40,30,5);
					temp.DrawString(wsCount, -1, &font, boundsCount, &format, &fontBrush);		
					temp.DrawImage(*pBmp, x+5, y,pBmp->m_pBitmap->GetWidth(),pBmp->m_pBitmap->GetHeight());
				}
				m_Temp->GetClip(&oldReg);
				m_Temp->GetClip(&bufReg);
				bufReg.Intersect(&gp2);
				m_Temp->SetClip(&bufReg);
				m_Temp->FillEllipse(&colorBrush,bufRt1);
				m_Temp->DrawEllipse(&colorPen,bufRt1);
				m_Temp->SetClip(&oldReg);
				RectF boundsName(x1+20,y1-15,STEP_X-40,30);
				RectF boundsCount(x1+20,y1+STEP_Y*3/4-15,STEP_X-40,30);
				DrawFillRoundRect(*m_Temp,colorPen,colorBrush,x1+20,y1-15,STEP_X-40,30,5);
				m_Temp->DrawString(wsName, -1, &font, boundsName, &format, &fontBrush);		
				DrawFillRoundRect(*m_Temp,colorPen,colorBrush,x1+20,y1+STEP_Y*3/4-15,STEP_X-40,30,5);
				m_Temp->DrawString(wsCount, -1, &font, boundsCount, &format, &fontBrush);		
				m_Temp->DrawImage(*pBmp, x1+5, y1,pBmp->m_pBitmap->GetWidth(),pBmp->m_pBitmap->GetHeight());
				if (itEls->second->m_pUnitItem->m_bRotate)
				{
					pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
				}

			}
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
	sizeTotal.cx = STEP_X*pDoc->m_piiSize.first+100/STEP_CH_X;
 	sizeTotal.cy = STEP_Y*pDoc->m_piiSize.second+100/STEP_CH_Y;
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

void CeRepMapEditorView::DrawElement(piiPair pp, bool bDeleteUnit /*= false*/)
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
	if (pDoc->m_iMode == MODE_CURSOR)
	{
		pFrame->m_wndProperties.SetUnitItem(itEls->second->m_pUnitItem,this);
		return;
	}
	else
		pFrame->m_wndProperties.SetUnitItem(NULL,NULL);

	if (pDoc->m_iMode == MODE_AREAS)
	{
		itEls->second->m_rgbColor = RGB(255,255,255);
		if (!bDeleteUnit)
		{
			itEls->second->m_rgbColor = pFrame->m_wndProperties.GetColor();
		}
	}

	if (pDoc->m_iMode==MODE_RECRUIT	||
		pDoc->m_iMode==MODE_MUSQUETIER	||
		pDoc->m_iMode==MODE_HUSSAR		||
		pDoc->m_iMode==MODE_GRENADIER	||
		pDoc->m_iMode==MODE_GAUBICA	||
		pDoc->m_iMode==MODE_EGER		||
		pDoc->m_iMode==MODE_DRAGOON	||
		pDoc->m_iMode==MODE_CUIRASSIER	||
		pDoc->m_iMode==MODE_CANNON		)
	{
		ifend(itEl,pFrame->m_mibiUnits,pDoc->m_iMode)
			return;

		pBmp = itEl->second;

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*2/3-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y+(itEls->first.first%2?STEP_Y/2:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*2/3;
		y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y+(itEls->first.first%2?STEP_Y/2:0);

		if(itEls->second->m_bHasUnit)
		{
			itEls->second->m_bHasUnit = false;
			delete itEls->second->m_pUnitItem;
		}
		if (!bDeleteUnit)
		{
			CString sName = pFrame->m_wndProperties.GetName();
			int iCount = pFrame->m_wndProperties.GetCount();
			bool bRotate = pFrame->m_wndProperties.GetRotate();
			COLORREF rgbColor = pFrame->m_wndProperties.GetColor();

			itEls->second->m_bHasUnit = true;
			itEls->second->m_pUnitItem = new CUnitItem(sName,iCount,pDoc->m_iMode,bRotate,rgbColor,itEls->second);
			if (itEls->second->m_pUnitItem->m_bRotate)
			{
				pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
			}
			graphics.DrawImage(*pBmp, x+5-2, y,pBmp->m_pBitmap->GetWidth(),pBmp->m_pBitmap->GetHeight());
			m_Temp->DrawImage(*pBmp, x1+5-2, y1,pBmp->m_pBitmap->GetWidth(),pBmp->m_pBitmap->GetHeight());
			if (itEls->second->m_pUnitItem->m_bRotate)
			{
				pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
			}
		}
	}

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
		pDoc->m_iMode!=MODE_BRIDGE111111&&
		pDoc->m_iMode!=MODE_RECRUIT		&&
		pDoc->m_iMode!=MODE_MUSQUETIER	&&
		pDoc->m_iMode!=MODE_HUSSAR		&&
		pDoc->m_iMode!=MODE_GRENADIER	&&
		pDoc->m_iMode!=MODE_GAUBICA		&&
		pDoc->m_iMode!=MODE_EGER		&&
		pDoc->m_iMode!=MODE_DRAGOON		&&
		pDoc->m_iMode!=MODE_CUIRASSIER	&&
		pDoc->m_iMode!=MODE_CANNON		&&
		pDoc->m_iMode!=MODE_AREAS

		)
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

		x = STEP_X*(itEls->first.first+1)-pFrame->m_pEmpty->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pFrame->m_pEmpty->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;


		//		graphics.DrawImage(*pFrame->m_pEmpty,x,y-1);

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

		x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
		y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);


		graphics.DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
		m_Temp->DrawImage(*pBmp, x1, y1,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);

		itEls->second->m_iType = pDoc->m_iMode;

		x*=pDoc->m_scale;
		y*=pDoc->m_scale;


		m_Coords.insert(make_pair(make_pair(STEP_X*itEls->first.first+84/STEP_CH_X-dx,STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)+42/STEP_CH_Y-dy),itEls->first));
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
			x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2-dx;
			y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0)-dy;

			x1 = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
			y1 = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);

			graphics.DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
			m_Temp->DrawImage(*pBmp, x1, y1,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
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
	sizeTotal.cx = STEP_X*pDoc->m_piiSize.first+100/STEP_CH_X;
	sizeTotal.cy = STEP_Y*pDoc->m_piiSize.second+100/STEP_CH_Y;
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

	if(pDoc->m_iMode==MODE_RECRUIT		) {pDoc->m_iMode = MODE_MUSQUETIER	; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_MUSQUETIER	) {pDoc->m_iMode = MODE_HUSSAR		; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_HUSSAR		) {pDoc->m_iMode = MODE_GRENADIER	; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_GRENADIER	) {pDoc->m_iMode = MODE_GAUBICA		; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_GAUBICA		) {pDoc->m_iMode = MODE_EGER		; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_EGER			) {pDoc->m_iMode = MODE_DRAGOON		; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_DRAGOON		) {pDoc->m_iMode = MODE_CUIRASSIER	; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_CUIRASSIER	) {pDoc->m_iMode = MODE_CANNON		; pFrame->m_Units->Redraw();return;}
	if(pDoc->m_iMode==MODE_CANNON		) {pDoc->m_iMode = MODE_RECRUIT		; pFrame->m_Units->Redraw();return;}

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
	if (!m_Coords.size())
		return;
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
		if (pDoc->m_iMode == MODE_AREAS)
		{
			DrawElement(pp,true);
		}
		if (pDoc->m_iMode >= MODE_RECRUIT&& pDoc->m_iMode<=MODE_CANNON)
		{
			DrawElement(pp,true);
		}
		else
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
	rt.right = pDoc->m_piiSize.first*STEP_X+100/STEP_CH_X;
	rt.bottom = pDoc->m_piiSize.second*STEP_Y+100/STEP_CH_Y;

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

		x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
		y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);

		temp.DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);


		if(itEls->second->m_iType==MODE_WATER)
		{
			ifnend(it,pFrame->m_mibiBridgeBitmaps,itEls->second->m_iBuilding)
			{
				pBmp = it->second;

				x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X/2;
				y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);
				temp.DrawImage(*pBmp, x, y,pBmp->m_pBitmap->GetWidth()/STEP_CH_X,pBmp->m_pBitmap->GetHeight()/STEP_CH_Y);
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

		if (itEls->second->m_rgbColor!=RGB(255,255,255))
		{
			int iXs[6];
			int iYs[6];

			x = STEP_X*itEls->first.first+STEP_X/2;
			y = STEP_Y*itEls->first.second+STEP_X/2+(itEls->first.first%2?STEP_Y/2:0);


			iXs[0] = x + STEP_X * 0 / 4 + 2; iYs[0] = y + STEP_Y * 0 / 2 + 0;
			iXs[1] = x + STEP_X * 5 / 8 + 8; iYs[1] = y + STEP_Y * 0 / 2 + 0;
			iXs[2] = x + STEP_X * 4 / 4 + 2; iYs[2] = y + STEP_Y * 1 / 2;
			iXs[3] = x + STEP_X * 5 / 8 + 8; iYs[3] = y + STEP_Y * 2 / 2;
			iXs[4] = x + STEP_X * 0 / 4 + 2; iYs[4] = y + STEP_Y * 2 / 2;
			iXs[5] = x - STEP_X * 1 / 4 - 12; iYs[5] = y + STEP_Y * 1 / 2; 

			PointF ppf[6];

			COLORREF rgb = itEls->second->m_rgbColor;
			SolidBrush colorBrush(Color(30,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));
			Pen colorPen(Color(255,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)),7);
			int i;
			for (i=0;i<6;i++)
			{
				ppf[i].X = iXs[i];
				ppf[i].Y = iYs[i];
			}

			temp.DrawPolygon(&colorPen,ppf,6);
			temp.FillPolygon(&colorBrush,ppf,6);

		}

		if (itEls->second->m_bHasUnit)
		{
			ifnend(it,pFrame->m_mibiUnits,itEls->second->m_pUnitItem->m_iType)
			{
				pBmp = it->second;
				if (itEls->second->m_pUnitItem->m_bRotate)
				{
					pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
				}

				x = STEP_X*(itEls->first.first+1)-pBmp->m_pBitmap->GetWidth()/STEP_CH_X+STEP_X*2/3;
				y = STEP_Y*(itEls->first.second+1)-pBmp->m_pBitmap->GetHeight()/STEP_CH_Y+STEP_Y+(itEls->first.first%2?STEP_Y/2:0);

				x-=2;
				Gdiplus::RectF bufRt(x+20,y,STEP_X-40,STEP_X);
				Gdiplus::RectF bufRt0 = bufRt;

				bufRt0.X-=5;
				bufRt0.Y+=15;
				bufRt0.Width+=10;
				bufRt0.Height-=30;

				COLORREF rgb = itEls->second->m_pUnitItem->m_rgbColor;
				SolidBrush colorBrush(Color(30,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));
				Pen colorPen(Color(255,GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)),3);
				GraphicsPath gp1;
				Region oldReg;
				Region bufReg;

				WCHAR wsName[1024], wsCount[1024];
				CString sName = itEls->second->m_pUnitItem->m_sName;
				CString sCount;
				sCount.Format("%d", itEls->second->m_pUnitItem->m_iCount);
				mbstowcs(wsName,sName,sName.GetLength()+1);
				mbstowcs(wsCount,sCount,sCount.GetLength()+1);
				StringFormat format;
				format.SetAlignment(StringAlignmentCenter);
				format.SetLineAlignment(StringAlignmentCenter);
				Gdiplus::Font font(L"Arial", 10, FontStyleBold);

				SolidBrush fontBrush(Color(255, 255, 255, 255)); 

				gp1.AddRectangle(bufRt0);

				temp.GetClip(&oldReg);
				temp.GetClip(&bufReg);
				bufReg.Intersect(&gp1);
				temp.SetClip(&bufReg);
				temp.FillEllipse(&colorBrush,bufRt);
				temp.DrawEllipse(&colorPen,bufRt);
				temp.SetClip(&oldReg);
				RectF boundsName(x+20,y-15,STEP_X-40,30);
				RectF boundsCount(x+20,y+STEP_Y*3/4-15,STEP_X-40,30);
				DrawFillRoundRect(temp,colorPen,colorBrush,x+20,y-15,STEP_X-40,30,5);
				temp.DrawString(wsName, -1, &font, boundsName, &format, &fontBrush);		
				DrawFillRoundRect(temp,colorPen,colorBrush,x+20,y+STEP_Y*3/4-15,STEP_X-40,30,5);
				temp.DrawString(wsCount, -1, &font, boundsCount, &format, &fontBrush);		
				temp.DrawImage(*pBmp, x+5, y,pBmp->m_pBitmap->GetWidth(),pBmp->m_pBitmap->GetHeight());
				if (itEls->second->m_pUnitItem->m_bRotate)
				{
					pBmp->m_pBitmap->RotateFlip(RotateNoneFlipX);
				}

			}
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

void CeRepMapEditorView::DrawFillRoundRect(Graphics &g, Pen &p, SolidBrush& b, float X, float Y, float width, float height, float radius)
{
	GraphicsPath gp;
	gp.AddLine(X + radius, Y, X + width - (radius*2), Y);
	gp.AddArc(X + width - (radius*2), Y, radius*2, radius*2, 270, 90);
	gp.AddLine(X + width, Y + radius, X + width, Y + height - (radius*2));
	gp.AddArc(X + width - (radius*2), Y + height - (radius*2), radius*2, radius*2,0,90);
	gp.AddLine(X + width - (radius*2), Y + height, X + radius, Y + height);
	gp.AddArc(X, Y + height - (radius*2), radius*2, radius*2, 90, 90);
	gp.AddLine(X, Y + height - (radius*2), X, Y + radius);
	gp.AddArc(X, Y, radius*2, radius*2, 180, 90);
	gp.CloseFigure();
	g.FillPath(&b, &gp);
	g.DrawPath(&p, &gp);
	gp.Reset();
}

void CeRepMapEditorView::FilterByColorAndForest(bool bFilterOn, COLORREF rgb)
{
	m_bFilterOn = bFilterOn;
	m_rgbFilter = rgb;

	ClearDraw();
	GetDocument()->UpdateAllViews(NULL);
}