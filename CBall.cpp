#include "CBall.h"

CBall::CBall(double  x,  double  y,  double  vx,  double  vy,  double  r)
{
 
	hBrush  =  CreateSolidBrush(RGB(0,  255,  0));

	this->x = x; 
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->r = r;
	this->prev_ticks  =  GetTickCount();
}

void CBall::UpdateHBrush1()
{
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
}

void CBall::UpdateHBrush2()
{
	hBrush = CreateSolidBrush(RGB(0, 255, 0));
}

void CBall::UpdateHBrush3()
{
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
}

CBall::~CBall()
{
	DeleteObject(hBrush);
}

void  CBall::Draw(HDC  dc)
{
	HBRUSH hOldBrush;

	hOldBrush = SelectBrush(dc, hBrush);
	Ellipse(dc, (x - r), (y - r), (x + r), (y + r));

	SelectBrush(dc,  hOldBrush);
}

void  CBall::Move(DWORD  ticks)
{
	double s_delta = ((double)(ticks - this->prev_ticks)) / 1000.0;

	if ((this->x >= (bounds.right - r)) && (this->vx > 0)) 
		this->vx = -(this->vx);
	if ((this->x <= r) && (this->vx < 0)) 
		this->vx = -(this->vx);

	if ((this->y >= (bounds.bottom - r)) && (this->vy > 0)) 
		this->vy = -(this->vy);
	if ((this->y <= r) && (this->vy < 0)) 
		this->vy = -(this->vy);
	if (((this->x + r) >= limit->GetMinX()) && ((this->x - r) <= limit->GetMaxX()))
	{
		if (this->vy > 0)
		{
			if (((limit->GetY() - this->y) < this->r) && ((limit->GetY() - this->y) > 0))
				this->vy = -(this->vy);
		}
		else
		{
			if  (((this->y  -  limit->GetY())  <  this->r)  &&  ((this->y  - limit->GetY()) > 0))
				this->vy = -(this->vy);
		}
	}

	this->prev_ticks = ticks; 
	double dx = vx  * s_delta;
	double  dy  =  vy  * s_delta;

	this->x  += dx;
	this->y  += dy;

}

void  CBall::SetBounds(RECT  bnds)
{
	this->bounds  =  bnds;
}

void  CBall::SetHLimiter(CHLimiter  *l)
{
	this->limit = l;
}