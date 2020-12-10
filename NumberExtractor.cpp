#include "NumberExtractor.h"
NumberExtractor::NumberExtractor(std::string astr_WordSeq, int startIndexExtractionAfter)
{
    indexOfListNumberExtracted = 0;
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
    conv["nineteen"] = 19;

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
    std::string stringSeq;
    bool recordString = true;
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
                stringSeq = stringSeq + " " + word;
                continue;
            }
            if (!hasEndTy)
            {
                numsExtracted.push_back(number);
            }
            hasEndTy = false;

            stringSeq = stringSeq + " " + word;
            recordString = true;
        }
        else
        {
            numsExtracted.push_back(404);
            recordString = false;
        }
        if (!recordString && stringSeq != "")
        {
            stringSeq = trim(stringSeq);
            // std::cout << "stringSeq #" << stringSeq << "#" << std::endl;
            listOfNumberStringExtracted.push_back(stringSeq);
            stringSeq = "";
        }
    }

    if (stringSeq != "")
    {
        stringSeq = trim(stringSeq);
        // std::cout << "stringSeq #" << stringSeq << "#" << std::endl;
        listOfNumberStringExtracted.push_back(stringSeq);
        stringSeq = "";
    }

    int out = 0;
    // bool zeroStartNumber = true;
    bool afterThousand = false;
    std::string result = "";
    for (int i = 0; i < numsExtracted.size(); i++)
    {
        out = numsExtracted[i];
        // if (out == 0 && zeroStartNumber)
        // {
        //     continue;
        // }
        if (out != 404)
        {
            // zeroStartNumber = false;
            switch (out)
            {
            case 0:
                if (afterThousand)
                {
                    afterThousand = false;
                    break;
                }
                // if (!zeroStartNumber)
                if (result != "")
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
                afterThousand = true;
                // if (i < numsExtracted.size() - 2)
                // {
                //     if (numsExtracted[i + 1] != 404 && numsExtracted[i + 2] != 404)
                //     {
                //         result = result + "0";
                //         break;
                //     }
                //     if (numsExtracted[i + 1] != 404)
                //     {
                //         result = result + "00";
                //         break;
                //     }
                // }
                result = result + "000";
                break;
            case 222:
                result = result + ",";
                break;
            default:
                if (i < numsExtracted.size() - 1)
                {
                    if (result != "" && numsExtracted[i + 1] == 404)
                    {
                        if (result.back() == '0')
                        {
                            result.erase(result.length() - 1, 1);
                        }
                    }
                }
                if (result != "" && numsExtracted[i] != 404 && i == numsExtracted.size() - 1 && numsExtracted[i - 1] != 0)
                {
                    if (result.back() == '0')
                    {
                        result.erase(result.length() - 1, 1);
                    }
                }

                // for special case
                if (i > 1)
                {
                    if (numsExtracted[i - 1] == 0 and numsExtracted[i - 2] == 1000)
                    {
                        if (i == numsExtracted.size() - 1)
                        {
                            result.erase(result.length() - 1, 1);
                        }
                        if (i == numsExtracted.size() - 2)
                        {
                            result.erase(result.length() - 2, 2);
                        }
                    }
                }

                result = result + std::to_string(numsExtracted[i]);
                break;
            }
        }
        // if meet unknown
        if (out == 404 || i == numsExtracted.size() - 1)
        {
            if (result != "")
            {
                // std::cout << "result #" << result << "#" << std::endl;
                listOfNumberExtracted.push_back(result);
            }
            result = "";
            // zeroStartNumber = true;
            afterThousand = false;
        }
    }
};

