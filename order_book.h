#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "price_level.h"

typedef struct OrderBook
{
    PriceLevel *first_ask;
    PriceLevel *first_bid;    
} OrderBook;

OrderBook *create_order_book(void);
void destroy_order_book(OrderBook *order_book);
void find_price_level(OrderBook *order_book, int64_t price, int is_ask, PriceLevel **found_price_level);
void insert_price_level(OrderBook *order_book, PriceLevel *new_price_level, int is_ask);
void remove_price_level(OrderBook *order_book, PriceLevel *price_level, int is_ask);

#endif