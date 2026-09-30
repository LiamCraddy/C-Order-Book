#ifndef MATCHING_H
#define MATCHING_H

#include "order_book.h"

void match(OrderBook *order_book, Order *incoming_order);

#endif