#include<iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<dos.h>
int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int xmax, ymax;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "D:\\BORLANDC\\BGI");

   /* read result of initialization */
   errorcode = graphresult();
   /* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

   setcolor(getmaxcolor());
   xmax = getmaxx();
   ymax = getmaxy();
   /* draw a diagonal line */
  /*
   for(int i=0; i<=xmax; i++)
   {    line(0, 390, xmax, 390);
	bar(i+25,315 ,i+125 ,345);
	bar(i,345,i+150,375);
	circle(i+25,375,15) ;
	circle(i+125,375,15) ;
	delay(25);
	cleardevice();
   } */
   float slope = -390/xmax;
   for(int i=0; i<=xmax; i++)
   {    line(0, 390, xmax, 0);
	bar(i+25,315 ,i+125 ,345);
	bar(i,345,i+150,375);
	circle(i+25,375,15) ;
	circle(i+125,375,15) ;
	delay(25);
	cleardevice();
   }

  // bar(100,100 ,200 ,130);
  // bar(75,130,225,155);
  // circle(100,155,15) ;
  // circle(200,155,15) ;
   /* clean up */
   getch();
   closegraph();
   return 0;
}