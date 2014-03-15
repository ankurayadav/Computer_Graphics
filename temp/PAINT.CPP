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
	delay(1);
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

	while(1)
{      // cleardevice();
		getmouse(&xi,&yi);
	putpixel(xi,yi,2);
	delay(1);
}
	getch();
	closegraph();
	return 0;
}