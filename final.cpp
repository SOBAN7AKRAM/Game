#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;

// variables for counting score,player and enemy health etc
int score=0,count=15,horizontalCount=15,followCount=20,playerhealth=30,VEH=15,HEH=15,FEH=20;
int bulletCount=0,bulletCountV=0,bulletCountH=0;
// variable for moving ghost 
string direction="down";
string horizontalDirection="left";
string followStatus="isAlive";

// functions for game opening menu's
void logo();
void loading();
void loginMenuHeader();
void menu();
void options();
void keysDetail();
void instruction();
void YouDie();
void YouWon();
void resumeMenu();

//functions for printing maze,player and ghosts
void printmaze();
void printPlayer(char player[3][3], int &px, int &py);
void printVerticalGhost(char verticalGhost[3][3],int &vgx,int &vgy);
void printHorizontalGhost(char horizontalGhost[3][3],int &hgx,int &hgy);
void printFollowGhost(char followGhost[3][3],int &fgx,int &fgy);

//functions for removing player and ghosts
void removeplayer(int &px,int &py);
void removeVerticalGhost(int &vgx,int &vgy);
void removeHorizontalGhost(int &hgx,int &hgy);
void removeFollowGhost(int &fgx,int &fgy);

//functions for moving player
void moveleft(char player[3][3],int &px,int &py);
void moveright(char player[3][3],int &px,int &py);
void movedown(char player[3][3],int &px,int &py);
void moveup(char player[3][3],int &px,int &py);

//functions for moving ghosts
void moveVerticalGhost(char verticalGhost[3][3],int &vgx,int &vgy);
void moveHorizontalGhost(char horizontalGhost[3][3],int &hgx,int &hgy);
void moveFollowGhost(char followGhost[3][3],int &fgx,int &fgy,int &px,int &py);

//functions for printing bullet of player,vertical enemy and horizontal enemy
void printBullet(int x,int y);
void printBulletV(int x,int y);
void printBulletH(int x,int y);

//functions for erasing bullets
void eraseBullet(int x,int y);
void eraseBulletV(int x,int y);
void eraseBulletH(int x,int y);

//functions to generate a bullet
void generateBullet(int bulletX[],int bulletY[],bool isBulletActive[],int px,int py);
void generateBulletV(int bulletVX[],int bulletVY[],bool isBulletActiveVertical[],int vgx,int vgy);
void generateBulletH(int bulletHX[],int bulletHY[],bool isBulletActiveHorizontal[],int hgx,int hgy);

//functions to make bullets inactive
void makeBulletInactive(int i,bool isBulletActive[]);
void makeBulletInactiveV(int i, bool isBulletActiveVertical[]);
void makeBulletInactiveH(int i, bool isBulletActiveHorizontal[]);

//functions to move bullets
void moveBullet(int bulletX[],int bulletY[],bool isBulletActive[]);
void moveBulletV(int bulletVX[],int bulletVY[],bool isBulletActiveVertical[]);
void moveBulletH(int bulletHX[],int bulletHY[],bool isBulletActiveHorizontal[]);

//functions to print score,player and enemy health
void printscore();
void addscore();
void playerHealth();
void verticalEnemyHealth();
void horizontalEnemyHealth();
void followEnemyHealth();

//function to detect collision of bullet with enemy and player
void bulletCollisionWithVerticalEnemy(int bulletX[],int bulletY[], bool isBulletActive[]);
void bulletCollisionWithHorizontalEnemy(int bulletX[],int bulletY[], bool isBulletActive[]);
void bulletCollisionWithFollowEnemy(int bulletX[],int bulletY[], bool isBulletActive[]);
//function to detect collision of follow ghost with player
bool detectCollision(int &px,int &py, int &fgx,int &fgy);

//functions for moving cursor to xy position 
void gotoxy(int x, int y);
//function to read from console
char getCharatxy(short int x, short int y);

//function to store saved game data in file
void storeData(int &px,int &py,int &fgx,int &fgy,int &vgx,int &vgy,int &hgx,int &hgy);
//function to read saved game data from file
void readData(int &px,int &py,int &fgx,int &fgy,int &vgx,int &vgy,int &hgx,int &hgy);
int parseData(string number,int i);
void storeBullet(bool isBulletActive[],bool isBulletActiveV[],bool isBulletActiveH[],int bulletX[],int bulletY[],int bulletVX[],int bulletVY[],int bulletHX[],int bulletHY[]);
void readBullet(int bulletX[],int bulletY[],int bulletVX[],int bulletVY[],int bulletHX[],int bulletHY[]);

//2D array to print maze
string mazeArray1[32][1] = {
    {"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%                                                                            %"},
    {"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"}};
