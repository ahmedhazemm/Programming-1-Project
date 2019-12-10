#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>

//Global Variables List:
//boxmax : total number of boxes that can be completed in the grid (equal to nxn).
//boxcompall : total number of boxes that have been completed during the current game (compared with boxmax to check if the game has ended).
//boxcomp : number of boxes completed during a player's turn (used to detect whether the same player should play again or if it should be the other player's turn).
//countstep1 : total number of accepted moves/lines that player 1 has made throughout the current game.
//countstep2 : total number of accepted moves/lines that player 2 has made throughout the current game.
//countboxcom1 : total number of boxes that have been completed by player 1 throughout the current game.
//countboxcom2 : total number of boxes that have been completed by player 2 throughout the current game.
//play : flag that has an initial value of '0' once it is a player's turn to move and is set to 1 once the player has made an accepted move/line.
//nameA : array that stores the name of player 1.
//nameB : array that stores the name of player 2.

int boxmax,boxcompall,boxcomp,countstep1,countstep2,countboxcom1,countboxcom2,play;
char nameA[100],nameB[100];

//Main Menu function which scans char mmc from the user to navigate to the required section (incorrect input resets the main menu).
//clrscr : function that clears all of the text in the command window (defined below).

void main_menu()
{
    clrscr();
    printf("Welcome to Dots and Boxes\n\n\n");
    char mmc;
    printf("1:Single Player\n");
    printf("2:Multi player\n");
    printf("3:Load Game\n");
    printf("4:Scoreboard\n");
    scanf("%c",&mmc);
    switch (mmc)
    {
    case '1':

        break;
    case '2':
        choose_grid();
        break;
    case '3':

        break;
    case '4':

        break;
    default :
        main_menu();
    }

}

void choose_grid()
{
    char c;
    //Let user choose either a 2x2 grid by entering 'b' or a 5x5 grid by entering 'e' (choosing value for char c).
    //User can also choose 'm' to return to the Main Menu.
    //If user enters any other input then display an error message and ask for input again.
    do
    {
        clrscr();
        printf("Please enter (b) for Beginner, (e) for Expert or (m) for Main Menu\n");
        scanf(" %c",&c);
        if (c!='b' && c!='e' && c!='m')
        {
            printf("Error: incorrect input format\n");
        }
        if (c=='m')
            main_menu();
    }
    while(c!='b' && c!='e' && c!='m');
    //Initialize the number of rows and columns in the 2D array that holds the game interface
    //then determine the exact values depending on the users choice.
    //Also determines the value of boxmax.
    int rownum=0,colnum=0;
    if (c=='b')
    {
        rownum = 4+(1*3)+1;
        colnum = 7+(1*6)+1;
        boxmax = 4;
    }
    else if (c=='e')
    {
        rownum = 4+(4*3)+1;
        colnum = 7+(4*6)+1;
        boxmax = 25;
    }
    //Create two 2D arrays with the required dimensions depending on the size of the grid that the user chose.
    //arr : array that stores the characters that will be displayed on grid ( dots,lines,boxes and row and column numbers for each point (coordinates) ).
    //vals : array that stores integer values corresponding to each character in the arr array
    //meaning of the values in the initial vals matrix : ( '9' for dots, '0' for spaces and dot coordinates (row and column numbers) ).
    //Then clear the display and request the names of player 1 and player 2.
    //Then clear the display again and call the 'create_grid' function sending the parameters for row number, column number, arr array location(address of first value),
    //char c, vals array location (address of first value), name of player 1, name of player 2.

    int arr[rownum][colnum];
    int vals[rownum][colnum];
    clrscr();
    scan_player_name(nameA,nameB);
    clrscr();
    create_grid(rownum,colnum,arr,c,vals,nameA,nameB);
}

