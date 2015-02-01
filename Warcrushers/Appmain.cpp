// Framework para trabajar con DirectDraw
// version corregida.

// aqui el nombre del programa en los dos lados
#define NAME "Warcrushers"
#define TITLE "Warcrushers"

#define AUTHOR "Carlos Peris"

#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>

#include <mmsystem.h>
//#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dinput.h>


// clearscreen, rutina de debug
#include "res\resource.h"
#include "ddutils.hpp"
#include "sprite.hpp"					// wrapper del sprite
#include "music.h"						// musica
#include "unit.h"	
#include "unitmanager.cpp"
#include "xml/xmlManager.h"
#include "direct.h"

#define CRITICLIMIT 5
#define HITTIME 30

//#include "ht_ddutil.h"
void InitMapEasy();
void InitMapMedium();
void InitMapHard();
void DrawFire(int a, float b);
void InitMap(int st);
void InitMainMenu();
void InitMenuDif();
void InitPauseMenu();
void PauseMenu();
void PauseMenuUpdate();
void ScenarioMenuUpdate();
void Credits();
void CampaignMenuUpdate();
void MainMenuUpdate();
void InitEnding();
void Ending();
int soundVolume;
int musicVolume;
bool hintsActive;
int currentUnits;
int gameMode;
int db = 1;

//WINDOW.H
void WindowInit(bool _select, int _inix, int _iniy, int _width, int _height, int _r, int _g, int _b);
void WindowDraw();
void WindowAddLine(const char *in);
int WindowUpdate();
void WindowClose();
int wOp;
bool wActive = false;
//ENDIF

char *ingameMsg = NULL;
int ingameMsgTimer = 0;
int ingameMarkTimer = 0;
int markx, marky;


typedef struct 
{
   int mission;
   int x,y;
   int markx,marky;
   bool reenter;
   char *msg;
   bool triggered;
   int time;
}trig;

trig *triggers;

char *author = "Carlos Peris";
int kk=0;

LPDIRECTDRAW             lpDD;           // objeto DirectDraw 
LPDIRECTDRAW4            lpDD4;           // objeto DirectDraw 
LPDIRECTDRAWSURFACE4     lpDDSPrimary;   // buffer primario DirectDraw
LPDIRECTDRAWSURFACE4     lpDDSBack;      // buffer secundario DirectDraw

BOOL                    bActive;        // aplicacion activa?
HWND					hwnd;

///////////////////////////////////////////////////
	LPDIRECTINPUT8			lpdi;			// Direct Input 
	LPDIRECTINPUTDEVICE8	g_pMouse;		// Mouse
	HANDLE					g_hevtMouse;
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///////////////////////////////////////////////////
// estos defines son para el modo grafico
  #define	SCREENX		800
  #define	SCREENY		600
  #define	COLOR		16
///////////////////////////////////////////////////
// defines generales de la aplicacion
///////////////////////////////////////////////////
  
  #define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 
  #define MAX(a, b)  (((a) < (b)) ? (b) : (a)) 
///////////////////////////////////////////////////
  #define VIDEO 0
  #define SISTEMA 1
///////////////////////////////////////////////////
///////////////////////////////////////////////////
  #define	MOVX		2
  #define	DEFACC		1
  #define	INCACC		0.05
  //#define	SCROLLVEL	4
///////////////////////////////////////////////////
  #define	ALTO		5
  #define	LARGO		10
///////////////////////////////////////////////////
  #define	INVALID		-1
  #define	EMPTY		0
  #define	CAMP		1
  #define	FORTRESS	2
  #define	CASTLE		3 
  #define	VILLAGE		4
  #define	CITADEL		5
////////////////////////////////////////////////////
  #define   NONE		0
  #define	HUMAN		1
  #define	COMP		2
////////////////////////////////////////////////////


  #define CITADELRATIO 4
  #define VILLAGERATIO 2
  #define CAMPRATIO 1
  #define FORTRESSRATIO 3
  #define CASTLERATIO 5

  #define BATTLETIME 5
  #define TMOUSE 5
////////////////////////COMP///////////////////
	int gold[2];
	//int cgold = 1500;
int optarmy = 10;
int hlocs = 0;
int clocs = 0;
int harmy = 0;

  #define ECO		0
  #define KILL		1
  #define BUILD		2
/////////////////////////////////
  #define STARTUP	-1
  #define MENU1		0
  #define INGAME	1
  #define VICTORY	2
  #define DEFEAT	3
  #define MENU2		4
  #define BRIEFING	5
  #define CREDITS	6
  #define PAUSE	    7
  #define OBJECTIVES	    8
  #define SCENARIO			9
  #define CONFIRMQUIT	    10
  #define CONFIRMEXIT	    11
  #define ENDING			12
#define CAMPAIGN			0
/////////////////////////////////
  #define   ALPHA		140
  char		s[50];  

  int		fps = 0;
  DWORD		time1, time2, time1t, time2t;  

  int mousetime = 0;

long gametime;
long intervaltime;
#define  DAYLONG 10000
#define  DAYTIME 0
#define  NIGHTTIME 1
int hora = DAYTIME;
#define TIMEOUT  250*5


int objectiveCom, objectivePar1, objectivePar2, objectiveEndsMission;

#define OBJ_KILL	0
#define OBJ_BUILD	1
#define OBJ_RECRUIT 2
#define OBJ_CONQUER 3
#define OBJ_DONTLOSE 4

typedef struct 
{
   int hecho;
   int ocupado;
   int mission;
   int x,y;
   int reintentos;
}ejercito;

ejercito army[10];

#define FRAMEOFFSET  4


int turno = 0;

int minarmy;



  int modok;

  int gameStatus = STARTUP;
/////////////////graficos//////////////////////////  
  sprite	day, sun , moon;
  sprite	marker;
  sprite	briefingBackground;
  sprite	marco1, marco2, marco3;
  sprite	panel0, panel1, panel2, panel3, panel4;
  sprite	suelo;
  sprite	cons[10];
  sprite	minis[2];
  sprite	soldado11;
  sprite	negro;
  sprite	soldado21;
  sprite    font, mfont, comandos;
  sprite	target0, target1;
  sprite	bandera0, bandera1;
  sprite	banderag0, banderag1;
  sprite	ex0, ex1;
  sprite	human, comp, none;
  sprite	estructuras;
  sprite	celdas;
  sprite	battle;
  sprite	arbol1;
  sprite	escudo;
  unit		units[MAXUNITS];
  #define   DANYOFLECHAS 6
  #define   MAXFLECHAS 20
    
/////////////////////MENU////////////////////
  sprite	casco, bg, wc, fuego, victory, defeat, dif;
/////////////////variables del juego///////////////
  //int		gold = 5000;
  int		tick = 0;
	#define HARD 1
  	#define MEDIUM 2
  	#define EASY 3

  int		dificultad = MEDIUM;
  
  #define AWIDTH 25
  #define AHEIGHT 8

  typedef struct 
  {
	  bool onceBuilt;
     int construccion;
	 int unidentro;
	 int unifuera;
     int unienemigo;
	 int people;
	 int raceowner;
     int racestriker;
	 int integrity;
     int maxintegrity;
	 int units[AHEIGHT][AWIDTH]; 
	 int visible;
	 int explored;
	 int evervisible;
	 int t_visible;
     int g_construccion;
	 int g_visible;
	 unit flechas[MAXFLECHAS];
  }celula;


  //INTEGRITIES
  #define INT_CAMP		2000
  #define INT_VILLAGE	3000
  #define INT_FORTRESS	4000
  #define INT_CITADEL	6000
  #define INT_CASTLE	8000

  //EXPLORING/VISIBILITY
  #define GNOTEXPLORED	0
  #define GEXPLORED		1
  #define GNOTVISIBLE	0
  #define GVISIBLE		1
  #define TVISIBLE		100

  //GOLD
  #define CAMPGOLD		350
  #define FORTRESSGOLD	500
  #define CASTLEGOLD	1000
  #define RECRUITGOLD	5
  #define REPAIRGOLD	3

  int ratio[10];
  celula mapa[ALTO][LARGO];
  UINT yactual = 0;
  UINT xactual = 0;
  int oriy = -1;
  int orix = -1;


  typedef struct 
  {
    float	x;
	float	y;
	float	accx;
	float	accy;
	int		lastx, lasty;	
	sprite	punt;
	sprite	puntOverV;	
	sprite	puntOverG;
	sprite	puntOverB;	
  }uncursor;

  uncursor cur;



//NEW DEVELOP
bool overBuilding;
bool overGround;
bool overVillage;
bool leftMouseButton;
bool lastLeftMouseButton;
bool leftMouseReleased;
bool leftMousePressed;
bool rightMouseButton;
void SelectUnits(int i, int j);
void Repair(int i, int j, int race);
void Recruit(int i, int j, int race);
void Explore(int ii, int jj);

int currentStage;
int AI_agressiveness = 5;
int difficulty[] = {EASY, EASY, MEDIUM, MEDIUM, HARD, HARD};

///////////////////////////////////////////////////
  #define	MAXINSIDE_CAMP			50
  #define	MAXINSIDE_FORTRESS		100
  #define	MAXINSIDE_CASTLE		200
  #define	MAXINSIDE_VILLAGE		100
  #define	MAXINSIDE_CITADEL		300

  #define   MAXVILLAGERS			100

  int MAXINSIDE[] = {0, MAXINSIDE_CAMP, MAXINSIDE_FORTRESS, MAXINSIDE_CASTLE, MAXINSIDE_VILLAGE, MAXINSIDE_CITADEL};
///////////////////////////////////////////////////

/*
#define OBJ_KILL	0
#define OBJ_BUILD	1
#define OBJ_RECRUIT 2
#define OBJ_CONQUER 3
#define OBJ_DONTLOSE 4
*/


bool CheckVictory()
{
	//return true;
	bool enemyDefeated = false;
	int bCount = 0;
	int uCount = 0;

	if (clocs == 0) enemyDefeated = true;

	switch(objectiveCom)
	{
		case OBJ_KILL:
			return enemyDefeated;
			break;

		case OBJ_BUILD:
			if (!objectiveEndsMission && !enemyDefeated) return false;
			
			for(int ii = 0;ii < ALTO;ii++)
				for(int jj = 0;jj < LARGO;jj++)		
				{
					if (mapa[ii][jj].raceowner == HUMAN &&
						mapa[ii][jj].construccion == objectivePar2) bCount++;
				}

			if (bCount >= objectivePar1) return true;
			break;

		case OBJ_RECRUIT:
			for(int i = 0; i < MAXUNITS; i++)
				if (units[i].active)
				{
					if (units[i].bando == HUMAN) uCount++;
				}
			currentUnits = uCount;
			if (currentUnits >= objectivePar1) currentUnits = objectivePar1;

			if (!objectiveEndsMission && !enemyDefeated) return false;
			if (uCount >= objectivePar1) return true;
			break;

		case OBJ_CONQUER:
			if (!objectiveEndsMission && !enemyDefeated) return false;
			if (mapa[objectivePar1][objectivePar2].raceowner == HUMAN) return true;
			break;

		case OBJ_DONTLOSE:
			return enemyDefeated;
			break;
	}
	return false;
}


bool CheckDefeat()
{
	if 	(hlocs == 0) return true;

	switch(objectiveCom)
	{
		case OBJ_DONTLOSE:
			if (mapa[objectivePar1][objectivePar2].raceowner != HUMAN) return true;
			break;
	}

	return false;
}




////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//									UNIT MANAGEMENT								  //
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
  int ColocaUnit(int locy, int locx, int bando, int *mx, int*my);


////////////////////////////////////////////////////////////////////////////////////
void IniUnits()
{
	for(int ii = 0;ii < ALTO;ii++)
       for(int jj = 0;jj < LARGO;jj++)		
         for (int i = 0; i < AHEIGHT; i++)
            for (int j = 0; j < AWIDTH; j++)			
				mapa[ii][jj].units[i][j] = INVALID;			
	for(int i = 0; i < MAXUNITS; i++) units[i].active = false;
}

////////////////////////////////////////////////////////////////////////////////////

