#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "list.h"
#include "Map.h"
#include "mUsers.h"

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
    int item;
    char *type;
};

typedef Item Item;
typedef Category Category;
typedef Discounts Discounts;

Category* createCategory()
{
    Category* category = (Category*)malloc(sizeof(Category));

    category->items = createList();
    category->type = (char*)malloc(sizeof(char) * 20);
    category->max = 0;
    category->current = 0;

    return category;
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

Discounts* createEmptyDiscount(bool isItem)
{
    Discounts* discount = (Discounts*)malloc(sizeof(Discounts));

    discount->discount = 0;
    discount->isItem = isItem;
    if (discount->isItem)
    {
        discount->item = -1;
    }
    else
    {
        discount->type = (char*)malloc(sizeof(char) * 20);
    }

    return discount;
}

Discounts* createDiscount()
{
    Discounts* discount = (Discounts*)malloc(sizeof(Discounts));
    char* aux = (char*)malloc(sizeof(char) * 10);

    printf("Se hara un descuento a un \"item\" o a un \"tipo\" de item: ");
    scanf("%s", aux);

    if (strcmp(aux, "item") == 0)
    {
        discount->isItem = true;
        printf("Ingrese id de item con descuento: ");
        scanf("%i", &discount->item);
        printf("Indique porcentaje a descontar: ");
        scanf("%i", &discount->discount);
    }
    else if (strcmp(aux, "tipo") == 0)
    {
        discount->isItem = false;
        printf("Ingrese tipo de item con descuento: ");
        discount->type = (char*)malloc(sizeof(char) * 20);
        scanf("%s", discount->type);
        printf("Indique porcentaje a descontar: ");
        scanf("%i", &discount->discount);
    }
    else
    {
        printf("Descuento incorrecto, intente nuevamente!\n");
        free(discount);
    }
    free(aux);

    return discount;
}

void setDiscountValue(Discounts* discount, char* value, bool isItem, int i)
{
    switch (i)
    {
        case 1:
            discount->discount = atoi(value);
            break;
        case 2:
            if (isItem)
            {
                discount->item = atoi(value);
            }
            else
            {
                strcpy(discount->type, value);
            }
            break;
    }
}

void insertToCategory(Map* category, Item* item, int max)
{
    Category* aux = searchMap(category, item->type);
    if (aux != NULL)
    {
        pushBack(aux->items, item);
        aux->current += item->stock;
        if (aux->current > aux->max)
        {
            int del = aux->current - aux->max;
            aux->current = aux->max;
            item->stock -= del;
        }
    }
    else
    {
        Category* newCategory = createCategory();

        newCategory->type = item->type;
        newCategory->max = max;
        newCategory->current += item->stock;
        if (newCategory->current > newCategory->max)
        {
            int del = newCategory->current - newCategory->max;
            newCategory->current = newCategory->max;
            item->stock -= del;
        }

        pushBack(newCategory->items, item);
        insertMap(category, item->type, newCategory);
    }
}

void insertItemToMaps(Item* item, Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName)
{
    item->id = sizeMapa(itemPerId);

    insertMap(itemPerId, &item->id, item);
    insertMap(itemPerName, item->name, item);

    List* auxBrand = searchMap(itemPerBrand, item->brand);
    if (auxBrand != NULL)
    {
        pushBack(auxBrand, item);
    }
    else
    {
        auxBrand = createList();
        pushBack(auxBrand, item);
        insertMap(itemPerBrand, item->brand, auxBrand);
    }

    List* auxPrice = searchMap(itemPerPrice, &item->price);
    if (auxPrice != NULL)
    {
        pushBack(auxPrice, item);
    }
    else
    {
        auxPrice = createList();
        pushBack(auxPrice, item);
        insertMap(itemPerPrice, &item->price, auxPrice);
    }
}

void setItemValue(Item* item, char* value, int i)
{
    switch (i)
    {
        case 0:
            item->price = atoi(value);
            break;
        case 1:
            item->stock = atoi(value);
            break;
        case 2:
            item->name = value;
            break;
        case 3:
            item->brand = value;
            break;
        case 4:
            item->type = value;
            break;
    }
}

void createItem(Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, Map* category)
{
    Item* item = createEmptyItem();
    
    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]s", item->name);
    printf("Ingrese la marca del producto: ");
    scanf(" %[^\n]s", item->brand);
    printf("Ingrese el precio del producto: ");
    scanf("%d", &item->price);
    printf("Ingrese el tipo de producto: ");
    scanf("%s", item->type);
    printf("Ingrese la cantidad stock: ");
    scanf("%d", &item->stock);

    Category* aux = searchMap(category, item->type);
    if (aux == NULL)
    {
        Category* newCategory = createCategory();

        newCategory->type = item->type;
        newCategory->current = item->stock;
        printf("Ingrese cantidad maxima de item en stock: ");
        scanf("%i", &newCategory->max);

        if (newCategory->current > newCategory->max)
        {
            newCategory->current = newCategory->max;
            item->stock = newCategory->max;
        }

        pushBack(newCategory->items, item);
        insertMap(category, newCategory->type, newCategory);
    }
    else
    {
        pushBack(aux->items, item);
        aux->current += item->stock;
        if (aux->current > aux->max)
        {
            int del = aux->current - aux->max;
            aux->current = aux->max;
            item->stock -= del;
        }
    }
    
    insertItemToMaps(item, itemPerId, itemPerBrand, itemPerPrice, itemPerName);
}

