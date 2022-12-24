#include <iostream>
#include "OrderInputProcessor.cpp"
#include "Orderbook.cpp"

using namespace std;

int main() {
    OrderInputProcessor orderInputProcessor;
    Orderbook orderbook;

    for (string line; getline(cin, line);)
    {
        string command;
        int id;
        string side;
        int qty;
        float price;

        if (orderInputProcessor.process(line, &command, &id, &side, &qty, &price)) {
            if (command == "place") {
                id = orderbook.addOrder(side, qty, price);
            } else if (command == "cancel") {
                orderbook.cancelOrder(id, side);
            } else if (command == "print") {
                orderbook.printOrderbook();
            }
        };
    }

    return 0;
}