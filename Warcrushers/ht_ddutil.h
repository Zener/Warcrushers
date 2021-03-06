/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddutil.cpp
 *  Content:    Routines for loading bitmap and palettes from resources
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

extern IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap);
extern IDirectDrawSurface * DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy, int memLoc);
extern HRESULT              DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
extern HRESULT              DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD                DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT TransAlphaMMX(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dest,
   RECT srcRect, RECT destRect, WORD ALPHA, DWORD ColorKey, WORD BPP);
extern HRESULT TransAlphaImproved(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dest, 
				   LONG lDestX, LONG lDestY, RECT srcRect, WORD ALPHA, DWORD ColorKey, WORD BPP);
extern HRESULT TransAlphaFast(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dest, 
					   LONG lDestX, LONG lDestY, RECT srcRect, DWORD ColorKey, WORD BPP);


#ifdef __cplusplus
}
#endif  /* __cplusplus */
       


