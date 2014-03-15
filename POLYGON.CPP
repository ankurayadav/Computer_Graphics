#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
int initmouse()
{
	union REGS in,out;
	in.x.ax=0x0000;
	int86(0x33,&in,&out);
	if(out.x.ax==0xffff)
	return 1;
	else
	return 0;
}
void showmouse()
{       union REGS in,out;
	in.x.ax=0x0001;
	int86(0x33,&in,&out);

}
void getmouse(int *x,int*y)
{
	union REGS in,out;
	in.x.ax=0x0003;
	while(1)
	{
	int86(0x33,&in,&out);
	if(out.x.bx & 0x0001 == 0x0001)
	   break;

	}
	*x=out.x.cx;
	*y=out.x.dx;
	delay(1000);
}
void bres(int,int, int, int);
void fill(int xi,int yi,int outcolor, int fillcolor);
int main()
{    	int xi,yi,xo,yo,n;
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\tc\\BGI");
      //	int xmax=getmaxx();
      //	int ymax=getmaxy();
	printf("How many sides in your polygon :");
	scanf("%d",&n);
	initmouse();
	showmouse();
	getmouse(&xi,&yi);
	int x1=xi, y1=yi ;
     //	circle(xi,yi,10);
	printf("(%d,%d)",xi,yi);
	for(int i=0; i<n-1; i++)
     {
	getmouse(&xo,&yo);
     //	circle(xo,yo,10);
     //	line(xi,yi,xo,yo);
	printf("-->(%d,%d)",xo,yo);
	bres(xi,yi,xo,yo);
	xi=xo;
	yi=yo;
     }

	bres(xi,yi,x1,y1);
	int fx, fy ;

	getmouse(&fx,&fy);

	fill(fx,fy,11,4);

	getch();
	closegraph();
	return 0;
}

void fill(int xi,int yi,int outcolor, int fillcolor)
{
	if(getpixel(xi,yi)!=outcolor&&getpixel(xi,yi)!=fillcolor)
	{	putpixel(xi,yi,fillcolor);
		fill(xi+1,yi,outcolor,fillcolor);
		fill(xi-1,yi,outcolor,fillcolor);
		fill(xi,yi+1,outcolor,fillcolor);
		fill(xi,yi-1,outcolor,fillcolor);
	       // fill(xi+1,yi+1,outcolor,fillcolor);
	}
}


void bres(int xi,int yi,int xo, int yo)
{	int dx = abs(xo-xi) ;  int t;
	int dy = abs(yo-yi) ;
	int p = 2*dy - dx;
	int dy2= 2*dy ;
	int dx2=2*dx;
	int dxy2=2*(dx-dy);
	int dyx2 = 2*(dy-dx);
	int m = (xo-xi)*(yo-yi) ;
if(m>0)
{
	if(dx>dy)
	{
	if(xi>xo)
	{	t=xi;
		xi=xo;
		xo=t;
		t=yi;
		yi=yo;
		yo=t;
	}
	putpixel(xi,yi,11);
	for(int i=xi+1; i<=xo;i++)
	{	if(p<0)
		{ p+=dy2;
		}
		else
		{ yi++ ;
		  p+=dyx2;
		}
		putpixel(i,yi,11);
	}
	}
	else {
		if(yi>yo)
		{	t=xi;
			xi=xo;
			xo=t;
			t=yi;
			yi=yo;
			yo=t;
		}
		putpixel(xi,yi,11);
		for(int i=yi+1; i<=yo;i++)
		{	if(p<0)
			{      // xi++;
				p+=dx2;
			}
			else
			{       xi++;
				p+=dxy2;
			}
			putpixel(xi,i,11);
		}
	}
}
else
{
	if(dx>dy)
	{
	if(xi>xo)
	{	t=xi;
		xi=xo;
		xo=t;
		t=yi;
		yi=yo;
		yo=t;
	}
	putpixel(xi,yi,11);
	for(int i=xi+1; i<=xo;i++)
	{	if(p<0)
		{ p+=dy2;
		}
		else
		{ yi-- ;
		  p+=dyx2;
		}
		putpixel(i,yi,11);
	}
	}
	else {
		if(yi>yo)
		{	t=xi;
			xi=xo;
			xo=t;
			t=yi;
			yi=yo;
			yo=t;
		}
		putpixel(xi,yi,11);
		for(int i=yi+1; i<=yo;i++)
		{	if(p<0)
			{      // xi++;
				p+=dx2;
			}
			else
			{       xi--;
				p+=dxy2;
			}
			putpixel(xi,i,11);
		}
	}

}

}