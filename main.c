#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int play=0,player=1,boxmax,boxcompall,boxcomp_flag;
char garbage[100];

typedef struct
{
    char name [100];
    int color;
    int n_lines;
    int n_boxes;
} players ;
players p_one, p_two ;


void two_players ()
{
    char temp;

    printf("Enter the Name of Player One :\n");
    fgets(p_one.name,100,stdin);
    p_one.name[ strlen(p_one.name) - 1 ] = 0;
    do
    {
        clrscr();
        printf("Enter a Valid Color of Player One :  \t 1:Blue 2:Green 3:Brown 4:Red\n");
        scanf("%c",&temp);
        fgets(garbage,100,stdin);
        p_one.color=temp-48;
        if (p_one.color==3)
            p_one.color=temp-48+3;
    }
    while (p_one.color!=1 && p_one.color!=2 && p_one.color!=6 && p_one.color!=4);

    clrscr();
    printf("Enter the Name of Player two : \n");
    fgets(p_two.name,100,stdin);
    p_two.name[ strlen(p_two.name) - 1 ] = 0;
    do
    {
        clrscr();
        printf("Enter a Valid Color of Player two :  \t 1:Blue 2:Green 3:Brown 4:Red\n");
        scanf("%c",&temp);
        fgets(garbage,100,stdin);
        p_two.color=temp-48;
        if (p_two.color==3)
            p_two.color=temp-48+3;
    }
    while ( (p_two.color!=1 && p_two.color!=2 && p_two.color!=6 && p_two.color!=4) || p_two.color==p_one.color );

    choosing_grid();
}

void choosing_grid ()
{
    char grid_size_char;
    do
    {
        clrscr();
        printf("Enter Preferred Grid Size from 2 to 8 \tNote: Beginner Size is 2 , Expert Size is 5 \n");
        scanf("%c",&grid_size_char);
        fgets(garbage,100,stdin);
    }
    while ( (grid_size_char < 50) || (grid_size_char > 56) );
    int grid_size_int = grid_size_char - 48 ;

    boxmax = grid_size_int * grid_size_int ;

    //sizing_grid
    int row_num=1+(grid_size_int+1)+(3*grid_size_int);
    int col_num=2+(grid_size_int+1)+(9*grid_size_int);

    //initializing arrays
    char array[row_num][col_num];
    int vals[row_num][col_num];

    //adding dots and spaces and indexes
    int row_index=49, col_index=49;
    for (int i=0 ; i<row_num ; i++)
    {
        for (int j=0 ; j<col_num ; j++)
        {
            if ( (i%4==1) && (j%10==2) )
            {
                array[i][j]=254; //ASCII of dots used
                vals[i][j]=9;
            }
            else if ((i==0)&& (j%10==2))
            {
                array[i][j]=col_index;
                col_index++;
            }
            else if ((j==0)&& (i%4==1))
            {
                array[i][j]=row_index;
                row_index++;
            }
            else
            {
                array[i][j]=' ';
                vals[i][j]=0;
            }
        }
    }

    clrscr();
    print_grid(row_num,col_num,array,vals);
    //the game starts by joining points
    joining_points(row_num,col_num,array,vals) ;
}

