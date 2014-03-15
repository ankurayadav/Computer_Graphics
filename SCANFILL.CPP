// Scan Line Filling Algorithm.

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<iostream.h>
#include<dos.h>


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
typedef struct tedge
{
	int yupper;
	float xi,n;
	struct tedge * next;
}edge;

typedef struct pt
{
	int x,y;
}point;

//Insert edge into list in order to increment X-Intercept  field

void insertedge(edge *list,edge * edge1)
{
	edge *p,*q=list;
	p=q->next;
	while(p!=NULL)
	{
		if(edge1->xi<p->xi)
		{
			p=NULL;
		}
		else
		{
			q=p;
			p=p->next;
		}
	}
	edge1->next=q->next;
	q->next=edge1 ;
}

//for an index ,return y-coordinate of next line

int ynext(int k,int cnt,point * pts)
{
	int j;
	if((k+1) > (cnt-1))
	{
		j=0;
	}
	else
	{
		j=k+1;
	}
	while(pts[k].y == pts[j].y) // Untill the List matches.
	{
		if((j+1) > (cnt-1))
			j=0;
		else
			j++;
	}
	return (pts[j].y);
}

// Building an Edge.

void makeedge(point lower,point upper,int ycomp,edge *e,edge * edges[])
{
	e->n = (float)(upper.x-lower.x)/(upper.y-lower.y);
	e->xi = lower.x;
	if(upper.y < ycomp)
		e->yupper = upper.y-1;
	else
		e->yupper = upper.y;
	insertedge(edges[lower.y],e);
}

void buildedgelist(int cnt,point * pts , edge * edges[])
{
	edge* e;
	point v1,v2;
	int i,yprev=pts[cnt-2].y;

	v1.x=pts[cnt-1].x;
	v1.y=pts[cnt-1].y;

	for(i=0;i<cnt;i++)
	{
		v2=pts[i];
		if(v1.y != v2.y)
		  {
			e=(edge*)malloc(sizeof(edge));
			if(v1.y<v2.y)
			{
			  makeedge(v1,v2,ynext(i,cnt,pts),e,edges);
			}
			else
			{
			 makeedge(v2,v1,yprev,e,edges);
			}
		   }
		yprev=v1.y;
		v1=v2;
	}
}

void buildactivelist(int scan,edge*active,edge* edges[])
{
	edge *p,*q;
	p=edges[scan]->next;
	while(p)
	{
		q=p->next;
		insertedge(active,p);
		p=q;
	}
}

// Scan

void fillscan(int scan,edge * active)
{
	edge *p1,*p2;
	int i;

	p1=active->next;
	while(p1)
	{
		p2=p1->next;
		for(i=p1->xi;i<p2->xi;i++)
		{
			putpixel((int)i,scan,10);
			//delay(1);
		}
			p1=p2->next;
	}
}

// Remove Edge List.

void deleteafter(edge *q)
{
	edge *p = q->next;
	q->next = p->next;
	free(p);
}

// Update Active Edge List.

void updateactivelist(int scan,edge * active)
{
	edge *q=active,*p=active->next;
	while(p)
		if(scan >= p->yupper)
		{
			p=p->next;
			deleteafter(q);
		}
		else
		{
			p->xi = p->xi+p->n;
			q=p;
			p=p->next;
		}
}

void resortactivelist(edge * active)
{
	edge *q,*p=active->next;

	active->next=NULL;

	while(p)
	{
		q=p->next;
		insertedge(active,p);
		p=q;
	}
}

void scanfill(int cnt,point * pts)
{
	edge * edges[439],*active;
	int i,scan;

	for(i=0;i<439;i++)
	{
		edges[i]=(edge*)malloc(sizeof(edge));
		edges[i]->next=NULL;
	}

	buildedgelist(cnt,pts,edges);
	active = (edge*) malloc(sizeof(edge));
	active->next=NULL;

	for(scan=0;scan<439;scan++)    // 439 is WINDOW_SIZE
	{
		buildactivelist(scan,active,edges);
		if(active->next)
		{
			fillscan(scan,active);
			updateactivelist(scan,active);
			resortactivelist(active);
		}
	}
}

int main()
{
/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int xmax, ymax;
clrscr();

//cleardevice();
/* initialize graphics and local variables */
initgraph(&gdriver, &gmode, "D:\BORLANDC\BGI");

cleardevice();

int count;
cout<<"Enter no of nodes : ";
cin>>count;

point *p;
p=(point *)malloc(count*sizeof(point));
	initmouse();
	showmouse();

for(int i=0;i<count;i++)
   {
	//getmouse(&p[i].x,&p[i].y);
	printf("%d :",i);
	scanf("%d",&p[i].x);
	scanf("%d",&p[i].y);
	circle(p[i].x,p[i].y,10);
       //	printf("(%d,%d)",p[i].x,p[i].y);
   }
    /*  	 p[0].x=100;
	 p[0].y=100;
	 p[1].x=130;
	 p[1].y=100;
	 p[2].x=130;
	 p[2].y=125;
	 p[3].x=170;
	 p[3].y=100;
	 p[4].x=170;
	 p[4].y=130;
	 p[5].x=130;
	 p[5].y=150;
	 p[6].x=170;
	 p[6].y=170;
	 p[7].x=170;
	 p[7].y=200;
	 p[8].x=130;
	 p[8].y=175;
	 p[9].x=130;
	 p[9].y=200;
	 p[10].x=100;
	 p[10].y=200;    */

  for(int i=0;i<count-1;i++)
     {	line(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
	//getch();
      }	line(p[i].x-1,p[i].y,p[0].x-1,p[0].y);
		//getch();

      scanfill(count,p);
	getch();
	return 0;
}