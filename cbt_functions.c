#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"



void clrscreen()
{
    system("@cls||clear");
}


// Dmande du nom
void setup_player(entity_s *player)
{
    clrscreen();
    char name[1024];
    printf("Tu diriges le celebre \"Vapeur bleu\", train à vapeur de transport de marchandises\n");
    printf("Choisi ton nom :\n");
    scanf("%[^\n]s",name); //permet d'enregister tout jusqu'au premier \n, dont les espaces. Peut générer un crash si le joueur entre un nom plus gros que 1024 octets.
    player->name=strdup(name);
    clrscreen();
    //dessin();
}

//Initialisation du round
int round_start_ia(entity_s *mob, team_s *opponents)
{
    if (mob->status==DEAD)
    {
        printf("%s Etat : stable\n",mob->name);
        return -1;
    }
    if (mob->pm<mob->pm_max) { mob->pm++; } //On peut ajouter cette ligne si on veut que le monstre régénère des pm
    if (mob->spell!=NULL)
    {
        if (mob->pm>=mob->spell->cost_pm) { mob->action=rand()%3; }
    }
    else { mob->action=rand()%2; }
    mob->target=opponents->members[rand()%4];
    printf("%s Pourcentage de desordre: %d\n", mob->name, mob->hp);
}

void choice_target (entity_s *character,team_s *targetted_team)
{
    int i;
    printf("Que vas tu réparer ? :{1}[%s] {2}[%s] {3}[%s] {4}[%s]\n",targetted_team->members[0]->name,targetted_team->members[1]->name,targetted_team->members[2]->name,targetted_team->members[3]->name);
    scanf("%d",&i);
    character->target=targetted_team->members[i-1];
}


int round_start_character(entity_s *character, team_s *allies, team_s *ennemies)
{
    if (character->status==DEAD)
    {
        printf("%sN'est plus disponnible pour ce trajet\n",character->name);
        return -1;
    }

    int targetted_team=0;
    int round_step=1;

    if (character->pm<character->pm_max) { character->pm++; }
    printf("%s Etat de calme :%d\n", character->name, character->hp);
    printf("%s pm: %d\n",character->name, character->pm);
    while(round_step==1)
    {
        printf("[1]Reparer [2]se mettre a couvert [3]%s action speciale (coute %d) [4]bouteille d'eau(coute 10pm) ?\n",character->spell->name,character->spell->cost_pm);
        scanf("%u",&(character->action));
        if (character->action==ANTIDOTE & character->pm<3){ printf("Pas assez de pm pour aller chercher une \"bouteille d'eau\"\n");  }
        else { round_step++;}
    }
    if (character->action!=DEFENSE)
    {
        while(round_step==2) {
            printf("Choisis ta cible :\n");
            printf("Quelle equipe ? : {0}[%s] {1}[%s]\n",allies->name, ennemies->name);
            scanf("%d",&targetted_team);
            if (targetted_team==0)
            {
                choice_target(character, allies);
                if (character->target->status==DEAD)
                {
                    printf("Cette cible est hors jeu, choisis en une autre\n");
                }
                else
                {
                  round_step++;
                }
            }
            else if (targetted_team==1)
            {
                choice_target(character, ennemies);
                if (character->target->status==DEAD)
                {
                    printf("Cette cible est hors jeu, choisis en une autre\n");
                }
                else
                {
                    round_step++;
                }
            }
            else
            {
                printf(">!>!>!Mauvaise commande!<!<!<\n");
            }
        }
    }
    else {
      character->target=character; // Permet d'éviter d'appeler plus tard la fonction attaque avec un target=NULL
    }
    printf("\n");
}

//Resolution de l'attaque d'une entitée sur une autre
int attack(entity_s *assaillant, entity_s *target)
{
    if (assaillant->status==DEAD)
    {
      printf("%s N'est plus considere(e) pour ce trajet.\n",assaillant->name);
      return -1;
    }

    if (target->status==DEAD)
    {
      printf("La cible \"%s\" N'est plus considere(e) pour ce trajet.\n",assaillant->name);
      return -1;
    }

    printf("-------------- %s --------------\n", assaillant->name);

    switch (assaillant->action) {

        case ATTACK:

            if (target->action==DEFENSE) {
                printf("%s Se protege!\n",target->name);
              }
            printf("%s utilise %s et inflige %d points de desordre à %s.\n", assaillant->name, assaillant->attack, assaillant->dmg/target->def, target->name);
            target->hp-=assaillant->dmg/target->def;
            break;

        case DEFENSE:

            assaillant->def+=4;
            printf("%s Se protege!\n",assaillant->name);
            break;

        case CAST:

            printf("%s utilise %s sur %s\n", assaillant->name, assaillant->spell->name, target->name);
            spell(assaillant, target);
            break;

        case ANTIDOTE:

            printf("%s utilise BOUTEILLE D'EAU\n",assaillant->name);
            printf("%s est rafraichi(e)\n",assaillant->name);
            assaillant->pm-=10;
            assaillant->status=1;
            break;

    }

    printf("\n");
    if(target->hp<=0)
    {
        target->status=0;
    }
}

//Resolution du spell des alliés vers une entitée
void spell(entity_s *caster, entity_s *target)
{
    if (caster->spell->def!=0)
    {
        target->def_init+=caster->spell->def;
        printf("%s gain %d point of defense\n",target->name,caster->spell->def);
    }
    if (caster->spell->dmg!=0)
    {
        target->hp+=caster->spell->dmg;
        printf("%s lost %d life points\n",target->name,caster->spell->dmg);
    }
    if (caster->spell->hp!=0)
    {
        target->hp+=caster->spell->dmg;
        printf("%s is healed by %d life points\n",target->name,caster->spell->hp);
    }
    if (caster->spell->status_modif!=(-1))
    {
        target->status=caster->spell->status_modif;
    }
    caster->pm-=caster->spell->cost_pm;
}

//Resolutions spéciales en fonction du statut de l'entitée
void status_resume(entity_s *entity)
{
    switch (entity->status) {

        case POISONNED:
            entity->hp-=5;
            printf("%s est trempé et prend 5 points de desordre\n",entity->name);
            break;

        case DEAD:
            printf("%s est mis hors jeu.\n",entity->name);
            break;
    }
    entity->def=entity->def_init;
}

void add_to_team(team_s *team, entity_s *member)
{
    team->members = realloc(team->members, (team->size + 1) * sizeof(entity_s *));
    team->members[team->size] = member;
    team->size++;
}

int victory_check(team_s *allies, team_s *opponents)
{
    int v_check=0;
    for (int i = 0; i < 4; i++)
    {
        if (allies->members[i]->status==DEAD)
        {
          v_check++;
        }
    }
    if (v_check==4)
    {
          printf("Le VapeurBleu a eu raison de vous\n",opponents->name);
          return 1;
    }
    v_check=0;
    for (int i = 0; i < 4; i++)
    {
        if (opponents->members[i]->status==DEAD)
        {
            v_check++;
        }
    }
    if (v_check==4)
    {
          printf("Victoire, vous avez conduit le VapeurBleu à sa destination suivante!\n",opponents->name);
          return 1;
    }
    return 0;
}
