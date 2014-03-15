#include<graphics.h>
#include<dos.h>
#include<conio.h>
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
	delay(100);
}
int main()
{    	int xi,yi,xo,yo;
   //	cout<<"Enter the initial coordinates:";
   //	cin>>xi>>yi;
  //	cout<<"Enter the final coordinates:";
  //	cin>>xo>>yo;
  //	clrscr();
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"D:\\BORLANDC\\BGI");
	int xmax=getmaxx();
	int ymax=getmaxy();
	initmouse();
	showmouse();
	getmouse(&xi,&yi);
	while(1)
{       cleardevice();
	circle(xi,yi,10);
	getmouse(&xo,&yo);
	circle(xo,yo,10);
	line(xi,yi,xo,yo);
 /*	if(xi>xo)
	{       int t=xi;
		xi=xo;
		xo=t;
		t=yi;
		yi=yo;
		yo=t;
	}
	float m,x,y;
	m=float(yo-yi)/float(xo-xi) ;
	y=yi;
	x=xi;
	if(m<=1)
	{
		for(x=xi;x<xo;x++)
		{
		    putpixel(x,y,15);
		    y=y+m;
		}
	}
	if(m>1)
	{       float m1=1/m;
		for(y=yi;y<yo;y++)
		{
			putpixel(x,y,15);
			x=x+m1;
		}
	}   */
	delay(100);
}
	getch();
	closegraph();
	return 0;
}