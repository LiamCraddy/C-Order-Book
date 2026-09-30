#include <inttypes.h>
#include <stdio.h>
#include "display.h"

void print_book(OrderBook *order_book) {
    if (order_book == NULL) {
        printf("No order book provided. \n");
        return;
    }
    printf("Order Book:\n");
    printf("Asks:\n");
    PriceLevel *current_ask = order_book->first_ask;
    while (current_ask != NULL) {
        printf("Price: %" PRId64 ".%02" PRId64 ", Total Quantity: %" PRIu64 " \n", current_ask->price / 100, current_ask->price % 100, current_ask->total_quantity);
        Order *current_order = current_ask->head;
        while (current_order != NULL) {
            printf(" Order ID: %" PRIu64 ", Remaining Quantity: %" PRIu64 "\n", current_order->order_id, current_order->remaining_quantity);
            current_order = current_order->next;
        }
        current_ask = current_ask->next;
    }

    printf("================================\n");
    printf("Bids: \n");
    PriceLevel *current_bid = order_book->first_bid;
    while (current_bid != NULL) {
        printf("Price: %" PRId64 ".%02" PRId64 ", Total Quantity: %" PRIu64 " \n", current_bid->price / 100, current_bid->price % 100, current_bid->total_quantity);
        Order *current_order = current_bid->head;
        while (current_order != NULL) {
            printf(" Order ID: %" PRIu64 ", Remaining Quantity: %" PRIu64 "\n", current_order->order_id, current_order->remaining_quantity);
            current_order = current_order->next;
        }
        current_bid = current_bid->next;
    }
}
