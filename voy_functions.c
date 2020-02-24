#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"


void add_destination(destinations_s *destinations, lieu_s* lieu)
{
    destinations->liste_lieux = realloc(destinations->liste_lieux, (destinations->size + 1) * sizeof(lieu_s **));
    destinations->liste_lieux[destinations->size] = lieu;
    destinations->size++;
}

void voyage(joueur_s *joueur)
{
    aff_lieux_proches(joueur->position);
    printf("Endurance : %d\n", joueur->endurance);
    char* position_tmp = joueur->position->nom;
    while (strcmp(position_tmp,joueur->position->nom)==0)
    {
      joueur->position = choix_destination(joueur->position);
      vide_buff();
    }
    joueur->endurance -= joueur->position->diff;
}

lieu_s* choix_destination(lieu_s* position)
{
  char choix[200];
  int a;
  printf("Ou aller ?\n");
  scanf("%[^\n]s", choix);

  for (int i=0; i<position->lieux_proches.size; i++)
  {
      if(strcmp(choix, position->lieux_proches.liste_lieux[i]->nom)==0)
      {
          position = position->lieux_proches.liste_lieux[i];
          printf("%s\n", position->nom);
          return position;
      }
  }
  printf("Cette destination est indisponible\n");
  return position;
}

void repos(joueur_s* joueur){
  char choix[200];
  while (1) {
    scanf("%[^\n]s", choix);
    if(strcmp(choix,"oui")==0){
      joueur->endurance += 20;
      if (joueur->endurance>joueur->endurance_max) { joueur->endurance = joueur->endurance_max; }
      printf("Endurance : %d\n", joueur->endurance);
      vide_buff();
      return ;
    }else if (strcmp(choix,"non")!=0) {
      printf("oui/non\n");
    }else {
      vide_buff();
      return;
    }
  vide_buff();
  }
}

void avant_poste(lieu_s* lieu){
  char choix[200];
  while (1) {
    scanf("%[^\n]s", choix);
    if(strcmp(choix,"oui")==0){
      lieu->avant_poste = 1;
      lieu->diff = lieu->diff/2;
      return ;
    }else if (strcmp(choix,"non")!=0) {
      printf("oui/non");
    }else {
      return;
    }
  vide_buff();
  }
}

void vide_buff(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}