bool NewUnit(int bando, int locx, int locy, int location, int energy)
{
	int i = 0;
	bool trobat = false;

	while(!trobat && i < MAXUNITS)
	{
		if (!units[i].active) trobat = true;
		else i++;
	}
	if (i == MAXUNITS) return false;
	units[i].active = true;
	units[i].bando = bando;
    units[i].locx = locx;
    units[i].locy = locy;
    units[i].destx = locx;
    units[i].desty = locy;
	units[i].location = location;
	units[i].xp = 0;
	if (location == OUTSIDE)
	{
		int mx, my;	
        if (ColocaUnit(locy, locx, bando, &mx, &my) != INVALID)
		{
			units[i].x = mx;
			units[i].y = my;
			mapa[locy][locx].units[my][mx] = i;
		}
	}
    units[i].energy = energy;	
	units[i].maxenergy = 100;	
	units[i].ataque = 12;	
    units[i].frame = 0;
	if (bando == HUMAN) 
	{
		units[i].armadura = 2;
		units[i].velocidad = 6;
		units[i].critico = 6;	
	}
	else
	{
		units[i].armadura = 4;	
		units[i].velocidad = 5;
		units[i].critico = 6;	
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////////

void MeteUnits(int _y, int _x, int _bando)
{
	int i = 0;
	int j = 0;
	int d = 0;
	bool trobat = false;
	int soldier;

			
	if (mapa[_y][_x].raceowner != _bando || mapa[_y][_x].construccion <= EMPTY || mapa[_y][_x].unifuera == 0 || mapa[_y][_x].unidentro >= MAXINSIDE[mapa[_y][_x].construccion])
		return;

	

	for (i=0;i<AHEIGHT/2;i++)
	{
       for (int j = AWIDTH; j >= 0; j--)			
		{
		   d = j/2;
		   if (j%2 == 1) d = -d;
            soldier = mapa[_y][_x].units[i][12+d];
			if (soldier != INVALID)
			{
				if (units[soldier].active && 
				units[soldier].bando == _bando &&
				units[soldier].locx == _x &&
				units[soldier].locy == _y &&
				units[soldier].location == OUTSIDE) 
				trobat = true;
			}		   
			if (trobat) break;
	   }
	   if (trobat) break;
	}
    if (!trobat) return;

	units[soldier].location = INSIDE; 
	mapa[_y][_x].unidentro++;
 	units[soldier].destx = _x;   
    units[soldier].desty = _y;   
	units[soldier].frame = 0;
    mapa[_y][_x].unifuera--;					  
    mapa[_y][_x].units[i][12+d] = INVALID;	
}

////////////////////////////////////////////////////////////////////////////////////

int ColocaUnit(int locy, int locx, int bando, int *mx, int*my)
{
   if (mapa[locy][locx].raceowner == bando ||	
	   mapa[locy][locx].raceowner == NONE)
   {
		int min = 5;
		int mincol;

		for (int j = 0; j <= AWIDTH; j++)			
		{
		   int d = j/2;
		   if (j%2 == 1) d = -d;
		   int suma = 0;
		   for (int k = 0;k < AHEIGHT/2;k++)
		   {
			   if (mapa[locy][locx].units[k][12+d] != INVALID) suma++;
		   }
		   if (suma < min) {min = suma;mincol = 12+d;}

   		}

		if (min == 5) return 0;
		*mx = mincol;
		*my = 0;
		if (mapa[locy][locx].units[0][mincol] == INVALID) return 1;
		return 0;
   }
   else
   {
		int min = 5;
		int mincol;
		for (int j = 0; j <= AWIDTH; j++)			
		{
		   int d = j/2;
		   if (j%2 == 1) d = -d;		   
		   int suma = 0;
		   for (int k = AHEIGHT/2;k < AHEIGHT;k++)
		   {
			   if (mapa[locy][locx].units[k][12+d] != INVALID) suma++;
		   }
		   if (suma < min) {min = suma;mincol = 12+d;}
   		}
		if (min == 5) return 0;
		*mx = mincol;
		*my = AHEIGHT-1;
		if (mapa[locy][locx].units[AHEIGHT-1][mincol] == INVALID) return 1;
		return 0;
   }
   return 0;
}

////////////////////////////////////////////////////////////////////////////////////

int BuscaUnitDentro(int _y, int _x, int _bando)
{

	int i = 0;
	bool trobat = false;

	while(!trobat && i < MAXUNITS)
	{
		if (units[i].active && 
			units[i].bando == _bando &&
			units[i].locx == _x &&
			units[i].locy == _y &&
            units[i].location == INSIDE) 
			trobat = true;
		else i++;
	}
	if (i == MAXUNITS) return -1;
	return i;
}

////////////////////////////////////////////////////////////////////////////////////

void SacaUnits(int _y, int _x, int _bando)
{
	int i = 0;
	bool trobat = false;

	if (mapa[_y][_x].construccion <= EMPTY || mapa[_y][_x].unidentro <= 0) return;
			

	while(!trobat && i < MAXUNITS)
	{
		if (units[i].active && 
			units[i].bando == _bando &&
			units[i].locx == _x &&
			units[i].locy == _y &&
            units[i].location == INSIDE) 
			trobat = true;
		else i++;
	}
	if (i == MAXUNITS) return;	
/*
	int min = 5;
    int mincol;
    for (int j = 0; j < AWIDTH; j++)			
	{
	   int suma = 0;
       for (int k = 0;k < AHEIGHT/2;k++)
	   {
		   if (mapa[_x][_y].units[k][j] != INVALID) suma++;
	   }
	   if (suma < min) {min = suma;mincol = j;}
   	}
	if (min == 5) return;
	*/
	int nx, ny;
    if (ColocaUnit(_y, _x, units[i].bando, &nx, &ny))
	{
 	    mapa[_y][_x].unidentro--;
		mapa[_y][_x].unifuera++;
		units[i].location = OUTSIDE; 
		mapa[_y][_x].units[0][nx] = i;
		units[i].x = nx;
		units[i].y = ny;
	}
	/*
	int j = 0;
	trobat = false;
    while(!trobat && j < AWIDTH)
	{
		if (mapa[xactual][yactual].units[0][j] == INVALID) trobat = true;
		else j++;
	}
	if (j == AWIDTH) return;	
    mapa[xactual][yactual].units[0][j] = i;
    units[i].x = j*25;
    units[i].y = 140;
*/
}

////////////////////////////////////////////////////////////////////////////////////

int EnemigoDelante(int ii,int jj,int i,int j)
{
   int y;
   if (i <= (AHEIGHT/2)-1)
	   y = AHEIGHT/2;
   else
	   y = (AHEIGHT/2)-1;
   int soldier = mapa[ii][jj].units[y][j];
   if (soldier != INVALID) return y;
   return 0; //FALSO
}					

////////////////////////////////////////////////////////////////////////////////////

int ExitsPath(int ox, int oy, int dx, int dy)
{
	return -1;
}


class AInode
{
	public:
	int f, g;
	float distToGoal;
	int x;
	int y;

	
	AInode(int _x, int _y, int _destx, int _desty)
	{
		x = _x;
		y = _y;
		distToGoal = (int)sqrt((float)(abs(x - _destx)*abs(x - _destx) + abs(y - _desty)*abs(y - _desty)));
	}

	
};


float AIdistToGoal(int x, int y, int destx, int desty)
{
	return sqrt((float)((abs(x - destx)*abs(x - destx)) + (abs(y - desty)*abs(y - desty))));
}



void AIMoveUnit(unit soldier, int *sx, int *sy)
{
	int asx = 0, asy = 0;
	// Podemos llegar
	
	if (soldier.locx < soldier.destx) *sx = 1;
	if (soldier.locx > soldier.destx) *sx = -1;
	if (soldier.locy < soldier.desty) *sy = 1;
	if (soldier.locy > soldier.desty) *sy = -1;		

	// Elegir entre X y Y
	if (AIdistToGoal(soldier.locx + *sx, soldier.locy, soldier.destx, soldier.desty)
		> AIdistToGoal(soldier.locx, soldier.locy + *sy, soldier.destx, soldier.desty)
		)
		//if (*sy != 0) 
		{asx = *sx;*sx = 0;}
	else
		//if (*sx != 0) 
		{asy = *sy;*sy = 0;}

	// Colision check
		
	int tx = soldier.locx + *sx;
	int ty = soldier.locy + *sy;
	int seg = 0;
	while (mapa[ty][tx].construccion < 0)
	{
		if (*sx != 0)
		{
			*sx = 0; *sy = asy;asy = 0;
		}
		else
		{
			*sy = 0; *sx = asx;asx = 0;
		}
		tx = soldier.locx + *sx;
	    ty = soldier.locy + *sy;
		if (seg++ > 30) exit(1);
	}
	
	
}

int tactunits = 0;

void FracMovement()
{
	for(int ii = 0;ii < ALTO;ii++)
      for(int jj = 0;jj < LARGO;jj++)
	  {
		 //HACIA DELANTE DEFEMDIENDO
         for (int i = (AHEIGHT/2)-1; i > 0;i--)
		 {
            for (int j = 0; j < AWIDTH; j++)			
			{
   		       if (mapa[ii][jj].units[i][j] == INVALID)
			   {
			      int soldier = mapa[ii][jj].units[i-1][j];
			   	  if (soldier != INVALID)
				  {
					  units[soldier].frameFractionY = tactunits/25.0f;
					 
					  units[soldier].frame = (tactunits%18 < 9)?3:0;
					  if ((units[soldier].frameFractionY) <= 0.1f) units[soldier].frame = 0;
				  }
				  
				  //else units[soldier].frameFractionY = 0.0f;
			   }
			   else 
			   {
				   int soldier = mapa[ii][jj].units[i][j];
				   if (units[soldier].frameFractionY == 0 && units[soldier].frame == 3) units[soldier].frame = 0;
			   }
			   
			}
		 }
		 //HACIA DELANTE ATACANDO
		 for (int i = (AHEIGHT/2); i < AHEIGHT-1;i++)
		 {
            for (int j = 0; j < AWIDTH; j++)			
			{
   		       if (mapa[ii][jj].units[i][j] == INVALID)
			   {
			      int soldier = mapa[ii][jj].units[i+1][j];
			   	  if (soldier != INVALID)
				  {
					  units[soldier].frameFractionY = -tactunits/25.0f;
					  units[soldier].frame = (tactunits%18 < 9)?3:0;
					  //if ((units[soldier].frameFractionY) <= 0.1f) units[soldier].frame = 0;
				  }
				  
				  //else units[soldier].frameFractionY = 0.0f;
			   }
			   else 
			   {
				   int soldier = mapa[ii][jj].units[i][j];
				   if (units[soldier].frameFractionY == 0 && units[soldier].frame == 3) units[soldier].frame = 0;
			   }
			}
		 }
	  }
}





void ActualitzaUnits()
{
   tactunits += tick;
   if (tactunits < 25)
   {
		FracMovement();
	   
	   return;
   }
   tactunits=0;
   //boolean first = true;
   
//else if (first)

      for(int ii = 0;ii < ALTO;ii++)
      for(int jj = 0;jj < LARGO;jj++)		    
      {
	     for(int i = (AHEIGHT/2)-1;i < (AHEIGHT/2)+1;i++)
			 for (int j = 0; j < AWIDTH; j++)			
			 {	
				 if (mapa[ii][jj].units[i][j] != INVALID)
				 {
					int soldier = mapa[ii][jj].units[i][j];

					units[soldier].hit = false;

					//MOVIMIENTO A OTRA CELDA
					if (units[soldier].desty != ii || units[soldier].destx != jj)
					{
					  int sx=0, sy=0;
					  AIMoveUnit(units[soldier], &sx, &sy);
					  
					  int destbando = mapa[ii+sy][jj+sx].raceowner;
										  
					  int mx,my;
					  if (ColocaUnit(ii+sy, jj+sx, units[soldier].bando, &mx,& my))
					  {
						  units[soldier].frameFractionY = 0.0f; //ZNR PRUEBA
						  units[soldier].x = mx;
						  units[soldier].y = my;
						  mapa[ii][jj].units[i][j] = INVALID;
						  mapa[ii+sy][jj+sx].units[my][mx] = soldier;
						  units[soldier].locy = ii+sy;
						  units[soldier].locx = jj+sx;
						  if (mapa[ii][jj].raceowner == units[soldier].bando)	
							 mapa[ii][jj].unifuera--;								 						  
						  else
							 mapa[ii][jj].unienemigo--;   						  				
						  if (units[soldier].bando == mapa[ii+sy][jj+sx].raceowner)
						  {
							  mapa[ii+sy][jj+sx].unifuera++;
						  }
						  else if (mapa[ii+sy][jj+sx].raceowner == NONE)
						  {
							  mapa[ii+sy][jj+sx].unifuera++;
							  mapa[ii+sy][jj+sx].raceowner = units[soldier].bando;
						  }
						  else
						  {
							  mapa[ii+sy][jj+sx].unienemigo++;
							  mapa[ii+sy][jj+sx].racestriker = units[soldier].bando;
						  }
					  }
					}					
				 }			  	 
			 }
		}
   for(int ii = 0;ii < ALTO;ii++)
      for(int jj = 0;jj < LARGO;jj++)
	  {
		 //HACIA DELANTE DEFENDIENDO
         for (int i = (AHEIGHT/2)-1; i > 0;i--)
		 {
            for (int j = 0; j < AWIDTH; j++)			
			{
   		       if (mapa[ii][jj].units[i][j] == INVALID)
			   {
			      int soldier = mapa[ii][jj].units[i-1][j];

					units[soldier].hit = false;

			   	  if (soldier != INVALID)
				  {
					 mapa[ii][jj].units[i][j] = soldier;
					 mapa[ii][jj].units[i-1][j] = INVALID;
					 units[soldier].y ++;
					 units[soldier].frameFractionY = 0.0f;
				  }
			   }
			   
			}
		 }
		 //HACIA DELANTE ATACANDO
		 for (int i = (AHEIGHT/2); i < AHEIGHT-1;i++)
		 {
            for (int j = 0; j < AWIDTH; j++)			
			{
   		       if (mapa[ii][jj].units[i][j] == INVALID)
			   {
			      int soldier = mapa[ii][jj].units[i+1][j];
			   	  if (soldier != INVALID)
				  {
					 mapa[ii][jj].units[i][j] = soldier;
					 mapa[ii][jj].units[i+1][j] = INVALID;
					 units[soldier].y--;
					 units[soldier].frameFractionY = 0.0f;
				  }
			   }
			   
			}
		 }
	  }
}

////////////////////////////////////////////////////////////////////////////////////

void MueveUnits(int _oy, int _ox, int _dy, int _dx, int race)
{
	for (int i = 0; i < AHEIGHT;i++)
       for (int j = 0; j < AWIDTH; j++)	
	   {
		  int soldier = mapa[_oy][_ox].units[i][j];
		  if (soldier != INVALID)		  
			 if (units[soldier].bando == race)
			 {
			    units[soldier].destx = _dx;
			    units[soldier].desty = _dy;		  
			 }
	   }
	if (race == HUMAN)
		oriy = -1;	
}

////////////////////////////////////////////////////////////////////////////////////

void DrawUnits()
{
	
    int i = 0, j = 0, kk=0;
	/*
	for (i=0; i < 10 ;i++)
		if (army[i].ocupado && army[i].y == yactual && army[i].x == xactual)
		{
		   PrintNumGFX(font, 0,0, i, lpDDSBack);    
		   PrintNumGFX(font, 0,15, army[i].mission, lpDDSBack);    
		   PrintNumGFX(font, 0,30, army[i].hecho, lpDDSBack);    
		   PrintNumGFX(font, 0,45, army[i].reintentos, lpDDSBack);    
		}
    for (i=0; i < 10 ;i++)if (army[i].ocupado) kk++;
    PrintNumGFX(font, 400,0, kk, lpDDSBack);    
    */
	/*
	while( i < MAXUNITS)
	{
		if (units[i].active && 
			units[i].bando == mapa[yactual][xactual].raceowner &&
			units[i].locx == xactual &&
			units[i].locy == yactual &&
            units[i].location == INSIDE) 
			j++;
		i++;
	}
	PrintNumGFX(font, 20,0, j, lpDDSBack);    */
	sprite def, att;
	switch(mapa[yactual][xactual].raceowner)
	{
			case HUMAN: 				
				def = soldado11;
				att = soldado21;
				if (mapa[yactual][xactual].unienemigo == 0)	def = soldado11;				
				break;								
			default:	
				def = soldado21;
				att = soldado11;				
				if (mapa[yactual][xactual].unienemigo == 0)	def = soldado21;				
				break;
	}	

   for (i = 0; i < AHEIGHT; i++)
      for (int j = 0; j < AWIDTH; j++)      
	  {
		 int soldier = mapa[yactual][xactual].units[i][j];
		 int soldx = units[soldier].x*25;
		 int soldy = 140+((units[soldier].y+units[soldier].frameFractionY)*28);		 
		 if (soldier != INVALID)
         {			 
			 if (units[soldier].bando == mapa[yactual][xactual].raceowner)
			 {
	  	        def.blit(units[soldier].frame*48,0,(1+units[soldier].frame)*48,def.height,soldx, soldy,DDBLT_KEYSRC,lpDDSBack,0);    
			 }
		     else
				att.blit((units[soldier].frame+FRAMEOFFSET)*48,0,(1+FRAMEOFFSET+units[soldier].frame)*48,att.height,soldx, soldy,DDBLT_KEYSRC,lpDDSBack,0);
			 int recx = soldx + 24-(units[soldier].maxenergy/12);
			 FillRectangle(lpDDSBack,recx, soldy,(100/6)+2 , 3, 200, 190, 50);
			 FillRectangle(lpDDSBack,recx+1, soldy+1,100/6 , 1, 10, 10, 0);
			 FillRectangle(lpDDSBack,recx+1, soldy+1,units[soldier].energy/6 , 1, 0, 225, 0);
			 if (units[soldier].hitTime > 0)
			 {
				 if (tick) units[soldier].hitTime--;
				 //FillRectangle(lpDDSBack,recx+1, soldy+1,units[soldier].energy/6 , 1,225, 0,0);
				 switch(units[soldier].hit)
				 {
				    case 1: sprintf(s, "Grr!", units[soldier].hit);break;
					case 2: sprintf(s, "Dwah!", units[soldier].hit);break;
					case 3: sprintf(s, "Eii!", units[soldier].hit);break;
					default:sprintf(s, "Ggh!", units[soldier].hit);
				 }
				 PrintGFX(mfont, soldx+2, soldy-15, s, lpDDSBack);
			 }
		 }
	  }	   	  

}

////////////////////////////////////////////////////////////////////////////////////

void DestruyeConstruccion(unsigned int i, unsigned int j)
{
	//int t = mapa[i][j].unidentro;
	while (mapa[i][j].unidentro > 0 && mapa[i][j].unifuera < 100)
	{
		mapa[i][j].unidentro--;
		bool trobat = false;
		int tty = 0;								
		while (!trobat && tty < AHEIGHT/2)
		{
			int ttx = 0;
			while (!trobat && ttx < AWIDTH)
			{
				if (mapa[i][j].units[tty][ttx] == INVALID)
				{
					trobat = true;
					int soldier = BuscaUnitDentro(i, j, mapa[i][j].raceowner);
					if (soldier != -1)
					{
						mapa[i][j].units[tty][ttx] = soldier;
						units[soldier].location = OUTSIDE; 
						units[soldier].x = ttx;
						units[soldier].y = tty;
						mapa[i][j].unifuera++;												
					}
				}
				ttx++;
			}
			tty++;
		}
	}
	//ELIMINAR EL RASTRO
	while (mapa[i][j].unidentro > 0)
	{
		int soldier = BuscaUnitDentro(i, j, mapa[i][j].raceowner);
		if (soldier != -1)
			units[soldier].active = false;
		mapa[i][j].unidentro--;
	}

	//for (int tkk = 0 ; tkk < t;tkk++)
	//   SacaUnits(i, j, mapa[i][j].raceowner);					  
	mapa[i][j].integrity = 0;
	mapa[i][j].construccion = NONE;
	if ((i == yactual) && (j == xactual)) Sonido(10,SB,2 );
}

///////////////////////////////////////////////////
// si quereis trabajar con bltfast comentad todo lo de clippers.
// Si hay un clipper por medio un bltfast falla SIEMPRE.
LPDIRECTDRAWCLIPPER		lpDDClipper;	// un clipper para recortar.

// esto nos es muy útil para definir las CLIP-LISTS.
typedef struct 
	{
    RGNDATAHEADER hdr;
    RECT rgndata[4];
    } CLIPLIST, *LPCLIPLIST;

////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
// finiObjects
//		release de los objetos del sistema
////////////////////////////////////////////////////////////////////////
static void finiObjects( void )
{
    if( lpDD != NULL )
    {
        if( lpDDSPrimary != NULL )
        {
			lpDDSPrimary->Release();
            lpDDSPrimary = NULL;
        }
        lpDD->Release();
        lpDD = NULL;
    }
} 

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int Dentro(int x1, int y1, int x2, int y2, int ox, int oy)
{
	int x = (int)cur.x - ox;
	int y = (int)cur.y - oy;
	if ((y >= y1) && (y <= y2))
	{
		if ((x >= x1) && (x <= x2))
			return 1;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////

void EndMouse()
{	
	if (g_pMouse) 
	 {
	 	  g_pMouse->Unacquire();
	
	     g_pMouse->Release();
	     g_pMouse = NULL;
	 }
	
	 if (lpdi) {
	     lpdi->Release();
	     lpdi = NULL;
	 }
}


////////////////////////////////////////////////////////////////////////
// BloquearSuperficie()
////////////////////////////////////////////////////////////////////////
DDSURFACEDESC2 BloquearSuperficie( LPDIRECTDRAWSURFACE4 puntero, LPRECT region)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hRet;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	hRet = puntero->Lock(region, &ddsd,  DDLOCK_WAIT | DDLOCK_WRITEONLY, NULL);
	if(hRet != DD_OK) exit(1);
	return ddsd;
}
DDSURFACEDESC2 BloquearSuperficie2( LPDIRECTDRAWSURFACE4 puntero, LPRECT region)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hRet;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	hRet = puntero->Lock(region, &ddsd,  DDLOCK_WAIT | DDLOCK_READONLY, NULL);
	if(hRet != DD_OK) exit(1);
	return ddsd;
}

////////////////////////////////////////////////////////////////////////
// DesbloquearSuperficie()
////////////////////////////////////////////////////////////////////////
void DesbloquearSuperficie(LPDIRECTDRAWSURFACE4 puntero)
{

	puntero->Unlock(NULL);
}






void InitGfx()
{	
	InitFonts();

	day.load("img/hud/daytime.bmp",VIDEO, lpDD4);
	day.setcolorkey(CLR_INVALID);
	sun.load("img/hud/sun.bmp",VIDEO, lpDD4);
	sun.setcolorkey(CLR_INVALID);
	moon.load("img/hud/moon.bmp",VIDEO, lpDD4);
	moon.setcolorkey(CLR_INVALID);

	marker.load("img/hud/marker.bmp",VIDEO, lpDD4);
	marker.setcolorkey(CLR_INVALID);

	marco1.load("img/hud/marc1.bmp",VIDEO, lpDD4);
	marco2.load("img/hud/marc2.bmp",VIDEO, lpDD4);
	marco3.load("img/hud/marc3.bmp",VIDEO, lpDD4);


	panel0.load("img/hud/panel0.bmp",VIDEO, lpDD4);
	panel1.load("img/hud/panel1.bmp",VIDEO, lpDD4);
	panel3.load("img/hud/panel3.bmp",VIDEO, lpDD4);
	suelo.load("img/game/ground.bmp",SISTEMA, lpDD4);
	
	minis[0].load("img/hud/minis.bmp",VIDEO, lpDD4);
	minis[0].setcolorkey(CLR_INVALID);
	minis[1].load("img/hud/minitt.bmp",VIDEO, lpDD4);
	minis[1].setcolorkey(CLR_INVALID);

	negro.load("img/game/alpha.bmp",VIDEO, lpDD4);
	negro.setcolorkey(CLR_INVALID);

	cons[0].load("img/game/camp.bmp",VIDEO, lpDD4);
    cons[1].load("img/game/fortress.bmp",VIDEO, lpDD4);
    cons[2].load("img/game/castle.bmp",VIDEO, lpDD4);
    cons[3].load("img/game/village.bmp",VIDEO, lpDD4);
	cons[4].load("img/game/city.bmp",VIDEO, lpDD4);
    cons[0].setcolorkey(CLR_INVALID);
	cons[1].setcolorkey(CLR_INVALID);
	cons[2].setcolorkey(CLR_INVALID);
	cons[3].setcolorkey(CLR_INVALID);
	cons[4].setcolorkey(CLR_INVALID);

	soldado11.load("img/game/unit02.bmp",VIDEO, lpDD4);
	soldado11.setcolorkey(CLR_INVALID);
	soldado21.load("img/game/unit01.bmp",VIDEO, lpDD4);
	soldado21.setcolorkey(CLR_INVALID);
	cur.punt.load("img/hud/cursor.bmp", VIDEO, lpDD4);
	cur.puntOverV.load("img/hud/cursor-rec.bmp", VIDEO, lpDD4);
	cur.puntOverV.setcolorkey(CLR_INVALID);
	cur.puntOverB.load("img/hud/cursor-in.bmp", VIDEO, lpDD4);	
	cur.puntOverB.setcolorkey(CLR_INVALID);
	cur.puntOverG.load("img/hud/cursor-out.bmp", VIDEO, lpDD4);	
	cur.puntOverG.setcolorkey(CLR_INVALID);
	cur.x = SCREENX/2;
	cur.y = SCREENY/2;
	cur.lastx = 0;
	cur.lasty = 0;
	cur.accx = 0;
	cur.accy = 0;
	cur.punt.setcolorkey(CLR_INVALID);

	target0.load("img/hud/target0.bmp", VIDEO, lpDD4);
    target0.setcolorkey(CLR_INVALID);
	target1.load("img/hud/target1.bmp", VIDEO, lpDD4);
    target1.setcolorkey(CLR_INVALID);
	bandera0.load("img/hud/flag0.bmp", VIDEO, lpDD4);
    bandera0.setcolorkey(CLR_INVALID);
	bandera1.load("img/hud/flag1.bmp", VIDEO, lpDD4);
    bandera1.setcolorkey(CLR_INVALID);
	banderag0.load("img/hud/bflag0.bmp", VIDEO, lpDD4);
    banderag0.setcolorkey(CLR_INVALID);
	banderag1.load("img/hud/bflag1.bmp", VIDEO, lpDD4);
    banderag1.setcolorkey(CLR_INVALID);
	
	ex0.load("img/hud/ex0.bmp", VIDEO, lpDD4);
    ex0.setcolorkey(CLR_INVALID);
	ex1.load("img/hud/ex1.bmp", VIDEO, lpDD4);
    ex1.setcolorkey(CLR_INVALID);
	font.load("img/hud/font.bmp", VIDEO, lpDD4);
    font.setcolorkey(CLR_INVALID);
	mfont.load("img/hud/nfont.bmp", VIDEO, lpDD4);
    mfont.setcolorkey(CLR_INVALID);
	
	comandos.load("img/hud/commands.bmp", VIDEO, lpDD4);
    comandos.setcolorkey(CLR_INVALID);	
	estructuras.load("img/hud/buildingstext.bmp", VIDEO, lpDD4);
    estructuras.setcolorkey(CLR_INVALID);	
	human.load("img/hud/human.bmp", VIDEO, lpDD4);
	comp.load("img/hud/comp.bmp", VIDEO, lpDD4);
	none.load("img/hud/none.bmp", VIDEO, lpDD4);
	celdas.load("img/hud/buttons.bmp", VIDEO, lpDD4);
	arbol1.load("img/game/tree.bmp",VIDEO, lpDD4);
	arbol1.setcolorkey(CLR_INVALID);	
	escudo.load("img/hud/shield.bmp",VIDEO, lpDD4);
	escudo.setcolorkey(CLR_INVALID);	
	////////////////MENU////////////////////////////
	//dif.load("img/dif.bmp",SISTEMA, lpDD4);
	//dif.setcolorkey(CLR_INVALID);	
	bg.load("img/menu/bg.bmp",VIDEO, lpDD4);
	bg.setcolorkey(CLR_INVALID);
	casco.load("img/menu/helmet.bmp",SISTEMA, lpDD4);
	casco.setcolorkey(CLR_INVALID);
	//startgame.load("img/startgame.bmp",VIDEO, lpDD4);
	//startgame.setcolorkey(CLR_INVALID);
	//quit.load("img/quit.bmp",VIDEO, lpDD4);
	//quit.setcolorkey(CLR_INVALID);
	wc.load("img/menu/wc.bmp",VIDEO, lpDD4);
	wc.setcolorkey(CLR_INVALID);
	//pardos.load("img/theheroes.bmp",VIDEO, lpDD4);
	//pardos.setcolorkey(CLR_INVALID);
	fuego.load("img/game/fire.bmp",SISTEMA, lpDD4);
	fuego.setcolorkey(CLR_INVALID);	
	victory.load("img/game/victory.bmp",SISTEMA, lpDD4);
	victory.setcolorkey(CLR_INVALID);
	defeat.load("img/game/defeat.bmp",SISTEMA, lpDD4);
	defeat.setcolorkey(CLR_INVALID);	
	battle.load("img/hud/battle.bmp",VIDEO, lpDD4);
	battle.setcolorkey(CLR_INVALID);
}


////////////////////////////////////////////////////////////////////////


BOOL RestoreSurfaces( void ) 
{ 
    
    HRESULT		ddrval; 
     
	ddrval = lpDDSPrimary->Restore();
	ddrval = lpDDSBack->Restore();

	SpriteManager::RestoreAll();
/*	panel0.pdds->Restore();
	panel1.pdds->Restore();
	panel3.pdds->Restore();
	suelo.pdds->Restore();
	minis[0].pdds->Restore();
	minis[1].pdds->Restore();
	cons[0].pdds->Restore();
    cons[1].pdds->Restore();
    cons[2].pdds->Restore();
    cons[3].pdds->Restore();
	cons[4].pdds->Restore();
	soldado11.pdds->Restore();
	soldado21.pdds->Restore();
	cur.punt.pdds->Restore();
	target0.pdds->Restore();
    target1.pdds->Restore();
    bandera0.pdds->Restore();
    bandera1.pdds->Restore();
    banderag0.pdds->Restore();
    banderag1.pdds->Restore();
	ex0.pdds->Restore();
    ex1.pdds->Restore();
    font.pdds->Restore();
	mfont.pdds->Restore();
    comandos.pdds->Restore();
    estructuras.pdds->Restore();
    human.pdds->Restore();
	comp.pdds->Restore();
	none.pdds->Restore();
	celdas.pdds->Restore();
	arbol1.pdds->Restore();
	escudo.pdds->Restore();
	////////////////MENU////////////////////////////
	dif.pdds->Restore();
	bg.pdds->Restore();
	casco.pdds->Restore();
	startgame.pdds->Restore();
	quit.pdds->Restore();
	wc.pdds->Restore();
	pardos.pdds->Restore();
	fuego.pdds->Restore();
	victory.pdds->Restore();
	defeat.pdds->Restore();
	battle.pdds->Restore();
///////////////////////////////////////////////////

	panel0.reload("img/panel0.bmp");
	panel1.reload("img/panel1.bmp");
	panel3.reload("img/panel3.bmp");
	suelo.reload("img/ground00.bmp");
	minis[0].reload("img/minis.bmp");
	minis[1].reload("img/minitt.bmp");
	cons[0].reload("img/camp.bmp");
    cons[1].reload("img/fortress.bmp");
    cons[2].reload("img/castle.bmp");
    cons[3].reload("img/village.bmp");    
	cons[4].reload("img/village.bmp");    
	soldado11.reload("img/unit02.bmp");
	soldado21.reload("img/unit01.bmp");
	cur.punt.reload("img/punt.bmp");	
	target0.reload("img/target0.bmp");
    target1.reload("img/target1.bmp");
    bandera0.reload("img/bandera0.bmp");
    bandera1.reload("img/bandera1.bmp");
    banderag0.reload("img/banderag0.bmp");
    banderag1.reload("img/banderag1.bmp");    
	ex0.reload("img/ex0.bmp");
    ex1.reload("img/ex1.bmp");
    font.reload("img/font.bmp");
	mfont.reload("img/nfont.bmp");
    comandos.reload("img/comandos.bmp");
    estructuras.reload("img/estructuras.bmp");
    human.reload("img/human.bmp");
	comp.reload("img/comp.bmp");
	none.reload("img/none.bmp");
	celdas.reload("img/celdas.bmp");
	arbol1.reload("img/arbol1.bmp");
	escudo.reload("img/escudo.bmp");
	////////////////MENU////////////////////////////
	dif.reload("img/dif.bmp");
	bg.reload("img/bg.bmp");
	casco.reload("img/casco.bmp");
	startgame.reload("img/startgame.bmp");
	quit.reload("img/quit.bmp");
	wc.reload("img/wc.bmp");
	pardos.reload("img/theheroes.bmp");
	fuego.reload("img/fuego.bmp");
	victory.reload("img/victory.bmp");
	defeat.reload("img/defeat.bmp");
	battle.reload("img/battle.bmp");
///////////////////////////////////////////////////
*/
	return TRUE; 
}


void LimpiarTeclado()
{
	for (int i = 40;i < 6*16;i++) GetAsyncKeyState(i);
}


////////////////////////////////////////////////////////////////////////
/*
void ArmyMoves()
{    
	int race = HUMAN;
	int t = 0;
	if (mapa[oriy][orix].raceowner == race)
	{
	   t = mapa[oriy][orix].unifuera;
       mapa[oriy][orix].unifuera -= t;   
	}
	else
	{
	   t = mapa[oriy][orix].unienemigo;
       mapa[oriy][orix].unienemigo -= t;   
	}
	if (mapa[yactual][xactual].raceowner == race)
		mapa[yactual][xactual].unifuera += t;
    if ((mapa[yactual][xactual].raceowner != race) && (mapa[yactual][xactual].raceowner != NONE))
	{
		mapa[yactual][xactual].unienemigo += t;
		mapa[yactual][xactual].racestriker = race;
	}
    if (mapa[yactual][xactual].raceowner == NONE)
	{
		mapa[yactual][xactual].unifuera = t;
        mapa[yactual][xactual].raceowner = race;
	}
	oriy = -1;

}*/
////////////////////////////////////////////////////////////////////////

void Construir(int race)
{
	if (mapa[yactual][xactual].raceowner == race)
    switch(mapa[yactual][xactual].construccion)
	{
		case NONE:
			if (gold[race-1] >= CAMPGOLD)
			{
				mapa[yactual][xactual].construccion ++;
				mapa[yactual][xactual].integrity = INT_CAMP;
				mapa[yactual][xactual].maxintegrity = INT_CAMP;
				gold[race-1] -= CAMPGOLD;		
				mapa[yactual][xactual].onceBuilt = true;
			}
			break;
		case CAMP:
			if (gold[race-1] >= FORTRESSGOLD)
			{
				mapa[yactual][xactual].construccion ++;
			    mapa[yactual][xactual].integrity = (int)(((float)mapa[yactual][xactual].integrity/(float)mapa[yactual][xactual].maxintegrity)*INT_FORTRESS);
				mapa[yactual][xactual].maxintegrity = INT_FORTRESS;
				gold[race-1] -= FORTRESSGOLD;				
				mapa[yactual][xactual].onceBuilt = true;
			}
			break;
		case FORTRESS:
			if (gold[race-1] >= CASTLEGOLD)
			{
				mapa[yactual][xactual].construccion ++;
			    mapa[yactual][xactual].integrity = (int)(((float)mapa[yactual][xactual].integrity/(float)mapa[yactual][xactual].maxintegrity)*INT_CASTLE);;
				mapa[yactual][xactual].maxintegrity = INT_CASTLE;
				gold[race-1] -= CASTLEGOLD;				
				mapa[yactual][xactual].onceBuilt = true;
			}
			break;
	}
	mousetime = TMOUSE*5;

/*
	if ((gold>=500) && (mapa[yactual][xactual].construccion < CASTLE))
	{

	     mapa[yactual][xactual].construccion ++;
		 if (mapa[yactual][xactual].construccion == CAMP)
			 mapa[yactual][xactual].integrity = 100;
		 else
			mapa[yactual][xactual].integrity = (100+mapa[yactual][xactual].integrity)/2;
	     gold -= 500;
	     Sleep(300);
	}
	*/
}

////////////////////////////////////////////////////////////////////////////////////

void DrawHelp(	DIMOUSESTATE dims)
{
   if (Dentro(120,16,166,62,627,400)) // Construir / Upgrade		   
   {
      if (mapa[yactual][xactual].construccion == NONE) comandos.blit(0,45,comandos.width,70, 643, 370, DDBLT_KEYSRC, lpDDSBack,0);	   		  
	  if (mapa[yactual][xactual].construccion == CAMP) comandos.blit(0,71,comandos.width,105, 640, 365, DDBLT_KEYSRC, lpDDSBack,0);	   		  
	  if (mapa[yactual][xactual].construccion == FORTRESS) comandos.blit(0,108,comandos.width,142, 642, 365, DDBLT_KEYSRC, lpDDSBack,0);	   		  
   }		   
   if (Dentro(120,78,166,124,627,400)) // Repair
	  comandos.blit(0,190,comandos.width,210, 645, 370, DDBLT_KEYSRC, lpDDSBack,0);	   		  	  
   if (Dentro(66,78,112,124,627,400)) // Recruit
   	   comandos.blit(0,170,comandos.width,190, 645, 372, DDBLT_KEYSRC, lpDDSBack,0);	   		  	  
   if (Dentro(11,16,57,62,627,400))
   	   comandos.blit(0,2,comandos.width,20, 646, 370, DDBLT_KEYSRC, lpDDSBack,0);	   		  	  
   if (Dentro(66,16,112,62,627,400))
   	   comandos.blit(0,25,comandos.width,43, 645, 371, DDBLT_KEYSRC, lpDDSBack,0);	   		  	  
   if (Dentro(11,78,57,124,627,400))		   //Move/attack
   	   comandos.blit(0,147,comandos.width,165, 645, 371, DDBLT_KEYSRC, lpDDSBack,0);	   		  	     
}		

////////////////////////////////////////////////////////////////////////////////////

void ControlInGame(	DIMOUSESTATE dims)
{
  //if (!tick) return;
	

   if ((((dims.rgbButtons[0] & 0x80) >0)  &&(Dentro(120,16,166,62,627,400))) || GetAsyncKeyState(0x55))// Construir / Upgrade		   
   {
   			   Construir(HUMAN);		     
   }
	//REPAIR	   
   if (((((dims.rgbButtons[0] & 0x80) >0) && Dentro(120,78,166,124,627,400))) || GetAsyncKeyState(0x50))// Repair
   {
		Repair(yactual, xactual, HUMAN);
		mousetime = TMOUSE;

				
	  
   }
	//RECRUIT
   if (((Dentro(66,78,112,124,627,400))&& ((dims.rgbButtons[0] & 0x80) >0) ) || GetAsyncKeyState(0x52))// Recruit
   {
		Recruit(yactual, xactual, HUMAN);			 
		mousetime = TMOUSE;
   }


   //Meter peña
		   if (mapa[yactual][xactual].raceowner == HUMAN)
		   {
             if ((Dentro(11,16,57,62,627,400) && leftMouseButton ) || GetAsyncKeyState(0x49)
				 || (Dentro(0,0,640,180,0,0) && leftMouseButton))
			 {
			   		  MeteUnits(yactual, xactual, HUMAN);
					  mousetime = TMOUSE;			
    		 }			
			 if (mapa[yactual][xactual].construccion >= VILLAGE && Dentro(0,0,640,180,0,0) && rightMouseButton)
			 {				
					//RECRUIT
					Recruit(yactual, xactual, HUMAN);			 
					mousetime = TMOUSE;
			 }
			 //Sacar peña
             if ((Dentro(66,16,112,62,627,400) && leftMouseButton)|| GetAsyncKeyState(0x4F)
				 				 || (Dentro(0,0,640,180,0,200) && leftMouseButton)
				 )			 
				  {
					  SacaUnits(yactual, xactual, HUMAN);
					  mousetime = TMOUSE;
				  }
	
		   }
		   //////////////////////////////////////
			if ((Dentro(11,78,57,124,627,400) && leftMouseButton)
                || GetAsyncKeyState(0x41))				
				//Move/attack
			{
		
				if (oriy == -1) 
				     if (((mapa[yactual][xactual].raceowner==HUMAN) && (mapa[yactual][xactual].unifuera > 0))
						 || ((mapa[yactual][xactual].racestriker==HUMAN) && (mapa[yactual][xactual].unienemigo > 0)))
					 {
					    oriy = yactual;
                        orix = xactual;
					 }
	
			}				
		   //Mover ejercito
		    
	       for(int i = 0;i < ALTO;i++)
              for(int j = 0;j < LARGO;j++)
			  {                 
			     if (Dentro(0,0,58,32,16+j*60,416+i*34))
				 {
					 if (mapa[i][j].construccion != INVALID)
					 {					  
						if (leftMouseReleased && oriy >= 0)
						{
						   MueveUnits(oriy, orix, i,j, HUMAN);
						   mousetime = TMOUSE;
						}
						else
						{
							if (leftMouseButton)
							{
								yactual = i;
								xactual = j;						   
							}
							if (leftMousePressed) SelectUnits(i,j);						
						}
					 }
				 }
			  }


	   if ((mapa[yactual][xactual].raceowner==HUMAN) && (mapa[yactual][xactual].construccion > NONE) &&Dentro(0,0,627,180,0,0))
	   {
			overBuilding = true;
			if (mapa[yactual][xactual].construccion >= VILLAGE && mapa[yactual][xactual].people > 0 && gold[0] > RECRUITGOLD) overVillage = true;
	   }
	  if ((mapa[yactual][xactual].raceowner==HUMAN) && (mapa[yactual][xactual].construccion > NONE) && Dentro(0,0,627,180,0,200))
	   {
			overGround = true;
	   }

		//}///////////END INGAME/////////////
}		




////////////////////////////////////////////////////////////////////////
// void Control()
////////////////////////////////////////////////////////////////////////

DIMOUSESTATE dimsg;          /* DirectInput mouse state structure */
void Control()
{
  if (!tick) return;
  
	WindowUpdate();

  

  if (mousetime > 0) 
     mousetime--;

  


   DIMOUSESTATE dims;          /* DirectInput mouse state structure */
	HRESULT hr;
	
	// AHORA EMPIEZA EL DIRECT INPUT DEL MOUSE
	// PEDIMOS EL ESTADO DEL MOUSE
	hr = g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &dims); 
	
	if (hr == DI_OK) // SI TENEMOS EL ESTADO
	{
		dimsg = dims;
		/* Ahora en dims hay el estado actual del mouse
		 * dims tiene :
		 *	    LONG lX, lY, lZ;
		 *			Son los desplazamientos relativos en los 3 ejes (Z es la rueda)
		 *     BYTE rgbButtons[4];
		 *			Son los 4 botones posibles de un mouse, con & 0x80 se ve si estan pulsados
		 */
		if (dims.lX == 0)
		{		
			cur.accx = DEFACC;
		}
		if (dims.lY == 0)
		{		
			cur.accy = DEFACC;
		}
		if (dims.lX > 0)
		{
			if (cur.lastx > 0) cur.accx+= (float)INCACC;
			else cur.accx = DEFACC;
			cur.lastx = 1;			
		}
		if (dims.lX < 0)
		{
			if (cur.lastx < 0) cur.accx += (float)INCACC;
			else cur.accx = DEFACC;
			cur.lastx = -1;
		}
		if (dims.lY > 0)
		{
			if (cur.lasty > 0) cur.accy+= (float)INCACC;
			else cur.accy = DEFACC;
			cur.lasty = 1;
		}
		if (dims.lY < 0)
		{
			if (cur.lasty < 0) cur.accy += (float)INCACC;
			else cur.accy = DEFACC;
			cur.lasty = -1;
		}
		if (mousetime <= 0) 
		{
			overBuilding = false;
			overGround = false;
			overVillage = false;

			lastLeftMouseButton = leftMouseButton;
			leftMouseButton = ((dims.rgbButtons[0] & 0x80) > 0);
			rightMouseButton = ((dims.rgbButtons[1] & 0x80) > 0);

			if (!leftMouseButton && lastLeftMouseButton) leftMouseReleased = true;
			else leftMouseReleased = false;

			if (leftMouseButton && !lastLeftMouseButton) leftMousePressed = true;
			else leftMousePressed = false;


			if(gameStatus == INGAME && !wActive) ControlInGame(dims);
			else if (gameStatus == MENU1)
			{ 				
				MainMenuUpdate();
				/*
			  if (leftMouseButton)
			  {
				  	LimpiarTeclado();
					if (wOp >= 0)					
					{
						mousetime = TMOUSE*2;					
						MainMenuUpdate();
					}
			  }*/
			}
			else if (gameStatus == VICTORY || gameStatus == DEFEAT)
			{
			  if (leftMouseButton)
			  {
				if (Dentro(0,0,SCREENX,SCREENY,0,0)) // Start game
				{
					if (gameMode == CAMPAIGN)
					{
						xmlManager *xml;

						xml = new xmlManager();
						xml->loadXml("map\\campaigns.dat");		
						int stageCount = xml->getTagCount("stage");
					
						delete xml;

						if (gameStatus == VICTORY && currentStage+1 == stageCount)
							InitEnding();
						else 
							InitMenuDif();
					}
					else InitMainMenu();

					mousetime = TMOUSE*5;
				}				
			  }
			}			
			else if (gameStatus == MENU2)
			{ 
				CampaignMenuUpdate();				
			}
			else if (gameStatus == SCENARIO)
			{ 
				ScenarioMenuUpdate();				
			}
			else if (gameStatus == ENDING)
			{ 
				if (leftMouseButton)
				{
					if (wOp >= 0)
					{
						InitMainMenu();
						mousetime = TMOUSE*2;					
					}
				}
			}			
			else if (gameStatus == BRIEFING)
			{
				if (leftMouseButton)
				{
					//LimpiarTeclado();
					if (wOp >= 0)
					{
						gameStatus = INGAME;
						mousetime = TMOUSE*2;					
						WindowClose();
					}
				}					
			}
            else if (gameStatus == CREDITS)
			{
				if (leftMouseButton && wOp >= 0) {InitMainMenu();mousetime = TMOUSE*2;}
			}
			
			else if (gameStatus == PAUSE)
			{
				PauseMenuUpdate(); 
			}

			else if (gameStatus == OBJECTIVES)
			{
				if (leftMouseButton && wOp >= 0) {InitPauseMenu();mousetime = TMOUSE*2;}
			}
		}					
		cur.x += (float)dims.lX*cur.accx;
		cur.y += (float)dims.lY*cur.accy;
				
		if (cur.x < 0) cur.x = 0;
		if (cur.x > SCREENX-8) cur.x = SCREENX-8;
		if (cur.y < 0) cur.y = 0;
		if (cur.y > SCREENY-8) cur.y = SCREENY-8;
		
	}
	else g_pMouse->Acquire(); // SI NO TENEMOS EL ESTADO, PEDIR EL MOUSE


	
}

////////////////////////////////////////////////////////////////////////////////////

int realFps = 0;

int CalculaFps()
{
	time2 = timeGetTime();
	fps++;
	if(time2 - time1 > 1000)
	{
		time1 = timeGetTime();
		realFps = fps;
		fps = 0;
	}
	return fps;
}



void DrawFps()
{
	int fps = realFps;
	sprintf(s, "FPS: %d \0", fps);
	//PrintText(10, 10, lpDDSBack, s, RGB(255,0,0));
}





////////////////////////////////////////////////////////////////////////////////
// LoadMap(char *name)
////////////////////////////////////////////////////////////////////////////////
void LoadMap(char *name)
{
	FILE *fd;
	
	fd = fopen(name, "r");		

	fscanf(fd, "%d\n", &xactual);
	fscanf(fd, "%d\n", &yactual);
	fscanf(fd, "%d\n", &gold[0]);
	fscanf(fd, "%d\n", &gold[1]);
	fscanf(fd, "%d\n", &hora);	
	fscanf(fd, "%d\n", &AI_agressiveness);	

	fscanf(fd, "%d\n", &objectiveCom);
	fscanf(fd, "%d\n", &objectivePar1);
	fscanf(fd, "%d\n", &objectivePar2);
	fscanf(fd, "%d\n", &objectiveEndsMission);
	
	/*objectiveCom = OBJ_BUILD;
	objectivePar1 = 5;
	objectivePar2 = CAMP;*/

	/*objectiveCom = OBJ_RECRUIT;
	objectivePar1 = 500;*/

	/*objectiveCom = OBJ_CONQUER;
	objectivePar1 = 0;
	objectivePar2 = 0;

	objectiveEndsMission = 1;
	gold[0] = 10000;
	*/

	for(int i=0;i<5;i++)
       for(int j=0;j<10;j++)
	   {
		   fscanf(fd, "%d\n", &mapa[i][j].construccion);
		   fscanf(fd, "%d\n", &mapa[i][j].unidentro);
		   fscanf(fd, "%d\n", &mapa[i][j].unifuera);
		   fscanf(fd, "%d\n", &mapa[i][j].unienemigo);
		   fscanf(fd, "%d\n", &mapa[i][j].people);
		   fscanf(fd, "%d\n", &mapa[i][j].raceowner);
		   fscanf(fd, "%d\n", &mapa[i][j].racestriker);
		   fscanf(fd, "%d\n", &mapa[i][j].integrity);
		   fscanf(fd, "%d\n", &mapa[i][j].explored);
		   fscanf(fd, "%d\n", &mapa[i][j].evervisible);		       	  
		   if (mapa[i][j].construccion > 0) mapa[i][j].onceBuilt = true;
		   
		   int k;

		   for(k = 0; k < mapa[i][j].unidentro;k++)
		   		NewUnit(mapa[i][j].raceowner, j,i,INSIDE, 100);
		   for(k = 0; k < mapa[i][j].unifuera;k++)
		   		NewUnit(mapa[i][j].raceowner, j,i, OUTSIDE, 100);
		   for(k = 0; k < mapa[i][j].unienemigo;k++)
		   		NewUnit(mapa[i][j].racestriker, j,i,OUTSIDE, 100);			
		   if (mapa[i][j].construccion > 0)
		   {
			   switch(mapa[i][j].construccion)
			   {
					case CASTLE: mapa[i][j].maxintegrity = INT_CASTLE; break;
					case CAMP: mapa[i][j].maxintegrity = INT_CAMP; break;
					case FORTRESS: mapa[i][j].maxintegrity = INT_FORTRESS; break;
					case VILLAGE: mapa[i][j].maxintegrity = INT_VILLAGE; break;
					case CITADEL: mapa[i][j].maxintegrity = INT_CITADEL; break;
			   }			   	   

			   mapa[i][j].integrity = (mapa[i][j].integrity * mapa[i][j].maxintegrity)  / 100;
		   }

		   //VISI
		   if (mapa[i][j].explored) Explore(i, j);
       }	


	fclose(fd);
}


void ResetMap()
{
	for(int i = 0;i < ALTO;i++)
       for(int j = 0;j < LARGO;j++)
	   {
		   mapa[i][j].onceBuilt = false;
		   mapa[i][j].construccion	= 0;
		   mapa[i][j].unifuera		= 0;
		   mapa[i][j].unidentro		= 0;
		   mapa[i][j].unienemigo	= 0;
		   mapa[i][j].raceowner		= NONE;		   		   
		   mapa[i][j].explored		= GNOTEXPLORED;		   		   
		   mapa[i][j].visible = GNOTVISIBLE;		   
		   mapa[i][j].evervisible = 0;

	   }	
}

int trigCount = 0;

void InitScenarioMap(char *path)
{
	gameMode = SCENARIO;

	ingameMsgTimer = 0;
	ingameMarkTimer = 0;

	IniUnits();
	ResetMap();
	
	LoadMap(path);

	trigCount = 0;
	dificultad = difficulty[AI_agressiveness];
	currentUnits = 0;
}


void InitMap(int stage)
{
	gameMode = CAMPAIGN;

	ingameMsgTimer = 0;
	ingameMarkTimer = 0;


	currentStage = stage;
	char *strbuf = new char[256];
	xmlManager *xml;
	xml = new xmlManager();
	xml->loadXml("map\\campaigns.dat");		
					
	IniUnits();
	ResetMap();
	sprintf(strbuf, "map/%s", xml->getStrValue(xml->getNodeByName("stage", stage+1), "map", 1));
	
	LoadMap(strbuf);

	trigCount = xml->getTagCount(xml->getNodeByName("stage", stage+1), "onenter");
	
	if (trigCount > 0)
	{
		triggers = new trig[trigCount];

		for (int i = 0; i < trigCount; i++)
		{
			// ESTO NO VA Y ES UN BUGGGG
			//triggers[i].y = xml->getIntValue( xml->getNodeByName("stage", stage+1), "y", i+1);
			//triggers[i].x = xml->getIntValue( xml->getNodeByName("stage", stage+1), "x", i+1);
			
			triggers[i].y = xml->getIntValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "y", 1);
			triggers[i].x = xml->getIntValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "x", 1);
			
			triggers[i].marky = xml->getIntValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "marky", 1);
			triggers[i].markx = xml->getIntValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "markx", 1);
			
			triggers[i].reenter = xml->getBoolValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "reenter", 1);
			triggers[i].msg = xml->getStrValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "msg", 1);

			triggers[i].time = xml->getIntValue( xml->getNodeByName(xml->getNodeByName("stage", stage+1), "onenter", i+1), "time", 1);
			if (triggers[i].time <= 0) triggers[i].time = 300;
			
			triggers[i].triggered = false;
		}
		
	}

	//AI_agressiveness = xml->getIntValue(xml->getNodeByName("stage", stage+1), "aiagressiveness", 1);
	delete xml;

	dificultad = difficulty[AI_agressiveness];
	currentUnits = 0;
}




