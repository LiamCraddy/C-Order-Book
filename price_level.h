#include <stdint.h>
#include "order.h"

typedef struct PriceLevel {
    int64_t price; // Price in ticks, 1 tick = 0.01 Cent
    Order *head;   // Pointer to the head of the order linked list
    Order *tail;   // Pointer to the tail of the order linked list
    uint64_t total_quantity; // Total quantity of orders at this price level
    PriceLevel *next; // Pointer to the next price level in the order book
    PriceLevel *prev; // Pointer to the previous price level in the order book
} PriceLevel;