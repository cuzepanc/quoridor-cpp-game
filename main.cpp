#include <iostream>
#include <cmath>
#include <string>
#include <graphics.h>
using namespace std;

const int numLarge = 9;
const int numSmall = 8;
const int cellSizeLarge = 60;
const int cellSizeSmall = 15;

const int Size = 2 * numLarge - 1;
char board[Size][Size];
int bariereA = 10, bariereB = 10, bariereC = 5, bariereD = 5 ;
char orientare = 'h'; // Orientarea curenta: 'h' orizontala 'v' verticala

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
int poz1=1,poz2,poz3=2,poz4=3;
int mod=2;

int totalWidth = (numLarge * cellSizeLarge) + (numSmall * cellSizeSmall);
int startX = (screenWidth - totalWidth) / 2;
int startY = (screenHeight - totalWidth) / 2;

void ApelInstructiuniSiPioni(int &optiune);
void Alege_Pioni(int &pion1Index,int &pion2Index);
void ApelJoc(int &optiune);

 char pioninames[14][50] =
    {
        "1pion_alb.bmp", "2pion_negru.bmp", "3pion_magenta.bmp", "4pion_lila.bmp",
        "5pion_pink.bmp", "6pion_roz.bmp", "7pion_rosu.bmp", "8pion_portocaliu.bmp",
        "9pion_mustar.bmp", "10pion_galben.bmp", "11pion_lime.bmp", "12pion_verde.bmp",
        "13pion_cyan.bmp", "14pion_blue.bmp"
    };

bool isMouseInButton(int x1, int y1, int x2, int y2)
{
    return mousex() >= x1 && mousex() <= x2 && mousey() >= y1 && mousey() <= y2;
}

void initBoard()
{
    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)
            board[i][j] = '.'; // Tabla este goala

    board[0][8] = 'A';
    board[Size - 1][8] = 'B';
    if(mod==4)
    {
        board[8][0]='C';
        board[8][Size-1]='D';
    }
}

void drawTableBackground(int startX, int startY, int width, int height)
{
    readimagefile("TABLA_DE_JOC.bmp", startX, startY, startX + width, startY + height);
}

void drawPion(int x, int y, char pion)
{
    if (pion == 'A') readimagefile(pioninames[poz1], x - 27, y - 27, x + 27, y + 27);
    else if (pion == 'B') readimagefile(pioninames[poz2], x - 27, y - 27, x + 27, y + 27);
         else if (pion == 'C') readimagefile(pioninames[poz3], x - 27, y - 27, x + 27, y + 27);
              else if (pion == 'D') readimagefile(pioninames[poz4], x - 27, y - 27, x + 27, y + 27);
}

void drawBariera(int x, int y, char tip)
{
    if (tip == '-') readimagefile("TEXTURA3o.bmp", x, y + cellSizeLarge - 14.5 , x + cellSizeLarge, y + (cellSizeLarge / 2) + 1.5);
    else if (tip == '|') readimagefile("TEXTURA3.bmp", x + cellSizeLarge - 14.5, y , x + cellSizeLarge/2 + 1.5, y + cellSizeLarge);
}


void drawMessages2(const string &messageA, const string &barrierMessageA, const string &messageB, const string &barrierMessageB,const string &messageC, const string &barrierMessageC, const string &messageD, const string &barrierMessageD, char player,const string &error)
{
    setcolor(LIGHTRED);
    setbkcolor(BLACK);
    char errorBuffer[256];
    strncpy(errorBuffer, error.c_str(), sizeof(errorBuffer) - 1);
    errorBuffer[sizeof(errorBuffer) - 1] = '\0';

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    int x,y;
    x = screenWidth/2;
    settextstyle(8, HORIZ_DIR, 2);
    outtextxy(x, 50, errorBuffer);

    setcolor(WHITE);
    setbkcolor(BLACK);
    settextjustify(TOP_TEXT, TOP_TEXT);
    settextstyle(8, HORIZ_DIR, 2);

    // cream buffer temporar pentru text
    char messageABuffer[256],messageBBuffer[256];
    char barrierABuffer[256],barrierBBuffer[256];

    // copiem string-urile in buffer
    strncpy(messageABuffer, messageA.c_str(), sizeof(messageABuffer) - 1);
    strncpy(barrierABuffer, barrierMessageA.c_str(), sizeof(barrierABuffer) - 1);

    strncpy(messageBBuffer, messageB.c_str(), sizeof(messageBBuffer) - 1);
    strncpy(barrierBBuffer, barrierMessageB.c_str(), sizeof(barrierBBuffer) - 1);


    messageABuffer[sizeof(messageABuffer) - 1] = '\0';
    barrierABuffer[sizeof(barrierABuffer) - 1] = '\0';

    messageBBuffer[sizeof(messageBBuffer) - 1] = '\0';
    barrierBBuffer[sizeof(barrierBBuffer) - 1] = '\0';

    // jcătorul A - stanga
    x = 20+textwidth(messageABuffer);
    y=getmaxy()/4+getmaxy()/8 - 40;
    outtextxy(x, y, messageABuffer);
    x=20;
    x = x+textwidth(barrierABuffer);
    y = getmaxy()/4+getmaxy()/8;
    outtextxy(x, y, barrierABuffer);

    // jucătorul B - dreapta
    x = startX +numLarge * cellSizeLarge + numSmall * cellSizeSmall + textwidth(messageBBuffer) +20;
    y=getmaxy()/4+getmaxy()/8 - 40;
    outtextxy(x, y, messageBBuffer);
    x = startX +numLarge * cellSizeLarge + numSmall * cellSizeSmall + textwidth(barrierBBuffer) +20;
    y = getmaxy()/4+getmaxy()/8;
    outtextxy(x, y, barrierBBuffer);
    y = y+40;

    if (player == 'A')
    {
        x = 20+textwidth("MUTA...");
        outtextxy(x, y, "MUTA...");
    }
    else if(player=='B')
    {
        x = startX +numLarge * cellSizeLarge + numSmall * cellSizeSmall + textwidth("MUTA...") +20;
        outtextxy(x, y, "MUTA...");
    }

    char messageCBuffer[256],messageDBuffer[256];
    char barrierCBuffer[256],barrierDBuffer[256];

    // copiem string-urile în buffer
    strncpy(messageCBuffer, messageC.c_str(), sizeof(messageCBuffer) - 1);
    strncpy(barrierCBuffer, barrierMessageC.c_str(), sizeof(barrierCBuffer) - 1);

    strncpy(messageDBuffer, messageD.c_str(), sizeof(messageDBuffer) - 1);
    strncpy(barrierDBuffer, barrierMessageD.c_str(), sizeof(barrierDBuffer) - 1);

    messageCBuffer[sizeof(messageCBuffer) - 1] = '\0';
    barrierCBuffer[sizeof(barrierCBuffer) - 1] = '\0';

    messageDBuffer[sizeof(messageDBuffer) - 1] = '\0';
    barrierDBuffer[sizeof(barrierDBuffer) - 1] = '\0';

    // jucatorul C - stanga
    setcolor(WHITE);
    x = 20+textwidth(messageCBuffer);
    y=getmaxy()/2+getmaxy()/8;
    outtextxy(x, y, messageCBuffer);
    x=20;
    x = x+textwidth(barrierCBuffer);
    y = y+40;
    outtextxy(x, y, barrierCBuffer);

    // jucatorul D - dreapta
    x = startX +numLarge * cellSizeLarge + numSmall * cellSizeSmall + textwidth(messageDBuffer) +20;
    y=getmaxy()/2+getmaxy()/8;
    outtextxy(x, y, messageDBuffer);
    x = startX +numLarge * cellSizeLarge + numSmall * cellSizeSmall + textwidth(barrierDBuffer) +20;
    y = y+40;
    outtextxy(x, y, barrierDBuffer);
    y+=40;

    if (player == 'C')
    {
        x = 20+textwidth("MUTA...");
        outtextxy(x, y, "MUTA...");
    }
    else if(player=='D')
    {
        x = startX +numLarge * cellSizeLarge + numSmall * cellSizeSmall + textwidth("MUTA...") +20;
        outtextxy(x, y, "MUTA...");
    }

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    x = screenWidth/2;
    y = startY+numLarge*cellSizeLarge+numSmall*cellSizeSmall+30;
    //bariere
    if(orientare=='h') outtextxy(x, y, "ORIENTARE: ORIZONTALA ");
    else outtextxy(x, y, "ORIENTARE: VERTICALA ");

}
void drawBoard2(const string &messageA, const string &barrierMessageA, const string &messageB, const string &barrierMessageB,const string &messageC, const string &barrierMessageC, const string &messageD, const string &barrierMessageD, char player,const string &error)
{

    readimagefile("background.bmp", 0, 0, screenWidth, screenHeight);
    drawTableBackground(startX, startY, numLarge * cellSizeLarge + numSmall * cellSizeSmall, numLarge * cellSizeLarge + numSmall * cellSizeSmall);
    drawMessages2(messageA, barrierMessageA, messageB, barrierMessageB,messageC, barrierMessageC, messageD, barrierMessageD,player,error);


    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)
        {
            int x = startX + j / 2 * (cellSizeLarge + cellSizeSmall) + (j % 2 == 0 ? 0 : cellSizeSmall);
            int y = startY + i / 2 * (cellSizeLarge + cellSizeSmall) + (i % 2 == 0 ? 0 : cellSizeSmall);

            if (board[i][j] == 'A' || board[i][j] == 'B' || board[i][j]=='C' || board[i][j]=='D')
                drawPion(x + cellSizeLarge / 2, y + cellSizeLarge / 2, board[i][j]);
            else if (board[i][j] == '-' || board[i][j] == '|')
                drawBariera(x, y, board[i][j]);

        }

}


