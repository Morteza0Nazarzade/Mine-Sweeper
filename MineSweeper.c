#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#pragma warning (disable:4996)
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

char input[101]; //input

int break_loop = 0; //it defines that the loop in the game, should or should not be broken

void info(); //shows player's info and can also start a game

void registery(); //sign in, sign up, changing name

void command(char input[4], int* flag);

int compare(char first[100], char second[100]) //compares two strings , return 1 if they are the same
{
	int check = 1;

	if (strlen(first) == strlen(second))
	{
		for (int i = 0; i < strlen(first); i++)
		{
			if (first[i] != second[i])
			{
				check = 0;
				break;
			}
		}
		return check;
	}
	else
		return 0;
}

struct player //player's name and info
{
	char name[101];
	int games_played;
	int winnigs;
	int losses;
};

struct block //status of each block of the chart
{
	wchar_t output;
	int num_bomb;
	int index_x;
	int index_y;
	int is_bomb;
	int color;
};

//variables
int i = -1; // current slot of memory
int memory_hold = -1; //max memory
int result = 0; //is there a repeatetive name?
typedef struct player player;
player* list; //a pointer for deefining a list
typedef block block;
block tile[8][8]; //defining the blocks of the game

void loading() //first loading screen
{
	system("color 0f");
	printf("loading");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	system("cls||clear");
	printf("loading");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".\n");
	Sleep(1000);
	printf("\033[1;32mHello\033[0m\n");
	Sleep(1000);
	printf("\033[1;32mWelcome to\033[0m\n");
	Sleep(1000);
}

