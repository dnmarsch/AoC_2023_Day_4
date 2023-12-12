#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>


class Scratchcard
{
public:
    Scratchcard()
    {}
    void calcSumWinningPoints();
    unsigned long int getSumWinningPoints() const {
        return sumWinningPoints;
    }

private:
    void readInput();
    unsigned long int sumWinningPoints = 0;
    int gameNum = 0;
    int numWinningNums = 10;
    // int numWinningNums = 5;
    std::vector<int> winningNums= {};
    std::map<int,int> cardNums = {};
    std::ifstream inputFile{"input.txt"};
    // std::ifstream inputFile{"test.txt"};
};

void Scratchcard::calcSumWinningPoints()
{
    readInput();
}

/**
 * @brief Read all lines of input from file
 * 
 */
void Scratchcard::readInput()
{
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << "\n";
        //reset gameNum to be grabbed
        gameNum = 0;
        /* erase all entries for vector & map for next line */
        cardNums.clear();
        winningNums.clear();
        int num;
        char separator;
        std::stringstream ss(line);

        while(ss >> num || !ss.eof())
        {
            if (ss.fail())
            {
                ss.clear(); // clear the fail bit
                ss >> separator; // read the separator '|'
                continue;
            }
            if(gameNum == 0)
            { 
                gameNum = num;
            }
            /* store all winning numbers in vector to compare with scratchcard numbers */
            else if(winningNums.size() < numWinningNums)
            {
                std::cout << "winning number: " << num << "\n";
                winningNums.push_back(num);
            }
            else
            {
                std::cout << "scratchcard number: " << num << "\n";
                cardNums[num] = num; //store this round's scratchcard numbers
            }
        }
        /* print out map each line */
        for(auto entry : cardNums)
        {
            std::cout << "entry: " << entry.first << "\n";
        }

        // check for winning numbers and keep track of total winning points
        int winningPoints = 0;
        for(auto winningNum : winningNums)
        {
            if(cardNums.count(winningNum) > 0) // We have a winning number!
            {
                if(winningPoints == 0) winningPoints = 1;
                else winningPoints *= 2;
            }
        }
        sumWinningPoints += winningPoints; //add round's winning points to total
    }
}

int main() {
    Scratchcard scratchcards;

    scratchcards.calcSumWinningPoints();

    auto sumWinningPoints = scratchcards.getSumWinningPoints();
    std::cout << "FINAL VALUE: " << sumWinningPoints;

    return 0;
}