void introduceNume(char nume[100])
{

    initwindow(screenWidth/3,screenHeight/3 , " ", screenWidth/3, screenHeight/3);
    setbkcolor(COLOR(239,226,207));
    cleardevice();
    setcolor(COLOR(89,40,35));
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(6,0,3);
    outtextxy(getmaxx()/2, 30, "Introduceti numele jucatorului:");


    int x = getmaxx()/2+10, y = getmaxy()/2+10;
    int i = 0;  // Indexul pentru caracterul curent din nume

    while (true)
    {
        char ch = getch();
        // enter
        if (ch == 13) break;
        // daca tasta apasata este backspace, stergem ultimul caracter
        else if (ch == 8)
       {
            if (i > 0)
            {
                i--;
                nume[i] = '\0';  // stergem caracterul
                cleardevice(); // curatam ecranul pentru a rescrie
                outtextxy(getmaxx()/2, 30, "Introduceti numele jucatorului:");
                outtextxy(x, y, nume); // afisam numele actualizat
            }
        }
        // daca este orice alta tasta, o adaugam la nume
        else
        {
            nume[i] = ch;
            i++;
            nume[i] = '\0'; // asiguram terminarea stringului
            cleardevice(); // curatam ecranul pentru a rescrie
            outtextxy(getmaxx()/2, 30, "Introduceti numele jucatorului:");
            outtextxy(x, y, nume); // afisam numele actualizat
        }
    }
    cleardevice();
}

bool pozitiiValide(int x, int y, int i, int j)
{
    if (x >= 0 && x < Size && y >= 0 && y < Size && board[x][y] == '.')
    {
        if (y == j)
        {
            if (x == i + 2)
                return board[i + 1][j] != '-';
            else if (x == i - 2)
                return board[i - 1][j] != '-';
        }
        else if (x == i)
        {
            if (y == j + 2)
                return board[i][j + 1] != '|';
            else if (y == j - 2)
                return board[i][j - 1] != '|';
        }
    }
    return false;
}


bool respectaRegulaFataInFata(int x, int y, int nx, int ny, char jucatorCurent)
{
    char adversar = (jucatorCurent == 'A') ? 'B' : 'A';
    if (!(nx >= 0 && nx < Size && ny >= 0 && ny < Size)) return 0;
    if ((abs(x - nx) == 4 && y == ny) || (x == nx && abs(y - ny) == 4))
    {
        int mijlocX = (x + nx) / 2;
        int mijlocY = (y + ny) / 2;

        if ((board[mijlocX][mijlocY]>='A' && board[mijlocX][mijlocY]<='D' && board[mijlocX][mijlocY]!=jucatorCurent) && board[nx][ny] == '.')
        {
            if(x-nx==4 && y==ny)
                if(board[nx+1][ny] != '.' || board[x-1][ny] != '.') return false;
            if(nx-x==4 && y==ny)
                if(board[nx-1][ny] != '.' || board[x+1][ny] != '.') return false;
            if(y-ny==4 && x==nx)
                if(board[nx][ny+1] != '.' || board[x][y-1] != '.') return false;
            if(ny-y==4 && x==nx)
                if(board[nx][ny-1] != '.' || board[x][y+1] != '.') return false;
            return true;
        }
    }

    if (abs(x - nx) == 2 && abs(y - ny) == 2)
    {
        if (board[nx][y]>='A' && board[nx][y]<='D' && board[nx][y]!=jucatorCurent)
        {
            if(x-nx==2 && nx-1>=0 && board[nx-1][y]=='.') return 0;
            if(x-nx==2 && (board[nx-1][y]!='.' || nx-1<0))
                 {
                     if(y-ny==2 && x-1>=0 && ny+1<Size && (board[nx][ny+1]!='.' || board[x-1][y]!='.')) return 0; //stanga sus
                     if(ny-y==2 && ny-1>=0 && x-1>=0 && (board[nx][ny-1]!='.' || board[x-1][y]!='.')) return 0; //dreapta sus
                 }
            if(nx-x==2 && nx+1<Size && board[nx+1][y]=='.') return 0;
            if(nx-x==2 && (board[nx+1][y]!='.' || nx+1>=Size))
                 {
                     if(y-ny==2 && ny+1<Size && x+1<Size && (board[nx][ny+1]!='.' || board[x+1][y]!='.')) return 0; //stanga jos
                     if(ny-y==2 && ny-1>=0 && x+1<Size && (board[nx][ny-1]!='.' || board[x+1][y]!='.')) return 0; //dreapta jos
                 }
            return 1;
        }
        if(board[x][ny]>='A' && board[x][ny]<='D' && board[x][ny]!=jucatorCurent)
        {
            if(ny-y==2 && ny+1<Size && board[x][ny+1]=='.') return 0;
            if(ny-y==2 && (board[x][ny+1]!='.' || ny+1>=Size))
                {
                    if(x-nx==2 && nx+1<Size && y+1<Size && (board[nx+1][ny]!='.' || board[x][y+1]!='.')) return 0; //dreapta sus
                    if(nx-x==2 && nx-1>=0 && y+1<Size && (board[nx-1][ny]!='.' || board[x][y+1]!='.')) return 0; //dreapta jos
                }
            if(y-ny==2 && ny-1>=0 && board[x][ny-1]=='.') return 0;
            if(y-ny==2 && (board[x][ny-1]!='.' || ny-1<0))
                {
                    if(x-nx==2 && y-1>=0 && nx+1<Size && (board[nx+1][ny]!='.' || board[x][y-1]!='.')) return 0; //stanga sus
                    if(nx-x==2 && nx-1>=0 && y-1>=0 && (board[nx-1][ny]!='.' || board[x][y-1]!='.')) return 0; //stanga jos
                }
            return 1;
        }

    }

    return false;
}

