#pragma once

#include <string>

enum class OrderBookType{bid, ask, sale, unknown, asksale, bidsale};

class OrderBookEntry 
{
    public:
        /** Create a new OrderBookEntry with passed parameters */
        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType,
                        std::string username = "dataset");

        static OrderBookType stringToOrderBookType(std::string s);

        static bool compareByTimestamp(const OrderBookEntry& o1, const OrderBookEntry& o2);
        static bool compareByPriceAsc(const OrderBookEntry& o1, const OrderBookEntry& o2);
        static bool compareByPriceDesc(const OrderBookEntry& o1, const OrderBookEntry& o2);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};