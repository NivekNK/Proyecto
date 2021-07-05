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

void setRut(User* user, char* s);

void printUser(User* user);

#endif /* M_Users */