void drawboard2(char player)
{

    int xCurent, yCurent;
    bool accesibile[Size][Size];
    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)
            accesibile[i][j]=0;

    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            if (board[i][j] == player)
            {
                xCurent = i;
                yCurent = j;
                break;
            }

    const int dx[] = {-2, 2, 0, 0,-2,-2,2,2,0,0,-4,4};
    const int dy[] = {0, 0, -2, 2,-2,2,-2,2,-4,4,0,0};

    for (int k = 0; k < 12; k++)
    {
        int nx = xCurent + dx[k];
        int ny = yCurent + dy[k];

        if (pozitiiValide(nx, ny, xCurent, yCurent) || respectaRegulaFataInFata(xCurent, yCurent, nx, ny, player))
                accesibile[nx][ny] = 1;


    }
    int v1,v2,poz;

    if(player=='A') poz=poz1;
    else if(player=='B') poz=poz2;
         else if(player=='C') poz=poz3;
              else poz=poz4;

    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)

            if (accesibile[i][j]==1)
            {
                if(poz==0) setfillstyle(SOLID_FILL, COLOR(255, 255, 255)); // Culoare pentru poziții accesibile
                if(poz==1) setfillstyle(SOLID_FILL, COLOR(0, 0, 0));
                if(poz==2) setfillstyle(SOLID_FILL, COLOR(100, 0, 100));
                if(poz==3) setfillstyle(SOLID_FILL, COLOR(200, 162, 200));
                if(poz==4) setfillstyle(SOLID_FILL, COLOR(231, 84, 128));
                if(poz==5) setfillstyle(SOLID_FILL, COLOR(255, 182, 193));
                if(poz==6) setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
                if(poz==7) setfillstyle(SOLID_FILL, COLOR(255, 165, 0));
                if(poz==8) setfillstyle(SOLID_FILL, COLOR(255, 204, 0));
                if(poz==9) setfillstyle(SOLID_FILL, COLOR(255, 255, 0));
                if(poz==10) setfillstyle(SOLID_FILL, COLOR(50, 205, 50));
                if(poz==11) setfillstyle(SOLID_FILL, COLOR(0, 100, 0));
                if(poz==12) setfillstyle(SOLID_FILL, COLOR(100, 120, 120));
                if(poz==13) setfillstyle(SOLID_FILL, COLOR(100, 120, 255));
                v1=j/2*cellSizeLarge+j/2*cellSizeSmall;
                v2=i/2*cellSizeLarge+i/2*cellSizeSmall;
                bar(v1+startX+21, v2+startY+21, v1+startX+cellSizeLarge-21, v2+startY+cellSizeLarge-21);
            }

}

bool mutaJucator(char jucator, int x, int y)
{
    int xCurent = -1, yCurent = -1;

    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)
            if (board[i][j] == jucator)
            {
                xCurent = i;
                yCurent = j;
                break;
            }



    if (pozitiiValide(x, y, xCurent, yCurent) || respectaRegulaFataInFata(xCurent, yCurent, x, y, jucator))
    {
        board[xCurent][yCurent] = '.';
        board[x][y] = jucator;
        return true;
    }
    return false;
}

bool isBlockedLee(char player)
{
    bool visited[Size][Size] = {0};
    int Lin[Size * Size], Col[Size * Size];
    int prim = 1, ultim = 1;

    int startX, startY;
    for(int i=0;i<Size;i++)
       for(int j=0;j<Size;j++)
           if(board[i][j]==player)
              {
                 startX=i;
                 startY=j;
                 break;
              }

    Lin[prim] = startX;
    Col[prim] = startY;
    visited[startX][startY] = 1;

    const int dx[] = {-2, 2, 0, 0};
    const int dy[] = {0, 0, -2, 2};

    while (prim <= ultim)
    {
        int x = Lin[prim];
        int y = Col[prim];
        prim++;

        if ((player == 'A' && x == Size - 1) || (player == 'B' && x == 0) || (player == 'C' && y == Size-1) || (player == 'D' && y == 0)) return 0;

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < Size && ny >= 0 && ny < Size && !visited[nx][ny])
            {
                if (board[(x + nx) / 2][(y + ny) / 2] == '.')
                {
                    visited[nx][ny] = 1;
                    ultim++;
                    Lin[ultim] = nx;
                    Col[ultim] = ny;
                }
            }
        }
    }

    return 1;
}

bool plaseazaBariera(int x, int y, char orientare,char player, string &error)
{
    if (x >= 0 && x < Size && y >= 0 && y < Size)
    {
        if((x%2==y%2) || (orientare=='h' && x%2==0 && y%2!=0) || (orientare=='v' && x%2!=0 && y%2==0)) {error="EROARE! Nu pot fi adaugate bariere la pozitia selectata! Incearca din nou!"; return 0;}
        if (orientare == 'h' && y + 2 < Size)
        {
            if(!(x%2!=0 && y%2==0)) return 0;
            if(board[x][y]!='.' || board[x][y+2]!='.')
            {
                error= "EROARE! Nu mai pot fi adaugate bariere la pozitia  selectata! Incearca din nou!" ;
                return 0;
            }
            else
            {
                board[x][y]='-';
                board[x][y + 2]='-';
                if (isBlockedLee('A'))
                {
                    if(player=='A') error ="EROARE! Aceasta bariera iti blocheaza drumul! Incearca din nou!";
                    else error="EROARE! Aceasta bariera blocheaza drumul adversarului! Incearca din nou!";
                    board[x][y] = '.';
                    board[x][y+2] = '.';
                    return 0;
                }
                else if(isBlockedLee('B'))
                {
                    if(player=='B') error="EROARE! Aceasta bariera iti blocheaza drumul! Incearca din nou!";
                    else error="EROARE! Aceasta bariera blocheaza drumul adversarului! Incearca din nou!";
                    board[x][y] = '.';
                    board[x][y+2] = '.';
                    return 0;
                }
            }
        }
        else if (orientare == 'v' && x + 2 < Size)
        {
            if(!(x%2==0 && y%2!=0)) return 0;
            if(board[x][y]!='.' || board[x+2][y]!='.')
            {
                error= "EROARE! Nu mai pot fi adaugate bariere la pozitia selectata! Incearca din nou!";
                return 0;
            }
            else
            {
                board[x][y]='|';
                board[x + 2][y]='|';
                if (isBlockedLee('A'))
                {
                    if(player=='A') error = "EROARE! Aceasta bariera iti blocheaza drumul! Incearca din nou!";
                    else error = "EROARE! Aceasta bariera blocheaza drumul adversarului! Incearca din nou!";
                    board[x][y] = '.';
                    board[x+2][y] = '.';
                    return 0;
                }
                else if(isBlockedLee('B'))
                {
                    if(player=='B') error= "EROARE! Aceasta bariera iti blocheaza drumul! Incearca din nou!";
                    else error="EROARE! Aceasta bariera blocheaza drumul adversarului! Incearca din nou!";
                    board[x][y] = '.';
                    board[x+2][y] = '.';
                    return 0;
                }
            }
        }
        else
            {
                error= "EROARE! Bariera invalida! Incearca din nou.";
                return 0;
            }
    }

    else
        {
            error= "EROARE! Coordonate invalide! Incearca din nou.";
            return 0;
        }
    return 1;
}


bool verificaCastigator(char jucator)
{
    if (jucator == 'A')
        for (int i = 0; i < Size; ++i)
            if (board[Size - 1][i] == 'A') return true;
    if (jucator == 'B')
        for (int i = 0; i < Size; ++i)
            if (board[0][i] == 'B') return true;
    if (jucator == 'C')
        for (int i = 0; i < Size; ++i)
            if (board[i][Size-1] == 'C') return true;
    if (jucator == 'D')
        for (int i = 0; i < Size; ++i)
            if (board[i][0] == 'D') return true;
    return false;
}


bool getCellFromMouse(int mouseX, int mouseY, int &row, int &col)
{
    int totalWidth = (numLarge * cellSizeLarge) + (numSmall * cellSizeSmall);

    // verificam daca click-ul este in interiorul tablei
    if (mouseX < startX  || mouseX >= startX + totalWidth || mouseY < startY || mouseY >= startY + totalWidth)
        return false;

    int offsetX = mouseX - startX;
    int offsetY = mouseY - startY;

    // calculăm randul si coloana pe baza celulelor mari si mici
    int largeSectionWidth = cellSizeLarge + cellSizeSmall;

    int yIndex = offsetY / largeSectionWidth; // indexul pentru sectiuni
    int xIndex = offsetX / largeSectionWidth;

    int insideY = offsetY % largeSectionWidth;
    int insideX = offsetX % largeSectionWidth;

    if (insideY < cellSizeLarge && insideX < cellSizeLarge)
        {
            // este o celula mare
            row = 2 * yIndex;
            col = 2 * xIndex;
            return true;
        }
    else if (insideY >= cellSizeLarge && insideX < cellSizeLarge)
        {
            // este o bariera orizontala
            row = 2 * yIndex + 1;
            col = 2 * xIndex;
            return true;
        }
       else if (insideX >= cellSizeLarge && insideY < cellSizeLarge)
        {
            // este o bariera verticala
            row = 2 * yIndex;
            col = 2 * xIndex + 1;
            return true;
        }

    // click-ul nu se afla intr-o zona valida
    return false;
}

