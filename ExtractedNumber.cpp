#include "NumberExtractor.h"

NumberExtractor::ExtractedNumber::ExtractedNumber(
    std::string astr_seqOfNumber,
    int numberToStore, int numAfterDeci)
{
    mstr_numberSeq = astr_seqOfNumber;
    mi_number = numberToStore;
    mi_numberAfterDecimal = numAfterDeci;
};

double NumberExtractor::ExtractedNumber::GetExtractedNumberAsDouble() const
{
    if (mi_numberAfterDecimal != -1)
    {
        return std::stod(std::to_string(mi_number) + "." + std::to_string(mi_numberAfterDecimal));
    }
    return std::stod(std::to_string(mi_number));
}

int NumberExtractor::ExtractedNumber::GetNumberOfStringForNumber() const
{
    return unsigned(mstr_numberSeq.length());
};