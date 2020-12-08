#pragma once
#include "string"
#include "vector"
#include "map"
#include "iterator"
#include <iostream>
#include <sstream>

class NumberExtractor
{
public:
    class ExtractedNumber
    {

    public:
        ExtractedNumber(std::string astr_seqOfNumber = "",
                        int numberToStore = -1, int numAfterDeci = -1);
        int GetExtractedNumberAsInt() const
        {
            return mi_number;
        }

        double GetExtractedNumberAsDouble() const;
        bool IsExtractedNumberValid() const
        {
            return mi_number >= 0;
        }

        std::string GetNumberStringSeq() const
        {
            return mstr_numberSeq;
        }
        bool IsExtractedNumberAnInt() const
        {
            return (mi_numberAfterDecimal < 0) && IsExtractedNumberValid();
        }

        // number of words in mstr_numberSeq
        int GetNumberOfStringForNumber() const;

    private:
        // substring of mstr_numberSeq containing the words implementing the number
        std::string mstr_numberSeq;

        // the extracted number
        int mi_number = -1;

        // the extracted number after word decimal etc, if we have extracted a double
        int mi_numberAfterDecimal = -1;
    };

public:
    // the numbers are extracted from astr_WordSeq
    // starting after word startIndexExtractionAfter, first word starts at index 0
    NumberExtractor(std::string astr_WordSeq, int startIndexExtractionAfter = -1);

    // same as before, but the single are already extracted into a vector
    // the numbers are extracted from ar_allWordAsString
    // starting after the word startIndexExtractionAfter, first word starts at index in vector 0
    NumberExtractor(const std::vector<std::string> &ar_allWordAsString,
                    int startIndexExtractionAfter);

    //  extracts all number from member mstr_wordSeq and insert into member m_extractedNumberSeq
    bool PerformFullExtraction();

    // extracts the next complete number from sequence of wors provide in constructor
    ExtractedNumber ExtractNextFullNumber();

    bool EndsWith(const std::string &mainStr, const std::string &toMatch);
    bool IfWordIsNumber(std::map<std::string, int> m, std::string word);
    std::vector<std::string> getListOfNumberExtracted() const;

private:
    /* data */
    int indexOfListNumberExtracted;
    std::vector<std::string> listOfNumberExtracted;
    std::vector<ExtractedNumber> m_extractedNumberSeq;
};
