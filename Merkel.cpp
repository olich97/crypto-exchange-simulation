
#include "Merkel.h"
#include <iostream>
#include "CSVReader.h"

Merkel::Merkel() 
{
}

void Merkel::init() 
{
    loadOrderBook();
    int input;
    while(true) 
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void Merkel::loadOrderBook() 
{
    orders = CSVReader::readCSV("order_book_data.csv");
}

void Merkel::printMenu() 
{
    // 1. Print help -> instruction for the app
    std::cout << "1: Print help" << std::endl;
    // 2. Print exchange stats -> current internal statistics like offers, bids etc.
    std::cout << "2: Print exchange stats" << std::endl;
    // 3. Make an offer -> what I've got to sell
    std::cout << "3: Make an offer" << std::endl;
    // 4. Make a bid -> what I would like to buy
    std::cout << "4: Make a bid" << std::endl;
    // 5. Print wallet -> current balance of my assets
    std::cout << "5: Print wallet" << std::endl;
    // 6. Continue -> got to next time step
    std::cout << "6: Continue" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "Type in 1-6: " << std::endl;
}

void Merkel::printHelp() 
{
    std::cout << "Help - your aim is to make big money. Analyse the market and make bids and offers!" << std::endl;
    std::cout << std::endl;
}

void Merkel::printMarketStats() 
{
    std::cout << "OrderBook contains: " << orders.size() << " entries" << std::endl;
    unsigned int bids = 0;
    unsigned int asks = 0;
    for(const OrderBookEntry& o : orders) 
    {
        if (o.orderType == OrderBookType::ask) asks++;
        if (o.orderType == OrderBookType::bid) bids++;
    }
    std::cout << "OrderBook asks: " << asks << ", bids " << bids << std::endl;
    std::cout << std::endl;
}

void Merkel::enterOffer() 
{
    std::cout << "Make an offer - enter the amount" << std::endl;
    std::cout << std::endl;
}

void Merkel::enterBid() 
{
    std::cout << "Make a bid - enter the amount" << std::endl;
    std::cout << std::endl;
}

void Merkel::printWallet() 
{
    std::cout << "Your wallet is empty!" << std::endl;
    std::cout << std::endl;
}

void Merkel::gotToNextTimeFrame() 
{
    std::cout << "Going to next time frame..." << std::endl;
     std::cout << std::endl;
}

void Merkel::processUserOption(int userOption) 
{
    switch (userOption)
    {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterOffer();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotToNextTimeFrame();
            break;
        default:
            std::cout << "Invalid choice. Choose 1-6!" << std::endl;
            std::cout << std::endl;
            break;
    }
}


int Merkel::getUserOption() 
{
    // getting user input
    int userOption;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}