void InitMapMedium()
{		
	IniUnits();
	ResetMap();
	LoadMap("map/stage1.map");
}


void InitMapHard()
{
	for(int i = 0;i < ALTO;i++)
       for(int j = 0;j < LARGO;j++)
	   {
		   mapa[i][j].construccion	= 0;
		   mapa[i][j].unifuera		= 0;
		   mapa[i][j].unidentro		= 0;
		   mapa[i][j].unienemigo	= 0;
		   mapa[i][j].raceowner		= NONE;		   		   
	   }
	
	mapa[3][2].construccion = VILLAGE; 
	mapa[3][2].integrity = 100;
    mapa[3][2].people = 30; 

    mapa[1][8].construccion = CAMP; 
	mapa[1][8].integrity = 65; 
	mapa[1][8].unidentro = 10;
	mapa[1][8].unifuera = 0;
    mapa[1][8].raceowner = HUMAN;    
	
	mapa[3][6].raceowner = COMP;
	mapa[3][6].unifuera = 0;
	mapa[3][6].unidentro = 40;
	mapa[3][6].construccion = FORTRESS;
	mapa[3][6].integrity = 100;

	mapa[1][5].construccion = VILLAGE; 
	mapa[1][5].integrity = 100;
    mapa[1][5].people = 30; 

	mapa[0][4].construccion = VILLAGE; 
	mapa[0][4].integrity = 100;
    mapa[0][4].people = 30; 

	mapa[1][1].raceowner = COMP;
	mapa[1][1].unifuera = 0;
	mapa[1][1].unidentro = 40;
	mapa[1][1].construccion = FORTRESS;
	mapa[1][1].integrity = 100;


	gold[0] = 300;
	dificultad = HARD;
	gold[1] = 1500;
	xactual = 8;yactual = 1;
}


