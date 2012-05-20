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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#pragma warning (disable:4244)
#pragma warning (disable:4018)
#pragma warning (disable:4996)
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif
#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <GdiPlus.h>
#include <math.h>
#include <macros.h>
#include <client.h>
#include <messagehandler.h>
#include <connectionlistener.h>
#include <disco.h>
#include <message.h>
#include <loghandler.h>
#include <tlshandler.h>
#include <tlsdefault.h>
#include <logsink.h>
#include <base64.h>
#include <config.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#include <cstdio> // [s]print[f]


#define MODE_CURSOR				1
#define MODE_PLAIN				2
#define MODE_BRIDGE				3
#define MODE_HILL				4
#define MODE_WATER				5
#define MODE_MOUNTAIN			6
#define MODE_FOREST				7
#define MODE_BRIDGE001001		8
#define MODE_BRIDGE001010		9
#define MODE_BRIDGE010001		10
#define MODE_BRIDGE010010		11
#define MODE_BRIDGE011000		12
#define MODE_BRIDGE011011		13
#define MODE_BRIDGE000011		14

#define MODE_BRIDGE000101		15
#define MODE_BRIDGE010100		16
#define MODE_BRIDGE010101		17
#define MODE_BRIDGE100010		18
#define MODE_BRIDGE100100		19
#define MODE_BRIDGE101000		20
#define MODE_BRIDGE101010		21
#define MODE_BRIDGE111111		22

#define MODE_BIG_CITY			23
#define MODE_D1					24
#define MODE_D2					25
#define MODE_D3					26
#define MODE_D4					27
#define MODE_D5					28
#define MODE_H1					29
#define MODE_H2					30
#define MODE_H3					31
#define MODE_H4					32
#define MODE_H5					33
#define MODE_SMALL_CITY			34

#define MODE_RECRUIT			35
#define MODE_MUSQUETIER			36
#define MODE_HUSSAR				37
#define MODE_GRENADIER			38
#define MODE_GAUBICA			39
#define MODE_EGER				40
#define MODE_DRAGOON			41
#define MODE_CUIRASSIER			42
#define MODE_CANNON				43

#define MODE_AREAS				44

#define MODE_FILTERS			45

#define STEP_ORIG_X				100
#define STEP_ORIG_Y				86
#define STEP_X					150
#define STEP_Y					200
#define STEP_CH_X				((double)(STEP_ORIG_X)/(double)(STEP_X))
#define STEP_CH_Y				((double)(STEP_ORIG_Y)/(double)(STEP_Y))
#define MIN_SCALE				0.1
#define MAX_SCALE				10

using namespace std;
using namespace Gdiplus;

class CMapItem;
class CUnitItem;

typedef pair<int, int> piiPair;
class CPairSorter
{
public:
	CPairSorter(){}
	~CPairSorter(){}
	bool operator()(const piiPair& p1, const piiPair& p2) const;
};

typedef map<piiPair,CMapItem*,CPairSorter> mpiimiMap;
typedef mpiimiMap::iterator mpiimiMapIt;
typedef vector<CMapItem*> vmiVector;
typedef vmiVector::iterator vmiVectorIt;
typedef map<piiPair,piiPair,CPairSorter> mpiipiiMap;
typedef mpiipiiMap::iterator mpiipiiMapIt;

typedef map<piiPair,CUnitItem*> mpiiuiMap;
typedef mpiiuiMap::iterator mpiiuiMapIt;
typedef vector<CUnitItem*> vuiVector;
typedef vuiVector::iterator vuiVectorIt;
typedef set<CUnitItem*> suiSet;
typedef suiSet::iterator suiSetIt;

class CGdiPlusBitmapResource;

typedef map<int, CGdiPlusBitmapResource*> mibiMap;
typedef mibiMap::iterator mibiMapIt;

#define forr(it,co) for((it)=(co).begin();(it)!=(co).end();++(it))
#define ifnend(it,co,ke) if(((it)=(co).find(ke))!=(co).end())
#define ifend(it,co,ke) if(((it)=(co).find(ke))==(co).end())
#define ifinsertmap(it,co,ke,pa) ifend(it,co,ke) (it)=(co).insert(std::make_pair((ke),(pa))).first;
#define ACCURACY 0.0000001
#define eq(d1,d2) (fabs((d1)-(d2))<ACCURACY)
#define neq(d1,d2) (!eq(d1,d2))

template <class T>
void mystdcopy(T& from, T& to)
{
	(to).clear();
	std::copy((from).begin(),(from).end(),std::inserter((to),(to).end()));
}

template <class T>
void mycstdcopy(const T& from, T& to)
{
	(to).clear();
	std::copy((from).begin(),(from).end(),std::inserter((to),(to).end()));
}


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


