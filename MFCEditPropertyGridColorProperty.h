#pragma once

// CMFCEditPropertyGridColorProperty command target

class CMFCEditPropertyGridColorProperty : public CMFCPropertyGridColorProperty
{
public:
	CMFCEditPropertyGridColorProperty(const CString& strName, const COLORREF& color, CPalette* pPalette = NULL, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);
	virtual ~CMFCEditPropertyGridColorProperty();
	virtual BOOL OnEndEdit() override;
};


