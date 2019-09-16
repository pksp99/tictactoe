#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define cox(a) (getmaxx()/2+a)
#define coy(a) (getmaxy()/2-a)
#define MAX 20
#define ROUND(a) (int)(a+0.5)
struct lins
{
	int stx,sty,enx,eny;
};
struct lins l[MAX];
int as(int a)
{
	if(a>=0)
		return a;
	else
	return -a;
}

int stx,sty,enx,eny;
int pk=58,pkw=7; //pk is pixels per centimeter // pkw gives boldness of object with respect to pk
int xc,yc;//it is coordinate of centre of first box of the board
int box; //it is length of unit block
int xpoints,opoints ;
int mat[MAX][MAX]; /*matrix reprents game in computer memory
			 mat[i][j]==0 if nothing
			 mat[i][j]==1 if contains x
			 mat[i][j]=2 if contains O						*/
void xprint(int x,int y, int color , float scale); //prints x with coordinate (x,y)
void oprint(int x, int y,int color,float scale) ; //prints O with coordinate (x,y)
void board(int n,float scale);//draws the game board and assigns #box#
void squa(int x,int y,int color,float scale);//highlighting square which moves in game
int game(int n,float scale,int k,int winpoints);//manages keyboard input and things to display
int win(int a[MAX][MAX],int x,int y, int n, int k);/*returns 1 if x wins
							 returns 2 if o wins
							 else return 0	*/
void dda(int a, int b , int c, int d);
void ddaw(int a, int b , int c, int d);
int huge det()
{
	return 0;        //requird for svga
}
void custom(int scale);
void amatuer(int scale);
void intermed(int scale);
void adv(int scale);
int main(void)
{
	int gdriver = 0, gmode = 1,scale;
	char temp[20],i,c;
	clrscr();
	gdriver=installuserdriver("SVGA",&det);
	initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
	scale=1;
	i=0;
	setcolor(12);
	settextstyle(0,HORIZ_DIR,100);
	sprintf(temp,"1. AMATEUR");
	outtextxy(100,getmaxy()/15,temp);
	sprintf(temp,"2. INTERMEDIATE");
	outtextxy(100,2*getmaxy()/15,temp);
	sprintf(temp,"3. ADVANCED");
	outtextxy(100,3*getmaxy()/15,temp);
	sprintf(temp,"4. CUSTOM");
	outtextxy(100,4*getmaxy()/15,temp);
	while((i>4||i<1))
	{
		c=getch();
		i=c-'0';
		if(c==27)
			exit(1);
	}
	switch(i)
	{
		case 1:
		amatuer(scale);
		break;
		case 2:
		intermed(scale);
		break;
		case 3:
		adv(scale);
		break;
		case 4:
		custom(scale);
		break;
	}
	getch();
	closegraph();
	return 0 ;
}

