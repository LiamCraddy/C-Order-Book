#include "order_book.h"   
#include "matching.h"     
#include "display.h"      
#include <stdio.h>
#include <inttypes.h>

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

    uint64_t order_id2 = 2;
    OrderType type1 = ORDER_TYPE_BUY;
    OrderExecutionType e_type1 = ORDER_LIMIT;
    int64_t price1 = 10000;  
    uint64_t quant1 = 30;
    uint64_t time1 = 2;
     
    Order *resting_sell = create_order(order_id, type, e_type, price, quant, time);
    if (resting_sell == NULL) {
        return 1;
    }
    match(orderbook, resting_sell);
    print_book(orderbook);


    Order *bid = create_order(order_id2, type1, e_type1, price1, quant1, time1);


    match(orderbook, bid);

    print_book(orderbook);

    Order *bid2 = create_order(3, ORDER_TYPE_BUY, ORDER_LIMIT, 10000, 50, 3);
    match(orderbook, bid2);
    print_book(orderbook);

    Order *sell2 = create_order(4, ORDER_TYPE_SELL, ORDER_LIMIT, 10100, 40, 4);
    match(orderbook, sell2);
    print_book(orderbook);

    Order *buy3 = create_order(5, ORDER_TYPE_BUY, ORDER_MARKET, 0, 100, 5);
    match(orderbook, buy3);
    print_book(orderbook);

    destroy_order_book(orderbook);

    printf("======================================\n");
    printf("              FINISHED                \n");
    printf("======================================\n");
    return 0;
}
