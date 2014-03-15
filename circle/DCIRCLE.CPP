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
	delay(500);
}
void crc(int,int, int, int);
int main()
{    	int xi,yi,xo,yo,x,y;
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"D:\\BORLANDC\\BGI");
      //	int xmax=getmaxx();
      //	int ymax=getmaxy();
	initmouse();
	showmouse();
	getmouse(&xi,&yi);
	getmouse(&xo,&yo);
	int h,r ;
	float m=pow((xo-xi),2);
	float n=pow((yo-yi),2);
	r=sqrt(m+n);
	xi=xi + ((xo-xi)/2);
	yi=yi +((yo-yi)/2);
 //	circle(xi,yi,10);
	h=1-r;
	x=0;y=r;
	while(x<=y)
	{      	crc(x,y,xi,yi);
		if(h<0)
		{
			h=h+(2*x)+1 ;
		}
		else
		{       h=h+(2*(x-y))+1 ;
			y=y-1;
		}
		x++;
	}
	getch();
	closegraph();
	return 0;
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
