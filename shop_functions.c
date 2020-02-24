#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"

void add_to_shop(pair_s pair, shop_s *shop)
{
  shop->pair_list = realloc(shop->pair_list, (shop->size + 1) * sizeof(pair_s));
  shop->pair_list[shop->size] = pair;
  shop->size++;
}

void add_to_bag(item_s *item, bag_s *bag)
{
  for (int i = 0; i < bag->size; i++)
  {
    if (bag->pair_list[i].item->name == item->name)
    {
      bag->pair_list[i].quantity ++;
      return;
    }
  }
  bag->pair_list = realloc(bag->pair_list, (bag->size + 1) * sizeof(pair_s));
  bag->pair_list[bag->size] = (pair_s) {1,item};
  bag->size++;
}

void tri_shop(shop_s *shop)
{
    int v=0;
    while(v<shop->size)
    {
        int i=v;
        for (int j=0; j<shop->size; j++)
        {
            if (strcmp(shop->pair_list[i].item->name,shop->pair_list[j].item->name)<0)
            {
                swap(shop->pair_list,i,j);
                j=i;
            }
        }
        v ++;
    }
}

void print_shop(shop_s *shop)
{
    printf(">>>> %s <<<<\n", shop->name);
    for (int i=0; i< shop->size; i++)
    {
        printf("[%d] %s | prix : %d po | stock: %d\n",i, shop->pair_list[i].item->name, shop->pair_list[i].item->price, shop->pair_list[i].quantity);
    }
}

void print_bag(bag_s *bag)
{
    printf("----------Votre sac---------\n");
    for (int i=0; i< bag->size; i++)
    {
        printf("%s | stock: %d\n", bag->pair_list[i].item->name, bag->pair_list[i].quantity);
    }
    printf("Pieces d'or(po) : %d\n",bag->money);
    printf("\n");
}

void buy_item(bag_s *bag, shop_s *shop)
{
    int buy;
    printf("Entrer l'index de l'objet que vous souhaitez acheter:\n");
    scanf("%d",&buy);
    if (shop->pair_list[buy].quantity==0)
    {
        printf("/!\\Le marchand n'a plus cet item en magasin./!\\\n\n");
        return;
    }
    if (shop->pair_list[buy].item->price>bag->money)
    {
        printf("/!\\Vous n'avez pas assez d'argent pour acheter cet item/!\\\n\n");
        return;
    }
    shop->pair_list[buy].quantity-=1;
    bag->money -= shop->pair_list[buy].item->price;
    add_to_bag(shop->pair_list[buy].item, bag);
    printf("Vous achetez %s pour %d pieces d'or.\n\n",shop->pair_list[buy].item->name,shop->pair_list[buy].item->price);
}
