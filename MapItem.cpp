#include "StdAfx.h"
#include "MapItem.h"

CMapItem::CMapItem(void)
{
	m_iType = 0;
	m_iSubType = 0;
	m_iBuilding = 0;
	m_vmiNeibs.resize(6,0);
	m_piiIndex = make_pair(0,0);
	m_pUnitItem = NULL;
	m_bHasUnit = false;
	m_bHasFortif = false;
	m_rgbColor = RGB(255,255,255);
}

CMapItem::~CMapItem(void)
{
}
CMapItem::CMapItem(int iType, int iSubType, int iBuilding, vmiVector& vmiNeibs, piiPair& piiIndex, CUnitItem* pUnitItem, 	bool bHasUnit,	bool bHasFortif, COLORREF rgbColor)
{
	m_iType = iType;
	m_iSubType = iSubType;
	m_iBuilding = iBuilding;
	m_vmiNeibs.clear();
	mystdcopy(m_vmiNeibs,vmiNeibs);
	m_piiIndex = make_pair(0,0);
	m_pUnitItem = pUnitItem;
	m_bHasUnit = bHasUnit;
	m_bHasFortif = bHasFortif;
	m_rgbColor = rgbColor;
}
CMapItem::CMapItem(const CMapItem& i)
{
	m_iType = i.m_iType;
	m_iSubType = i.m_iSubType;
	m_iBuilding = i.m_iBuilding;
	std::copy((i.m_vmiNeibs).begin(),(i.m_vmiNeibs).end(),std::inserter((m_vmiNeibs),(m_vmiNeibs).end()));
	mycstdcopy(i.m_vmiNeibs,m_vmiNeibs);
	m_piiIndex = i.m_piiIndex;
	m_pUnitItem = i.m_pUnitItem;
	m_bHasUnit = i.m_bHasUnit;
	m_bHasFortif = i.m_bHasFortif;
	m_rgbColor = i.m_rgbColor;
}
void CMapItem::operator=(const CMapItem& i)
{
	m_iType = i.m_iType;
	m_iSubType = i.m_iSubType;
	m_iBuilding = i.m_iBuilding;
	std::copy((i.m_vmiNeibs).begin(),(i.m_vmiNeibs).end(),std::inserter((m_vmiNeibs),(m_vmiNeibs).end()));
	mycstdcopy(i.m_vmiNeibs,m_vmiNeibs);
	m_piiIndex = i.m_piiIndex;
	m_pUnitItem = i.m_pUnitItem;
	m_bHasUnit = i.m_bHasUnit;
	m_bHasFortif = i.m_bHasFortif;
	m_rgbColor = i.m_rgbColor;
}
bool CMapItem::operator<(const CMapItem& i) const
{
	vmiVectorIt it;
	if (m_piiIndex<i.m_piiIndex)
		return true;
	if (m_piiIndex>i.m_piiIndex)
		return false;
	if (m_iType<i.m_iType)
		return true;
	if (m_iType>i.m_iType)
		return false;
	if (m_iSubType<i.m_iSubType)
		return true;
	if (m_iSubType>i.m_iSubType)
		return false;
	if (m_iBuilding<i.m_iBuilding)
		return true;
	if (m_iBuilding>i.m_iBuilding)
		return false;
	if (m_bHasUnit<i.m_bHasUnit)
		return true;
	if (m_bHasUnit>i.m_bHasUnit)
		return false;
	if (m_bHasFortif<i.m_bHasFortif)
		return true;
	if (m_bHasFortif>i.m_bHasFortif)
		return false;
	if (m_rgbColor<i.m_rgbColor)
		return true;
	if (m_rgbColor>i.m_rgbColor)
		return false;

	return false;	
}
bool CMapItem::operator==(const CMapItem& i) const
{
	vmiVectorIt it;
	if (m_piiIndex!=i.m_piiIndex)
		return false;
	if (m_iType!=i.m_iType)
		return false;
	if (m_iSubType!=i.m_iSubType)
		return false;
	if (m_iBuilding!=i.m_iBuilding)
		return false;	
	if (m_bHasUnit!=i.m_bHasUnit)
		return false;
	if (m_bHasFortif!=i.m_bHasFortif)
		return false;
	if (m_rgbColor!=i.m_rgbColor)
		return false;
	return true;	
}
CUnitItem::CUnitItem(void)
{
	m_pMapItem = NULL;
	m_sName = "";
	m_iCount = 0;
	m_iType = 0;
	m_bRotate = false;
	m_rgbColor = RGB(255,255,255);
}
CUnitItem::CUnitItem(CString sName, int iCount, int iType, bool bRotate, COLORREF rgbColor, CMapItem* pMapItem)
{
	m_sName = sName;
	m_iCount = iCount;
	m_iType = iType;
	m_bRotate = bRotate;
	m_rgbColor = rgbColor;
	m_pMapItem = pMapItem;
}
CUnitItem::CUnitItem(const CUnitItem& i)
{
	m_sName = i.m_sName;
	m_iCount = i.m_iCount;
	m_iType = i.m_iType;
	m_bRotate = i.m_bRotate;
	m_rgbColor = i.m_rgbColor;
	m_pMapItem = i.m_pMapItem;
}
void CUnitItem::operator=(const CUnitItem& i)
{
	m_sName = i.m_sName;
	m_iCount = i.m_iCount;
	m_iType = i.m_iType;
	m_bRotate = i.m_bRotate;
	m_rgbColor = i.m_rgbColor;
	m_pMapItem = i.m_pMapItem;
}
bool CUnitItem::operator<(const CUnitItem& i) const
{
	if(m_sName < i.m_sName)
		return true;
	if(m_sName > i.m_sName)
		return false;
	if(m_iCount < i.m_iCount)
		return true;
	if(m_iCount > i.m_iCount)
		return false;
	if(m_iType < i.m_iType)
		return true;
	if(m_iType > i.m_iType)
		return false;
	if(m_bRotate < i.m_bRotate)
		return true;
	if(m_bRotate > i.m_bRotate)
		return false;
	if(m_rgbColor < i.m_rgbColor)
		return true;
	if(m_rgbColor > i.m_rgbColor)
		return false;
	if(m_pMapItem < i.m_pMapItem)
		return true;
	if(m_pMapItem > i.m_pMapItem)
		return false;
	return false;

}
bool CUnitItem::operator==(const CUnitItem& i) const
{
	if(m_sName != i.m_sName)
		return false;
	if(m_iCount != i.m_iCount)
		return false;
	if(m_iType != i.m_iType)
		return false;
	if(m_bRotate != i.m_bRotate)
		return false;
	if(m_rgbColor != i.m_rgbColor)
		return false;
	if(m_pMapItem != i.m_pMapItem)
		return false;
	return true;
}
CUnitItem::~CUnitItem(void)
{

}