////////////////////////////////////////////////////////////////////////
// void inicializar()
////////////////////////////////////////////////////////////////////////

void Inicializar()
{	
	SpriteManager::Init();

	ratio[CITADEL] = CITADELRATIO;
	ratio[VILLAGE] = VILLAGERATIO;
	ratio[CAMP] = CAMPRATIO;
	ratio[FORTRESS] = FORTRESSRATIO;
	ratio[CASTLE] = CASTLERATIO;

	InitAudio();
	InitGfx();
	
	//music();
	time1 = timeGetTime();		
	time1t = time1;		
}

int ff1 = 0;
int ff2 = 16;
int ss[5] = {0,0,0,0,0};
long ftime = 0;
int stime = 0;
int sturn = 0;

void ActualizarFuego()
{
   ftime+=tick;
   stime+=tick;
   if (ftime > 3)
   {
	   ftime = 0;
       ff1++;
       ff2++;
	   if (ff1>=32) ff1 = 0;
       if (ff2>=32) ff2 = 0;
	   
   }
   if (stime > BATTLETIME/3)
   {
	   sturn++;
	   stime = 0;
       for (int i=0;i < 5;i++)
	   { 
		   //if (sturn%5==i) 
			   ss[i]++;
       	   if (ss[i]>=3) ss[i] = 0;
	   }
   }

}

bool revealMapCheat = false;

bool Visible(int i, int j)
{	
	if ((mapa[i][j].racestriker == HUMAN && mapa[i][j].unienemigo > 0)||
       mapa[i][j].raceowner == HUMAN)
	   return true;
	return false;
}

