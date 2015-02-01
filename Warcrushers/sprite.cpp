#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "sprite.hpp"
#include "ddutils.hpp"
#include "ht_ddutil.h"

sprite::sprite()
{
	init = false;
}


sprite::sprite(char *name,IDirectDraw4 *pdd)
{
//HBITMAP             hbm;
BITMAP              bm;
DDSURFACEDESC2       ddsd;

hbm=(HBITMAP)LoadImage(NULL,name,IMAGE_BITMAP,0,0,
					   LR_LOADFROMFILE|LR_CREATEDIBSECTION);
if (hbm == NULL)
	{
	exit (-1);
	}

int res=GetObject(hbm,sizeof(bm),&bm);      // get size of sprite

ZeroMemory(&ddsd, sizeof(ddsd));
ddsd.dwSize = sizeof(ddsd);
ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
ddsd.dwWidth = bm.bmWidth;
ddsd.dwHeight = bm.bmHeight;

if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
	{
	exit(-2);
	}
copy(pdds,hbm,0,0,0,0);
//DeleteObject(hbm);
}



void sprite::load(char *_name, int flag,IDirectDraw4 *pdd)
{

BITMAP              bm;
DDSURFACEDESC2     ddsd;

name = new char[strlen(_name)];
strcpy(name, _name);

hbm=(HBITMAP)LoadImage(NULL,name,IMAGE_BITMAP,0,0,
					   LR_LOADFROMFILE|LR_CREATEDIBSECTION);
if (hbm == NULL)
	{
	exit (-1);
	}

int res=GetObject(hbm,sizeof(bm),&bm);      // get size of sprite

ZeroMemory(&ddsd, sizeof(ddsd));
ddsd.dwSize = sizeof(ddsd);
ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
if (flag) ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY; 
ddsd.dwWidth = bm.bmWidth;
ddsd.dwHeight = bm.bmHeight;
width = bm.bmWidth;
height = bm.bmHeight;


HRESULT hres=pdd->CreateSurface(&ddsd, &pdds, NULL);
dddebugmsg(hres);
copy(pdds,hbm,0,0,0,0);
//DeleteObject(hbm);

if( pdds == NULL )
	{
	exit(-3);
	}

if (!init)
	SpriteManager::AddSprite(this);

init = true;
}


HRESULT sprite::reload()//char *_name)
{
//HBITMAP             hbm;
HRESULT             hr;


hbm = (HBITMAP)LoadImage(NULL,name,IMAGE_BITMAP,0,0,
						 LR_LOADFROMFILE|LR_CREATEDIBSECTION);

if (hbm == NULL)
	{
	OutputDebugString("handle is null\n");
	return E_FAIL;
	}

hr = copy(pdds, hbm, 0, 0, 0, 0);
if (hr != DD_OK)
	{
	OutputDebugString("ddcopybitmap failed\n");
	}

//DeleteObject(hbm);
return hr;
}


void sprite::blitfast(int x1,int y1,int x2,int y2,int ox, int oy,DWORD mode,
					LPDIRECTDRAWSURFACE4 &lpDDSBack)
{
RECT rcRect;
    
// redraw border
rcRect.left = x1;
rcRect.top = y1;
rcRect.right = x2;
rcRect.bottom = y2;
lpDDSBack->BltFast( ox,oy,pdds,&rcRect, mode | DDBLTFAST_WAIT );
}



void sprite::blit(int x1,int y1,int x2,int y2,int ox, int oy,DWORD mode,
					LPDIRECTDRAWSURFACE4 &lpDDSBack, int extra)
{
RECT		srcRect,destRect;
HRESULT		ddrval;

    
// redraw border
srcRect.left = x1;
srcRect.top = y1;
srcRect.right = x2;
srcRect.bottom = y2;

destRect.left = ox;
destRect.top = oy;
destRect.right = ox+(x2-x1);
destRect.bottom = oy+(y2-y1);

    //extra = 0;
    if (extra)
	{
		DDBLTFX     ops; 
		ops.dwSize = sizeof( ops ); 
	    //ops.dwDDFX = 0;	
		//ops.dwDDFX = DDBLTFX_MIRRORUPDOWN;
		ops.dwDDFX = DDBLTFX_MIRRORLEFTRIGHT;
		// vease que pasamos NULL en el campo DDBLTFX. Si quereis efectos
		// espec	taculares debereis rehacer esa parte de la llamada.
		ddrval=lpDDSBack->Blt(&destRect,pdds,&srcRect, mode | DDBLT_DDFX | DDBLT_WAIT  , &ops);

	}
	else
		ddrval=lpDDSBack->Blt(&destRect,pdds,&srcRect, mode | DDBLT_WAIT  , NULL);

}