string transfnr(int nr)
{
    if(nr==1) return "UNA";
    if(nr==2) return "DOUA";
    if(nr==3) return "TREI";
    if(nr==4) return "PATRU";
    if(nr==5) return "CINCI";
    if(nr==6) return "SASE";
    if(nr==7) return "SAPTE";
    if(nr==8) return "OPT";
    if(nr==9) return "NOUA";
    if(nr==10) return "ZECE";
}

void drawMenu()
{

    readimagefile("meniuNOU.bmp",0,0,screenWidth,screenHeight);

    int font=4, font_size=2, direction=0;
    settextstyle(font, direction, font_size);

    // desenam si umplem dreptunghiul pentru Player vs Player

    int stx=4*screenWidth/6;
    int sty=screenHeight/3;
    setfillstyle(SOLID_FILL, COLOR(60,19,13));
    bar(stx,sty,stx+315,sty+50);
    setbkcolor(COLOR(60,19,13));
    setcolor(COLOR(239,226,207));
    outtextxy(stx+15, sty+15, "PLAYER VS PLAYER");

    // desenam si umplem dreptunghiul pentru Player vs Calculator
    sty+=80;
    setfillstyle(SOLID_FILL,COLOR(60,19,13));
    bar(stx,sty, stx+315, sty+50 );
    setbkcolor(COLOR(60,19,13));
    setcolor(COLOR(239,226,207));
    outtextxy(stx+15, sty+15, "PLAYER VS PC1");

    // desenam si umplem dreptunghiul pentru Player vs SmartCalculator
    sty+=80;
    setfillstyle(SOLID_FILL,COLOR(60,19,13));
    bar(stx, sty, stx+315, sty+50);
    setbkcolor(COLOR(60,19,13));
    setcolor(COLOR(239,226,207));
    outtextxy(stx+15, sty+15, "PLAYER VS PC2");

    // pentru instructiuni
    stx=4*screenWidth/5;
    sty=2*screenHeight/3;
    font=0, font_size=2, direction=0;
    settextstyle(font, direction, font_size);
    setfillstyle(SOLID_FILL, COLOR(179,84,2));
    fillellipse(stx,sty,55,55);
    setfillstyle(SOLID_FILL, COLOR(60,19,13));
    fillellipse(stx,sty,45,45);
    setbkcolor(COLOR(60,19,13));
    setcolor(COLOR(239,226,207));
    outtextxy(stx-40, sty-15, "AJUTOR");

    //pentru pioni
    readimagefile("emblema.bmp", stx-50,sty+70,stx+50,sty+170);

}

void GreenButton(int x, int y, int xx, int yy)
{
    setfillstyle(SOLID_FILL, GREEN);
    bar(x,y,xx,yy);
    setbkcolor(GREEN);
    setcolor(BLACK);
    int font=0, font_size=3, direction=0;
    settextstyle(font, direction, font_size);
    outtextxy(x+55, y+15, "SELECTAT");
}

void ApelMeniu(int &optiune)
{

    initwindow(screenWidth, screenHeight, " MENIU ");
    int stx, sty;
    drawMenu();
    bool selectionMade = false;
    while (!selectionMade)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);

            // verificam daca s-a apasat pe butonul Player vs Player
            stx=4*screenWidth/6;
            sty=screenHeight/3;
            if (isMouseInButton(stx, sty, stx+315, sty+50))
              {
                 selectionMade = true;
                 delay(500);
                 GreenButton(stx,sty,stx+315,sty+50);
                 optiune=1;
                 delay(600);
              }

            // verificam daca s-a apasat pe butonul Player vs Calculator
            else
            {
                sty=sty+80;
                if (isMouseInButton(stx, sty, stx+315, sty+50))
                {
                   selectionMade = true;
                   delay(500);
                   GreenButton(stx,sty, stx+315, sty+50);
                   optiune=2;
                   delay(600);
                }

                else
                {
                    // verificam daca s-a apasat pe butonul Player vs SmartCalculator
                    sty=sty+80;
                    if (isMouseInButton(stx, sty, stx+315, sty+50))
                    {
                       selectionMade = true;
                       delay(500);
                       GreenButton(stx, sty, stx+315, sty+50);
                       optiune=3;
                       delay(600);
                    }
                    else
                    {
                       // verificam daca s-a apasat pe butonul de instructiuni
                       stx=4*screenWidth/5;
                       sty=2*screenHeight/3;
                       if(isMouseInButton(stx-60,sty-60, stx+50 ,sty+50))
                       {
                          delay(400);
                          optiune=4;
                          selectionMade=true;
                          closegraph();

                       }
                       // verificam daca s-a apasat pe butonul pentry alegerea pionilor
                       else if(isMouseInButton(stx-50,sty+70,stx+50,sty+170))
                       {
                           delay(400);
                           optiune=5;
                           selectionMade=true;
                           closegraph();

                       }
                    }
                }
             }
         }
    }
}

void Castig_Calculator(int &optiune)
{
    initwindow(screenWidth, screenHeight, " PIERZATOR ");
    readimagefile("pierdut.bmp",0,0,screenWidth,screenHeight);
    while(true)
    {
        if(kbhit())
        {
            char c=getch();
            if(c==27)
            {
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
            }
        }
    }
    cleardevice();

}

void Castig_Player(int &optiune,const string &nume)
{
    initwindow(screenWidth, screenHeight, " CASTIGATOR ");
    readimagefile("castig2.bmp",0,0,screenWidth,screenHeight);

    int visiniu = COLOR(139, 0, 0);
    setcolor(visiniu);
    settextstyle(GOTHIC_FONT, 0, 8);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setbkcolor(getpixel(screenWidth / 2, screenHeight / 2));
    outtextxy(screenWidth / 2, screenHeight / 2, const_cast<char*>(nume.c_str()));

    getch();
    while(true)
    {
        if(kbhit())
        {
            char c=getch();
            if(c==27)
            {
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
            }
        }
    }
    cleardevice();

}

void Castig_Player2(int &optiune,const string &nume)
{
    initwindow(screenWidth, screenHeight, " CASTIGATOR ");
    readimagefile("castig1.bmp",0,0,screenWidth,screenHeight);

    getch();
    while(true)
    {
        if(kbhit())
        {
            char c=getch();
            if(c==27)
            {
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
            }
        }
    }
    cleardevice();

}

