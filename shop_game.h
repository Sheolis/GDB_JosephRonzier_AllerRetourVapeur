#ifndef __GAME_H_
#define __GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum availability availability_e;
typedef struct shop shop_s;
typedef struct item item_s;
typedef struct bag bag_s;
typedef struct pair pair_s;

int index_research(pair_s *pair_list, int size, char *item_name);
void swap(pair_s *pair_list, int i, int j);


void add_to_shop(pair_s pair, shop_s *shop);
void add_to_bag(item_s *item, bag_s *bag);
void tri_shop(shop_s *shop);
void print_shop(shop_s *shop);
void print_bag(bag_s *bag);
void buy_item(bag_s *bag, shop_s *shop);

//enum availability { NOT_AFFORDABLE=0, AFFORDABLE=1};

//

struct shop
{
    char *name;
    int size;
    pair_s *pair_list;
};

struct item
{
    char* name;
    int price;
};

struct bag
{
  int money;
  int size;
  pair_s *pair_list;
};

struct pair
{
  unsigned int quantity;
  item_s *item;
};

#endif