void addItem(Map* itemPerId, Map* category)
{
    int id;
    int stock;
    printf("Ingrese ID: ");
    scanf("%i", &id);
    Item* item = searchMap(itemPerId, &id);
    if (item == NULL)
    {
        printf("Item no encontrado!\n");
        return;
    }

    printf("Ingrese cantidad a agregar: ");
    scanf("%i", &stock);

    Category* aux = searchMap(category, item->type);
    if (aux->current == aux->max)
    {
        printf("No se puede agregar mas de este tipo de item!\n");
        return;
    }

    if (aux->current + stock > aux->max)
    {
        stock = aux->max - aux->current;
    }

    item->stock += stock;
    aux->current += stock;

    printf("Stock correctamente agregado!\n");
}

void removeItemFromId(Map* itemPerId, Map* category)
{
    int id;
    int stock;
    printf("Ingrese ID: ");
    scanf("%i", &id);
    Item* item = searchMap(itemPerId, &id);
    if (item == NULL)
    {
        printf("Item no encontrado!\n");
        return;
    }

    printf("Ingrese cantidad a eliminar: ");
    scanf("%i", &stock);

    Category* aux = searchMap(category, item->type);
    if (aux->current == 0)
    {
        printf("No se puede eliminar mas de este tipo de item!\n");
       return;
    }

    if (aux->current - stock < 0)
    {
        stock = aux->current;
    }
        
    aux->current -= stock;
    item->stock -= stock;
    if (item->stock < 0) item->stock = 0;

    printf("Stock correctamente eliminado!\n");
}

void printItem(Item* item, User* currentUser)
{
    printf("ID: %i - %s | Precio Normal: $%i | ", item->id, item->name, item->price);
    // Si hay un usuario con la sesion iniciada
    if (strlen(getRut(currentUser)) != 0)
    {
        List* discounts = getDiscounts(currentUser);
        if (listSize(discounts) != 0)
        {
            Discounts* discount = firstList(discounts);
            while (discount != NULL)
            {
                if (discount->isItem)
                {
                    if (discount->item == item->id)
                    {
                        int price = (item->price * discount->discount) / 100;
                        price = item->price - price;
                        printf("Precio Descuento: $%i", price);
                        printf(" | ");
                        break;
                    }
                }
                else
                {
                    if (strcmp(discount->type, item->type) == 0)
                    {
                        int price = (item->price * discount->discount) / 100;
                        price = item->price - price;
                        printf("Precio Descuento: $%i", price);
                        printf(" | ");
                        break;
                    }
                }
                discount = nextList(discounts);
            }
        }
    }
    printf("Marca: %s | Tipo: %s | Cantidad: %i |\n", item->brand, item->type, item->stock);
}

void itemSearch(Map* itemPerId, User* currentUser)
{
    int id;
    printf("Ingrese ID: ");
    scanf("%i", &id);

    Item* item = searchMap(itemPerId, &id);
    if (item == NULL)
    {
        printf("Item no encontrado!\n");
        return;
    }

    printItem(item, currentUser);
}

