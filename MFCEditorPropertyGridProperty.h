#pragma once

// CMFCEditorPropertyGridProperty command target

class CMFCEditorPropertyGridProperty : public CMFCPropertyGridProperty
{
public:
	CMFCEditorPropertyGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);
	CMFCEditorPropertyGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);
	virtual ~CMFCEditorPropertyGridProperty();

	virtual BOOL OnEndEdit() override;
	virtual void OnSelectCombo() override;
};


