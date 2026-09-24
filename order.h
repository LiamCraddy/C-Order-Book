#include <stdint.h>

typedef enum {
    ORDER_TYPE_BUY,
    ORDER_TYPE_SELL
} OrderType;

typedef enum {
    ORDER_LIMIT,
    ORDER_MARKET
} OrderExecutionType;

typedef enum {
    ORDER_NEW,
    ORDER_PARTIALLY_FILLED,
    ORDER_FILLED,
    ORDER_CANCELED,
    ORDER_REJECTED
} OrderStatus;

typedef struct Order {
    uint64_t order_id;
    OrderType type;
    OrderExecutionType execution_type;
    int64_t price; // Price in ticks, 1 tick = 0.01 Cent
    uint64_t quantity;
    uint64_t remaining_quantity;
    uint64_t timestamp;
    OrderStatus status;
    
    struct Order* next;
    struct Order* prev;
} Order;

Order *create_order(uint64_t order_id, OrderType type, OrderExecutionType execution_type, int64_t price, uint64_t quantity, uint64_t timestamp);
void destroy_order(Order *order);
