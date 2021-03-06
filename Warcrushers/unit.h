// unit.h: interface for the unit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIT_H__BF0ABD04_F315_4865_BBBB_3B034E462CF7__INCLUDED_)
#define AFX_UNIT_H__BF0ABD04_F315_4865_BBBB_3B034E462CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define INSIDE 0
#define OUTSIDE 1

#define MAXUNITS 5000

class unit  
{
public:
	unit();
	virtual ~unit();
	bool active;
	int bando;
	int energy;
	int maxenergy;
	int action;
	int frame;
	int location;
	int locx;
	int locy;
	int destx;
	int desty;
	int x,y;
	int ataque;
    int critico;
	int armadura;
	int velocidad;
	int velcont;
	float frameFractionY;
	int xp;
	int hit;
	int hitTime;
   	//void load(char *,int,IDirectDraw4 *);
	
};

#endif // !defined(AFX_UNIT_H__BF0ABD04_F315_4865_BBBB_3B034E462CF7__INCLUDED_)


   