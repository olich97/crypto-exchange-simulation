#pragma once

#include <string>

enum class AvocadoType{conventional, organic};
// https://www.kaggle.com/datasets/neuromusic/avocado-prices
class AvocadoEntry 
{
    public:
        /** Create a new AvocadoEntry with passed parameters */
        AvocadoEntry( std::string _date, 
                      double _averagePrice, 
                      AvocadoType type,
                      std::string _year, 
                      std::string _region, 
                      double _totalVolume );

        std::string date; // the date of the observation
        double averagePrice; // the average price of a single avocado
        AvocadoType type; // conventional or organic
        std::string year; // year in which the avocados were sold
        std::string region; // the city or region of the observation
        double totalVolume; // total number of avocados sold
};