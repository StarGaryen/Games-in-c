/*author JON SNOW*/
#include<time.h>
#include<stdio.h>
#include<windows.h>
#define DOWN 80
#define UR 02
#define UL 00
#define DR 22
#define DL 20
void update_ball_cord();
void gotoxy(short X,short Y);//set cursor position to (X,Y)
void draw_wall(); //draw outer wall
void reset();
void play();
void draw_ball(BOOL a); //draw ball if a=TRUE else removes ball
void draw_plate(short i);// digit on ones place to decide draw or remove and digit on tens place to decide plate number
void wall_hit();// check for ball hit on upper and lower walls
void back_hit(); // check for ball hit on side walls
void plate_hit();//cheak for ball hit on both plateforms
void delay(int miliseconds);
void lives();
void exitgame();
COORD plate[2]; //plate[0]==> user1 platform and plate[1]==> user2 platform

struct BALL{
        COORD coordinates;
        int dir;
    }ball;
struct Score{
	short saves;
	short lives;
	}score[2]={{0,3},{0,3}};
int main()
{
	draw_wall();
	lives();
	ball.dir=UR;
	reset();
	draw_plate(01);
	draw_plate(11);
	play();
	exitgame();
	return 0;
}
void update_ball_cord()
{
    if(ball.dir==UR)
    {
        ball.coordinates.X++;
        ball.coordinates.Y--;
    }
    else if(ball.dir==UL)
    {
        ball.coordinates.X--;
        ball.coordinates.Y--;
    }
    else if(ball.dir==DR)
    {
        ball.coordinates.X++;
        ball.coordinates.Y++;
    }
    else if(ball.dir==DL)
    {
        ball.coordinates.X--;
        ball.coordinates.Y++;
    }
    else
        printf("/a");
}
void gotoxy(short x,short y)
{
    COORD a;
    a.X=x;
    a.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void draw_wall()
{
    int i;
	for(i=6;i<=71;i++)
    {
        gotoxy(i,1);
        printf("%c",220);
        gotoxy(i,23);
        printf("%c",223);
    }
    for(i=2;i<23;i++)
    {
        gotoxy(6,i);
        printf("%c",221);
        gotoxy(71,i);
        printf("%c",222);
    }
    gotoxy(6,24);
}
void reset()
{
	srand((unsigned) ball.coordinates.Y);
	ball.coordinates.X=38;
	ball.coordinates.Y=rand()%15 + 5;
	plate[0].X=8;
	plate[1].X=69;
	plate[0].Y=plate[1].Y=ball.coordinates.Y;
}
void play()
{
    do{
        wall_hit();
        back_hit();
        plate_hit();
        draw_ball(TRUE);
        delay(80);
        draw_ball(FALSE);
        update_ball_cord();
    }while(TRUE);

}
void draw_ball(BOOL a)
{
    gotoxy(ball.coordinates.X,ball.coordinates.Y);
    if(a)
    printf("%c",15);
    else
    	printf(" ");
}
void draw_plate(short i)
{
	char k;
	short j;
	if(i%10)
		k='|';
	else
		k=' ';
	for(j=0;j<4;j++)
	{
		gotoxy(plate[i/10].X,plate[i/10].Y+ j);
		printf("%c",k);
	}
}
void wall_hit()
{
	if(ball.coordinates.Y==2)
		ball.dir+=20;
	else if(ball.coordinates.Y==22)
		ball.dir-=20;
}
void back_hit()
{
	if(ball.coordinates.X==8)
	{
		score[0].lives--;
		lives();
		exitgame();
	}
	else if (ball.coordinates.X==69)
	{
		score[1].lives--;
		lives();
		exitgame();
	}
}
void plate_hit()
{
	if(ball.coordinates.X==plate[0].X+1 && (ball.coordinates.Y==plate[0].Y+3 || ball.coordinates.Y==plate[0].Y || ball.coordinates.Y==plate[0].Y+1 || ball.coordinates.Y==plate[0].Y+2 ||((ball.coordinates.Y==plate[0].Y-1)&& ball.dir == 20) || ((ball.coordinates.Y==plate[0].Y+4)&& ball.dir == 0)))
	{
		ball.dir+=2;
		score[0].saves++;
	}
	else if(ball.coordinates.X==plate[1].X-1 && (ball.coordinates.Y==plate[1].Y+3 || ball.coordinates.Y==plate[1].Y || ball.coordinates.Y==plate[1].Y+1 || ball.coordinates.Y==plate[1].Y+2 ||((ball.coordinates.Y==plate[1].Y-1)&& ball.dir == 22) || ((ball.coordinates.Y==plate[1].Y+4)&& ball.dir == 2)))
	{
		ball.dir-=2;
		score[1].saves++;
	}
}
void delay(int miliseconds)
{
    clock_t now,then;
    int pause;
    char key;
    pause = miliseconds*(CLOCKS_PER_SEC/1000);
    now=then=clock();
    while(now-then < pause)
    {
        now=clock();
        if(kbhit())
        {
            key=getch();
            if(key=='o' && plate[1].Y>2)
            {
                gotoxy(plate[1].X,plate[1].Y+3);
                printf(" ");
                plate[1].Y--;
                gotoxy(plate[1].X,plate[1].Y);
                printf("|");
            }
            else if(key=='l' && plate[1].Y<19)
            {
                gotoxy(plate[1].X,plate[1].Y);
                printf(" ");
                plate[1].Y++;
                gotoxy(plate[1].X,plate[1].Y+3);
                printf("|");
            }
            else if(key=='w' && plate[0].Y>2)
            {
                gotoxy(plate[0].X,plate[0].Y+3);
                printf(" ");
                plate[0].Y--;
                gotoxy(plate[0].X,plate[0].Y);
                printf("|");
            }
            else if(key=='s' && plate[0].Y<19)
            {
                gotoxy(plate[0].X,plate[0].Y);
                printf(" ");
                plate[0].Y++;
                gotoxy(plate[0].X,plate[0].Y+3);
                printf("|");
            }
            else
            {
                printf("\a");
            }
        }
    }
}
void lives()
{
    gotoxy(1,10);
    printf("Lives\n  %d",score[0].lives);
    gotoxy(72,10);
    printf("Lives");
    gotoxy(75,11);
    printf("%d",score[1].lives);
}
void exitgame()
{
    if(score[0].lives==0)
    {
        system("cls");
        printf("player 2 won\npress enter to exit");
        getchar();
        exit(0);
    }
    else if(score[1].lives==0)
    {
        system("cls");
        printf("player 2 won\npress enter to exit");
        getchar();
        exit(0);
    }
    else
    {
        draw_plate(00);
        draw_plate(10);
        reset();
        draw_plate(01);
        draw_plate(11);

        play();
    }


}