void doijucatori(const string &player1,const string &player2,const string &player3,const string &player4,int &optiune)
{
    bool rulare = true;
    char jucatorCurent = 'A';

    string messageA,messageB,message,error;
    string barrierMessageA,barrierMessageB,barrierMessage;
    string messageC,messageD;
    string barrierMessageC,barrierMessageD;
    bariereA = 10, bariereB = 10;
    bariereC = 5, bariereD = 5;
    if(mod==4)
        bariereA=bariereB=5;
    int activePage = 0;
    error="";
    while (rulare)
    {
        setactivepage(activePage);
        setvisualpage(1 - activePage);
        cleardevice();

        if (kbhit())
        {
            char c = getch();
            if (c == 27)
                rulare = false;
            if(c=='r' || c=='R') orientare = (orientare == 'h') ? 'v' : 'h';
        }

        messageA = player1;
        if(bariereA>0) barrierMessageA="BARIERE RAMASE: "+ transfnr(bariereA);
        else barrierMessageA="NICIO BARIERA RAMASA!";

        messageB = player2;
        if(bariereB>0) barrierMessageB="BARIERE RAMASE: "+ transfnr(bariereB);
        else barrierMessageB="NICIO BARIERA RAMASA!";

        if(mod==2)
        {
            messageC="";
            barrierMessageC="";
            messageD="";
            barrierMessageD="";
        }
        else
        {
            messageC = player3;
            if(bariereC>0) barrierMessageC="BARIERE RAMASE: "+ transfnr(bariereC);
            else barrierMessageC="NICIO BARIERA RAMASA!";

            messageD = player4;
            if(bariereD>0) barrierMessageD="BARIERE RAMASE: "+ transfnr(bariereD);
            else barrierMessageD="NICIO BARIERA RAMASA!";
        }


        if (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN)) // Verifică dacă un buton de mouse a fost apăsat
        {
            int x,y;
            error="";
            getCellFromMouse(mousex(), mousey(),x,y);
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);

                if (mutaJucator(jucatorCurent, x, y))
                {
                    if (verificaCastigator(jucatorCurent))
                    {

                        if(jucatorCurent=='A') Castig_Player(optiune,player1);
                        else if(jucatorCurent=='B') Castig_Player(optiune,player2);
                        if(mod==4)
                        {
                            if(jucatorCurent=='C') Castig_Player(optiune,player3);
                            else if(jucatorCurent=='D') Castig_Player(optiune,player4);
                        }
                        rulare = false;
                    }
                    if(mod==2) jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                    else
                    {
                        if(jucatorCurent=='A') jucatorCurent='B';
                        else if(jucatorCurent=='B') jucatorCurent='C';
                             else if(jucatorCurent=='C') jucatorCurent='D';
                                  else if(jucatorCurent=='D') jucatorCurent='A';
                    }
                }
            }
            else if (ismouseclick(WM_RBUTTONDOWN))
            {
                clearmouseclick(WM_RBUTTONDOWN);
                getCellFromMouse(mousex(), mousey(),x,y);
                if ((jucatorCurent == 'A' && bariereA <= 0) || (jucatorCurent == 'B' && bariereB <= 0) || (jucatorCurent == 'C' && bariereC <= 0) || (jucatorCurent == 'D' && bariereD <= 0)) error= "OOPS! Nu mai ai bariere disponibile. Fa o mutare!";
                else
                {
                    if (jucatorCurent == 'A' && bariereA > 0)
                    {
                        if (plaseazaBariera(x, y,orientare, jucatorCurent,error))
                        {
                          bariereA--;
                          if(mod==2) jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                          else jucatorCurent='B';
                        }
                        else drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,messageC, barrierMessageC, messageD, barrierMessageD,jucatorCurent,error);
                        if(bariereA>0) barrierMessageA="BARIERE RAMASE: "+ transfnr(bariereA);
                        else barrierMessageA="NICIO BARIERA RAMASA!";

                    }
                    else if (jucatorCurent == 'B' && bariereB > 0)
                    {
                        if (plaseazaBariera(x, y,orientare, jucatorCurent,error))
                        {
                            bariereB--;
                            if(mod==2) jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                            else jucatorCurent='C';
                        }
                        else drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,messageC, barrierMessageC, messageD, barrierMessageD, jucatorCurent,error);
                        if(bariereB>0) barrierMessageB="BARIERE RAMASE: "+ transfnr(bariereB);
                        else barrierMessageB="NICIO BARIERA RAMASA!";
                    }
                    else if (jucatorCurent == 'C' && bariereC > 0)
                    {
                        if (plaseazaBariera(x, y,orientare, jucatorCurent,error))
                        {
                            bariereC--;
                            jucatorCurent='D';
                        }
                        else drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,messageC, barrierMessageC, messageD, barrierMessageD, jucatorCurent,error);
                        if(bariereC>0) barrierMessageC="BARIERE RAMASE: "+ transfnr(bariereC);
                        else barrierMessageC="NICIO BARIERA RAMASA!";
                    }
                    else if (jucatorCurent == 'D' && bariereD > 0)
                    {
                        if (plaseazaBariera(x, y,orientare, jucatorCurent,error))
                        {
                            bariereD--;
                            jucatorCurent='A';
                        }
                        else drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,messageC, barrierMessageC, messageD, barrierMessageD, jucatorCurent,error);
                        if(bariereD>0) barrierMessageD="BARIERE RAMASE: "+ transfnr(bariereD);
                        else barrierMessageD="NICIO BARIERA RAMASA!";
                    }
                }
            }
        }


        cleardevice();
        drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,messageC, barrierMessageC, messageD, barrierMessageD,jucatorCurent,error);
        drawboard2(jucatorCurent);
        delay(100);
        activePage = 1 - activePage;

    }
}

void moveAI(char player,string &error)
{

    int bariereRamase = (player == 'A') ? bariereA : bariereB;
    int decideActiune = rand() %  2; // 0 = pune barieră, 1 = mutare pion

    if (decideActiune == 0 && bariereRamase > 0)
    {
        int incercari = 0;
        while (incercari < 100)
        {
            int x = rand() % Size;
            int y = rand() % Size;
            char orientare = (rand() % 2 == 0) ? 'h' : 'v';
            if (plaseazaBariera(x, y, orientare, player,error))
            {
                if (player == 'A')
                    bariereA--;
                else
                    bariereB--;

                return;
            }
            error="";
            incercari++;
        }
    }

    int currentX = -1, currentY = -1;

    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)
            if (board[i][j] == player)
            {
                currentX = i;
                currentY = j;
                break;
            }

    const int dx[] = {-2, 2, 0, 0};
    const int dy[] = {0, 0, -2, 2};

    int incercari = 0;
    while (incercari < 100)
    {
        int dir = rand() % 4;
        int newX = currentX + dx[dir];
        int newY = currentY + dy[dir];

        if (pozitiiValide(newX, newY, currentX, currentY) || respectaRegulaFataInFata(currentX, currentY, newX, newY, player))
        {
            board[currentX][currentY] = '.';
            board[newX][newY] = player;
            return;
        }
        incercari++;
    }
}

void joccalculator(const string &player1,int &optiune)
{
    bool rulare = true;
    char jucatorCurent = 'A';
    int activePage = 0;
    string messageA,messageB,message,error="";
    string barrierMessageA,barrierMessageB,barrierMessage;
    bariereA = 10, bariereB = 10;
    while (rulare)
    {
         setactivepage(activePage);
         setvisualpage(1 - activePage);
         cleardevice();

        if (kbhit())
        {
            char c = getch();
            if (c == 27) // Escape key
                rulare = false;
            if(c=='r' || c=='R') orientare = (orientare == 'h') ? 'v' : 'h';
        }

        messageA = player1;
        if(bariereA>0) barrierMessageA="BARIERE RAMASE: "+ transfnr(bariereA);
        else barrierMessageA="NICIO BARIERA RAMASA!";

        messageB = "Calculator";
        if(bariereB>0) barrierMessageB="BARIERE RAMASE: "+ transfnr(bariereB);
        else barrierMessageB="NICIO BARIERA RAMASA!";


        if (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN))
        {

            int x,y;
            error="";
            getCellFromMouse(mousex(), mousey(),x,y);
            if (jucatorCurent == 'A' && ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                if (mutaJucator(jucatorCurent, x, y))
                {
                    if (verificaCastigator(jucatorCurent))
                    {
                        Castig_Player2(optiune,player1);
                        rulare = false;
                    }
                    jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                }
            }
            else if (ismouseclick(WM_RBUTTONDOWN))
            {
                clearmouseclick(WM_RBUTTONDOWN);
                if (jucatorCurent == 'A' && bariereA <= 0) error= "OOPS! Nu mai ai bariere disponibile. Fa o mutare!";
                else
                {
                    if (jucatorCurent == 'A' && bariereA > 0)
                    {
                        if (plaseazaBariera(x, y, orientare, jucatorCurent,error))
                        {
                            bariereA--;
                            jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                        }
                        else drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,"", "", "", "",jucatorCurent,error);
                        if(bariereA>0) barrierMessageA="BARIERE RAMASE: "+ transfnr(bariereA);
                        else barrierMessageA="NICIO BARIERA RAMASA!";
                    }
                }
            }
        }
        else
        {
            string error1="";

            if (jucatorCurent == 'B')
            {
               delay(1000);
               moveAI('B',error1);

               if (verificaCastigator('B'))
               {
                 Castig_Calculator(optiune);
                 rulare = false;
               }
               jucatorCurent = 'A';
             }
        }


        drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,"","","","",jucatorCurent,error);
        if(jucatorCurent=='A')  drawboard2('A');
        delay(100);
        activePage = 1 - activePage;
    }

}


