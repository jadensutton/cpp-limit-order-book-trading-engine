#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "sstream"

using namespace std;

class OrderInputProcessor {
    private:
        void rejectOrder(string outputMessage) {
            /// @brief Method will output an order rejection message
            /// @param outputMessage output message

            cout << "ORDER REJECTED - " << outputMessage << endl;
        }

    public:
        bool process(string inputLine, string *side, int *qty, float *price) {
            /// @brief Method will extract order parameters from a string input line
            /// @param inputLine user input
            /// @param side order side
            /// @param qty order qty
            /// @param price order price
            /// @return true if for valid order parameters, false otherwise


            vector <string> tokens;
            
            stringstream check1(inputLine);
            
            string intermediate;
            
            while(getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }

            if (tokens.size() == 3) {
                if (tokens[0] != "buy" && tokens[0] != "sell") {
                    rejectOrder("Side must be 'buy' or 'sell'");
                    return false;
                }

                *side = tokens[0];
                *qty = stoi(tokens[1]);
                *price = stof(tokens[2]);

                return true;
            }

            
            return false;
        }
};