void display(int* flag) //display of the table during the game
{
	system("cls||clear");
	wprintf(L"\n╔═══════════════════════════╗\n");
	if (*flag == 10)
		wprintf(L"║    flags remaining: %d    ║\n", *flag);
	else
		wprintf(L"║    flags remaining: %d     ║\n", *flag);

	wprintf(L"╚═══════════════════════════╝\n\n");
	wprintf(L"\t\t\033[1;32m╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\033[0m\n");
	wprintf(L"\t\t\033[1;32m║ 0 ║ 1 ║ 2 ║ 3 ║ 4 ║ 5 ║ 6 ║ 7 ║ 8 ║\033[0m\n");
	wprintf(L"\t\t\033[1;32m╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\033[0m\n");
	wprintf(L"\t\t\033[1;32m║ 1 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[0][0].color, tile[0][0].output, tile[0][1].color, tile[0][1].output, tile[0][2].color, tile[0][2].output, tile[0][3].color, tile[0][3].output, tile[0][4].color, tile[0][4].output, tile[0][5].color, tile[0][5].output, tile[0][6].color, tile[0][6].output, tile[0][7].color, tile[0][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 2 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[1][0].color, tile[1][0].output, tile[1][1].color, tile[1][1].output, tile[1][2].color, tile[1][2].output, tile[1][3].color, tile[1][3].output, tile[1][4].color, tile[1][4].output, tile[1][5].color, tile[1][5].output, tile[1][6].color, tile[1][6].output, tile[1][7].color, tile[1][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 3 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[2][0].color, tile[2][0].output, tile[2][1].color, tile[2][1].output, tile[2][2].color, tile[2][2].output, tile[2][3].color, tile[2][3].output, tile[2][4].color, tile[2][4].output, tile[2][5].color, tile[2][5].output, tile[2][6].color, tile[2][6].output, tile[2][7].color, tile[2][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 4 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[3][0].color, tile[3][0].output, tile[3][1].color, tile[3][1].output, tile[3][2].color, tile[3][2].output, tile[3][3].color, tile[3][3].output, tile[3][4].color, tile[3][4].output, tile[3][5].color, tile[3][5].output, tile[3][6].color, tile[3][6].output, tile[3][7].color, tile[3][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 5 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[4][0].color, tile[4][0].output, tile[4][1].color, tile[4][1].output, tile[4][2].color, tile[4][2].output, tile[4][3].color, tile[4][3].output, tile[4][4].color, tile[4][4].output, tile[4][5].color, tile[4][5].output, tile[4][6].color, tile[4][6].output, tile[4][7].color, tile[4][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 6 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[5][0].color, tile[5][0].output, tile[5][1].color, tile[5][1].output, tile[5][2].color, tile[5][2].output, tile[5][3].color, tile[5][3].output, tile[5][4].color, tile[5][4].output, tile[5][5].color, tile[5][5].output, tile[5][6].color, tile[5][6].output, tile[5][7].color, tile[5][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 7 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[6][0].color, tile[6][0].output, tile[6][1].color, tile[6][1].output, tile[6][2].color, tile[6][2].output, tile[6][3].color, tile[6][3].output, tile[6][4].color, tile[6][4].output, tile[6][5].color, tile[6][5].output, tile[6][6].color, tile[6][6].output, tile[6][7].color, tile[6][7].output);
	wprintf(L"\t\t\033[1;32m╠═══╬\033[0m═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t\033[1;32m║ 8 ║\033[0m \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║ \033[1;%dm%lc\033[0m ║\n", tile[7][0].color, tile[7][0].output, tile[7][1].color, tile[7][1].output, tile[7][2].color, tile[7][2].output, tile[7][3].color, tile[7][3].output, tile[7][4].color, tile[7][4].output, tile[7][5].color, tile[7][5].output, tile[7][6].color, tile[7][6].output, tile[7][7].color, tile[7][7].output);
	wprintf(L"\t\t\033[1;32m╚═══╩\033[0m═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n\n");
}

void last_display(int* flag) //last display of the table
{
	system("cls||clear");
	wprintf(L"\n╔═══════════════════════════╗\n");
	if (*flag == 10)
		wprintf(L"║    flags remaining: %d    ║\n", *flag);
	else
		wprintf(L"║    flags remaining: %d     ║\n", *flag);
	wprintf(L"╚═══════════════════════════╝\n\n");
	wprintf(L"\t\t╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n");
	wprintf(L"\t\t║ 0 ║ 1 ║ 2 ║ 3 ║ 4 ║ 5 ║ 6 ║ 7 ║ 8 ║\n");
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 1 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[0][0].output, tile[0][1].output, tile[0][2].output, tile[0][3].output, tile[0][4].output, tile[0][5].output, tile[0][6].output, tile[0][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 2 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[1][0].output, tile[1][1].output, tile[1][2].output, tile[1][3].output, tile[1][4].output, tile[1][5].output, tile[1][6].output, tile[1][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 3 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[2][0].output, tile[2][1].output, tile[2][2].output, tile[2][3].output, tile[2][4].output, tile[2][5].output, tile[2][6].output, tile[2][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 4 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[3][0].output, tile[3][1].output, tile[3][2].output, tile[3][3].output, tile[3][4].output, tile[3][5].output, tile[3][6].output, tile[3][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 5 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[4][0].output, tile[4][1].output, tile[4][2].output, tile[4][3].output, tile[4][4].output, tile[4][5].output, tile[4][6].output, tile[4][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 6 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[5][0].output, tile[5][1].output, tile[5][2].output, tile[5][3].output, tile[5][4].output, tile[5][5].output, tile[5][6].output, tile[5][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 7 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[6][0].output, tile[6][1].output, tile[6][2].output, tile[6][3].output, tile[6][4].output, tile[6][5].output, tile[6][6].output, tile[6][7].output);
	wprintf(L"\t\t╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
	wprintf(L"\t\t║ 8 ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║ %lc ║\n", tile[7][0].output, tile[7][1].output, tile[7][2].output, tile[7][3].output, tile[7][4].output, tile[7][5].output, tile[7][6].output, tile[7][7].output);
	wprintf(L"\t\t╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n\n");
}

void title_screen()  //title screen
{
	_setmode(_fileno(stdout), 0x20000); //setting in unicode mode
	system("cls||clear");
	system("color F0");

	wprintf(L"████	████    ██████  ████	██    ████████\n");
	Sleep(250);
	wprintf(L"██ ██  ██ ██      ██    ██ ██   ██    ███     \n");
	Sleep(250);
	wprintf(L"██  ████  ██      ██    ██  ██  ██    ████████\n");
	Sleep(250);
	wprintf(L"██   ██	  ██      ██    ██   ██ ██    ███    \n");
	Sleep(250);
	wprintf(L"██   ██   ██    ██████  ██    ████    ████████\n");
	wprintf(L"\n");
	Sleep(250);
	wprintf(L"████████    ██    ██    ██    ████████    ████████    ████████    ████████    ████████\n");
	Sleep(250);
	wprintf(L"██          ██    ██    ██    ███         ███         ██    ██    ███         ██    ██\n");
	Sleep(250);
	wprintf(L"████████     ██  ████  ██     ████████    ████████    ████████    ████████    ████████\n");
	Sleep(250);
	wprintf(L"      ██      ████  ████      ███         ███         ██          ███         ██  ███ \n");
	Sleep(250);
	wprintf(L"████████       ██    ██       ████████    ████████    ██          ████████    ██   ███\n");
	Sleep(500);
	system("color 4f");
	Sleep(500);
	system("color F0");
	Sleep(500);
	system("color 2f");
	Sleep(500);
	system("color F0");
	Sleep(1750);
	system("cls||clear");
	_setmode(_fileno(stdout), 0x4000);
	registery();
}

void registery() //here player can sign up, change name or sign in
{
	result = 0;
	Sleep(500);
	system("color 1f");
	wprintf(L"If you have already signed up, enter your name \nif you want to change your previous name enter 1\nif your new, enter 0:\n\n");

	while (result == 0)
	{
		gets_s(input); //getting input from user

		switch (*input)
		{
		case '0': //sign up
			if (strlen(input) == 1) //checks if user is not trying anything funny :)
			{
				system("cls||clear");
				printf("SIGN UP\n\npick a name(up to 100 charcaters and the first character cannot be numeric):\n");
				gets_s(input);
				result = 0;
				for (int j = -1; j <= memory_hold; j++) //checks if the name is already taken
				{
					if (j == -1)
						continue;
					else if (compare((list + j)->name, input))
					{
						i = j;
						result = 1;
						break;
					}
				}
				memory_hold++;
				i++;
				strcpy((list + memory_hold)->name, input);

				if ((int)(list + memory_hold)->name[0] < 48 || (int)(list + memory_hold)->name[0] > 57 && result == 0) //name should not start with a numeric character to be confused with commands
				{
					(list + memory_hold)->games_played = 0;
					(list + memory_hold)->winnigs = 0;
					(list + memory_hold)->losses = 0;
					system("cls||clear");
					printf("sign up was SUCCESSFUL!\n\n");
					Sleep(1000);
					printf("Welcome %s", (list + i)->name);
					Sleep(1000);
					system("cls||clear");
					registery();
				}
				else //if there was a user with the same name...
				{
					if (result == 1)
						printf("This name is already taken!");
					else
						printf("INVALID NAME");
					Sleep(1500);
					system("cls||clear");
					registery();
				}

			}
			else // but if he does lie...
			{
				--memory_hold;
				--i;
				printf("INVALID NAME");
				Sleep(1500);
				system("cls||clear");
				registery();
			}
			break;
		case '1': // changing name
			if (strlen(input) == 1)
			{
				system("cls||clear");
				printf("CHANGE NAME\n\n");
				printf("Enter your previous name:");
				gets_s(input);
				result = 0;
				for (int j = -1; j <= memory_hold; j++) //checks if there is a user with this name
				{
					if (j == -1)
						continue;
					else if (compare((list + j)->name, input))
					{
						i = j;
						result = 1;
						break;
					}
				}

				switch (result)
				{
				case 0: //if the user was lying
					printf("name NOT FOUND!");
					Sleep(1000);
					system("cls||clear");
					registery();
					break;
				case 1: //if there is a user with that name
					printf("name FOUND\nEnter your new name(up to 100 charcaters and the first character cannot be numeric):");
					gets_s(input);
					result = 0;
					for (int j = -1; j <= memory_hold; j++) //checks if the name is already taken
					{
						if (j == -1)
							continue;
						else if (compare((list + j)->name, input))
						{
							i = j;
							result = 1;
							break;
						}
					}
					if ((int)(list + memory_hold)->name[0] < 48 || (int)(list + memory_hold)->name[0] > 57 && result == 0)
					{
						strcpy((list + i)->name, input); //applying the change
						printf("the name is changed SUCCESSFULY\n");
						Sleep(1000);
						system("cls||clear");
						registery();
					}
					else
					{
						if (result == 1)
							printf("This name is already taken!");
						else
							printf("INVALID NAME");
						Sleep(1500);
						system("cls||clear");
						registery();
					}
				default: //just is case something wierd happens
					printf("UNKNOWN ERROR");
					Sleep(1000);
					system("cls||clear");
					registery();
					break;
				}
			}
			else //again if the user thinks they are funny :)
			{
				printf("INVALID NAME");
				Sleep(1500);
				system("cls||clear");
				registery();
			}
			break;
		default: //log in
			result = 0;

			for (int j = -1; j <= memory_hold; j++) //is there a user with this name
			{
				if (j == -1)
					continue;
				else if (compare((list + j)->name, input))
				{
					i = j;
					result = 1;
					break;
				}
			}

			switch (result)
			{
			case 0:
				printf("name NOT FOUND!\n");
				Sleep(1000);
				system("cls||clear");
				registery();
				break;
			case 1:
				printf("welcome %s", input);
				Sleep(1000);
				system("cls||clear");
				info();
				break;
			default:
				printf("UNKNOWN ERROR");
				Sleep(1000);
				system("cls||clear");
				registery();
				break;
			}
			break;
		}
	}
}

void show_bomb()//displays the bombs when the player loses
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tile[i][j].is_bomb == 1)
				tile[i][j].output = 0x01A0;
		}
	}
}

void win(int* flag)//when the player has won ...
{
	system("cls||clear");
	system("color 2f");
	last_display(flag);
	wprintf(L"YOU WIN!\n");
	(list + i)->games_played++;
	(list + i)->winnigs++;
	Sleep(1500);
	break_loop = 1;
}

int is_won(int* flag)//checks if the player has won
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tile[i][j].is_bomb == 1 && tile[i][j].output != 0x2660)
				return 0;
		}
	}

	win(flag);
}

