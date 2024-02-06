
#include "Merkel.h"
#include <iostream>
#include "CSVReader.h"

Merkel::Merkel() 
{
}

void Merkel::init() 
{
    int input;
    currentTime = orderBook.getEarliestTime();
    while(true) 
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void Merkel::printMenu() 
{
    // 1. Print help -> instruction for the app
    std::cout << "1: Print help" << std::endl;
    // 2. Print exchange stats -> current internal statistics like offers, bids etc.
    std::cout << "2: Print exchange stats" << std::endl;
    // 3. Make an ask -> what I've got to sell
    std::cout << "3: Make an ask" << std::endl;
    // 4. Make a bid -> what I would like to buy
    std::cout << "4: Make a bid" << std::endl;
    // 5. Print wallet -> current balance of my assets
    std::cout << "5: Print wallet" << std::endl;
    // 6. Continue -> got to next time step
    std::cout << "6: Continue" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "========================" << std::endl;
}

void Merkel::printHelp() 
{
    std::cout << "Help - your aim is to make big money. Analyse the market and make bids and offers!" << std::endl;
    std::cout << std::endl;
}

void Merkel::printMarketStats() 
{
    for (const std::string& p : orderBook.getKnownProducts()) 
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << asks.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(asks) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(asks) << std::endl;

        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Bids seen: " << bids.size() << std::endl;
        std::cout << "Max bid: " << OrderBook::getHighPrice(bids) << std::endl;
        std::cout << "Min bid: " << OrderBook::getLowPrice(bids) << std::endl;

    }
}

void Merkel::enterAsk() 
{
    std::cout << "Make an ask - enter the data: product, price, amount (e.g ETH/BTC,100,0.5)" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) 
    {
        std::cout << "Merkel::enterAsk Bad input! " << input  << std::endl;
    } 
    else 
    {
        try 
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], 
                                                     tokens[2], 
                                                     currentTime, 
                                                     tokens[0], 
                                                     OrderBookType::ask);
            orderBook.insertOrder(obe);
        } 
        catch (const std::exception& e) 
        {
            std::cout << "Merkel::enterAsk Bad input! " << input  << std::endl;
        }
        
    }
    std::cout << "You typed: " << input <<std::endl;
}

void Merkel::enterBid() 
{
    std::cout << "Make a bid - enter the data: product, price, amount (e.g ETH/BTC,100,0.5)" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) 
    {
        std::cout << "Merkel::enterBid Bad input! " << input  << std::endl;
    } 
    else 
    {
        try 
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], 
                                                     tokens[2], 
                                                     currentTime, 
                                                     tokens[0], 
                                                     OrderBookType::bid);
            orderBook.insertOrder(obe);
        } 
        catch (const std::exception& e) 
        {
            std::cout << "Merkel::enterBid Bad input! " << input  << std::endl;
        }
        
    }
    std::cout << "You typed: " << input <<std::endl;
}

void Merkel::printWallet() 
{
    std::cout << "Your wallet is empty!" << std::endl;
    std::cout << std::endl;
}

void Merkel::gotToNextTimeFrame() 
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << ", amount: " << sale.amount << std::endl;
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
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
            enterAsk();
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
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6: " << std::endl;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    } 
    catch (const std::exception& e) {
        std::cout << "Merkel::getUserOption Bad input! " << line  << std::endl;
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}
