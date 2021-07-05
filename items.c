#include <stdbool.h>
#include "items.h"
#include "list.h"

struct item
{
    int id;
    int price;
    int stock;
    char *name;
    char *brand;
    char *type;
};

struct category
{
    List* items;
    char *type;
    int max;
    int current;
};

struct discounts
{
    int discount;
    bool isItem;
    item* item;
    char *type;
};

typedef item item;
typedef category category;
typedef discounts discounts;


