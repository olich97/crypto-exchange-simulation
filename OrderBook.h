#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook 
{
    public:
        /**
        * Construct, reading a csv data file
        *
        * @param filename 
        */
        OrderBook(std::string filename);
        /**
        * Get the list of known products.
        * 
        * @return std::vector<std::string> 
        */
        std::vector<std::string> getKnownProducts();

         /**
        * Retrieves the earliest timestamp in the OrderBook.
        *
        * @return the earliest timestamp
        */
        std::string getEarliestTime();

        /**
        * Inserts an order into the order book and sorts the orders by timestamp.
        *
        * @param order The order to be inserted into the order book.
        */
        void insertOrder(OrderBookEntry& order);

        /**
        * Matches asks to bids in the order book for a specific product and timestamp.
        *
        * @param product the product to match asks and bids for
        * @param timestamp the timestamp to match asks and bids for
        *
        * @return a vector of order book entries representing the sales
        */
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        /**
        * Retrieves the next time based on the given timestamp in then OrderBook
        * If there is no next timestamp, wraps around to the start
        * 
        * @param timestamp the input timestamp
        *
        * @return the next time
        */
        std::string getNextTime(std::string timestamp);

        /**
        * Retrieves a list of orders based on the specified criteria.
        * 
        * @param type The type of order book to retrieve from.
        * @param product The specific product to retrieve orders for.
        * @param timestamp The timestamp at which the orders were placed.
        * @return A vector of OrderBookEntry objects that match the specified criteria.
        */
        std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                              std::string product, 
                                              std::string timestamp);
        
        /**
         * Get the highest price from the given list of order book entries.
         *
         * @param orders The list of order book entries
         *
         * @return The highest price
         */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        
        /**
         * Returns the lowest price from the given list of order book entries.
         *
         * @param orders the list of order book entries
         *
         * @return the lowest price
         */
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

        /**
        * Calculate the total volume of orders in given list of order book entries.
        *
        * @param orders the vector of OrderBookEntry objects
        *
        * @return the total volume
        */
        static double getTotalVolume(std::vector<OrderBookEntry>& orders);
    

    private:
        std::vector<OrderBookEntry> orders;

};