void create_grid(int y, int x, char arr[y][x],char c,int vals[y][x],char nameA[100],char nameB[100])
{
    //player : flag that has a value of '1' when it is player 1's turn and value of '-1' when it is player 2's turn (initially set to '-1' as it is
    //swapped at the beginning of each turn so for the first turn it is swapped from -1 to 1 making it player 1's turn).
    //boxcompall : global variable defined above. At the start of each game it has an initial value of '0' (total number of boxes completed by any player).
    //countboxcom1 : global variable defined above. At the start of each game it has an initial value of '0' (total number of boxes completed by player 1).
    //countboxcom2 : global variable defined above. At the start of each game it has an initial value of '0' (total number of boxes completed by player 2).
    //countstep1 : global variable defined above. At the start of each game it has an initial value of '0' (total number of accepted lines/moves made by player 1).
    //countstep2 : global variable defined above. At the start of each game it has an initial value of '0' (total number of accepted lines/moves made by player 2).


    int i,j,player=-1,play=0;
    boxcompall=0;
    countboxcom1=0;
    countboxcom2=0;
    countstep1=0;
    countstep2=0;

    //254 is the ASCII code for the dots used in the interface.
    //49 is the ASCII code for the number '1' to be used to write down indexes for rows and columns
    //to show the coordinates of each dot in the grid.
    char point=254;
    char gridindexrow=49,gridindexcol=49;
    //Depending on the index, assign a value to the specific index in the arrays.
    //For array arr : a character is assigned to each index depending on what is to be printed on screen.
    //For array vals : an integer is assigned depending on the whether is a dot (value 9) or space(value '0').
    for (i=0; i<y; i++)
    {
        for (j=0; j<x; j++)
        {
            if (i==0)
            {
                if (j%6==1)
                {
                    arr[i][j]=gridindexrow++;
                    vals[i][j]=0;
                }
                else
                {
                    arr[i][j]=' ';
                    vals[i][j]=0;
                }
            }
            else if (j==0)
            {
                if (i%3==1)
                {
                    arr[i][j]=gridindexcol++;
                    vals[i][j]=0;
                }
                else
                {
                    arr[i][j]=' ';
                    vals[i][j]=0;
                }
            }
            else if(i%3==1)
            {
                if (j%6==1)
                {
                    arr[i][j]=point;
                    vals[i][j]=9;
                }
                else
                {
                    arr[i][j]=' ';
                    vals[i][j]=0;
                }
            }
            else
            {
                arr[i][j]=' ';
                vals[i][j]=0;
            }
        }

    }
    // Print the newly created grid on the screen with the appropriate colors for each element in the array.
    for (i=0; i<y; i++)
    {
        for (j=0; j<x; j++)
        {
            if (i==0)
            {
                if (j%6==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                    printf("%c",arr[i][j]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                }
                else
                {
                    printf("%c",arr[i][j]);
                }

            }
            else if (j==0)
            {
                if (i%3==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                    printf("%c",arr[i][j]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                }
                else
                {
                    printf("%c",arr[i][j]);
                }
            }
            else
            {
                printf("%c",arr[i][j]);
            }
        }
        printf("\n");
    }
    //Print the score and number of steps for each player.
    printf("\nScore:\t%s:\t%d\t%s:\t%d\n",nameA,countboxcom1,nameB,countboxcom2);
    printf("Steps:\t%s:\t%d\t%s:\t%d\n",nameA,countstep1,nameB,countstep2);

    //Do while loop:
    //Change player turn (after player=-player, initial value of player is '1').
    //Call the function 'join_grid' while sending it the parameters for row number(y), column number(x), arr array
    //location, char 'c' which indicates the size of the grid that the user chose, vals array location, player flag which indicates whether it is player 1's turn (1)
    //or player 2's turn (-1), player 1's name, player 2's name.
    //end_check : function that checks if the game has ended
    //While end_check=0 (game has not ended),continue to execute the loop.

    do
    {
        player=-player;
        join_grid(y,x,arr,c,vals,player,nameA,nameB);
    }
    while(!end_check());

    //Once the game has ended, call the 'winner' function which displays which player won or if the game was a draw.
    winner();
}

void join_grid(int y, int x, char arr[y][x],char t,int vals[y][x],int player,char nameA[100],char nameB[100])
{
    int i,j,a,b,c,d,rowdiff,coldiff,p1x,p1y,p2x,p2y;
    int lastindex;

    //196 and 179 are the ASCII codes for the characters used to draw lines in the game horizontally
    //or vertically respectively.
    char rowline = 196, colline = 179, aa, bb, cc, dd;
    //If the user chose 'b' then the largest row and column value for a dot is 3,3.
    //If the user chose 'e' then the largest row and column value for a dot is 6,6.
    if (t=='b')
    {
        lastindex=3;
    }
    else if (t=='e')
    {
        lastindex=6;
    }

    //Do while loop of game (condition at the bottom of the 'join_grid' function).
    do
    {
        //play : global variable (defined above) that has an initial value of '0' meaning that the player has not made a move yet
        //the value changes to '1' if the player has made an accepted move/line.
        //player : if it is equal to '1' then it is player 1's turn, else it is player 2's turn so the player who is going to play the next move is indicated
        //with the appropriate color.
        play=0;
        if (player==1)
        {
            printf("\nTurn:\t");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
            printf("%s\n",nameA);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        }
        else
        {
            printf("\nTurn:\t");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
            printf("%s\n",nameB);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        }

        //Scan the coordinates of the two points to be joined as characters then subtract 48 from their ASCII
        //codes and store them as integers (e.g: if user enters '1' for char aa, the ASCII code for '1' is 49
        //so we subtract 48 to get 1 then store in integer a).
        //This is done to avoid crashing the program if (scanf) was used to scan an integer and the user entered
        //a character that is not numeric.
        printf("\nPlease enter the required points:");
        scanf(" %c",&aa);
        scanf(" %c",&bb);
        scanf(" %c",&cc);
        scanf(" %c",&dd);
        a = aa-48, b = bb-48;
        c = cc-48;
        d = dd-48;

        //If the coordinates of the points were outside the limits of the grid then display an error message.
        if (a<1 || a>lastindex || b<1 || b>lastindex || c<1 || c>lastindex || d<1 || d>lastindex)
        {
            printf("\nError: these points do not exist\n");
        }
        //Calculate difference in rows and difference in columns and square the values in case the user enter the
        //coordinates of a dot which has a higher row or column index first.
        //Then check for possible errors such as: entering the same point twice or entering points
        //that are not directly adjacent to each other horizontally or vertically.
        //If an accepted move/line is made, set the value of the indices in the vals array to the player variable value ('1' for player 1, '-1' for player 2)
        //and set variable play to '1' (meaning that the current player has made a move/line).
        else
        {
            rowdiff = (a-c)*(a-c);
            coldiff = (b-d)*(b-d);
            if (rowdiff==0)
            {
                if (coldiff==0)
                {
                    printf("\nError: cannot enter the same point twice\n");
                }
                else if (coldiff == 1)
                {
                    p1y = (a-1)*3+1;
                    p1x = (b-1)*6+1;
                    p2y = (c-1)*3+1;
                    p2x = (d-1)*6+1;

                    if (p2x<p1x)
                    {
                        p1x = p1x ^ p2x;
                        p2x = p1x ^ p2x;
                        p1x = p1x ^ p2x;
                    }
                    if (arr[p1y][p1x+2]!=rowline)
                    {
                        for (i=p1x+2; i<p2x-1; i++)
                        {
                            arr[p1y][i]=rowline;
                            vals[p1y][i]=player;
                            play=1;
                        }
                    }
                    else
                    {
                        printf("\nError: there is a line already drawn in this position\n");
                    }
                }
                else
                {
                    printf("\nError: cannot join these two points\n");
                }
            }
            else if (coldiff==0)
            {
                if (rowdiff==0)
                {
                    printf("\nError: cannot enter the same point twice\n");
                }
                else if (rowdiff == 1)
                {
                    p1y = (a-1)*3+1;
                    p1x = (b-1)*6+1;
                    p2y = (c-1)*3+1;
                    p2x = (d-1)*6+1;
                    if (p2y<p1y)
                    {
                        p1y = p1y ^ p2y;
                        p2y = p1y ^ p2y;
                        p1y = p1y ^ p2y;
                    }
                    if (arr[p1y+1][p1x]!=colline)
                    {
                        for (i=p1y+1; i<p2y; i++)
                        {
                            arr[i][p1x]=colline;
                            vals[i][p1x]=player;
                            play=1;
                        }
                    }
                    else
                    {
                        printf("\nError: there is a line already drawn in this position\n");
                    }
                }
                else
                {
                    printf("\nError: cannot join these two points\n");
                }

            }
            else
            {
                printf("\nError: cannot join these two points\n");
            }
        }


        //Check if a box has been completed (closed) after the latest move/line by calling the 'check_box' function with parameter for row number(y), column number(x),
        //player (whose turn it was during the latest move), vals array location.
        check_box(y,x,player,vals);
        // If the move/line was accepted (play changed from '0' to '1'), then clear the display and print the grid after the latest move with appropriate colors.
        if(play==1)
        {
            clrscr();
            for (i=0; i<y; i++)
            {
                for (j=0; j<x; j++)
                {
                    if (i==0)
                    {
                        if (j%6==1)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                            printf("%c",arr[i][j]);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        }
                        else
                        {
                            printf("%c",arr[i][j]);
                        }

                    }
                    else if (j==0)
                    {
                        if (i%3==1)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                            printf("%c",arr[i][j]);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        }
                        else
                        {
                            printf("%c",arr[i][j]);
                        }
                    }
                    else if (i!=0&&j!=0&&(i%3!=1||j%6!=1))
                    {
                        if(vals[i][j]==4)
                        {
                            if(vals[i+1][j]==1)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                                arr[i][j]=nameA[0];
                                printf("%c",arr[i][j]);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                            }
                            else if (vals[i+1][j]==-1)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                                arr[i][j]=nameB[0];
                                printf("%c",arr[i][j]);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                            }
                        }
                        else if (vals[i][j]==1)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                            printf("%c",arr[i][j]);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        }

                        else if (vals[i][j]==-1)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                            printf("%c",arr[i][j]);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        }
                        else
                        {
                            printf("%c",arr[i][j]);
                        }
                    }
                    else
                    {
                        printf("%c",arr[i][j]);
                    }
                }
                printf("\n");
            }
            //If the move/line was accepted (play changed from '0' to '1'), then check the player variable to see whose turn it was then increase the variable
            //indicating how many steps were played by that player (countstep1 for player 1, countstep2 for player 2).
            if(play==1)
            {
                if(player==1)
                {
                    countstep1++;
                }
                else if (player==-1)
                {
                    countstep2++;
                }
            }
            //Print the score and number of steps.
            printf("\nScore:\t%s:\t%d\t%s:\t%d\n",nameA,countboxcom1,nameB,countboxcom2);
            printf("Steps:\t%s:\t%d\t%s:\t%d\n",nameA,countstep1,nameB,countstep2);
        }
    }
    while((play==0||boxcomp!=0)&&!end_check());
    //The condition of the loop is that either [the play variable is equal to '0' (move/line was not accepted so the turn does switch over the the other player)
    //OR the boxcomp variable is not equal to '0' (at least one box was completed this turn so the current player gets another move]
    //AND the game didn't end (if the game ends, then the condition is false to avoid a player getting a turn after all boxes were completed and the game has ended)
    //by checking if the 'end_check' function returns '1' (game ended) or '0' (game has not ended).
}

