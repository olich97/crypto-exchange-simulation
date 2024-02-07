#include "OrderBook.h"
#include "CSVReader.h"
#include <map>


OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() 
{
    std::vector<std::string> products;
    std::map<std::string, bool> productMap;
    for (const OrderBookEntry& order : orders) 
    {
        productMap[order.product] = true;
    }
    // now flatten the map to a vector of strings
    for (auto const& product : productMap) 
    {
        products.push_back(product.first);
    }
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                std::string product, 
                                                std::string timestamp)
{
    std::vector<OrderBookEntry> result;
    for (OrderBookEntry& order : orders) 
    {
        if (order.orderType == type && order.product == product && order.timestamp == timestamp) 
        {
            result.push_back(order);
        }
    }
    return result;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) 
{
    double max = orders[0].price;
    for (OrderBookEntry& order : orders) 
    {
        if (order.price > max) max = order.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) 
{
    double min = orders[0].price;
    for (OrderBookEntry& order : orders) 
    {
        if (order.price < min) min = order.price;
    }
    return min;
}

double OrderBook::getTotalVolume(std::vector<OrderBookEntry>& orders) 
{
    double totalVolume = 0.0;
    for(const OrderBookEntry& order : orders) {
        totalVolume += order.amount;
    }
    return totalVolume;
}


std::string OrderBook::getEarliestTime() 
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp) 
{
    std::string nextTimestamp;
    for (const OrderBookEntry& order : orders) 
    {
        if (order.timestamp > timestamp) 
        {
            nextTimestamp = order.timestamp;
            break;
        }
    }
    if (nextTimestamp == "") 
    {
        nextTimestamp = orders[0].timestamp;
    }
    return nextTimestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> sales;
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc); // sort asks lowest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc); // sort bids highest first
    
    for (OrderBookEntry& ask : asks) 
    {
        for (OrderBookEntry& bid : bids) 
        {
            if (bid.price >= ask.price) 
            { // we have a match
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};
                if (bid.username == "simuser") 
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if (ask.username == "simuser") 
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }
                // now we work out how much was sold
                // create new bids and asks covering
                // anything that was not sold
                if (bid.amount == ask.amount) 
                { // bid completely clears ask
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0; // make sure the bid is not processed again
                    break; // can do no more with this ask, go onto the next ask
                }
                if (bid.amount > ask.amount) 
                { // ask is completely gone, slice the bid
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount; // adjust the bid in place
                    ask.amount = 0; // ask is completely gone, go to next ask
                    break;
                }
                if (bid.amount < ask.amount && bid.amount > 0) 
                { // bid is completely gone, slice the ask
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= bid.amount; // update the ask
                    bid.amount = 0; // make sure the bid is not processed again
                    continue; // some ask remains, go to the next bid
                }
            }
        }
    }
    return sales;
}