#include <stdlib.h>
#include "order.h"

Order *create_order(uint64_t order_id, OrderType type, OrderExecutionType execution_type, int64_t price, uint64_t quantity, uint64_t timestamp) {
    Order *order = (Order *)malloc(sizeof(Order));
    if (order == NULL) {
        return NULL; // Memory allocation failed
    }
    
    order->order_id = order_id;
    order->type = type;
    order->execution_type = execution_type;
    order->price = (execution_type == ORDER_MARKET) ? 0 : price;
    order->quantity = quantity;
    order->remaining_quantity = quantity; // Initially, remaining quantity is the same as total quantity
    order->timestamp = timestamp;
    order->status = ORDER_NEW; // New orders start with ORDER_NEW status
    order->next = NULL;
    order->prev = NULL;

    return order;
}

void destroy_order(Order *order) {
    if (order != NULL) {
        free(order);
    }
}