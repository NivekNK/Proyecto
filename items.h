#include "Map.h"
#include "mUsers.h"

typedef struct Item Item;
typedef struct Category Category;
typedef struct Discounts Discounts;

Item* createEmptyItem();

Discounts* createEmptyDiscount(bool isItem);

Discounts* createDiscount();
//Funcion que agrega descuento dependiendo del isItem
void setDiscountValue(Discounts* discount, char* value, bool isItem, int i);
//Inserta un item a una categoria
void insertToCategory(Map* category, Item* item, int max);
//Inserta el item nuevo al mapa de estos
void insertItemToMaps(Item* item, Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName);
//Ingresa el valor a un item
void setItemValue(Item* item, char* value, int i);
//Funcion que crea el item en los respectivos mapas
void createItem(Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, Map* category);
//Agrega un item a una categoria por su id
void addItem(Map* itemPerId, Map* category);
//Quita un item de una categoria por su id
void removeItemFromId(Map* itemPerId, Map* category);
//Busca un item por su id
void itemSearch(Map* itemPerId, User* user);
//Busca un item por su categoria
void typeSearch(Map* category, User* user);
//Precio de menor a mayor
void ascendingPrice(Map* itemPerPrice, User* user);
//Items orden alfabetico
void alphabeticPrint(Map* itemPerName, User* user);
//Busca el item por marca
void brandSearch(Map* itemPerBrand, User* user);

void categoryStatus(Map* category);
//Muestra los descuentos
void printDiscounts(User* user, Map* itemPerId);

char* itemToChar(Item* item, Map* category);

char* discountsToChar(User* user);