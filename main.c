#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"

int main() {
    spell_s poison={0, 0, 0, 10, 2, "Poison"};
    spell_s soin={0, 0, 25, 25, -1, "Soin"};
    spell_s strike={0, -50, 0, 25, -1, "Strike"};
    spell_s shield={1, 0, 0, 15, -1, "Shield"};
    entity_s player= {"Player","Cle a molette",100, 100, 25, 25, 20, 0, 0, 1, &water, 1, 1};
    entity_s alfred= {"Alfred technicien","reconsideration des donnees",50, 50, 100, 100, 10, 0, 0, 1, &soin, 1, 1};
    entity_s lili=   {"Lili navigatrice","calcul du temps de trajet",100, 100, 25, 25, 20, 0, 0, 1, &strike, 1, 1};
    entity_s hector= {"Hector gros bras","reserrage de boulons",125, 125, 30, 30, 18, 0, 0, 1, &shield, 1, 1};
    entity_s chief=  {"Moteur principal","echauffement", 200, 200, 10, 10, 12, 0, 0, 1, &poison, 1, 1};
    entity_s orc=    {"Le four","fumee menacante", 110, 110, 0, 0, 9, 0, 0, 1, NULL, 1, 1};
    entity_s gob=    {"Les divers tubes","tremblements anormaux", 50, 50, 0, 0, 4, 0, 0, 1, NULL, 1, 1};
    entity_s squig=  {"Tout ce qui chauffe","vapeurs sous pression", 100, 100, 0, 0, 10, 0, 0, 1, NULL, 1, 1};
    team_s allies=   {"Equipage du VapeurBleu", 0, NULL};
    team_s opponents={"Machinerie du VapeurBleu", 0, NULL};
    add_to_team(&allies,&player); add_to_team(&allies,&healer); add_to_team(&allies,&warrior); add_to_team(&allies,&templar);
    add_to_team(&opponents,&chief); add_to_team(&opponents,&orc); add_to_team(&opponents,&gob); add_to_team(&opponents,&squig);
    setup_player(&player);
    return 0;
}
