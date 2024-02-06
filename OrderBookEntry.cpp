
#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry( double _price, 
                                double _amount, 
                                std::string _timestamp, 
                                std::string _product, 
                                OrderBookType _orderType )
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp), 
  product(_product), 
  orderType(_orderType) {}


  
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) 
{
  if (s == "bid") return OrderBookType::bid;
  else if (s == "ask")  return OrderBookType::ask;
  else return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(const OrderBookEntry& o1, const OrderBookEntry& o2) 
{
  return o1.timestamp < o2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(const OrderBookEntry& o1, const OrderBookEntry& o2) 
{
  return o1.price < o2.price;
}

bool OrderBookEntry::compareByPriceDesc(const OrderBookEntry& o1, const OrderBookEntry& o2) 
{
  return o1.price > o2.price;
}