void tile_assign8X8(int bombs)//placing the bombs and giving value to the blocks' variables
{
	_setmode(_fileno(stdout), 0x20000); //unicode mode

	break_loop = 0;

	int is_3[8] = { 0 };

	for (int i = 0; i < 8; i++) //assigning
	{
		for (int j = 0; j < 8; j++)
		{
			tile[i][j].index_x = i + 1;
			tile[i][j].index_y = j + 1;
			tile[i][j].is_bomb = 0;
			tile[i][j].output = ' ';
			tile[i][j].num_bomb = 0;
			tile[i][j].color = 37;
		}
	}


	for (int i = 0; i < 10; i++) //placing bombs
	{
		int a, b;
		srand(time(NULL));

		a = rand() % 7;
		b = rand() % 7;

		if (tile[a][b].is_bomb == 0 && is_3[b] < 3)
		{
			tile[a][b].is_bomb = 1;
			is_3[b] += 1;
		}
		else
			--i;
	}

}

void game8X8()//starts the game
{
	system("cls||clear");
	system("color 0f");
	wprintf(L"Please wait\n");

	tile_assign8X8(10);

	int flag_left = 10;

	display(&flag_left);

	while (break_loop == 0)
	{
		gets_s(input);
		command(input, &flag_left);
		is_won(&flag_left);
	}

	wprintf(L"To play again enter 0\nTo get back to INFO enter 1\nOr enter 2 to get back to title:\n\n");

	while (1)
	{
		gets_s(input);

		if (input[0] == '0')
		{
			game8X8();
			break;
		}
		else if (input[0] == '1')
		{
			info();
			break;
		}
		else if (input[0] == '2')
		{
			title_screen();
			break;
		}
	}
}

