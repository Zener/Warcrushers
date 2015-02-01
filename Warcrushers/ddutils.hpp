#ifndef _DDUTILS_INC
#define _DDUTILS_INC


#include <windows.h>
#include <ddraw.h>
#include "sprite.hpp"


void dddebugmsg(HRESULT);
void ddClearScreen(LPDIRECTDRAWSURFACE4 &,int,int,int);
void PrintText(int,int,LPDIRECTDRAWSURFACE4,char *,COLORREF);
void Fondo(LPDIRECTDRAWSURFACE4 &source,LPDIRECTDRAWSURFACE4 &lpdds);
void FillRectangle(LPDIRECTDRAWSURFACE4 &lpdds,int x, int y, int w, int h, int r,int g, int b);
void PrintNumGFX(sprite font, int x, int y, int n, LPDIRECTDRAWSURFACE4 lpdds);
void PrintGFX(sprite font, int x, int y, char *s, LPDIRECTDRAWSURFACE4 lpdds);
void PrintRGFX(sprite font, int x, int y, char *s, LPDIRECTDRAWSURFACE4 lpdds);
void DrawLine(LPDIRECTDRAWSURFACE4 &lpdds, int x0, int y0, int x1, int y1, int r,int g, int b);
int getGFXStringWidth(char *ss, int start, int length);
void InitFonts();
#endif

