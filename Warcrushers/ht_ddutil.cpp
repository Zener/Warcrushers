/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddutil.cpp
 *  Content:    Routines for loading bitmap and palettes from resources
 *
 ***************************************************************************/
#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "ht_ddutil.h"

/*
 *  DDLoadBitmap
 *
 *  create a DirectDrawSurface from a bitmap resource.
 *
 */
extern "C" IDirectDrawSurface * DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy, int memLoc)
{
    HBITMAP             hbm;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    IDirectDrawSurface *pdds;

    //
    //  try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx, dy, LR_CREATEDIBSECTION);

    if (hbm == NULL)
        hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
        return NULL;

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

    //
    // create a DirectDrawSurface for this bitmap
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;

	if (memLoc == 0)
	{
		// In video memory first then try system memory
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	}
	else
	{
		// In system memory only
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	}

    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;

    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return NULL;

    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

    DeleteObject(hbm);

    return pdds;
}

/*
 *  DDReLoadBitmap
 *
 *  load a bitmap from a file or resource into a directdraw surface.
 *  normaly used to re-load a surface after a restore.
 *
 */
HRESULT DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap)
{
    HBITMAP             hbm;
    HRESULT             hr;

    //
    //  try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hbm == NULL)
        hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
    {
        OutputDebugString("handle is null\n");
        return E_FAIL;
    }

    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    if (hr != DD_OK)
    {
        OutputDebugString("ddcopybitmap failed\n");
    }


    DeleteObject(hbm);
    return hr;
}

/*
 *  DDCopyBitmap
 *
 *  draw a bitmap into a DirectDrawSurface
 *
 */
extern "C" HRESULT DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;

    //
    // make sure this surface is restored.
    //
    pdds->Restore();

    //
    //  select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        OutputDebugString("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
    dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;

    //
    // get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }

    DeleteDC(hdcImage);

    return hr;
}

//
//  DDLoadPalette
//
//  Create a DirectDraw palette object from a bitmap resoure
//
//  if the resource does not exist or NULL is passed create a
//  default 332 palette.
//
extern "C" IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap)
{
    IDirectDrawPalette* ddpal;
    int                 i;
    int                 n;
    int                 fh;
    HRSRC               h;
    LPBITMAPINFOHEADER  lpbi;
    PALETTEENTRY        ape[256];
    RGBQUAD *           prgb;

    //
    // build a 332 palette as the default.
    //
    for (i=0; i<256; i++)
    {
        ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
        ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
        ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
        ape[i].peFlags = (BYTE)0;
    }

    //
    // get a pointer to the bitmap resource.
    //
    if (szBitmap && (h = FindResource(NULL, szBitmap, RT_BITMAP)))
    {
        lpbi = (LPBITMAPINFOHEADER)LockResource(LoadResource(NULL, h));
        if (!lpbi)
            OutputDebugString("lock resource failed\n");
        prgb = (RGBQUAD*)((BYTE*)lpbi + lpbi->biSize);

        if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (lpbi->biBitCount > 8)
            n = 0;
        else if (lpbi->biClrUsed == 0)
            n = 1 << lpbi->biBitCount;
        else
            n = lpbi->biClrUsed;

        //
        //  a DIB color table has its colors stored BGR not RGB
        //  so flip them around.
        //
        for(i=0; i<n; i++ )
        {
            ape[i].peRed   = prgb[i].rgbRed;
            ape[i].peGreen = prgb[i].rgbGreen;
            ape[i].peBlue  = prgb[i].rgbBlue;
            ape[i].peFlags = 0;
        }
    }
    else if (szBitmap && (fh = _lopen(szBitmap, OF_READ)) != -1)
    {
        BITMAPFILEHEADER bf;
        BITMAPINFOHEADER bi;

        _lread(fh, &bf, sizeof(bf));
        _lread(fh, &bi, sizeof(bi));
        _lread(fh, ape, sizeof(ape));
        _lclose(fh);

        if (bi.biSize != sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (bi.biBitCount > 8)
            n = 0;
        else if (bi.biClrUsed == 0)
            n = 1 << bi.biBitCount;
        else
            n = bi.biClrUsed;

        //
        //  a DIB color table has its colors stored BGR not RGB
        //  so flip them around.
        //
        for(i=0; i<n; i++ )
        {
            BYTE r = ape[i].peRed;
            ape[i].peRed  = ape[i].peBlue;
            ape[i].peBlue = r;
        }
    }

    pdd->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);

    return ddpal;
}

/*
 * DDColorMatch
 *
 * convert a RGB color to a pysical color.
 *
 * we do this by leting GDI SetPixel() do the color matching
 * then we lock the memory and see what it got mapped to.
 */
