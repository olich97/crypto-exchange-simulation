#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class Merkel 
{
    public:
        Merkel();
        void init();
    private:
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotToNextTimeFrame();
        void processUserOption(int userOption);
        int getUserOption();

        std::string currentTime;

        OrderBook orderBook{"test.csv"};
};