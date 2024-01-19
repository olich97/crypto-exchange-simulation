#include <iostream>


void printMenu() 
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

void printHelp() 
{
    std::cout << "Help - your aim is to make big money. Analyse the market and make bids and offers!" << std::endl;
    std::cout << std::endl;
}

void printMarketStats() 
{
    std::cout << "Market looks godd!" << std::endl;
    std::cout << std::endl;
}

void enterOffer() 
{
    std::cout << "Make an offer - enter the amount" << std::endl;
    std::cout << std::endl;
}

void enterBid() 
{
    std::cout << "Make a bid - enter the amount" << std::endl;
     std::cout << std::endl;
}

void printWallet() 
{
    std::cout << "Your wallet is empty!" << std::endl;
    std::cout << std::endl;
}

void gotToNextTimeFrame() 
{
    std::cout << "Going to next time frame..." << std::endl;
     std::cout << std::endl;
}

void processUserOption(int userOption) 
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


int getUserOption() 
{
    // getting user input
    int userOption;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

int main()
{
    while (true)
    {
        printMenu();
        int option = getUserOption();
        processUserOption(option);
    }

    return 0;
}