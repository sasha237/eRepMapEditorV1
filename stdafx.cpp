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

// stdafx.cpp : source file that includes just the standard includes
// eRepMapEditor.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


bool CPairSorter::operator()(const piiPair& p1, const piiPair& p2) const
{
	if (p1==p2)
		return false;
	if (p1.second<p2.second)
		return true;
	if (p1.second>p2.second)
		return false;
	if (p1.first+1!=p2.first&&p1.first-1!=p2.first)
		return p1.first<p2.first;
	return p1.first%2<p2.first%2;
}