void sprite::blittrans(int x1,int y1,int x2,int y2,int ox, int oy,DWORD mode,
					LPDIRECTDRAWSURFACE4 &lpDDSBack, int alpha)
{
	RECT		srcRect,destRect;
	HRESULT		ddrval;
    
	// redraw border
	srcRect.left = x1;
	srcRect.top = y1;
	srcRect.right = x2;
	srcRect.bottom = y2;

	destRect.left = ox;
	destRect.top = oy;
	destRect.right = ox+(x2-x1);
	destRect.bottom = oy+(y2-y1);

	//TransAlphaFast(pdds, lpDDSBack, ox, oy, srcRect, 65535, 16);
    //TransAlphaImproved(pdds, lpDDSBack, ox, oy, srcRect, alpha, 65535, 16);
    TransAlphaMMX(pdds, lpDDSBack, srcRect, destRect, alpha, 65535, 16);
}





//set a color key for a surface, given a RGB.
//if you pass CLR_INVALID as the color key, the pixel
//in the upper-left corner will be used.
HRESULT sprite::setcolorkey(COLORREF rgb)
{
DDCOLORKEY ddck;

ddck.dwColorSpaceLowValue  = colormatch(pdds, rgb);
ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}



//draw a sprite into a DirectDrawSurface
HRESULT sprite::copy(IDirectDrawSurface4 *pdds,HBITMAP hbm,
					 int x, int y, int dx, int dy)
{
HDC                 hdcImage;
HDC                 hdc;
BITMAP              bm;
DDSURFACEDESC2      ddsd;
HRESULT             hr;

if (hbm == NULL || pdds == NULL) return E_FAIL;

// make sure this surface is restored.
pdds->Restore();

//  select sprite into a memoryDC so we can use it.
hdcImage = CreateCompatibleDC(NULL);
if (!hdcImage)
	OutputDebugString("createcompatible dc failed\n");
SelectObject(hdcImage, hbm);

// get size of the sprite
GetObject(hbm, sizeof(bm), &bm);    // get size of sprite
dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
dy = dy == 0 ? bm.bmHeight : dy;

// get size of surface.
ddsd.dwSize = sizeof(ddsd);
ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
pdds->GetSurfaceDesc(&ddsd);

if ((hr = pdds->GetDC(&hdc)) == DD_OK)
	{
	StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, 
				x, y, dx, dy, SRCCOPY);
	pdds->ReleaseDC(hdc);
	}
DeleteDC(hdcImage);
return hr;
}


//convert a RGB color to a pysical color.
//we do this by leting GDI SetPixel() do the color matching
//then we lock the memory and see what it got mapped to.
DWORD sprite::colormatch(IDirectDrawSurface4 *pdds, COLORREF rgb)
{
COLORREF rgbT;
HDC hdc;
DWORD dw = CLR_INVALID;
DDSURFACEDESC2 ddsd;
HRESULT hres;

//use GDI SetPixel to color match for us
if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
	rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
	SetPixel(hdc, 0, 0, rgb);               // set our value
	pdds->ReleaseDC(hdc);
	}

// now lock the surface so we can read back the converted color
ddsd.dwSize = sizeof(ddsd);
while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING);

if (hres == DD_OK)
	{
	dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
	dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
	pdds->Unlock(NULL);
	}

//  now put the color that was there back.
//
if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
	SetPixel(hdc, 0, 0, rgbT);
	pdds->ReleaseDC(hdc);
	}
return dw;
}


HRESULT sprite::restore()
{
return pdds->Restore();
}


sprite* list[MAXSPRITES];	
int counter;


	 void SpriteManager::Init()
	{
		counter = 0;
	}


void SpriteManager::AddSprite(sprite *s)
{
		list[counter] = s;
		counter++;
}


void SpriteManager::RestoreAll()
{
	for(int i = 0; i < counter;i++)
	{
		list[i]->pdds->Restore();
		list[i]->reload();
	}
}

/*sprite::~sprite()
{
if( pdds != NULL )
	{
	pdds->Release();
	pdds=NULL;
	}
}*/


