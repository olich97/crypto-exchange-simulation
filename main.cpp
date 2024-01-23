#include <iostream>
#include <string>
#include "Merkel.h"

/**
 * Computes the average price of the given list of order book entries.
 *
 * @param entries The list of order book entries
 *
 * @return The average price
 *
 * @throws None
 */
double computeAveragePrice(std::vector<OrderBookEntry>& entries) 
{
    if (entries.empty()) {
        return 0;
    }
    double sum = 0;
    for (OrderBookEntry& entry : entries) {
        sum += entry.price;
    }
    return sum / entries.size();
}

/**
 * Computes the lowest price from the given list of order book entries.
 *
 * @param entries the list of order book entries
 *
 * @return the lowest price
 *
 * @throws None
 */
double computeLowPrice(std::vector<OrderBookEntry>& entries) 
{
    double lowPrice = entries[0].price;
    for (OrderBookEntry& entry : entries) {
        if (entry.price < lowPrice) {
            lowPrice = entry.price;
        }
    }
    return lowPrice;
}

/**
 * Computes the highest price from a vector of OrderBookEntry.
 *
 * @param entries the vector of OrderBookEntry
 *
 * @return the highest price
 *
 * @throws None
 */
double computeHighPrice(std::vector<OrderBookEntry>& entries) 
{
    double highPrice = entries[0].price;
    for (OrderBookEntry& entry : entries) {
        if (entry.price > highPrice) {
            highPrice = entry.price;
        }
    }
    return highPrice;
}

/**
 * Computes the price spread of the given vector of order book entries.
 *
 * @param entries the vector of order book entries
 *
 * @return the price spread
 */
double computePriceSpread(std::vector<OrderBookEntry>& entries) 
{
    double maxPrice = computeHighPrice(entries);
    double minPrice = computeLowPrice(entries);
    return maxPrice - minPrice;
}

int main()
{
    std::vector<OrderBookEntry> entries;
    entries.push_back(OrderBookEntry(1000, 0.9, "2020/03/17 17:01:24.884492", "BTC/USD", OrderBookType::bid));
    entries.push_back(OrderBookEntry(2000, 0.7, "2020/03/17 17:01:23.884492", "BTC/USD", OrderBookType::ask));
    entries.push_back(OrderBookEntry(1100, 0.4, "2020/03/17 17:01:24.884492", "BTC/USD", OrderBookType::bid));

    for (unsigned int i = 0; i < entries.size(); ++i)
    {
        std::string orderTypeStr = (entries[i].orderType == OrderBookType::bid) ? "bid" : "ask";
        std::cout << "Data of the entry number " << i << " is: " 
        << " price: " << entries[i].price  
        << ", amount: " << entries[i].amount 
        << ", product: " << entries[i].product 
        << ", orderType: " << orderTypeStr
        << std::endl;
    }

    std::cout << "Avarage price of given entries is: " << computeAveragePrice(entries) << std::endl;
    std::cout << "Hightest price of given entries is: " << computeHighPrice(entries) << std::endl;
    std::cout << "Lowest price of given entries is: " << computeLowPrice(entries) << std::endl;
    std::cout << "Price spread of given entries is: " << computePriceSpread(entries) << std::endl;

    Merkel app{};
    app.init();

    return 0;
}