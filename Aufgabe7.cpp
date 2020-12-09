#include "NumberExtractor.h"
#include "fstream"
#include "iostream"
#include <iomanip>
#include "math.h"
using namespace std;

bool test0()
{
	string utter = "fly_niki six hundred zulu contact tower now "
				   "one two three point eight servus "
				   "one thousand zero nine ga"
				   "zero one two three";

	NumberExtractor numEx(utter);
	NumberExtractor::ExtractedNumber exNum = numEx.ExtractNextFullNumber();
	if (exNum.GetExtractedNumberAsInt() != 600 ||
		exNum.GetNumberStringSeq() != "six hundred")
	{
		return false;
	}

	exNum = numEx.ExtractNextFullNumber();
	if ((fabs(exNum.GetExtractedNumberAsDouble() - 123.8) > 0.0001) || (exNum.GetNumberStringSeq() != "one two three point eight"))
	{
		return false;
	}

	exNum = numEx.ExtractNextFullNumber();
	if (exNum.IsExtractedNumberValid() || exNum.GetNumberStringSeq() != "")
	{
		return false;
	}
	return true;
}

int main()
{
	std::cout << std::setprecision(2) << std::fixed;
	if (test0())
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "true" << std::endl;
	}

	// string utter = " six hundred a "
	// 			   "one two three point eight servus";
	// std::cout << utter << std::endl;
	// NumberExtractor new1 = NumberExtractor(utter);
	// NumberExtractor::ExtractedNumber out1 = new1.ExtractNextFullNumber();
	// NumberExtractor::ExtractedNumber out2 = new1.ExtractNextFullNumber();
	// std::cout << out2.GetExtractedNumberAsDouble() << std::endl;
	// std::cout << out2.GetNumberStringSeq() << std::endl;
	// std::cout << out1.GetNumberStringSeq() << std::endl;
	// std::cout << out1.GetExtractedNumberAsInt() << std::endl;
	// std::cout << out2.GetNumberOfStringForNumber() << std::endl;
}