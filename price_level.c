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
    if (price_level != NULL) {
        Order *current_order = price_level->head;
        while (current_order != NULL) {
            Order *next_order = current_order->next;
            destroy_order(current_order);
            current_order = next_order;
        }
        free(price_level);
    }
}

void add_order_to_price_level(PriceLevel *price_level, Order *order)  {
    
    if (price_level == NULL || order == NULL) {
        return;
    }

    if (price_level->tail == NULL) {
        price_level->head = order;
        price_level->tail = order;
    } else {
        price_level->tail->next = order;
        order->prev = price_level->tail;
        price_level->tail = order; 
        order->next = NULL;
    }

    price_level->total_quantity += order->quantity;
}
void remove_order_price_level(PriceLevel *price_level, Order *order) {
    if (price_level == NULL || order == NULL) {
        return;
    }
    if (order->prev == NULL) {
        price_level->head = order->next;
        if (order->next != NULL) {
            order->next->prev = NULL;
        }
    } else {
        order->prev->next = order->next;
    }
    if (order->next == NULL) {
        price_level->tail = order->prev;
        if (order->prev != NULL) {
            order->prev->next = NULL;
        }
    } else {
        order->next->prev = order->prev;
    }

    price_level->total_quantity -= order->quantity;
    order->next = NULL;
    order->prev = NULL;
}