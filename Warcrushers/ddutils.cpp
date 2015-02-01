//#include "defines.hpp"
#define SCREENX 800
#define SCREENY 600
//#include <string.h>
#include "ddutils.hpp"
#include <stdio.h>
//#include <iostream.h>


char *fsize;

void InitFonts()
{
	FILE *fd;

	fsize = new char[256];
	fd = fopen("img\\hud\\fontmetrics.dat", "rb");
	if (fd != NULL)
	{//loadFromFile(fd);
		
		for(int i = 0; i< 256;i++)
			if (fread(&fsize[i],sizeof(char),1,fd) < 0) break;
	}
	fclose(fd);
}




void dddebugmsg(HRESULT h)
{
	/*
switch (h)
	{
	case DD_OK:
		cout << "The request completed successfully." << endl; 
		break;
	case DDERR_ALREADYINITIALIZED :
		cout << "The object has already been initialized." << endl;
		break;
	case DDERR_BLTFASTCANTCLIP :
		cout << "A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface2::BltFast method. " << endl;
		break;
	case DDERR_CANNOTATTACHSURFACE :
		cout << "A surface cannot be attached to another requested surface. " << endl;
	case DDERR_CANNOTDETACHSURFACE :
		cout << "A surface cannot be detached from another requested surface. " << endl;
		break;
	case DDERR_CANTCREATEDC :
		cout << "Windows cannot create any more device contexts (DCs). " << endl;
		break;
	case DDERR_CANTDUPLICATE :
		cout << "Primary and 3D surfaces, or surfaces that are implicitly created, cannot be duplicated. " << endl;
		break;
	case DDERR_CANTLOCKSURFACE :
		cout << "Access to this surface is refused because an attempt was made to lock the primary surface without DCI support. " << endl;
		break;
	case DDERR_CANTPAGELOCK :
		cout << "An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface. " << endl;
		break;
	case DDERR_CANTPAGEUNLOCK :
		cout << "An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface. " << endl;
		break;
	case DDERR_CLIPPERISUSINGHWND :
		cout << "An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle. " << endl;
		break;
	case DDERR_COLORKEYNOTSET :
		cout << "No source color key is specified for this operation. " << endl;
		break;
	case DDERR_CURRENTLYNOTAVAIL :
		cout << "No support is currently available. " << endl;
		break;
	case DDERR_DCALREADYCREATED :
		cout << "A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface. " << endl;
		break;
	case DDERR_DIRECTDRAWALREADYCREATED :
		cout << "A DirectDraw object representing this driver has already been created for this process. " << endl;
		break;
	case DDERR_EXCEPTION :
		cout << "An exception was encountered while performing the requested operation. " << endl;
		break;
	case DDERR_EXCLUSIVEMODEALREADYSET :
		cout << "An attempt was made to set the cooperative level when it was already set to exclusive. " << endl;
		break;
	case DDERR_GENERIC :
		cout << "There is an undefined error condition. " << endl;
		break;
	case DDERR_HEIGHTALIGN :
		cout << "The height of the provided rectangle is not a multiple of the required alignment. " << endl;
		break;
	case DDERR_HWNDALREADYSET :
		cout << "The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created. " << endl;
		break;
	case DDERR_HWNDSUBCLASSED :
		cout << "DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed. " << endl;
		break;
	case DDERR_IMPLICITLYCREATED :
		cout << "The surface cannot be restored because it is an implicitly created surface. " << endl;
		break;
	case DDERR_INCOMPATIBLEPRIMARY :
		cout << "The primary surface creation request does not match with the existing primary surface." << endl; 
		break;
	case DDERR_INVALIDCAPS :
		cout << "One or more of the capability bits passed to the callback function are incorrect. " << endl;
		break;
	case DDERR_INVALIDCLIPLIST :
		cout << "DirectDraw does not support the provided clip list. " << endl;
		break;
	case DDERR_INVALIDDIRECTDRAWGUID :
		cout << "The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier. " << endl;
		break;
	case DDERR_INVALIDMODE :
		cout << "DirectDraw does not support the requested mode. " << endl;
		break;
	case DDERR_INVALIDOBJECT :
		cout << "DirectDraw received a pointer that was an invalid DirectDraw object. " << endl;
		break;
	case DDERR_INVALIDPARAMS :

		cout << "One or more of the parameters passed to the method are incorrect. " << endl;
		break;
	case DDERR_INVALIDPIXELFORMAT :
		cout << "The pixel format was invalid as specified. " << endl;
		break;
	case DDERR_INVALIDPOSITION :
		cout << "The position of the overlay on the destination is no longer legal. " << endl;
		break;
	case DDERR_INVALIDRECT :
		cout << "The provided rectangle was invalid. " << endl; 
		break;
	case DDERR_INVALIDSURFACETYPE :
		cout << "The requested operation could not be performed because the surface was of the wrong type. " << endl;
		break;
	case DDERR_LOCKEDSURFACES :
		cout << "One or more surfaces are locked, causing the failure of the requested operation. " << endl;
		break;
	case DDERR_NO3D :
		cout << "No 3D hardware or emulation is present. " << endl;
		break;
	case DDERR_NOALPHAHW :
		cout << "No alpha acceleration hardware is present or available, causing the failure of the requested operation. " << endl;
		break;
	case DDERR_NOBLTHW :
		cout << "No blitter hardware is present. " << endl;
		break;
	case DDERR_NOCLIPLIST :
		cout << "No clip list is available. " << endl;
		break;
	case DDERR_NOCLIPPERATTACHED :
		cout << "No DirectDrawClipper object is attached to the surface object. " << endl;
		break;
	case DDERR_NOCOLORCONVHW :
		cout << "The operation cannot be carried out because no color-conversion hardware is present or available. " << endl;
		break;
	case DDERR_NOCOLORKEY :
		cout << "The surface does not currently have a color key. " << endl;
		break;
	case DDERR_NOCOLORKEYHW :
		cout << "The operation cannot be carried out because there is no hardware support for the destination color key. " << endl;
		break;
	case DDERR_NOCOOPERATIVELEVELSET :
		cout << "A create function is called without the IDirectDraw2::SetCooperativeLevel method being called. " << endl;
		break;
	case DDERR_NODC :
		cout << "No DC has ever been created for this surface. " << endl;
		break;
	case DDERR_NODDROPSHW :
		cout << "No DirectDraw raster operation (ROP) hardware is available. " << endl;
		break;
	case DDERR_NODIRECTDRAWHW :
		cout << "Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware. " << endl;
		break;
	case DDERR_NODIRECTDRAWSUPPORT :
		cout << "DirectDraw support is not possible with the current display driver. " << endl;
		break;
	case DDERR_NOEMULATION :
		cout << "Software emulation is not available. " << endl;
		break;
	case DDERR_NOEXCLUSIVEMODE :
		cout << "The operation requires the application to have exclusive mode, but the application does not have exclusive mode. " << endl;
		break;
	case DDERR_NOFLIPHW :
		cout << "Flipping visible surfaces is not supported. " << endl;
		break;
	case DDERR_NOGDI :
		cout << "No GDI is present. " << endl;
		break;
	case DDERR_NOHWND :
		cout << "Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle. " << endl;
		break;
	case DDERR_NOMIPMAPHW :
		cout << "The operation cannot be carried out because no mipmap texture mapping hardware is present or available. " << endl;
		break;
	case DDERR_NOMIRRORHW :
		cout << "The operation cannot be carried out because no mirroring hardware is present or available. " << endl;
		break;
	case DDERR_NOOVERLAYDEST :
		cout << "The IDirectDrawSurface2::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface2::UpdateOverlay method has not been called on to establish a destination. " << endl;
		break;
	case DDERR_NOOVERLAYHW :
		cout << "The operation cannot be carried out because no overlay hardware is present or available. " << endl;
		break;
	case DDERR_NOPALETTEATTACHED :
		cout << "No palette object is attached to this surface. " << endl;
		break;
	case DDERR_NOPALETTEHW :
		cout << "There is no hardware support for 16- or 256-color palettes. " << endl;
		break;
	case DDERR_NORASTEROPHW :
		cout << "The operation cannot be carried out because no appropriate raster operation hardware is present or available. " << endl;
		break;
	case DDERR_NOROTATIONHW :
		cout << "The operation cannot be carried out because no rotation hardware is present or available. " << endl;
		break;
	case DDERR_NOSTRETCHHW :
		cout << "The operation cannot be carried out because there is no hardware support for stretching. " << endl;
		break;
	case DDERR_NOT4BITCOLOR :
		cout << "The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette. " << endl;
		break;
	case DDERR_NOT4BITCOLORINDEX :
		cout << "The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette. " << endl;
		break;
	case DDERR_NOT8BITCOLOR :
		cout << "The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette. " << endl;
		break;
	case DDERR_NOTAOVERLAYSURFACE :
		cout << "An overlay component is called for a non-overlay surface. " << endl;
		break;
	case DDERR_NOTEXTUREHW :
		cout << "The operation cannot be carried out because no texture-mapping hardw are is present or available. " << endl;
		break;
	case DDERR_NOTFLIPPABLE :
		cout << "An attempt has been made to flip a surface that cannot be flipped. " << endl;
		break;
	case DDERR_NOTFOUND :
		cout << "The requested item was not found. " << endl;
		break;
	case DDERR_NOTINITIALIZED :
		cout << "An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized. " << endl;
		break;
	case DDERR_NOTLOCKED :
		cout << "An attempt is made to unlock a surface that was not locked. " << endl;
		break;
	case DDERR_NOTPAGELOCKED :
		cout << "An attempt is made to page unlock a surface with no outstanding page locks. " << endl;
		break;
	case DDERR_NOTPALETTIZED :
		cout << "The surface being used is not a palette-based surface. " << endl;
		break;
	case DDERR_NOVSYNCHW :
		cout << "The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations. " << endl;
		break;
	case DDERR_NOZBUFFERHW :
		cout << "The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers. " << endl;
		break;
	case DDERR_NOZOVERLAYHW :
		cout << "The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays. " << endl;
		break;
	case DDERR_OUTOFCAPS :
		cout << "The hardware needed for the requested operation has already been allocated. " << endl;
		break;
	case DDERR_OUTOFMEMORY: 
		cout << "DirectDraw does not have enough memory to perform the operation. " << endl;
		break;
	case DDERR_OUTOFVIDEOMEMORY :
		cout << "DirectDraw does not have enough display memory to perform the operation. " << endl;
		break;
	case DDERR_OVERLAYCANTCLIP :
		cout << "The hardware does not support clipped overlays. " << endl;
		break;
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE :
		cout << "An attempt was made to have more than one color key active on an overlay. " << endl;
		break;
	case DDERR_OVERLAYNOTVISIBLE :
		cout << "The IDirectDrawSurface2::GetOverlayPosition method is called on a hidden overlay. " << endl;
		break;
	case DDERR_PALETTEBUSY :
		cout << "Access to this palette is refused because the palette is locked by another thread. " << endl;
		break;
	case DDERR_PRIMARYSURFACEALREADYEXISTS :
		cout << "This process has already created a primary surface. " << endl;
		break;
	case DDERR_REGIONTOOSMALL :
		cout << "The region passed to the IDirectDrawClipper::GetClipList method end is too small. " << endl;
		break;
	case DDERR_SURFACEALREADYATTACHED :
		cout << "An attempt was made to attach a surface to another surface to which it is already attached. " << endl;
		break;
	case DDERR_SURFACEALREADYDEPENDENT :
		cout << "An attempt was made to make a surface a dependency of another surface to which it is already dependent." << endl; 
		break;
	case DDERR_SURFACEBUSY :
		cout << "Access to the surface is refused because the surface is locked by another thread. " << endl;
		break;
	case DDERR_SURFACEISOBSCURED :
		cout << "Access to the surface is refused because the surface is obscured. " << endl;
		break;
	case DDERR_SURFACELOST :
		cout << "Access to the surface is refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have the IDirectDrawSurface2::Restore method called on it. " << endl;
		break;
	case DDERR_SURFACENOTATTACHED :
		cout << "The requested surface is not attached. " << endl;
		break;
	case DDERR_TOOBIGHEIGHT :
		cout << "The height requested by DirectDraw is too large. " << endl;
		break;
	case DDERR_TOOBIGSIZE :
		cout << "The size requested by DirectDraw is too large. However, the individual height and width are OK. " << endl;
		break;
	case DDERR_TOOBIGWIDTH :
		cout << "The width requested by DirectDraw is too large. " << endl;
		break;
	case DDERR_UNSUPPORTED :
		cout << "The operation is not supported. " << endl;
		break;
	case DDERR_UNSUPPORTEDFORMAT :
		cout << "The FourCC format requested is not supported by DirectDraw. " << endl;
		break;
	case DDERR_UNSUPPORTEDMASK :
		cout << "The bitmask in the pixel format requested is not supported by DirectDraw. " << endl;
		break;
	case DDERR_UNSUPPORTEDMODE :
		cout << "The display is currently in an unsupported mode. " << endl;
		break;
	case DDERR_VERTICALBLANKINPROGRESS :
		cout << "A vertical blank is in progress. " << endl;
		break;
	case DDERR_WASSTILLDRAWING :
		cout << "The previous blit operation that is transferring information to or from this surface is incomplete. " << endl;
		break;
	case DDERR_WRONGMODE :
		cout << "This surface cannot be restored because it was created in a different mode. " << endl;
		break;
	case DDERR_XALIGN :
		cout << "The provided rectangle was not horizontally aligned on a required boundary. " << endl;
		break;
	}*/
}

