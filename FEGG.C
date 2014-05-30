#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>
union REGS i,o;		//Register values for mouse function
int initmouse();
void restrictmouseptr(int,int,int,int);
void getmousepos(int *,int *,int *);
void main()
{
	int gd=DETECT,gm,maxx,maxy,x,y,button;
	int score=0,speed=5,level=0;
	int ax=30,by=0,count_eggs=10;
	int color=1,qualify_score=100;
	char name[40];
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	maxx=getmaxx();
	maxy=getmaxy();
	setbkcolor(1);
	setviewport(0,0,maxx,maxy,1);
	if(initmouse()==0)
	{
		closegraph();
		restorecrtmode(); //to go back to normal graphics mode or deleting viewport.
		printf("MOUSE DRIVER NOT LOADED!!!!!!!");
		exit(1);
	}
	restrictmouseptr(0,getmaxy()-20,maxx,getmaxy()-15);
	setfillstyle(1,15);
	gotoxy(5,2);
	printf("PLEASE ENTER YOUR NAME :: ");
	gets(name);
	cleardevice();
	gotoxy(5,5);
	printf("INSTRUCTIONS ");
	gotoxy(5,7);
	printf("1 : Collect as many eggs as you can.");
	gotoxy(5,9);
	printf("2 : Collecting a RED egg will give 50 POINTS.");
	gotoxy(5,11);
	printf("3 : Collecting a WHITE egg will deduct 20 POINTS.");
	gotoxy(5,13);
	printf("4 : Collecting all OTHER eggs will give 10 POINTS.");
	gotoxy(5,15);
	printf("5 : Total Levels : 6");
	gotoxy(5,17);
	printf("6 : 10 EGGS in all levels");
	gotoxy(5,19);
	printf("7 : Initial Score : 0");
	gotoxy(5,21);
	printf("8 : USE MOUSE FOR MOVING THE BASKET");
	getch();
	cleardevice();
	gotoxy(320,2);
	printf("YOUR SCORE : %d ",score);
	gotoxy(320,4);
	printf("EGGS LEFT : %d ",count_eggs);
	gotoxy(320,6);
	printf("TO QUALIFY : %d ",qualify_score);
	gotoxy(320,8);
	printf("LEVEL : %d ",level+1);

	while(!kbhit())
	{
		getmousepos(&button,&x,&y);
		setcolor(15);
		setfillstyle(1,color);
		fillellipse(ax,by,10,15);
		if(color==4)
		{
			if((by>getmaxy()-20)&&(by<=getmaxy()-15)) // For checking the egg position.
			{
				if(ax>=x-20&&ax<=(x+60))
				{
					score+=50;
					gotoxy(320,2);
					printf("YOUR SCORE : %d ",score);
				}
			}
		}
		else if(color==15)
		{
			if((by>getmaxy()-20)&&(by<=getmaxy()-15)) // For checking the egg position.
			{
				if(ax>=x-20&&ax<=(x+60))
				{
					score-=20;
					gotoxy(320,2);
					printf("YOUR SCORE : %d ",score);
				}
			}
		}
		else
		{
			if((by>getmaxy()-20)&&(by<=getmaxy()-15)) // For checking the egg position.
			{
				if(ax>=x-20&&ax<=(x+60))
				{
					score+=10;
					gotoxy(320,2);
					printf("YOUR SCORE : %d ",score);
				}
			}
		}
		if(by>getmaxy()+15)
		{
			by=0;
			ax=10+random(getmaxx()-150);
			count_eggs--;
			if(count_eggs==0)
			{
				if(score>=qualify_score)
				{
					level++;
					gotoxy(32,10);
					printf("LEVEL %d COMPLETED.........",level);
					count_eggs=10;
					speed++;
					qualify_score+=100;
					getch();
					if(level==6)
					{
						goto end;
					}
					gotoxy(32,10);
					printf("                           ");
				}
				else
				{
					gotoxy(32,10);
					printf("NOT QUALIFIED.....TRY AGAIN",level);
					getch();
					goto end;
				}
			}
				color=2+random(14);
		}
		gotoxy(320,4);
		printf("EGGS LEFT : %d ",count_eggs);
		gotoxy(320,6);
		printf("TO QUALIFY : %d ",qualify_score);
		gotoxy(320,8);
		printf("LEVEL : %d ",level+1);
		setcolor(14);
		line(x,getmaxy(),x+40,getmaxy());
		line(x,getmaxy(),x-20,getmaxy()-20);
		line(x+40,getmaxy(),x+60,getmaxy()-20);
		ellipse(x+20,getmaxy()-20,0,360,40,5);
		delay(10);
		setcolor(1);
		line(x,getmaxy(),x+40,getmaxy());
		line(x,getmaxy(),x-20,getmaxy()-20);
		line(x+40,getmaxy(),x+60,getmaxy()-20);
		ellipse(x+20,getmaxy()-20,0,360,40,5);
		setfillstyle(1,1);
		fillellipse(ax,by,10,15);
		by+=speed;
	}
	end:
	cleardevice();
	gotoxy(30,12);
	printf("PLAYER NAME : %s ",name);
	gotoxy(33,15);
	printf("GAME OVER....   ");
	gotoxy(30,18);
	printf("YOUR SCORE : %d",score);
	gotoxy(58,24);
	printf("MADE BY :");
	gotoxy(55,25);
	printf("LALIT AGGARWAL");
	gotoxy(30,10);
	getch();
	getch();
}
int initmouse()
{
	i.x.ax=0;	//for  initialising mouse.
	int86(0x33,&i,&o);
	return(o.x.ax);
}
void restrictmouseptr(int x1,int y1,int x2,int y2)
{
	i.x.ax=7;   //to define the upper left boundry of mouse.
	i.x.cx=x1;
	i.x.dx=x2;
	int86(0x33,&i,&o);
	i.x.ax=8;   //to define the bottom right boundry of mouse.
	i.x.cx=y1;
	i.x.dx=y2;
	int86(0x33,&i,&o);
}
void getmousepos(int *button,int *x, int *y)
{
	i.x.ax=3;   //to move mouse.
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
}

