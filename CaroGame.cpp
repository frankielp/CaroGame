#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <mmsystem.h>
#include <iomanip>
#include <string>
#include <fstream>
	
using namespace std;

// Define 
const int consoleWidth = 142, consoleHeight = 35;
//Move
#define UP				72
#define DOWN			80
#define LEFT			75
#define RIGHT			77
#define ENTER			13
#define ESC				27

//Color
#define Black			0
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define DarkRed			4
#define DarkPink		5
#define DarkYellow		6
#define DarkWhite		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15
#define Default			7 

//Prototype
//Hard
const  long Defend_Score1[7] = { 0, 1,9,81,729,6561,59049 };
const  long Attack_Score1[7] = { 0, 3, 24, 192, 1536, 12288, 98304 };
//Medium
const  long Defend_Score2[7] = { 0, 1, 9, 81, 729, 6561,59049 }; 
const  long Attack_Score2[7] = { 0, 1, 2, 3, 4, 5, 6 };
struct object
{
	int x, y;
	char icon;
	string name;
	int num = 0;
	string modeplay;
	string sizeplay;
	string levelplay;
	string result;
};
enum turn { play1, play2 };
turn playturn;
object pointer,player1,player2;
int boardsize = 3;
int key;
bool check=true;
string Music="ON ";
char Arr[10][10],mode,level;
//Define Function
void fixConsoleWindow() 
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void setConsoleWindow(int w, int h)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top, w, h, TRUE);
}
int wherex()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}
int wherey()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}
void gotoXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void control(object &X, char key)
{
	X.x = wherex();
	X.y = wherey();
	if ((int)key == LEFT)
	{
		X.x--;
		gotoXY(X.x,X.y);
	}
    else if ((int)key == RIGHT)
	{
		X.x++;
		gotoXY(X.x, X.y);
	}
    else if ((int)key == DOWN)
	{
		X.y++;
		gotoXY(X.x, X.y);
	}
    else if ((int)key == UP)
	{
		X.y--;
		gotoXY(X.x, X.y);
	}
}
void Textcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void clrscr()
{
    CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
    HANDLE	hConsoleOut;
    COORD	Home = { 0,0 };
    DWORD	dummy;

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

    FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
    csbiInfo.dwCursorPosition.X = 0;
    csbiInfo.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void hidePointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
} 
void unhidePointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//Music
void BackGround()
{
	if (check)
		PlaySound(TEXT("DummyUndertaleOST-TobyFox.wav"), NULL, SND_LOOP | SND_ASYNC);
}
void Enter()
{
	if (check)
		PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void Tap()
{
	if (check)
		PlaySound(TEXT("tap.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}
void DrawMusic()
{
	if (check)
		PlaySound(TEXT("Undertale OST_ 015 - sans.wav"), NULL, SND_LOOP | SND_ASYNC);
}
void WinMusic()
{
	if (check)
		PlaySound(TEXT("Undertale OST_ 046 - Spear of Justice.wav"), NULL, SND_LOOP | SND_ASYNC);
}
void LoseMusic()
{
	if (check)
		PlaySound(TEXT("Undertale OST_ 011 - Determination.wav"), NULL, SND_LOOP | SND_ASYNC);
}

// Print Function
void WordCaro1()
{
	hidePointer();
	int x = 20, y = 0;
	//C
	Textcolor(rand() % 15 + 1);
	gotoXY(x, y);				    cout << "ccccccccccccccc ";
	gotoXY(x - 4, y + 1);	   cout << "c::::::::::::::::c ";
	gotoXY(x - 5, y + 2);     cout << "c:::::::cccccccccc ";
	gotoXY(x - 6, y + 3); cout << "c::::::c ";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 7, y + 4); cout << "c::::::c";
	gotoXY(x - 7, y + 5); cout << "c::::::c ";
	gotoXY(x - 7, y + 6); cout << "c::::::c";
	gotoXY(x - 7, y + 7); cout << "c::::::c";
	gotoXY(x - 7, y + 8); cout << "c::::::c";
	gotoXY(x - 7, y + 9); cout << "c::::::c";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 6, y + 10); cout << "c::::::c";
	gotoXY(x - 5, y + 11);  cout << "c:::::::ccccccccc ";
	gotoXY(x - 4, y + 12);	   cout << "c:::::::::::::::c";
	gotoXY(x, y + 13);            cout << "cccccccccccccc";
	//A
	Textcolor(rand() % 15 + 1);
	gotoXY(x+=28,y=0);				    cout << "aaaaaaaaaaaa";
	gotoXY(x - 3, y + 1);	   cout << "a::::::::::::::::a";
	gotoXY(x - 4, y + 2);	   cout << "a::::::::::::::::::a";
	gotoXY(x - 5, y + 3);     cout << "a:::::aaaaaaaaaa:::::a";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 6, y + 4); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 5); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 6); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 7); cout << "a:::::aaaaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 8); cout << "a:::::aaaaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 9); cout << "a:::::a          a:::::a";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 6, y + 10); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 11); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 12);  cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 13);	   cout << "aaaaaaa          aaaaaaa";
	

	//R
	Textcolor(rand() % 15 + 1);
	gotoXY(x +=29, y = 0);				    cout << "rrrrrrrrrrrrrrr";
	gotoXY(x - 2, y + 1);	   cout << "r:::::::::::::::::r";
	gotoXY(x - 2, y + 2);	   cout << "r::::::::::::::::::r";
	gotoXY(x - 2, y + 3);     cout << "r:::::rrrrrrrr::::::r";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 2, y + 4); cout << "r:::::r       r::::::r";
	gotoXY(x - 2, y + 5); cout << "r:::::r        r::::r";
	gotoXY(x - 2, y + 6); cout << "r:::::r       r::::r";
	gotoXY(x - 2, y + 7); cout << "r::::::rrrrrrrr:::r";
	gotoXY(x - 2, y + 8); cout << "r::::::rrrrrrr:::::r";
	gotoXY(x - 2, y + 9); cout << "r:::::r        r:::::r";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 2, y + 10); cout << "r:::::r         r:::::r";
	gotoXY(x - 2, y + 11); cout << "r:::::r          r:::::r";
	gotoXY(x - 2, y + 12);  cout << "r:::::r           r:::::r";
	gotoXY(x - 2, y + 13);	   cout << "rrrrrr            rrrrrrr";
	//R
	Textcolor(rand() % 15 + 1);
	gotoXY(x+=32, y = 0);		cout << "ooooooooooooo";
	gotoXY(x - 3, y + 1);	   cout << "o:::::::::::::::::o";
	gotoXY(x - 4, y + 2);	   cout << "o:::::::::::::::::::o";
	gotoXY(x - 5, y + 3);     cout << "o::::::ooooooooo::::::o";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 6, y + 4); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 5); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 6); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 7); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 8); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 9); cout << "o::::::o         o::::::o";
	Textcolor(rand() % 15 + 1);
	gotoXY(x - 5, y + 10); cout << "o::::::ooooooooo::::::o";
	gotoXY(x - 4, y + 11); cout << "o:::::::::::::::::::o";
	gotoXY(x - 3, y + 12);  cout << "o:::::::::::::::::o";
	gotoXY(x , y + 13);	   cout << "oooooooooooooo";


}
void WordCaro2()
{
	hidePointer();
	clrscr();
	int x = 20, y = 0;
	//C
	Sleep(100);
	Textcolor(DarkYellow);
	gotoXY(x, y);				    cout << "ccccccccccccccc ";
	gotoXY(x - 4, y + 1);	   cout << "c::::::::::::::::c ";
	gotoXY(x - 5, y + 2);     cout << "c:::::::cccccccccc ";
	gotoXY(x - 6, y + 3); cout << "c::::::c ";
	gotoXY(x - 7, y + 4); cout << "c::::::c";
	gotoXY(x - 7, y + 5); cout << "c::::::c ";
	gotoXY(x - 7, y + 6); cout << "c::::::c";
	gotoXY(x - 7, y + 7); cout << "c::::::c";
	gotoXY(x - 7, y + 8); cout << "c::::::c";
	gotoXY(x - 7, y + 9); cout << "c::::::c";
	gotoXY(x - 6, y + 10); cout << "c::::::c";
	gotoXY(x - 5, y + 11);  cout << "c:::::::ccccccccc ";
	gotoXY(x - 4, y + 12);	   cout << "c:::::::::::::::c";
	gotoXY(x, y + 13);            cout << "cccccccccccccc";
	//A
	Sleep(100);
	Textcolor(DarkCyan);
	gotoXY(x += 28,y = 0);				    cout << "aaaaaaaaaaaa";
	gotoXY(x - 3, y + 1);	   cout << "a::::::::::::::::a";
	gotoXY(x - 4, y + 2);	   cout << "a::::::::::::::::::a";
	gotoXY(x - 5, y + 3);     cout << "a:::::aaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 4); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 5); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 6); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 7); cout << "a:::::aaaaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 8); cout << "a:::::aaaaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 9); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 10); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 11); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 12);  cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 13);	   cout << "aaaaaaa          aaaaaaa";


	//R
	Sleep(100);
	Textcolor(Blue);
	gotoXY(x += 29, y = 0);				    cout << "rrrrrrrrrrrrrrr";
	gotoXY(x - 2, y + 1);	   cout << "r:::::::::::::::::r";
	gotoXY(x - 2, y + 2);	   cout << "r::::::::::::::::::r";
	gotoXY(x - 2, y + 3);     cout << "r:::::rrrrrrrr::::::r";
	gotoXY(x - 2, y + 4); cout << "r:::::r       r::::::r";
	gotoXY(x - 2, y + 5); cout << "r:::::r        r::::r";
	gotoXY(x - 2, y + 6); cout << "r:::::r       r::::r";
	gotoXY(x - 2, y + 7); cout << "r::::::rrrrrrrr:::r";
	gotoXY(x - 2, y + 8); cout << "r::::::rrrrrrr:::::r";
	gotoXY(x - 2, y + 9); cout << "r:::::r        r:::::r";
	gotoXY(x - 2, y + 10); cout << "r:::::r         r:::::r";
	gotoXY(x - 2, y + 11); cout << "r:::::r          r:::::r";
	gotoXY(x - 2, y + 12);  cout << "r:::::r           r:::::r";
	gotoXY(x - 2, y + 13);	   cout << "rrrrrr            rrrrrrr";
	//R
	Sleep(100);
	Textcolor(DarkWhite);
	gotoXY(x += 32, y = 0);		cout << "ooooooooooooo";
	gotoXY(x - 3, y + 1);	   cout << "o:::::::::::::::::o";
	gotoXY(x - 4, y + 2);	   cout << "o:::::::::::::::::::o";
	gotoXY(x - 5, y + 3);     cout << "o::::::ooooooooo::::::o";
	gotoXY(x - 6, y + 4); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 5); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 6); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 7); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 8); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 9); cout << "o::::::o         o::::::o";
	gotoXY(x - 5, y + 10); cout << "o::::::ooooooooo::::::o";
	gotoXY(x - 4, y + 11); cout << "o:::::::::::::::::::o";
	gotoXY(x - 3, y + 12);  cout << "o:::::::::::::::::o";
	gotoXY(x , y + 13);	   cout << "oooooooooooooo";
}
void WordCaro3()
{
	hidePointer();
	int x = 20, y = 0;
	//C
	Textcolor(DarkYellow);
	gotoXY(x, y);				    cout << "ccccccccccccccc ";
	gotoXY(x - 4, y + 1);	   cout << "c::::::::::::::::c ";
	gotoXY(x - 5, y + 2);     cout << "c:::::::cccccccccc ";
	gotoXY(x - 6, y + 3); cout << "c::::::c ";
	gotoXY(x - 7, y + 4); cout << "c::::::c";
	gotoXY(x - 7, y + 5); cout << "c::::::c ";
	gotoXY(x - 7, y + 6); cout << "c::::::c";
	gotoXY(x - 7, y + 7); cout << "c::::::c";
	gotoXY(x - 7, y + 8); cout << "c::::::c";
	gotoXY(x - 7, y + 9); cout << "c::::::c";
	gotoXY(x - 6, y + 10); cout << "c::::::c";
	gotoXY(x - 5, y + 11);  cout << "c:::::::ccccccccc ";
	gotoXY(x - 4, y + 12);	   cout << "c:::::::::::::::c";
	gotoXY(x, y + 13);            cout << "cccccccccccccc";
	//A
	Textcolor(DarkCyan);
	gotoXY(x += 28, y = 0);				    cout << "aaaaaaaaaaaa";
	gotoXY(x - 3, y + 1);	   cout << "a::::::::::::::::a";
	gotoXY(x - 4, y + 2);	   cout << "a::::::::::::::::::a";
	gotoXY(x - 5, y + 3);     cout << "a:::::aaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 4); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 5); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 6); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 7); cout << "a:::::aaaaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 8); cout << "a:::::aaaaaaaaaaaa:::::a";
	gotoXY(x - 6, y + 9); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 10); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 11); cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 12);  cout << "a:::::a          a:::::a";
	gotoXY(x - 6, y + 13);	   cout << "aaaaaaa          aaaaaaa";


	//R
	Textcolor(Blue);
	gotoXY(x += 29, y = 0);				    cout << "rrrrrrrrrrrrrrr";
	gotoXY(x - 2, y + 1);	   cout << "r:::::::::::::::::r";
	gotoXY(x - 2, y + 2);	   cout << "r::::::::::::::::::r";
	gotoXY(x - 2, y + 3);     cout << "r:::::rrrrrrrr::::::r";
	gotoXY(x - 2, y + 4); cout << "r:::::r       r::::::r";
	gotoXY(x - 2, y + 5); cout << "r:::::r        r::::r";
	gotoXY(x - 2, y + 6); cout << "r:::::r       r::::r";
	gotoXY(x - 2, y + 7); cout << "r::::::rrrrrrrr:::r";
	gotoXY(x - 2, y + 8); cout << "r::::::rrrrrrr:::::r";
	gotoXY(x - 2, y + 9); cout << "r:::::r        r:::::r";
	gotoXY(x - 2, y + 10); cout << "r:::::r         r:::::r";
	gotoXY(x - 2, y + 11); cout << "r:::::r          r:::::r";
	gotoXY(x - 2, y + 12);  cout << "r:::::r           r:::::r";
	gotoXY(x - 2, y + 13);	   cout << "rrrrrr            rrrrrrr";
	//R
	Textcolor(DarkWhite);
	gotoXY(x += 32, y = 0);		cout << "ooooooooooooo";
	gotoXY(x - 3, y + 1);	   cout << "o:::::::::::::::::o";
	gotoXY(x - 4, y + 2);	   cout << "o:::::::::::::::::::o";
	gotoXY(x - 5, y + 3);     cout << "o::::::ooooooooo::::::o";
	gotoXY(x - 6, y + 4); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 5); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 6); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 7); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 8); cout << "o::::::o         o::::::o";
	gotoXY(x - 6, y + 9); cout << "o::::::o         o::::::o";
	gotoXY(x - 5, y + 10); cout << "o::::::ooooooooo::::::o";
	gotoXY(x - 4, y + 11); cout << "o:::::::::::::::::::o";
	gotoXY(x - 3, y + 12);  cout << "o:::::::::::::::::o";
	gotoXY(x, y + 13);	   cout << "oooooooooooooo";
}
void StandardBoard()
{
	for (int i = 0; i <= consoleHeight; i++)
	{
		Sleep(1);
		gotoXY(26, i);
		gotoXY(consoleWidth - 45, i);
		cout << (char)219;
	}
	for (int i = 1; i <= consoleWidth - 45; i++)
	{
		Sleep(1);
		gotoXY(consoleWidth - 45 - i, 26);
		cout << (char)205;
	}
	//print score 1
	gotoXY(consoleWidth - 44, 6);
	cout << (char)219 << (char)205 << (char)205 << (char)205 << (char)254;
	for (int i = 1; i <= 35; i++)
	{
		gotoXY(consoleWidth - 39 + i, 1);
		cout << (char)205;
		gotoXY(consoleWidth - 39 + i, 11);
		cout << (char)205;
	}
	for (int i = 1; i < 10; i++)
	{
		gotoXY(consoleWidth - 39, 1 + i);
		cout << (char)219;
		gotoXY(consoleWidth - 4, 1 + i);
		cout << (char)219;
	}
	gotoXY(consoleWidth - 39, 1);
	cout << (char)220;
	gotoXY(consoleWidth - 4, 1);
	cout << (char)220;
	gotoXY(consoleWidth - 39, 11);
	cout << (char)223;
	gotoXY(consoleWidth - 4, 11);
	cout << (char)223;
	//print score 2
	gotoXY(consoleWidth - 44, 17);
	cout << (char)219 << (char)205 << (char)205 << (char)205 << (char)254;
	for (int i = 1; i <= 35; i++)
	{
		gotoXY(consoleWidth - 39 + i, 13);
		cout << (char)205;
		gotoXY(consoleWidth - 39 + i, 23);
		cout << (char)205;
	}
	for (int i = 1; i < 10; i++)
	{
		gotoXY(consoleWidth - 39, 13 + i);
		cout << (char)219;
		gotoXY(consoleWidth - 4, 13 + i);
		cout << (char)219;
	}
	gotoXY(consoleWidth - 39, 13);
	cout << (char)220;
	gotoXY(consoleWidth - 4, 13);
	cout << (char)220;
	gotoXY(consoleWidth - 39, 23);
	cout << (char)223;
	gotoXY(consoleWidth - 4, 23);
	cout << (char)223;
	//print score 3
	gotoXY(consoleWidth - 44, 30);
	cout << (char)219 << (char)205 << (char)205 << (char)205 << (char)254;
	gotoXY(consoleWidth - 39, 12);
	for (int i = 1; i <= 35; i++)
	{
		gotoXY(consoleWidth - 39 + i, 25);
		cout << (char)205;
		gotoXY(consoleWidth - 39 + i, 35);
		cout << (char)205;
	}
	for (int i = 1; i < 10; i++)
	{
		gotoXY(consoleWidth - 39, 25 + i);
		cout << (char)219;
		gotoXY(consoleWidth - 4, 25 + i);
		cout << (char)219;
	}
	gotoXY(consoleWidth - 39, 25);
	cout << (char)220;
	gotoXY(consoleWidth - 4, 25);
	cout << (char)220;
	gotoXY(consoleWidth - 39, 35);
	cout << (char)223;
	gotoXY(consoleWidth - 4, 35);
	cout << (char)223;
	//print logo
	gotoXY(18, 28); cout << "     _________     _________      ________      _________  ";
	gotoXY(18, 29);	cout << "    /  ______/|   /  ___   /|    /  ___  /|    /  ____  /| ";
	gotoXY(18, 30);	cout << "   /  /______|/  /  /__/  / /   /  /__/ / /   / /    / / /  ";
	gotoXY(18, 31);	cout << "  /  /______    /  ___   / /   /  ____  \\    / /____/ / / ";
	gotoXY(18, 32);	cout << " /_________/|  /__/| /__/ /   /__/|  /__/|  /________/ /   ";
	gotoXY(18, 33);	cout << " |________|/   |__|/ |__|/    |__|/  |__|/  |________|/ ";
	//print information 1
	Textcolor(DarkGreen);
	gotoXY((35-player1.name.size())/2+ (consoleWidth - 39), 4); cout << player1.name;
	Textcolor(Default);
	gotoXY(113, 6); cout << "SYMBOL: ";
	Textcolor(Yellow);
	cout << player1.icon;
	Textcolor(Default);
	gotoXY(113, 8); cout << "MOVE	: " << player1.num;
	//print information 2
	Textcolor(DarkGreen);
	gotoXY((35 - player2.name.size()) / 2 + (consoleWidth - 39),16); cout << player2.name;
	Textcolor(Default);
	gotoXY(113, 18); cout << "SYMBOL: ";
	Textcolor(DarkCyan);
	cout << player2.icon;
	Textcolor(Default);
	gotoXY(113, 20); cout << "MOVE   : " << player2.num;
	//print guide
	Textcolor(DarkGreen);
	gotoXY(118, 28); cout << "GUIDE";
	Textcolor(Default);
	gotoXY(113, 30); cout << "ARROW KEYS: MOVE";
	gotoXY(113, 32); cout << "ENTER: CHOOSE";

}
void Board3x3()
{
	//print collumm
	for (int i = 7; i <= 19; i++)
	{
		gotoXY(30, i);
		cout << (char)186;
		gotoXY(40, i);
		cout << (char)186;
		gotoXY(50, i);
		cout << (char)186;
		gotoXY(60, i);
		cout << (char)186;
	}
	//print row
	for (int i = 30; i <= 60; i++)
	{
		gotoXY(i, 7);
		cout << (char)205;
		gotoXY(i, 11);
		cout << (char)205;
		gotoXY(i, 15);
		cout << (char)205;
		gotoXY(i, 19);
		cout << (char)205;
	}
}
void Board5x5()
{
	//print collumm
	for (int i = 5; i <= 20; i++)
	{
		gotoXY(30, i);
		cout << (char)186;
		gotoXY(36, i);
		cout << (char)186;
		gotoXY(42, i);
		cout << (char)186;
		gotoXY(48, i);
		cout << (char)186;
		gotoXY(54, i);
		cout << (char)186;
		gotoXY(60, i);
		cout << (char)186;
	}
//print row
	for (int i = 30; i <= 60; i++)
	{
		gotoXY(i,5);
		cout << (char)205;
		gotoXY(i,8);
		cout << (char)205;
		gotoXY(i, 11);
		cout << (char)205;
		gotoXY(i, 14);
		cout << (char)205;
		gotoXY(i, 17);
		cout << (char)205;
		gotoXY(i, 20);
		cout << (char)205;
	}
}
void Board7x7()
{
	//print collumm
	for (int i = 2; i <= 23; i++)
	{
		gotoXY(24, i);
		cout << (char)186;
		gotoXY(30, i);
		cout << (char)186;
		gotoXY(36, i);
		cout << (char)186;
		gotoXY(42, i);
		cout << (char)186;
		gotoXY(48, i);
		cout << (char)186;
		gotoXY(54, i);
		cout << (char)186;
		gotoXY(60, i);
		cout << (char)186;
		gotoXY(66, i);
		cout << (char)186;
	}
	//print row
	for (int i = 24; i <= 66; i++)
	{
		gotoXY(i, 2);
		cout << (char)205;
		gotoXY(i, 5);
		cout << (char)205;
		gotoXY(i, 8);
		cout << (char)205;
		gotoXY(i, 11);
		cout << (char)205;
		gotoXY(i, 14);
		cout << (char)205;
		gotoXY(i, 17);
		cout << (char)205;
		gotoXY(i, 20);
		cout << (char)205;
		gotoXY(i, 23);
		cout << (char)205;
	}
}
void Result()
{
	//height 21
	//width 129
	setConsoleWindow(1000, 400);
	clrscr();
	//boundary
	for (int i = 2; i <= 19; i++)
	{
		gotoXY(3, i);
		cout << (char)219;
		gotoXY(125, i);
		cout << (char)219;

	}
	for (int i = 3; i <= 18; i++)
	{
		gotoXY(6, i);
		cout << (char)186;
		gotoXY(122, i);
		cout << (char)186;
	}
	for (int i = 4; i <= 124; i++)
	{
		gotoXY(i, 2);
		cout << (char)223;
		gotoXY(i, 19);
		cout << (char)220;
	}
	for (int i = 6; i <= 122; i++)
	{
		gotoXY(i, 3);
		cout << (char)205;
		gotoXY(i, 18);
		cout << (char)205;
	}
	//corner
	gotoXY(6, 3); cout << (char)201;
	gotoXY(6, 18); cout << (char)200;
	gotoXY(122, 3); cout << (char)187;
	gotoXY(122, 18); cout << (char)188;
	//guide
	gotoXY(50, 21); cout << "PRESS ANY KEY TO BACK TO MENU";
}
void Winner()
{
	gotoXY(15, 7);  cout << "          ___         ___   ___   ____        ___   ____        ___   ___________    ___________    ";
	gotoXY(15, 8);  cout << "         /  /        /  /  /  /  /    \\      /  /  /    \\      /  /  /   _______/   /   ____   /   ";
	gotoXY(15, 9); cout << "        /  /  ___   /  /  /  /  /  /\\  \\    /  /  /  /\\  \\    /  /  /   /______    /   /___/  /  ";
	gotoXY(15, 10); cout << "       /  /  /  /  /  /  /  /  /  /  \\  \\  /  /  /  /  \\  \\  /  /  /   _______/   /   ___   _/  ";
	gotoXY(15, 11); cout << "      /  /__/  /__/  /  /  /  /  /    \\  \\/  /  /  /    \\  \\/  /  /   /_______   /   /   \\  \\ ";
	gotoXY(15, 12); cout << "     /______________/  /__/  /__/      \\____/  /__/      \\____/  /___________/  /___/    /__/     ";
}
void Loser()
{
	gotoXY(20, 7);  cout << "          ____          ____________   __________   ___________    ___________     ";
	gotoXY(20, 8);  cout << "         /   /         /  ______   /  /  _______/  /   _______/   /   ____   /   ";
	gotoXY(20, 9);  cout << "        /   /         /  /     /  /   \\  \\        /   /______    /   /___/  /  ";
	gotoXY(20, 10); cout << "       /   /         /  /     /  /     \\  \\      /   _______/   /   ___   _/  ";
	gotoXY(20, 11); cout << "      /   /______   /  /_____/  /  _____\\  \\    /   /_______   /   /   \\  \\ ";
	gotoXY(20, 12); cout << "     /__________/  /_________ _/  /_________/  /___________/  /___/    /__/   ";
}
void Draw()
{
	gotoXY(30, 7);  cout << "        ___________   __________    _______    ___       ____             ";
	gotoXY(30, 8);  cout << "       /  _____   /  /  ____   /   /  __   |  |   | / | /   / ";
	gotoXY(30, 9);  cout << "      /  /    /  /  /  /___/  /   /  /  |  |  |   |/  |/   /   ";
	gotoXY(30, 10); cout << "     /  /    /  /  /  ___   _/   /  /___|  |  |           /  ";
	gotoXY(30, 11); cout << "    /  /____/  /  /  /   \\  \\   /  _____   |  |    /|    /  ";
	gotoXY(30, 12); cout << "   /__________/  /__/    /__/  /__/     |__|  |___/ |___/           ";
}
void Empty(int x,int y)
{
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";
	gotoXY(x++, y++); cout << "                                                            ";

}