extern "C" DWORD DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb)
{
    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC ddsd;
    HRESULT hres;

    //
    //  use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
        SetPixel(hdc, 0, 0, rgb);               // set our value
        pdds->ReleaseDC(hdc);
    }

    //
    // now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;

    if (hres == DD_OK)
    {
        dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
        dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
        pdds->Unlock(NULL);
    }

    //
    //  now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }

    return dw;
}

/*
 * DDSetColorKey
 *
 * set a color key for a surface, given a RGB.
 * if you pass CLR_INVALID as the color key, the pixel
 * in the upper-left corner will be used.
 */
extern "C" HRESULT DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb)
{
    DDCOLORKEY          ddck;

    ddck.dwColorSpaceLowValue  = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}



///////////////////////////////////////////////////////////////////////
HRESULT TransAlphaMMX(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dest,
   RECT srcRect, RECT destRect, WORD ALPHA, DWORD ColorKey, WORD BPP)
{
	int register i,j;
	int height,width;
	BYTE* lpSprite;
	BYTE* lpDest;
	WORD dPitch, SpritePitch;
	WORD sbuf,dbuf;
	DDSURFACEDESC2 srcDDSD, destDDSD;

	__int64 ALPHA64, COLORKEY64, ALPHABY4;
	__int64 MASKRED, MASKGREEN, MASKBLUE;
	__int64 ADD64     = 0x0040004000400040;

	// Check if the global g_isMMX flag is set
	//if ( ! g_isMMX )
	//	return DDERR_GENERIC;

	// Check the ALPHA value
	if (ALPHA < 0)
		ALPHA = 0;
	else if (ALPHA > 256)
		ALPHA = 256;

	// Set height and width of SPRITE
    height = srcRect.bottom - srcRect.top;
    width =  srcRect.right - srcRect.left;

	// Lock down both surfaces for read and write
	ZeroMemory(&srcDDSD, sizeof(srcDDSD));
	srcDDSD.dwSize = sizeof(srcDDSD);
	src->Lock(NULL, &srcDDSD, DDLOCK_WAIT, NULL);

	ZeroMemory(&destDDSD, sizeof(destDDSD));
	destDDSD.dwSize = sizeof(destDDSD);
	dest->Lock(NULL, &destDDSD, DDLOCK_WAIT, NULL);

    // Set the pitch for both surfaces
    SpritePitch = (WORD)srcDDSD.lPitch;
    dPitch      = (WORD)destDDSD.lPitch;

    // Initialize the pointers to the first pixel in the rectangle
    lpSprite = (BYTE*)srcDDSD.lpSurface;
    lpDest   = (BYTE*)destDDSD.lpSurface;


	switch(BPP)
	{
	case 8:
		// IMHO paletized modes are a thing of the past please feel free to 
		// implement this if you so desire.
		break;

	case 15:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card that uses the 5-5-5 format 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////

	
		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + srcRect.left * 2;
		lpDest   += (destRect.top * dPitch) + destRect.left * 2;

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2*width));
		dbuf = (WORD)(dPitch - (2*width));

		// Setup the color channel masks
		MASKRED   = 0xF800F800F800F800;
		MASKGREEN = 0x07E007E007E007E0;
		MASKBLUE  = 0x001F001F001F001F;

		_asm
		{
			movd mm2,ALPHA    ; Copy ALPHA into mm2
			punpcklwd mm2,mm2 ; Unpack mm2 - 0000 0000 00aa 00aa
			punpckldq mm2,mm2 ; Unpack mm2 - 00aa 00aa 00aa 00aa
			movq ALPHA64,mm2  ; Save the result into ALPHA64

			psrlw mm2, 2      ; Divide each ALPHA value by 4
			movq ALPHABY4,mm2 ; Save the result to ALPHABY4

			movd mm4,ColorKey ; Copy ColorKey into mm4
			punpcklwd mm4,mm4 ; Unpack mm4 - 0000 0000 cccc cccc
			punpckldq mm4,mm4 ; Unpack mm4 - cccc cccc cccc cccc
			movq COLORKEY64,mm4 ; Save the result into COLORKEY64

		}

		i = height;
		do
		{
			j = width/4;
			// If you see two lines together this means that I am guessing that these two
			// instructions will pair in the Pentium U & V pipes.
			_asm
			{
				push edi ;Save off to restore later
				push esi ;Save off to restore later


				mov edi,lpDest				; Move the destination pointer into edi
				mov esi,lpSprite			; Move the source pointer into esi

			SPAN_RUN_555: movq mm7,[edi]	; Copy the 8 bytes pointed to by edi into mm7
				movq mm6,[esi]				; Copy the 8 bytes pointed to by esi into mm6

				movq mm2,ALPHA64			; Copy ALPHA64 into mm2
				movq mm0,mm7				; RED - Copy mm7 to mm0, destination pixels

				pand mm0,MASKRED			; RED - and mm0 with the red channel mask [0r00 0r00 0r00 0r00]
				movq mm1,mm6				; RED - Copy mm6 to mm1, source pixels

				pand mm1,MASKRED			; RED - and mm1 with red channel mask [0r00 0r00 0r00 0r00]
				psrlw mm0,11				; RED - shift each pixel to the right by 11 [000r 000r 000r 000r]

				movq mm5,mm7				; GRN - Copy destination pixels (mm7) to mm5
				psrlw mm1,11				; RED - shift each pixel to the right by 11 [000r 000r 000r 000r]


				paddw mm1, ADD64


				movq mm3,mm6				; GRN - Copy source pixels (mm6) to mm3
				psubsw mm1,mm0				; RED - Subtract the destination from the source

				pand mm5,MASKGREEN			; GRN - and mm5 with the green channel mask [00g0 00g0 00g0 00g0]
				pmullw mm1,mm2				; RED - multiple the subtraction result by the ALPHA value

				pand mm3,MASKGREEN			; GRN - and mm3 with the green channel mask [00g0 00g0 00g0 00g0]
				psrlw mm5,5					; GRN - shift each pixel to the right by 5 [000g 000g 000g 000g]

				psrlw mm3,5					; GRN - Shift green source to the right by 5
				nop							; Do nothing


				paddw mm3, ADD64


				psrlw mm1,8					; RED - Divide by 256 this is done to avoid floating point math
				psubsw mm3,mm5				; GRN - Subtract the green source and destination components

				pmullw mm3,mm2				; GRN - Multiple the result from the subtraction by the alpha value
				paddw mm1,mm0				; RED - Add the destination red component value


				psubw mm1, ALPHABY4


				psllw mm1,11				; RED - Shift the red component back into place, 11 to the left
				movq mm0,mm7				; BLU - Copy the destination pixels to mm0

				pand mm0, MASKBLUE			; BLU - 'and' mm0 with the blue channel mask [000b 000b 000b 000b]
				psrlw mm3,8					; GRN - Divide by 256 this is done to avoid floating point math

				paddw mm3,mm5				; GRN - Add the destination green component value
				movq mm4, mm6				; BLU - Copy the source into mm4


				psubw mm3, ALPHABY4


				pand mm4, MASKBLUE			; BLU - 'and' mm0 with the blue channel mask [000b 000b 000b 000b]
				psllw mm3,5					; GRN - Shift the green component back into place, 5 to the left


				paddw mm4, ADD64


				psubsw mm4,mm0				; BLU - Subtract the blue source and destination components
				por mm1,mm3					; GRN - 'or' the red and green components results back together

				pmullw mm4,mm2				; BLU - Multiple the result from the subtraction by the alpha value
				movq mm3,COLORKEY64			; Load COLORKEY64 into mm4

				psrlw mm4,8					; BLU - Divide by 256 this is done to avoid floating point math
				pcmpeqw mm3,mm6				; Compare colorKey to original source

				paddw mm4,mm0				; BLU - Add the destination blue component value
				movq mm5,mm3				; Copy mm3 to mm5


				psubw mm4, ALPHABY4


				por mm1,mm4					; BLU - 'or' the blue result to the red and green results
				pand mm5,mm7				; 'and' mm5 and the original destination pixels

				pandn mm3,mm1				; not's mm3 then performs and "AND" with mm1

				por mm3,mm5					; And mm3 and mm5

				movq [edi],mm3				; Copy the 4 alpha blended pixels to the destination

				add edi,8					; Add 8 bytes to the destination pointer
				mov eax,dword ptr [j]		; Load the value of j into eax

				add esi,8					; Add 8 bytes to the source pointer
				sub eax,1					; subtract 1 from eax (j--)

				mov dword ptr [lpDest], edi ; Save the new destination pointer value
				mov dword ptr [j],eax		; save the new value back to j

				mov dword ptr [lpSprite], esi ; Save the new source pointer value
				cmp eax,0					; If eax = 0 we have set the flag

				jg SPAN_RUN_555				; if flag is zero finish else loop back for more

				emms						; Clean up the MMX registers

				pop esi ; Restore esi
				pop edi ; Restore edi
			}

			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);

		break;

	case 16:

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + srcRect.left * 2;
		lpDest   += (destRect.top * dPitch) + destRect.left * 2;

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2*width));
		dbuf = (WORD)(dPitch - (2*width));

		// Setup the color channel masks
		MASKRED   = 0xF800F800F800F800;
		MASKGREEN = 0x07E007E007E007E0;
		MASKBLUE  = 0x001F001F001F001F;

		_asm
		{
			movd mm2,ALPHA    ; Copy ALPHA into mm2
			punpcklwd mm2,mm2 ; Unpack mm2 - 0000 0000 00aa 00aa
			punpckldq mm2,mm2 ; Unpack mm2 - 00aa 00aa 00aa 00aa
			movq ALPHA64,mm2  ; Save the result into ALPHA64

			psrlw mm2, 2      ; Divide each ALPHA value by 4
			movq ALPHABY4,mm2 ; Save the result to ALPHABY4

			movd mm4,ColorKey ; Copy ColorKey into mm4
			punpcklwd mm4,mm4 ; Unpack mm4 - 0000 0000 cccc cccc
			punpckldq mm4,mm4 ; Unpack mm4 - cccc cccc cccc cccc
			movq COLORKEY64,mm4 ; Save the result into COLORKEY64

		}

		i = height;
		do
		{
			j = width/4;
			// If you see two lines together this means that I am guessing that these two
			// instructions will pair in the Pentium U & V pipes.
			_asm
			{
				push edi ;Save off to restore later
				push esi ;Save off to restore later


				mov edi,lpDest				; Move the destination pointer into edi
				mov esi,lpSprite			; Move the source pointer into esi

			SPAN_RUN_565: movq mm7,[edi]	; Copy the 8 bytes pointed to by edi into mm7
				movq mm6,[esi]				; Copy the 8 bytes pointed to by esi into mm6

				movq mm2,ALPHA64			; Copy ALPHA64 into mm2
				movq mm0,mm7				; RED - Copy mm7 to mm0, destination pixels

				pand mm0,MASKRED			; RED - and mm0 with the red channel mask [0r00 0r00 0r00 0r00]
				movq mm1,mm6				; RED - Copy mm6 to mm1, source pixels

				pand mm1,MASKRED			; RED - and mm1 with red channel mask [0r00 0r00 0r00 0r00]
				psrlw mm0,11				; RED - shift each pixel to the right by 11 [000r 000r 000r 000r]

				movq mm5,mm7				; GRN - Copy destination pixels (mm7) to mm5
				psrlw mm1,11				; RED - shift each pixel to the right by 11 [000r 000r 000r 000r]


				paddw mm1, ADD64


				movq mm3,mm6				; GRN - Copy source pixels (mm6) to mm3
				psubsw mm1,mm0				; RED - Subtract the destination from the source

				pand mm5,MASKGREEN			; GRN - and mm5 with the green channel mask [00g0 00g0 00g0 00g0]
				pmullw mm1,mm2				; RED - multiple the subtraction result by the ALPHA value

				pand mm3,MASKGREEN			; GRN - and mm3 with the green channel mask [00g0 00g0 00g0 00g0]
				psrlw mm5,5					; GRN - shift each pixel to the right by 5 [000g 000g 000g 000g]

				psrlw mm3,5					; GRN - Shift green source to the right by 5
				nop							; Do nothing


				paddw mm3, ADD64


				psrlw mm1,8					; RED - Divide by 256 this is done to avoid floating point math
				psubsw mm3,mm5				; GRN - Subtract the green source and destination components

				pmullw mm3,mm2				; GRN - Multiple the result from the subtraction by the alpha value
				paddw mm1,mm0				; RED - Add the destination red component value


				psubw mm1, ALPHABY4


				psllw mm1,11				; RED - Shift the red component back into place, 11 to the left
				movq mm0,mm7				; BLU - Copy the destination pixels to mm0

				pand mm0, MASKBLUE			; BLU - 'and' mm0 with the blue channel mask [000b 000b 000b 000b]
				psrlw mm3,8					; GRN - Divide by 256 this is done to avoid floating point math

				paddw mm3,mm5				; GRN - Add the destination green component value
				movq mm4, mm6				; BLU - Copy the source into mm4


				psubw mm3, ALPHABY4


				pand mm4, MASKBLUE			; BLU - 'and' mm0 with the blue channel mask [000b 000b 000b 000b]
				psllw mm3,5					; GRN - Shift the green component back into place, 5 to the left


				paddw mm4, ADD64


				psubsw mm4,mm0				; BLU - Subtract the blue source and destination components
				por mm1,mm3					; GRN - 'or' the red and green components results back together

				pmullw mm4,mm2				; BLU - Multiple the result from the subtraction by the alpha value
				movq mm3,COLORKEY64			; Load COLORKEY64 into mm4

				psrlw mm4,8					; BLU - Divide by 256 this is done to avoid floating point math
				pcmpeqw mm3,mm6				; Compare colorKey to original source

				paddw mm4,mm0				; BLU - Add the destination blue component value
				movq mm5,mm3				; Copy mm3 to mm5


				psubw mm4, ALPHABY4


				por mm1,mm4					; BLU - 'or' the blue result to the red and green results
				pand mm5,mm7				; 'and' mm5 and the original destination pixels

				pandn mm3,mm1				; not's mm3 then performs and "AND" with mm1

				por mm3,mm5					; And mm3 and mm5

				movq [edi],mm3				; Copy the 4 alpha blended pixels to the destination

				add edi,8					; Add 8 bytes to the destination pointer
				mov eax,dword ptr [j]		; Load the value of j into eax

				add esi,8					; Add 8 bytes to the source pointer
				sub eax,1					; subtract 1 from eax (j--)

				mov dword ptr [lpDest], edi ; Save the new destination pointer value
				mov dword ptr [j],eax		; save the new value back to j

				mov dword ptr [lpSprite], esi ; Save the new source pointer value
				cmp eax,0					; If eax = 0 we have set the flag

				jg SPAN_RUN_565				; if flag is zero finish else loop back for more

				emms						; Clean up the MMX registers

				pop esi ; Restore esi
				pop edi ; Restore edi
			}

			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);

		break;


	case 24:

		// Not Implemented
		break;

	case 32:

	    // Not implemented
		break;

	} // End RGB Format switch statement

	src->Unlock(NULL);
	dest->Unlock(NULL);

	return DD_OK;
}

