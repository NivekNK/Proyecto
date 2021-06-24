#include <stdio.h>
#include <Map.h>
#include <stdbool.h>

typedef struct User User;

void registerUser(Map* users);

User* logIn(Map* users);

bool isAdmin(User* user);

char* getRut(User* user);