void custom(int scale)
{
	int i,whowins,n,k,w;
	char winner[20],c,temp[20];
	setfillstyle(SOLID_FILL,14);
	floodfill(1,2,15);

	settextstyle(0,HORIZ_DIR,100);
	sprintf(temp,"Select the size of the board");
	setcolor(9);
	outtextxy(20,getmaxy()/8,temp);
	setcolor(12);
	for(i=3;i<=8;i++)
	{
		sprintf(temp,"%d",i);
		outtextxy(100*i-200,getmaxy()/4-70,temp);
	}
	n=0;
	while(n<3||n>8)
	{
		c=getch();
		n=c-'0';
	}
	setcolor(0);
	sprintf(temp,"%d",n);
	outtextxy(100*n-200,getmaxy()/4-70,temp);
	sprintf(temp,"Select the length of consecutive streak");
	setcolor(9);
	outtextxy(20,3*getmaxy()/8,temp);
	setcolor(12);
	for(i=3;i<=n;i++)
	{
		sprintf(temp,"%d",i);
		outtextxy(100*i-200,getmaxy()/2-70,temp);
	}
	k=0;
	while(k<3||k>n)
	{
		c=getch();
		k=c-'0';
	}
	setcolor(0);
	sprintf(temp,"%d",k);
	outtextxy(100*k-200,getmaxy()/2-70,temp);

	sprintf(temp,"Set minimum win points");
	setcolor(9);
	outtextxy(20,5*getmaxy()/8,temp);
	setcolor(12);
	for(i=1;i<=10;i++)
	{
		sprintf(temp,"%d",i);
		if(i==10)
			sprintf(temp,"M");
		outtextxy(100*i,6*getmaxy()/8-70,temp);
	}
	w=0;
	while(w<1||w>10)
	{
		c=getch();
		w=c-'0';
		if(c=='M'||c=='m')
			w=10;
	}
	setcolor(0);
	sprintf(temp,"%d",w);
	if(w==10)
		sprintf(temp,"M");
	outtextxy(100*w,6*getmaxy()/8-70,temp);
	getch();

	setfillstyle(SOLID_FILL,15);
	floodfill(1,2,15);
	whowins=game(n,scale,k,w);
	setcolor(0);
	if(whowins==0)
		sprintf(winner,"ITS A TIE !!!");
	else
		sprintf(winner,"%c WON THE MATCH",whowins);
	settextstyle(0,	HORIZ_DIR,10);
	if(whowins=='X')
		setcolor(9);
	else if(whowins=='O')
		setcolor(12);
	outtextxy(40,70,winner);
}
void amatuer(int scale)
{
	int whowins;
	char winner[20];
	setfillstyle(SOLID_FILL,15);
	floodfill(1,2,15);
	whowins=game(3,scale,3,1);
	setcolor(0);
	if(whowins==0)
		sprintf(winner,"ITS A TIE !!!");
	else
		sprintf(winner,"%c WON THE MATCH",whowins);
	settextstyle(0,	HORIZ_DIR,10);
	if(whowins=='X')
		setcolor(9);
	else if(whowins=='O')
		setcolor(12);
	outtextxy(40,70,winner);
}
void intermed(int scale)
{
	int whowins;
	char winner[20];
	setfillstyle(SOLID_FILL,15);
	floodfill(1,2,15);
	whowins=game(4,scale,3,10);
	setcolor(0);
	if(whowins==0)
		sprintf(winner,"ITS A TIE !!!");
	else
		sprintf(winner,"%c WON THE MATCH",whowins);
	settextstyle(0,	HORIZ_DIR,10);
	if(whowins=='X')
		setcolor(9);
	else if(whowins=='O')
		setcolor(12);
	outtextxy(40,70,winner);
}
void adv(int scale)
{
	int whowins;
	char winner[20];
	setfillstyle(SOLID_FILL,15);
	floodfill(1,2,15);
	whowins=game(5,scale,3,10);
	setcolor(0);
	if(whowins==0)
		sprintf(winner,"ITS A TIE !!!");
	else
		sprintf(winner,"%c WON THE MATCH",whowins);
	settextstyle(0,	HORIZ_DIR,10);
	if(whowins=='X')
		setcolor(9);
	else if(whowins=='O')
		setcolor(12);
	outtextxy(40,70,winner);
}
void xprint(int x, int y , int color , float scale)
{
	int i,w;
	w=pkw*scale;
	setcolor(color);
	for(i=0;i<=w;i++)
	{
		line((x)+pk/2*scale+i-w/2,(y)+pk/2*scale,(x)-pk/2*scale+i-w/2,(y)-pk/2*scale) ;
		line((x)-pk/2*scale+i-w/2,(y)+pk/2*scale,(x)+pk/2*scale+i-w/2,(y)-pk/2*scale) ;
	}

}
void oprint(int x, int y,int color,float scale)
{
	int i,w;
	scale=0.8*scale;
	w=pkw*scale;
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	circle((x),(y),pk/2*1.41*scale);
	circle((x),(y),pk/2*1.41*scale-w);
	floodfill((x),(y)+pk/2*1.41*scale-1,color);

}

