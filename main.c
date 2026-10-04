#include "order_book.h"   
#include "matching.h"     
#include "display.h"      
#include <stdio.h>


int main() {
    OrderBook *orderbook = create_order_book();
    if (orderbook == NULL) {
        return 1;
    }
    uint64_t order_id = 1;
    OrderType type = ORDER_TYPE_SELL;
    OrderExecutionType e_type = ORDER_LIMIT;
    int64_t price = 10000;  
    uint64_t quant = 50;
    uint64_t time = 1;
     
    Order *resting_sell = create_order(order_id, type, e_type, price, quant, time);
    if (resting_sell == NULL) {
        return 1;
    }
    
    match(orderbook, resting_sell);
    printf("hello");

    print_book(orderbook);

    return 0;
}
