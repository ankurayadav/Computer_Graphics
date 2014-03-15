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
void crc(int,int, int, int);
void fill(int,int, int, int);
int main()
{    	int xi,yi,xo,yo,x,y;
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"D:\\BORLANDC\\BGI");
      //	int xmax=getmaxx();
      //	int ymax=getmaxy();
	int r;
	printf("Enter radius :");
	scanf("%d",&r);
	initmouse();
	showmouse();
	getmouse(&xi,&yi);
	int h;
 //	circle(xi,yi,10);
	h=1-r;
	x=0;y=r;
	int d;
	while(x<=y)
	{  	crc(x,y,xi,yi);
		if(h<0)
		{       d=x<<1;
			h=h+d+1 ;
		}
		else
		{       d=(x-y)<<1;
			h=h+d+1 ;
			y=y-1;
		}
		x++;

	}

	fill(xi,yi,11,4);

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

void crc(int x,int y,int xi,int yi)
{
	putpixel((xi+x),(yi+y),11);
	putpixel((xi-x),(yi+y),11);
	putpixel((xi+x),(yi-y),11);
	putpixel((xi-x),(yi-y),11);
	putpixel((xi+y),(yi+x),11);
	putpixel((xi-y),(yi+x),11);
	putpixel((xi+y),(yi-x),11);
	putpixel((xi-y),(yi-x),11);
}
