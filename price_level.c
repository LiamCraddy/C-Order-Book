#include <stdlib.h>
#include "price_level.h"

PriceLevel *create_price_level(int64_t price) {
    PriceLevel *price_level = (PriceLevel *) malloc(sizeof(PriceLevel));
    if (price_level == NULL) {
        return NULL;
    }

    price_level->price = price;
    price_level->head = NULL;
    price_level->tail = NULL;
    price_level->total_quantity = 0;
    price_level->next = NULL;
    price_level->prev = NULL;

    return price_level;
}


void destroy_price_level(PriceLevel *price_level) {
    if (price_level!= NULL) {
        Order *current_order = price_level->head;
        while (current_order != NULL) {
            Order *next_order = current_order->next;
            destroy_order(current_order);
            current_order = next_order;
        }
        free(price_level);
    }
}