void FillRectangle(LPDIRECTDRAWSURFACE4 &lpdds,int x, int y, int w, int h, int r,int g, int b)
{
	RECT destRect;
    
	// redraw border
	destRect.left = x;
	destRect.top = y;
	destRect.right = x+w;
	destRect.bottom = y+h;

	HRESULT ddrval;
	DDBLTFX ddbltfx; 
	ddbltfx.dwSize = sizeof(ddbltfx); 
	ddbltfx.dwFillColor = ((r>>3)<<11) | ((g>>2)<<5) | (b>>3); 
	ddrval = lpdds->Blt(
			&destRect,        // Destination is entire surface
			NULL,        // No source surface
			NULL,        // No source rectangle
			DDBLT_COLORFILL , &ddbltfx); 
}


void ddClearScreen(LPDIRECTDRAWSURFACE4 &lpdds,int r,int g, int b)
{
RECT destRect;
    
// redraw border
destRect.left = 0;
destRect.top = 0;
destRect.right = SCREENX;
destRect.bottom = SCREENY;

HRESULT ddrval;
DDBLTFX ddbltfx; 
ddbltfx.dwSize = sizeof(ddbltfx); 
ddbltfx.dwFillColor = RGB(r,g,b);
ddrval = lpdds->Blt(
		&destRect,        // Destination is entire surface
        NULL,        // No source surface
        NULL,        // No source rectangle
        DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx); 
}

