#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "AvocadoEntry.h"

/**
 * Tokenizes a CSV line using the specified separator.
 *
 * @param csvLine The CSV line to tokenize
 * @param separator The character used to separate the tokens
 *
 * @return A vector of strings containing the tokens
 *
 * @throws None
 */
std::vector<std::string> tokenise(std::string csvLine, char separator) 
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        
        tokens.push_back(csvLine.substr(start, end - start));
        start = end + 1;
    } while (end != std::string::npos);
    return tokens;
}
int main()
{
    std::ifstream csvFile{"avocado.csv"};
    std::string line;
    std::vector<AvocadoEntry> entries;

    if (csvFile.is_open()) 
    {
        int validLines = 0;
        int totalLinesProcessed = 0;
        int totalErrors = 0;
        while(std::getline(csvFile, line)) 
        {
            totalLinesProcessed++;
            std::vector<std::string> tokens = tokenise(line, ',');

            // the file contains 14 coloumns in total, but we using only 6 for simplicity
            if (tokens.size() != 14)
            {
                std::cout << "Invalid line: " << line << std::endl;
                totalErrors++;
                continue;
            }

            try {
                std::string date = tokens[1];
                std::string year = tokens[12];
                std::string region = tokens[13];
                double averagePrice = std::stod(tokens[2]);
                double totalVolume = std::stod(tokens[3]);
                // checking AvocadoType enum
                AvocadoType type;
                if (tokens[11] == "conventional") type = AvocadoType::conventional;
                else if (tokens[11] == "organic")  type = AvocadoType::organic;
                else throw std::invalid_argument("Invalid AvocadoType, must be conventional or organic");
                entries.push_back(AvocadoEntry{
                    date, averagePrice, type, year, region, totalVolume
                });
                validLines++;
            } 
            catch (const std::exception& e) {
                std::cout << "Error processing line (exception found): " << line << std::endl;
                std::cout << e.what() << std::endl;
                totalErrors++;
                continue;
            }
        }
        csvFile.close();

        std::cout << "-------------------------------------- " << std::endl;
        std::cout << "Total processed lines: " << totalLinesProcessed << std::endl;
        std::cout << "Number of valid lines: " << validLines << std::endl;
        std::cout << "Number of errors: " << totalErrors << std::endl;
    }
    else 
    {
        std::cout << "Cannot open the file " << std::endl;
    }

    return 0;
}