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

        bool isInt(string s) {
            /// @brief Method will check if a string is an integer
            /// @param s string
            /// @return true if integer, false otherwise

            for (int i = 0; i < s.length(); i++) {
                if (!isdigit(s[i])) {
                    return false;
                }
            }

            return true;
        }

        bool isFloat(string s) {
            /// @brief Method will check if a string is a float
            /// @param s string
            /// @return true if integer, false otherwise

            if (s[0] == '.' || s[s.length() - 1] == '.' || count(s.begin(), s.end(), '.') > 1) {
                return false;
            }

            for (int i = 0; i < s.length(); i++) {
                if (!isdigit(s[i]) && s[i] != '.') {
                    return false;
                }
            }

            return true;
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
                } else if (!isInt(tokens[1]) || stoi(tokens[1]) <= 0) {
                    rejectOrder("Quantity must be a whole number and greater than zero");
                    return false;
                } else if (!isFloat(tokens[2]) || stof(tokens[2]) <= 0) {
                    rejectOrder("Price must be numeric and greater than zero");
                    return false;
                }

                *side = tokens[0];
                *qty = stoi(tokens[1]);
                *price = stof(tokens[2]);

                return true;
            }

            rejectOrder("Too few or too many parameters");
            return false;
        }
};