NumberExtractor::NumberExtractor(const std::vector<std::string> &ar_allWordAsString,
                                 int startIndexExtractionAfter)
{
    indexOfListNumberExtracted = 0;
    for (int i = 0; i < ar_allWordAsString.size(); i++)
    {
        NumberExtractor temp(ar_allWordAsString[i]);
        for (int f = 0; f < temp.getListOfNumberExtracted().size(); f++)
        {
            listOfNumberExtracted.push_back(temp.getListOfNumberExtracted()[f]);
            listOfNumberStringExtracted.push_back(temp.getListOfNumberStringExtracted()[f]);
        }
        listOfVectorStringExtractedNumber.push_back(temp.getListOfNumberExtracted());
        listOfVectorStringExtractedString.push_back(temp.getListOfNumberStringExtracted());
    }
};

std::vector<std::string> NumberExtractor::getListOfNumberExtracted() const
{
    return listOfNumberExtracted;
};

std::vector<std::string> NumberExtractor::getListOfNumberStringExtracted() const
{
    return listOfNumberStringExtracted;
};

std::vector<std::vector<std::string>> NumberExtractor::getListOfVectorStringExtractedNumber() const
{
    return listOfVectorStringExtractedNumber;
};

std::vector<std::vector<std::string>> NumberExtractor::getListOfVectorStringExtractedString() const
{
    return listOfVectorStringExtractedString;
};
;

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

bool NumberExtractor::PerformFullExtraction()
{

    try
    {
        std::string numberBeforeDecStr = "";
        std::string numberAfterDecStr = "";
        for (int i = 0; i < listOfNumberExtracted.size(); i++)
        {
            if (listOfNumberExtracted[i].find(",") != -1)
            {
                // have number after decimal
                numberBeforeDecStr = listOfNumberExtracted[i]
                                         .substr(0, listOfNumberExtracted[i].find(","));
                numberAfterDecStr = listOfNumberExtracted[i]
                                        .substr(listOfNumberExtracted[i].find(",") + 1,
                                                listOfNumberExtracted[indexOfListNumberExtracted].length());
                NumberExtractor::ExtractedNumber output = ExtractedNumber(listOfNumberStringExtracted[i],
                                                                          std::stoi(numberBeforeDecStr), std::stoi(numberAfterDecStr));

                m_extractedNumberSeq.push_back(output);
            }
            else
            {
                NumberExtractor::ExtractedNumber output = ExtractedNumber(listOfNumberStringExtracted[i],
                                                                          std::stoi(listOfNumberExtracted[i]), -1);
                m_extractedNumberSeq.push_back(output);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
};

NumberExtractor::ExtractedNumber NumberExtractor::ExtractNextFullNumber()
{
    if (indexOfListNumberExtracted >= listOfNumberExtracted.size())
    {
        NumberExtractor::ExtractedNumber output = ExtractedNumber("", -1, -1);
        return output;
    }
    std::string numberBeforeDecStr = "";
    std::string numberAfterDecStr = "";

    if (listOfNumberExtracted[indexOfListNumberExtracted].find(",") != -1)
    {
        // have number after decimal
        numberBeforeDecStr = listOfNumberExtracted[indexOfListNumberExtracted]
                                 .substr(0, listOfNumberExtracted[indexOfListNumberExtracted].find(","));
        numberAfterDecStr = listOfNumberExtracted[indexOfListNumberExtracted]
                                .substr(listOfNumberExtracted[indexOfListNumberExtracted].find(",") + 1,
                                        listOfNumberExtracted[indexOfListNumberExtracted].length());
        NumberExtractor::ExtractedNumber output = ExtractedNumber(listOfNumberStringExtracted[indexOfListNumberExtracted],
                                                                  std::stoi(numberBeforeDecStr), std::stoi(numberAfterDecStr));
        indexOfListNumberExtracted++;
        return output;
    }
    NumberExtractor::ExtractedNumber output = ExtractedNumber(listOfNumberStringExtracted[indexOfListNumberExtracted],
                                                              std::stoi(listOfNumberExtracted[indexOfListNumberExtracted]), -1);

    indexOfListNumberExtracted++;
    return output;
};

std::string NumberExtractor::ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string NumberExtractor::rtrim(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace)))
                .base(),
            s.end());
    return s;
}

std::string NumberExtractor::trim(std::string s)
{
    return ltrim(rtrim(s));
}