// Support Function
void information()
{
	switch (mode)
	{
	case 'p':
	{
		player1.modeplay = "PxP";
		player2.modeplay = "PxP";
		player1.levelplay = "NULL";
		player2.levelplay = "NULL";
	}
		break; 
	case 'c':
		player1.modeplay = "PxC";
		break;
	default:
		break;
	}
	switch (level)
	{
	case 'e':
	{
		player1.levelplay = "EASY";
		player2.levelplay = "EASY";
	}
	break;
	case 'm':
	{
		player1.levelplay = "MEDIUM";
		player2.levelplay = "MEDIUM";
	}
	break;
	case 'h':
	{
		player1.levelplay = "HARD";
		player2.levelplay = "HARD";
	}
	break;
	default:
		break;
	}
		switch (boardsize)
		{
		case 3:
		{
			player1.sizeplay = "3X3";
			player2.sizeplay = "3X3";
		}
		break;
		case 5:
		{
			player1.sizeplay = "5X5";
			player2.sizeplay = "5X5";
		}
		break;
		case 7:
		{
			player1.sizeplay = "7X7";
			player2.sizeplay = "7X7";
		}
		break;
		default:
			break;
		}
}
void saveInfor(object player, string result)
{
		player.result = result;
		ofstream Output;
		Output.open("Statistic.txt", ios::app);
		Output << player.name << " ";
		Output << player.modeplay << " ";
		Output << player.levelplay << " ";
		Output << player.sizeplay << " ";
		Output << player.result<<" ";
		Output << player.num;
		Output << "\n";
		Output.close();
}
void resetArr(char Arr[][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			Arr[i][j] = ' ';
}

void control3x3(object & player, char Arr[][10])
{
	player.x = wherex();
	player.y = wherey();
	while (((key = _getch()) != ENTER) || (Arr[(player.y - 9) / 4][(player.x - 35) / 10] !=' '))
	{
		switch (key)
		{
		case LEFT:
		{
			if (player.x > 35)
			player.x -= 10;
		}
		break;
		case RIGHT:
		{
			if (player.x < 55)
			player.x += 10;
		}
		break;
		case UP:
		{
			if (player.y > 9)
			player.y -= 4;
		}
		break;
		case DOWN:
		{
			if (player.y < 17)
			player.y += 4;
		}
		break;
		}
		gotoXY(player.x, player.y);
	}
	Tap();
	Arr[(player.y-9)/4][(player.x-35)/10] = player.icon;
	if (player.icon == player1.icon)
	{
		Textcolor(Yellow);
		cout << player.icon;
		Textcolor(Default);
	}
	else if (player.icon == player2.icon)
	{
		Textcolor(DarkCyan);
		cout << player.icon;
		Textcolor(Default);
	}
	gotoXY(player.x, player.y);
}
void control5x5(object& player, char Arr[][10])
{
	player.x = wherex();
	player.y = wherey();
	while (((key = _getch()) != ENTER) || (Arr[(player.y - 6) / 3][(player.x - 33) / 6] != ' '))
	{
		switch (key)
		{
			case LEFT:
			{
				if (player.x > 33)
					player.x -= 6;
			}
			break;
			case RIGHT:
			{
				if (player.x < 57)
					player.x += 6;
			}
			break;
			case UP:
			{
				if (player.y > 6)
					player.y -= 3;
			}
			break;
			case DOWN:
			{
				if (player.y < 18)
					player.y += 3;
			}
			break;
		}
		gotoXY(player.x, player.y);
	}
	Tap();
	Arr[(player.y-6)/3][(player.x-33)/6] = player.icon;
	if (player.icon == player1.icon)
	{
		Textcolor(Yellow);
		cout << player.icon;
		Textcolor(Default);
	}
	else if (player.icon == player2.icon)
	{
		Textcolor(DarkCyan);
		cout << player.icon;
		Textcolor(Default);
	}	gotoXY(player.x, player.y);
}
void control7x7(object& player, char Arr[][10])
{
	player.x = wherex();
	player.y = wherey();
	while (((key = _getch()) != ENTER) || (Arr[(player.y - 3) / 3][(player.x - 27) / 6] != ' '))
	{
		switch (key)
		{
		case LEFT:
		{
			if (player.x > 27)
				player.x -= 6;
		}
		break;
		case RIGHT:
		{
			if (player.x < 63)
				player.x += 6;
		}
		break;
		case UP:
		{
			if (player.y > 3)
				player.y -= 3;
		}
		break;
		case DOWN:
		{
			if (player.y < 21)
				player.y += 3;
		}
		break;
		}
		gotoXY(player.x, player.y);
	}
	Tap();
	Arr[(player.y-3)/3][(player.x-27)/6] = player.icon;
	if (player.icon == player1.icon)
	{
		Textcolor(Yellow);
		cout << player.icon;
		Textcolor(Default);
	}
	else if (player.icon == player2.icon)
	{
		Textcolor(DarkCyan);
		cout << player.icon;
		Textcolor(Default);
	}	gotoXY(player.x, player.y);
}
void chooseMenu(object& X)
{
	switch (X.y)
	{
	case 20:
	{
		Textcolor(DarkGreen);
		gotoXY((141 - 8) / 2, 20); cout << "START GAME";
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 22); cout << "SETTING";
		gotoXY((141 - 8) / 2, 20);
	}
	break;
	case 21:
	{
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 20); cout << "START GAME";
		Textcolor(DarkGreen);
		gotoXY((141 - 8) / 2, 22); cout << "SETTING";
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 24); cout << "STATISTIC";
		gotoXY((141 - 8) / 2, 21);
	}
	break;
	case 22:
	{
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 22); cout << "SETTING";
		Textcolor(DarkGreen);
		gotoXY((141 - 8) / 2, 24); cout << "STATISTIC";
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 26); cout << "ABOUT";
		gotoXY((141 - 8) / 2, 22);
	}
	break;
	case 23:
	{
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 24); cout << "STATISTIC";
		Textcolor(DarkGreen);
		gotoXY((141 - 8) / 2, 26); cout << "ABOUT";
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 28); cout << "EXIT";
		gotoXY((141 - 8) / 2, 23);
	}
	break;
	case 24:
	{
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 26); cout << "ABOUT";
		Textcolor(DarkGreen);
		gotoXY((141 - 8) / 2, 28); cout << "EXIT";
		Textcolor(Default);
		gotoXY((141 - 8) / 2, 24);
	}
	break;
	}
}
void chooseSetting(object& X, object& player1, object& player2, string& Music)
{
	switch (X.y)
	{
	case 20:
	{
		Textcolor(DarkCyan);
		gotoXY(67, 18);
		cout << "SETTING";
		gotoXY(60, 20);
		cout << "CHOOSE PLAYER ICON (X/O) : " << player1.icon << endl;
		Textcolor(Default);
		gotoXY(60, 22);
		cout << "MUSIC (ON/OFF): " << Music << endl;
		gotoXY(60, 20);
		if (key == ENTER)
		{
			Enter();
			if (player1.icon == 'X')
			{
				player1.icon = 'O';
				player2.icon = 'X';
			}
			else if (player1.icon == 'O')
			{
				player2.icon = 'O';
				player1.icon = 'X';
			}
			key = 0;
			chooseSetting(pointer, player1, player2, Music);
		}
		else
			Tap();
	}
	break;
	case 21:
	{
		Textcolor(Default);
		gotoXY(60, 20);
		cout << "CHOOSE PLAYER ICON (X/O) : " << player1.icon << endl;
		Textcolor(DarkCyan);
		gotoXY(60, 22);
		cout << "MUSIC (ON/OFF): " << Music << endl;
		Textcolor(Default);
		gotoXY(60, 24);
		cout << "SIZE OF THE GAMEBOARD (3x3/5x5/7x7): " << boardsize << "x" << boardsize<< endl;
		gotoXY(60, 21);
		key = _getch();
		if (key == 13)
		{
			Enter();
			if (Music == "ON ")
			{
				check = false;
				Music = "OFF";
			}
			else if (Music == "OFF")
			{
				check = true;
				Music = "ON ";
			}
			chooseSetting(pointer, player1,player2, Music);
		}
		Tap();
	}
	break;
	case 22:
	{
		Textcolor(Default);
		gotoXY(60, 22);
		cout << "MUSIC (ON/OFF): " << Music << endl;
		Textcolor(DarkCyan);
		gotoXY(60, 24);
		cout << "SIZE OF THE GAMEBOARD (3x3/5x5/7x7): " << boardsize << "x" << boardsize<< endl;
		gotoXY(60, 22);
		key = _getch();
		if (key == 13)
		{
			Enter();
			if (boardsize == 3)
				boardsize = 5;
			else if (boardsize == 5)
				boardsize = 7;
			else if (boardsize == 7)
				boardsize = 3;
			chooseSetting(pointer, player1, player2, Music);
		}
		Tap();
	}
		break;
	}
}
void chooseMode(object& X)
{
	switch (X.y)
	{
	case 20:
	{
		Textcolor(DarkCyan);
		gotoXY((consoleWidth - 16) / 2, 20);
		cout << "PLAY IN P-P MODE";
		Textcolor(Default);
		gotoXY((consoleWidth - 16) / 2, 22);
		cout << "PLAY IN P-C MODE" << endl;
		gotoXY((consoleWidth - 16) / 2, 20);
		mode ='p';
		Tap();
	}
	break;
	case 21:
	{
		gotoXY((consoleWidth - 16) / 2, 20);
		cout << "PLAY IN P-P MODE";
		Textcolor(DarkCyan);
		gotoXY((consoleWidth - 16) / 2, 22);
		cout << "PLAY IN P-C MODE" << endl;
		gotoXY((consoleWidth - 16) / 2, 21);
		Textcolor(Default);
		mode ='c';
		Tap();
	}
	break;
	}
}
void chooseLevel(object& X)
{
	switch (X.y)
	{
	case 20:
	{
		Textcolor(DarkCyan);
		gotoXY(141 / 2, 20); cout << "EASY";
		Textcolor(Default);
		gotoXY(141 / 2, 22); cout << "MEDIUM";
		gotoXY(141 / 2, 20);
		level = 'e';
		Tap();
	}
	break;
	case 21:
	{
		Textcolor(Default);
		gotoXY(141 / 2, 20); cout << "EASY";
		Textcolor(DarkCyan);
		gotoXY(141 / 2, 22); cout << "MEDIUM";
		Textcolor(Default);
		gotoXY(141 / 2, 24); cout << "HARD";
		gotoXY(141 / 2, 21);
		Textcolor(Default);
		level = 'm';
		Tap();
	}
	break;
	case 22:
	{
		Textcolor(Default);
		gotoXY(141/ 2, 22); cout << "MEDIUM";
		Textcolor(DarkCyan);
		gotoXY(141/ 2, 24); cout << "HARD";
		gotoXY(141 / 2, 22);
		Textcolor(Default);
		level = 'h';
		Tap();
	}
	break;
	}
}