void info()//displays the user's info
{
	system("cls||clear");
	system("color 1f");
	_setmode(_fileno(stdout), 0x4000); //ASCII mode
	printf("INFO\n\nPlayer : %s\nstatus:\ngames played : %d\nwins : %d\nlosses : %d\n\n", (list + i)->name, (list + i)->games_played, (list + i)->winnigs, (list + i)->losses);
	printf("to start a game enter 1, for getting back to title enter 2:");
	gets_s(input);

	if (strlen(input) == 1)
	{
		switch (input[0])
		{
		case '1':
			system("cls||clear");
			system("color 1f");
			game8X8();
			break;
		case '2':
			title_screen();
			break;
		default:
			printf("INVALID COMMAND");
			Sleep(1500);
			system("cls||clear");
			info();
			break;
		}
	}
	else
	{
		printf("INVALID COMMAND");
		Sleep(1500);
		system("cls||clear");
		info();
	}
}

void lose(int* flag)//when the player loses...
{
	system("cls||clear");
	system("color 4f");
	show_bomb();
	last_display(flag);
	wprintf(L"YOU LOST!\n");
	(list + i)->games_played++;
	(list + i)->losses++;
	Sleep(1500);
	break_loop = 1;
}

void auto_open(int x, int y);

void quick_open(int x, int y)//calculates the bombs around the chosen tile
{
	if (tile[y][x].output == ' ') //checks if the block is already open
	{
		if (x == 0 && y == 0)
		{
			tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y][x].is_bomb;
		}
		else if (y == 0 && x == 7)
		{
			tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
		}
		else if (y == 7 && x == 0)
		{
			tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
		}
		else if (y == 7 && x == 7)
		{
			tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
		}
		else if (y == 0)
		{
			tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x + 1].is_bomb;
		}
		else if (y == 7)
		{
			tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
		}
		else if (x == 0)
		{
			tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x + 1].is_bomb;
		}
		else if (x == 7)
		{
			tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
		}
		else
		{
			tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y + 1][x + 1].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
			tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
		}

		if (tile[y][x].is_bomb == 0)
		{
			switch (tile[y][x].num_bomb)
			{
			case  0:
				tile[y][x].output = '0';
				auto_open(x, y);
				break;
			case 1:
				tile[y][x].output = '1';
				tile[y][x].color = RED;
				break;
			case 2:
				tile[y][x].output = '2';
				tile[y][x].color = BLUE;
				break;
			case 3:
				tile[y][x].output = '3';
				tile[y][x].color = GREEN;
				break;
			case 4:
				tile[y][x].output = '4';
				tile[y][x].color = YELLOW;
				break;
			case 5:
				tile[y][x].output = '5';
				tile[y][x].color = MAGENTA;
				break;
			case 6:
				tile[y][x].output = '6';
				tile[y][x].color = CYAN;
				break;
			case 7:
				tile[y][x].output = '7';
				tile[y][x].color = RED;
				break;
			case 8:
				tile[y][x].output = '8';
				tile[y][x].color = GREEN;
				break;
			}
		}
	}
}

