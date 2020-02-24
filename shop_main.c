#include "cbt_game.h"
#include "shop_game.h"
#include "voy_game.h"
#include "game.h"



int main()
{
    char move[1024];

    shop_s shop={"L'bon shop", 0, NULL};
    bag_s bag={100, 0, NULL};

    item_s sword= {"Lance", 25};
    item_s shield={"Targe", 20};
    item_s bow=   {"Arc", 30};
    item_s b_d_a=   {"Buveuse d'ames", 200};
    pair_s sword_shop= {5,&sword};
    pair_s shield_shop= {5, &shield};
    pair_s bow_shop= {5, &bow};
    pair_s b_d_a_shop= {1, &b_d_a};
    add_to_shop(shield_shop, &shop);
    add_to_shop(bow_shop, &shop);
    add_to_shop(sword_shop, &shop);
    add_to_shop(b_d_a_shop, &shop);
    tri_shop(&shop);

    do
    {
        print_shop(&shop);
        print_bag(&bag);
        printf("Partir ? (o,n)\n");
        scanf("%s",move);
        printf("%d\n", bag.size);
        if (move[0]=='n'){ buy_item(&bag, &shop); }

    } while (move[0]=='n') ;


    return 0;
}
