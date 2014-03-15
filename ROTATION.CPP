#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<mouse.h>
#include<graphics.h>
struct vec3{
	public:
		int value[3];
};
class mat3{
	public:
		float value[3][3];
		vec3 operator *(vec3 v);
};
vec3 mat3::operator * (vec3 v)
{
	vec3 r;
	for(int k=0; k<3; k++)
	{
		r.value[k]=0;
		for(int i=0; i<3; i++)
		{
			r.value[k]+= value[k][i]*v.value[i];
		}
	}
	return r;
}
void main()
{    int gdriver=DETECT, gmode ;
	initgraph(&gdriver, &gmode, "d:\\borlandc\\bgi") ;
	initmouse();
	showmouse();
	int maxx, maxy, midx, midy;
	maxx = getmaxx();
	maxy = getmaxy();
	midx = maxx/2;
	midy = maxy/2;
	line(midx, 0, midx, maxx);
	line(0, midy, maxx, midy);
	int n;
	cout<<"Enter no. of lines :" ;
	cin>>n;
	vec3 cor[100];
	for(int i=0; i<2*n ; i++)
	{	getmouse(&cor[i].value[0], &cor[i].value[1]);
		cor[i].value[0]-=midx;
		cor[i].value[1]-=midy;
		if(i%2!=0)
		{	line(midx+cor[i-1].value[0], midy+cor[i-1].value[1], midx+cor[i].value[0], midy+cor[i].value[1]);
			//line(cor[i-1].value[0],cor[i-1].value[1], cor[i].value[0], cor[i].value[1]);
		}
	}
	cout<<"Enter any general pivot :";
	int newx , newy ;
	getmouse(&newx, &newy);

	for(i=0; i<2*n ; i++)
	{	//getmouse(&cor[i].value[0], &cor[i].value[1]);
		cor[i].value[0]+=midx;
		cor[i].value[1]+=midy;
		cor[i].value[0]-=newx;
		cor[i].value[1]-=newy;
		//if(i%2!=0)
		//{	line(midx+cor[i-1].value[0], midy+cor[i-1].value[1], midx+cor[i].value[0], midy+cor[i].value[1]);
			//line(cor[i-1].value[0],cor[i-1].value[1], cor[i].value[0], cor[i].value[1]);
		//}
	}

	getch();
	cleardevice();
	line(midx, 0, midx, maxx);
	line(0, midy, maxx, midy);
	mat3 rotate ;
	int de = 180 ;
	rotate.value[0][0]=cos(de*3.14/180)  ;	rotate.value[0][1]=-sin(de*3.14/180)  ; rotate.value[0][2]= 0 ;
	rotate.value[1][0]=sin(de*3.14/180)  ;	rotate.value[1][1]=cos(de*3.14/180)  ; rotate.value[1][2]=0  ;
	rotate.value[2][0]=0 ;	rotate.value[2][1]=0  ; rotate.value[2][2]=1  ;
	setcolor(11);
	//vec3 res ;
	for(i=0; i<2*n; i++)
	{    cor[i] = rotate*cor[i] ;
		if(i%2!=0)
		{	//line(midx+cor[i-1].value[0], midy+cor[i-1].value[1], midx+cor[i].value[0], midy+cor[i].value[1]);
			line(newx+cor[i-1].value[0], newy+cor[i-1].value[1], newx+cor[i].value[0], newy+cor[i].value[1]);
			//line(cor[i-1].value[0],cor[i-1].value[1], cor[i].value[0], cor[i].value[1]);
		}
	}

	getch();
}