void auto_open(int x, int y)//it automaticly opens the tiles around the 0;
{
	//frist finds the place of tile and the tiles that must be opened
	if (x == 0 && y == 0)
	{
		quick_open(x + 1, y);
		quick_open(x, y + 1);
		quick_open(x + 1, y + 1);
	}
	else if (y == 0 && x == 7)
	{
		quick_open(x - 1, y);
		quick_open(x, y + 1);
		quick_open(x - 1, y + 1);
	}
	else if (y == 7 && x == 0)
	{
		quick_open(x + 1, y);
		quick_open(x, y - 1);
		quick_open(x + 1, y - 1);
	}
	else if (y == 7 && x == 7)
	{
		quick_open(x - 1, y);
		quick_open(x, y - 1);
		quick_open(x - 1, y - 1);
	}
	else if (y == 0)
	{
		quick_open(x + 1, y);
		quick_open(x, y + 1);
		quick_open(x + 1, y + 1);
		quick_open(x - 1, y);
		quick_open(x - 1, y + 1);
	}
	else if (y == 7)
	{
		quick_open(x + 1, y);
		quick_open(x, y - 1);
		quick_open(x + 1, y - 1);
		quick_open(x - 1, y);
		quick_open(x - 1, y - 1);
	}
	else if (x == 0)
	{
		quick_open(x + 1, y);
		quick_open(x, y - 1);
		quick_open(x, y + 1);
		quick_open(x + 1, y - 1);
		quick_open(x + 1, y + 1);
	}
	else if (x == 7)
	{
		quick_open(x - 1, y);
		quick_open(x, y + 1);
		quick_open(x, y - 1);
		quick_open(x - 1, y + 1);
		quick_open(x - 1, y - 1);
	}
	else
	{
		quick_open(x + 1, y);
		quick_open(x - 1, y);
		quick_open(x, y + 1);
		quick_open(x, y - 1);
		quick_open(x - 1, y - 1);
		quick_open(x - 1, y + 1);
		quick_open(x + 1, y - 1);
		quick_open(x + 1, y + 1);
	}
}