//Check Result
//3x3
void checkcolumn3x3(char icon,char Arr[][10],int& max)
{
	for (int i = 0; i < 3; i++)
	{
		int count = 0;
		for (int j = 0; j < 3; j++)
			if (Arr[j][i] == icon)
				count += 1;
		if (max < count)
			max = count;
	}
}
void checkrow3x3(char icon, char Arr[][10], int& max)
{
	for (int i = 0; i < 3; i++)
	{
		int count = 0;
		for (int j = 0; j < 3; j++)
			if (Arr[i][j] == icon)
				count += 1;
		if (max < count)
			max = count;
	}
}
void check1stdiagonal3x3(char icon, char Arr[][10], int& max)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
		if (Arr[i][i] == icon)
			count++;
	if (max < count)
		max = count;
}
void check2nddiagonal3x3(char icon, char Arr[][10], int& max)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
		if (Arr[2-i][i] == icon)
			count++;
	if (max < count)
		max = count;
}
//5x5
void checkcolumn5x5(char icon, char Arr[][10], int& max)
{
	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
			if (Arr[j][i] == icon)
				count += 1;
		if (max < count)
			max = count;
	}
}
void checkrow5x5(char icon, char Arr[][10], int& max)
{
	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
			if (Arr[i][j] == icon)
				count += 1;
		if (max < count)
			max = count;
	}
}
void check1stdiagonal5x5(char icon, char Arr[][10], int& max)
{
	int count = 0;
	for (int i = 0; i < 5; i++)
		if (Arr[i][i] == icon)
			count++;
	if (max < count)
		max = count;
}
void check2nddiagonal5x5(char icon, char Arr[][10], int& max)
{
	int count = 0;
	for (int i = 0; i < 5; i++)
		if (Arr[4 - i][i] == icon)
			count++;
	if (max < count)
		max = count;
}
//7x7
void checkcolumn7x7(char icon, char Arr[][10], int& max)
{
	int count=0; 
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			if (Arr[j][i] == icon)
			{
				count = 0;
				for (int k = j; k < 7; k++)
					if (Arr[k][i] == icon)
						count += 1;
					else
						break;
				if (max < count)
					max = count;
			}	
	}
}
void checkrow7x7(char icon, char Arr[][10], int& max)
{
	int count = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			if (Arr[i][j] == icon)
			{
				count = 0;
				for (int k = j; k < 7; k++)
					if (Arr[i][k] == icon)
						count += 1;
					else
						break;
				if (max < count)
					max = count;
			}
		
	}
}
void check1stdiagonal7x7(char icon, char Arr[][10], int& max)
{
	int count=0;
	//
	int i = 0,j;
	while (i < 7)
	{
		if (Arr[i][i] == icon)
		{
			count = 0;
			int icount = i;
			while (Arr[icount][icount] == icon)
			{
				count += 1;
				icount += 1;
			}
		}
			i += 1;
		if (max < count)
			max = count;
	}
	//
	i = 1;
	j = 0;
	while (i < 6)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount += 1;
			}
		}
		i += 1;
		j += 1;
		if (max < count)
			max = count;
	}
	//
	i = 2;
	j = 0;
	while (i <5 )
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount += 1;
			}
		}
		i += 1;
		j += 1;
		if (max < count)
			max = count;
	}
	//
	i = 0;
	j = 1;
	while (i <= 7)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount += 1;
			}
		}
		i += 1;
		j += 1;
		if (max < count)
			max = count;
	}
	//
	i = 0;
	j = 2;
	while (i <= 7)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount += 1;
			}
		}
		i += 1;
		j += 1;
		if (max < count)
			max = count;
	}
}
void check2nddiagonal7x7(char icon, char Arr[][10], int& max)
{
	int count=0;
	//
	int i = 0, j = 6;
	while (j >= 0)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount -= 1;
			}
		}
		j -= 1;
		i += 1;
		if (max < count)
			max = count;
	}
	//
	i = 1;
	j = 6;
	while (j >= 0)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount -= 1;
			}
		}
		i += 1;
		j -= 1;
		if (max < count)
			max = count;
	}
	//
	i = 2;
	j = 6;
	while (j >= 0)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount -= 1;
			}
		}
		i += 1;
		j -= 1;
		if (max < count)
			max = count;
	}
	//
	i = 0;
	j = 5;
	while (j >= 0)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount -= 1;
			}
		}
		i += 1;
		j -= 1;
		if (max < count)
			max = count;
	}
	//
	i = 0;
	j = 4;
	while (j >= 0)
	{
		if (Arr[i][j] == icon)
		{
			count = 0;
			int icount = i, jcount = j;
			while (Arr[icount][jcount] == icon)
			{
				count += 1;
				icount += 1;
				jcount -= 1;
			}
		}
		i += 1;
		j -= 1;
		if (max < count)
			max = count;
	}
}

