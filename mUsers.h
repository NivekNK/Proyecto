<<<<<<< HEAD
#include <stdio.h>
#include <stdbool.h>
#include "Map.h"

#ifndef MUsers_h
#define MUsers_h

typedef struct User User;

User* createEmptyUser();

void copyUser(User* copy, User* toCopy);

void registerUser(Map* users);

User* logIn(Map* users);

bool isAdmin(User* user);

char* getRut(User* user);

void printUser(User* user);

#endif /* M_Users */
=======
#include <stdio.h>
#include <Map.h>
#include <stdbool.h>

typedef struct User User;

void registerUser(Map* users);

User* logIn(Map* users);

bool isAdmin(User* user);

char* getRut(User* user);
>>>>>>> c76b294740a02ae13ffc2915946a5a27413b500c
