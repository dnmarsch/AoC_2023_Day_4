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
    void getNumberScratchCards(std::string line);
    int numLines = 0;
    unsigned long int sumWinningPoints = 0;
    int gameNum = 0;
    int numWinningNums = 10;
    // int numWinningNums = 5; //for test.txt (could instead count #s until reaching |, but no need since same width every time)
    std::vector<int> winningNums= {};
    std::map<int,int> cardNums = {};
    std::ifstream inputFile{"input.txt"};
    // std::ifstream inputFile{"test.txt"};
    std::vector<std::string> scratchCards = {};
    std::map<int,int> numCards = {};
};

void Scratchcard::getNumberScratchCards(std::string line)
{
    // std::cout << line << "\n";

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
            // std::cout << "winning number: " << num << "\n";
            winningNums.push_back(num);
        }
        else
        {
            // std::cout << "scratchcard number: " << num << "\n";
            cardNums[num] = num; //store this round's scratchcard numbers
        }
    }
    // /* print out map each line */
    // for(auto entry : cardNums)
    // {
    //     std::cout << "entry: " << entry.first << "\n";
    // }

    // check for winning numbers and keep track of total winning points
    int cardWinningNums = 0;
    // int winningPoints = 0;
    for(auto winningNum : winningNums)
    {
        if(cardNums.count(winningNum) > 0) // We have a winning number!
        {
            // if(winningPoints == 0) winningPoints = 1;
            // else winningPoints *= 2;
            cardWinningNums++;
        }
    }
    // sumWinningPoints += winningPoints; //add round's winning points to total
    
    //for each winning card, increment value of key/card
    int value = numCards[gameNum];
    for(auto i = gameNum+1; i< gameNum+cardWinningNums+1; i++)
    {
        numCards[i] += value;
        // std::cout << "card#: " << i << "card winning nums: " << cardWinningNums << "\tOccurrences: " << numCards[i] << "\n";
    }
}

void Scratchcard::calcSumWinningPoints()
{
    readInput(); //store entire file, line by line, in vector

    //get all originals read & add copies to vector to be process afterwards
    for(auto card : scratchCards)
    {
        getNumberScratchCards(card);
    }

    //sum each value of all keys in map
    for(auto card : numCards)
    {
        sumWinningPoints += card.second;
        std::cout << "card #: " << card.first << " has: " << card.second << "\n";
    }
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
        scratchCards.push_back(line);
        numLines++;
        numCards[numLines]++; //there is 1 original card for each line
    }
    // for(auto card : numCards)
    // {
    //     std::cout << "card#: " << card.first << "\thas: " << card.second << "\n";
    // }
}

int main() {
    Scratchcard scratchcards;

    scratchcards.calcSumWinningPoints();

    auto sumWinningPoints = scratchcards.getSumWinningPoints();
    std::cout << "FINAL VALUE: " << sumWinningPoints;

    return 0;
}