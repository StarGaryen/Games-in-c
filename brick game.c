/*author StarGaryen*/

#include<stdio.h>
#include<windows.h>
#include<time.h>
#define UR 02
#define UL 00
#define DR 22
#define DL 20
#define RIGHT 100
#define LEFT 97
void draw_box(int i);
void set_box_location();
void remove_box(int i);
void play();
void remove_ball();
void gotoxy(int x,int y);
void draw_boundary();
void exitgame();
void delay(int milliseconds);
void reset();
void hit_platform();
int hit_base();
int hit_wall();
void hit_box();
void remove_platform();
void draw_platform();
struct BOX{
    int x;
    int y;
    int expose;
    int draw;
    }box[64];
struct BALL{
        int x;
        int y;
        int dir;
    }ball={10,13, 22};
struct SCORE{
    int box_hit;
    int saved;
    int lives;
    }score={0,0,5};
struct Base{
    int x;
    int y;
    }platform={16,22};
int main()
{
    reset();
    draw_boundary();
    set_box_location();
    draw_platform();
    play();
    exitgame();
	return 0;
}
void reset()
{
    srand((unsigned)score.box_hit);
    ball.x=rand()%20+ 8;
    ball.y=21;
    ball.dir=0;
    platform.x=ball.x-1;
    platform.y=22;
}
void play()
{
    while(score.box_hit<64)
    {
        draw_ball();
        delay(150);
        remove_ball();
        up_ball_cor();
        hit_base();
        hit_wall();
        hit_platform();
        hit_box();
    }

}
void draw_box(int i)
{
    gotoxy(box[i].x,box[i].y);
    printf("%c%c%c%c",218,194,194,191);
    gotoxy(box[i].x,box[i].y + 1);
    printf("%c%c%c%c",192,193,193,217);
    gotoxy(6,24);
}
void remove_box(int i)
{
     gotoxy(box[i].x,box[i].y);
     printf("    ");
     gotoxy(box[i].x,box[i].y+1);
     printf("    ");
     gotoxy(6,23);
}
void set_box_location()
{
    int box_no;
    for(box_no=0;box_no<64;box_no++)
    {
        box[box_no].x=(box_no%16)*4+7;
        box[box_no].y=(box_no/16)*2+2;
        draw_box(box_no);
        box[box_no].expose=1;
    }
}
void gotoxy(int x,int y)
{
    COORD a;
    a.X=x;
    a.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void draw_boundary()
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
int draw_ball()
{
    gotoxy(ball.x,ball.y);
    printf("%c",15);
}
void remove_ball()
{
    gotoxy(ball.x,ball.y);
    printf(" ");
}
int hit_wall()
{
    int i=0;
    if(ball.x==7)
    {
        ball.dir+=2;
        i++;
    }
    else if (ball.x==70)
    {
        ball.dir-=2;
        i++;
    }
    if(ball.y==2)
    {
        ball.dir+=20;
        i++;
    }
    return i;
}
int hit_base()
{
    if(ball.y==22)
    {
        score.lives--;
        exitgame();
    }
}
int up_ball_cor()
{
    if(ball.dir==UR)
    {
        ball.x++;
        ball.y--;
    }
    else if(ball.dir==UL)
    {
        ball.x--;
        ball.y--;
    }
    else if(ball.dir==DR)
    {
        ball.x++;
        ball.y++;
    }
    else if(ball.dir==DL)
    {
        ball.x--;
        ball.y++;
    }
    else
        printf("/a");
}
void exitgame()
{
    if(score.lives<=0)
    {
        system("cls");
        printf("\n\n\n\t\t Game over.\n\t\tYou hit %d boxes. You saved ball %d times from falling\n\t\tHit any key to exit.....",score.box_hit, score.saved);
        getchar();
        exit(0);
    }
    else if(score.box_hit==64)
    {
        system("cls");
        printf("\n\n\t\tYou won\n\t\tHit any key to exit....");
        getchar();
        exit(0);
    }
    else
    {
        gotoxy(13,13);
        printf("Press enter to continue");
        getchar();
        gotoxy(13,13);
        printf("                                                 ");
        remove_platform();
        reset();
        draw_platform();
        play();
    }
}
void delay(int milliseconds)
{
    long pause;
    char key;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
    {
        now = clock();
        if(kbhit()){
        key=getch();
    if(key==RIGHT && platform.x<=66)
    {
        gotoxy(platform.x,platform.y);
        printf(" ");
        platform.x+=1;
        gotoxy(platform.x + 3,platform.y);
        printf("=");
    }
    else if (key== LEFT && platform.x>=8)
    {
        gotoxy(platform.x + 3,platform.y);
        printf(" ");
        platform.x-=1;
        gotoxy(platform.x,platform.y);
        printf("=");
    }
    }
     if(key==27)
    {
        then=clock();
    }
    }
}
void draw_platform()
{
    gotoxy(platform.x,platform.y);
    printf("====");
}
void remove_platform()
{
    gotoxy(platform.x,platform.y);
    printf("    ");
}
void hit_platform()
{
    int i;
    if(ball.y==21 && ((ball.x== platform.x-1&& ball.dir==22) || ball.x== platform.x  || ball.x==platform.x+1 || ball.x==platform.x+2 || ball.x==platform.x+3 || ( ball.x == platform.x+4 && ball.dir==20)))
    {
        ball.dir=ball.dir-20;
        score.saved++;
    }
}
void hit_box()
{
    int i;
    for(i=63;i>=0;i--)
    {
        if(ball.y==(box[i].y) + 2 && box[i].expose==1 && (ball.dir== 00 || ball.dir==02)&& ((ball.x==(box[i].x)-1&& ball.dir== 02) || ball.x==box[i].x || ball.x==box[i].x+1|| ball.x==(box[i].x) + 2 || ball.x==(box[i].x)+3 || (ball.x==box[i].x+4 && ball.dir==00) ))
        {
            ball.dir+=20;
            remove_box(i);
            box[i].expose=0;
            score.box_hit++;
        }
        else if(ball.y== box[i].y-1 && ball.dir/10==2 && box[i].expose==1 && ((ball.x==box[i].x-1&& ball.dir== 22) || ball.x==box[i].x || ball.x==box[i].x+1|| ball.x==box[i].x + 2 || ball.x==box[i].x+3 || (ball.x==box[i].x+4 && ball.dir==20) ))
        {
            ball.dir-=20;
            remove_box(i);
            box[i].expose=0;
            score.box_hit++;
        }
        else if(ball.x==box[i].x-1 && ball.dir%10==2 && box[i].expose==1 && ((ball.y==box[i].y-1 && ball.dir==22) || ball.y==box[i].y || ball.y==box[i].y+1 || (ball.y==box[i].y+2 && ball.dir == 02)))
        {
           ball.dir-=2;
            remove_box(i);
            box[i].expose=0;
            score.box_hit++;
        }
        else if(ball.x==box[i].x+4 && ball.dir%10==0 && box[i].expose==1 && ((ball.y==box[i].y-1 && ball.dir==20) || ball.y==box[i].y || ball.y==box[i].y+1 || (ball.y==box[i].y+2 && ball.dir ==00 )))
        {
            ball.dir+=2;
            remove_box(i);
            box[i].expose=0;
            score.box_hit++;
        }
    }
}
