#pragma once

class CGdiPlusBitmap
{
public:
	Gdiplus::Bitmap* m_pBitmap;

public:
	CGdiPlusBitmap();							
	CGdiPlusBitmap(LPCWSTR pFile);				
	virtual ~CGdiPlusBitmap();					

	void Empty();								

	bool Load(LPCWSTR pFile);


	operator Gdiplus::Bitmap*() const;
};

class CGdiPlusBitmapResource : public CGdiPlusBitmap
{
protected:
	HGLOBAL m_hBuffer;

public:
	CGdiPlusBitmapResource();
	CGdiPlusBitmapResource(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	CGdiPlusBitmapResource(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	CGdiPlusBitmapResource(UINT id, UINT type, HMODULE hInst = NULL);
	virtual ~CGdiPlusBitmapResource();

	void Empty();

	bool Load(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	bool Load(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	bool Load(UINT id, UINT type, HMODULE hInst = NULL);
};