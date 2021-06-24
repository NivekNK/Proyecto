#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <list.h>
#include <Map.h>
#include <mUsers.h>

struct User
{
    char* name;
    char* surname;
    char* rut;
    bool admin;
    List* discounts;
};

typedef User User;

User* createUser(char* name, char* surname, char* rut, bool admin, List* discounts)
{
    User* user = (User*)malloc(sizeof(User));
    strcpy(user->name, name);
    strcpy(user->surname, surname);
    strcpy(user->rut, rut);
    user->admin = admin;
    user->discounts = discounts;
}

void registerUser(Map* users)
{    
    char* name = (char*)malloc(sizeof(char*) * 20);
    char* surname = (char*)malloc(sizeof(char*) * 20);
    char* rut =(char*)malloc(sizeof(char*) * 20);
    char* esAdmin = (char*)malloc(sizeof(char*) * 3);
    bool admin = false;
    List* discounts = createList();
    
    printf("Ingrese Nombre\n");
    scanf("%s", name);
    printf("Ingrese Apellido\n");
    scanf("%s", surname);
    printf("Ingrese RUT\n");
    scanf("%s", rut);
    printf("¿El nuevo usuario es administrador?, ingrese SI o NO");
    scanf("%s", esAdmin);
    // falta ciclo para comprobar esAdmin //
    if ( strcmp("SI", esAdmin) == 0 ) admin = true;
    if ( stcmp("NO", esAdmin) == 0 ) admin = false;
    
    User* user = createUser(name, surname, rut, admin, discounts);
    insertMap(users, rut, user);
    
}

User* logIn(Map* users)
{
    char* rut =(char*)malloc(sizeof(char*) * 20);
    printf("Ingrese su RUT\n");
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