////////////////////////////////////////////////////////////////////////
// TransAlphaFast - 
////////////////////////////////////////////////////////////////////////

HRESULT TransAlphaFast(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dest, 
					   LONG lDestX, LONG lDestY, RECT srcRect, DWORD ColorKey, WORD BPP)
{
    int register i,j;
	int height,width;
    BYTE* lpSprite;
    BYTE* lpDest;
    LONG dPitch, SpritePitch;
    DWORD sColorKey;
    DWORD sTemp,dTemp;
    WORD sbuf,dbuf;
    DWORD Result;
	BOOL oddWidth = FALSE;
	DDSURFACEDESC2 srcDDSD, destDDSD;

    // Set height and width of SPRITE
    height = srcRect.bottom - srcRect.top;
    width  = srcRect.right - srcRect.left;

    // Lock down both surfaces for read and write
	ZeroMemory(&srcDDSD, sizeof(srcDDSD));
	srcDDSD.dwSize = sizeof(srcDDSD);
	src->Lock(NULL, &srcDDSD, DDLOCK_WAIT, NULL);
    
	ZeroMemory(&destDDSD, sizeof(destDDSD));
	destDDSD.dwSize = sizeof(destDDSD);
	dest->Lock(NULL, &destDDSD, DDLOCK_WAIT, NULL);

    // Set the pitch for both surfaces
    SpritePitch = srcDDSD.lPitch;
    dPitch      = destDDSD.lPitch;

    // Initialize the pointers to the upper left hand corner of the surface
    lpSprite = (BYTE*)srcDDSD.lpSurface;
    lpDest   = (BYTE*)destDDSD.lpSurface;

	// Get the color key for sprite surface
	sColorKey = ColorKey;

	// Start RGB Format switch statement
	switch(BPP)
	{
	case 8:
		// IMHO paletized modes are a thing of the past please feel free to 
		// implement this if you so desire.
		break;

	case 15:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card that uses the 5-5-5 format 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
		lpDest   += (lDestY * dPitch) + (lDestX * 2);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2 * width));
		dbuf = (WORD)(dPitch - (2 * width));

		// Is the Sprite width odd or even?
		if (width % 2 == 1)
		{
			oddWidth = TRUE;
			width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
		}
		else
			width = width / 2;  //div by 2, processing 2 pixels at a time.


		i = height;
		do
		{
			if (oddWidth)
			{
				sTemp = *((WORD*)lpSprite);

				if (sTemp != sColorKey)
				{
					dTemp = *((WORD*)lpDest);
					*((WORD*)lpDest) = (WORD)(((sTemp & 0x7BDE) >> 1) + ((dTemp & 0x7BDE) >> 1));
				}

				lpDest   += 2;
				lpSprite += 2;
			}

			j = width;
			do
			{
				sTemp  = *((DWORD*)lpSprite);
				dTemp  = *((DWORD*)lpDest);
				Result = dTemp;

				if ((sTemp & 0xFFFF) != sColorKey)
				{
					Result &= 0xFFFF0000;
					Result |= ((sTemp & 0x7BDE) >> 1) + ((dTemp & 0x7BDE) >> 1);
				}
				if ((sTemp >> 16) != sColorKey)
				{
					Result &= 0xFFFF;
					Result |= ((sTemp & 0x7BDE0000) >> 1) + ((dTemp & 0x7BDE0000) >> 1);
				}

				*((DWORD*)lpDest) = Result;
				lpDest   += 4;
				lpSprite += 4;
			}while (--j > 0);
			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);

		break;

	case 16:

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
		lpDest   += (lDestY * dPitch) + (lDestX * 2);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2 * width));
		dbuf = (WORD)(dPitch - (2 * width));

		// Is the Sprite width odd or even?
		if (width % 2 == 1)
		{
			oddWidth = TRUE;
			width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
		}
		else
			width = width / 2;  //div by 2, processing 2 pixels at a time.

		i = height;
		do
		{
			if (oddWidth)
			{
				sTemp = *((WORD*)lpSprite);

				if (sTemp != sColorKey)
				{
					dTemp = *((WORD*)lpDest);
					*((WORD*)lpDest) = (WORD)(((sTemp & 0xF7DE) >> 1) + ((dTemp & 0xF7DE) >> 1));
				}

				lpDest   += 2;
				lpSprite += 2;
			}

			j = width;
			do
			{
				sTemp  = *((DWORD*)lpSprite);
				dTemp  = *((DWORD*)lpDest);
				Result = dTemp;

				if ((sTemp & 0xFFFF) != sColorKey)
				{
					Result &= 0xFFFF0000;
					Result |= ((sTemp & 0xF7DE) >> 1) + ((dTemp & 0xF7DE) >> 1);
				}
				if ((sTemp >> 16) != sColorKey)
				{
					Result &= 0xFFFF;
					Result |= ((sTemp & 0xF7DE0000) >> 1) + ((dTemp & 0xF7DE0000) >> 1);
				}

				*((DWORD*)lpDest) = Result;
				lpDest   += 4;
				lpSprite += 4;

			}while (--j > 0);
			lpDest += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;

	case 24:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card capable of 24bit rendering 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 3);
		lpDest   += (lDestY * dPitch) + (lDestX * 3);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (3 * width));
		dbuf = (WORD)(dPitch - (3 * width));

		i = height;
		do
		{
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ((sTemp &= 0xFFFFFF) != sColorKey)
				{
					dTemp  = *((DWORD*)lpDest);
					Result = ((sTemp & 0xFEFEFE) >> 1) + ((dTemp & 0xFEFEFE) >> 1);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest++;
				}
				else
				{
					lpDest += 3;
				}

				lpSprite += 3;

			}while (--j > 0);
			lpDest += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;

	case 32:
		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 4);
		lpDest   += (lDestY * dPitch) + (lDestX * 4);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (4 * width));
		dbuf = (WORD)(dPitch - (4 * width));

		i = height;
		do
		{
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ((sTemp &= 0xFFFFFF) != sColorKey)
				{
					dTemp  = *((DWORD*)lpDest);
					Result = ((sTemp & 0xFEFEFE) >> 1) + ((dTemp & 0xFEFEFE) >> 1);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest += 2;
				}
				else
				{
					lpDest += 4;
				}

				lpSprite += 4;

			}while (--j > 0);
			lpDest += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;
	} // End RGB Format switch statement


    src->Unlock(NULL);
    dest->Unlock(NULL);

	return DD_OK;
}


