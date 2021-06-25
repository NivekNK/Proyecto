#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include "mUsers.h"
#include "Map.h"
#include "list.h"

#define NOREGISTER 4 // 7
#define SOCIAL 4 // 9
#define ADMIN 4 // 15

// 0 = black 8 = gray
// 1 = blue 9 = light blue
// 2 = green 10 = light green
// 3 = light green 11 = light green
// 4 = red 12 = light red
// 5 = purple 13 = light purple
// 6 = yellow 14 = light yellow
// 7 = white 15 = bright white

void colorPrint(const char* s, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf("%s\n", s);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

char* getOptions(int option, User* user)
{
    switch (option)
    {
        case 0:
            return "Iniciar Sesion";
        case 1:
            return "Registrar";
        case 2:
            return "Option 3";
        case 3:
            return "Salir";
    }
}

void useOptions(int* option, User* user, Map* users)
{
    char* rut = (char*)malloc(sizeof(char) * 20);

    switch (*option)
    {
        case 0:
            copyUser(user, logIn(users));
            break;
        case 1:
            registerUser(users);
            break;
        case 2:
            //User* aux = searchMap(users, getRut(user));
            printUser(user);
            break;
        case 3:
            *option = -1;
            break;
    }
}

void getCurrentOption(int* currentOption, int options, User* user, Map* users)
{
    switch(getch())
    {
        case 72:
            // code for arrow up
            if (*currentOption != 0)
                *currentOption = *currentOption - 1;
            break;
        case 80:
            // code for arrow down
            if (*currentOption + 1 < options)
                *currentOption = *currentOption + 1;
            break;
        case '\r':
            // go to selected option
            useOptions(currentOption, user, users);
            break;
        default:
            break;
    }
}

int main()
{
    Map* users = createMap(is_equal_string);
    setSortFunction(users, lower_than_string);

    User* currentUser;
    int currentOption = 0;
    int oldCurrent = -1;

    int options = 0;

    do
    {
        if (currentUser == NULL)
        {
            options = NOREGISTER;
        }
        else
        {
            if (isAdmin(currentUser))
                options = ADMIN;
            else
                options = SOCIAL;
        }

        if (oldCurrent != currentOption)
        {
            system("cls");
            // printf("Current: %i\n", currentOption);
            // printf("Total: %i\n", options);
            for (int i = 0; i < options; i++)
            {
                if (i == currentOption)
                {
                    colorPrint(getOptions(i, currentUser), 4);
                }
                else
                {
                    printf("%s\n", getOptions(i, currentUser));
                }
            }
        }

        oldCurrent = currentOption;
        getCurrentOption(&currentOption, options, currentUser, users);

    } while (currentOption > -1);
    

    return 0;
}