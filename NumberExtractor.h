#pragma once
#include "string"
#include "vector"
#include "map"
#include "iterator"

class NumberExtractor
{
    // public:
    // class ExtractedNumber
    // {

    // public:
    //     ExtractedNumber(std::string astr_seqOfNumber = "",
    //                     int numberToStore = -1, int numAfterDeci = -1);
    //     int GetExtractedNumberAsInt() const
    //     {
    //         return mi_number;
    //     }

    //     double GetExtractedNumberAsDouble() const;
    //     bool IsExtractedNumberValid() const
    //     {
    //         return mi_number >= 0;
    //     }
    //     std::string GetNumberStringSeq() const
    //     {
    //         return mstr_numberSeq;
    //     }
    //     bool IsExtractedNumberAnInt() const
    //     {
    //         return (mi_numberAfterDecimal < 0) && IsExtractedNumberValid();
    //     }
    //     int GetNumberOfStringForNumber() const;

    // private:
    //     std::string mstr_numberSeq;
    //     int mi_number = -1;
    //     int mi_numberAfterDecimal = -1;
    // };

public:
    NumberExtractor(std::string astr_WordSeq, int startIndexExtractionAfter = -1);
    // NumberExtractor(const std::vector<std::string> &ar_allWordAsString,
    //                 int startIndexExtractionAfter);
    // ExtractedNumber ExtractNextFullNumber();
    bool EndsWith(const std::string &mainStr, const std::string &toMatch);
    bool IfWordIsNumber(std::map<std::string, int> m, std::string word);
    std::vector<int> getListOfNumberExtracted() const;

private:
    /* data */
    std::vector<int> listOfNumberExtracted;
};
