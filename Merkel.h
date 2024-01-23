#include <vector>
#include "OrderBookEntry.h"

class Merkel 
{
    public:
        Merkel();
        void init();    
    private:
        void loadOrderBook();
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterOffer();
        void enterBid();
        void printWallet();
        void gotToNextTimeFrame();
        void processUserOption(int userOption);
        int getUserOption();

         std::vector<OrderBookEntry> orders;
};