#pragma once
#include "string"
#include "vector"
#include "map"
#include "iterator"
#include <algorithm>
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

    class myexception : public exception
    {
        virtual const char *what() const throw()
        {
            return "My exception happened";
        }
    } myex;

public:
    // the numbers are extracted from astr_WordSeq
    // starting after word startIndexExtractionAfter, first word starts at index 0
    NumberExtractor(std::string astr_WordSeq, int startIndexExtractionAfter = -1);

    // same as before, but the single are already extracted into a vector
    // the numbers are extracted from ar_allWordAsString
    // starting after the word startIndexExtractionAfter, first word starts at index in vector 0
    NumberExtractor(const std::vector<std::string> &ar_allWordAsString,
                    int startIndexExtractionAfter = -1);

    //  extracts all number from member mstr_wordSeq and insert into member m_extractedNumberSeq
    bool PerformFullExtraction();

    // extracts the next complete number from sequence of wors provide in constructor
    ExtractedNumber ExtractNextFullNumber();

    // how many numbers are extracted from string provided in constructor
    int GetExtractedNumbersCnt() const
    {
        return static_cast<int>(m_extractedNumberSeq.size());
    }

    // return extracted string with index as an interger (throws exception if index invalid)
    std::string GetNumberAsString(int index) const
    {
        return m_extractedNumberSeq.at(index).GetNumberStringSeq();
    }

    // return extracted number with index as an interger (throws exception if index invalid)
    int GetNumberAsInt(int index) const
    {
        return m_extractedNumberSeq.at(index).GetExtractedNumberAsInt();
    }

    // return extracted number with index as a floating point (throws exception if index invalid)
    double GetNumberAsDouble(int index) const
    {
        return m_extractedNumberSeq.at(index).GetExtractedNumberAsDouble();
    }

    // is extracted number with index a valid number (throws exception if index invalid)
    bool IsNumberValid(int index) const
    {
        return m_extractedNumberSeq.at(index).IsExtractedNumberValid();
    }

    // is extracted number with index a valid interger? (throws exception if index invalid)
    bool IsNumberInt(int index) const
    {
        return IsNumberValid(index) && m_extractedNumberSeq.at(index).IsExtractedNumberAnInt();
    }

    // is extracted number with index a valid floating point number? (throws exception if index invalid)
    bool IsNumberDouble(int index) const
    {
        return IsNumberValid(index) && !m_extractedNumberSeq.at(index).IsExtractedNumberAnInt();
    }

    bool EndsWith(const std::string &mainStr, const std::string &toMatch);
    bool IfWordIsNumber(std::map<std::string, int> m, std::string word);
    std::vector<std::string> getListOfNumberExtracted() const;
    std::vector<std::string> getListOfNumberStringExtracted() const;
    std::vector<std::vector<std::string>> getListOfVectorStringExtractedNumber() const;
    std::vector<std::vector<std::string>> getListOfVectorStringExtractedString() const;

private:
    /* data */
    int indexOfListNumberExtracted;
    std::vector<std::string> listOfNumberExtracted;
    std::vector<std::string> listOfNumberStringExtracted;
    std::vector<std::vector<std::string>> listOfVectorStringExtractedNumber;
    std::vector<std::vector<std::string>> listOfVectorStringExtractedString;
    std::vector<NumberExtractor::ExtractedNumber> m_extractedNumberSeq;
    std::string trim(std::string s);
    std::string ltrim(std::string s);
    std::string rtrim(std::string s);
};
