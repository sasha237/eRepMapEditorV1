#pragma once

class CMapItem;
class CUnitItem;

class CUnitItem
{
public:
	CMapItem* m_pMapItem;
	CString m_sName;
	int m_iCount;
	int m_iType;
	bool m_bRotate;
	COLORREF m_rgbColor;
	CUnitItem(void);
	CUnitItem(CString sName, int iCount, int iType, bool bRotate, COLORREF rgbColor, CMapItem* pMapItem);
	CUnitItem(const CUnitItem& i);
	void operator=(const CUnitItem& i);
	bool operator<(const CUnitItem& i) const;
	bool operator==(const CUnitItem& i) const;
	~CUnitItem(void);
};

class CMapItem
{
public:
	CUnitItem* m_pUnitItem;
	int m_iType;
	int m_iSubType;
	int m_iBuilding;
	vmiVector m_vmiNeibs;
	piiPair m_piiIndex;
	bool m_bHasUnit;
	bool m_bHasFortif;
	COLORREF m_rgbColor;
	CMapItem(void);
	CMapItem(int iType, int iSubType, int iBuilding, vmiVector& vmiNeibs, piiPair& piiIndex, CUnitItem* pUnitItem, 	bool bHasUnit,	bool bHasFortif, COLORREF rgbColor);
	CMapItem(const CMapItem& i);
	void operator=(const CMapItem& i);
	bool operator<(const CMapItem& i) const;
	bool operator==(const CMapItem& i) const;
	~CMapItem(void);
};
