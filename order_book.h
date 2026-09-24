#include "price_level.h"

typedef struct OrderBook
{
    PriceLevel *first_ask;
    PriceLevel *first_bid;    
} OrderBook;
