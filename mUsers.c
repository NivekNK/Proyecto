#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "mUsers.h"
#include "list.h"
#include "Map.h"
#include "items.h"

struct User
{
    char* name;
    char* surname;
    char* rut;
    bool admin;
    List* discounts;
};

typedef User User;

User* createEmptyUser()
{
    User* user = (User*)malloc(sizeof(User));

    user->name = (char*)malloc(sizeof(char) * 20);
    user->surname = (char*)malloc(sizeof(char) * 20);
    user->rut =(char*)malloc(sizeof(char) * 20);
    user->admin = false;
    user->discounts = createList();

    return user;
}

User* createUser(char* name, char* surname, char* rut, bool admin)
{
    User* user = createEmptyUser();

    strcpy(user->name, name);
    strcpy(user->surname, surname);
    strcpy(user->rut, rut);
    user->admin = admin;

    return user;
}

void setUserValue(User* user, char* value, int i)
{
    switch (i)
    {
        case 0:
            user->name = value;
            break;
        case 1:
            user->surname = value;
            break;
        case 2:
            user->rut = value;
            break;
        case 3:
            if (strcmp("SI", value) == 0)
            {
                user->admin = true;
            }
            else if (strcmp("NO", value) == 0)
            {
                user->admin = false;
            }
            break;
    }
}

void copyUser(User* copy, User* toCopy)
{
    if (toCopy == NULL)
    {
        printf("Usuario no encontrado!\n");
        return;
    }

    copy->rut = toCopy->rut;
    copy->name = toCopy->name;
    copy->surname = toCopy->surname;
    copy->admin = toCopy->admin;
    copy->discounts = toCopy->discounts;
}

bool isRut(char* rut, char* check)
{
    if (strlen(rut) > 12)
    {
        return false;
    }

    if (isalpha(rut[11]))
    {
        rut[11] = toupper(rut[11]);
    }

    int j = 0;
    for (int i = 0; i < 12; i++)
    {
        switch (i)
        {
            case 2:
                if (rut[i] != '.')
                {
                    return false;
                }
                break;
            case 6:
                if (rut[i] != '.')
                {
                    return false;
                }
                break;
            case 10:
                if (rut[i] != '-')
                {
                    return false;
                }
                break;
            case 11:
                if (isalpha(rut[i]))
                {
                    if (rut[i] != 'K')
                    {
                        return false;
                    }
                }
                else if (!isdigit(rut[i]))
                {
                    return false;
                }
                break;
            default:
                if (!isdigit(rut[i]))
                {
                    return false;
                }
                check[j] = rut[i];
                j++;
                break;
        }
    }

    return true;
}

bool isRealRut(char* rut)
{
    int serie[6] = {2, 3, 4, 5, 6, 7};
    char* check = (char*)malloc(sizeof(char) * 20);
    char digit = rut[11];
    int j = 0;
    int value = 0;
    
    if (isRut(rut, check))
    {
        for (int i = 7; i >= 0; i--)
        {
            char *ptr = (char*)malloc(sizeof(char) * 2);
            ptr[0] = check[i];
            ptr[1] = '\0';
            value += (atoi(ptr) * serie[j]);
            free(ptr);
            j++;
            if (j > 5) j = 0;
        }
        free(check);

        value = value % 11;
        value = 11 - value;
        if (value == 11)
        {
            value = 0;
        }

        if (value == 10)
        {
            if (isalpha(digit))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (isdigit(digit))
            {
                char *ptr = (char*)malloc(sizeof(char) * 2);
                ptr[0] = digit;
                ptr[1] = '\0';
                if (value == atoi(ptr))
                {
                    free(ptr);
                    return true;
                }
                else
                {
                    free(ptr);
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        free(check);
        return false;
    }
}

char* checkRut()
{
    char* rut = (char*)malloc(sizeof(char) * 20);
    scanf("%s", rut);
    while (!isRealRut(rut))
    {
        printf("RUT incorrecto, ingrese otro: ");
        scanf("%s", rut);
    }

    if (isalpha(rut[11]))
    {
        rut[11] = toupper(rut[11]);
    }

    return rut;
}

void registerUser(Map* users)
{
    char* name = (char*)malloc(sizeof(char) * 20);
    char* surname = (char*)malloc(sizeof(char) * 20);
    char* esAdmin = (char*)malloc(sizeof(char) * 3);
    bool admin = false;

    printf("Ingrese RUT: ");
    char* rut = checkRut();
    printf("Ingrese Nombre: ");
    scanf("%s", name);
    printf("Ingrese Apellido: ");
    scanf("%s", surname);   
    printf("El nuevo usuario es administrador?, ingrese SI o NO: ");
    scanf("%s", esAdmin);
    // falta ciclo para comprobar esAdmin //
    if ( strcmp("SI", esAdmin) == 0 ) admin = true;
    else if ( strcmp("NO", esAdmin) == 0 ) admin = false;
    
    User* user = createUser(name, surname, rut, admin);
    insertMap(users, user->rut, user);

    printf("Usuario registrado!\n");
}

User* logIn(Map* users)
{
    printf("Ingrese su RUT: ");
    char* rut = checkRut();

    User* user = searchMap(users, rut);
    free(rut);
    if (user) return user;
    else return NULL;
}

void logOut(User* user)
{
    User* empty = createEmptyUser();
    empty->rut = "";
    copyUser(user, empty);
}

bool isAdmin(User* user)
{
    return user->admin;
}

char* getRut(User* user)
{
    return user->rut;
}

void setRut(User* user, char* s)
{
    user->rut = s;
}

void printUser(User* user)
{
    if (strlen(getRut(user)) == 0)
    {
        printf("Sesion no iniciada!");
        return;
    }        

    printf("Nombre: %s\n", user->name);
    printf("Apellido: %s\n", user->surname);
    printf("RUT: %s\n", user->rut);
}

void addDiscount(Map* users)
{
    printf("Ingrese RUT de usuario: ");
    char* rut = checkRut();

    User* user = searchMap(users, rut);
    if (user == NULL)
    {
        printf("Usuario no encontrado!\n");
        free(rut);
        return;
    }

    free(rut);
    Discounts* discount = createDiscount();
    if (discount == NULL) return;
    pushBack(user->discounts, discount);
}

void cleanDiscounts(Map* users)
{
    printf("Ingrese RUT de usuario: ");
    char* rut = checkRut();

    User* user = searchMap(users, rut);
    if (user == NULL)
    {
        printf("Usuario no encontrado!\n");
        free(rut);
        return;
    }

    cleanList(user->discounts);
    free(rut);
}

List* getDiscounts(User* user)
{
    return user->discounts;
}

void socialClub(User* user, Map* users, Map* itemPerId)
{
    if (isAdmin(user))
    {
        printf("Ingrese RUT de usuario a revisar: ");
        char* rut = checkRut();
        User* aux = searchMap(users, rut);
        if (aux != NULL)
        {
            printDiscounts(aux, itemPerId);
        }
        else
        {
            printf("Usuario no encontrado!\n");
        }

        free(rut);
    }
    else
    {
        printDiscounts(user, itemPerId);
    }
}

char* userToChar(User* user)
{
    char* string = (char*)malloc(sizeof(char) * 100);
    strcpy(string, user->name);
    strcat(string, ",");
    strcat(string, user->surname);
    strcat(string, ",");
    strcat(string, user->rut);
    strcat(string, ",");

    if (user->admin)
    {
        strcat(string, "SI");
    }
    else
    {
        strcat(string, "NO");
    }
    strcat(string, ",\n");

    return string;
}