//'check_box' function checks whether a box has been completed after an accepted move/line was made.
void check_box(int y, int x,int player,int vals[y][x])
{
    int i,j;
    //Set the value of the boxcomp variable to '0' as it is used the indicate the number of boxes completed after a single move.
    boxcomp=0;

    //The specified indices (starting with i=4 and j=6 where i is incremented by 3 and j is incremented by 6) in the vals array hold the value of the number of
    //lines made for each box and is calculated by adding the absolute values of the values stored in the indices specified which contain either '1' or '-1'.
    //Once the sum is equal to '4', the box is marked as complete. The value stored in the index [i+1][j] is then checked to make sure that this box was not already
    //completed in a previous term. If vals[i+1][j] is equal to '0', then this box was completed after the latest move/line so it's value is set to the
    //player value ('1' for player 1, '-1' for player 2) to mark that the box was completed by the specified player.
    //This means that during the checking of the sum vals[i][j], if the value is equal to '4' but vals[i+1][j] was not equal to '0' , this indicates that this box is
    //complete but it was already claimed by a player (avoid awarding boxes completed by one player to the other player).
    //This is also done to determine the appropriate color for the completed box.
    //The boxcomp variable is then incremented to indicate that a box was completed after the latest move/line (so that the player who completed the box gets another turn).
    //Also, increment the variable containing the value of the number of boxes completed by the player who closed the most recently closed box (if a box was closed and it
    //was player 1's turn the increment countboxcom1, if it was player 2's turn then increment countboxcom2) (the increment is done twice if two boxes are closed with the
    //same move/line).
    //Finally, increment boxcompall (total number of boxes completed by any player) by the number of boxes completed after the latest move.

    for(i=2; i<y; i+=3)
    {
        for(j=4; j<x; j+=6)
        {

            vals[i][j]=abs(vals[i-1][j])+abs(vals[i+2][j])+abs(vals[i][j-3])+abs(vals[i][j+3]);
            if (vals[i][j]==4&&vals[i+1][j]==0)
            {
                boxcomp++;
                vals[i+1][j]=player;
                if(player==1)
                    countboxcom1++;
                else if (player==-1)
                    countboxcom2++;
            }
        }
    }
    boxcompall+=boxcomp;
}



