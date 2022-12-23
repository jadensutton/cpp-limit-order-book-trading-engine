#include <iostream>

using namespace std;

struct order
{
    int id;
    int qty;
    float price;
    order *next;
};

class Orderbook
{
    private:
        order *bidsHead, *asksHead;
        int bidId, askId;

        int lookForMatch(order *newOrder, string side) {
            /// @brief Method will try to match a newly submitted order with an existing order in the order book
            /// @param newOrder pointer to new order
            /// @param side order side
            /// @return -1 if no fill, 0 if partial fill, 1 if complete fill

            order *tmp;
            int fillStatus = -1;

            if (side == "buy") {
                tmp = asksHead;
                while (tmp != NULL) {
                    if (newOrder->price >= tmp->price) {
                        if (newOrder->qty > tmp->qty) {
                            if (removeOrder(tmp->id, "buy")) {
                                newOrder->qty -= tmp->qty;
                                cout << "ORDER " << tmp->id << " FILLED" << endl;
                                fillStatus = 0;

                                if (newOrder->qty == 0) {
                                    cout << "NEW ORDER FILLED" << endl;
                                    return 1;    
                                }
                            } else {
                                cout << "Attempted to match buy order " << newOrder->id << " with sell order " << tmp->id << " but failed" << endl;
                            }
                        } else {
                            tmp->qty -= newOrder->qty;
                            cout << "NEW ORDER FILLED" << endl;
                            return 1;
                        }
                    } else {
                        break;
                    }
                    tmp = tmp->next;
                }
            } else if (side == "sell") {
                tmp = bidsHead;
                while (tmp != NULL) {
                    if (newOrder->price <= tmp->price) {
                        if (newOrder->qty >= tmp->qty) {
                            if (removeOrder(tmp->id, "buy")) {
                                newOrder->qty -= tmp->qty;
                                cout << "ORDER " << tmp->id << " FILLED" << endl;
                                fillStatus = 0;

                                if (newOrder->qty == 0) {
                                    cout << "NEW ORDER FILLED" << endl;
                                    return 1;    
                                }
                            } else {
                                cout << "Attempted to match sell order " << newOrder->id << " with buy order " << tmp->id << " but failed" << endl;
                            }
                        } else {
                            tmp->qty -= newOrder->qty;
                            cout << "NEW ORDER FILLED" << endl;
                            return 1;
                        }
                    } else {
                        break;
                    }
                    tmp = tmp->next;
                }
            }

            return fillStatus;
        }
        
    public:
        Orderbook() {
            bidsHead = NULL;
            asksHead = NULL;
            bidId = 1;
            askId = 1;
        }

        void printOrderbook() {
            /// @brief Method will print out the current orderbook

            order *tmp;
            tmp = bidsHead;
            cout << "Bids:" << endl;
            while (tmp != NULL) {
                cout << "Id: " << tmp->id << " Qty: " << tmp->qty << " Price: " << tmp->price << endl;
                tmp = tmp->next;
            }

            tmp = asksHead;
            cout << "Asks:" << endl;
            while (tmp != NULL) {
                cout << "Id: " << tmp->id << " Qty: " << tmp->qty << " Price: " << tmp->price << endl;
                tmp = tmp->next;
            }
        }

        bool removeOrder(int id, string side) {
            /// @brief Method will remove an order from the orderbook
            /// @param id order id
            /// @param side order side
            /// @return true if order successfully removed, false otherwise
            
            order *tmp;
            if (side == "buy") {
                tmp = bidsHead;
                if (id == tmp->id) {
                    bidsHead = bidsHead->next;
                    return true;
                }

                while (tmp->next != NULL) {
                    if (id == tmp->next->id) {
                        tmp->next = tmp->next->next;
                        return true;
                    }
                    tmp = tmp->next;
                }
            } else if (side == "sell") {
                tmp = asksHead;
                if (id == tmp->id) {
                    asksHead = asksHead->next;
                    return true;
                }

                while (tmp->next != NULL) {
                    if (id == tmp->next->id) {
                        tmp->next = tmp->next->next;
                        return true;
                    }
                    tmp = tmp->next;
                }
            }

            return false;
        }

        int addOrder(string side, int qty, float price)
        {
            /// @brief Method will add a new order to the orderbook
            /// @param side order side
            /// @param qty order quantity
            /// @param price order limit price
            /// @return 0 if immediate fill, order id otherwise

            order *newOrder = new order;
            newOrder->next = NULL;
            newOrder->qty = qty;
            newOrder->price = price;

            if (lookForMatch(newOrder, side) == 1) {
                return 0;
            }

            if (side == "buy") {
                newOrder->id = bidId;
                bidId += 1;

                if(bidsHead == NULL) {
                    bidsHead = newOrder;
                } else if (newOrder-> price > bidsHead->price) {
                    newOrder->next = bidsHead;
                    bidsHead = newOrder;
                } else if (bidsHead->next == NULL) {
                    bidsHead->next = newOrder;
                } else {
                    order *tmp = bidsHead;
                    while (tmp->next != NULL) {
                        if (newOrder->price > tmp->next->price) {
                            newOrder->next = tmp->next;
                            tmp->next = newOrder;
                            break;
                        } else if (tmp->next->next == NULL) {
                            tmp->next->next = newOrder;
                            break;
                        }
                        tmp = tmp->next;
                    }
                }
            } else if (side == "sell") {
                newOrder->id = askId;
                askId += 1;

                if(asksHead == NULL) {
                    asksHead = newOrder;
                } else if (newOrder-> price < asksHead->price) {
                    newOrder->next = asksHead;
                    asksHead = newOrder;
                } else if (asksHead->next == NULL) {
                    asksHead->next = newOrder;
                } else {
                    order *tmp = asksHead;
                    while (tmp->next != NULL) {
                        if (newOrder->price < tmp->next->price) {
                            newOrder->next = tmp->next;
                            tmp->next = newOrder;
                            break;
                        } else if (tmp->next->next == NULL) {
                            tmp->next->next = newOrder;
                            break;
                        }
                        tmp = tmp->next;
                    }
                }
            }
            
            return newOrder->id;
        }
};