void print_grid (int row_num, int col_num, char array[row_num][col_num], int vals[row_num][col_num] )
{
    for (int i=0 ; i<row_num ; i++)
    {
        for (int j=0 ; j<col_num ; j++)
        {
            if ( ((i==0)&& (j%10==2)) || ((j==0)&& (i%4==1)) )
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),5);
                printf("%c",array[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            }
            else
            {
                if (vals[i][j]==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p_one.color);
                    printf("%c",array[i][j]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                }
                else if (vals [i][j]==-1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p_two.color);
                    printf("%c",array[i][j]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                }
                else
                    printf("%c",array[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nScore:\t%s:\t%d\t%s:\t%d\n",p_one.name,p_one.n_boxes,p_two.name,p_two.n_boxes);
    printf("Steps:\t%s:\t%d\t%s:\t%d\n",p_one.name,p_one.n_lines,p_two.name,p_two.n_lines);
    if (!end_check())
    {
        printf("Turn :\t");
        if (player==1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p_one.color);
            printf("%s\n",p_one.name);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        }
        else if (player==-1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p_two.color);
            printf("%s\n",p_two.name);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        }
    }
}

void joining_points (int row_num, int col_num, char array[row_num][col_num], int vals[row_num][col_num])
{
    int last_index = row_num/3 ;
    int i,j,a,b,c,d,rowdiff,coldiff,p1x,p1y,p2x,p2y,error;
    char aa,bb,cc,dd;

    do
    {
        play=0;
        error=0;
        printf("\nPlease enter the required points:");
        scanf(" %c",&aa);
        scanf(" %c",&bb);
        scanf(" %c",&cc);
        scanf(" %c",&dd);
        fgets(garbage,100,stdin);
        a = aa-48;
        b = bb-48;
        c = cc-48;
        d = dd-48;

        if (a<1 || a>last_index || b<1 || b>last_index || c<1 || c>last_index || d<1 || d>last_index)
        {
            printf("\nError: these points do not exist\n");
            error=1;
        }
        else
        {
            rowdiff = abs(a-c);
            coldiff = abs(b-d);
            if (rowdiff==0)
            {
                if (coldiff==0)
                {
                    printf("\nError: cannot enter the same point twice\n");
                    error=1;
                }
                else if (coldiff == 1)
                {
                    p1y = (a-1)*4+1;
                    p1x = (b-1)*10+2;
                    p2y = (c-1)*4+1;
                    p2x = (d-1)*10+2;

                    if (p2x<p1x)
                    {
                        p1x = p1x ^ p2x;
                        p2x = p1x ^ p2x;
                        p1x = p1x ^ p2x;
                    }
                    if (array[p1y][p1x+5]==' ')
                    {
                        for (i=p1x+2; i<p2x-1; i++)
                        {
                            array[p1y][i]=196;// ASCII of used horizontal line
                            vals[p1y][i]=player;
                            play=1;
                        }
                    }
                    else
                    {
                        printf("\nError: there is a line already drawn in this position\n");
                        error=1;
                    }
                }
                else
                {
                    printf("\nError: cannot join these two points\n");
                    error=1;
                }
            }
            else if (coldiff==0)
            {
                if (rowdiff==0)
                {
                    printf("\nError: cannot enter the same point twice\n");
                    error=1;
                }
                else if (rowdiff == 1)
                {
                    p1y = (a-1)*4+1;
                    p1x = (b-1)*10+2;
                    p2y = (c-1)*4+1;
                    p2x = (d-1)*10+2;

                    if (p2y<p1y)
                    {
                        p1y = p1y ^ p2y;
                        p2y = p1y ^ p2y;
                        p1y = p1y ^ p2y;
                    }
                    if (array[p1y+2][p1x]==' ')
                    {
                        for (i=p1y+1; i<p2y; i++)
                        {
                            array[i][p1x]=179;// ASCII of used vertical line
                            vals[i][p1x]=player;
                            play=1;
                        }
                    }
                    else
                    {
                        printf("\nError: there is a line already drawn in this position\n");
                        error=1;
                    }
                }
                else
                {
                    printf("\nError: cannot join these two points\n");
                    error=1;
                }

            }
            else
            {
                printf("\nError: cannot join these two points\n");
                error=1;
            }
        }

        check_box(row_num,col_num,player,array,vals);
        check_chain(row_num,col_num,player,array,vals); //checking if the closed box (if there) closed a chain too or not

        if (!error)
        {
            if(player==1)
                p_one.n_lines++;
            else
                p_two.n_lines++;

            if (!boxcomp_flag)
            {
                play=1;
                player=-player;
            }

            clrscr();
            print_grid(row_num,col_num,array,vals);
        }

    }
    while(!end_check());
    winner();
}

int end_check()
{
    if(boxcompall==boxmax)
        return 1;
    else
        return 0;
}

void check_box(int row_num, int col_num,int player,char array[row_num][col_num],int vals[row_num][col_num])
{
    int i,j,k,m;
    boxcomp_flag=0;
    for(i=3; i<row_num; i+=4)
    {
        for(j=7; j<col_num; j+=10)
        {
            int z =abs(vals[i-2][j])+abs(vals[i+2][j])+abs(vals[i][j-5])+abs(vals[i][j+5]);
            if (z==4&&vals[i+1][j]==0)
            {
                boxcomp_flag++;
                vals[i+1][j]=player;

                if(player==1)
                {
                    p_one.n_boxes++;
                    //assigning the borders
                    for (k=j-3 ; k<=j+3 ; k++)
                    {
                        vals[i-2][k]=player;
                        vals[i+2][k]=player;
                    }
                    for (k=i-1 ; k<=i+1 ; k++)
                    {
                        vals[k][j-5]=player;
                        vals[k][j+5]=player;
                    }

                    // shading the box
                    for (k=i-1 ; k<=i+1 ; k++)
                    {
                        for (m=j-3 ; m<=j+3 ; m++)
                        {
                            array[k][m]=219; //ASCII of shade
                            vals[k][m]=player;
                        }
                    }
                }
                else if (player==-1)
                {
                    p_two.n_boxes++;
                    //assigning the borders
                    for (k=j-3 ; k<=j+3 ; k++)
                    {
                        vals[i-2][k]=player;
                        vals[i+2][k]=player;
                    }
                    for (k=i-1 ; k<=i+1 ; k++)
                    {
                        vals[k][j-5]=player;
                        vals[k][j+5]=player;
                    }

                    // shading the box
                    for (k=i-1 ; k<=i+1 ; k++)
                    {
                        for (m=j-3 ; m<=j+3 ; m++)
                        {
                            array[k][m]=219; //ASCII of shade
                            vals[k][m]=player;
                        }
                    }
                }
            }
        }
    }
    boxcompall+=boxcomp_flag;
}

void check_chain (int row_num, int col_num,int player,char array[row_num][col_num],int vals[row_num][col_num])
{
    int i,j,k,m;

    //checking horizontal chains
    for (i=3 ; i<row_num ; i+=4)
    {
        for(j=2 ; j<col_num ; j+=10)
        {
            if ( (vals[i][j-2]!=0) && (vals[i][j+2]!=0) && (vals[i][j-2] == vals[i][j+2]) && (array[i][j] != array[i][j+2]) )
            {
                for (k=i-1 ; k<=i+1 ; k++)
                {
                    for (m=j-1 ; m<=j+1 ; m++)
                    {
                        vals[k][m]=player;
                        array[k][m]=219;
                    }
                }
            }
        }
    }

    //checking vertical chain
    for (i=1 ; i<row_num ; i+=4)
    {
        for(j=7 ; j<col_num ; j+=10)
        {
            if ( (vals[i-1][j]!=0) && (vals[i+1][j]!=0) && (vals[i-1][j] == vals[i+1][j]) && (array[i][j] != array[i+1][j]) )
            {
                for (m=j-3 ; m<=j+3 ; m++)
                {
                    vals[i][m]=player;
                    array[i][m]=219;
                }
            }
        }
    }
}

void winner()
{
    if(p_one.n_boxes > p_two.n_boxes)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p_one.color);
        printf("The WINNER IS\t %s",p_one.name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    }
    else if (p_two.n_boxes > p_one.n_boxes)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p_two.color);
        printf("The WINNER IS\t %s",p_two.name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    }
    else
        printf("\t\tDRAW");
}

void clrscr()
{
    system("@cls||clear");
}


int main()
{
    two_players();
    return 0;
}