//////////////////////////////////////////////////////////////////////////////////
// TransAlphaImproved - 
//////////////////////////////////////////////////////////////////////////////////
HRESULT TransAlphaImproved(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dest, 
				   LONG lDestX, LONG lDestY, RECT srcRect, WORD ALPHA, DWORD ColorKey, WORD BPP)
{
	int register i,j;
	int height,width;
	BYTE* lpSprite;
	BYTE* lpDest;
	WORD dPitch, SpritePitch;
	DWORD sColorKey;
	DWORD sTemp,dTemp;
	DWORD sr,sg,sb,dr,dg,db;
	WORD sbuf,dbuf;
	DWORD Result;
	BOOL oddWidth = FALSE;
	DDSURFACEDESC2 srcDDSD, destDDSD;
	DWORD REDC,GREENC, BLUEC;
	DWORD PLUS64;
	DWORD ALPHABY4;
	DWORD doubleColorKey;


	// Check the ALPHA value
	if (ALPHA < 0)
		ALPHA = 0;
	else if (ALPHA > 256)
		ALPHA = 256;

	// Set height and width of SPRITE
    height = srcRect.bottom - srcRect.top;
    width = srcRect.right - srcRect.left; 

	// Lock down both surfaces for read and write
	ZeroMemory(&srcDDSD, sizeof(srcDDSD));
	srcDDSD.dwSize = sizeof(srcDDSD);
	src->Lock(NULL, &srcDDSD, DDLOCK_WAIT, NULL);
    
	ZeroMemory(&destDDSD, sizeof(destDDSD));
	destDDSD.dwSize = sizeof(destDDSD);
	dest->Lock(NULL, &destDDSD, DDLOCK_WAIT, NULL);

    // Get the color key for sprite surface
    sColorKey = ColorKey;

	// Set the pitch for both surfaces
    SpritePitch = (WORD)srcDDSD.lPitch;
    dPitch      = (WORD)destDDSD.lPitch;

    // Initialize the pointers to the upper left hand corner of surface
    lpSprite = (BYTE*)srcDDSD.lpSurface;
    lpDest   = (BYTE*)destDDSD.lpSurface;

	// Do some work outside of the loop
	PLUS64         = 64 | (64 << 16);
	ALPHABY4      = (ALPHA / 4) | ((ALPHA / 4) << 16);
	doubleColorKey = ColorKey | (ColorKey << 16);

	switch(BPP)
	{
	case 8:
		// IMHO paletized modes are a thing of the past please feel free to 
		// implement this if you so desire.
		break;

	case 15:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card that uses the 5-5-5 format 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////
		
		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
		lpDest   += (lDestY * dPitch) + (lDestX * 2);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2 * width));
		dbuf = (WORD)(dPitch - (2 * width));

		// Is the Sprite width odd or even?
		if (width % 2 == 1)
		{
			oddWidth = TRUE;
			width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
		}
		else
			width = width / 2;  //div by 2, processing 2 pixels at a time.

		i = height;
		do
		{
			if (oddWidth)
			{
				sTemp = *((WORD*)lpSprite);

				if (sTemp != sColorKey)
				{
					dTemp = *((WORD*)lpDest);
					sb = sTemp & 0x1f;
					db = dTemp & 0x1f;
					sg = (sTemp >> 5) & 0x1f;
					dg = (dTemp >> 5) & 0x1f;
					sr = (sTemp >> 10) & 0x1f;
					dr = (dTemp >> 10) & 0x1f;

					*((WORD*)lpDest) = (WORD)((ALPHA * (db - sb) >> 8) + sb |
						((ALPHA * (dg - sg) >> 8) + sg) << 5 |
						((ALPHA * (dr - sr) >> 8) + sr) << 10);
				}

				lpDest += 2;
				lpSprite += 2;
			}
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ( sTemp != doubleColorKey )
				{
					dTemp = *((DWORD*)lpDest);

					sb = sTemp & 0x001F001F;
					db = dTemp & 0x001F001F;
					sg = (sTemp >> 5)  & 0x001F001F;
					dg = (dTemp >> 5)  & 0x001F001F;
					sr = (sTemp >> 10) & 0x001F001F;
					dr = (dTemp >> 10) & 0x001F001F;

					BLUEC  = ((((ALPHA * ((sb + PLUS64) - db)) >> 8) + db) - ALPHABY4) & 0x001F001F;
					GREENC = (((((ALPHA * ((sg + PLUS64) - dg)) >> 8) + dg) - ALPHABY4) & 0x001F001F) << 5;
					REDC   = (((((ALPHA * ((sr + PLUS64) - dr)) >> 8) + dr) - ALPHABY4) & 0x001F001F) << 10;

					Result = BLUEC | GREENC | REDC;

					if ( (sTemp >> 16) == ColorKey )
							Result = (Result & 0xFFFF) | (dTemp & 0xFFFF0000);
					else if ( (sTemp & 0xFFFF) == ColorKey )
							Result = (Result & 0xFFFF0000) | (dTemp & 0xFFFF);

					*((DWORD*)lpDest) = Result;
				}
				lpDest    += 4;
				lpSprite  += 4;

			}while (--j > 0);

			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);

		break;

	case 16:

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
		lpDest   += (lDestY * dPitch) + (lDestX * 2);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2 * width));
		dbuf = (WORD)(dPitch - (2 * width));

		// Is the Sprite width odd or even?
		if (width % 2 == 1)
		{
			oddWidth = TRUE;
			width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
		}
		else
			width = width / 2;  //div by 2, processing 2 pixels at a time.


		i = height;
		do
		{
			if (oddWidth)
			{
				sTemp = *((WORD*)lpSprite);

				if (sTemp != ColorKey)
				{
					dTemp = *((WORD*)lpDest);
					sb = sTemp & 0x1f;
					db = dTemp & 0x1f;
					sg = (sTemp >> 5) & 0x3f;
					dg = (dTemp >> 5) & 0x3f;
					sr = (sTemp >> 11) & 0x1f;
					dr = (dTemp >> 11) & 0x1f;

					*((WORD*)lpDest) = (WORD)((ALPHA * (sb - db) >> 8) + db |
						((ALPHA * (sg - dg) >> 8) + dg) << 5 |
						((ALPHA * (sr - dr) >> 8) + dr) << 11);
				}

				lpDest   += 2;
				lpSprite += 2;
			}
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ( sTemp != doubleColorKey )
				{
					dTemp = *((DWORD*)lpDest);

					sb = sTemp & 0x001F001F;
					db = dTemp & 0x001F001F;
					sg = (sTemp >> 5)  & 0x003F003F;
					dg = (dTemp >> 5)  & 0x003F003F;
					sr = (sTemp >> 11) & 0x001F001F;
					dr = (dTemp >> 11) & 0x001F001F;

					BLUEC  = ((((ALPHA * ((sb + PLUS64) - db)) >> 8) + db) - ALPHABY4) & 0x001F001F;
					GREENC = (((((ALPHA * ((sg + PLUS64) - dg)) >> 8) + dg) - ALPHABY4) & 0x003F003F) << 5;
					REDC   = (((((ALPHA * ((sr + PLUS64) - dr)) >> 8) + dr) - ALPHABY4) & 0x001F001F) << 11;

					Result = BLUEC | GREENC | REDC;

					if ( (sTemp >> 16) == ColorKey )
							Result = (Result & 0xFFFF) | (dTemp & 0xFFFF0000);
					else if ( (sTemp & 0xFFFF) == ColorKey )
							Result = (Result & 0xFFFF0000) | (dTemp & 0xFFFF);

					*((DWORD*)lpDest) = Result;
				}
				lpDest    += 4;
				lpSprite  += 4;

			}while (--j > 0);

			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);

		break;

	case 24:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card capable of 24bit rendering 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 3);
		lpDest   += (lDestY * dPitch) + (lDestX * 3);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (3 * width));
		dbuf = (WORD)(dPitch - (3 * width));

		i = height;
		do
		{
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ((sTemp & 0xFFFFFF) != sColorKey)
				{
					dTemp = *((DWORD*)lpDest);
					sb = sTemp & 0xFF;
					db = dTemp & 0xFF;
					sg = (sTemp >> 8) & 0xFF;
					dg = (dTemp >> 8) & 0xFF;
					sr = (sTemp >> 16) & 0xFF;
					dr = (dTemp >> 16) & 0xFF;

					Result = (DWORD)((ALPHA * (db - sb) >> 8) + sb |
						((ALPHA * (dg - sg) >> 8) + sg) << 8 |
						((ALPHA * (dr - sr) >> 8) + sr) << 16);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest++;
				}
				else
				{
					lpDest += 3;
				}

				lpSprite += 3;

			}while (--j > 0);
			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;

	case 32:

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 4);
		lpDest   += (lDestY * dPitch) + (lDestX * 4);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (4 * width));
		dbuf = (WORD)(dPitch - (4 * width));

		i = height;
		do
		{
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ((sTemp & 0xFFFFFF) != sColorKey)
				{
					dTemp = *((DWORD*)lpDest);
					sb = sTemp & 0xFF;
					db = dTemp & 0xFF;
					sg = (sTemp >> 8) & 0xFF;
					dg = (dTemp >> 8) & 0xFF;
					sr = (sTemp >> 16) & 0xFF;
					dr = (dTemp >> 16) & 0xFF;

					Result = (DWORD)((ALPHA * (db - sb) >> 8) + sb |
						((ALPHA * (dg - sg) >> 8) + sg) << 8 |
						((ALPHA * (dr - sr) >> 8) + sr) << 16);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest += 2;
				}
				else
				{
					lpDest += 4;
				}

				lpSprite += 4;

			}while (--j > 0);
			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;
	} // End RGB Format switch statement


	src->Unlock(NULL);
	dest->Unlock(NULL);

	return DD_OK;
}