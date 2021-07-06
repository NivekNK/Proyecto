#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include "manageFiles.h"
#include "mUsers.h"
#include "items.h"
#include "Map.h"
#include "list.h"

#define NOREGISTER 7
#define SOCIAL 8
#define ADMIN 16

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

char* getOptions(int option, int options)
{
    if (options == 7)
    {
        switch (option)
        {
            case 0:
                return "Iniciar Sesion";
            case 1:
                return "Buscar items por marca";
            case 2:
                return "Tipo de items por precio";
            case 3:
                return "Buscar item por ID";
            case 4:
                return "Items por precio";
            case 5:
                return "Items alfabeticamente";
            case 6:
                return "Salir";
        }
    }
    else if (options == 8)
    {
        switch (option)
        {
            case 0:
                return "Club de Socios";
            case 1:
                return "Buscar items por marca";
            case 2:
                return "Tipo de items por precio";
            case 3:
                return "Buscar item por ID";
            case 4:
                return "Items por precio";
            case 5:
                return "Items alfabeticamente";
            case 6:
                return "Cerrar Sesion";
            case 7:
                return "Salir";
        }
    }
    else
    {
        switch (option)
        {
            case 0:
                return "Importar archivos";
            case 1:
                return "Registrar Usuario";
            case 2:
                return "Crear Item";
            case 3:
                return "Agregar Item";
            case 4:
                return "Eliminar Item";
            case 5:
                return "Estado de categorias";
            case 6:
                return "Agregar descuento a Usuario";
            case 7:
                return "Eliminar descuentos de Usuario";
            case 8:
                return "Club de Socios";
            case 9:
                return "Buscar items por marca";
            case 10:
                return "Tipo de items por precio";
            case 11:
                return "Buscar item por ID";
            case 12:
                return "Items por precio";
            case 13:
                return "Items alfabeticamente";
            case 14:
                return "Cerrar Sesion";
            case 15:
                return "Salir";
        }
    }
}

void useOptions(int* option, int options, User* currentUser, Map* users, Map* category, 
    Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, bool* imported)
{
    if (options == 7)
    {
        switch (*option)
        {
            case 0:
                copyUser(currentUser, logIn(users));
                break;
            case 1:
                brandSearch(itemPerBrand, currentUser);
                break;
            case 2:
                typeSearch(category, currentUser);
                break;
            case 3:
                itemSearch(itemPerId, currentUser);
                break;
            case 4:
                ascendingPrice(itemPerPrice, currentUser);
                break;
            case 5:
                alphabeticPrint(itemPerName, currentUser);
                break;
            case 6:
                *option = -1;
                break;
        }
    }
    else if (options == 8)
    {
        switch (*option)
        {
            case 0:
                socialClub(currentUser, users, itemPerId);
                break;
            case 1:
                brandSearch(itemPerBrand, currentUser);
                break;
            case 2:
                typeSearch(category, currentUser);
                break;
            case 3:
                itemSearch(itemPerId, currentUser);
                break;
            case 4:
                ascendingPrice(itemPerPrice, currentUser);
                break;
            case 5:
                alphabeticPrint(itemPerName, currentUser);
                break;
            case 6:
                *option = 0;
                logOut(currentUser);
                break;
            case 7:
                *option = -1;
                break;
        }
    }
    else
    {
        switch (*option)
        {
            case 0:
                if (*imported == false)
                {
                    importFromCSV(itemPerId, itemPerBrand, itemPerPrice, itemPerName, category, users);
                    *imported = true;
                }
                else
                {
                    printf("Archivos ya importados!\n");
                }
                break;
            case 1:
                registerUser(users);
                break;
            case 2:
                createItem(itemPerId, itemPerBrand, itemPerPrice, itemPerName, category);
                break;
            case 3:
                addItem(itemPerId, category);
                break;
            case 4:
                removeItemFromId(itemPerId, category);
                break;
            case 5:
                categoryStatus(category);
                break;
            case 6:
                addDiscount(users);
                break;
            case 7:
                cleanDiscounts(users);
                break;
            case 8:
                socialClub(currentUser, users, itemPerId);
                break;
            case 9:
                brandSearch(itemPerBrand, currentUser);
                break;
            case 10:
                typeSearch(category, currentUser);
                break;
            case 11:
                itemSearch(itemPerId, currentUser);
                break;
            case 12:
                ascendingPrice(itemPerPrice, currentUser);
                break;
            case 13:
                alphabeticPrint(itemPerName, currentUser);
                break;
            case 14:
                *option = 0;
                logOut(currentUser);
                break;
            case 15:
                *option = -1;
                break;
        }
    }
}

void getCurrentOption(int* currentOption, int options, User* currentUser, Map* users, Map* category, 
    Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, bool* imported)
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
            // go to selected option with enter
            useOptions(currentOption, options, currentUser, users, category, itemPerId, itemPerBrand, itemPerPrice, itemPerName, imported);
            break;
        default:
            break;
    }
}

int main()
{
    Map* users = createMap(is_equal_string);
    setSortFunction(users, lower_than_string);

    Map* itemPerId = createMap(is_equal_int);
    setSortFunction(itemPerId, lower_than_int);

    Map* itemPerBrand = createMap(is_equal_string);

    Map* itemPerPrice = createMap(is_equal_int);
    setSortFunction(itemPerPrice, lower_than_int);

    Map* itemPerName = createMap(is_equal_string);
    setSortFunction(itemPerName, lower_than_string);

    Map* category = createMap(is_equal_string);

    User* currentUser = createEmptyUser();
    setRut(currentUser, "");

    int currentOption = 0;
    int oldCurrent = -1;

    int options = 0;
    int oldOptions = 0;

    bool imported = false;
    importUsers(users);

    do
    {
        if (strlen(getRut(currentUser)) == 0)
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

        if (oldCurrent != currentOption || oldOptions != options)
        {
            system("cls");
            
            if (strlen(getRut(currentUser)) == 0) colorPrint("No Registrado", 6);
            else if (isAdmin(currentUser)) colorPrint("Administrador", 5);
            else colorPrint("Socio", 3);
            printf("\n");

            for (int i = 0; i < options; i++)
            {
                if (i == currentOption)
                {
                    colorPrint(getOptions(i, options), 4);
                }
                else
                {
                    printf("%s\n", getOptions(i, options));
                }
            }
        }

        oldOptions = options;
        oldCurrent = currentOption;
        getCurrentOption(&currentOption, options, currentUser, users, category, itemPerId, itemPerBrand, itemPerPrice, itemPerName, &imported);

    } while (currentOption > -1);
    
    exportUsers(users);
    if (imported) exitApp(itemPerId, users, category);

    return 0;
}