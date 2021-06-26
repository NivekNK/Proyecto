#include <stdbool.h>
#include <string.h>
#include "items.h"
#include "list.h"
#include "Map.h"

struct Item
{
    int id;
    int price;
    int stock;
    char *name;
    char *brand;
    char *type;
};

struct Category
{
    List* items;
    char *type;
    int max;
    int current;
};

struct Discounts
{
    int discount;
    bool isItem;
    Item* item;
    char *type;
};

typedef Item Item;
typedef Category Category;
typedef Discounts Discounts;

Category* createEmptyCategory()
{
    Category* category = (Category*)malloc(sizeof(Category));

    category->items = createList();
    category->type = (char*)malloc(sizeof(char) * 20);
    category->max = 0;
    category->current = 0;

    return category;
}

void createCategory()
{
    
}

Item* createEmptyItem()
{
    Item* item = (Item*)malloc(sizeof(Item));
    
    item->id = 0;
    item->price = 0;
    item->stock = 0;
    item->name = (char*)malloc(sizeof(char) * 20);
    item->brand = (char*)malloc(sizeof(char) * 20);
    item->type = (char*)malloc(sizeof(char) * 20);
    
    return item;
}

void createItem(Map* inventory, Map* category)
{
    Item* item = createEmptyItem();
    
    int size = sizeMapa(inventory);
    item->id = size;

    printf("Ingrese el nombre del producto\n");
    scanf("%s",item->name);
    printf("Ingrese la marca del producto\n");
    scanf("%s",item->brand);
    printf("Ingrese el tipo de producto\n");
    scanf("%s",item->type);
    printf("Ingrese el precio del producto\n");
    scanf("%d",&item->price);
    printf("Ingrese la cantidad stock");
    scanf("%d",&item->stock);
    insertMap(inventory,&item->id,item);
    
    Category* aux = searchMap(category, item->type);
    if (aux != NULL)
    {
        pushBack(aux->items, item);
        aux->current += item->stock;
    }
    else
    {
        
    }
}

void addItem(Map* inventory)
{
    //añadir comprobacion  añandir resto de mapas
    int id;
    int stock;
    scanf("%i", &id);
    scanf("%i", &stock);

    Item* item = searchMap(inventory, &id);
    item->stock=+stock;
}

void removeItemFromId(Map* inventory)
{
    //añadir comprobacion,quitar en resto de mapas
    int id;
    int stock;
    scanf("%i", &id);
    scanf("%i", &stock);

    Item* item = searchMap(inventory, &id);
    item->stock=-stock;
}