// functie pentru gasirea celei mai scurte cai folosind BFS (distanta pana la linia de castig)
int calculeazaDistanta(char player)
{
    int dist[Size][Size] = {0};
    int Lin[Size * Size], Col[Size * Size];
    int startX, startY, prim = 1, ultim = 1;
    int minim=1e9;

    for(int i=0;i<Size;i++)
        for(int j=0;j<Size;j++)
            if(board[i][j]=='.') dist[i][j]=0;
            else if(board[i][j]=='|' || board[i][j]=='-') dist[i][j]=-1;
                 else if(board[i][j]==player) { dist[i][j]=1; startX=i; startY=j;}
                      else dist[i][j]=-1;
    Lin[prim] = startX; Col[prim] = startY;
    const int dx[] = {-2, 2, 0, 0};
    const int dy[] = {0, 0, -2, 2};
    int counter = 0;

    while (prim <= ultim)
    {
        int x = Lin[prim], y = Col[prim];
        prim++;
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < Size && ny >= 0 && ny < Size && (dist[nx][ny]==0 || dist[x][y]+1<dist[nx][ny]))
            {
                if (dist[(x+nx)/2][(ny+y)/2] != -1)
                {
                    dist[nx][ny] = dist[x][y] + 1;
                    ultim++;
                    Lin[ultim] = nx;
                    Col[ultim] = ny;
                }
            }
        }

    }
    if(player=='A')
        for(int i=0;i<Size;i+=2)
           if(dist[16][i]>0 && dist[16][i]<minim) minim=dist[16][i];
    if(player=='B')
        for(int i=0;i<Size;i+=2)
           if(dist[0][i]>0 && dist[0][i]<minim) minim=dist[0][i];
    return minim; // distanta mare daca nu exista drum valid
}


void eliminaBariera(int x, int y, char orientare)
{
    if (orientare == 'h')
    {
        // stergem bariera orizontala
        board[x][y] = '.';
        board[x][y + 1] = '.';
        board[x][y + 2] = '.';
    }
    else if (orientare == 'v')
    {
        // stergem bariera verticala
        board[x][y] = '.';
        board[x + 1][y] = '.';
        board[x + 2][y] = '.';
    }
}

bool plaseazaBarieraEficient(char player)
{
    char adversar = (player == 'A') ? 'B' : 'A';
    int distAdversar = calculeazaDistanta(adversar);
    int xCandidat = -1, yCandidat = -1;
    char orientareCandidata = 'h';
    string barrierMessage;

    for (int x = 0; x < Size; x++)
        for (int y = 0; y < Size; y++)
            for (char orientare='h';orientare<='v';orientare+=14)
                if(board[x][y]=='.' && !(x%2==0 && y%2==0))
                   if (plaseazaBariera(x, y, orientare, player,barrierMessage))
                   {
                        int nouaDistAdversar = calculeazaDistanta(adversar);
                        if (nouaDistAdversar > distAdversar)
                        { // creste distanta adversarului
                            xCandidat = x;
                            yCandidat = y;
                            orientareCandidata = orientare;
                        }
                        // revoca bariera pentru a testa alte pozitii
                        eliminaBariera(x, y, orientare);
                   }

    if (xCandidat != -1)
    {
        // plaseaza bariera cea mai eficienta
        plaseazaBariera(xCandidat, yCandidat, orientareCandidata, player,barrierMessage);
        return true;
    }
    return false;
}


void ai2(char player)
{
    char adversar = (player == 'A') ? 'B' : 'A';

    int distPlayer = calculeazaDistanta(player); // distanța AI-ului pana la linia de castig
    int distAdversar = calculeazaDistanta(adversar); // distanta adversarului pana la linia de castig
    if(bariereB>0 && distAdversar<distPlayer && plaseazaBarieraEficient('B')) bariereB--;
    else
    {
        // daca nu este nevoie sa blocheze, muta pionul spre cea mai scurta cale
        int xCurent, yCurent;
        for (int i = 0; i < Size; i++)
           for (int j = 0; j < Size; j++)
              if (board[i][j] == player)
              {
                 xCurent = i;
                 yCurent = j;
                 break;
              }
        const int dx[] = {-2, 2, 0, 0,-2,-2,2,2,-4,4,0,0};
        const int dy[] = {0, 0, -2, 2,-2,2,-2,2,0,0,-4,4};
        int mx,my,minim=1e9,p;
        bool foundValidMove = false;
        for (int k = 0; k < 12; k++)
        {
           int nx = xCurent + dx[k], ny = yCurent + dy[k];
           if (pozitiiValide(nx, ny, xCurent, yCurent) || respectaRegulaFataInFata(xCurent,yCurent,nx,ny,player))
           {
              foundValidMove = true;
              board[nx][ny]=player;
              board[xCurent][yCurent]='.';
              p=calculeazaDistanta(player);
              if(p<minim)
              {
                 mx=nx;
                 my=ny;
                 minim=p;
              }
              board[nx][ny]='.';
              board[xCurent][yCurent]=player;
           }
        }

       mutaJucator(player,mx,my);
    }
}


void jocstrategie(const string &player1, int &optiune)
{
    bool rulare = true;
    char jucatorCurent = 'A';
    int activePage = 0;
    string messageA,messageB,message,error="";
    string barrierMessageA,barrierMessageB,barrierMessage;
    bariereA = 10, bariereB = 10;
    while (rulare)
    {
         setactivepage(activePage);
         setvisualpage(1 - activePage);
         cleardevice();

        if (kbhit())
        {
            char c = getch();
            if (c == 27) // Escape key
                rulare = false;
            if(c=='r' || c=='R') orientare = (orientare == 'h') ? 'v' : 'h';

        }

        messageA = player1;
        if(bariereA>0) barrierMessageA="BARIERE RAMASE: "+ transfnr(bariereA);
        else barrierMessageA="NICIO BARIERA RAMASA!";

        messageB = "CALCULATOR";
        if(bariereB>0) barrierMessageB="BARIERE RAMASE: "+ transfnr(bariereB);
        else barrierMessageB="NICIO BARIERA RAMASA!";

        if (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN))
        {

            int x,y;
            error="";
            getCellFromMouse(mousex(), mousey(),x,y);
            if (jucatorCurent == 'A' && ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                if (mutaJucator(jucatorCurent, x, y))
                {
                    if (verificaCastigator(jucatorCurent))
                    {
                        Castig_Player2(optiune,player1);
                        rulare = false;
                    }
                    jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                }
            }
            else if (ismouseclick(WM_RBUTTONDOWN))
            {
                clearmouseclick(WM_RBUTTONDOWN);
                if (jucatorCurent == 'A' && bariereA <= 0) error= "OOPS! Nu mai ai bariere disponibile. Fa o mutare!";
                else
                {
                    if (jucatorCurent == 'A' && bariereA > 0)
                    {
                        if (plaseazaBariera(x, y, orientare, jucatorCurent,error))
                        {
                            bariereA--;
                            jucatorCurent = (jucatorCurent == 'A') ? 'B' : 'A';
                        }
                        else drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,"","","","",jucatorCurent,error);
                        if(bariereA>0) barrierMessageA="BARIERE RAMASE: "+ transfnr(bariereA);
                        else barrierMessageA="NICIO BARIERA RAMASA!";
                    }
                }
            }
        }

            if (jucatorCurent == 'B')
            {
                delay(200);
                ai2('B');
                if (verificaCastigator('B'))
                {
                   Castig_Calculator(optiune);
                   rulare = false;
                }
                jucatorCurent = 'A';
            }

        drawBoard2(messageA, barrierMessageA, messageB, barrierMessageB,"","","","",jucatorCurent,error);
        if(jucatorCurent=='A')  drawboard2('A');
        delay(100);
        activePage = 1 - activePage;
    }

}