void DrawMap()
{
	panel0.blit(0,0,panel0.width,panel0.height, 0, 400, 0, lpDDSBack,0);	   
	for(int i = 0;i < ALTO;i++)
       for(int j = 0;j < LARGO;j++)
	   {
		   if (mapa[i][j].evervisible) mapa[i][j].visible = true;
			
			if (revealMapCheat)
			{
				mapa[i][j].explored = true;
				mapa[i][j].visible = true;
				mapa[i][j].t_visible = 10;				
			}

			if (mapa[i][j].construccion < 0) continue;
		   if (mapa[i][j].explored == GEXPLORED)
		   {
			   if (mapa[i][j].construccion >= 0) suelo.blit(j*16,i*16,(j*16)+58,(i*16)+32, 16+j*60, 416+i*34, 0, lpDDSBack,0);	   
			   if ((mapa[i][j].visible == GVISIBLE || mapa[i][j].t_visible >0) && mapa[i][j].construccion > 0) minis[0].blit((mapa[i][j].construccion-1)*58,0,mapa[i][j].construccion*58,32, 16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	   
			   if (mapa[i][j].visible == GNOTVISIBLE && mapa[i][j].t_visible <= 0)				   
			   {
				   
				   if (mapa[i][j].g_construccion > 0) minis[0].blit((mapa[i][j].g_construccion-1)*58,0,mapa[i][j].g_construccion*58,32, 16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	   
				   minis[1].blit(0,0,58,32, 16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	   
				   continue;
			   }
			   if (mapa[i][j].t_visible > 0) mapa[i][j].t_visible--;

			   if (mapa[i][j].raceowner == HUMAN) bandera0.blit(0,0,18,31,16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	 
			   if (mapa[i][j].raceowner == COMP) bandera1.blit(0,0,18,31,16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	 
			   if (mapa[i][j].unifuera > 0)
			   {
				  if (mapa[i][j].raceowner == HUMAN)
					  ex0.blit(0,0,10,15,18+j*60, 430+i*34, DDBLT_KEYSRC, lpDDSBack,0);	 
				  else ex1.blit(0,0,10,15,18+j*60, 430+i*34, DDBLT_KEYSRC, lpDDSBack,0);	 
			   }
			   if (mapa[i][j].unienemigo > 0)
			   {
				  if (mapa[i][j].racestriker == HUMAN)
					 ex0.blit(0,0,10,15,58+j*60, 430+i*34, DDBLT_KEYSRC, lpDDSBack,0);	 
				  else ex1.blit(0,0,10,15,58+j*60, 430+i*34, DDBLT_KEYSRC, lpDDSBack,0);	 
			   }
			   if ((mapa[i][j].construccion > 0) && (mapa[i][j].integrity <= 50)) 
				  fuego.blittrans(ff1*30,0,2+(ff1+1)*30,50,28+j*60 , 390+i*34, DDBLT_KEYSRC, lpDDSBack,ALPHA/2);	   
			   if ((mapa[i][j].unienemigo > 0))
			   {
				  if (db > 0 ) battle.blit(0,0,58,32, 16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	      
			   }
		   }
		   else minis[1].blit(0,0,58,32, 16+j*60, 416+i*34, DDBLT_KEYSRC, lpDDSBack,0);	   
	   }
    if (oriy == -1) target0.blit(0,0,63,36, 13+xactual*60, 413+yactual*34, DDBLT_KEYSRC, lpDDSBack,0);	   
    else target1.blit(0,0,63,36, 13+xactual*60, 413+yactual*34, DDBLT_KEYSRC, lpDDSBack,0);	   
}


void DrawArrows()
{
	for (int i = 0;i < MAXFLECHAS;i++)
	   if (mapa[yactual][xactual].flechas[i].active)
	   {
		   int lon = 20;
		   int y = mapa[yactual][xactual].flechas[i].y;
		   if (y <= 150) lon = ((y-50)/4)+15;
		   else lon = ((250-y)/4)+15;
		   if (mapa[yactual][xactual].raceowner == HUMAN)
		      FillRectangle(lpDDSBack,mapa[yactual][xactual].flechas[i].x, mapa[yactual][xactual].flechas[i].y +(lon/2)-lon/5,1 , lon/5, 70, 195, 200);
		   else 
			  FillRectangle(lpDDSBack,mapa[yactual][xactual].flechas[i].x, mapa[yactual][xactual].flechas[i].y +(lon/2)-lon/5,1 , lon/5, 230, 35, 30);
		   FillRectangle(lpDDSBack,mapa[yactual][xactual].flechas[i].x, mapa[yactual][xactual].flechas[i].y +(lon/2),1 , lon, 215, 135, 0);
		   FillRectangle(lpDDSBack,mapa[yactual][xactual].flechas[i].x, mapa[yactual][xactual].flechas[i].y +lon+(lon/2),1 , lon/12, 215, 215, 225);
	   }
}


void DrawNotVisible()
{
	if (mapa[yactual][xactual].explored == GEXPLORED)
	{
		if (mapa[yactual][xactual].g_construccion > 0) 
		{
			cons[mapa[yactual][xactual].g_construccion-1].blit(0,0,640,180, 0, 0, DDBLT_KEYSRC, lpDDSBack,0);	   		
		} 
		else 
		{
			arbol1.blit(0,66,arbol1.width,arbol1.height, 640-90*(xactual%3)+xactual*60-yactual*43,0, DDBLT_KEYSRC, lpDDSBack,0);		
			arbol1.blit(0,40,arbol1.width,arbol1.height, 500-(LARGO-xactual)*30+(ALTO-yactual)*10-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);
			arbol1.blit(0,30,arbol1.width,arbol1.height, 30-(xactual%2)*40+(xactual%4*50)+(yactual+xactual)*20+yactual*33,0, DDBLT_KEYSRC, lpDDSBack,0);
			arbol1.blit(0,20,arbol1.width,arbol1.height, 500-(LARGO-xactual)*30+(ALTO-yactual)*10-yactual*25-(LARGO-xactual)*30+(ALTO-yactual)*40-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);				
			arbol1.blit(0,10,arbol1.width,arbol1.height, -90*(xactual%3)+xactual*60-yactual*43,0, DDBLT_KEYSRC, lpDDSBack,0);		
			arbol1.blit(0,00,arbol1.width,arbol1.height, 0-(LARGO-xactual)*30+(ALTO-yactual)*40-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);
			arbol1.blit(0,00,arbol1.width,arbol1.height, 420-(xactual)*30+(yactual)*22-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);
			
		}
		negro.blit(0,0,negro.width,negro.height,0, 0, DDBLT_KEYSRC, lpDDSBack,0);	   	
	}
	else negro.blit(0,0,negro.width,negro.height,0, 0, 0, lpDDSBack,0);	   	
}


void DrawMainScreen()
{
	UINT i1,i2,i3,i4;
	i1 = 4+xactual*7 * yactual*2 - (xactual-yactual)*13;
	i2 = 2+(yactual -xactual)*13-LARGO*3+xactual*17;
	i3 = 1+i1 + xactual;
	i4 = 3+i1+ i2;	
	i1 = i1%5;
	i2 = i2%5;
	i3 = i3%5;
	i4 = i4%5;
	suelo.blit(i1*320,0,(i1+1)*320,200, 0, 0, 0, lpDDSBack,0);	   
    suelo.blit(i2*320,0,(i2+1)*320,200, 320, 0, 0, lpDDSBack,0);	   
	suelo.blit(i3*320,0,(i3+1)*320,200, 0, 200, 0, lpDDSBack,0);	   
    suelo.blit(i4*320,0,(i4+1)*320,200, 320, 200, 0, lpDDSBack,0);	   
	if (mapa[yactual][xactual].visible == GNOTVISIBLE && mapa[yactual][xactual].visible <= 0) 
	{
		DrawNotVisible();
		return;
	}	
	if (mapa[yactual][xactual].construccion > 0) 
	{
		cons[mapa[yactual][xactual].construccion-1].blit(0,0,640,180, 0, 0, DDBLT_KEYSRC, lpDDSBack,0);	   
		float integrity = ((float)mapa[yactual][xactual].integrity/(float)mapa[yactual][xactual].maxintegrity);
		if (integrity <= 0.66f) 
		{	
			DrawFire(mapa[yactual][xactual].construccion, integrity);		
		}	
		int recx = 210;

		FillRectangle(lpDDSBack,recx, 40,200+2 , 5, 200, 190, 50);
		FillRectangle(lpDDSBack,recx+1, 40+1,200 , 3, 10, 10, 0);		
		FillRectangle(lpDDSBack,recx+1, 40+1, (int)(integrity*200) , 3, 0, 225, 0);
	
		float unitCapacity = ((float)mapa[yactual][xactual].unidentro) / ((float)MAXINSIDE[mapa[yactual][xactual].construccion]);
		FillRectangle(lpDDSBack,recx, 40+10,200+2 , 5, 200, 190, 50);
		FillRectangle(lpDDSBack,recx+1, 40+1+10,200 , 3, 10, 10, 0);		
		FillRectangle(lpDDSBack,recx+1, 40+1+10, (int)(unitCapacity*200) , 3, 255, 0, 0);
	

	}
	else 
	{
		if (!mapa[yactual][xactual].onceBuilt) {
		arbol1.blit(0,66,arbol1.width,arbol1.height, 640-90*(xactual%3)+xactual*60-yactual*43,0, DDBLT_KEYSRC, lpDDSBack,0);		
		arbol1.blit(0,40,arbol1.width,arbol1.height, 500-(LARGO-xactual)*30+(ALTO-yactual)*10-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);
		arbol1.blit(0,30,arbol1.width,arbol1.height, 30-(xactual%2)*40+(xactual%4*50)+(yactual+xactual)*20+yactual*33,0, DDBLT_KEYSRC, lpDDSBack,0);
		arbol1.blit(0,20,arbol1.width,arbol1.height, 500-(LARGO-xactual)*30+(ALTO-yactual)*10-yactual*25-(LARGO-xactual)*30+(ALTO-yactual)*40-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);				
		arbol1.blit(0,10,arbol1.width,arbol1.height, -90*(xactual%3)+xactual*60-yactual*43,0, DDBLT_KEYSRC, lpDDSBack,0);		
		arbol1.blit(0,00,arbol1.width,arbol1.height, 0-(LARGO-xactual)*30+(ALTO-yactual)*40-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);
		arbol1.blit(0,00,arbol1.width,arbol1.height, 420-(xactual)*30+(yactual)*22-yactual*25,0, DDBLT_KEYSRC, lpDDSBack,0);
		}
	}
	DrawUnits();
	DrawArrows();	
}


void DisplayMessage(char *msg, int tim)
{
	ingameMsg = msg;
	ingameMsgTimer = tim;
}

void DisplayMark(int y, int x, int tim)
{
	marky = y;markx = x;
	ingameMarkTimer = tim;
}


void DrawGUI()
{
//	char g1[20];

	if (ingameMsg != NULL)
	{
		PrintGFX(mfont, 10, 10, ingameMsg, lpDDSBack);
	}		
	else{
	if (objectiveCom == OBJ_RECRUIT)
	{
		char *s = new char[256];
		sprintf(s, "Recruit %d more soldiers\0", objectivePar1 - currentUnits);
		PrintGFX(mfont, 10, 10, s, lpDDSBack);
		delete s;
	}
	
	if (objectiveCom == OBJ_BUILD)
	{
		char *s = new char[256];
		char *buildString= new char[256];;
		switch(objectivePar2)
		{
			case CAMP:
				sprintf(buildString, "camp/s\0");
				break;

			case FORTRESS:
				sprintf(buildString, "fortress/es\0");
				break;

			case CASTLE:
				sprintf(buildString, "castle/s\0");
				break;
		}
		sprintf(s, "Build %d more %s\0", objectivePar1, buildString);
		PrintGFX(mfont, 10, 10, s, lpDDSBack);
		delete s;
		delete buildString;
	}
	}
	//PrintGFX(mfont, 10, 60, "work in progress demo", lpDDSBack);
	//PrintRGFX(mfont, 210, 60, "3294", lpDDSBack);
	switch (mapa[yactual][xactual].raceowner)
	{
		case COMP:comp.blit (0,0,comp.width,comp.height, 640, 0, 0, lpDDSBack,0);	   	break;
		case HUMAN:human.blit (0,0,human.width,human.height, 640, 0, 0, lpDDSBack,0);	   	break;
		default:none.blit (0,0,none.width,none.height, 640, 0, 0, lpDDSBack,0);	   	break;
	}

    panel3.blit(0,0,panel3.width,panel3.height, 640, 150, 0, lpDDSBack,0);	   	
	
	//PrintGFX(mfont, 700, 160, "Gold", lpDDSBack);

	if (mapa[yactual][xactual].visible || mapa[yactual][xactual].evervisible)
	{
	PrintNumGFX(font, 775, 160, gold[HUMAN-1], lpDDSBack);
    //Unidentro/Unifuera
	PrintNumGFX(font, 727, 202, mapa[yactual][xactual].unidentro, lpDDSBack);
	PrintNumGFX(font, 775, 202, mapa[yactual][xactual].unifuera, lpDDSBack);
	//Unidentro/Unifuera NEXT
	PrintNumGFX(font, 727, 225, mapa[yactual][xactual].unidentro+(int)sqrt((float)mapa[yactual][xactual].unidentro), lpDDSBack);
			
	if (mapa[yactual][xactual].construccion > NONE)
	{
		switch(mapa[yactual][xactual].construccion)
		{
			case CAMP:		estructuras.blit(0,3,estructuras.width,25,645,125,DDBLT_KEYSRC,lpDDSBack,0);			
				break;				
			case FORTRESS:	estructuras.blit(0,28,estructuras.width,50,645,125,DDBLT_KEYSRC,lpDDSBack,0);			
				break;
			case CASTLE:	estructuras.blit(0,53,estructuras.width,75,645,125,DDBLT_KEYSRC,lpDDSBack,0);			
				break;
			case VILLAGE:	estructuras.blit(0,75,estructuras.width,100,645,125,DDBLT_KEYSRC,lpDDSBack,0);			
				break;
			case CITADEL:	estructuras.blit(0,97,estructuras.width,121,645,125,DDBLT_KEYSRC,lpDDSBack,0);			
				break;
		}
		PrintNumGFX(font, 780, 127, mapa[yactual][xactual].integrity, lpDDSBack);		
	}
	if (mapa[yactual][xactual].construccion >= VILLAGE)
	{
	   //sprintf(g1, "PEOPLE: %d\0", mapa[yactual][xactual].people);
	   //PrintText(650, 100, lpDDSBack, g1, RGB(255,255,255));	
		PrintNumGFX(font, 755, 258, mapa[yactual][xactual].people, lpDDSBack);
		PrintNumGFX(font, 755, 281, mapa[yactual][xactual].people+(int)sqrt((float)mapa[yactual][xactual].people)/2, lpDDSBack);	
	}
	if (mapa[yactual][xactual].racestriker != NONE)
	{
	   switch(mapa[yactual][xactual].racestriker)
	   {
	      case HUMAN:
			  banderag1.blit(0,0,banderag1.width,banderag1.height,747,307,DDBLT_KEYSRC,lpDDSBack,0);
			   //sprintf(g1, "%s\0", "Player");break;
			   break;
          case COMP:
			  banderag0.blit(0,0,banderag0.width,banderag0.height,747,307,DDBLT_KEYSRC,lpDDSBack,0);
			   //sprintf(g1, "%s\0", "Comp");break;
			   break;
	   }
	   //PrintText(720, 310, lpDDSBack, g1, RGB(255,255,255));	
	   //sprintf(g1, "STRIKERS: %d\0", mapa[yactual][xactual].unienemigo);
	   //PrintText(650, 120, lpDDSBack, g1, RGB(255,255,255));	
	   PrintNumGFX(font, 755, 332, mapa[yactual][xactual].unienemigo, lpDDSBack);	
	}
	}
	//DIA Y NOCHE
	if (hora == DAYTIME)
	{
		sun.blit(0,0,sun.width,sun.height,600-14,2,DDBLT_KEYSRC,lpDDSBack,0);
	}
	else
	{
		moon.blit(0,0,moon.width,moon.height,600-14,2,DDBLT_KEYSRC,lpDDSBack,0);
	}
	day.blit(0,0,day.width,day.height,600-2-13,2-2,DDBLT_KEYSRC,lpDDSBack,0);


	panel1.blit(0,0,panel1.width,panel1.height,627,400,0,lpDDSBack,0);

    if (mapa[yactual][xactual].raceowner != HUMAN)
	{
		celdas.blit(0,0,46,46,638,416,0,lpDDSBack,0);
		celdas.blit(46,0,46*2,46,693,416,0,lpDDSBack,0);		
		celdas.blit(46*2,0,46*3,46,747,416,0,lpDDSBack,0);		
		//celdas.blit(46*3,0,46*4,46,638,478,0,lpDDSBack,0);
		celdas.blit(46*4,0,46*5,46,693,478,0,lpDDSBack,0);		
		celdas.blit(46*5,0,46*6,46,747,478,0,lpDDSBack,0);		
		if (mapa[yactual][xactual].racestriker != HUMAN)
		{
			celdas.blit(46*3,0,46*4,46,638,478,0,lpDDSBack,0);
		}
	}
	else
	{
		if (mapa[yactual][xactual].unidentro == 0)
			celdas.blit(46,0,92,46,693,416,0,lpDDSBack,0);		
		if (mapa[yactual][xactual].unifuera == 0)
		{
			celdas.blit(0,0,46,46,638,416,0,lpDDSBack,0);			
			celdas.blit(46*3,0,46*4,46,638,478,0,lpDDSBack,0);
		}
		if (mapa[yactual][xactual].construccion == NONE)
		{
			celdas.blit(0,0,46,46,638,416,0,lpDDSBack,0);
			celdas.blit(46,0,92,46,693,416,0,lpDDSBack,0);		
			celdas.blit(46*5,0,46*6,46,747,478,0,lpDDSBack,0);				
		}
		else
		{
			if (mapa[yactual][xactual].integrity == 100)
			   celdas.blit(46*5,0,46*6,46,747,478,0,lpDDSBack,0);				
		}
		if (mapa[yactual][xactual].construccion >= CASTLE)
		{
			celdas.blit(46*2,0,46*3,46,747,416,0,lpDDSBack,0);		
		}
		if ((mapa[yactual][xactual].construccion != VILLAGE && mapa[yactual][xactual].construccion != CITADEL)
			|| (mapa[yactual][xactual].people == 0))
		    celdas.blit(46*4,0,46*5,46,693,478,0,lpDDSBack,0);		
		
		
	}
	DrawHelp(dimsg);
	escudo.blit(0,0,escudo.width,escudo.height,605,380,DDBLT_KEYSRC,lpDDSBack,0);			


	// New dev
	// Movement line
	if (oriy != -1)
	{		
		DrawLine(lpDDSBack,46+(orix*60),430+(oriy*34),46+(xactual*60),430+(yactual*34), 255, 0, 0);
	}

	//TRIGGERS
	for(int i = 0; i < trigCount;i++)
	{
		if (yactual == triggers[i].y && xactual == triggers[i].x && ingameMsg == NULL && mapa[yactual][xactual].raceowner == HUMAN)
		{
			if (!triggers[i].triggered || triggers[i].reenter)
			{
				if (triggers[i].marky != -1)
				{
					DisplayMark(triggers[i].marky, triggers[i].markx, triggers[i].time);
				}
			
				DisplayMessage(triggers[i].msg, triggers[i].time);			
			}

			if (!triggers[i].triggered)
			{
				triggers[i].triggered = true;
				break;
			}
		}
	}
	
	if (tick) {ingameMsgTimer--;ingameMarkTimer--;}
	if (ingameMsgTimer < 0) ingameMsg = NULL;

	if (ingameMarkTimer > 0 && ingameMarkTimer%100 > 10)
	{
		switch(marky)
		{
			case -2:
				switch(markx)
				{
					case 0: marker.blit(0,0,marker.width,marker.height, 275, 50, DDBLT_KEYSRC, lpDDSBack,0);
						break;
				}
				break;

			default:
				marker.blit(0,0,marker.width,marker.height, 46+(markx*60) - 40 -39, 430+(marky*34) - 35 - 29, DDBLT_KEYSRC, lpDDSBack,0);
				break;
		}
	}
}


//////////////////////////////////////////////////////////////////
long btime = 0;

void NewFlecha(unit flechas[],int locy, int locx, int soldier, int columna)
{
	int i = 0;
	bool trobat = false;

	while(!trobat && i < MAXFLECHAS)
	{
		if (!flechas[i].active) trobat = true;
		else i++;
	}
	if (i == MAXFLECHAS) return;
	flechas[i].active = true;
    flechas[i].locy = locy;
    flechas[i].locx = locx;
	flechas[i].destx = columna;
	flechas[i].desty = rand()%2-rand()%2;
    flechas[i].location = soldier;
	flechas[i].velocidad = 5+rand()%3;
    flechas[i].ataque = DANYOFLECHAS;
	flechas[i].y = 40+rand()%50;
    flechas[i].x = 20+(25*columna)-flechas[i].desty*15;

}


void ActualizaFlechas(unit flechas[])
{
	for (int i = 0;i < MAXFLECHAS;i++)
		if (flechas[i].active)
		{
			flechas[i].x += flechas[i].desty;
			flechas[i].y += flechas[i].velocidad;
			if (flechas[i].y > 250)
			{ 
				flechas[i].active = false;
				int s = flechas[i].location;
				if (units[s].active && units[s].y >= AHEIGHT/2)
				{
				   units[s].energy -= DANYOFLECHAS;
				   if (units[s].energy <= 0)
				   {
					  units[s].active = false;
				 	  mapa[units[s].locy][units[s].locx].units[units[s].y][units[s].x] = INVALID;
					  mapa[units[s].locy][units[s].locx].unienemigo--;
				   }						
				}																
			}
		}
}


int CuentaFlechas(int i, int j)
{
	int cont = 0;
	for (int k=0;k< MAXFLECHAS;k++)
		if (mapa[i][j].flechas[k].active) cont++;
   return cont;
}

void AtaqueConstruccion(int i, int j, bool defendida)
{	
	int il = (AHEIGHT/2);
	for (int jl = 0; jl < AWIDTH; jl++)			
	   if (mapa[i][j].units[il][jl] != INVALID)
	   {
	 	  int soldier = mapa[i][j].units[il][jl];				
		  //ATAQUE DE LA CONSTRUCCION
		  int cont = CuentaFlechas(i,j);		
		  if (cont*2 < mapa[i][j].unidentro && rand()%256 > 220)  NewFlecha(mapa[i][j].flechas, i,j, soldier, jl);		  
          //ATAKE A LA CONSTRUCCION	
		  if (!defendida)
		  {
			  if (units[soldier].velcont > 10)
			  {
				  units[soldier].frame = (units[soldier].frame+1)%3;
				  units[soldier].velcont = 0;
				  if (units[soldier].frame == 2)
				  {
					  int critico = (((rand()%1000)*units[soldier].critico)/1000);
					  int hit = units[soldier].ataque + critico;
					  if (critico >= CRITICLIMIT)
					  { 
						  units[soldier].hit = rand()%4;
						  units[soldier].hitTime = HITTIME;
					  }
					  mapa[i][j].integrity -= hit;
				  }		  	  	  
			  }
			  else 
				 units[soldier].velcont += units[soldier].velocidad;								
		  }
	   }
	


	//float t2 = (float)mapa[i][j].unienemigo;					  
	//t2 = (float)sqrt(t2/6);
	//mapa[i][j].integrity -= 1;//(int)(t2/ratio[mapa[i][j].construccion]);
	//if (rand()%100 > 80)mapa[i][j].unienemigo = MAX(0,(mapa[i][j].unienemigo)-ratio[mapa[i][j].construccion]);
	if (mapa[i][j].integrity <= 0) DestruyeConstruccion(i, j);					 
}

void Conquista(int i, int j)
{

	if ((i == yactual) && (j == xactual) && 
				mapa[yactual][xactual].racestriker == HUMAN && 
				mapa[yactual][xactual].unidentro==0){ Sonido(9,SB,2 ); }

    mapa[i][j].unifuera = mapa[i][j].unienemigo;
	mapa[i][j].unienemigo = 0;
	mapa[i][j].raceowner = mapa[i][j].racestriker;
	mapa[i][j].racestriker = NONE;
	
   for(int ty = AHEIGHT/2;ty < AHEIGHT;ty++)
	  for(int tx =0;tx < AWIDTH;tx++)
	  {
		 int unidad = mapa[i][j].units[ty][tx];
		 if (unidad != INVALID)
		 {
			mapa[i][j].units[ty][tx] = INVALID;
			mapa[i][j].units[AHEIGHT-ty-1][tx] = unidad;	
			units[unidad].y = AHEIGHT-ty-1;
		 }
	  }


	 
}

void Battle()
{
   int pinyos = 0;
   btime+=tick;
   if (btime > BATTLETIME)
   {
       btime = 0;
       for(UINT i = 0; i < ALTO; i++)
	   for(UINT j = 0; j < LARGO; j++)
	   {		  
		  if (mapa[i][j].unienemigo > 0)
		  {				
			  pinyos = 1;
			  if (mapa[i][j].unifuera > 0)
			  {
				  if (mapa[i][j].unidentro > 0 ) AtaqueConstruccion(i,j, true);
				  for(int il = (AHEIGHT/2)-1;il < (AHEIGHT/2)+1;il++)
		 	         for (int jl = 0; jl < AWIDTH; jl++)			
						 if (mapa[i][j].units[il][jl] != INVALID)
						 {
							int soldier = mapa[i][j].units[il][jl];				
			 			    //ATAQUE
							int yenemigo = 0;
							if (yenemigo = EnemigoDelante(i,j,il,jl))
							{
								units[soldier].frameFractionY = 0.0f;
								if (units[soldier].velcont > 10)
								{
								   units[soldier].frame = (units[soldier].frame+1)%3;
								   units[soldier].velcont = 0;
								   if (units[soldier].frame == 2)
								   {
									   int enemigo = mapa[i][j].units[yenemigo][jl];
									   int critico = (((rand()%1000)*units[soldier].critico)/1000);
									   int hit = units[soldier].ataque + critico - units[enemigo].armadura;
									   units[enemigo].energy -=  hit ;
									   if (critico >= CRITICLIMIT){
										   units[soldier].hitTime = HITTIME;
										   units[soldier].hit = rand()%4;
									   }
									   if (units[enemigo].energy <= 0)
									   {
										    units[soldier].frame = 0;
											units[enemigo].active = false;
											mapa[i][j].units[yenemigo][jl] = INVALID;
											if (yenemigo >= AHEIGHT/2) mapa[i][j].unienemigo--;
											else 
											{
												mapa[i][j].unifuera--;
												if (mapa[i][j].unifuera == 0 && mapa[i][j].unidentro <= 0) // CONQUISTADO!!
												{
													Conquista(i, j);																									
												}
											}
									   }
								   }
								}
								else 
								   units[soldier].velcont += units[soldier].velocidad;								
							}
							else // A buscar un tio cerca pa matal.lo
							{
								int yenemigo = 0;
								boolean trobat = false;
								int dist = 1;
								while (!trobat && dist < AWIDTH)
								{									
									if (jl-dist >= 0 && (yenemigo = EnemigoDelante(i,j,il,jl-dist)))
									{
										trobat = true;
										if (mapa[i][j].units[il][jl-1] == INVALID) 
										{
											units[soldier].x--;
											mapa[i][j].units[il][jl] = INVALID;				
											mapa[i][j].units[il][jl-1] = soldier;				
										}
									}
									else if (jl+dist < AWIDTH && (yenemigo = EnemigoDelante(i,j,il,jl+dist)))
									{
										trobat = true;
										if (mapa[i][j].units[il][jl+1] == INVALID) 
										{
											units[soldier].x++;
											mapa[i][j].units[il][jl] = INVALID;				
											mapa[i][j].units[il][jl+1] = soldier;				
										}
									}
									dist++;
								}
							}
						 }						
			  }
			  else //NO hay unidades fuera
			  {
				  if (mapa[i][j].unidentro == 0)				  
					  Conquista(i, j);				  
				  if ((mapa[i][j].unidentro > 0) && (mapa[i][j].construccion > NONE))
				  {
					  AtaqueConstruccion(i,j, false);
					 //ATAKE A LA CONSTRUCCION					 
				  }
			  }

		  }
		  else mapa[i][j].racestriker = NONE; 
	   }
   }
   //if (!pinyos /*&& (rand()%1000) > 997*/){ 
	   
	   //if (hora == DAYTIME) Sonido(14, SB, 3);
		//else Sonido(15, SB, 3);
	   //Sonido(11,SB,2 );
   //}

}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////                           AI                                   ////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


void NewArmy(int i, int j)
{
	int t = MIN(mapa[i][j].unidentro, minarmy);
	int k = 0;
	
	while(army[k].ocupado && k < 10)	
		k++;	
	if (k == 10) return;

	for (int tt = 0;tt< t;tt++)	
		SacaUnits(i, j, COMP);		

	army[k].mission = ECO;
	if (hlocs > clocs && gold[1] > 1000) army[k].mission = BUILD;
	else if (gold[1] > 3000) army[k].mission = KILL;
	army[k].ocupado = 1;
	army[k].hecho = 0;
	army[k].x = j;
    army[k].y = i;
	army[k].reintentos = 5;		   
}

void CRecruit()
{
   for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
   {
	  if (mapa[i][j].raceowner == COMP && 
	      mapa[i][j].construccion >= VILLAGE)
		 if (gold[1] >= RECRUITGOLD && mapa[i][j].people > 20 
		 	 && mapa[i][j].unidentro < 100)
		 {
			 if (NewUnit(mapa[i][j].raceowner, j, i, INSIDE, 100))
			 {
				gold[1] -= RECRUITGOLD;
				mapa[i][j].people--;
				mapa[i][j].unidentro++;							
			 }				
		 }	   
   }
}

void Explore(int ii, int jj)
{
   int d = 1;
   if (hora == NIGHTTIME) d = 0;
   for(int j = MAX(ii-d,0);j <= MIN(ii+d, ALTO-1); j++)
   {
	  mapa[j][jj].visible = GVISIBLE;
	  mapa[j][jj].explored = GEXPLORED;
	  mapa[j][jj].t_visible = TVISIBLE;
	  mapa[j][jj].g_construccion = mapa[j][jj].construccion;
   }
   for(int k = MAX(jj-d,0);k <= MIN(jj+d, LARGO-1); k++)			
   {
     mapa[ii][k].visible = GVISIBLE;
	 mapa[ii][k].explored = GEXPLORED;
	 mapa[ii][k].t_visible = TVISIBLE;
	 mapa[ii][k].g_construccion = mapa[ii][k].construccion;
   }

   /*
   for(int j = MAX(ii-d,0);j <= MIN(ii+d, ALTO-1); j++)
	  for(int k = MAX(jj-d,0);k <= MIN(jj+d, LARGO-1); k++)			
	  {
	     mapa[j][k].visible = GVISIBLE;
		 mapa[j][k].explored = GEXPLORED;
	  }*/
}

void ResetVisibility()
{
   for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
		mapa[i][j].visible = GNOTVISIBLE;
            	
}  

void CambioDia()
{
	if (gametime < 1) return;
	if (gametime % DAYLONG == 0)
	{
		if (hora == DAYTIME)
			hora = NIGHTTIME;
		else hora = DAYTIME;
	}
}

void CalculateVars()
{
	hlocs = 0;
	harmy = 0;
	optarmy = 10;
	clocs = 0;
	CambioDia();
	
	ResetVisibility();
   for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
   {
	   ActualizaFlechas(mapa[i][j].flechas);
	  
	   if (mapa[i][j].raceowner == HUMAN)
	   {
		  hlocs++;
		  //mapa[i][j].explored = GEXPLORED;
		  Explore(i, j);
		  //mapa[i][j].visible = GVISIBLE;
		  
		  if (mapa[i][j].racestriker == COMP) clocs++;
	      optarmy = MAX(mapa[i][j].unifuera + mapa[i][j].unidentro, optarmy);
		  harmy += mapa[i][j].unifuera + mapa[i][j].unidentro;		  
	   }
	   if (mapa[i][j].raceowner == COMP)
	   {
		  clocs++;
		  if (mapa[i][j].racestriker == HUMAN && mapa[i][j].unienemigo > 0) 
		  {			  
			  hlocs++;
			  Explore(i, j);
			  //mapa[i][j].visible = GVISIBLE;
			  //mapa[i][j].explored = GEXPLORED;
			  //mapa[i][j].g_construccion = mapa[i][j].construccion;
		  }
		 /* if (mapa[i][j].construccion >= VILLAGE)
			if (cgold >= RECRUITGOLD && mapa[i][j].people > 20 
				&& mapa[i][j].unidentro < 100)
			{
				cgold -= RECRUITGOLD;
				mapa[i][j].people--;
				mapa[i][j].unidentro++;							
				NewUnit(mapa[i][j].raceowner, j, i, INSIDE, 100);				
			}*/
	   }
   }
   /*
   for(i = 0; i < 10; i++) 
   {
	   if (i%4 == turno%4)
		  army[i].hecho = 0;
	   else
		  army[i].hecho = 1;
   }
   turno++;
   
   for(i = 0; i < 10;i++)
   {
	   if (army[i].ocupado)
	   {
		   switch(mapa[army[i].y][army[i].x].raceowner)
		   {
				case COMP:
					if (mapa[army[i].y][army[i].x].unifuera == 0)
						army[i].ocupado = 0;
					break;
				case HUMAN:
					if (mapa[army[i].y][army[i].x].unienemigo == 0)
						army[i].ocupado = 0;
					break;
		   }
		   for(int j = 0; j < 10;j++)
		   {
			if (i !=j)
			   if ((army[i].x == army[j].x) &&
				   (army[i].y == army[j].y))
					army[j].ocupado = 0;
			}
	   }       
   }*/
   // PARA VER SI HA MUERTO EL EJERCITO
   for(int i = 0; i < 10;i++)
	  if (army[i].ocupado)
	  {
		 if (mapa[army[i].y][army[i].x].raceowner != COMP ||
			 mapa[army[i].y][army[i].x].raceowner == COMP && mapa[army[i].y][army[i].x].unifuera == 0)
		 {
			army[i].reintentos--;
			if (army[i].reintentos == 0) army[i].ocupado = 0;
		 }
		 for(int j = 0; j < 10;j++)
		 {
			if (i !=j)
			   if ((army[i].x == army[j].x) &&
				   (army[i].y == army[j].y))
					army[j].ocupado = 0;
		 }
	  }

   if (CheckVictory()) 
   {
	   Sonido(12,SB,2 );
	   gameStatus = VICTORY;
		
	   if (gameMode == CAMPAIGN)
	   {
		   xmlManager *xml;

		   xml = new xmlManager();
		   xml->loadXml("map\\config.dat");		
		   int last = xml->getIntValue("last");
		   if (currentStage+1 == last) last++;
		   xml->setIntValue("last", last);

		   xml->save();

		   delete xml;
	   }
   }
   if (CheckDefeat()) {Sonido(13,SB,2 );gameStatus = DEFEAT;}
}

int Counter(int i)
{
	// ME HAN INTERCEPTADO
	int e = mapa[army[i].y][army[i].x].unienemigo;
   switch(mapa[army[i].y][army[i].x].raceowner)
   {
		case COMP:
			if (e > 0)
			{
				army[i].hecho = 1;
			    army[i].ocupado = 0;
				return 1;
			}
			break;			
		//case HUMAN:
		//	army[i].hecho = 1;	
		//	army[i].ocupado = 0;
		//	return 1;
   }
   return 0;
}


char gg1[20];
char gg2[20];
					
void Economy()
{
   for(int i = 0; i < 10;i++)
   {
	   if (army[i].ocupado && army[i].mission==ECO && !army[i].hecho)
	   {
		  if (Counter(i)) continue;
		  if (hlocs >= clocs-1 && (rand()%100 > 60))
			 army[i].mission = BUILD;
		  else
		  {
				int trobat = 0;
				int d = 1;
				while(!trobat && d<5)
				{			
					for(int j = MAX(army[i].y-d,0);j < MIN(army[i].y+d, ALTO); j++)
					for(int k = MAX(army[i].x-d,0);k < MIN(army[i].x+d, LARGO); k++)
					{
						if ((mapa[j][k].construccion >= VILLAGE && mapa[j][k].raceowner != COMP)
						|| (mapa[j][k].construccion > NONE && mapa[j][k].unidentro == 0))
						{									
							trobat = 1;
							army[i].hecho = 1;					
							army[i].ocupado = 0;
							MueveUnits(army[i].y,army[i].x, j, k, COMP);					
						}
					}
					d++;
				}
				if (!trobat && d >= 5) army[i].mission = KILL;
		  }
	   }

   }  
}


long lastarmy = 0;
void BuildArmy()
{
   for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
   if (mapa[i][j].raceowner == COMP && AI_agressiveness > 0)
   {
	   minarmy = (int)(optarmy*0.5);
	   //if (AI_agressiveness == 0) minarmy *= 2;
	   if (AI_agressiveness >= 4) minarmy /= 2;
	   if (mapa[i][j].unidentro >= MIN(minarmy,99) ||
		   gametime-lastarmy > 2000)
	   {		   
		   lastarmy = gametime;
		   NewArmy(i,j);
		   return;
	   }
   }
}

void Defend()
{
   for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
   if (mapa[i][j].raceowner == COMP)
   {
	   if (mapa[i][j].unienemigo>0 && mapa[i][j].unidentro > 0)
	   {
		   if ((mapa[i][j].unidentro + mapa[i][j].unifuera)*2 > mapa[i][j].unienemigo)
		   {
			   if (mapa[i][j].unidentro > 15)			   		
				 for (int kk=0; kk < 15;kk++) SacaUnits(i, j, COMP);			   
			   else if (mapa[i][j].unidentro > 5)			   		
			     for (int kk=0; kk < 5;kk++) SacaUnits(i, j, COMP);			   
			   else  SacaUnits(i, j, COMP);
		   }			   
	   }
   }
}



//!!!!!!
void BuildS()
{
	for(int i = 0; i < 10;i++)
    {
	   if (army[i].ocupado && army[i].mission==BUILD && !army[i].hecho)
	   {
		 if (mapa[army[i].y][army[i].x].construccion == NONE && mapa[army[i].y][army[i].x].raceowner == COMP) 
		 {
			 if (gold[1] > (FORTRESSGOLD + CAMPGOLD)*2)
			 {
				mapa[army[i].y][army[i].x].construccion = FORTRESS;
				gold[1] -= (FORTRESSGOLD + CAMPGOLD);
				mapa[army[i].y][army[i].x].integrity = INT_FORTRESS;
				mapa[army[i].y][army[i].x].maxintegrity = INT_FORTRESS;
				army[i].hecho = 1;
				army[i].ocupado = 0;
			 }
			 else if (gold[1] > CAMPGOLD*2)
			 {

				/*mapa[yactual][xactual].construccion ++;
				mapa[yactual][xactual].integrity = INT_CAMP;
				mapa[yactual][xactual].maxintegrity = INT_CAMP;
				gold -= CAMPGOLD;**/
			

				mapa[army[i].y][army[i].x].construccion = CAMP;
				gold[1] -= CAMPGOLD;
				mapa[army[i].y][army[i].x].integrity = INT_CAMP;
				mapa[army[i].y][army[i].x].maxintegrity = INT_CAMP;
				army[i].hecho = 1;
				army[i].ocupado = 0;
			 }
			 else army[i].mission = KILL;
		 }
		 else
		 {
		    //MARCA
			 int trobat = 0;
 		     int d = 1;
			  while(!trobat && d<5)
			  {			
				for(int j = MAX(army[i].y-d,0);j < MIN(army[i].y+d, ALTO); j++)
				for(int k = MAX(army[i].x-d,0);k < MIN(army[i].x+d, LARGO); k++)
				{
					if (mapa[j][k].construccion == NONE)						
					{									
						trobat = 1;						
						MueveUnits(army[i].y,army[i].x, j, k, COMP);
						army[i].y = j;
						army[i].x = k;
					}
				}
				d++;
			  }			  
			  if (d >= 5) army[i].mission = KILL;
		 }
	   }
	}
	
}

void Attack()
{
   for(int i = 0; i < 10;i++)
   {
	   if (army[i].ocupado && army[i].mission==KILL && !army[i].hecho)
	   {
		  if (Counter(i)) continue;
		  //if (hlocs >= clocs-1 && (rand()%100 > 60))
		  //	 army[i].mission = BUILD;
		  //else{
          int trobat = 0;
		  int d = 1;
		  while(!trobat && d<5)
		  {			
			for(int j = MAX(army[i].y-d,0);j < MIN(army[i].y+d, ALTO); j++)
			for(int k = MAX(army[i].x-d,0);k < MIN(army[i].x+d, LARGO); k++)
			{
				if ((mapa[j][k].construccion > 0 && mapa[j][k].raceowner != COMP)
					|| (mapa[j][k].construccion > NONE && mapa[j][k].unidentro == 0)
					|| mapa[j][k].racestriker == HUMAN)
				{									
					trobat = 1;
					army[i].hecho = 1;
					army[i].ocupado = 0;
					MueveUnits(army[i].y,army[i].x, j, k, COMP);					
				}
			}
			d++;
          }
		  if (d >= 5) army[i].mission = BUILD;
		  //}
	   }

   }  
}



/*
void Attack()
{
	for(int i = 0; i < 10;i++)
   {
	   if (army[i].ocupado && army[i].mission==KILL && !army[i].hecho)
	   {
		 if (hlocs >= clocs && (rand()%100 > 50))
			 army[i].mission = BUILD;
		 else
		 {
	 	    if (Counter(i)) return;
 		    army[i].hecho = 1;
      
			int trobat = 0;
			int d = 1;
			while(!trobat && d<6)
			{			
				for(int j = MAX(army[i].y-d,0);j < MIN(army[i].y+d, ALTO); j++)
				for(int k = MAX(army[i].x-d,0);k < MIN(army[i].x+d, LARGO); k++)
				{
					if ((mapa[j][k].construccion > NONE && mapa[j][k].raceowner != COMP)
					|| (mapa[j][k].construccion > NONE && mapa[j][k].unidentro == 0 && mapa[j][k].unifuera == 0))
					{									
						trobat = 1;
						int backy = army[i].y;
						int backx = army[i].x;
						if (j > backy) army[i].y++;
						if (j < backy) army[i].y--;
						if (k > backx) army[i].x++;
						if (k < backx) army[i].x--;
						if (j == backy && k == backx)
						{
							if (mapa[j][k].raceowner != HUMAN)
							{
								int t = mapa[j][k].unifuera;
								mapa[j][k].unifuera-=t;
								mapa[j][k].unidentro+=t;
								mapa[j][k].raceowner = COMP;
								army[i].ocupado = 0;
							}
							return;
						}
						int t = 0;
						if (mapa[backy][backx].raceowner != HUMAN)
						{
							t = mapa[backy][backx].unifuera;
							mapa[backy][backx].unifuera -=t;						
						}
						else
						{
							t = mapa[backy][backx].unienemigo;
							mapa[backy][backx].unienemigo -=t;						
						}
						if (mapa[army[i].y][army[i].x].raceowner != HUMAN)
						{
							mapa[army[i].y][army[i].x].unifuera += t;
							mapa[army[i].y][army[i].x].raceowner = COMP;
						}
						else
						{
							mapa[army[i].y][army[i].x].unienemigo+=t;
							mapa[army[i].y][army[i].x].racestriker = COMP;
						}
					}					
				}
				d++;
			}
			if (d >= 6) army[i].mission = BUILD;
		 }	
	   }

   }
   
}
*/

void Tuning()
{
	for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
   {	   
     //if (mapa[i][j].raceowner == COMP && mapa[i][j].unifuera>0)
	 //{
		//if (mapa[i][j].unienemigo == 0 && mapa[i][j].construccion > 0)
		//{
			//int t = mapa[i][j].unifuera;
			MeteUnits(i, j, COMP);
			//mapa[i][j].unifuera --;
			//mapa[i][j].unidentro ++;
		//}
	 //}
   }
   
}

//int kkk = 0;
int tthinking = 0;
void Thinking()
{
	CalculateVars();
	tthinking+=tick;
	if (tthinking > 100*dificultad)
	{
		tthinking=0;		
		CRecruit();
		Economy();
		BuildS();
		BuildArmy();		
		Defend();
		Attack();
		Tuning();
    }	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


void TTuning()
{
   for(int i = 0; i < ALTO; i++)
   for(int j = 0; j < LARGO; j++)
   {
		if ((mapa[i][j].unidentro == 0)
		&& (mapa[i][j].unifuera == 0)
		&& (mapa[i][j].unienemigo == 0))
		mapa[i][j].raceowner = NONE;
   }
}

void Grow()
{
   intervaltime+=tick;
   if (intervaltime > TIMEOUT)
   {
	   intervaltime = 0;
	   for(int i = 0; i < ALTO; i++)
		   for(int j = 0; j < LARGO; j++)
		   {
			  if (mapa[i][j].construccion > EMPTY)
			  {
			     if (mapa[i][j].unidentro > 0)
				 {
					int t = (int)sqrt((float)mapa[i][j].unidentro);
					if (mapa[i][j].unidentro + t >= MAXINSIDE[mapa[i][j].construccion])
						t = MAXINSIDE[mapa[i][j].construccion] - mapa[i][j].unidentro;
			 	    //mapa[i][j].unidentro += t;
					for (int bi = 0 ; bi < t; bi++)
					{
					   if (NewUnit(mapa[i][j].raceowner, j, i, INSIDE, 100))
							mapa[i][j].unidentro++;
					}
				 }
			  }
			  if (mapa[i][j].construccion >= VILLAGE)
			  {
					int t = (int)sqrt((float)mapa[i][j].people)/2;
					if (mapa[i][j].people + t >= MAXVILLAGERS)
						t = MAXVILLAGERS - mapa[i][j].people;
					mapa[i][j].people += t;
					switch (mapa[i][j].raceowner)
					{
						case HUMAN:
							gold[0] += mapa[i][j].people*3;
							break;
						case COMP:
							gold[1] += mapa[i][j].people*3;
							break;
					}
			  }
		   }
   }

}

UINT Gettick()
{
	time2t = timeGetTime();
	if(time2t - time1t > 10)
	{
		time1t = timeGetTime();	
		return 1;
	}	
   return 0;
}



void UpdateGame()
{
   tick = Gettick();
   if (tick){
	   db++;
	   if (db > 10) db = -5;
   }
   if (gameStatus==INGAME && !wActive)
   {
      gametime+=tick;
	  if (tick) ingameMsgTimer--;
	  ActualitzaUnits();
      Thinking();
      Battle();   
      Grow();
	  TTuning();
   }
   ActualizarFuego();

}

void DrawFire(int c, float i)
{
	switch(c)
	{
	   case CAMP:
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 248, 106, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 111, 99, DDBLT_KEYSRC, lpDDSBack,ALPHA);			
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 400, 40, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 579, 62, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 if (i <= 0.33)
		 {
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 204, 17, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 367, 04, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   		 
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 452, 10, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 75, 26, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 }
		break;
	  case FORTRESS:
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 288, 116, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 111, 116, DDBLT_KEYSRC, lpDDSBack,ALPHA);			
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 400, 38, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 584, 87, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 if (i <= 0.33)
		 {
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 204, 17, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 367, 04, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   		 
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 452, 10, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 58, 36, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 }
		break;
	case CASTLE:
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 22, 50, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 258, 122, DDBLT_KEYSRC, lpDDSBack,ALPHA);			
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 449, 119, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 548, 0, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 if (i <= 0.40)
		 {
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 407, 38, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 137, 10, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   		 
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 310, 118, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 592, 98, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 }
		 if (i <= 0.20)
		 {
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 311, 35, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,30,2+(ff2+1)*30,55, 263, 0, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   		 
			fuego.blittrans(ff1*30,33,2+(ff1+1)*30,55, 150, 0, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 26,93, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 }
		break;
	case VILLAGE:
	case CITADEL:
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 288, 116, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 111, 116, DDBLT_KEYSRC, lpDDSBack,ALPHA);			
		 fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 400, 38, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 584, 87, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 if (i <= 0.33)
		 {
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 204, 17, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 367, 04, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   		 
			fuego.blittrans(ff1*30,0,2+(ff1+1)*30,55, 452, 10, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
			fuego.blittrans(ff2*30,0,2+(ff2+1)*30,55, 58, 36, DDBLT_KEYSRC, lpDDSBack,ALPHA);	   
		 }
		break;

	}
}


void DrawAll()
{
	DrawMap();
    DrawMainScreen();  
	DrawGUI();

	
}	

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// PlayTick()
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PlayTick()
{
	if (modok) Audio();		// Sonido
	//tick = Gettick();   
    UpdateGame();
	Control();		// Responder a las ordenes
	if (wActive && wOp >= 0)
		WindowClose();
	
	DrawAll();
	if (mapa[yactual][xactual].construccion > 0 && mapa[yactual][xactual].integrity <= mapa[yactual][xactual].maxintegrity/2) 	
	{
		for(int i = 0; i < 4;i++)
		{
			Sonido(i, SB, 0 );//Sonido(i,SR, 0 );
		}

	}
	

   if (mapa[yactual][xactual].unienemigo > 0)
   {
	  int lado = rand()%3;
      if (rand()%7 == 0) Sonido(2, lado,1);
	  if (rand()%7 == 1) Sonido(3, lado,1);
	  if (rand()%7 == 2) Sonido(4, lado,1);
	  if (rand()%7 == 3) Sonido(5, lado,1);
	  if (rand()%7 == 4) Sonido(6, lado,1);
	  if (rand()%7 == 5) Sonido(7, lado,1);
	  if (rand()%7 == 6) Sonido(8, lado,1);	  
   }

	

  // Sleep(10);
//	cur.punt.blit(0,0,26,41, (int)cur.x, (int)cur.y, DDBLT_KEYSRC, lpDDSBack, 0);	         			  
	
    DrawFps();			// Calculo de fps	
}

////////////////////////////////////////////////////////////////////////
// Menu()


void MainMenu()
{
	Fondo(bg.pdds, lpDDSBack);	   
	casco.blit(0,0,casco.width,casco.height, 200, 0, DDBLT_KEYSRC, lpDDSBack,0);	   	
	wc.blit(0,0,wc.width,wc.height, 110, 40, DDBLT_KEYSRC, lpDDSBack,0);	   
	//startgame.blit(0,0,startgame.width,startgame.height, 230, 400, DDBLT_KEYSRC, lpDDSBack,0);	   
	//quit.blit(0,0,quit.width,quit.height, 340, 490, DDBLT_KEYSRC, lpDDSBack,0);	   
	//pardos.blit(0,0,pardos.width,pardos.height, 417, 260, DDBLT_KEYSRC, lpDDSBack,0);		
	fuego.blit(ff1*30,0,(ff1+1)*30,55, 300, 226, DDBLT_KEYSRC, lpDDSBack,0);	   	
	fuego.blit(ff2*30,0,(ff2+1)*30,55, 220, 229, DDBLT_KEYSRC, lpDDSBack,0);	   	
	UpdateGame();

	Control();
}

void MenuDif()
{
	Fondo(bg.pdds, lpDDSBack);	   
	casco.blit(0,0,casco.width,casco.height, 200, 0, DDBLT_KEYSRC, lpDDSBack,0);	   	
	wc.blit(0,0,wc.width,wc.height, 110, 40, DDBLT_KEYSRC, lpDDSBack,0);	   
	//pardos.blit(0,0,pardos.width,pardos.height, 417, 260, DDBLT_KEYSRC, lpDDSBack,0);	
	//dif.blit(0,0,dif.width,dif.height, 180, 330, DDBLT_KEYSRC, lpDDSBack,0);	
	fuego.blit(ff1*30,0,(ff1+1)*30,55, 300, 226, DDBLT_KEYSRC, lpDDSBack,0);	   	
	fuego.blit(ff2*30,0,(ff2+1)*30,55, 220, 229, DDBLT_KEYSRC, lpDDSBack,0);	   	
	UpdateGame();
	Control();
}



float sleepTime = 50;
int DESIREDFRAMERATE = 60;



void GameSleep()
{
	CalculaFps();
	if (realFps > DESIREDFRAMERATE*2) sleepTime += 0.2f;
	if (realFps > DESIREDFRAMERATE) sleepTime += 0.1f;
	if (realFps < DESIREDFRAMERATE) sleepTime -= 0.1f;
	if (realFps < DESIREDFRAMERATE/2) sleepTime -= 0.2f;
	if (sleepTime > 1) Sleep((long)sleepTime);
}


////////////////////////////////////////////////////////////////////////
// updateFrame()
////////////////////////////////////////////////////////////////////////


void updateFrame()
{
	HRESULT ddrval;    
	
    switch(gameStatus)
	{
		case STARTUP:
			InitMainMenu();
			break;
		case INGAME: 
			PlayTick();break;
		case MENU1: 
			MainMenu();break;
		case SCENARIO:
		case MENU2:
			MenuDif();break;
		case VICTORY:
			PlayTick();
			victory.blit(0,0,victory.width,victory.height, 70, 0, DDBLT_KEYSRC, lpDDSBack,0);break;
		case DEFEAT:
			PlayTick();
			defeat.blit(0,0,defeat.width,defeat.height, 200, 0, DDBLT_KEYSRC, lpDDSBack,0);break;
		case BRIEFING:
			Fondo(briefingBackground.pdds, lpDDSBack);
			UpdateGame();
			Control();
			break;
		case ENDING:
			Ending();
			break;
        case CREDITS: 
			Credits();break;
		case PAUSE: 
		case OBJECTIVES:
			PauseMenu();break;
		
		default: break;
	}

	WindowDraw();
	
	if (overBuilding)
	{
		if (overVillage)
			cur.puntOverV.blit(0,0,cur.puntOverV.width, cur.puntOverV.height, (int)cur.x, (int)cur.y, DDBLT_KEYSRC, lpDDSBack, 0);
		else
			cur.puntOverB.blit(0,0,cur.puntOverB.width, cur.puntOverB.height, (int)cur.x, (int)cur.y, DDBLT_KEYSRC, lpDDSBack, 0);	         			  	
	}
	else if (overGround)
		cur.puntOverG.blit(0,0,cur.puntOverG.width, cur.puntOverG.height, (int)cur.x, (int)cur.y, DDBLT_KEYSRC, lpDDSBack, 0);	         			  	
	else
		cur.punt.blit(0,0,26,41, (int)cur.x, (int)cur.y, DDBLT_KEYSRC, lpDDSBack, 0);
	ddrval = lpDDSPrimary->Flip(NULL, DDFLIP_WAIT );		// Flip!	
	GameSleep();	
} 

////////////////////////////////////////////////////////////////////////
// handler de pulsacion de tecla
////////////////////////////////////////////////////////////////////////
void OnKeyDown(int key, HWND hWnd)
{
	if (mousetime > 0) return;
	switch( key )
        {
        case VK_ESCAPE:
			switch(gameStatus)
			{
				case MENU1:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;
				case INGAME:
					InitPauseMenu();
					break;
				case MENU2:
				case CREDITS:
				case SCENARIO:
					InitMainMenu();
					break;
				case OBJECTIVES:
					InitPauseMenu();
					break;
			}
            break;
        }
}

////////////////////////////////////////////////////////////////////////
// WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
////////////////////////////////////////////////////////////////////////
long FAR PASCAL WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	switch( message )
	{
		case WM_ACTIVATEAPP:
			bActive = wParam;
			if ((bActive) && (kk>0))
			{
				RestoreSurfaces(); 
			}					
			else kk++;			
			break;
		case WM_SETCURSOR:
			SetCursor(NULL);
			return TRUE;
		case WM_CREATE:
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam,hWnd);
			break;
		case WM_DESTROY:
			FiniAudio();
			lpDD->RestoreDisplayMode();
			EndMouse();
			finiObjects();
			PostQuitMessage( 0 );
			break;		
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
} 

////////////////////////////////////////////////////////////////////////
// En caso de error de la inicializacion DDraw
////////////////////////////////////////////////////////////////////////
BOOL initFail( HWND hwnd )
{
	finiObjects();
	MessageBox( hwnd, "DirectDraw Init FAILED", TITLE, MB_OK );
	DestroyWindow( hwnd );
	return FALSE;
} 

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////// SECUENCIA DE INICIO DE DIRECT DRAW /////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// doInit - Inicializa la aplicacion, la ventana y DDraw
// no se deberia tocar nada, hasta donde dice "y aqui van los datos de
// la app"
////////////////////////////////////////////////////////////////////////

static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
	WNDCLASS            wc;
	DDSURFACEDESC2       ddsd;
	DDSCAPS2             ddscaps;
	HRESULT             ddrval;


	// negocia la window class con el API de Win32
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( hInstance, "res/dia2.ico" );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuName = NAME;
	wc.lpszClassName = NAME;
	RegisterClass( &wc );
	
	//crea la ventana
	hwnd=CreateWindow(NAME,NAME,WS_CLIPCHILDREN | WS_CLIPSIBLINGS |WS_POPUP| WS_VISIBLE,
				0,0,SCREENX,SCREENY,NULL,NULL,hInstance,NULL);
	if( !hwnd )
	{
		return FALSE;
	}

	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );
	// crear el objeto DDraw principal, el papa de todos los demas
	ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
	if( ddrval != DD_OK )
	{
		return initFail(hwnd);
	}
	ddrval = lpDD->QueryInterface(IID_IDirectDraw4,(LPVOID *)&lpDD4);
	if( ddrval != DD_OK )
	{
		return initFail(hwnd);
	}

	// imponer el modo cooperativo.
	//ddrval = lpDD4->SetCooperativeLevel( hwnd, DDSCL_NORMAL | DDSCL_ALLOWREBOOT | DDSCL_NOWINDOWCHANGES | DDSCL_EXCLUSIVE);
	ddrval = lpDD4->SetCooperativeLevel( hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | DDSCL_ALLOWREBOOT);
	if( ddrval != DD_OK ) 
	{
		return initFail(hwnd);
	}
	// Poner el modo grafico que queramos
	ddrval = lpDD4->SetDisplayMode(SCREENX,SCREENY,COLOR,0,0);
	if( ddrval != DD_OK )
	{
		return initFail(hwnd);
	}
	// Creacion del doble buffer
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	ddrval = lpDD4->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
	if( ddrval != DD_OK )
	{
		return initFail(hwnd);
	}	
	//Pillamos el puntero al backbuffer 
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	ddrval = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);
	
	if( ddrval != DD_OK )
	{
		return initFail(hwnd);
	}


	// creacion de un clipper
	ddrval = lpDD->CreateClipper((DWORD)0,&lpDDClipper,NULL);
	RECT rc;
	SetRect(&rc, 0, 0, SCREENX, SCREENY);
	CLIPLIST ClipList;
	ClipList.hdr.dwSize = sizeof(RGNDATAHEADER);
	ClipList.hdr.iType = RDH_RECTANGLES;
	ClipList.hdr.nCount = 1;
	ClipList.hdr.nRgnSize = 0;
	memcpy(&ClipList.hdr.rcBound, &rc, sizeof(RECT));
	memcpy(&ClipList.rgndata, &rc, sizeof(RECT));
	ddrval = lpDDClipper->SetClipList((LPRGNDATA)&ClipList,0);
	ddrval = lpDDSBack->SetClipper(lpDDClipper);

	// Y ya esta. Aqui van los datos de la app.

	
	//////////////Mouse
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID *)&lpdi, NULL); 
	char buffer[128];
	//creamos el directinput
	if (FAILED(hr))
	{
		sprintf(buffer, "%s", "Ha fallat");
	}
	else
		sprintf(buffer, "%s", "Ha funcionat");

	// obtenemos acceso al mouse mediante directimput
	hr = lpdi->CreateDevice(GUID_SysMouse, &g_pMouse, NULL);
	
	if (FAILED(hr)) 
	{
	    sprintf(buffer, "%s", "CreateDevice(SysMouse)");    
		return TRUE;
	}
	// el formato con el que queremos trabajar
	hr = g_pMouse->SetDataFormat(&c_dfDIMouse);
	
	if (FAILED(hr)) 
	{
	    sprintf(buffer, "%s", "SetDataFormat(SysMouse, dfDIMouse)");    
		return TRUE;
	}
	//Mouse en modo exclusivo
	hr = g_pMouse->SetCooperativeLevel(hwnd,
	               DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	 
	if (FAILED(hr)) {
	    sprintf(buffer, "%s", "SetCooperativeLevel(SysMouse)");
	    return TRUE;
	}
	 
	g_hevtMouse = CreateEvent(0, 0, 0, 0);
	
	if (g_hevtMouse == NULL) {
	    sprintf(buffer, "%s", "CreateEvent");
	    return TRUE;
	}
	 
	hr = g_pMouse->SetEventNotification(g_hevtMouse);
	 
	if (FAILED(hr)) {
	    sprintf(buffer, "%s", "SetEventNotification(SysMouse)");
	    return TRUE;
	}
	 
	g_pMouse->Acquire(); 
	
	Inicializar();

	return TRUE;
} 





