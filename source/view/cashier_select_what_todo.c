#include <stdlib.h>

#include "view/views.h"
#include "utils/input.h"
#include "utils/string.h"

#include "shop/basket.h"

void autocomplete_stock_list(const char *user_input, StockList *stocks)
{
    list_foreach(item, stocks)
    {
        Item *itemInStocks = (Item *)item->value;

        char item_id_string[5];
        sprintf(item_id_string, "%03d", itemInStocks->id);

        if (str_start_with(user_input, item_id_string))
        {
            printf("%04d %s %5.2f€ ", itemInStocks->id, itemInStocks->label, itemInStocks->price);
            if (itemInStocks->reduction != 0)
            {
                printf("%3d %% \n", itemInStocks->reduction);
            }
            else
                printf("\n");
        }
    }
}

void cashier_select_what_todo(StockList *stock)
{
    Item *item;

    BareCode item_barecode = -1;
    char item_raw_barecode[5];

    int item_quantity = -1;
    char item_raw_quantity[5];

    float totValue = 0.;
    Basket *basket = basket_create();

    do
    {
        stocks_display(stock);
        user_input("Inserez le codebarre de l'article", "####", item_raw_barecode);

        item_barecode = atoi(item_raw_barecode);
        item = stocks_lookup_item(stock, item_barecode);

        if (item != NULL)
        {
            user_input("Entrez la quatite que vous souhaitez acheter", "####", item_raw_quantity);
            item_quantity = atoi(item_raw_quantity);

            if (item_quantity <= 0)
            {
                printf("Achat annuler!\n");
            }
            else
            {
                basket_add_item(basket, item, item_quantity);

                totValue = item->price;
                totValue -= item->price * item->reduction;
                totValue *= item_quantity;
            }
        }

    } while (user_yes_no("Voulez-vous continuer a ajouter des articles au panier ?"));

    printf("voici le contenu du panier : \n\n");
    basket_print_bill(basket);
}