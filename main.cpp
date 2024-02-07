#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "OrderBookEntry.h"
#include "Merkel.h"
#include "CSVReader.h"

int main()
{
    Merkel app{};
    app.init();
    return 0;
}