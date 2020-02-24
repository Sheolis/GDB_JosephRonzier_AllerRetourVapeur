#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"


void aff_lieux_proches(lieu_s *position)
{
  printf("Vous pouvez aller a une de ces destinations :\n");
  for (int i=0; i<position->lieux_proches.size; i++)
  {
    printf("%s\n",position->lieux_proches.liste_lieux[i]->nom);
  }
}