void board(int n,float scale)
{
	int i,j,temp,length,t;
	temp=(pk+25)*scale;
	box=temp;
	length=temp*n;
	setcolor(0);
	if(n%2==1)
	{
		t=temp/2;
		line(cox(length/2),coy(t),cox(-length/2),coy(t));
		line(cox(length/2),coy((-t)),cox(-length/2),coy((-t)));
		line(cox(t),coy(length/2),cox(t),coy((-length/2)));
		line(cox(-t),coy((length/2)),cox(-t),coy((-length/2)));
		temp=(pk+25)*scale;
		for(i=1;i<=n/2;i++)
		{
			t=temp+t;
			line(cox(length/2),coy(t),cox(-length/2),coy(t));
			line(cox(length/2),coy((-t)),cox(-length/2),coy((-t)));
			line(cox(t),coy(length/2),cox(t),coy((-length/2)));
			line(cox(-t),coy((length/2)),cox(-t),coy((-length/2)));

		}
		xc=cox(0)-temp*(int)(n/2);
		yc=coy(0)-temp*(int)(n/2);
	}
	else
	{
		line(cox(length/2),coy((0)),cox(-length/2),coy((0)));
		line(cox(0),coy(length/2),cox(0),coy((-length/2)));
		t=(pk+25)*scale;
		temp=t;
		for(i=1;i<=n/2;i++)
		{
			line(cox(length/2),coy(t),cox(-length/2),coy(t));
			line(cox(length/2),coy((-t)),cox(-length/2),coy((-t)));
			line(cox(t),coy(length/2),cox(t),coy((-length/2)));
			line(cox(-t),coy((length/2)),cox(-t),coy((-length/2)));
			t=t+temp;
		}
		t=temp;
		xc=-(temp*n/2-t/2)+cox(0);
		yc=-(temp*n/2-t/2)+coy(0);
	}
}
void squa(int x ,int y, int color,float scale)
{
	int temp,i;
	setlinestyle(SOLID_LINE,0,2);
	setcolor(color);
	temp=(box/2-pkw/2);
	for(i=0;i<pkw/2*scale;i++)
	{
		rectangle(x-temp+i, y-temp+i, x+temp-i, y+temp-i);
	}
}
int game(int n, float scale, int k,int winpoints)
{
	int i,j,t1,t2,step,temp,count=0,p,tpx,tpy,tpk,tsx,tso;  //step==odd O plays first
	int c,xk,yk;              //step==even x plays first
	int maxi,maxj;
	char xscore[20],oscore[20];
	xpoints=0;
	opoints=0;
	board(n,scale);
	maxi=(n-1)*box+xc;
	maxj=(n-1)*box+yc;
	squa(xc,yc,1,scale);
	c=0;
	xk=xc;
	yk=yc;
	i=xk/box;
	j=yk/box;
	t1=i;
	t2=j;
	i=j=0;
	step=0;
	setcolor(0);
	sprintf(xscore,"WINPOINTS : %d",winpoints);
	sprintf(oscore,"STREAK LENGTH : %d",k);
	if(winpoints==10)
		sprintf(xscore,"Play till end");
	settextstyle(0, HORIZ_DIR, 5);
	outtextxy(getmaxx()/4,10*getmaxy()/12+30,xscore);
	outtextxy(getmaxx()/4,11*getmaxy()/12,oscore);
	while(c!=27)
	{


		c=getch();
		if(c==27)
			continue;

		if(c=='a'||c=='s'||c=='d'||c=='w')
		{
			squa(xk,yk,15,scale);
			for(p=0;p<count;p++)
				ddaw(l[p].stx,l[p].sty,l[p].enx,l[p].eny);
		}
		switch(c)
		{
			case 'a':
				if(xk==xc)
					xk=maxi;
				else
					xk=xk-box;
				squa(xk,yk,1,scale);
				i=xk/box-t1;
				break;
			case 'd':
				if(xk==maxi)
					xk=xc;
				else
					xk=xk+box;
				i=xk/box-t1;
				squa(xk,yk,1,scale);
				break;
			case 'w':
				if(yk==yc)
					yk=maxj;
				else
					yk=yk-box;
				j=yk/box-t2;
				squa(xk,yk,1,scale);
				break;
			case 's':
				if(yk==maxj)
					yk=yc;
				else
					yk=yk+box;
				j=yk/box-t2;
				squa(xk,yk,1,scale);
				break;
			case 13:
				if(mat[i][j]==0)
				{
					temp=step%2;
					switch(temp)
					{
						case 0:
							xprint(xk,yk,9,scale);
							mat[i][j]=1;
							break;
						case 1:
							oprint(xk,yk,12,scale);
							mat[i][j]=2;
							break;
					}
					step++;
					temp=(win(mat,i,j,n,k));
					if(temp==1)     //if won the match...
					 {
						if(mat[i][j]==1)
							xpoints++;
						else if(mat[i][j]==2)
							opoints++;
						tpx=stx;
						tpy=sty;
						tpk=k;
						stx=stx*box+xc;
						sty=sty*box+yc;
						enx=enx*box+xc;
						eny=eny*box+yc;
						if(stx-enx==0)
						{
							sty=sty+box/2;
							eny=eny-box/2;

							while(tpk>0)
							{
								tpy++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						else if(sty-eny==0)
						{
							stx=stx+box/2;
							enx=enx-box/2;
							while(tpk>0)
							{
								tpx++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						l[count].stx=stx;
						l[count].sty=sty;
						l[count].enx=enx;
						l[count].eny=eny;
						dda(stx,sty,enx,eny);
						count++;
						temp=(win1(mat,i,j,n,k));
					 }
					 if(temp==2)     //if won the match...
					 {
						if(mat[i][j]==1)
							xpoints++;
						else if(mat[i][j]==2)
							opoints++;
						tpx=stx;
						tpy=sty;
						tpk=k;
						stx=stx*box+xc;
						sty=sty*box+yc;
						enx=enx*box+xc;
						eny=eny*box+yc;
						if(stx-enx==0)
						{
							sty=sty+box/2;
							eny=eny-box/2;

							while(tpk>0)
							{
								tpy++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						else if(sty-eny==0)
						{
							stx=stx+box/2;
							enx=enx-box/2;
							while(tpk>0)
							{
								tpx++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}

						l[count].stx=stx;
						l[count].sty=sty;
						l[count].enx=enx;
						l[count].eny=eny;
						dda(stx,sty,enx,eny);
						count++;
						temp=(win2(mat,i,j,n,k));
					 }
					 if(temp==3)     //if won the match...
					 {
						if(mat[i][j]==1)
							xpoints++;
						else if(mat[i][j]==2)
							opoints++;
						tpx=stx;
						tpy=sty;
						tpk=k;
						stx=stx*box+xc;
						sty=sty*box+yc;
						enx=enx*box+xc;
						eny=eny*box+yc;

						if(stx-sty==enx-eny)
						{
							stx=stx+box/2;
							sty=sty+box/2;
							enx=enx-box/2;
							eny=eny-box/2;
							while(tpk>0)
							{
								tpx++;
								tpy++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						else if(stx+sty==enx+eny)
						{
							stx=stx-box/2;
							sty=sty+box/2;
							enx=enx+box/2;
							eny=eny-box/2;
							while(tpk>0)
							{
								tpx--;
								tpy++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						l[count].stx=stx;
						l[count].sty=sty;
						l[count].enx=enx;
						l[count].eny=eny;
						dda(stx,sty,enx,eny);
						count++;
						temp=(win3(mat,i,j,n,k));
					 }
					 if(temp==4)     //if won the match...
					 {
						if(mat[i][j]==1)
							xpoints++;
						else if(mat[i][j]==2)
							opoints++;
						tpx=stx;
						tpy=sty;
						tpk=k;
						stx=stx*box+xc;
						sty=sty*box+yc;
						enx=enx*box+xc;
						eny=eny*box+yc;

						if(stx-sty==enx-eny)
						{
							stx=stx+box/2;
							sty=sty+box/2;
							enx=enx-box/2;
							eny=eny-box/2;
							while(tpk>0)
							{
								tpx++;
								tpy++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						else if(stx+sty==enx+eny)
						{
							stx=stx-box/2;
							sty=sty+box/2;
							enx=enx+box/2;
							eny=eny-box/2;
							while(tpk>0)
							{
								tpx--;
								tpy++;
								tpk--;
								if(mat[tpx][tpy]==1)
									xprint((tpx*box+xc),(tpy*box+yc),8,scale);
								else if(mat[tpx][tpy]==2)
									oprint((tpx*box+xc),(tpy*box+yc),8,scale);
							}
						}
						l[count].stx=stx;
						l[count].sty=sty;
						l[count].enx=enx;
						l[count].eny=eny;
						dda(stx,sty,enx,eny);
						count++;
					 }
				}
		}

		sprintf(xscore,"X:%d",tsx);
		sprintf(oscore,"O:%d",tso);
		settextstyle(0, HORIZ_DIR, 70);
		setcolor(15);
		outtextxy(50,getmaxy()/2,xscore);
		outtextxy(1050,getmaxy()/2,oscore);
		sprintf(xscore,"X:%d",(xpoints));
		sprintf(oscore,"O:%d",(opoints));
		setcolor(9);
		outtextxy(50,getmaxy()/2,xscore);
		setcolor(12);
		outtextxy(1050,getmaxy()/2,oscore);
		tsx=xpoints;
		tso=opoints;
		if(n==3)
		{
			if(xpoints)
			{
				getch();
				return 'X';
			}
			if(opoints)
			{
				getch();
				return 'O';
			}
		}
		if(winpoints!=10)
		{
			if(winpoints<=xpoints)
			{
				getch();
				return 'X';
			}
			if(winpoints<=opoints)
			{
				getch();
				return 'O';
			}
		}
		if(step>=n*n)
		{
			if(xpoints>opoints)
			{
				getch();
				return 'X';
			}
			else if(xpoints<opoints)
			{
				getch();
				return 'O';
			}
			else
			{
				getch();
				return 0;
			}
		}
	}

	return 0;
}

int win(int a[20][20],int x,int y, int n, int k)
{
	int i,j,ct1,ct2,flag;
	for(i=x,j=y,ct1=0;;i--)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(i==0)
			{
				stx--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;i++)
	{
		enx=i;
		eny=j;
		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(i==n-1)
			{
				enx++;
				break;
			}
		}
		else
			break;
	}

	if(ct1+ct2-1==k)
		return 1;


	for(i=x,j=y,ct1=0;;j--)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0)
			{
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++)
	{
		enx=i;
		eny=j;
		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1)
			{
				eny++;
				break;
			}
		}
		else
			break;
	}

	if(ct1+ct2-1==k)
		return 2;

	for(i=x,j=y,ct1=0;;j--,i--)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==0)
			{
				stx--;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i++)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==n-1)
			{
				enx++;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 3;
	for(i=x,j=y,ct1=0;;j--,i++)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==n-1)
			{
				stx++;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i--)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==0)
			{
				enx--;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 4;
	return 0;

}
int win1(int a[20][20],int x,int y, int n, int k)
{
	int i,j,ct1,ct2,flag;
	for(i=x,j=y,ct1=0;;j--)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0)
			{
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++)
	{
		enx=i;
		eny=j;
		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1)
			{
				eny++;
				break;
			}
		}
		else
			break;
	}

	if(ct1+ct2-1==k)
		return 2;

	for(i=x,j=y,ct1=0;;j--,i--)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==0)
			{
				stx--;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i++)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==n-1)
			{
				enx++;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 3;
	for(i=x,j=y,ct1=0;;j--,i++)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==n-1)
			{
				stx++;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i--)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==0)
			{
				enx--;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 4;
	return 0;

}
int win2(int a[20][20],int x,int y, int n, int k)
{
	int i,j,ct1,ct2,flag;
	for(i=x,j=y,ct1=0;;j--,i--)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==0)
			{
				stx--;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i++)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==n-1)
			{
				enx++;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 3;
	for(i=x,j=y,ct1=0;;j--,i++)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==n-1)
			{
				stx++;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i--)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==0)
			{
				enx--;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 4;
	return 0;

}
int win3(int a[20][20],int x,int y, int n, int k)
{
	int i,j,ct1,ct2,flag;

	for(i=x,j=y,ct1=0;;j--,i++)
	{
		stx=i;
		sty=j;
		if(a[i][j]==a[x][y])
		{
			ct1++;
			if(j==0||i==n-1)
			{
				stx++;
				sty--;
				break;
			}
		}
		else
			break;
	}

	for(i=x,j=y,ct2=0;;j++,i--)
	{
		enx=i;
		eny=j;

		if(a[i][j]==a[x][y])
		{
			ct2++;
			if(j==n-1||i==0)
			{
				enx--;
				eny++;
				break;
			}
		}
		else
			break;
	}
	if(ct1+ct2-1==k)
		return 4;
	return 0;

}


