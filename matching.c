#include "order_book.h"
#include <stdio.h>
#include <inttypes.h>

int order_crosses(Order *incoming_order, PriceLevel *opposite_price_level) {
    if (incoming_order->execution_type == ORDER_MARKET) {
        return 1;
    }
    if (incoming_order->type == ORDER_TYPE_BUY) {
        return incoming_order->price >= opposite_price_level->price;
    } else {
        return incoming_order->price <= opposite_price_level->price;
    }
}

void match(OrderBook *order_book, Order *incoming_order) {
    if (order_book == NULL || incoming_order == NULL) {
        return;
    }
    PriceLevel *opposite_price_level = NULL;
    if (incoming_order->type == ORDER_TYPE_BUY) {
        opposite_price_level = order_book->first_ask;
    } else {
        opposite_price_level = order_book->first_bid;
    }
    
    if (opposite_price_level!= NULL && order_crosses(incoming_order, opposite_price_level)) {

        while ((opposite_price_level != NULL && incoming_order->remaining_quantity > 0) 
        && order_crosses(incoming_order, opposite_price_level)) {
    

            Order *current_order = opposite_price_level->head;
            while (current_order != NULL && incoming_order->remaining_quantity > 0) {
                

                uint64_t t_quantity = current_order->remaining_quantity < incoming_order->remaining_quantity ? current_order->remaining_quantity : incoming_order->remaining_quantity;
                current_order->remaining_quantity -= t_quantity;
                incoming_order->remaining_quantity -= t_quantity;
                opposite_price_level->total_quantity -= t_quantity;

                if (current_order->remaining_quantity == 0) {
                    Order *next_order = current_order->next;
                    remove_order_price_level(opposite_price_level, current_order);
                    printf("Order %" PRIu64 " fully filled and removed from price level %" PRId64 ".%02" PRId64 "\n", current_order->order_id, opposite_price_level->price / 100, opposite_price_level->price % 100);
                    destroy_order(current_order);
                    current_order = next_order;
    
                } else {
                    current_order = current_order->next;
                }


                
            }
            if (opposite_price_level->head == NULL) {
            int is_ask = (incoming_order->type == ORDER_TYPE_BUY);
            PriceLevel *empty_level = opposite_price_level;

            opposite_price_level = empty_level->next;  
            remove_price_level(order_book, empty_level, is_ask);
            }
                
        }
    }   
    if (incoming_order->execution_type == ORDER_LIMIT && incoming_order->remaining_quantity > 0) {
        PriceLevel *level = NULL;
        int is_ask = (incoming_order->type == ORDER_TYPE_SELL);
        find_price_level(order_book, incoming_order->price, is_ask, &level);
        if (level != NULL) {
            add_order_to_price_level(level, incoming_order);
        } else {
            PriceLevel *level = create_price_level(incoming_order->price);
            insert_price_level(order_book, level, is_ask);
            add_order_to_price_level(level, incoming_order);
        }
    }
    if (incoming_order->remaining_quantity == 0 || incoming_order->execution_type == ORDER_MARKET) {
        destroy_order(incoming_order);
    }


    return;
}