void Fondo(LPDIRECTDRAWSURFACE4 &source,LPDIRECTDRAWSURFACE4 &lpdds)
{
RECT destRect;
    
// redraw border
destRect.left = 0;
destRect.top = 0;
destRect.right = SCREENX;
destRect.bottom = SCREENY;

HRESULT ddrval;
ddrval = lpdds->Blt(
		&destRect,        // Destination is entire surface
        source,        // No source surface
        &destRect,        // No source rectangle
         DDBLT_WAIT, NULL); 
}



////////////////////////////////////////////////////////////////////////
void PrintText(int x, int y, LPDIRECTDRAWSURFACE4 lpdds, char *text, COLORREF color)
{
	HDC hdc;
	lpdds->GetDC(&hdc);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, text, strlen(text));
	lpdds->ReleaseDC(hdc);
}


void PrintNumGFX(sprite font, int x, int y, int n, LPDIRECTDRAWSURFACE4 lpdds)
{
	char t[20];
	sprintf(t,"%d", n);
	UINT k = strlen(t)-1;
	for (UINT i = 0; i <= k; i++)
		font.blit(1+((t[k-i]-'0')*15),1,15+((t[k-i]-'0')*15),21,x-(i*14),y,DDBLT_KEYSRC,lpdds,0);
}

