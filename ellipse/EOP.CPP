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
void ellipse(int,int, int, int);
int main()
{    	int xi,yi;
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"d:\\borlandc\\BGI");
      //	int xmax=getmaxx();
      //	int ymax=getmaxy();
	int rx , ry ;
	printf("Enter value or rx :") ;
	scanf("%d",&rx);
	printf("\nEnter value or ry :") ;
	scanf("%d",&ry);
	initmouse();
	showmouse();
	getmouse(&xi,&yi);
	putpixel(xi,yi,11);
	ellipse(xi,yi,rx,ry);
	getch();
	return 0;
}

void ellipse(int xi, int yi,int rx, int ry)
{
	long int pry = ry*ry;
	long int prx = rx*rx;
	float p1 = pry-(prx*ry)+(prx/4);
	long int x=0;
	long int y=ry;
	long int tpry=2*pry, tprx = 2*prx;
	long int tpryx= tpry*x, tprxy= tprx*y;
	do
	{     	putpixel(xi+x,yi+y,11);
		putpixel(xi-x,yi+y,11);
		putpixel(xi+x,yi-y,11);
		putpixel(xi-x,yi-y,11);
		x++;
		if(p1<0)
		{     	//p1=p1 + (2*pry*x) +pry ;
			  p1=p1 + tpry + tpryx +pry;

		}
		else
		{       y--;
			//p1=p1 + (2*pry*x)-(2*prx*y) +pry ;
			p1=p1+ tpry +tpryx -tprx-tprxy +pry;
			tprxy=tprxy+tprx;
		}
		tpryx=tpryx+tpry;

	}while((2*pry*x)<=(2*prx*y)) ;
	tpry= 2*pry;
	tprx=2*prx;
	tprxy=tprx*y;
	tpryx=tpry*x;
	//	REGION 2
	p1 = pry*(x+0.5)*(x+0.5)+prx*(y-1)*(y-1)-pry*prx;

	do
	{     	putpixel(xi+x,yi+y,11);
		putpixel(xi-x,yi+y,11);
		putpixel(xi+x,yi-y,11);
		putpixel(xi-x,yi-y,11);
		y--;
		if(p1>0)
		{      //p1=p1 - (2*prx*y) +prx ;
			p1=p1 - tprx - tprxy + prx;
		}
		else
		{       x++;
		       //	p1=p1 + (2*pry*x)-(2*prx*y) +prx ;
			p1=p1 + tpry + tpryx - tprx - tprxy +prx;
			tpryx= tpryx + tpry;
		}
		tprxy=tprxy-tprx;
	}while((tprxy)!=0) ;

		putpixel(xi+x,yi+y,11);
		putpixel(xi-x,yi+y,11);
		putpixel(xi+x,yi-y,11);
		putpixel(xi-x,yi-y,11);

}
