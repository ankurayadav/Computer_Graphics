#include<iostream.h>
#include<conio.h>
#include<mouse.h>
#include<graphics.h>
#include<math.h>

struct vec3{

	public:
		int value[3];
};

class mat3{
	public:
		float value[3][3];
		mat3 operator * (mat3 y);
		vec3 operator * (vec3 v);

};

mat3 mat3::operator * (mat3 y)
{
	mat3 z;
	for(int k=0; k<3; k++)
	{
		for(int i=0; i<3; i++)
		{
			z.value[k][i]=0;
			for(int j=0;j<3; j++)
			{
				z.value[k][i]+=value[k][j]*y.value[j][i];
			}
		}
	}
	return z;
}

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
{
	clrscr();

 /*	mat3 x,y,z;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cout<<i+j<<"\t";
			x.value[i][j]=i+j;
			y.value[i][j]=i+j;
		}
		cout<<endl;
	}

	z=x*y;

	cout<<endl;

	for(i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cout<<z.value[i][j]<<"\t";
		}
		cout<<endl;
	}

	vec3 v, r;
	v.value[0]=1; v.value[1]=2; v.value[2]=3;

	r=x*v;

	cout<<endl<<r.value[0]<<"\t"<<r.value[1]<<"\t"<<r.value[2];   */
	int gdriver=DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "d:\\borlandc\\bgi");

	initmouse();
	showmouse();

	int maxx = getmaxx();
	int maxy = getmaxy();

	int midx = maxx / 2;
	int midy = maxy / 2;

	line(midx, 0, midx, maxy);
	line(0, midy, maxx, midy);
	int n ;
	cout<<"Enter number of lines :" ;
	cin>> n;

	vec3 pos[100];
	for(int i=0; i<2*n; i++)
	{
		getmouse(&pos[i].value[0], &pos[i].value[1]);
		pos[i].value[0]-=midx; pos[i].value[1]-=midy;
		pos[i].value[2]=1 ;
		if(i%2!=0)
		{
			line(midx+pos[i-1].value[0],midy+pos[i-1].value[1],midx+pos[i].value[0],midy+pos[i].value[1]);
		}
	}
	cout<<"\nEnter general pivot point :";
	vec3 pivot;
	getmouse(&pivot.value[0], &pivot.value[1]);
	for(i=0; i<2*n; i++)
	{
		pos[i].value[0]-=pivot.value[0]; pos[i].value[1]-=pivot.value[1];
	}

	mat3 rotate;
	vec3 rotated[14];
	float d = 180 ;

	rotate.value[0][0]=cos(d*3.14/180)  ; rotate.value[0][1]=-sin(d*3.14/180)  ;  rotate.value[0][2]=0  ;
	rotate.value[1][0]=sin(d*3.14/180)  ; rotate.value[1][1]=cos(d*3.14/180)  ;  rotate.value[1][2]=0  ;
	rotate.value[2][0]=0  ; rotate.value[2][1]=0  ;  rotate.value[2][2]=1  ;

	getch();

	cleardevice();
	line(midx, 0, midx, maxy);
	line(0, midy, maxx, midy);

	for(i=0;i<2*n;i++)
	{
		rotated[i]= rotate*pos[i];
		if(i%2!=0)
		{
			line(midx+rotated[i-1].value[0], midy+rotated[i-1].value[1], midx+rotated[i].value[0], midy+rotated[i].value[1]);
			//line(pivot.value[0]+midx+rotated[i-1].value[0],pivot.value[1]+midy+rotated[i-1].value[1],pivot.value[0]+midx+rotated[i].value[0],pivot.value[1]+midy+rotated[i].value[1]);
		}
	}


	getch();
}