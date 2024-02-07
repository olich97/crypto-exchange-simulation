#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
    public:
        Wallet();

        /**
        * Insert a specified amount of a currency into the wallet.
        *
        * @param currency the type of currency to insert
        * @param amount the amount of currency to insert
        *
        * @return void
        * 
        * @throws std::exception if the amount is less than 0
        */
        void insertCurrency(std::string currency, double amount);

        /**
        * Removes the specified amount of the given currency from the wallet.
        *
        * @param currency the currency to be removed
        * @param amount the amount to be removed
        *
        * @return true if the currency was successfully removed, false otherwise
        *
        * @throws std::exception if the amount is less than 0
        */
        bool removeCurrency(std::string currency, double amount);

        /**
        * Check if the wallet contains the specified currency with the given amount.
        *
        * @param currency the currency to check for
        * @param amount the amount of the currency
        *
        * @return true if the wallet contains the specified currency with the given amount, false otherwise
        */
        bool containsCurrency(std::string currency, double amount);

        /**
         * Converts the Wallet object to a string representation.
         *
         * @return the string representation of the Wallet
         */
        std::string toString();

        /**
        * Check if the wallet can fulfill the given order.
        *
        * @param order The order to be checked
        *
        * @return True if the wallet can fulfill the order, false otherwise
        */
        bool canFullfillOrder(OrderBookEntry order);

        void processSale(OrderBookEntry& sale);

    private:
        std::map<std::string, double> currencies;
};