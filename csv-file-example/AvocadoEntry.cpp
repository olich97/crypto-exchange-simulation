#include "AvocadoEntry.h"

AvocadoEntry::AvocadoEntry(std::string _date, 
                           double _averagePrice, 
                           AvocadoType type, 
                           std::string _year, 
                           std::string _region, 
                           double _totalVolume)
    : date(_date), 
      averagePrice(_averagePrice), 
      type(type), 
      year(_year), 
      region(_region), 
      totalVolume(_totalVolume) {}