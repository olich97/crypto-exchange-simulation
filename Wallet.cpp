
#include "Wallet.h"
#include "CSVReader.h"
#include <vector>
#include <iostream>

Wallet::Wallet() 
{
};

void Wallet::insertCurrency(std::string currency, double amount)
{
    double balance;

    if (amount < 0) 
        throw std::exception{};

    if (currencies.count(currency) == 0) 
        balance = 0;
    else 
        balance = currencies[currency];
    
    balance += amount;
    currencies[currency] = balance;
}

bool Wallet::removeCurrency(std::string currency, double amount) 
{
    double balance;

    if (amount < 0) 
        throw std::exception{};

    if (currencies.count(currency) == 0)
        return false;
    else {
        // check if there is enough balance
        if(containsCurrency(currency, amount)) 
        {
            currencies[currency] -= amount;
            return true;
        } 
        else 
            return false;
    }
}

bool Wallet::containsCurrency(std::string currency, double amount)
{
    if (currencies.count(currency) == 0) 
        return false;
    else 
        return currencies[currency] >= amount;
}

std::string Wallet::toString()
{
    std::string result;
    for (std::pair<std::string, double> pair : currencies) 
    {
        std::string currency = pair.first;
        double amount = pair.second;
        result += currency + ": " + std::to_string(amount) + "\n";
    }
    return result;
}

bool Wallet::canFullfillOrder(OrderBookEntry order) 
{
    std::vector<std::string> cur = CSVReader::tokenise(order.product, '/');

    if (order.orderType == OrderBookType::ask) 
    {
        double amount = order.amount;
        std::string currency = cur[0];
        std::cout << "Wallet::canFullfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }

    if (order.orderType == OrderBookType::bid) 
    {
        double amount = order.amount * order.price;
        std::string currency = cur[1];
        std::cout << "Wallet::canFullfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }

    return false;
}

void Wallet::processSale(OrderBookEntry& sale)
{
    std::vector<std::string> cur = CSVReader::tokenise(sale.product, '/');

    if (sale.orderType == OrderBookType::asksale) 
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = cur[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = cur[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }

    if (sale.orderType == OrderBookType::bidsale) 
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = cur[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = cur[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}