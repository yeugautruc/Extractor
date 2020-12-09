#include "NumberExtractor.h"
#include "fstream"
#include "iostream"
#include <iomanip>
#include "math.h"
using namespace std;

NumberExtractor testForIntNumber(string wordSeq, vector<int> expNumber, bool &b_success, bool expected)
{
	NumberExtractor output(wordSeq);
	if (!output.PerformFullExtraction())
	{
		cout << "false1 #" << endl;
		b_success = !expected;
	};

	if (output.GetExtractedNumbersCnt() != expNumber.size())
	{
		cout << "false2 #" << endl;
		b_success = !expected;
	}
	for (int i = 0; i < expNumber.size(); i++)
	{
		if (expNumber[i] != output.GetNumberAsInt(i) || !output.IsNumberInt(i))
		{
			cout << "false3 #" << output.GetNumberAsInt(i) << "#" << endl;
			b_success = !expected;
		}
	}
	return output;
}

NumberExtractor testForDecimalNumber(string wordSeq, vector<double> expNumber, bool &b_success, bool expected)
{
	NumberExtractor output(wordSeq);
	if (!output.PerformFullExtraction())
	{
		cout << "false1 #" << endl;
		b_success = !expected;
	};
	if (output.GetExtractedNumbersCnt() != expNumber.size())
	{
		cout << "false2 #" << endl;
		b_success = !expected;
	}
	for (int i = 0; i < expNumber.size(); i++)
	{
		if (expNumber[i] != output.GetNumberAsDouble(i) || !output.IsNumberDouble(i))
		{
			cout << "false3 #" << output.GetNumberAsDouble(i) << "#" << endl;
			b_success = !expected;
		}
	}

	return output;
}

bool test0()
{
	string utter = "fly_niki six hundred zulu contact tower now "
				   "one two three point eight servus ";

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

bool testExtractNumberThousand()
{
	string wordSeq = "descend one zero thousand feet";
	vector<int> expNumbers = {10000};
	bool b_success = true;
	NumberExtractor numEx =
		testForIntNumber(wordSeq, expNumbers, b_success, true);

	string wordSeq2 = "on qnh one thousand zero nine";
	vector<int> expNumbers2 = {1009};
	bool b_success2 = true;
	NumberExtractor numEx2 =
		testForIntNumber(wordSeq2, expNumbers2, b_success2, true);

	string wordSeq3 = "on qnh one thousand zero twenty bye bye";
	vector<int> expNumbers3 = {1020};
	bool b_success3 = true;
	NumberExtractor numEx3 =
		testForIntNumber(wordSeq3, expNumbers3, b_success3, true);

	string wordSeq4 = "on qnh one thousand twenty eight reduce one six zero knots";
	vector<int> expNumbers4 = {1028, 160};
	bool b_success4 = true;
	NumberExtractor numEx4 =
		testForIntNumber(wordSeq4, expNumbers4, b_success4, true);

	string wordSeq5 = "on qnh one thousand zero two nine";
	vector<int> expNumbers5 = {1029};
	bool b_success5 = true;
	NumberExtractor numEx5 =
		testForIntNumber(wordSeq5, expNumbers5, b_success5, true);

	return b_success && b_success2 && b_success3 && b_success4 && b_success5;
}

bool testExtractDecimalNumber()
{
	string wordSeq = "contact director one one nine decimal eight four goodbye";
	vector<double> expNumbers = {119.84};
	bool b_success = true;
	NumberExtractor numEx =
		testForDecimalNumber(wordSeq, expNumbers, b_success, true);

	string wordSeq2 = "contact director one one nine point eight twenty one";
	vector<double> expNumbers2 = {119.821};
	bool b_success2 = true;
	NumberExtractor numEx2 =
		testForDecimalNumber(wordSeq2, expNumbers2, b_success2, true);
	return b_success && b_success2;
}

int main()
{
	// std::cout << std::setprecision(4) << std::fixed;
	std::cout << "test 0: " << ((test0()) ? "true" : "false") << std::endl;
	std::cout << "testExtractDecimalNumber: " << ((testExtractDecimalNumber()) ? "true" : "false") << std::endl;
	std::cout << "testExtractNumberThousand: " << ((testExtractNumberThousand()) ? "true" : "false") << std::endl;
	
}