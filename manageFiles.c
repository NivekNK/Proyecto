#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Map.h"
#include "items.h"
#include "mUsers.h"
#include "manageFiles.h"

//Funcion para leer el k-esimo elemento de un string (separado por comas)
const char *get_csv_field (char * tmp, int k) 
{
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

// Inserta posiciones creadas al mapa indicado
void insertItemsToMap(FILE* file, Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, Map* category)
{
    char linea[1024];
    for (int i = 0; fgets(linea, 100, file) != NULL; i++)
    {
        if (i == 0) continue;

        linea[strcspn(linea, "\n")] = 0;
        Item* item = createEmptyItem();
        for (int j = 0; j < 5; j++)
        {
          setItemValue(item, (char*)get_csv_field(linea, j), j);
        }

        int max = atoi(get_csv_field(linea, 5));
        insertToCategory(category, item, max);
        insertItemToMaps(item, itemPerId, itemPerBrand, itemPerPrice, itemPerName);
    }
}

void insertUserToMap(FILE* file, Map* users)
{
    char linea[1024];
    for (int i = 0; fgets(linea, 100, file) != NULL; i++)
    {
        if (i == 0) continue;

        linea[strcspn(linea, "\n")] = 0;
        User* user = createEmptyUser();
        for (int j = 0; j < 4; j++)
        {
          setUserValue(user, (char*)get_csv_field(linea, j), j);
        }

        insertMap(users, getRut(user), user);
    }
}

void insertDiscountToUser(FILE* file, Map* users)
{
    char linea[1024];
    for (int i = 0; fgets(linea, 100, file) != NULL; i++)
    {
        if (i == 0) continue;

        linea[strcspn(linea, "\n")] = 0;
        User* user = searchMap(users, (char*)get_csv_field(linea, 0));
        if (user != NULL)
        {
          List* discounts = getDiscounts(user);
          char del[] = " ";
          char* aux = (char*)malloc(sizeof(char) * 20);
          strcpy(aux, (char*)get_csv_field(linea, 1));
          
          for (int j = 1; (char*)get_csv_field(linea, j) != NULL != 0; j++)
          {
            bool isItem = true;
            if (strcmp(strtok(aux, del), "NO") == 0)
            {
              isItem = false;
            }

            Discounts* discount = createEmptyDiscount(isItem);
            setDiscountValue(discount, strtok(NULL, del), isItem, 1);
            setDiscountValue(discount, strtok(NULL, del), isItem, 2);
            pushBack(discounts, discount);

            if ((char*)get_csv_field(linea, j + 1) == NULL)
              break;
            
            strcpy(aux, (char*)get_csv_field(linea, j + 1));
          }
        }
    }
}

void importUsers(Map* users)
{
  FILE* user = fopen("usuarios.csv", "r");
  if (user != NULL)
  {
    insertUserToMap(user, users);
    printf("Usuarios correctamente importados!\n");
  }
  fclose(user);
}

void importFromCSV(Map* itemPerId, Map* itemPerBrand, Map* itemPerPrice, Map* itemPerName, Map* category, Map* users)
{
  FILE* items = fopen("items.csv", "r");
  if (items != NULL)
  {
    insertItemsToMap(items, itemPerId, itemPerBrand, itemPerPrice, itemPerName, category);
    printf("Items correctamente importados!\n");
  }
  fclose(items);

  FILE* discounts = fopen("descuentos.csv", "r");
  if (discounts != NULL)
  {
    insertDiscountToUser(discounts, users);
    printf("Descuentos correctamente importados!\n");
  }
  fclose(discounts);
}

void exportUsers(Map* users)
{
  FILE* user = fopen("usuarios.csv", "w");
  fputs("Nombre,Apellido,RUT,esAdmin,\n", user);
  User* auxUser = firstMap(users);
  while (auxUser != NULL)
  {
    char* aux = userToChar(auxUser);
    fputs(aux, user);
    free(aux);
    auxUser = nextMap(users);
  }
  fclose(user);
}

void exitApp(Map* itemPerId, Map* users, Map* category)
{
  FILE* discounts = fopen("descuentos.csv", "w");
  fputs("// Descuentos\n", discounts);
  User* auxDis = firstMap(users);
  while (auxDis != NULL)
  {
    List* disList = getDiscounts(auxDis);
    if (listSize(disList) == 0)
    {
      auxDis = nextMap(users);
      continue;
    }

    char* aux = discountsToChar(auxDis);
    fputs(aux, discounts);
    free(aux);
    auxDis = nextMap(users);
  }
  fclose(discounts);

  FILE* items = fopen("items.csv", "w");
  fputs("Price,CurrentStock,Name,Brand,Type,MaxStock,\n", items);
  Item* item = firstMap(itemPerId);
  while (item != NULL)
  {
    char* aux = itemToChar(item, category);
    fputs(aux, items);
    free(aux);
    item = nextMap(itemPerId);
  }
  fclose(items);
}