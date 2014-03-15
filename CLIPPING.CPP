//line clipping algorithm
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<malloc.h>
struct cpos{
	int x;
	int y;
};

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

int outcode(struct cpos *r, struct cpos *p);
void clip(struct cpos *r, struct cpos *p, int *a);
void main()
{
	int gdriver = DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "d:\\borlandc\\bgi");

	initmouse();
	showmouse();

	struct cpos *r;
	r=(cpos *)malloc(2*sizeof(cpos));

	cout<<"Enter two extreme coordinates of clipping rectangle..." ;

	for(int i=0;i<2;i++)
	{ 	getmouse(&r[i].x,&r[i].y);
		//circle(r[i].x,r[i].y,10);
	}

	setcolor(15);
	rectangle(r[0].x,r[0].y,r[1].x,r[1].y);

	cout<<"\nEnter any line coordinates...";
	struct cpos *p=(cpos *)malloc(2*sizeof(cpos));

	for(i=0;i<2;i++)
	{ 	getmouse(&p[i].x,&p[i].y);
		//circle(p[i].x,p[i].y,10);
	}

	setcolor(10);
	line(p[0].x,p[0].y,p[1].x,p[1].y);
	int check=0;
	while(check==0)
	{
		check=outcode(r,p);
	}
	getch();
	cleardevice();
	setcolor(15);
	rectangle(r[0].x,r[0].y,r[1].x,r[1].y);
	if(check!=-1)
	{    setcolor(10);
		line(p[0].x,p[0].y,p[1].x,p[1].y);
	}
	getch();
}
/*     1010    1000    1001
   ymin   __|________|__
	  0010 |  0000  | 0001
   ymax   __|________|__
	  0110 |  0100  | 0101
	    xmin     xmax
*/

int outcode(struct cpos *r, struct cpos *p)
{ 	int xmin = r[0].x;
	int ymin = r[0].y;
	int xmax = r[1].x;
	int ymax = r[1].y;

	int a[2];
	for(int i=0; i<2; i++)
	{       a[i]=0;
		if(p[i].x<xmin)
		{
			a[i]=(a[i]|2);
		}
		else if(p[i].x>xmax)
		{
			a[i]=(a[i]|1);
		}

		if(p[i].y<ymin)
		{
			a[i]=(a[i]|8);
		}
		else if(p[i].y>ymax)
		{
			a[i]=(a[i]|4);
		}
	}

	if((a[0]&a[1]))
	{    //cout<<a[0]<<a[1];
		return -1;
	}
	if((a[0]|a[1])==0)
	{    //cout<<a[0]<<a[1];
		return 1;
	}
	clip(r, p, a);
	return 0;
}

void clip(struct cpos *r, struct cpos *p, int *a)
{    int xmin = r[0].x;
	int ymin = r[0].y;
	int xmax = r[1].x;
	int ymax = r[1].y;

	float slope=float(p[1].y-p[0].y)/(p[1].x-p[0].x) ;

	for(int i=0; i<2 ;i++)
	{    if(a[i]==0)
		{continue;}
		if(a[i]&2)
		{
			p[i].y = p[i].y +  slope*(xmin-p[i].x);
			p[i].x = xmin;
			continue;
		}
		if(a[i]&1)
		{
			p[i].y = p[i].y +  slope*(xmax-p[i].x);
			p[i].x = xmax;
			continue;
		}
		if(a[i]&8)
		{
			p[i].x = p[i].x +  (ymin-p[i].y)/slope;
			p[i].y = ymin;
			continue;
		}
		if(a[i]&4)
		{
			p[i].x = p[i].x +  (ymax-p[i].y)/slope;
			p[i].y = ymax;
			continue;
		}
	}
}