void show(char click, int x, int y, int* flag)//this opens the tile user chooses
{
	if (click == 'R') //if right click happens
	{
		if (tile[y][x].output == 0x2660) //if is already flaged
		{
			tile[y][x].output = ' ';
			*flag += 1;
			display(flag);
		}
		else if (tile[y][x].output == ' ' && *flag > 0) //if must be flaged
		{
			tile[y][x].output = 0x2660;
			*flag -= 1;
			display(flag);
		}
		else if (*flag == 0) //if threre is no more flags left
		{
			wprintf(L"No more flags can be set");
			Sleep(1500);
			display(flag);
		}
		else //if its a opened tile
		{
			wprintf(L"This tile cannot be flaged/unflaged");
			Sleep(1500);
			display(flag);
		}
	}
	else if ((click == 'L') && tile[y][x].is_bomb == 0) //if left click happens
	{
		if (tile[y][x].output == ' ') //checks if the tile is not opened or flaged
		{
			//calculates the number of bombs around the tile
			if (x == 0 && y == 0)
			{
				tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y][x].is_bomb;
			}
			else if (y == 0 && x == 7)
			{
				tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
			}
			else if (y == 7 && x == 0)
			{
				tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
			}
			else if (y == 7 && x == 7)
			{
				tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
			}
			else if (y == 0)
			{
				tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x + 1].is_bomb;
			}
			else if (y == 7)
			{
				tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
			}
			else if (x == 0)
			{
				tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x + 1].is_bomb;
			}
			else if (x == 7)
			{
				tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
			}
			else
			{
				tile[y][x].num_bomb += tile[y][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y + 1][x + 1].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x - 1].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x].is_bomb;
				tile[y][x].num_bomb += tile[y - 1][x + 1].is_bomb;
			}
			//reassigns the output
			switch (tile[y][x].num_bomb)
			{
			case  0:
				tile[y][x].output = '0';
				auto_open(x, y);
				break;
			case 1:
				tile[y][x].output = '1';
				tile[y][x].color = RED;
				break;
			case 2:
				tile[y][x].output = '2';
				tile[y][x].color = BLUE;
				break;
			case 3:
				tile[y][x].output = '3';
				tile[y][x].color = GREEN;
				break;
			case 4:
				tile[y][x].output = '4';
				tile[y][x].color = YELLOW;
				break;
			case 5:
				tile[y][x].output = '5';
				tile[y][x].color = MAGENTA;
				break;
			case 6:
				tile[y][x].output = '6';
				tile[y][x].color = CYAN;
				break;
			case 7:
				tile[y][x].output = '7';
				tile[y][x].color = RED;
				break;
			case 8:
				tile[y][x].output = '8';
				tile[y][x].color = GREEN;
				break;
			}

			display(flag);
		}
		else if (tile[y][x].output == 0x2660) //if it is flaged
		{
			wprintf(L"Flaged tiles cannot be opened!");
			Sleep(1500);
			display(flag);
		}
		else //if it is already open
		{
			wprintf(L"This tile cannot be opened!");
			Sleep(1500);
			display(flag);
		}
	}
	else if (tile[y][x].output == ' ') //if the tile is a bomb and it is not opened yet
	{
		lose(flag);
	}
	else // if it is flaged
	{
		wprintf(L"Flaged tiles cannot be opened!");
		Sleep(1500);
		display(flag);
	}

}

void command(char input[4], int* flag)//checks if the input is valid
{
	int x, y;
	char click;
	if (strlen(input) > 4 || (int)input[0] < 49 || (int)input[0] > 57 || (int)input[1] < 49 || (int)input[1] > 57)
	{
		wprintf(L"INVALID COMMAND");
		Sleep(1500);
		display(flag);
	}
	else if (input[2] == 'R' || input[2] == 'L')
	{
		x = (int)input[1] - 49;
		y = (int)input[0] - 49;
		show(input[2], x, y, flag);
	}
	else
	{
		wprintf(L"INVALID COMMAND");
		Sleep(1500);
		display(flag);
	}
}



int main()
{
	list = (player*)malloc(50 * sizeof(player)); //alloctaes memory for the list of users

	loading();

	title_screen();
}