////////////////////////////////////////////////////////////////////////
// WinMain
////////////////////////////////////////////////////////////////////////

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{
	MSG	msg;
	lpCmdLine = lpCmdLine;
	hPrevInstance = hPrevInstance;	

	if( !doInit( hInstance, nCmdShow ) )
	{
		return FALSE;
	}

	while( 1 )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( !GetMessage( &msg, NULL, 0, 0 ) ) return msg.wParam;
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else if( bActive )
		{
			updateFrame();
		}
		else
		{
			// no gastamos CPU si no somos ventana activa.
			WaitMessage();
		}
	}
	lpDD->RestoreDisplayMode();
}




void SelectUnits(int i, int j)
{
	if (oriy == -1) 
		 if (((mapa[i][j].raceowner==HUMAN) && (mapa[i][j].unifuera > 0))
 		 || ((mapa[i][j].racestriker==HUMAN) && (mapa[i][j].unienemigo > 0)))
		 {
			oriy = i;
			orix = j;
		 }
}

void Repair(int i, int j, int race)
{

	if (gold[race-1] >= REPAIRGOLD 
		&& mapa[i][j].construccion >= CAMP
		&& mapa[i][j].unidentro > 0
		&& mapa[i][j].raceowner == race
		&& mapa[i][j].integrity < mapa[i][j].maxintegrity)					
		{
			gold[race-1] -= REPAIRGOLD;
			mapa[i][j].integrity+=10;					
		}
}