void Instructiuni()
{
    cleardevice();
    int backgroundColor = COLOR(239, 226, 207);
    setbkcolor(backgroundColor);
    cleardevice();

    int textColor = COLOR(89, 40, 35);
    setcolor(textColor);

    // Titlu
    settextstyle(GOTHIC_FONT, 0, 4);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(screenWidth / 2, 50, "CUM SE JOACA?");


    settextstyle(GOTHIC_FONT, 0, 2);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    int startX = 50, startY = 150, lineSpacing = 40;

    outtextxy(startX, startY, "Quoridor este un joc de strategie abstracta conceput pentru 2 sau 4 jucatori.");
    outtextxy(startX, startY += lineSpacing, "Are o tabla de 9X9.");
    outtextxy(startX, startY += lineSpacing, "Cate 2 pioni sunt asezati fata in fata pe prima linie, respectiv ultima linie.");
    outtextxy(startX, startY += lineSpacing, "Pentru 4 jucatori mai sunt 2 pioni asezati fata in fata pe prima coloana, repectiv ultima coloana. ");

    startY += 50;
    outtextxy(startX, startY, "CARE ESTE SCOPUL JOCULUI?");
    outtextxy(startX, startY += lineSpacing, "Scopul jocului este de a-ti aduce pionul de pe marginea initiala a tablei pe marginea opusa.");
    outtextxy(startX, startY += lineSpacing, "Primul jucator care ajunge la linia opusa castiga.");

    startY += 50;
    outtextxy(startX, startY, "REGULI:");
    outtextxy(startX, startY += lineSpacing, "1. Fiecare jucator primeste 10 bariere, verticale/orizontale, ce pot fi plasate cu CLICK DREAPTA.");
    outtextxy(startX, startY += lineSpacing, "   Schimbarea orientarii acestora se face apasand tasta R. Din default, aceasta este orizontala.");
    outtextxy(startX, startY += lineSpacing, "2. Pionii pot fi mutati o celula in directiile sus, jos, stanga, dreapta cu CLICK STANGA.");
    outtextxy(startX, startY += lineSpacing, "3. Jucatorii nu au voie sa blocheze complet caile adversarului catre linia finala.");
    outtextxy(startX, startY += lineSpacing, "4. Daca pionii se afla pe celule adiacente fara bariere intre ei, un jucator poate sari peste pionul adversar.");


    startY += 100;
    settextstyle(GOTHIC_FONT, 0, 2);
    outtextxy(screenWidth / 2, startY, "Apasa ESC pentru a reveni la meniul principal.");

    while (true) {
        if (kbhit()) {
            char c = getch();
            if (c == 27) // escape
                break;
        }
    }
}


void nrjucatori(int &optiune)
{
    initwindow(screenWidth, screenHeight, "Numar jucatori");
    readimagefile("player.bmp",0,0,screenWidth,screenHeight);

     // setăm culoarea textului si fundalului
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, COLOR(101, 33, 33));

    // dimensiuni pentru butoane
    int buttonWidth = 250;
    int buttonHeight = 222;

    // coordonate pentru butonul "2 Jucători"
    int btn2X1 = (screenWidth - buttonWidth) / 2 - 150; // centrat pe mijloc și spre stânga
    int btn2Y1 = (screenHeight - buttonHeight) / 2 + 77;
    int btn2X2 = btn2X1 + buttonWidth;
    int btn2Y2 = btn2Y1 + buttonHeight;

    // coordonate pentru butonul "4 Jucători"
    int btn4X1 = (screenWidth - buttonWidth) / 2 + 150; // centrat pe mijloc și spre dreapta
    int btn4Y1 = (screenHeight - buttonHeight) / 2 + 77 ;
    int btn4X2 = btn4X1 + buttonWidth;
    int btn4Y2 = btn4Y1 + buttonHeight;

    // desenăm butonul "2 Jucători"
    bar(btn2X1, btn2Y1, btn2X2, btn2Y2); // fundalul butonului
    rectangle(btn2X1, btn2Y1, btn2X2, btn2Y2); // conturul

    // text pe butonul "2"
    setbkcolor(COLOR(101, 33, 33));
    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    int text2Width = textwidth("2");
    int text2Height = textheight("2");
    outtextxy(btn2X1 + (buttonWidth - text2Width) / 2, btn2Y1 + (buttonHeight - text2Height) / 2, "2");

    // desenam butonul "4 Jucători"
    bar(btn4X1, btn4Y1, btn4X2, btn4Y2); // fundalul butonului
    rectangle(btn4X1, btn4Y1, btn4X2, btn4Y2); // conturul

    // text pe butonul "4"
    int text4Width = textwidth("4");
    int text4Height = textheight("4");
    outtextxy(btn4X1 + (buttonWidth - text4Width) / 2, btn4Y1 + (buttonHeight - text4Height) / 2, "4");

    while (true)
    {
        if(kbhit())
        {
            char c=getch();
            if(c==27)
            {
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
            }
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            // verificam daca utilizatorul a facut click pe butonul "2 Jucători"
            if (x >= btn2X1 && x <= btn2X2 && y >= btn2Y1 && y <= btn2Y2)
            {
                clearmouseclick(WM_LBUTTONDOWN);
                char nume[100]="";
                mod=2;
                introduceNume(nume);
                string player1(nume);
                delay(200);
                introduceNume(nume);
                string player2(nume);
                closegraph();
                initwindow(screenWidth, screenHeight, "Quoridor - PLAYER VS PLAYER");
                initBoard();
                doijucatori(player1,player2,"","",optiune);
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
                break;
            }

            // verificam dacă utilizatorul a facut click pe butonul "4 Jucători"
            if (x >= btn4X1 && x <= btn4X2 && y >= btn4Y1 && y <= btn4Y2)
                {
                clearmouseclick(WM_LBUTTONDOWN);
                mod=4;
                char nume[100]="";
                introduceNume(nume);
                string player1(nume);
                delay(200);
                introduceNume(nume);
                string player2(nume);
                delay(200);
                introduceNume(nume);
                string player3(nume);
                delay(200);
                introduceNume(nume);
                string player4(nume);
                closegraph();
                initwindow(screenWidth, screenHeight, "Quoridor - PLAYER VS PLAYER");
                initBoard();
                doijucatori(player1,player2,player3,player4,optiune);
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
                break;
            }
        }
    }

    closegraph();
}


void nrjucatori2(int &optiune)
{

    initwindow(screenWidth, screenHeight, "Numar jucatori");
    readimagefile("player.bmp",0,0,screenWidth,screenHeight);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, COLOR(101, 33, 33));

    int buttonWidth = 250;
    int buttonHeight = 222;

    int btn2X1 = (screenWidth - buttonWidth) / 2 - 150;
    int btn2Y1 = (screenHeight - buttonHeight) / 2 + 77;
    int btn2X2 = btn2X1 + buttonWidth;
    int btn2Y2 = btn2Y1 + buttonHeight;

    int btn4X1 = (screenWidth - buttonWidth) / 2 + 150;
    int btn4Y1 = (screenHeight - buttonHeight) / 2 + 77 ;
    int btn4X2 = btn4X1 + buttonWidth;
    int btn4Y2 = btn4Y1 + buttonHeight;

    bar(btn2X1, btn2Y1, btn2X2, btn2Y2);
    rectangle(btn2X1, btn2Y1, btn2X2, btn2Y2);


    setbkcolor(COLOR(101, 33, 33));
    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    int text2Width = textwidth("2");
    int text2Height = textheight("2");
    outtextxy(btn2X1 + (buttonWidth - text2Width) / 2, btn2Y1 + (buttonHeight - text2Height) / 2, "2");

    bar(btn4X1, btn4Y1, btn4X2, btn4Y2);
    rectangle(btn4X1, btn4Y1, btn4X2, btn4Y2);

    int text4Width = textwidth("4");
    int text4Height = textheight("4");
    outtextxy(btn4X1 + (buttonWidth - text4Width) / 2, btn4Y1 + (buttonHeight - text4Height) / 2, "4");


    while (true)
    {
        if(kbhit())
        {
            char c=getch();
            if(c==27)
            {
                closegraph();
                ApelMeniu(optiune);
                ApelJoc(optiune);
                ApelInstructiuniSiPioni(optiune);
            }
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= btn2X1 && x <= btn2X2 && y >= btn2Y1 && y <= btn2Y2)
            {
                mod=2;
                break;
            }

            if (x >= btn4X1 && x <= btn4X2 && y >= btn4Y1 && y <= btn4Y2)
            {
                mod=4;
                break;
            }
        }
    }

    closegraph();

}

