#include "StdAfx.h"
#include "GdiPlusBitmap.h"


CGdiPlusBitmap::CGdiPlusBitmap()							
{ 
	m_pBitmap = NULL; 
}
CGdiPlusBitmap::CGdiPlusBitmap(LPCWSTR pFile)				
{ 
	m_pBitmap = NULL; 
Load(pFile); 
}
CGdiPlusBitmap::~CGdiPlusBitmap()					
{ 
	Empty(); 
}

void CGdiPlusBitmap::Empty()								
{ 
	delete m_pBitmap; m_pBitmap = NULL; 
}

bool CGdiPlusBitmap::Load(LPCWSTR pFile)
{
	Empty();
	m_pBitmap = Gdiplus::Bitmap::FromFile(pFile);
	return m_pBitmap->GetLastStatus() == Gdiplus::Ok;
}

CGdiPlusBitmap::operator Gdiplus::Bitmap*() const			
{ 
	return m_pBitmap; 
}

CGdiPlusBitmapResource::CGdiPlusBitmapResource()					
{ 
	m_hBuffer = NULL; 
}
CGdiPlusBitmapResource::CGdiPlusBitmapResource(LPCTSTR pName, LPCTSTR pType /*= RT_RCDATA*/, HMODULE hInst /*= NULL*/)
{ 
	m_hBuffer = NULL; 
	Load(pName, pType, hInst); 
}
CGdiPlusBitmapResource::CGdiPlusBitmapResource(UINT id, LPCTSTR pType /*= RT_RCDATA*/, HMODULE hInst /*= NULL*/)
{ 
	m_hBuffer = NULL; 
	Load(id, pType, hInst); 
}
CGdiPlusBitmapResource::CGdiPlusBitmapResource(UINT id, UINT type, HMODULE hInst /*= NULL*/)
{ 
	m_hBuffer = NULL; 
	Load(id, type, hInst); 
}
CGdiPlusBitmapResource::~CGdiPlusBitmapResource()			
{ 
	Empty(); 
}

bool CGdiPlusBitmapResource::Load(UINT id, LPCTSTR pType /*= RT_RCDATA*/, HMODULE hInst /*= NULL*/)
{ 
	return Load(MAKEINTRESOURCE(id), pType, hInst); 
}
bool CGdiPlusBitmapResource::Load(UINT id, UINT type, HMODULE hInst /*= NULL*/)
{ 
	return Load(MAKEINTRESOURCE(id), MAKEINTRESOURCE(type), hInst); 
}
inline bool CGdiPlusBitmapResource::Load(LPCTSTR pName, LPCTSTR pType, HMODULE hInst)
{
	Empty();

	HRSRC hResource = ::FindResource(hInst, pName, pType);
	if (!hResource)
		return false;

	DWORD imageSize = ::SizeofResource(hInst, hResource);
	if (!imageSize)
		return false;

	const void* pResourceData = ::LockResource(::LoadResource(hInst, hResource));
	if (!pResourceData)
		return false;

	m_hBuffer  = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
	if (m_hBuffer)
	{
		void* pBuffer = ::GlobalLock(m_hBuffer);
		if (pBuffer)
		{
			CopyMemory(pBuffer, pResourceData, imageSize);

			IStream* pStream = NULL;
			if (::CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK)
			{
				m_pBitmap = Gdiplus::Bitmap::FromStream(pStream);
				pStream->Release();
				if (m_pBitmap)
				{ 
					if (m_pBitmap->GetLastStatus() == Gdiplus::Ok)
						return true;

					delete m_pBitmap;
					m_pBitmap = NULL;
				}
			}
			::GlobalUnlock(m_hBuffer);
		}
		::GlobalFree(m_hBuffer);
		m_hBuffer = NULL;
	}
	return false;
}

inline
void CGdiPlusBitmapResource::Empty()
{
	CGdiPlusBitmap::Empty();
	if (m_hBuffer)
	{
		::GlobalUnlock(m_hBuffer);
		::GlobalFree(m_hBuffer);
		m_hBuffer = NULL;
	} 
}