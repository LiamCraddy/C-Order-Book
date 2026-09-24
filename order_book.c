#include <stdlib.h>
#include "order_book.h"


OrderBook *create_order_book() {
    OrderBook *order_book = (OrderBook *) malloc(sizeof(OrderBook));
    if (order_book == NULL) {
        return NULL;
    }

    order_book->first_ask = NULL;
    order_book->first_bid = NULL;

    return order_book;
}

void destroy_order_book(OrderBook *order_book) {
    if (order_book != NULL) {
        PriceLevel *current_ask = order_book->first_ask;
        while (current_ask != NULL) {
            PriceLevel *next_ask = current_ask->next;
            destroy_price_level(current_ask);
            current_ask = next_ask;
        }

        PriceLevel *current_bid = order_book->first_bid;
        while (current_bid != NULL) {
            PriceLevel *next_bid = current_bid->next;
            destroy_price_level(current_bid);
            current_bid = next_bid;
        }

        free(order_book);
    }
}


void find_price_level(OrderBook *order_book, int64_t price, int is_ask, PriceLevel **found_price_level) {
    if (order_book == NULL) {
        return;
    }

    PriceLevel *current;
    if (is_ask) {
        current = order_book->first_ask;
    } else {
        current = order_book->first_bid;
    }
    while (current != NULL) {
        if (current->price == price) {
            *found_price_level = current;
            return;
        } current = current->next;
    }
    *found_price_level = NULL; 

    
}

void insert_price_level(OrderBook *order_book, PriceLevel *new_price_level, int is_ask) {
    if (order_book == NULL) {
        return;
    }

    PriceLevel **head;
    if (is_ask) {
        head = &order_book->first_ask;
    } else {
        head = &order_book->first_bid;
    }

    if (*head == NULL) {
        *head = new_price_level;
        new_price_level->next = NULL;
        new_price_level->prev = NULL;
        return;
    }
    

}