//Check result Function
bool check3x3(char icon, char Arr[][10])
{
	int max = 0;
	checkcolumn3x3(icon, Arr, max);
	checkrow3x3(icon, Arr, max);
	check1stdiagonal3x3(icon, Arr, max);
	check2nddiagonal3x3(icon, Arr, max);
	if (max == 3)
		return true;
	else
		return false;
}
bool check5x5(char icon, char Arr[][10])
{
	int max = 0;
	checkcolumn5x5(icon, Arr, max);
	checkrow5x5(icon, Arr, max);
	check1stdiagonal5x5(icon, Arr, max);
	check2nddiagonal5x5(icon, Arr, max);
	if (max == 5)
		return true;
	else
		return false;
}
bool check7x7(char icon, char Arr[][10])
{
	int max = 0;
	checkcolumn7x7(icon, Arr, max);
	checkrow7x7(icon, Arr, max);
	check1stdiagonal7x7(icon, Arr, max);
	check2nddiagonal7x7(icon, Arr, max);
	if (max == 5)
		return true;
	else
		return false;
}
int draw(int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (Arr[i][j] != 'X')
			{
				if (Arr[i][j] != 'O')
				{
					return 0;
				}
			}
		}
	return 1;
}

//Algorithm
//Medium
long AttackColl2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && i + count < size; count++)
	{
		if (Arr[i + count][j] == player2.icon)
			pcnum++;
		else if (Arr[i + count][j] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && i - count >= 0; count++)
	{
		if (Arr[i - count][j] == player2.icon)
			pcnum++;
		else if (Arr[i - count][j] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score2[hunum + 1];
	sum += Attack_Score2[pcnum];
	return sum;
}
long AttackRow2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size; count++)
	{
		if (Arr[i][j + count] == player2.icon)
			pcnum++;
		else if (Arr[i][j + count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >= 0; count++)
	{
		if (Arr[i][j - count] == player2.icon)
			pcnum++;
		else if (Arr[i][j - count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score2[hunum + 1];
	sum += Attack_Score2[pcnum];
	return sum;
}
long Attack1stDia2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size && i + count < size; count++)
	{
		if (Arr[i + count][j + count] == player2.icon)
			pcnum++;
		else if (Arr[i + count][j + count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >= 0 && i - count >= 0; count++)
	{
		if (Arr[i - count][j - count] == player2.icon)
			pcnum++;
		else if (Arr[i - count][j - count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score2[hunum + 1];
	sum += Attack_Score2[pcnum];
	return sum;
}
long Attack2ndDia2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j - count >= 0 && i + count < size; count++)
	{
		if (Arr[i + count][j - count] == player2.icon)
			pcnum++;
		else if (Arr[i + count][j - count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && j + count < size && i - count >= 0; count++)
	{
		if (Arr[i - count][j + count] == player2.icon)
			pcnum++;
		else if (Arr[i - count][j + count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score2[hunum + 1];
	sum += Attack_Score2[pcnum];
	return sum;
}
long DefendColl2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && i + count < size; count++)
	{
		if (Arr[i + count][j] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i + count][j] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	for (int count = 1; count < size && i - count >= 0; count++)
	{
		if (Arr[i - count][j] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i - count][j] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	sum += Defend_Score2[hunum];
	return sum;
}
long DefendRow2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size; count++)
	{
		if (Arr[i][j + count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i][j + count] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >= 0; count++)
	{
		if (Arr[i][j - count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i][j - count] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	sum += Defend_Score2[hunum];
	return sum;
}
long Defend1stDia2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size && i + count <size; count++)
	{
		if (Arr[i + count][j + count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i + count][j + count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >=0 && i -count >= 0; count++)
	{
		if (Arr[i - count][j - count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i - count][j - count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	sum += Defend_Score2[hunum];

	return sum;
}
long Defend2ndDia2(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 0; count < size && j - count >=0 && i + count < size; count++)
	{
		if (Arr[i + count][j - count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i + count][j - count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	for (int count = 0; count < size && j + count <size && i - count >= 0; count++)
	{
		if (Arr[i - count][j + count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i - count][j + count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	sum += Defend_Score2[hunum];

	return sum;
}

//Hard
long AttackColl(int i,int j,int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && i + count < size; count++)
	{
		if (Arr[i + count][j] == player2.icon)
			pcnum++;
		else if (Arr[i + count][j] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && i - count >=0; count++)
	{
		if (Arr[i - count][j] == player2.icon)
			pcnum++;
		else if (Arr[i - count][j] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	} 
	sum -= Defend_Score1[hunum+1];
	sum += Attack_Score1[pcnum];
	return sum;
}
long AttackRow(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size; count++)
	{
		if (Arr[i][j+count] == player2.icon)
			pcnum++;
		else if (Arr[i][j+count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >= 0; count++)
	{
		if (Arr[i][j-count] == player2.icon)
			pcnum++;
		else if (Arr[i][j-count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score1[hunum + 1];
	sum += Attack_Score1[pcnum];
	return sum;
}
long Attack1stDia(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size &&i+count<size; count++)
	{
		if (Arr[i + count][j+count] == player2.icon)
			pcnum++;
		else if (Arr[i + count][j+count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >=0 && i - count >=0; count++)
	{
		if (Arr[i - count][j-count] == player2.icon)
			pcnum++;
		else if (Arr[i - count][j-count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score1[hunum + 1];
	sum += Attack_Score1[pcnum];
	return sum;
}
long Attack2ndDia(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j - count >= 0 && i + count <size; count++)
	{
		if (Arr[i + count][j - count] == player2.icon)
			pcnum++;
		else if (Arr[i + count][j - count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	for (int count = 1; count < size && j + count <size && i - count >=0; count++)
	{
		if (Arr[i - count][j + count] == player2.icon)
			pcnum++;
		else if (Arr[i - count][j + count] == player1.icon)
		{
			hunum++;
			break;
		}
		else
			break;
	}
	sum -= Defend_Score1[hunum + 1];
	sum += Attack_Score1[pcnum];
	return sum;
}
long DefendColl(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && i + count < size; count++)
	{
		if (Arr[i + count][j] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i + count][j] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	for (int count = 1; count < size && i - count >= 0; count++)
	{
		if (Arr[i - count][j] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i - count][j] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	sum += Defend_Score1[hunum];
	return sum;
}
long DefendRow(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size; count++)
	{
		if (Arr[i][j + count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i][j + count] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >= 0; count++)
	{
		if (Arr[i][j - count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i][j - count] == player1.icon)
		{
			hunum++;
		}
		else
			break;
	}
	sum += Defend_Score1[hunum];
	return sum;
}
long Defend1stDia(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 1; count < size && j + count < size && i + count < size; count++)
	{
		if (Arr[i + count][j + count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i + count][j + count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	for (int count = 1; count < size && j - count >= 0 && i - count >= 0; count++)
	{
		if (Arr[i - count][j - count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i - count][j - count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	sum += Defend_Score1[hunum ];
	
	return sum;
}
long Defend2ndDia(int i, int j, int size)
{
	long sum = 0;
	int pcnum = 0;
	int hunum = 0;
	for (int count = 0; count < size && j - count >= 0 && i + count < size; count++)
	{
		if (Arr[i + count][j - count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i + count][j - count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	for (int count = 0; count < size && j + count < size && i - count >= 0; count++)
	{
		if (Arr[i - count][j + count] == player2.icon)
		{
			pcnum++;
			break;
		}
		else if (Arr[i - count][j + count] == player1.icon)
		{
			hunum++;

		}
		else
			break;
	}
	sum += Defend_Score1[hunum ];
	
	return sum;
}
//Main  Algorithm
//Easy
void randomPC(object& player2, int size, int minY, int minX, int distanceY, int distanceX)
{
	int x, y;
	do
	{
		x = rand();
		y = rand();
	} while (Arr[y % size][x % size] != ' ');
	player2.x = (x % size) * distanceX + minX;
	player2.y = (y % size) * distanceY + minY;
	gotoXY(player2.x, player2.y);
	Textcolor(DarkCyan);
	cout << player2.icon;
	Textcolor(Default);
	gotoXY(player2.x, player2.y);
	Arr[y % size][x % size] = player2.icon;
}
//Medium
int Medium3x3()// The heuristic
{
	long max_val = -1000;
	if (player2.num == 0 && Arr[1][1] == ' ')
	{
		player2.x = 1 * 10+ 35;
		player2.y = 1 * 4 + 9;
		Arr[1][1] = player2.icon;
		return 0;
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (Arr[i][j] == ' ')
				{
					long Attack = AttackColl2(i, j, 3) + AttackRow2(i, j, 3) + Attack1stDia2(i, j, 3) + Attack2ndDia2(i, j, 3);
					long Defend = DefendColl2(i, j, 3) + DefendRow2(i, j, 3) + Defend1stDia2(i, j, 3) + Defend2ndDia2(i, j, 3);
					if (max_val <= max(Attack, Defend))
					{
						max_val = max(Attack, Defend);
						player2.x = j * 10 + 35;
						player2.y = i * 4 + 9;
					}
				}
	}
	return 0;
}
int Medium5x5()// The heuristic
{
	long max_val = -1000;
	if (player2.num == 0 && Arr[2][2] == ' ')
	{
		player2.x = 2 * 6 + 33;
		player2.y = 2 * 3 + 6;
		Arr[2][2] = player2.icon;
		return 0;
	}
	else
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (Arr[i][j] == ' ')
				{
					long Attack = AttackColl(i, j, 5) + AttackRow(i, j, 5) + Attack1stDia(i, j, 5) + Attack2ndDia(i, j, 5);
					long Defend = DefendColl(i, j, 5) + DefendRow(i, j, 5) + Defend1stDia(i, j, 5) + Defend2ndDia(i, j, 5);
					if (max_val <= max(Attack, Defend))
					{
						max_val = max(Attack, Defend);
						player2.x = j * 6 + 33;
						player2.y = i * 3 + 6;
					}
				}
	}
	return 0;
}
int Medium7x7()// The heuristic
{
	long max_val = -1000;
	if (player2.num == 0 && Arr[3][3] == ' ')
	{
		player2.x = 3 * 6 + 27;
		player2.y = 3 * 3 + 3;
		return 0;
	}
	else
	{
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				if (Arr[i][j] == ' ')
				{
					long Attack = AttackColl(i, j, 7) + AttackRow(i, j, 7) + Attack1stDia(i, j, 7) + Attack2ndDia(i, j, 7);
					long Defend = DefendColl(i, j, 7) + DefendRow(i, j, 7) + Defend1stDia(i, j, 7) + Defend2ndDia(i, j, 7);
					if (max_val <= max(Attack, Defend))
					{
						max_val = max(Attack, Defend);
						player2.x = j * 6 + 27;
						player2.y = i * 3 + 3;
					}
				}
	}
	return 0;
}
//Hard
int minimax3x3(bool flag)// The minimax function
{
	int max_val = -1000, min_val = 1000;
	int i, j, value = 1;
	if (check3x3(player2.icon, Arr))
	{
		return 10;
	}
	else if (check3x3(player1.icon, Arr))
	{
		return -10;
	}
	else if (draw(3))
	{
		return 0;
	}
	//if score[i][i]=1 then it is empty
	int score[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			score[i][j] = 1;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (Arr[i][j] == ' ')
			{
				if (min_val > max_val) // reverse of alpha beta pruning condition
				{
					if (flag == true)
					{
						Arr[i][j] = player2.icon;
						value = minimax3x3(false);

					}
					else
					{
						Arr[i][j] = player1.icon;
						value = minimax3x3(true);
					}
					Arr[i][j] = ' ';
					score[i][j] = value;
				}
			}
		}

	if (flag == true)
	{
		max_val = -1000;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				if (score[i][j] > max_val && score[i][j] != 1)
				{
					max_val = score[i][j];
					player2.x = j * 10 + 35;
					player2.y = i * 4 + 9;
				}
			}
		return max_val;
	}
	if (flag == false)
	{
		min_val = 1000;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				if (score[i][j] < min_val && score[i][j] != 1)
				{
					min_val = score[i][j];
					player2.x = j * 10 + 35;
					player2.y = i * 4 + 9;
				}

			}
		return min_val;
	}
}
int Hard5x5()// The heuristic
{
	long max_val = -1000;
	if (player2.num == 0 && Arr[2][2] == ' ')
	{
		player2.x = 2 * 6 + 33;
		player2.y = 2 * 3 + 6;
		Arr[2][2] = player2.icon;
		return 0;
	}
	else
	{
		for(int i=0;i<5;i++)
			for (int j=0;j<5;j++)
				if (Arr[i][j] == ' ')
				{
					long Attack = AttackColl(i,j,5) + AttackRow(i, j,5) + Attack1stDia(i, j,5) + Attack2ndDia(i, j,5);
					long Defend = DefendColl(i, j,5) + DefendRow(i, j,5) + Defend1stDia(i, j,5) + Defend2ndDia(i, j,5);
					if (max_val <= max(Attack, Defend))
					{
						max_val = max(Attack, Defend);
						player2.x = j * 6 + 33;
						player2.y = i * 3 + 6;
					}
				}
	}
	return 0;
}
int Hard7x7()// The heuristic
{
	long max_val = -1000;
	if (player2.num == 0 && Arr[3][3] == ' ')
	{
		player2.x = 3 * 6 + 27;
		player2.y = 3 * 3 + 3;
		return 0;
	}
	else
	{
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				if (Arr[i][j] == ' ')
				{
					long Attack = AttackColl(i, j, 7) + AttackRow(i, j, 7) + Attack1stDia(i, j, 7) + Attack2ndDia(i, j, 7);
					long Defend = DefendColl(i, j, 7) + DefendRow(i, j, 7) + Defend1stDia(i, j, 7) + Defend2ndDia(i, j, 7);
					if (max_val <= max(Attack, Defend))
					{
						max_val = max(Attack, Defend);
						player2.x = j * 6 + 27;
						player2.y = i * 3 + 3;
					}
				}
	}
	return 0;
}

// Play Function
void PlayPP()
{
	player1.num = 0;
	player2.num = 0;
	information();
	clrscr();
	gotoXY((consoleWidth - 40) / 2,(consoleHeight-5)/2);
	cout << "ENTER NAME OF PLAYER 1 (NO SPACE): ";
	cin >> player1.name;
	gotoXY((consoleWidth - 40) / 2, (consoleHeight - 5) / 2+2);
	cout << "ENTER NAME OF PLAYER 2 (NO SPACE): ";
	cin>>player2.name;
	clrscr();
	StandardBoard();
	switch (boardsize)
	{
		case 3:
		{
			resetArr(Arr);
			Board3x3();
			gotoXY(35,9);
			unhidePointer();
			playturn = play1;
			while (1)
			{
				switch (playturn)
				{
					case play1:
					{
						control3x3(player1,Arr);
						player1.num++;
						Textcolor(Default);
						gotoXY(113, 8); cout << "MOVE	: " << player1.num;
						gotoXY(player1.x, player1.y);
						playturn = play2;
					}
					break;
					case play2:
					{
						control3x3(player2,Arr);
						player2.num++;
						Textcolor(Default);
						gotoXY(113, 20); cout << "MOVE	: " << player2.num;
						gotoXY(player2.x, player2.y);
						playturn = play1;
					}
						break;
				}
				
				if (check3x3(player1.icon, Arr))
				{
					saveInfor(player1, "WIN");
					saveInfor(player2, "LOSE");
					hidePointer();
					Sleep(800);
					WinMusic();
					clrscr();
					while (!_kbhit())
					{
						Textcolor(rand() % 15 + 1);
						Result();
						Winner();
						Sleep(400);
					}
					Textcolor(Default);
					break;
				}
				else if (check3x3(player2.icon, Arr))
				{
					saveInfor(player2, "WIN");
					saveInfor(player1, "LOSE");
					hidePointer();
					Sleep(800);
					WinMusic();
					while (!_kbhit())
					{
						clrscr();
						Textcolor(rand() % 15 + 1);
						Result();
						Winner();
						Sleep(400);
					}
					Textcolor(Default);
					break;
				}
				else if (draw(3))
				{
					saveInfor(player1, "DRAW");
					saveInfor(player2, "DRAW");
					hidePointer();
					Sleep(800);
					DrawMusic();
					while (!_kbhit())
					{
						clrscr();
						Result();
						Draw();
						Sleep(400);
					}
					break;
				}
			}
		}
		break;
		case 5:
		{
			resetArr(Arr);
			Board5x5();
			gotoXY(33, 6);
			unhidePointer();
			playturn = play1;
			while (1)
			{
				switch (playturn)
				{
				case play1:
				{
					control5x5(player1, Arr);
					player1.num++;
					Textcolor(Default);
					gotoXY(113, 8); cout << "MOVE	: " << player1.num;
					gotoXY(player1.x, player1.y);
					playturn = play2;
				}
				break;
				case play2:
				{
					control5x5(player2, Arr);
					player2.num++;
					Textcolor(Default);
					gotoXY(113, 20); cout << "MOVE	: " << player2.num;
					gotoXY(player2.x, player2.y);
					playturn = play1;
				}
				break;
				}
				if (check5x5(player1.icon, Arr))
				{
					saveInfor(player1, "WIN");
					saveInfor(player2, "LOSE");
					hidePointer();
					Sleep(800);
					WinMusic();
					while (!_kbhit())
					{
						clrscr();
						Textcolor(rand() % 15 + 1);
						Result();
						Winner();
						Sleep(400);
					}
					Textcolor(Default);
					break;
				}
				else if (check5x5(player2.icon, Arr))
				{
					saveInfor(player2, "WIN");
					saveInfor(player1, "LOSE");
					hidePointer();
					Sleep(800);
					WinMusic();
					while (!_kbhit())
					{
						clrscr();
						Textcolor(rand() % 15 + 1);
						Result();
						Winner();
						Sleep(400);
					}
					Textcolor(Default);
					break;
				}
				else if (draw(5))
				{
					saveInfor(player1, "DRAW");
					saveInfor(player2, "DRAW");
					hidePointer();
					Sleep(800);
					DrawMusic();
					while (!_kbhit())
					{
						clrscr();
						Result();
						Draw();
						Sleep(400);
					}
					break;
				}
			}
		}
		break;
		case 7:
		{
			resetArr(Arr);
			Board7x7();
			gotoXY(27, 3);
			unhidePointer();
			playturn = play1;
			while (1)
			{
				switch (playturn)
				{
				case play1:
				{
					control7x7(player1,Arr);
					player1.num++;
					Textcolor(Default);
					gotoXY(113, 8); cout << "MOVE	: " << player1.num;
					gotoXY(player1.x, player1.y);
					playturn = play2;
				}
				break;
				case play2:
				{
					control7x7(player2,Arr);
					player2.num++;
					Textcolor(Default);
					gotoXY(113, 20); cout << "MOVE	: " << player2.num;
					gotoXY(player2.x, player2.y);
					playturn = play1;
				}
				break;
				}
				if (check7x7(player1.icon, Arr))
				{
					saveInfor(player1, "WIN");
					saveInfor(player2, "LOSE");
					hidePointer();
					Sleep(800);
					WinMusic();
					while (!_kbhit())
					{
						clrscr();
						Textcolor(rand() % 15 + 1);
						Result();
						Winner();
						Sleep(400);
					}
					Textcolor(Default);
					break;
				}
				else if (check7x7(player2.icon, Arr))
				{
					saveInfor(player2, "WIN");
					saveInfor(player1, "LOSE");
					hidePointer();
					Sleep(800);
					WinMusic();
					while (!_kbhit())
					{
						clrscr();
						Textcolor(rand() % 15 + 1);
						Result();
						Winner();
						Sleep(400);
					}
					Textcolor(Default);
					break;
				}
				else if (draw(7))
				{
					hidePointer();
					Sleep(800);
					DrawMusic();
					while (!_kbhit())
					{
						saveInfor(player1, "DRAW");
						saveInfor(player2, "DRAW");
						clrscr();
						Result();
						Draw();
						Sleep(400);
					}
					break;
				}
			}
		}
		break;
	}

}
void PlayPC_easy()

{
	player1.num = 0;
	player2.num = 0;
	information();
	srand(time(NULL));
	clrscr();
	gotoXY((consoleWidth - 40) / 2, (consoleHeight - 5) / 2);
	cout << "ENTER NAME OF PLAYER 1 (NO SPACE): ";
	cin>>player1.name;
	player2.name = "CPU";
	clrscr();
	StandardBoard();
	switch (boardsize)
	{
	case 3:
	{
		resetArr(Arr);
		Board3x3();
		gotoXY(35, 9);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control3x3(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				randomPC(player2, 3, 9, 35, 4, 10);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check3x3(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check3x3(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(3))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	case 5:
	{
		resetArr(Arr);
		Board5x5();
		gotoXY(33, 6);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control5x5(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				randomPC(player2, 5, 6, 33, 3, 6);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check5x5(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check5x5(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(5))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	case 7:
	{
		resetArr(Arr);
		Board7x7();
		gotoXY(27, 3);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control7x7(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				randomPC(player2, 7, 3, 27, 3, 6);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check7x7(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check7x7(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(7))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	}

}
void PlayPC_medium()
{
	player1.num = 0;
	player2.num = 0;
	information();
	srand(time(NULL));

	clrscr();
	gotoXY((consoleWidth - 40) / 2, (consoleHeight - 5) / 2);
	cout << "ENTER NAME OF PLAYER 1 (NO SPACE): ";
	cin>> player1.name;
	player2.name = "CPU";
	clrscr();
	StandardBoard();
	switch (boardsize)
	{
	case 3:
	{
		resetArr(Arr);

		Board3x3();
		gotoXY(35, 9);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control3x3(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				Medium3x3();
				gotoXY(player2.x, player2.y);
				Textcolor(DarkCyan);
				cout << player2.icon;
				Textcolor(Default);
				Arr[(player2.y - 9) / 4][(player2.x - 35) / 10] = player2.icon;
				gotoXY(player2.x, player2.y);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check3x3(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check3x3(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(3))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	case 5:
	{
		resetArr(Arr);
		Board5x5();
		gotoXY(33, 6);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control5x5(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				Medium5x5();
				gotoXY(player2.x, player2.y);
				Textcolor(DarkCyan);
				cout << player2.icon;
				Textcolor(Default);
				Arr[(player2.y - 6) / 3][(player2.x - 33) / 6] = player2.icon;
				gotoXY(player2.x, player2.y);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check5x5(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check5x5(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(5))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	case 7:
	{
		resetArr(Arr);
		Board7x7();
		gotoXY(27, 3);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control7x7(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				Medium7x7();
				gotoXY(player2.x, player2.y);
				Textcolor(DarkCyan);
				cout << player2.icon;
				Textcolor(Default);
				Arr[(player2.y - 3) / 3][(player2.x - 27) / 6] = player2.icon;
				gotoXY(player2.x, player2.y);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check7x7(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check7x7(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(7))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	}
}
void PlayPC_hard()
{
	player1.num = 0;
	player2.num = 0;
	clrscr();
	information();
	gotoXY((consoleWidth - 40) / 2, (consoleHeight - 5) / 2);
	cout << "ENTER NAME OF PLAYER 1 (NO SPACE): ";
	cin>> player1.name;
	player2.name = "CPU";
	clrscr();
	StandardBoard();
	switch (boardsize)
	{
	case 3:
	{
		resetArr(Arr);
		Board3x3();
		gotoXY(35, 9);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control3x3(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				minimax3x3(true);
				gotoXY(player2.x, player2.y);
				Textcolor(DarkCyan);
				cout << player2.icon;
				Textcolor(Default);
				Arr[(player2.y - 9) / 4][(player2.x - 35) / 10] = player2.icon;
				gotoXY(player2.x, player2.y);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check3x3(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check3x3(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(3))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	case 5:
	{
		resetArr(Arr);
		Board5x5();
		gotoXY(33, 6);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			
			switch (playturn)
			{
			case play1:
			{
				control5x5(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				Hard5x5();
				gotoXY(player2.x, player2.y);
				Textcolor(DarkCyan);
				cout << player2.icon;
				Textcolor(Default);
				Arr[(player2.y - 6) / 3][(player2.x - 33) / 6] = player2.icon;
				gotoXY(player2.x, player2.y);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check5x5(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check5x5(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(5))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	case 7:
	{
		resetArr(Arr);
		Board7x7();
		gotoXY(27, 3);
		unhidePointer();
		playturn = play2;
		while (1)
		{
			switch (playturn)
			{
			case play1:
			{
				control7x7(player1, Arr);
				player1.num++;
				Textcolor(Default);
				gotoXY(113, 8); cout << "MOVE	: " << player1.num;
				gotoXY(player1.x, player1.y);
				playturn = play2;
			}
			break;
			case play2:
			{
				Hard7x7();
				gotoXY(player2.x, player2.y);
				Textcolor(DarkCyan);
				cout << player2.icon;
				Textcolor(Default);
				Arr[(player2.y - 3) / 3][(player2.x - 27) / 6] = player2.icon;
				gotoXY(player2.x, player2.y);
				player2.num++;
				Textcolor(Default);
				gotoXY(113, 20); cout << "MOVE	: " << player2.num;
				gotoXY(player2.x, player2.y);
				playturn = play1;
			}
			break;
			}
			if (check7x7(player1.icon, Arr))
			{
				saveInfor(player1, "WIN");
				hidePointer();
				Sleep(800);
				WinMusic();
				while (!_kbhit())
				{
					clrscr();
					Textcolor(rand() % 15 + 1);
					Result();
					Winner();
					Sleep(400);
				}
				Textcolor(Default);
				break;
			}
			else if (check7x7(player2.icon, Arr))
			{
				saveInfor(player1, "LOSE");
				hidePointer();
				Sleep(800);
				LoseMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Loser();
					Sleep(400);
				}
				break;
			}
			else if (draw(7))
			{
				saveInfor(player1, "DRAW");
				hidePointer();
				Sleep(800);
				DrawMusic();
				while (!_kbhit())
				{
					clrscr();
					Result();
					Draw();
					Sleep(400);
				}
				break;
			}
		}
	}
	break;
	}
}

//Main Funtion
void Level()
{
	//Clear
	Empty(50, 18);
	//
	Textcolor(Default);
	gotoXY(141 / 2, 18); cout << "LEVEL";
	Textcolor(DarkCyan);
	gotoXY(141 / 2, 20); cout << "EASY";
	Textcolor(Default);
	gotoXY(141 / 2, 22); cout << "MEDIUM";
	gotoXY(141 / 2, 24); cout << "HARD";
	gotoXY(141 / 2, 18);
	level = 'e';
	while ((key = _getch()) != ESC && (key != ENTER))
	{
		
		control(pointer, key);
		if (pointer.y > 21)
		{
			gotoXY(60, 22);
			pointer.y = wherey();
		}
		else if (pointer.y < 20)

		{
			gotoXY(60, 20);
			pointer.y = wherey();
		}
		chooseLevel(pointer);
	}
	Enter();
}
void Mode()
{
	//clear
	Textcolor(Default);
	Empty(50, 18);
	Empty(50, 20);
	//
	gotoXY((consoleWidth-9)/2, 18);
	cout << "PLAY MODE";
	Textcolor(DarkCyan);
	gotoXY((consoleWidth - 16) / 2, 20);
	cout << "PLAY IN P-P MODE";
	Textcolor(Default);
	gotoXY((consoleWidth - 16) / 2, 22);
	cout << "PLAY IN P-C MODE" << endl;
	gotoXY(70, 30);
	cout << "PRESS ESC TO GO BACK TO MENU ";
	gotoXY((consoleWidth - 16) / 2, 20);
	key = 0;
	mode = 'p';
	while (key != ENTER && key != ESC)
	{
		key = _getch();
		control(pointer, key);
		if (pointer.y > 21)
		{
			gotoXY(60, 21);
			pointer.y = wherey();
		}
		else if (pointer.y < 20)
		{
			gotoXY(60, 20);
			pointer.y = wherey();
		}
		chooseMode(pointer);
		Tap();
	}
	
}
void Setting()
{
	Empty(50, 18);
	Empty(50, 22);
	Textcolor(DarkCyan);
	gotoXY(67, 18);
	cout << "SETTING";
	gotoXY(60, 20);
	cout << "CHOOSE PLAYER ICON (X/O) : " << player1.icon << endl;
	Textcolor(Default);
	gotoXY(60, 22);
	cout << "MUSIC (ON/OFF): "<<Music<< endl;
	gotoXY(60, 24);
	cout << "SIZE OF THE GAMEBOARD (3x3/5x5/7x7): "<<boardsize<<"x"<<boardsize<< endl;
	gotoXY(70, 30);
	cout << "PRESS ESC TO BACK TO MENU";
	gotoXY(60, 20);
	while (1)
	{
		key = _getch();
		Tap();
		control(pointer, key);
		if (pointer.y > 22)
		{
			gotoXY(60, 22);
			pointer.y = wherey();
		}
		else if (pointer.y < 20)
		{
			gotoXY(60, 20);
			pointer.y = wherey();
		}
		chooseSetting(pointer, player1, player2, Music);
		if (key == ESC)
		{
			break;
		}
	}
}
void About()
{
	Empty(50, 18);
	Empty(50, 22);
	Textcolor(DarkCyan);
	gotoXY(68, 18);
	cout << "ABOUT";
	Textcolor(Default);
	gotoXY(60, 20);
	cout << "CARO GAME PROJECT" << endl;
	gotoXY(60, 22);
	cout << "SID  : 20125110" << endl;
	gotoXY(60, 24);
	cout << "NAME : LE PHAM NHAT QUYNH" << endl;
	gotoXY(60, 26);
	cout << "CLASS: 20CTT2" << endl;
	gotoXY(70, 30);
	cout << "PRESS ESC TO BACK MENU";
	while (1)
		if (_getch() == ESC)
			break;
		
}
void Statistic()
{
	clrscr();
	Textcolor(DarkCyan);
	gotoXY(30, 5);
	int k=7;
	cout <<"NAME               MODE          LEVEL          BOARD SIZE          RESULT          MOVE";
	Textcolor(Default);
	ifstream input;
	input.open("Statistic.txt");
		while (!input.eof()&&input.is_open())
		{
			getline(input,pointer.name,' ');
			getline(input,pointer.modeplay,' ');
			getline(input,pointer.levelplay,' ');
			getline(input,pointer.sizeplay,' ');
			getline(input, pointer.result,' ');
			input >> pointer.num;
			char chr=input.get();//eat the carriage
			if (chr != '\n')
				break;
			gotoXY(15, k);
			cout << setw(20) << setfill(' ') << pointer.name << setw(18) << setfill(' ') << pointer.modeplay << setw(14) << setfill(' ') << pointer.levelplay << setw(18) << setfill(' ') << pointer.sizeplay << setw(18) << setfill(' ') << pointer.result << setw(15) << setfill(' ') << pointer.num;
			k = k + 2;
		}
		input.close();
	gotoXY(3, 10);
	cout << "ESC: BACK TO MENU ";
	gotoXY(3, 12);
	cout << "X: DELETE ALL DATA";
	while (1)
	{
		char key;
		if ((key =_getch()) == ESC)
			break;
		if (key == 120 || key == 88)
		{
			system("del Statistic.txt");
			Statistic();
		}
	}

}

void Menu()
{
	fixConsoleWindow();
	setConsoleWindow(1100, 620);
	WordCaro3();
	Textcolor(DarkGreen);
	Empty(50, 18);
	Empty(50, 22);
	gotoXY(10, 25); cout << "ARROW KEYS: MOVE";
	gotoXY(10, 27); cout << "ENTER: CHOOSE";
	gotoXY((141 - 8) / 2, 20); cout << "START GAME";
	Textcolor(Default);
	gotoXY((141 - 8) / 2, 22); cout << "SETTING";
	gotoXY((141 - 8) / 2, 24); cout << "STATISTIC";
	gotoXY((141 - 8) / 2, 26); cout << "ABOUT";
	gotoXY((141 - 8) / 2, 28); cout << "EXIT";
	gotoXY((141 - 8) / 2, 20);
	pointer.y = wherey();
	key = 0;
	//Menu
	while (key != ENTER)
	{
		key = _getch();
		Tap();
		control(pointer, key);
		if (pointer.y > 24)
		{
			gotoXY((141 - 8) / 2, 24);
			pointer.y = wherey();
		}
		else if (pointer.y < 20)
		{
			gotoXY((141 - 8) / 2, 20);
			pointer.y = wherey();
		}
		chooseMenu(pointer);
	}
	Enter();
	// Choose
	switch (pointer.y)
	{
	case 20:
	{
		Mode();
		if (key == ENTER)
		{
			if (mode == 'p')
			{
				Enter();
				PlayPP();
				key = 0;
			}
			else if (mode == 'c')
			{
				Enter();
				Level();
			}
		}
		else if (key == ESC)
			Menu();
		if (key == ENTER)
		{
			Enter();
			switch (level)
			{
			case 'e':
				PlayPC_easy();
				break;
			case 'm':
				PlayPC_medium();
				break;
			case 'h':
				PlayPC_hard();
				break;
			default:
				break;
			}
		}
		clrscr();
		_getch();
		Tap();
		Menu();
	}
	break;
	case 21:
	{
		Setting();
		Menu();
	}
	break;
	case 22:
	{
		Statistic();
		clrscr();
		Menu();
	}
	break;
	case 23:
	{
		About();
		Menu();
	}
	break;
	case 24:
	{
		exit(0);
	}
	break;
	default:
		break;
	}
}

void StartGameScreen()
{
	
	player1.icon = 'X';
	player2.icon = 'O';
	// Play the background music
	BackGround();
	while (1)
	{
		WordCaro1();
		gotoXY((141-25)/2,25);
		Textcolor(Default);
		Sleep(200);
		cout << "PRESS ANY KEY TO CONTINUE";
		if (_kbhit())
		{
			_getch();
			Enter();
			break;
		}
	}
	WordCaro2();
}

//Main
int main()
{
	player1.icon = 'X';
	fixConsoleWindow();
	setConsoleWindow(1100, 620);
	StartGameScreen();
	Menu();
    return 0;
}