main()
{
    //variables to positioning player on console
    int px = 12, py = 16;
    //variables to positioning enemies on console
    int vgx=68, vgy=8, hgx=10, hgy=22, fgx=56, fgy=6;
    //variables to slow down the speed of ghost and timerB for bullet
    int timerV=2,timerH=2,timerF=2,timerB=2;
    
    //to store answer from detect collission function
    bool result;

    //arrays to store bullet
    int bulletX[10000];
    int bulletY[10000];
    int bulletVY[10000];
    int bulletVX[10000];
    int bulletHX[10000];
    int bulletHY[10000];

    //arrays to store active bullet
    bool isBulletActive[10000];
    bool isBulletActiveVertical[10000];
    bool isBulletActiveHorizontal[10000];

    // variables to print character used in printing player and enemy
    char p = 148, l = 240, g=219, a=162, b=229;
    //2D array to print player
    char player[3][3] = {
        {' ', p, ' '},
        {'(', l, ')'},
        {'/', ' ', '\\'}};
    //2D array to print vertical ghost
    char verticalGhost[3][3]={
        {' ','@',' '},
        {'(',g,')'},
        {'/',' ','\\'}
    };
    //2D array to print horizontal ghost 
    char horizontalGhost[3][3]={
        {' ',a,' '},
        {'{',g,'}'},
        {'<',' ','>'}
    };
    //2D array to print follow ghost
    char followGhost[3][3]={
        {' ',b,' '},
        {'[',g,']'},
        {'=',' ','='}
    };
    
    //calling function to print logo and opening menu
    system("cls");
    logo();
    loading();
    system("cls");
    loginMenuHeader();
    cout << endl << endl << endl;
    menu();
    //variables to store users option for main menu and optional menu
    int option, keyoption,choice=3;
    bool gamerunning(true);
    while (gamerunning)
    {

        cout << "Enter Your Option:";
        cin >> option;
        if (option == 1 || option==2)
        {    
            if (option==2)
            {
                // calling function to read data from file
               readData(px,py,fgx,fgy,vgx,vgy,hgx,hgy);
               readBullet(bulletX,bulletY,bulletVX,bulletVY,bulletHX,bulletHY);
               option=1;
            }
            //calling function to start the game
            system("cls");
            printmaze();
            printPlayer(player, px, py);
            printVerticalGhost(verticalGhost,vgx,vgy);
            printHorizontalGhost(horizontalGhost,hgx,hgy);
            printFollowGhost(followGhost,fgx,fgy);
            //loop for game running
            while (true)
            {
                //functions to print health and score
                playerHealth();
                printscore();
                verticalEnemyHealth();
                followEnemyHealth();
                horizontalEnemyHealth();
                result=detectCollision(px,py,fgx,fgy);
                //condition to check wheter player is die or won the game
                if (playerhealth<=0 || result==true || score>=50)
                {
                    system ("cls");
                    if (playerhealth<=0 || result==true)
                    {
                        YouDie();
                        Sleep(1000);
                    }  
                    else if(score>=50)
                    {
                        YouWon();
                        Sleep(1000);
                    }  
                    
                    system("cls");
                    loginMenuHeader();
                    cout << endl << endl << endl;
                    menu();
                    //initializing variables to initial values so that new game will start 
                    playerhealth=30;
                    score=0;
                    fgx=56, fgy=6;
                    px = 12, py = 16;
                    vgx=68, vgy=8, hgx=10, hgy=22,count=15,horizontalCount=15,followCount=20,VEH=15,HEH=15,FEH=20,timerV=2,timerH=2,timerF=2,timerB=2;
                    followStatus="isAlive";
                    break;
                    

                } 
                //read keys from console to move player
                if (GetAsyncKeyState(VK_RIGHT))
                {
                   moveright(player,px,py);
                }
                if (GetAsyncKeyState(VK_LEFT))
                {
                   moveleft(player,px,py);
                }
                if (GetAsyncKeyState(VK_UP))
                {
                   moveup(player,px,py);
                }
                if (GetAsyncKeyState(VK_DOWN))
                {
                   movedown(player,px,py);
                }
                //read keys from console to exit the game
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    choice=5;
                    while (choice!=3)
                     {
                        system ("cls");
                     loginMenuHeader();
                     cout << endl << endl << endl;
                     resumeMenu();
                     cout<<"Enter your choice:";
                     cin>>choice;
                     if (choice==1)
                     {
                         system ("cls");
                         printmaze();
                         break;
                     }
                     else if (choice==2)
                    {
                        //to store data in file
                       storeData(px,py,fgx,fgy,vgx,vgy,hgx,hgy);
                       storeBullet(isBulletActive,isBulletActiveVertical,isBulletActiveHorizontal,bulletX,bulletY,bulletVX,bulletVY,bulletHX,bulletHY);
                       cout<<"Game saved successfull"<<endl;
                       cout<<"Press any key to continue";
                       getch();
                    }
                    else if (choice==3)
                    {
                       return 0;
                    }
                     }
                    
                }
                if (GetAsyncKeyState('D'))
                {
                    //to fire bullets of player
                   char nextlocation=getCharatxy(px+3,py);
                   if (nextlocation!='%')
                   {
                      generateBullet(bulletX,bulletY,isBulletActive,px,py);  
                   }     
                }
                // timer to slow down the vertical ghost
                if (timerV==2)
                {
                    //count varibles to remove ghost if health is 0
                    if (count>0)
                    {
                        moveVerticalGhost(verticalGhost,vgx,vgy); 
                       
                        timerV=0;
                    }
                    if (count<=0)
                    {
                        removeVerticalGhost(vgx,vgy);
                    }
                }
                if (count>0)
                {
                    if (timerB==2)
                    {
                       generateBulletV(bulletVX,bulletVY,isBulletActiveVertical,vgx,vgy);
                       timerB=0;
                    }   
                }
                //timer to slow down the horizontal ghost
                if (timerH==2)
                {
                    if (horizontalCount>0)
                    {
                        moveHorizontalGhost(horizontalGhost,hgx,hgy);   
                        timerH=0;
                    }
                    if (horizontalCount<=0)
                    {
                        removeHorizontalGhost(hgx,hgy);
                    }
                }
                if (horizontalCount>0)
                {
                    generateBulletH(bulletHX,bulletHY,isBulletActiveHorizontal,hgx,hgy);
                }
                //timer to slow down the follow ghost
                if (timerF==2)
                {
                    if (followCount>0)
                    {
                        moveFollowGhost(followGhost,fgx,fgy,px,py);
                        timerF=0;
                    }
                    if (followCount<=0)
                    {
                        removeFollowGhost(fgx,fgy);
                        followStatus="dead";
                    }
                }  
               
               //calling functions to move bullets of enemy and player
                moveBulletV(bulletVX,bulletVY,isBulletActiveVertical); 
                moveBullet(bulletX,bulletY,isBulletActive); 
                moveBulletH(bulletHX,bulletHY,isBulletActiveHorizontal);
                //calling functions to detect bullet collision with enemy and player
                bulletCollisionWithVerticalEnemy(bulletX,bulletY,isBulletActive);
                bulletCollisionWithFollowEnemy(bulletX,bulletY,isBulletActive);
                bulletCollisionWithHorizontalEnemy(bulletX,bulletY,isBulletActive);
                //variables which are used to slow enemies and bullet
                timerV++;
                timerH++;
                timerF++;
                timerB++;
                Sleep(50);
            }
        }
        //if options 3 to open key detail and instruction menu
        if (option == 3)
        {
            options();
            while (true)
            {
                cout << "Enter your option:";
                cin >> keyoption;
                if (keyoption == 1)
                {
                    keysDetail();
                    cout << "Press any Key to continue:";
                    getch();
                    options();
                }
                if (keyoption == 2)
                {
                    instruction();
                    cout << "Press any key to continue;";
                    getch();
                    options();
                }
                if (keyoption == 3)
                {
                    system("cls");
                    loginMenuHeader();
                    cout << endl
                         << endl
                         << endl;
                    menu();
                    break;
                }
                else if (keyoption == 0 || keyoption > 3)
                {
                    cout << "INVALID OPTIONS" << endl;
                    cout << "Press any key to continue";
                    getch();
                    options();
                }
            }
        }
       //conditions to close the game
        if (option == 4)
        {
            return 0;
        }
        //condition to check invalid options
        else if (option == 0 || option > 4)
        {
            cout << "INVALID OPTIONS" << endl;
            cout << "Press any key to continue";
            getch();
            system("cls");
            loginMenuHeader();
            cout << endl
                 << endl
                 << endl;
            menu();
        }
    }
}
void logo()
{
    cout << "                                    .-==-=-.                    " << endl;
    cout << "                                   -*==. :=*=                   " << endl;
    cout << "                                   .#========#.                 " << endl;
    cout << "                                   #+++==++*#                   " << endl;
    cout << "                                   :##**=++*+----.              " << endl;
    cout << "                                :---:.           .---.          " << endl;
    cout << "                             .=-.                    :=         " << endl;
    cout << "                            :=           ...::::-*@+. .+        " << endl;
    cout << "                           .+  .%#*+======----*%@#+-=: --       " << endl;
    cout << "                           =. :+++*@%#*......==+*:...:  +       " << endl;
    cout << "                           =. :....%:..........-%.....: =.      " << endl;
    cout << "                           -: :....#=:..........@%....- ::       " << endl;
    cout << "                           .= :....=@+..........#@....- :=        " << endl;
    cout << "                            * .:....@%..........+@-...- :-        " << endl;
    cout << "                            =: -....#@:.........=@+..:: +.        " << endl;
    cout << "                             +  :...=@+.........:*=::. --         " << endl;
    cout << "                              +. .:::+-....:::::.....-+:          " << endl;
    cout << "                               -=-...:::::.....:::-==:            " << endl;
    cout << "                               .-+-:---======+++++*+-             " << endl;
    cout << "                               *  .+==*#*+*###%==+=*:+.           " << endl;
    cout << "                               .=- .==+##%%%%%%+===*%+.           " << endl;
    cout << "                                 :*--:=*%%#**+++++++**-.          " << endl;
    cout << "                                .*+=.  :=++++++++++++. *-         " << endl;
    cout << "                                =*===-====*++++++++**-==*         " << endl;
    cout << "                                :#*+++==++=-+*******+++*+         " << endl;
    cout << "                                 :*#***##:   ##*=: =##*-          " << endl;
    cout << "                                   :--+-   :=:+   =:             " << endl;
    cout << "                                     -=   .+  *.  --             " << endl;
    cout << "                                    :+    *   *.  --             " << endl;
    cout << "                                    .*    +.   *.  --             " << endl;
    cout << "                                   .*    -:   .+   =:             " << endl;
    cout << "                                -+*++==::=    ++.:-+*+=-.         " << endl;
    cout << "                              :*+=======++.  #*=========++=-      " << endl;
    cout << "                             -#+====-::-==* +*+=========-::-*=    " << endl;
    cout << "                             %+=====:..:=+# #*+=========:..:=++   " << endl;
    cout << "                             #***+++++***#- -+****************.   " << endl;
    cout << "                             ..:::::::..                         " << endl;
}
void loading()
{
    cout << "                                    LOADING";
    for (int i = 0; i < 4; i++)
    {
        cout << ".";
        Sleep(200);
    }
}
void loginMenuHeader()
{
    cout << " _____  _              _____             " << endl;
    cout << "|   __||_| ___  ___   |     | ___  ___   " << endl;
    cout << "|   __|| ||  _|| -_|  | | | || .'||   |  " << endl;
    cout << "|__|   |_||_|  |___|  |_|_|_||__,||_|_|  " << endl;
}
void menu()
{
    cout << "MENU" << endl;
    cout << "----------------" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Resume Game"<<endl;
    cout << "3. Option" << endl;
    cout << "4. Exit" << endl;
}
void options()
{
    system("cls");
    loginMenuHeader();
    cout << endl
         << endl
         << endl;
    cout << "OPTION MENU" << endl;
    cout << "-----------------" << endl;
    cout << "1. Keys" << endl;
    cout << "2. Instruction" << endl;
    cout << "3. Exit" << endl;
}
void keysDetail()
{
    system("cls");
    loginMenuHeader();
    cout << endl
         << endl
         << endl;
    cout << "KEYS DETAIL" << endl;
    cout << "-----------------" << endl;
    cout << "UP"
         << "\t"
         << "\t"
         << "Go Up" << endl;
    cout << "DOWN"
         << "\t"
         << "\t"
         << "Go Down" << endl;
    cout << "LEFT"
         << "\t"
         << "\t"
         << "Go Left" << endl;
    cout << "RIGHT"
         << "\t"
         << "\t"
         << "Go Right" << endl;
    cout << "D"
         << "\t"
         << "\t"
         << "Fire" << endl;
    cout << "ESCAPE"
         << "\t"
         << "\t"
         << "Exit Game" << endl;
}
void instruction()
{
    system("cls");
    loginMenuHeader();
    cout << endl
         << endl
         << endl;
    cout << "INSTRUCTIONS" << endl;
    cout << "------------------" << endl;
    cout << "Player will fire on right side by pressind 'D' key." << endl;
    cout << "Score will add when bullet interact with enemy"<<endl;
    cout << "Player health will decrease when enemy bullet collide with player"<<endl;
    cout << "Player will die if it collide with follow ghost"<<endl;
    cout << "Player will won the game if you score 50"<<endl;
}