char s2[1024*4];

int getGFXStringWidth(char *ss, int start, int length)
{
	char *s1, *s;

	int d = 0;
	s1 = &ss[start];
	strncpy(s2, s1, length);
	s2[length] = '\0';

    s = s2;
		
    UINT k = strlen(s)-1;
	
    for (UINT i = 0; i <= k; i++)
	{
		int off = s[i];
		if (off < 0) off+= 256;
		d += fsize[off];
	}
	return d;
}


void PrintGFX(sprite font, int x, int y, char *ss, LPDIRECTDRAWSURFACE4 lpdds)
{
	char *s;
    s = ss;//_strlwr( _strdup( ss ) );
	
    UINT k = strlen(s)-1;
	int d = 0;
    for (UINT i = 0; i <= k; i++)
	{		
		int off = s[i];
		if (off < 0) off += 256;
		int _x = (off%16)*16;
		int _y = ((int)(off/16))*16;
		d += fsize[off]/2;
		font.blit(_x, _y, _x+16, _y+16, x+d, y , DDBLT_KEYSRC,lpdds,0);
		d += fsize[off]/2;	
	}
}

void PrintRGFX(sprite font, int x, int y, char *ss, LPDIRECTDRAWSURFACE4 lpdds)
{
	char *s;
    s = _strlwr( _strdup( ss ) );
	
    UINT k = strlen(s)-1;
	int d = 0;
    for (UINT i = k; i >= 0; i--)
	{
		/*
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			int off = s[i]-'a';
			font.blit(off*16,0,(off+1)*16,12,x+d, y , DDBLT_KEYSRC,lpdds,0);
			if (s[i] == 'i') d += 5;
			else if (s[i] == 'w') d += 15;
			else if (s[i] == 'l') d += 8;
			else d += 12;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			//int off = s[i]-'0';
			//font.blit(off*10,13,(off+1)*10,25,x, y , DDBLT_KEYSRC,lpdds,0);
			//d = d+9;
		}	
		else d = d+5;*/
	}
}

