#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"


int index_research(pair_s *pair_list, int size, char *item_name)
{
    for (int i = 0 ; i<size ; i++ )
    {
        if (pair_list[i].item->name==item_name)
        {
            return i;
        }
    }
    return -1;
}

void swap(pair_s *pair_list, int i, int j)
{
  pair_s tmp = pair_list[i];
  pair_list[i]=pair_list[j];
  pair_list[j]=tmp;
}