void Recruit(int i, int j, int race)
{
	if (gold[race-1] >= RECRUITGOLD
	   && mapa[i][j].construccion>=VILLAGE
	   && mapa[i][j].people > 0
	   && mapa[i][j].unidentro < 100
	   && mapa[i][j].raceowner == race) 
	   {
		   if (NewUnit(mapa[i][j].raceowner, xactual, yactual, INSIDE, 100))
		   {
				mapa[i][j].people--;
				mapa[i][j].unidentro++;
			
				gold[race-1] -= RECRUITGOLD;
		   }
	   }
}


///////////////////////////////////////////////////////////////////////////////////
int wInix, wIniy;
int wWidth, wHeight;
int wR, wG, wB;
char **stringBuffer = NULL;
int iLineCounter = 0;
#define TEXTBORDERX 10
#define TEXTBORDERY 10
#define LINEHEIGHT 16
bool selectable = false;
int selectedLine = -1;


void WindowInit(bool _select, int _inix, int _iniy, int _width, int _height, int _r, int _g, int _b)
{
	if (wActive) WindowClose();
	wInix = _inix;
	wIniy = _iniy;
	wWidth = _width;
	wHeight = _height;
	wR = _r;
	wG = _g;
	wB = _b;
	wActive = true;
	selectable = _select;
	selectedLine = -1;
	wOp = -1;

	stringBuffer = new char*[30];

}


