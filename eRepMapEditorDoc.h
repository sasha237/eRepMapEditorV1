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

// eRepMapEditorDoc.h : interface of the CeRepMapEditorDoc class
//


#pragma once

#include "MapItem.h"

class CeRepMapEditorDoc : public CDocument
{
protected: // create from serialization only
	CeRepMapEditorDoc();
	DECLARE_DYNCREATE(CeRepMapEditorDoc)
	int m_iMode;
// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
// Implementation
public:
	virtual ~CeRepMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBridge();
	afx_msg void OnUpdateBridge(CCmdUI *pCmdUI);
	afx_msg void OnForest();
	afx_msg void OnUpdateForest(CCmdUI *pCmdUI);
	afx_msg void OnHill();
	afx_msg void OnUpdateHill(CCmdUI *pCmdUI);
	afx_msg void OnMountain();
	afx_msg void OnUpdateMountain(CCmdUI *pCmdUI);
	afx_msg void OnPlain();
	afx_msg void OnUpdatePlain(CCmdUI *pCmdUI);
	afx_msg void OnWater();
	afx_msg void OnUpdateWater(CCmdUI *pCmdUI);
	afx_msg void OnCursorElement();
	afx_msg void OnUpdateCursorElement(CCmdUI *pCmdUI);
	afx_msg void OnResizeElement();
	afx_msg void OnUpdateResizeElement(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWidth(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHeight(CCmdUI *pCmdUI);

	afx_msg void OnBridge001001();
	afx_msg void OnBridge001010();
	afx_msg void OnBridge010001();
	afx_msg void OnBridge010010();
	afx_msg void OnBridge011000();
	afx_msg void OnBridge011011();
	afx_msg void OnBridge000011();
	afx_msg void OnUpdateBridge001001(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge001010(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge010001(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge010010(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge011000(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge011011(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge000011(CCmdUI *pCmdUI);
	
	afx_msg void OnBridge000101();
	afx_msg void OnBridge010100();
	afx_msg void OnBridge010101();
	afx_msg void OnBridge100010();
	afx_msg void OnBridge100100();
	afx_msg void OnBridge101000();
	afx_msg void OnBridge101010();
	afx_msg void OnBridge111111();
	afx_msg void OnUpdateBridge000101(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge010100(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge010101(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge100010(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge100100(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge101000(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge101010(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBridge111111(CCmdUI *pCmdUI);





	afx_msg void OnBigCity();
	afx_msg void OnDefence1();
	afx_msg void OnDefence2();
	afx_msg void OnDefence3();
	afx_msg void OnDefence4();
	afx_msg void OnDefence5();
	afx_msg void OnHospital1();
	afx_msg void OnHospital2();
	afx_msg void OnHospital3();
	afx_msg void OnHospital4();
	afx_msg void OnHospital5();
	afx_msg void OnSmallCity();

	afx_msg void OnRECRUIT    ();
	afx_msg void OnMUSQUETIER();
	afx_msg void OnHUSSAR     ();
	afx_msg void OnGRENADIER  ();
	afx_msg void OnGAUBICA    ();
	afx_msg void OnEGER       ();
	afx_msg void OnDRAGOON    ();
	afx_msg void OnCUIRASSIER ();
	afx_msg void OnCANNON     ();


	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateBigCity(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefence1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefence2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefence3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefence4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefence5(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHospital1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHospital2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHospital3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHospital4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHospital5(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSmallCity(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoomIn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoomOut(CCmdUI *pCmdUI);


	afx_msg void OnUpdateRECRUIT    (CCmdUI *pCmdUI);
	afx_msg void OnUpdateMUSQUETIER (CCmdUI *pCmdUI);
	afx_msg void OnUpdateHUSSAR     (CCmdUI *pCmdUI);
	afx_msg void OnUpdateGRENADIER  (CCmdUI *pCmdUI);
	afx_msg void OnUpdateGAUBICA    (CCmdUI *pCmdUI);
	afx_msg void OnUpdateEGER       (CCmdUI *pCmdUI);
	afx_msg void OnUpdateDRAGOON    (CCmdUI *pCmdUI);
	afx_msg void OnUpdateCUIRASSIER (CCmdUI *pCmdUI);
	afx_msg void OnUpdateCANNON     (CCmdUI *pCmdUI);

	bool m_bShowNumbers;
	double m_scale;
	piiPair m_piiSize;
	mpiimiMap m_Elements;
	void ClearMap();
	void CalcNeibs();
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnRibbonShowNumbers();
	afx_msg void OnUpdateRibbonShowNumbers(CCmdUI *pCmdUI);
	afx_msg void OnHospitals();
	afx_msg void OnUpdateHospitals(CCmdUI *pCmdUI);
	afx_msg void OnDefences();
	afx_msg void OnUpdateDefences(CCmdUI *pCmdUI);
	afx_msg void OnUnits();
	afx_msg void OnUpdateUnits(CCmdUI *pCmdUI);
	afx_msg void OnAREAS();
	afx_msg void OnUpdateAREAS(CCmdUI *pCmdUI);
	afx_msg void OnFILTER_COLOR();
	afx_msg void OnUpdateFILTER_COLOR(CCmdUI *pCmdUI);
	afx_msg void OnFILTER_BY_FOREST();
	afx_msg void OnUpdateFILTER_BY_FOREST(CCmdUI *pCmdUI);
	afx_msg void OnALL_FILTERS();
	afx_msg void OnUpdateALL_FILTERS(CCmdUI *pCmdUI);	
	bool IsPropVisible();
	void FilterByForestAndColor();
	bool m_bFilterOn;
};