void dda(int a, int b , int c, int d)
{
	int dx, dy,steps,i,q,cl=7;
	float x,y,m;
	dx=c-a;
	dy=d-b;
	if(as(dy)<as(dx))
		steps=as(dx);
	else
		steps=as(dy);
	x=a;
	y=b;
	for(q=-1;q<=1;q++)
		{
			putpixel(ROUND(x)-q,ROUND(y)+q,cl);
			putpixel(ROUND(x),ROUND(y)+q,cl);
			putpixel(ROUND(x)+q,ROUND(y),cl);
			putpixel(ROUND(x)+q,ROUND(y)+q,cl);
		}

	for(i=0;i<as(steps);i++)
	{
		x=x+dx/(float)steps;
		y=y+dy/(float)steps;
		delay(1);
		for(q=-1;q<=1;q++)
		{
			putpixel(ROUND(x)-q,ROUND(y)+q,cl);
			putpixel(ROUND(x),ROUND(y)+q,cl);
			putpixel(ROUND(x)+q,ROUND(y),cl);
			putpixel(ROUND(x)+q,ROUND(y)+q,cl);
		}

	}
}
void ddaw(int a, int b , int c, int d)
{
	int dx, dy,steps,i,q,cl=7;
	float x,y,m;
	dx=c-a;
	dy=d-b;
	if(as(dy)<as(dx))
		steps=as(dx);
	else
		steps=as(dy);
	x=a;
	y=b;
	for(q=-1;q<=1;q++)
		{
			putpixel(ROUND(x)-q,ROUND(y)+q,cl);
			putpixel(ROUND(x),ROUND(y)+q,cl);
			putpixel(ROUND(x)+q,ROUND(y),cl);
			putpixel(ROUND(x)+q,ROUND(y)+q,cl);
		}

	for(i=0;i<as(steps);i++)
	{
		x=x+dx/(float)steps;
		y=y+dy/(float)steps;
		for(q=-1;q<=1;q++)
		{
			putpixel(ROUND(x)-q,ROUND(y)+q,cl);
			putpixel(ROUND(x),ROUND(y)+q,cl);
			putpixel(ROUND(x)+q,ROUND(y),cl);
			putpixel(ROUND(x)+q,ROUND(y)+q,cl);
		}

	}
}