void typeSearch(Map* category, User* currentUser)
{
    char* type = (char*)malloc(sizeof(char) * 20);
    printf("Ingrese tipo de item: ");
    scanf("%s", type);

    Category* aux = searchMap(category, type);
    if (aux != NULL)
    {
        Map* order = createMap(is_equal_int);
        setSortFunction(order, lower_than_int);

        Item* auxItem = firstList(aux->items);
        while (auxItem != NULL)
        {
            List* itemsPrice = searchMap(order, &auxItem->price);
            if (itemsPrice != NULL)
            {
                pushBack(itemsPrice, auxItem);
            }
            else
            {
                itemsPrice = createList();
                pushBack(itemsPrice, auxItem);
                insertMap(order, &auxItem->price, itemsPrice);
            }
            auxItem = nextList(aux->items);
        }

        List* items = firstMap(order);
        while (items != NULL)
        {
            Item* item = firstList(items);
            while (item != NULL)
            {
                printItem(item, currentUser);
                item = nextList(items);
            }
            items = nextMap(order);
        }

        free(order);
    }
    else
    {
        printf("Tipo de item no encontrado!\n");
    }

    free(type);
}

void ascendingPrice(Map* itemPerPrice, User* currentUser)
{
    List* items = firstMap(itemPerPrice);
    while (items != NULL)
    {
        Item* item = firstList(items);
        while (item != NULL)
        {
            printItem(item, currentUser);
            item = nextList(items);
        }
        items = nextMap(itemPerPrice);
    }
}

void alphabeticPrint(Map* itemPerName, User* currentUser)
{
    Item* item = firstMap(itemPerName);
    while (item != NULL)
    {
        printItem(item, currentUser);
        item = nextMap(itemPerName);
    }
}

void brandSearch(Map* itemPerBrand, User* currentUser)
{
    char* brand = (char*)malloc(sizeof(char) * 20);
    printf("Ingrese marca: ");
    scanf(" %[^\n]s", brand);

    List* brandList = searchMap(itemPerBrand, brand);
    free(brand);
    if (brandList == NULL)
    {
        printf("Marca no encontrada!\n");
        return;
    }

    Item* item = firstList(brandList);
    while (item != NULL)
    {
        printItem(item, currentUser);
        item = nextList(brandList);
    }
}

void categoryStatus(Map* category)
{
    Category* aux = firstMap(category);
    while (aux != NULL)
    {
        printf("%s: ", aux->type);
        printf("%i", aux->current);
        printf("/");
        printf("%i\n", aux->max);

        aux = nextMap(category);
    }
}

void printDiscounts(User* user, Map* itemPerId)
{
    List* discounts = getDiscounts(user);
    if (listSize(discounts) == 0)
    {
        printf("Actualmente no tiene descuentos!\n");
        return;
    }

    Discounts* discount = firstList(discounts);
    while (discount != NULL)
    {
        if (discount->isItem)
        {
            Item* item = searchMap(itemPerId, &discount->item);
            printf("%i%s de descuento en %s de la marca %s.\n", discount->discount, "%", item->name, item->brand);
        }
        else
        {
            printf("%i%s de descuentos en items de tipo \"%s\".\n", discount->discount, "%", discount->type);
        }
        discount = nextList(discounts);
    }
}

char* itemToChar(Item* item, Map* category)
{
    char* string = (char*)malloc(sizeof(char) * 100);
    sprintf(string, "%i", item->price);
    strcat(string, ",");
    char str[16];
    sprintf(str, "%i", item->stock);
    strcat(string, str);
    strcat(string, ",");
    strcat(string, item->name);
    strcat(string, ",");
    strcat(string, item->brand);
    strcat(string, ",");
    strcat(string, item->type);
    strcat(string, ",");

    Category* aux = searchMap(category, item->type);
    char str2[16];
    sprintf(str2, "%i", aux->max);
    strcat(string, str2);
    strcat(string, ",\n");

    return string;
}

char* discountsToChar(User* user)
{
    char* string = (char*)malloc(sizeof(char) * 500);
    strcpy(string, getRut(user));
    strcat(string, ",");

    List* discounts = getDiscounts(user);
    Discounts* discount = firstList(discounts);
    while (discount != NULL)
    {
        if (discount->isItem)
        {
            strcat(string, "SI ");
            char str[16];
            sprintf(str, "%i", discount->discount);
            strcat(string, str);
            strcat(string, " ");
            char str2[16];
            sprintf(str2, "%i", discount->item);
            strcat(string, str2);
        }
        else
        {
            strcat(string, "NO ");
            char str[16];
            sprintf(str, "%i", discount->discount);
            strcat(string, str);
            strcat(string, " ");
            strcat(string, discount->type);
        }
        strcat(string, ",");
        discount = nextList(discounts);
    }
    strcat(string, "\n");
    
    return string;
}