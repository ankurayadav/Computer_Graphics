#include<dos.h>

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
	delay(500);
}