void ApelJoc(int &optiune)
{
    if(optiune==1) nrjucatori(optiune);
    if(optiune==2)
    {

        char nume[100]="";
        introduceNume(nume);
        string player1(nume);
        delay(100);
        closegraph();
        initwindow(screenWidth, screenHeight, "Quoridor - PLAYER VS PC1");
        mod=2;
        initBoard();
        joccalculator(player1,optiune);
        closegraph();
        ApelMeniu(optiune);
        ApelJoc(optiune);
        ApelInstructiuniSiPioni(optiune);
    }
    if(optiune==3)
    {

        char nume[100]="";
        introduceNume(nume);
        string player1(nume);
        delay(100);
        initwindow(screenWidth, screenHeight, "Quoridor - PLAYER VS PC2");
        mod=2;
        initBoard();
        jocstrategie(player1,optiune);
        closegraph();
        ApelMeniu(optiune);
        ApelJoc(optiune);
        ApelInstructiuniSiPioni(optiune);
    }
}


void Alege_Pioni(int &pion1Index,int &pion2Index,int &pion3Index,int &pion4Index, int &optiune)
{

    int backgroundColor = COLOR(60, 13, 13);
    setbkcolor(backgroundColor);
    cleardevice();

    int textColor = COLOR(255, 229, 180);
    setcolor(textColor);
    settextstyle(GOTHIC_FONT, 0, 5.5);
    settextjustify(CENTER_TEXT, TOP_TEXT);

    char filenames[14][50] =
    {
        "1.bmp", "2.bmp", "3.bmp", "4.bmp",
        "5.bmp", "6.bmp", "7.bmp", "8.bmp",
        "9.bmp", "10.bmp", "11.bmp", "12.bmp",
        "13.bmp", "14.bmp"
    };

    int imgWidth = 200, imgHeight = 200;
    int centerX = screenWidth / 2, centerY = screenHeight / 2;


    int buttonImgWidth = 60, buttonImgHeight = 60;
    int leftButtonX1 = centerX - imgWidth / 2 - buttonImgWidth - 20;
    int leftButtonY1 = centerY - buttonImgHeight / 2;
    int leftButtonX2 = leftButtonX1 + buttonImgWidth;
    int leftButtonY2 = leftButtonY1 + buttonImgHeight;

    int rightButtonX1 = centerX + imgWidth / 2 + 20;
    int rightButtonY1 = centerY - buttonImgHeight / 2;
    int rightButtonX2 = rightButtonX1 + buttonImgWidth;
    int rightButtonY2 = rightButtonY1 + buttonImgHeight;

    int okButtonWidth = imgWidth;
    int okButtonHeight = buttonImgHeight;

    int okButtonX1 = centerX - okButtonWidth / 2;
    int okButtonY1 = centerY + imgHeight / 2 + 20;
    int okButtonX2 = okButtonX1 + okButtonWidth;
    int okButtonY2 = okButtonY1 + okButtonHeight;

    int currentIndex = 0;

    for (int step = 1; step <= mod; step++)
    {
        bool selectionMade = false;

        if (step == 1)  readimagefile("25.bmp", 0, 0, screenWidth, screenHeight/2);
        else if(step==2) readimagefile("24.bmp", 0, 0, screenWidth, screenHeight/2);
            else if(step==3) readimagefile("30.bmp", 0, 0, screenWidth, screenHeight/2);
                 else readimagefile("31.bmp", 0, 0, screenWidth, screenHeight/2);

        while (!selectionMade)
        {
            if(kbhit())
            {
               char c=getch();
               if(c==27)
               {
                  closegraph();
                  ApelMeniu(optiune);
                  ApelJoc(optiune);
                  ApelInstructiuniSiPioni(optiune);
               }
            }

            readimagefile(filenames[currentIndex], centerX - imgWidth / 2, centerY - imgHeight / 2, centerX + imgWidth / 2, centerY + imgHeight / 2);

            readimagefile("stanga.bmp", leftButtonX1, leftButtonY1, leftButtonX2, leftButtonY2);
            readimagefile("dreapta.bmp", rightButtonX1, rightButtonY1, rightButtonX2, rightButtonY2);

            readimagefile("selectat.bmp", okButtonX1, okButtonY1, okButtonX2, okButtonY2);

            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                int mouseX = mousex();
                int mouseY = mousey();

                if (isMouseInButton(leftButtonX1, leftButtonY1, leftButtonX2, leftButtonY2))
                     currentIndex = (currentIndex - 1 + 14) % 14; // trecere la imaginea anterioara
                else if (isMouseInButton(rightButtonX1, rightButtonY1, rightButtonX2, rightButtonY2))
                    currentIndex = (currentIndex + 1) % 14; // trecere la urmatoarea imagine

                // verifica daca s-a apasat butonul OK
                else if (isMouseInButton(okButtonX1, okButtonY1, okButtonX2, okButtonY2))
                {
                    if (step == 1)
                        pion1Index = currentIndex;
                    else if(step==2)
                        pion2Index = currentIndex;
                        else if(step==3) pion3Index=currentIndex;
                             else pion4Index=currentIndex;
                    selectionMade = true;
                }
            }
        }
        cleardevice();
    }
    // Afișează selecția finală
    cleardevice();
    if(mod==2)
    {
        readimagefile("26.bmp", 0, 0, screenWidth, screenHeight/2);
        readimagefile(filenames[pion1Index], centerX - imgWidth - 20, centerY - imgHeight / 2, centerX - 20, centerY + imgHeight / 2);
        readimagefile(filenames[pion2Index], centerX + 20, centerY - imgHeight / 2, centerX + imgWidth + 20, centerY + imgHeight / 2);

    }
    if(mod==4)
    {
        // pozitiile pentru imaginile suplimentare
        int newImg1X1 = centerX - 2 * imgWidth - 40;  // in stanga lui pion1
        int newImg1Y1 = centerY - imgHeight / 2;
        int newImg1X2 = centerX - imgWidth - 40;
        int newImg1Y2 = centerY + imgHeight / 2;

        int newImg2X1 = centerX + imgWidth + 40;      // in dreapta lui pion2
        int newImg2Y1 = centerY - imgHeight / 2;
        int newImg2X2 = centerX + 2 * imgWidth + 40;
        int newImg2Y2 = centerY + imgHeight / 2;

        readimagefile("26.bmp", 0, 0, screenWidth, screenHeight / 2);

        // afisarea imaginilor existente
        readimagefile(filenames[pion1Index], centerX - imgWidth - 20, centerY - imgHeight / 2, centerX - 20, centerY + imgHeight / 2);
        readimagefile(filenames[pion2Index], centerX + 20, centerY - imgHeight / 2, centerX + imgWidth + 20, centerY + imgHeight / 2);

        // afisarea noilor imagini
        readimagefile(filenames[pion3Index], newImg1X1, newImg1Y1, newImg1X2, newImg1Y2);
        readimagefile(filenames[pion4Index], newImg2X1, newImg2Y1, newImg2X2, newImg2Y2);
    }

    delay(2000);
    cleardevice();
}



void ApelInstructiuniSiPioni(int &optiune)
{
     if(optiune==4)
    {
        initwindow(screenWidth,screenHeight, "Quoridor - INSTRUCTIUNI DE JOC");
        Instructiuni();
        ApelMeniu(optiune);
        ApelJoc(optiune);
        ApelInstructiuniSiPioni(optiune);
    }
    if(optiune==5)
    {
        nrjucatori2(optiune);
        initwindow(screenWidth,screenHeight,"Quoridor -  PIONI ");
        Alege_Pioni(poz1,poz2,poz3,poz4,optiune);
        ApelMeniu(optiune);
        ApelJoc(optiune);
        ApelInstructiuniSiPioni(optiune);
    }
}

int main()
{
    int optiune;
    ApelMeniu(optiune);
    ApelJoc(optiune);
    ApelInstructiuniSiPioni(optiune);
    return 0;
}