// Converts the supplied RGB values to a DWORD Pixel Formatted Colour
DWORD RGBToColour( DWORD Red, DWORD Green, DWORD Blue )
{
   // Supplied Values(0 - 255) are converted to Pixel Formatted Values
   // If 565 format and Red = 128, RedVal will become 16 since 128 / 256 == 16 / 32(5 bits)
   DWORD RedVal = ( Red * ( 1 << 8 )) / 256;
   DWORD GreenVal = ( Green * ( 1 << 4 )) / 256;
   DWORD BlueVal = ( Blue * ( 1 << 0 )) / 256;

   // Convert the Values to the appropriate Location in the returned colour value
   RedVal <<= 5;
   GreenVal <<= 2;
   BlueVal <<= 0;

   return RedVal | GreenVal | BlueVal;
}


void PutPixel( LPDIRECTDRAWSURFACE4 TempSurf, int X, int Y, int Red, int Green, int Blue )
{
   DDSURFACEDESC2 DDSurfDesc;
   BYTE* SurfPtr;

   ZeroMemory( &DDSurfDesc, sizeof( DDSurfDesc ));
   DDSurfDesc.dwSize = sizeof( DDSurfDesc );


   TempSurf->Lock( 0, &DDSurfDesc, DDLOCK_WAIT, 0 );
   SurfPtr = ( BYTE* )DDSurfDesc.lpSurface;

   SurfPtr[ (X*2) + Y * DDSurfDesc.lPitch ] = 0;
   SurfPtr[ ((X*2) + Y * DDSurfDesc.lPitch) +1] = 128+64+32+16;

   TempSurf->Unlock( NULL );
}

void DrawLine(LPDIRECTDRAWSURFACE4 &lpdds, int x0, int y0, int x1, int y1, int r,int g, int bb)
{	
	int dx = x1 - x0;
    int dy = y1 - y0;


	if (abs(dx) > abs(dy)) {          // slope < 1
            float m = (float) dy / (float) dx;      // compute slope
            float b = y0 - m*x0;
            dx = (dx < 0) ? -1 : 1;
            while (x0 != x1) {
                x0 += dx;
				PutPixel( lpdds, x0, (int)(m*x0 + b), r, g, bb);
                //raster.setPixel(pix, x0, Math.round(m*x0 + b));
            }
        } else
        if (dy != 0) {                              // slope >= 1
            float m = (float) dx / (float) dy;      // compute slope
            float b = x0 - m*y0;
            dy = (dy < 0) ? -1 : 1;
            while (y0 != y1) {
                y0 += dy;
				PutPixel( lpdds, (int)(m*y0 + b), y0, r, g, bb);
                //raster.setPixel(pix, Math.round(m*y0 + b), y0);
            }
        }


	//PutPixel( LPDIRECTDRAWSURFACE TempSurf, int X, int Y, int Red, int Green, int Blue )
}      