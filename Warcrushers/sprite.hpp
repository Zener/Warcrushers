#ifndef _SPRITE_INC
#define _SPRITE_INC

#include <ddraw.h>

#define MAXSPRITES 200


class sprite
        {
        int sx,sy;		
		char *name;
		bool init;
		public:
			HBITMAP             hbm;
			int width, height;
			IDirectDrawSurface4 *pdds;
			sprite();
			sprite(char *,IDirectDraw4 *);
			void load(char *,int,IDirectDraw4 *);
			void blitfast(int,int,int,int,int,int,DWORD,LPDIRECTDRAWSURFACE4 &);
            void blit(int,int,int,int,int,int,DWORD,LPDIRECTDRAWSURFACE4 &, int);
			void blittrans(int,int,int,int,int,int,DWORD,LPDIRECTDRAWSURFACE4 &, int);
			HRESULT setcolorkey(COLORREF);
			HRESULT copy(IDirectDrawSurface4 *,HBITMAP,int,int,int,int);
			DWORD colormatch(IDirectDrawSurface4 *,COLORREF);
			HRESULT reload();//char *);
			HRESULT restore();
        };



class SpriteManager
{
	public:	
		static void Init();	
		static void AddSprite(sprite *s);
		static void RestoreAll();	
};


#endif
                    