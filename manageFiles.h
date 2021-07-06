#include <stdio.h>
#include "Map.h"

FILE* ImportArchive();

void importUsers(Map* users);

void importFromCSV(Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, Map* category, Map* users);

void exportUsers(Map* users);

void exitApp(Map* itemPerId, Map* users, Map* category);