void printmaze()
{
    int k = 3;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    for (int i = -1; i < 32; i++)
    {
        cout << mazeArray1[i][1] << endl;
    }
}
void printPlayer(char player[3][3], int &px, int &py)
{
    int k = 5;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    for (int i = 0; i < 3; i++)
    {
        gotoxy(px, py + i);
        for (int j = 0; j < 3; j++)
        {
            cout << player[i][j];
        }
        cout << endl;
    }
}
void printVerticalGhost(char verticalGhost[3][3],int &vgx,int &vgy)
{
    int k = 6;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    for (int i = 0; i < 3; i++)
    {
        gotoxy(vgx, vgy + i);
        for (int j = 0; j < 3; j++)
        {
            cout << verticalGhost[i][j];
        }
        cout << endl;
    }
}
void printHorizontalGhost(char horizontalGhost[3][3],int &hgx,int &hgy)
{
    int k = 8;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    for (int i = 0; i < 3; i++)
    {
        gotoxy(hgx, hgy + i);
        for (int j = 0; j < 3; j++)
        {
            cout << horizontalGhost[i][j];
        }
        cout << endl;
    }
}
void printFollowGhost(char followGhost[3][3],int &fgx,int &fgy)
{
    int k = 9;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    for (int i = 0; i < 3; i++)
    {
        gotoxy(fgx, fgy + i);
        for (int j = 0; j < 3; j++)
        {
            cout << followGhost[i][j];
        }
        cout << endl;
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharatxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar
                                                                                            : ' ';
}
void removeplayer(int &px,int &py)
{
    gotoxy(px,py);
    cout<<"   ";
    gotoxy(px,py+1);
    cout<<"   ";
    gotoxy(px,py+2);
    cout<<"   ";
}
void moveright(char player[3][3],int &px,int &py)
{
    char nextlocation=getCharatxy(px+3,py);
    char nextlocation1=getCharatxy(px+3,py+1);
    char nextlocation2=getCharatxy(px+3,py+2);
    if (nextlocation==' ' && nextlocation1==' ' && nextlocation2==' ')
    {
        gotoxy(px,py);
        removeplayer(px,py);
        px=px+1;
        gotoxy(px,py);
        printPlayer(player,px,py); 
    }
}
void moveleft(char player[3][3],int &px,int &py)
{
    char nextlocation=getCharatxy(px-1,py);
    char nextlocation1=getCharatxy(px-1,py+1);
    char nextlocation2=getCharatxy(px-1,py+2);
    if (nextlocation==' ' && nextlocation1==' ' && nextlocation2==' ')
    {
        gotoxy(px,py);
        removeplayer(px,py);
        px=px-1;
        gotoxy(px,py);
        printPlayer(player,px,py); 
    }
}
void moveup(char player[3][3],int &px,int &py)
{
    char nextlocation=getCharatxy(px,py-1);
    char nextlocation1=getCharatxy(px+1,py-1);
    char nextlocation2=getCharatxy(px+2,py-1);
    if (nextlocation==' ' && nextlocation1==' ' && nextlocation2==' ')
    {
        gotoxy(px,py);
        removeplayer(px,py);
        py=py-1;
        gotoxy(px,py);
        printPlayer(player,px,py); 
    }
}
void movedown(char player[3][3],int &px,int &py)
{
    char nextlocation=getCharatxy(px,py+3);
    char nextlocation1=getCharatxy(px+1,py+3);
    char nextlocation2=getCharatxy(px+2,py+3);
    if (nextlocation==' ' && nextlocation1==' '&& nextlocation2==' ')
    {
        gotoxy(px,py);
        removeplayer(px,py);
        py=py+1;
        gotoxy(px,py);
        printPlayer(player,px,py); 
    }
}
void removeVerticalGhost(int &vgx,int &vgy)
{
    gotoxy(vgx,vgy);
    cout<<"   ";
    gotoxy(vgx,vgy+1);
    cout<<"   ";
    gotoxy(vgx,vgy+2);
    cout<<"   ";
}
void removeHorizontalGhost(int &hgx,int &hgy)
{
    gotoxy(hgx,hgy);
    cout<<"   ";
    gotoxy(hgx,hgy+1);
    cout<<"   ";
    gotoxy(hgx,hgy+2);
    cout<<"   ";   
}
void removeFollowGhost(int &fgx,int &fgy)
{
    gotoxy(fgx,fgy);
    cout<<"   ";
    gotoxy(fgx,fgy+1);
    cout<<"   ";
    gotoxy(fgx,fgy+2);
    cout<<"   ";   
}
void moveVerticalGhost(char verticalGhost[3][3],int &vgx,int &vgy)
{
     if (direction=="down")
    {
        char nextlocation=getCharatxy(vgx,vgy+3);
        char nextlocation1=getCharatxy(vgx+1,vgy+3);
        char nextlocation2=getCharatxy(vgx+2,vgy+3);
        if ((nextlocation1=='%' || nextlocation=='%' || nextlocation2=='%' || nextlocation=='*' || nextlocation1=='*' || nextlocation2=='*') )
        {
            direction="up";
        }
        else 
        {
            removeVerticalGhost(vgx,vgy);
            vgy=vgy+1;
            printVerticalGhost(verticalGhost,vgx,vgy);
        }
    }
    if (direction=="up")
    {
        char nextlocation=getCharatxy(vgx,vgy-1);
        char nextlocation1=getCharatxy(vgx+1,vgy-1);
        char nextlocation2=getCharatxy(vgx+2,vgy-1);
        if ((nextlocation1=='%' || nextlocation=='%' || nextlocation2=='%') || (nextlocation=='*' || nextlocation1=='*' || nextlocation2=='*') )
        {
            direction="down";
        }
        else 
        {
            removeVerticalGhost(vgx,vgy);
            vgy=vgy-1;
            printVerticalGhost(verticalGhost,vgx,vgy);
        }
    }
}
void moveHorizontalGhost(char horizontalGhost[3][3],int &hgx,int &hgy)
{
    if (horizontalDirection=="left")
    {   
        char nextlocation=getCharatxy(hgx+3,hgy);
        char nextlocation1=getCharatxy(hgx+3,hgy+1);
        char nextlocation2=getCharatxy(hgx+3,hgy+2);
        if ((nextlocation1=='%' || nextlocation=='%' || nextlocation2=='%') || (nextlocation=='*' || nextlocation1=='*' || nextlocation2=='*') )
        {
            horizontalDirection="right";
        }
        else 
        {
            removeHorizontalGhost(hgx,hgy);
            hgx=hgx+1;
            printHorizontalGhost(horizontalGhost,hgx,hgy);
        }
    }
    if (horizontalDirection=="right")
    {
        char nextlocation=getCharatxy(hgx-1,hgy);
        char nextlocation1=getCharatxy(hgx-1,hgy+1);
        char nextlocation2=getCharatxy(hgx-1,hgy+2);
        if ((nextlocation1=='%' || nextlocation=='%' || nextlocation2=='%') || (nextlocation=='*' || nextlocation1=='*' || nextlocation2=='*') )
        {
            horizontalDirection="left";
        }
        else 
        {
            removeHorizontalGhost(hgx,hgy);
            hgx=hgx-1;
            printHorizontalGhost(horizontalGhost,hgx,hgy);
        }
    }
}
void moveFollowGhost(char followGhost[3][3],int &fgx,int &fgy,int &px,int &py)
{
    char l=240;
    char p=148;
    if (fgx>px)
    {
        char next=getCharatxy(fgx-1,fgy+1);
        char next1=getCharatxy(fgx-1,fgy+2);
        char next2=getCharatxy(fgx-1,fgy);
        if ((next==' ')  
         &&(next1==' ') 
        && (next2==' ' ))
        {
        removeFollowGhost(fgx,fgy);
        fgx--;
        printFollowGhost(followGhost,fgx,fgy);
        }
    }
    else if (fgx<px)
    {
        char next=getCharatxy(fgx+3,fgy+1);
        char next1=getCharatxy(fgx+3,fgy+2);
        char next2=getCharatxy(fgx+3,fgy);
        if ((next==' ') &&(next1==' ')  &&(next2==' ')) 
        {
        removeFollowGhost(fgx,fgy);
        fgx++;
        printFollowGhost(followGhost,fgx,fgy);
        }
    }
    else if (fgy>py)
    {
        char next=getCharatxy(fgx+1,fgy-1);
        char next1=getCharatxy(fgx,fgy-1);
        char next2=getCharatxy(fgx+2,fgy-1);
        if ((next==' ') && (next1==' ')  && (next2==' ')) 
        {
        removeFollowGhost(fgx,fgy);
        fgy--;
        printFollowGhost(followGhost,fgx,fgy);
        }
    }
    else if (fgy<py)
    {
        char next=getCharatxy(fgx+2,fgy+3);
        if (next==' ') 
        {
        removeFollowGhost(fgx,fgy);
        fgy++;
        printFollowGhost(followGhost,fgx,fgy);
        }
    }
}
void printBullet(int x,int y)
{
    int k = 4;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy(x,y);
    cout<<">";
}
void eraseBullet(int x,int y)
{
    gotoxy(x,y);
    cout<<" ";
}

void generateBullet(int bulletX[],int bulletY[],bool isBulletActive[],int px,int py)
{
    bulletX[bulletCount]=px+3;
    bulletY[bulletCount]=py+1;
    isBulletActive[bulletCount]=true;
    gotoxy(px+3,py+1);
    cout<<">";
    bulletCount++;
}
void makeBulletInactive(int i,bool isBulletActive[])
{
    isBulletActive[i]=false;
}
void moveBullet(int bulletX[],int bulletY[],bool isBulletActive[])
{
    for (int i=0;i<1000;i++)
    {
        
        if (isBulletActive[i]==true)
        {
        char nextlocation=getCharatxy(bulletX[i]+1,bulletY[i]);
        if (nextlocation!=' ')
        {
            eraseBullet(bulletX[i],bulletY[i]);
            makeBulletInactive(i,isBulletActive);
            if (nextlocation=='*')
            {
                cout<<" ";
                addscore();
            }
        }
        else
        {
            eraseBullet(bulletX[i],bulletY[i]);
            bulletX[i]=bulletX[i]+1;
            printBullet(bulletX[i],bulletY[i]);  
        }
        }

    }
}
void addscore()
{
    score++;
}
void printscore()
{
    int k = 10;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy(80,8);
    cout<<"Score:"<<score;
}
void bulletCollisionWithVerticalEnemy(int bulletX[],int bulletY[], bool isBulletActive[])
{ 

     for (int i=0;i<bulletCount;i++)
    {
        char next=getCharatxy(bulletX[i]+1,bulletY[i]);
        if (isBulletActive[i]==true)
        {
           if (next=='(' || next=='@' || next=='/' )
           {
            addscore();
            count--;
            eraseBullet(bulletX[i],bulletY[i]);
            isBulletActive[i]=false;
           }
        }
    }
}
void bulletCollisionWithHorizontalEnemy(int bulletX[],int bulletY[], bool isBulletActive[])
{ 
    char a=162;
    for (int i=0;i<bulletCount;i++)
    {
        char next=getCharatxy(bulletX[i]+1,bulletY[i]);
        if (isBulletActive[i]==true)
        {
            if (next==a || next=='{' || next=='<' )
           {
            addscore();
            horizontalCount--;
            eraseBullet(bulletX[i],bulletY[i]);
            isBulletActive[i]=false;
           }
        }
    }
}
void bulletCollisionWithFollowEnemy(int bulletX[],int bulletY[], bool isBulletActive[])
{
    char a=229;
     for (int i=0;i<bulletCount;i++)
    {
        char next=getCharatxy(bulletX[i]+1,bulletY[i]);
        if (isBulletActive[i]==true)
        {
            if (next==a || next=='[' || next=='=' )
           {
            addscore();
            eraseBullet(bulletX[i],bulletY[i]);
            followCount--;
            isBulletActive[i]=false;
           }
        }
    }
}

void printBulletV(int x,int y)
{
    int k = 2;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy(x,y);
    cout<<".";
}
void printBulletH(int x,int y)
{
    int k = 1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy(x,y);
    cout<<".";
}
void eraseBulletV(int x,int y)
{
    gotoxy(x,y);
    cout<<" ";
}
void eraseBulletH(int x,int y)
{
    gotoxy(x,y);
    cout<<" ";
}
void makeBulletInactiveV(int i, bool isBulletActiveVertical[])
{
    isBulletActiveVertical[i]=false;
}
void makeBulletInactiveH(int i, bool isBulletActiveHorizontal[])
{
    isBulletActiveHorizontal[i]=false;
}
void generateBulletV(int bulletVX[],int bulletVY[],bool isBulletActiveVertical[],int vgx,int vgy)
{
    bulletVX[bulletCountV]=vgx-1;
    bulletVY[bulletCountV]=vgy+1;
    isBulletActiveVertical[bulletCountV]=true;
    gotoxy(vgx-1,vgy+1);
    cout<<".";
    bulletCountV++;
}
void generateBulletH(int bulletHX[],int bulletHY[],bool isBulletActiveHorizontal[],int hgx,int hgy)
{
    bulletHX[bulletCountH]=hgx+1;
    bulletHY[bulletCountH]=hgy-1;
    isBulletActiveHorizontal[bulletCountH]=true;
    gotoxy(hgx+1,hgy-1);
    cout<<".";
    bulletCountH++;
}
void moveBulletV(int bulletVX[],int bulletVY[],bool isBulletActiveVertical[])
{
    char p=148;
    for (int i=0;i<bulletCountV;i++)
    {
        if (isBulletActiveVertical[i]==true)
        {
        char nextlocation=getCharatxy(bulletVX[i]-1,bulletVY[i]);
        if (nextlocation==' ')
        {
            eraseBulletV(bulletVX[i],bulletVY[i]);
            bulletVX[i]=bulletVX[i]-1;
            printBulletV(bulletVX[i],bulletVY[i]); 
        }
        else if (nextlocation!=' ')
        {
           eraseBulletV(bulletVX[i],bulletVY[i]);
           makeBulletInactiveV(i,isBulletActiveVertical);
           if (nextlocation==p || nextlocation==')' || nextlocation=='\\')
           {
                playerhealth--;
           }
        }

    }
    }
}
void moveBulletH(int bulletHX[],int bulletHY[],bool isBulletActiveHorizontal[])
{
   char p=148;
    for (int i=0;i<bulletCountH;i++)
    {
        if (isBulletActiveHorizontal[i]==true)
        {
        char nextlocation=getCharatxy(bulletHX[i],bulletHY[i]-1);
        char next=getCharatxy(bulletHX[i]+2,bulletHY[i]-1);
        if (nextlocation==' ') //&& next==' ' )
        {
             eraseBulletH(bulletHX[i],bulletHY[i]);
            bulletHY[i]=bulletHY[i]-1;
            printBulletH(bulletHX[i],bulletHY[i]); 
        }
        else if (nextlocation!=' ')// && next!=' ')
        {
           eraseBulletH(bulletHX[i],bulletHY[i]);
           makeBulletInactiveH(i,isBulletActiveHorizontal);
           if (nextlocation==p || nextlocation==')' || nextlocation=='\\')
           {
               playerhealth--;
           }
        }

    }
    } 
}
void playerHealth()
{
    int k = 5;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy (80,10);
    cout<<"PLAYER HEALTH:"<<playerhealth;
}
void YouDie()
{   
    cout<<"'##:::'##::'#######::'##::::'##::::'########::'####:'########:"<<endl;
    cout<<". ##:'##::'##.... ##: ##:::: ##:::: ##.... ##:. ##:: ##.....::"<<endl;
    cout<<":. ####::: ##:::: ##: ##:::: ##:::: ##:::: ##:: ##:: ##:::::::"<<endl;
    cout<<"::. ##:::: ##:::: ##: ##:::: ##:::: ##:::: ##:: ##:: ######:::"<<endl;
    cout<<"::: ##:::: ##:::: ##: ##:::: ##:::: ##:::: ##:: ##:: ##...::::"<<endl;
    cout<<"::: ##:::: ##:::: ##: ##:::: ##:::: ##:::: ##:: ##:: ##:::::::"<<endl;
    cout<<"::: ##::::. #######::. #######::::: ########::'####: ########:"<<endl;
    cout<<":::..::::::.......::::.......::::::........:::....::........::"<<endl; 
}
void YouWon()
{
    
    cout<<"'##:::'##::'#######::'##::::'##::::'##:::::'##::'#######::'##::: ##:"<<endl;
    cout<<". ##:'##::'##.... ##: ##:::: ##:::: ##:'##: ##:'##.... ##: ###:: ##:"<<endl;
    cout<<":. ####::: ##:::: ##: ##:::: ##:::: ##: ##: ##: ##:::: ##: ####: ##:"<<endl;
    cout<<"::. ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##: ##:::: ##: ## ## ##:"<<endl;
    cout<<"::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##: ##:::: ##: ##. ####:"<<endl;
    cout<<"::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##: ##:::: ##: ##:. ###:"<<endl;
    cout<<"::: ##::::. #######::. #######:::::. ###. ###::. #######:: ##::. ##:"<<endl;
    cout<<":::..::::::.......::::.......:::::::...::...::::.......:::..::::..::"<<endl;

}
void verticalEnemyHealth()
{
    int k = 6;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy (80,12);
    cout<<"Vertical Enemy Health:"<<count;
}
void horizontalEnemyHealth()
{
    int k = 8;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy(80,14);
    cout<<"Horizontal Enemy Health:"<<horizontalCount;
}
void followEnemyHealth()
{
    int k = 9;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    gotoxy (80,16);
    cout<<"Follower Enemy Health:"<<followCount;
}
bool detectCollision(int &px,int &py, int &fgx,int &fgy)
{  
    bool flag=false;
     if (followStatus=="isAlive")
     {
   if (fgx==px && fgy==py)
   {
       flag=true;
   }
   if ((fgx==px && fgy-1==py+3) || (fgx+1==px && fgy-1==py+3) || (fgx-1==px && fgy-1==py+3))
   {
       flag=true;
   }
   if ((fgx==px && fgy+3==py-1) || (fgx+1==px && fgy+3==py-1) || (fgx-1==px && fgy+3==py-1))
   {
       flag=true;
   }
   if ((fgx-1==px+3 && fgy==py) || (fgx-1==px+3 && fgy+1==py) || (fgx-1==px+3 && fgy+2==py))
   {
       flag=true;
   }
   if ((fgx+3==px && fgy==py) || (fgx+3==px && fgy-1==py) || (fgx+3==px && fgy+3==py))
   {
       flag=true;
   }
     }
 return flag;  
}
void storeData(int &px,int &py,int &fgx,int &fgy,int &vgx,int &vgy,int &hgx,int &hgy)
{
    fstream file;
    file.open("save.txt",ios::out);
    file<<px<<",";
    file<<py<<",";
    file<<fgx<<",";
    file<<fgy<<",";
    file<<vgx<<",";
    file<<vgy<<",";
    file<<hgx<<",";
    file<<hgy<<",";
    file<<score<<",";
    file<<playerhealth<<",";
    file<<count<<",";
    file<<followCount<<",";
    file<<horizontalCount;
    file.close();

}
void readData(int &px,int &py,int &fgx,int &fgy,int &vgx,int &vgy,int &hgx,int &hgy)
{
    string number="";
    fstream file;
    file.open("save.txt",ios::in);
    if (file.is_open())
   {
       std::getline(file, number);
       file.close();
   }
   else
   {
       // handle file opening error
       return;
   }
    px= parseData(number,1);
    py=parseData(number,2);
    fgx=parseData(number,3);
    fgy=parseData(number,4);
    vgx=parseData(number,5);
    vgy=parseData(number,6);
    hgx=parseData(number,7);
    hgy=parseData(number,8);
    score=parseData(number,9);
    playerhealth=parseData(number,10);
    count=parseData(number,11);
    followCount=parseData(number,12);
    horizontalCount=parseData(number,13);
    
    
}
int parseData(string number,int idx)
{
    int count=1;
    string num="";
    for (int i=0 ;i<number.length();i++)
    {
        if(number[i]==',')
        {
            count++;
        }
        else if (count==idx)
        {
            num=num+number[i];
        }    
    }
    return std::stoi(num);
}
void storeBullet(bool isBulletActive[],bool isBulletActiveV[],bool isBulletActiveH[],int bulletX[],int bulletY[],int bulletVX[],int bulletVY[],int bulletHX[],int bulletHY[])
{
    fstream file;
    file.open("saveBullet.txt",ios::out);
    for (int i=0;i<bulletCount;i++)
    {
        if (isBulletActive[i]==true)
        {
            file <<bulletX[i]<<",";
            file<<bulletY[i]<<",";
        }
    }
    //file<<endl;
    //for (int i=0;i<bulletCountV;i++)
    //{
    //    if(isBulletActiveV[i]==true)
    //    {
    //        file<<bulletVX[i]<<",";
    //        file<<bulletVY[i]<<",";
    //    }
    //}
    //file<<endl;
    //for (int i=0;i<bulletCountH;i++)
    //{
    //    if (isBulletActiveH[i]==true)
    //    {
    //        file<<bulletHX[i]<<",";
    //        file<<bulletHY[i]<<",";
    //    }
    //}
    file.close();

}
void readBullet(int bulletX[],int bulletY[],int bulletVX[],int bulletVY[],int bulletHX[],int bulletHY[])
{
    int count1=0;
    string number="";
    fstream file;
    file.open("saveBullet.txt",ios::in);
    if (file.is_open())
    {
      std::getline(file, number);
      file.close();
    }
    else
    {
      // handle file opening error
      return;
    }
       bulletX[count1]=parseData(number,1);
       bulletY[count1]=parseData(number,1);
       file.close();

}


void resumeMenu()
{
    cout<<"1. To resume Game"<<endl;
    cout<<"2. To Save Game"<<endl;
    cout<<"3. Exit"<<endl;
}