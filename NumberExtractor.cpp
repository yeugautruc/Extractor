#include "NumberExtractor.h"
#include <iostream>
#include <sstream>
#include "map"
NumberExtractor::NumberExtractor(std::string astr_WordSeq, int startIndexExtractionAfter)
{
    std::map<std::string, int> conv;
    conv["zero"] = 0;
    conv["decimal"] = 222;
    conv["point"] = 222;

    conv["one"] = 1;
    conv["two"] = 2;
    conv["three"] = 3;
    conv["four"] = 4;
    conv["five"] = 5;
    conv["six"] = 6;
    conv["seven"] = 7;
    conv["eight"] = 8;
    conv["nine"] = 9;
    conv["ten"] = 101;

    conv["eleven"] = 11;
    conv["twelve"] = 12;
    conv["thirteen"] = 13;
    conv["fourteen"] = 14;
    conv["fifteen"] = 15;
    conv["sixteen"] = 16;
    conv["seventeen"] = 17;
    conv["eighteen"] = 18;
    conv["ninteen"] = 19;

    conv["thousand"] = 1000;
    conv["hundred"] = 100;

    conv["twenty"] = 20;
    conv["thirty"] = 30;
    conv["forty"] = 40;
    conv["fifty"] = 50;
    conv["sixty"] = 60;
    conv["seventy"] = 70;
    conv["eighty"] = 80;
    conv["ninety"] = 90;

    std::vector<int> numsExtracted;
    std::istringstream iss(astr_WordSeq);
    std::string word;
    int number;
    while (iss >> word)
    {
        bool hasEndTy = false;
        if (IfWordIsNumber(conv, word))
        {
            number = conv[word];
            if (EndsWith(word, "ty"))
            {
                numsExtracted.push_back(number / 10);
                numsExtracted.push_back(10);
                hasEndTy = true;
                continue;
            }
            if (!hasEndTy)
            {
                numsExtracted.push_back(number);
            }
            hasEndTy = false;
        }
        else
        {
            numsExtracted.push_back(404);
        }
    }
    int out = 0;
    // for (int i = 0; i < numsExtracted.size(); i++)
    // {
    //     std::cout << numsExtracted[i] << " ;";
    // }
    bool zeroStartNumber = true;
    std::string result = "";
    for (int i = 0; i < numsExtracted.size(); i++)
    {
        out = numsExtracted[i];
        if (out == 0 && zeroStartNumber)
        {
            continue;
        }
        if (out != 404)
        {
            zeroStartNumber = false;

            switch (out)
            {
            case 0:
                if (!zeroStartNumber)
                {
                    result = result + "0";
                }
                break;
            case 10:
                if (result.length() > 3)
                {
                    if (result.substr(result.length() - 3, 2) == "00")
                    {
                        result.erase(result.length() - 3, 2);
                    }
                }
                result = result + "0";
                break;
            case 100:
                if (result.length() > 4)
                {
                    if (result.substr(result.length() - 4, 3) == "000")
                    {
                        result.erase(result.length() - 4, 3);
                    }
                }
                result = result + "00";
                break;
            case 101:
                result = result + "10";
                break;
            case 1000:
                result = result + "000";
                break;
            case 222:
                result = result + ",";
                break;
            default:
                if (result != "" && numsExtracted[i + 1] == 404)
                {
                    if (result.back() == '0')
                    {
                        result.erase(result.length() - 1, 1);
                    }
                }
                result = result + std::to_string(numsExtracted[i]);
                break;
            }
        }
        if (out == 404 || i == numsExtracted.size() - 1)
        {
            listOfNumberExtracted.push_back(result);
            result = "";
            zeroStartNumber = true;
        }
    }
};

// NumberExtractor::NumberExtractor(const std::vector<std::string> &ar_allWordAsString,
//                                  int startIndexExtractionAfter){

// };

std::vector<std::string> NumberExtractor::getListOfNumberExtracted() const
{
    return listOfNumberExtracted;
};

bool NumberExtractor::IfWordIsNumber(std::map<std::string, int> m, std::string word)
{
    std::map<std::string, int>::iterator it = m.find(word);
    if (it != m.end())
    {
        return true;
    }
    return false;
};

bool NumberExtractor::EndsWith(const std::string &mainStr, const std::string &toMatch)
{
    if (mainStr.size() >= toMatch.size() &&
        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        return true;
    else
        return false;
}