void WindowAddLine(const char *in)
{
	stringBuffer[iLineCounter] = new char[strlen(in)];
	strcpy(stringBuffer[iLineCounter], in);
	iLineCounter++;
}


int WindowUpdate()
{
	int x, y;

	if (!wActive) return -1;
	selectedLine = -1;
	wOp = -1;
	x = wInix + TEXTBORDERX;
	y = wIniy + TEXTBORDERY;

	for(int i = 0;i < iLineCounter;i++, y += LINEHEIGHT)
	{
		//if (i < 1) continue;
		bool skip = false;
		int begin = 0;
		int numLines = 1;

		int yy = y;
		while (begin < strlen(stringBuffer[i]))
		{		
			int len = strlen(stringBuffer[i])-begin;
		
			int k = 0;
			while (getGFXStringWidth(stringBuffer[i], begin, len) >= wWidth-TEXTBORDERX)			
				len--;									
			//check de return
			int m;
			for(m = 1; m < len;m++)
				if (stringBuffer[i][begin+m-1] == '\n') {skip = true;break;}
			if (m < len) len = m;
			


			begin += len;
			if (skip == true) {begin += 2;skip = false;}
			if (begin < strlen(stringBuffer[i])) {y += LINEHEIGHT;numLines++;}
		}

		if (Dentro(0, 0, wWidth, numLines*LINEHEIGHT, x, yy)) 
		{
			selectedLine = i;
		}

	}
	if (leftMouseButton && selectedLine < iLineCounter) wOp = selectedLine-1;
		
	return wOp;	
}


void WindowDraw()
{
	if (!wActive) return;
	int x, y;
	
	FillRectangle(lpDDSBack,wInix, wIniy, wWidth, wHeight, wR, wG, wB);
	//BORDER
	for(x = wInix-marco1.width;x < wInix+wWidth+marco1.width;x += marco1.width)
	{
		marco1.blit(0,0,marco1.width,marco1.height, x, wIniy-marco1.height, 0, lpDDSBack,0);	   
		marco1.blit(0,0,marco1.width,marco1.height, x, wIniy+wHeight, 0, lpDDSBack,0);	   
	}
	for(y = wIniy-marco2.height;y < wIniy+wHeight;y += marco2.height)
	{
		marco2.blit(0,0,marco2.width,marco2.height, wInix-marco2.width, y, 0, lpDDSBack,0);	   
		marco2.blit(0,0,marco2.width,marco2.height, wInix+wWidth, y, 0, lpDDSBack,0);	   
	}
	//CORNERS
	marco3.blit(0,0,marco3.width,marco3.height, wInix-marco3.width, wIniy-marco3.height, 0, lpDDSBack,0);	   
	marco3.blit(0,0,marco3.width,marco3.height, wInix+wWidth, wIniy-marco3.height, 0, lpDDSBack,0);	   
	marco3.blit(0,0,marco3.width,marco3.height, wInix-marco3.width, wIniy+wHeight, 0, lpDDSBack,0);	   
	marco3.blit(0,0,marco3.width,marco3.height, wInix+wWidth, wIniy+wHeight, 0, lpDDSBack,0);	   
	
	//TEXTO
	x = wInix;
	y = wIniy + TEXTBORDERY;
	for(int i = 0;i < iLineCounter;i++, y += LINEHEIGHT)
	{		
		int begin = 0;
		bool skip = false;

		while (begin < strlen(stringBuffer[i]))
		{
			skip = false;
			int len = strlen(stringBuffer[i])-begin;
			int k = 0;
			while (getGFXStringWidth(stringBuffer[i], begin, len) >= wWidth-TEXTBORDERX*2)			
				len--;						
			//check de return
			int m;
			for(m = 1; m < len;m++)
				if (stringBuffer[i][begin+m-1] == '\n') {skip = true;break;}
			if (m < len) len = m;
			
			char *s = new char[len+1];
			char *sb = &stringBuffer[i][begin];
			strncpy(s, sb, len);
			s[len] = '\0';
			int cont = 0;
			if (begin != 0) cont = 1;
			if (selectable)
			{
				int r,g,b;
				r = 64;g = 43;b = 55;
				if (i == 0) {r = 51; g = 58; b = 48;}
				else if (i == selectedLine) {r = 161; g = 128; b = 178;}				
				FillRectangle(lpDDSBack,x+2, y-2-cont+2, wWidth-4, LINEHEIGHT-1+cont, r, g, b);
			}
			PrintGFX(mfont, x + TEXTBORDERX, y, s, lpDDSBack);

			delete s;

			begin += len;
			if (skip) begin+=2;
			if (begin < strlen(stringBuffer[i])) y += LINEHEIGHT;
		}
		
	}
}

void WindowClose()
{
	if (!wActive) return;
	wActive = false;
	
	for(int i = 0;i < iLineCounter;i++)
	{
		//delete [] stringBuffer[i];
	}

	iLineCounter = 0;
	delete [] stringBuffer;
}


void InitCredits()
{

	WindowInit(true ,225, 200, 360, 342-80, 0, 0, 0);
	WindowAddLine("Warcrushers 0.9a\n \n\n  Design & Code: Carlos Peris\n \n\n  Music: Juan Barba\n \n\n  English Translation: Alfred Ferrer\n \n\n  Thanks to:\n   Carolina López \n\n  Lorenzo Ibarria \n\n  Raúl Durán\n \n\n\n\nhttp://kung-foo.dhs.org/zener\n\n\n\n ");
	WindowAddLine("Back");

	gameStatus = CREDITS;
}


void Credits()
{
	Fondo(bg.pdds, lpDDSBack);	   
	//casco.blit(0,0,casco.width,casco.height, 200, 0, DDBLT_KEYSRC, lpDDSBack,0);	   	
	wc.blit(0,0,wc.width,wc.height, 110, 40, DDBLT_KEYSRC, lpDDSBack,0);	   
	//fuego.blit(ff1*30,0,(ff1+1)*30,55, 300, 226, DDBLT_KEYSRC, lpDDSBack,0);	   	
	//fuego.blit(ff2*30,0,(ff2+1)*30,55, 220, 229, DDBLT_KEYSRC, lpDDSBack,0);	   	
	UpdateGame();

	Control();
}

void InitMainMenu()
{
	xmlManager *xml;
	xml = new xmlManager();
	xml->loadXml("map\\config.dat");		

	
    hintsActive = xml->getBoolValue("hints");
    musicVolume = xml->getIntValue("musicVolume");
	setMusicVolume(musicVolume);
	soundVolume = xml->getIntValue("soundVolume");
	setSoundVolume(soundVolume);
	delete xml;

							
	WindowInit(true ,325, 400, 155, 142, 0, 0, 0);
	WindowAddLine("Warcrushers 0.9a");
	WindowAddLine("Campaign");
	WindowAddLine("Scenario");
	/*if (hintsActive)
		WindowAddLine("Hints On");
	else
		WindowAddLine("Hints Off");*/
	switch(musicVolume)
	{
		case 0: WindowAddLine("Music OFF"); break;
		case 1: WindowAddLine("Music 25%");break;
		case 2: WindowAddLine("Music 50%");break;
		case 3: WindowAddLine("Music 75%");break;
		case 4: WindowAddLine("Music 100%");break;
	}
	switch(soundVolume)
	{
		case 0: WindowAddLine("Sound OFF"); break;
		case 1: WindowAddLine("Sound 25%");break;
		case 2: WindowAddLine("Sound 50%");break;
		case 3: WindowAddLine("Sound 75%");break;
		case 4: WindowAddLine("Sound 100%");break;
	}
	WindowAddLine("Credits");
	WindowAddLine("Exit");

	gameStatus = MENU1;
}


void InitScenarioMenu()
{
	gameStatus = SCENARIO;
 
	WindowInit(true ,325, 400, 155, 142, 0, 0, 0);

	WindowAddLine("Select Scenario");
	
	char res[1024];
	char *name_part;
	char file[1024];

	for(int i = 1; i < 100;i++)
	{
		res[0] = '\0';
		
		sprintf(file, "scenario%d\0", i);

		SearchPathA("scenario\\", file, ".map", 1024, res, &name_part);

		if (res[0] != '\0') WindowAddLine(name_part);
	}
}


void InitPauseMenu()
{
	WindowInit(true ,250, 130, 155, 142, 0, 0, 0);
	WindowAddLine("GAME PAUSED");
	WindowAddLine("Resume");
	WindowAddLine("Mission Objectives");
	/*if (hintsActive)
		WindowAddLine("Hints On");
	else
		WindowAddLine("Hints Off");*/
	switch(musicVolume)
	{
		case 0: WindowAddLine("Music OFF"); break;
		case 1: WindowAddLine("Music 25%");break;
		case 2: WindowAddLine("Music 50%");break;
		case 3: WindowAddLine("Music 75%");break;
		case 4: WindowAddLine("Music 100%");break;
	}
	switch(soundVolume)
	{
		case 0: WindowAddLine("Sound OFF"); break;
		case 1: WindowAddLine("Sound 25%");break;
		case 2: WindowAddLine("Sound 50%");break;
		case 3: WindowAddLine("Sound 75%");break;
		case 4: WindowAddLine("Sound 100%");break;
	}
    WindowAddLine("Quit");

	gameStatus = PAUSE;
}


void PauseMenu()
{
	DrawAll();
	//casco.blit(0,0,casco.width,casco.height, 150, 0, DDBLT_KEYSRC, lpDDSBack,0);

	UpdateGame();

	Control();
}


void InitMenuDif()
{
	gameStatus = MENU2;				

	gameMode = CAMPAIGN;

	xmlManager *xml;
	xml = new xmlManager();
	xml->loadXml("map\\config.dat");		
	int last = xml->getIntValue("last");
	delete xml;

	xml = new xmlManager();
	xml->loadXml("map\\campaigns.dat");		

	WindowInit(true ,400-150, 400, 300, 160, 0, 0, 0);
	WindowAddLine("Select mission.");



	int stageCount = xml->getTagCount("stage");
	if (last > 0 && last < stageCount) stageCount = last;

	for(int i = 0; i < stageCount;i++) {
		WindowAddLine(xml->getStrValue(xml->getNodeByName("stage", i+1), "name", 1));
	}

	delete xml;						

}

void InitObjectivesScreen()
{
	char *s = new char[256];
	

	gameStatus = OBJECTIVES;
	WindowInit(true ,300-140, 130, 300, 100, 0, 0, 0);
	WindowAddLine("MISSION OBJECTIVES");

	switch(objectiveCom)
	{
		case OBJ_KILL:
			WindowAddLine(" - Kill all enemy");
			break;

		case OBJ_BUILD:
			char *buildString;
			switch(objectivePar2)
			{
				case CAMP:
					sprintf(buildString, "camp/s\0");
					break;

				case FORTRESS:
					sprintf(buildString, "fortress/es\0");
					break;

				case CASTLE:
					sprintf(buildString, "castle/s\0");
					break;
			}
			sprintf(s, " - Build %d more %s\0", objectivePar1, buildString);
			WindowAddLine(s);		
			if (!objectiveEndsMission) WindowAddLine(" - Kill all enemy");
			break;

		case OBJ_RECRUIT:
			sprintf(s, " - Recruit %d more soldiers\0", objectivePar1 - currentUnits);
			WindowAddLine(s);
			break;

		case OBJ_CONQUER:
			WindowAddLine(" - Conquer region");
			if (!objectiveEndsMission) WindowAddLine(" - Kill all enemy");
			break;

		case OBJ_DONTLOSE:
			WindowAddLine(" - Don't lose region");
			if (!objectiveEndsMission) WindowAddLine(" - Kill all enemy");
			break;
	}
	WindowAddLine("Back");
}


void ScenarioMenuUpdate()
{
	char filename[256];

	if (!leftMouseButton) return;
				
	LimpiarTeclado();
	if (wOp < 0) return;
	mousetime = TMOUSE*2;					

	sprintf(filename, "scenario/%s", stringBuffer[wOp+1]);

	

	InitScenarioMap(filename);

	gameStatus = INGAME;
	WindowClose();
}


void CampaignMenuUpdate()
{
	if (!leftMouseButton) return;
				
	LimpiarTeclado();
	if (wOp < 0) return;
	mousetime = TMOUSE*2;					

	gameStatus = BRIEFING;						
	InitMap(wOp);
	WindowClose();
	// DESCRIPCION DE MISION
	WindowInit(true ,20, 20, 600, 360, 40, 30, 0);
	xmlManager *xml;
	xml = new xmlManager();
	xml->loadXml("map\\campaigns.dat");		
	briefingBackground.load(xml->getStrValue(xml->getNodeByName("stage", currentStage+1), "background", 1),SISTEMA, lpDD4);
	WindowAddLine(xml->getStrValue(xml->getNodeByName("stage", currentStage+1), "brief", 1));
	WindowAddLine("Press to continue");						
	delete xml;
}



void PauseMenuUpdate()
{
	if (!leftMouseButton) return;
	LimpiarTeclado();
	if (wOp < 0) return;
	mousetime = TMOUSE*2;					
	bool refreshScreen = false;

	switch(wOp)
	{
		case 0: WindowClose();
			gameStatus = INGAME;
			break;
		/*case 1: //ZNRMARK
			//refreshScreen = true;
			break;*/
		case 1:
			InitObjectivesScreen();
			break;
		case 2: musicVolume = (++musicVolume)%5;
			refreshScreen = true;
			setMusicVolume(musicVolume);
			break;
		case 3: 
			soundVolume = (++soundVolume)%5;
			refreshScreen = true;
			setSoundVolume(soundVolume);
			break;
		case 4:InitMainMenu();
			break;
	}

	if (refreshScreen){
		xmlManager *xml;
		xml = new xmlManager();
		xml->loadXml("map\\config.dat");		

		xml->setBoolValue("hints", hintsActive);
		xml->setIntValue("musicVolume", musicVolume);
		xml->setIntValue("soundVolume", soundVolume);	
		
		xml->save();

		delete xml;

		InitPauseMenu();
	}

}


void MainMenuUpdate()
{
	if (!leftMouseButton) return;
	LimpiarTeclado();
	if (wOp < 0) return;
	mousetime = TMOUSE*2;					
	
	bool refreshScreen = false;

	switch(wOp)
	{
		case 0: InitMenuDif();
			break;
		case 1: InitScenarioMenu();
			break;
		/*case 2: hintsActive = !hintsActive;
			refreshScreen = true;
			break;*/
		case 2: musicVolume = (++musicVolume)%5;
			refreshScreen = true;
			setMusicVolume(musicVolume);
			break;
		case 3: 
			soundVolume = (++soundVolume)%5;
			refreshScreen = true;
			setSoundVolume(soundVolume);
			break;
		case 4: InitCredits();
			break;
		case 5: PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
	}

	if (refreshScreen){
		xmlManager *xml;
		xml = new xmlManager();
		xml->loadXml("map\\config.dat");		

		xml->setBoolValue("hints", hintsActive);
		xml->setIntValue("musicVolume", musicVolume);
		xml->setIntValue("soundVolume", soundVolume);	
		
		xml->save();

		delete xml;

		InitMainMenu();
	}
}

int endingTicks;

void InitEnding()
{
	gameStatus = ENDING;
	WindowInit(true ,20, 20, 300, 180, 40, 30, 0);
	xmlManager *xml;
	xml = new xmlManager();
	xml->loadXml("map\\campaigns.dat");		
	briefingBackground.load(xml->getStrValue(xml->getNodeByName("ending"), "background", 1),SISTEMA, lpDD4);
	WindowAddLine(xml->getStrValue("endingtext"));
	WindowAddLine("Press to continue");						
	delete xml;

	endingTicks = 0;
}


void Ending()
{
	if (tick) endingTicks++;
	if (endingTicks > 990 && endingTicks%500 == 499)
	{
		xmlManager *xml;
		xml = new xmlManager();
		xml->loadXml("map\\campaigns.dat");		
		briefingBackground.load(xml->getStrValue(xml->getNodeByName("stage", ((endingTicks/500)%xml->getTagCount("stage"))+1 ), "background", 1),SISTEMA, lpDD4);
		delete xml;

	}

	Fondo(briefingBackground.pdds, lpDDSBack);
	UpdateGame();
	Control();		
}