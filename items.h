#include "Map.h"
#include "mUsers.h"

typedef struct Item Item;
typedef struct Category Category;
typedef struct Discounts Discounts;

Item* createEmptyItem();

Discounts* createEmptyDiscount(bool isItem);

Discounts* createDiscount();

void setDiscountValue(Discounts* discount, char* value, bool isItem, int i);

void insertToCategory(Map* category, Item* item, int max);

void insertItemToMaps(Item* item, Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName);

void setItemValue(Item* item, char* value, int i);

void createItem(Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, Map* category);

void addItem(Map* itemPerId, Map* category);

void removeItemFromId(Map* itemPerId, Map* category);

void itemSearch(Map* itemPerId, User* user);

void typeSearch(Map* category, User* user);

void ascendingPrice(Map* itemPerPrice, User* user);

void alphabeticPrint(Map* itemPerName, User* user);

void brandSearch(Map* itemPerBrand, User* user);

void categoryStatus(Map* category);

void printDiscounts(User* user, Map* itemPerId);

char* itemToChar(Item* item, Map* category);

char* discountsToChar(User* user);