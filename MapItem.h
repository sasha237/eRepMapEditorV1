#pragma once

class CMapItem
{
public:
	int m_iType;
	int m_iSubType;
	int m_iBuilding;
	vmiVector m_vmiNeibs;
	piiPair m_piiIndex;
	CMapItem(void);
	CMapItem(int iType, int iSubType, int iBuilding, vmiVector& vmiNeibs, piiPair& piiIndex);
	CMapItem(const CMapItem& i);
	void operator=(const CMapItem& i);
	bool operator<(const CMapItem& i) const;
	bool operator==(const CMapItem& i) const;
	~CMapItem(void);
};
