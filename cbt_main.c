#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"

//Fonction pour actualiser l'affichage dans la console

// MAIN
int combat() {
    srand(time(NULL));
    while (victory_check(&allies, &opponents)==0)
    {
        printf("\n<<<<<<<<<<<<<< NEW ROUND >>>>>>>>>>>>>>>\n\n");
        round_start_ia(&chief,&allies);
        round_start_ia(&orc,&allies);
        round_start_ia(&gob,&allies);
        round_start_ia(&squig,&allies);
        printf("\n");
        round_start_character(&player,&allies,&opponents); //screen cleared after that line
        round_start_character(&healer,&allies,&opponents);
        round_start_character(&warrior,&allies,&opponents);
        round_start_character(&templar,&allies,&opponents);
        for (int i = 0; i < 4; i++)
        {
            if (allies.members[i]->status!=0)
            {
                attack(allies.members[i],allies.members[i]->target);
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if (opponents.members[i]->status!=0)
            {
                attack(opponents.members[i],opponents.members[i]->target);
            }
        }
        printf("----------Status resolution----------\n");
        status_resume(&player);
        status_resume(&healer);
        status_resume(&warrior);
        status_resume(&templar);
        status_resume(&chief);
        status_resume(&orc);
        status_resume(&gob);
        status_resume(&squig);
    }
    return 0;
}
