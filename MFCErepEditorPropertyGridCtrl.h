#pragma once


// CMFCErepEditorPropertyGridCtrl
class CPropertiesWnd;
class CMFCErepEditorPropertyGridCtrl : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(CMFCErepEditorPropertyGridCtrl)

public:
	CMFCErepEditorPropertyGridCtrl();
	virtual ~CMFCErepEditorPropertyGridCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL EndEditItem(BOOL bUpdateData = TRUE) override;
	CPropertiesWnd* m_wndParent;
};


