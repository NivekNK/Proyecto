#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mUsers.h"
#include "list.h"
#include "Map.h"

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

void copyUser(User* copy, User* toCopy)
{
    if (toCopy == NULL) return;

    copy = createUser(toCopy->name, toCopy->surname, toCopy->rut, toCopy->admin);
    // strcpy(copy->name, toCopy->name);
    // strcpy(copy->surname, toCopy->surname);
    // strcpy(copy->rut, toCopy->rut);
    // copy->admin = toCopy->admin;
    // copy->discounts = toCopy->discounts;
}

void registerUser(Map* users)
{    
    char* name = (char*)malloc(sizeof(char) * 20);
    char* surname = (char*)malloc(sizeof(char) * 20);
    char* rut =(char*)malloc(sizeof(char) * 20);
    char* esAdmin = (char*)malloc(sizeof(char) * 3);
    bool admin = false;

    printf("Ingrese Nombre: ");
    scanf("%s", name);
    printf("Ingrese Apellido: ");
    scanf("%s", surname);
    printf("Ingrese RUT: ");
    scanf("%s", rut);
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
    char* rut = (char*)malloc(sizeof(char) * 20);
    printf("Ingrese su RUT: ");
    scanf("%s", rut);

    User* user = searchMap(users, rut);
    return user;
}

bool isAdmin(User* user)
{
    return user->admin;
}

char* getRut(User* user)
{
    return user->rut;
}

void printUser(User* user)
{
    if (user == NULL)
    {
        printf("Sesion no iniciada!");
        return;
    }

    //printf("HOLA\n");
    printf("Nombre: %s\n", user->name);
    printf("Apellido: %s\n", user->surname);
    printf("RUT: %s\n", user->rut);
}