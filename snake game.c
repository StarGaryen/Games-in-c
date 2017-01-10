/*author JON SNOW*/
#include<time.h>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<unistd.h>
#define RIGHT 100
#define LEFT 97
#define UP 119
#define DOWN 115
int speed =1;
char key=77;
int lenght=2;
int current_position=1;
int total_bends=1;
int life=3;
struct position
{
    int x;
    int y;
};
char direction;
struct position head,body_points[50],bend_location[100],food_location;
void instructions();
void draw_box();
void gotoxy(int ,int);
void heart();
void draw();
void update();
void up();
void down();
void right();
void left();
void update_rem_body();
void wall_hit();
void reset();
void delay(int);
void speedselect();
void exitgame();
int main()
{
    instructions();
    speedselect();
    reset();
    system("cls");
    draw_box();
    draw();
    update();
}
void instructions()
{
    gotoxy(10,7);
    printf("you know what to do.");
    gotoxy(10,6);
    printf("Press any key to continue");
    if(getchar()== 27)
        exit(0);
    fflush(stdin);
}
void draw_box()
{
    int i;
	for(i=6;i<=70;i++)
    {
        gotoxy(i,3);
        printf("%c",220);
        gotoxy(i,20);
        printf("%c",223);
    }
    for(i=4;i<20;i++)
    {
        gotoxy(6,i);
        printf("%c",221);
        gotoxy(70,i);
        printf("%c",222);
    }
    gotoxy(3,21);
}
void gotoxy(int x,int y)
{
    COORD a;
    a.X=x;
    a.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void heart()
{
    int i=1;
    if(head.x==food_location.x && head.y == food_location.y)
    {
        lenght++;
        i=rand()%70;
        if(i<6)
            i+=10;
        food_location.x=i;
        i=rand()%20;
        if(i<3)
            i+=6;
        food_location.y=i;
    }
}
void draw_snake()
{
    int i;
    gotoxy(head.x,head.y);
    printf("%c",16);
    for(i=0;i<lenght;i++)
    {
        if(head.x==body_points[i].x && body_points[i].y == head.y)
        {
            exitgame();
        }
        else
        {
            gotoxy(body_points[i].x,body_points[i].y);
            printf("%c",16);
        }
    }
}
void remove_snake()
{
    int i;
    gotoxy(head.x,head.y);
    printf(" ");
    for(i=0;i<lenght;i++)
    {
        gotoxy(body_points[i].x,body_points[i].y);
        printf(" ");
    }
}
void draw()
{
    int i;
    heart();
    gotoxy(food_location.x,food_location.y);
    printf("%c",3);
    gotoxy(6,1);
    printf("YOUR scanty SCORE : %d" ,lenght-2);
    gotoxy(6,22);
    printf("Lives : %d",life);
}
void update()
{ int i;
    do
    {
            current_position=1;
        if (direction ==UP)
            up();
        else if (direction==DOWN)
            down();
        else if(direction ==RIGHT)
            right();
        else if(direction== LEFT)
            left();
        wall_hit();
        draw();
        draw_snake();
        delay(1000/(speed*7));
        remove_snake();
        fflush(stdin);
    }while(!kbhit());
    key=getch();
    for(i=0;i<lenght;i++)
    {
        body_points[i].x=0;
        body_points[i].y=0;
    }
    if((direction==RIGHT || direction==LEFT) && ( key==UP || key==DOWN ))
    {
        direction=key;
        total_bends++;
        bend_location[total_bends-1]=head;
    }
     else if((direction==UP || direction == DOWN )&& (key== LEFT || key==RIGHT ))
    {
        direction=key;
        total_bends++;
        bend_location[total_bends-1]=head;
    }
     else
     {
            gotoxy(6,22);
            printf("\a%d",key);
     }
    update();
}
void up()
{
    head.y--;
    while(current_position<=lenght && (head.y + current_position) < bend_location[total_bends-1].y)
    {
        body_points[current_position-1].x= head.x;
        body_points[current_position-1].y=head.y + current_position;
        current_position++;
    }
    update_rem_body();
}
void down()
{
    head.y++;
    while(current_position<= lenght && (head.y - current_position) > bend_location[total_bends-1].y)
    {
        body_points[current_position-1].x= head.x;
        body_points[current_position-1].y=head.y -current_position ;
        current_position++;
    }
    update_rem_body();
}
void right()
{
    head.x++;
    while(current_position<=lenght && (head.x-current_position)>bend_location[total_bends-1].x)
    {
        body_points[current_position-1].x=head.x-current_position;
        body_points[current_position-1].y=head.y;
        current_position++;
    }
    update_rem_body();
}
void left()
{
    head.x--;
    while(current_position<=lenght && (head.x+current_position)<bend_location[total_bends-1].x)
    {
        body_points[current_position-1].x=head.x+current_position;
        body_points[current_position-1].y=head.y;
        current_position++;
    }
    update_rem_body();
}
void update_rem_body()
{
    int i ,q;
    for(i=total_bends-1;i >0 && current_position <= lenght;i--)
    {
        if(bend_location[i].x==bend_location[i-1].x &&  bend_location[i].y>bend_location[i-1].y)
        {
            for(q=1; bend_location[i].y- bend_location[i-1].y >= q && current_position<=lenght;q++)
            {
                body_points[current_position-1].x = bend_location[i].x;
                body_points[current_position-1].y=bend_location[i].y - q;
                current_position++;
            }
        }
        else if(bend_location[i].x==bend_location[i-1].x &&  bend_location[i].y<bend_location[i-1].y )
        {
            for(q=1; -(bend_location[i].y- bend_location[i-1].y )>= q && current_position<= lenght;q++)
            {
                body_points[current_position-1].x = bend_location[i].x;
                body_points[current_position-1].y=bend_location[i].y + q;
                current_position++;
            }
        }
        else if(bend_location[i].y==bend_location[i-1].y &&  bend_location[i].x >bend_location[i-1].x)
        {
            for(q=1; bend_location[i].x- bend_location[i-1].x >= q && current_position<=lenght;q++)
            {
                body_points[current_position-1].x = bend_location[i].x -q;
                body_points[current_position-1].y=bend_location[i].y ;
                current_position++;
            }
        }
        else if(bend_location[i].y==bend_location[i-1].y &&  bend_location[i].x<bend_location[i-1].x)
        {
            for(q=1;bend_location[i-1].x- bend_location[i].x >= q && current_position<=lenght;q++)
            {
                body_points[current_position-1].x = bend_location[i].x+q;
                body_points[current_position-1].y=bend_location[i].y ;
                current_position++;
            }
        }
        else
            {
            printf("cant set points");
            }
    }
}
void wall_hit()
{
    if(head.x==6 || head.x==70 || head.y==3 || head. y == 20)
       exitgame();

}
void reset()
{
    head.x=13;
    head.y=5;
    direction=RIGHT;
    food_location.x=16;
    food_location.y=5;
    body_points[0].x=12;
    body_points[0].y=5;
    body_points[1].x=11;
    body_points[1].y=5;
    bend_location[0].x=11;
    bend_location[0].y=5;
    lenght =2;
    total_bends=1;
}
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
void exitgame()
{
    life--;
    system("cls");
    gotoxy(10,5);
    printf("You Scored : %d \t\t Lives Remaining : %d",lenght-2,life);
    if(life>0)
        main();
    else
    {
        gotoxy(10,6);
        printf("press any key to exit ..");
        getchar();
        exit(0);
    }
}
void speedselect()
{
    system("cls");
    printf("Choose Difficulty\n1. EASY\n2. MEDIUM\n3. HARD\n4. I'm a  PRO%c%c%c",1,2,1);
    scanf("%d",&speed);
    fflush(stdin);
}
