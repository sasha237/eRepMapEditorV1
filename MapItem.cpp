#include "StdAfx.h"
#include "MapItem.h"

CMapItem::CMapItem(void)
{
	m_iType = 0;
	m_iSubType = 0;
	m_iBuilding = 0;
	m_vmiNeibs.resize(6,0);
	m_piiIndex = make_pair(0,0);
}

CMapItem::~CMapItem(void)
{
}
CMapItem::CMapItem(int iType, int iSubType, int iBuilding, vmiVector& vmiNeibs, piiPair& piiIndex)
{
	m_iType = iType;
	m_iSubType = iSubType;
	m_iBuilding = iBuilding;
	m_vmiNeibs.clear();
	mystdcopy(m_vmiNeibs,vmiNeibs);
	m_piiIndex = make_pair(0,0);
}
CMapItem::CMapItem(const CMapItem& i)
{
	m_iType = i.m_iType;
	m_iSubType = i.m_iSubType;
	m_iBuilding = i.m_iBuilding;
	std::copy((i.m_vmiNeibs).begin(),(i.m_vmiNeibs).end(),std::inserter((m_vmiNeibs),(m_vmiNeibs).end()));
	mycstdcopy(i.m_vmiNeibs,m_vmiNeibs);
	m_piiIndex = i.m_piiIndex;
}
void CMapItem::operator=(const CMapItem& i)
{
	m_iType = i.m_iType;
	m_iSubType = i.m_iSubType;
	m_iBuilding = i.m_iBuilding;
	std::copy((i.m_vmiNeibs).begin(),(i.m_vmiNeibs).end(),std::inserter((m_vmiNeibs),(m_vmiNeibs).end()));
	mycstdcopy(i.m_vmiNeibs,m_vmiNeibs);
	m_piiIndex = i.m_piiIndex;
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
	return true;	
}
