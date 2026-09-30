#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

#include <stdint.h>
#include "order.h"

typedef struct PriceLevel {
    int64_t price; // Price in ticks, 1 tick = 0.01 Cent
    Order *head;   // Pointer to the head of the order linked list
    Order *tail;   // Pointer to the tail of the order linked list
    uint64_t total_quantity; // Total quantity of orders at this price level
    struct PriceLevel *next; // Pointer to the next price level in the order book
    struct PriceLevel *prev; // Pointer to the previous price level in the order book
} PriceLevel;


PriceLevel *create_price_level(int64_t price);
void destroy_price_level(PriceLevel *price_level);
void add_order_to_price_level(PriceLevel *price_level, Order *order);
void remove_order_price_level(PriceLevel *price_level, Order *order);

#endif