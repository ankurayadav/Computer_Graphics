#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
struct pos{
	int x;
	int y;
	int d;
	float m;
}point[50],p[50] ;

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
	int xmax=getmaxx();
	int ymax=getmaxy();
	printf("How many sides in your polygon :");
	scanf("%d",&n);
	initmouse();
	showmouse();
	getmouse(&xi,&yi);
	int count=0;
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
	p[count].x=xi;p[count].y=yi;
	if(xi<xo)
	{ point[count].x=xi;
	}
	else
	{ point[count].x=xo;
	}
	if(yi>yo)
	{ point[count].y=yi;
	}
	else
	{ point[count].y=yo;
	}
	if(xo=xi)
	{ point[count++].d=1;
	}
	else
	{point[count].d=0;
	point[count++].m= (yo-yi)/(xo-xi);
	}
	xi=xo;
	yi=yo;
     }
	bres(xi,yi,x1,y1);
	if(xi<x1)
	{ point[count].x=xi;
	}
	else
	{ point[count].x=x1;
	}
	if(yi>y1)
	{ point[count].y=yi;
	}
	else
	{ point[count].y=y1;
	}
	if(x1=xi)
	{ point[count++].d=1;
	}
	else
	{point[count].d=0;
	point[count++].m= (y1-yi)/(x1-xi);
	}
	int ymax=0 ,m=0;
	pos match1, match2;
	for(i=0;i<count;i++)
	{  if(point[i].y>ymax )
	   {
	      ymax=point[i];
	   }
	}
	for(i=0; i<count; i++)
	{
		if(m==0&&point[i]==ymax)
		{   match1.x=point[i].x;
		    match1.y=point[i].y;
		    match1.m=point[i].m;
		}
		if(m==2&&point[i]==xmax)
		{  match2.x=point[i].x;
		   match2.y=point[i].y;
		   match2.m=point[i].m;
		}
	}



    //	int fx, fy ;
     //	int flag, count;
    //	int pos[50];
    //	getmouse(&fx,&fy);
    /*	int ny=fy;

	do
	{       count=0;
		flag=0;
		for(i=0; i<=xmax; i++)
		{    if(getpixel(i,ny)==11)
		     { 	flag=1;
			pos[count]=i;
			count++;
		     }
		}
		for(i=0; i<count; i=i+2)
		{
			bres(pos[i],ny,pos[i+1],ny);
		}
		ny--;
	}while(flag!=0&&ny>=0);

	ny=fy;

	do
	{       count=0;
		flag=0;
		for(i=0; i<=xmax; i++)
		{    if(getpixel(i,ny)==11)
		     { 	flag=1;
			pos[count]=i;
			count++;
		     }
		}
		for(i=0; i<count; i=i+2)
		{
			bres(pos[i],ny,pos[i+1],ny);
		}
		ny++;
	}while(flag!=0&&ny<=ymax); */
       //	fill(fx,fy,11,4);

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