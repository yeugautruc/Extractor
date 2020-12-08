#include "NumberExtractor.h"

NumberExtractor::ExtractedNumber::ExtractedNumber(
    std::string astr_seqOfNumber = "",
    int numberToStore = -1, int numAfterDeci = -1)
{
    mstr_numberSeq = astr_seqOfNumber;
    mi_number = numberToStore;
    mi_numberAfterDecimal = numAfterDeci;
};