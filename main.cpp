#include <iostream>
#include "OrderInputProcessor.cpp"
#include "Orderbook.cpp"

using namespace std;

int main() {
    OrderInputProcessor orderInputProcessor;
    Orderbook orderbook;

    for (string line; getline(cin, line);)
    {
        string side;
        int qty;
        float price;

        if (line == "print") {
            orderbook.printOrderbook();
        } else if (orderInputProcessor.process(line, &side, &qty, &price)) {
            int id;
            id = orderbook.addOrder(side, qty, price);
            if (id != 0) {
                cout << "Order placed - Id = " << id << endl;
            }
        };
    }

    return 0;
}