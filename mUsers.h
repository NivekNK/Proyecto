#include <stdio.h>
#include <stdbool.h>
#include "Map.h"
#include "list.h"

#ifndef MUsers_h
#define MUsers_h

typedef struct User User;

User* createEmptyUser();

void setUserValue(User* user, char* value, int i);

void copyUser(User* copy, User* toCopy);

void registerUser(Map* users);

User* logIn(Map* users);

void logOut(User* user);

bool isAdmin(User* user);

char* getRut(User* user);

void setRut(User* user, char* s);

void printUser(User* user);

void addDiscount(Map* users);

void cleanDiscounts(Map* users);

List* getDiscounts(User* user);

void socialClub(User* user, Map* users, Map* itemPerId);

char* userToChar(User* user);

#endif /* M_Users */