int end_check()
{
    //If the boxcompall (total number of boxes completed by any player) variable is equal to the
    //boxmax variable (total number of boxes that can be completed in the grid), then return '1' indicating that the game is over.
    //Otherwise, return '0' indicating the the game is not over.
    if(boxcompall==boxmax)
        return 1;
    else
        return 0;
}


void winner()
{
    //If the number of boxes completed by player 1 is greater than the number of boxes completed by player 2, display that the winner is player 1.
    //If the number of boxes completed by player 2 is greater than the number of boxes completed by player 1, display that the winner is player 2.
    //Otherwise, display that the game ended in a draw.
    if(countboxcom1>countboxcom2)
        printf("The winner is Player A");
    else if (countboxcom2>countboxcom1)
        printf("The winner is Player B");
    else
        printf("Draw");
}

//Definition of 'clrscr' function which clears the screen.
void clrscr()
{
    system("@cls||clear");
}

//Definition of 'scan_player_name' function which scans the names of player 1 and player 2 from the users.
void scan_player_name(char nameA[100],char nameB[100])
{
    printf("Please enter Player A name:");
    fgets(nameA,100,stdin);
    fgets(nameA,100,stdin);
    nameA[strlen(nameA)-1]=0;
    printf("\nPlease enter Player B name:");
    fgets(nameB,100,stdin);
    nameB[strlen(nameB)-1]=0;
}

int main()
{
    //Call the 'main_menu' function which starts the game.
    main_menu();


    return 0;
}
