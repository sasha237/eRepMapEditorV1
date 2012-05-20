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

// eRepMapEditorView.h : interface of the CeRepMapEditorView class
//


#pragma once

#include "GdiPlusBitmap.h"
class CeRepMapEditorView : public CScrollView
{
protected: // create from serialization only
	CeRepMapEditorView();
	DECLARE_DYNCREATE(CeRepMapEditorView)

// Attributes
public:
	CeRepMapEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CeRepMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	mpiipiiMap m_Coords;
	
	void HitDraw(UINT nFlags, CPoint point);
	void DrawElement(piiPair pp);
	void RegenUpper(piiPair pp);
	void RegenWater(piiPair pp);
	virtual void OnInitialUpdate();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	virtual void OnActivateView(BOOL bActivate, CScrollView* pActivateView, CScrollView* pDeactiveView);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileSaveAsPicture();
	int GetEncoderClsid(LPCWSTR lpFormat,CLSID * pClsid);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	Bitmap* m_BackBuffer;
	Graphics* m_Temp;
	void DrawAll();
	void ClearDraw();
};

#ifndef _DEBUG  // debug version in eRepMapEditorView.cpp
inline CeRepMapEditorDoc* CeRepMapEditorView::GetDocument() const
   { return reinterpret_cast<CeRepMapEditorDoc*>(m_pDocument); }
#endif

