#include "NumberExtractor.h"
#include "fstream"
#include "iostream"
#include <iomanip>
#include "math.h"
#include <windows.h>
#include "./AtcoCommand/ReadAtCoCommand.h"
using namespace std;

const unsigned short BLUE = 9, YELLOW = 14, PINK = 13, RED = 12, WHITE = 15, GREEN = 10, GRAY = 8;

void cout_with_color(unsigned short color, string text)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, WHITE);
}

NumberExtractor testForIntNumber(string wordSeq, vector<int> expNumber, bool &b_success, bool expected)
{
	NumberExtractor output(wordSeq);
	if (!output.PerformFullExtraction())
	{
		cout << "false1 #" << endl;
		b_success = !expected;
	}

	else if (unsigned(output.GetExtractedNumbersCnt()) != unsigned(expNumber.size()))
	{
		cout << "false2 #" << output.GetExtractedNumbersCnt() << "#" << expNumber.size() << "# ";
		b_success = !expected;
	}
	else
	{
		for (int i = 0; unsigned(i) < expNumber.size(); i++)
		{
			if (expNumber[i] != output.GetNumberAsInt(i) || !output.IsNumberInt(i))
			{
				cout << "false3 #" << output.GetNumberAsInt(i) << "#" << output.GetNumberAsString(i) << "#";
				b_success = !expected;
			}
		}
	}

	b_success = expected;
	return output;
}

NumberExtractor testForDecimalNumber(string wordSeq, vector<double> expNumber, bool &b_success, bool expected)
{
	NumberExtractor output(wordSeq);
	if (!output.PerformFullExtraction())
	{
		cout << "false1 #" << endl;
		b_success = !expected;
	}
	else if (unsigned(output.GetExtractedNumbersCnt()) != unsigned(expNumber.size()))
	{
		cout << "false2 #" << output.GetExtractedNumbersCnt() << "#" << expNumber.size() << "# ";
		b_success = !expected;
	}
	else
	{
		for (int i = 0; unsigned(i) < unsigned(expNumber.size()); i++)
		{
			if (expNumber[i] != output.GetNumberAsDouble(i) || !output.IsNumberDouble(i))
			{
				cout << "false3 #" << output.GetNumberAsDouble(i) << "#" << output.GetNumberAsString(i) << "#";
				b_success = !expected;
			}
		}
	}
	return output;
}

void Perform_Number_Extractor_And_Output(vector<string> wordSeq)
{
	NumberExtractor numEx1(wordSeq);
	numEx1.PerformFullExtraction();

	for (int i = 0; unsigned(i) < unsigned(numEx1.getListOfVectorStringExtractedNumber().size()); i++)
	{
		std::cout << "\"" << wordSeq[i] << "\" is result in: \n ";
		if (numEx1.getListOfVectorStringExtractedNumber()[i].size() == 0)
		{
			cout_with_color(YELLOW, "No numbers extracted!");
		}
		for (int f = 0; unsigned(f) < unsigned(numEx1.getListOfVectorStringExtractedNumber()[i].size()); f++)
		{
			cout_with_color(YELLOW, numEx1.getListOfVectorStringExtractedNumber()[i][f] + "  ");
		}
		std::cout << std::endl;
	}
}

void Perform_Number_Extractor_And_Output(vector<string> wordSeq, vector<vector<int>> expectNumberToRead)
{
	NumberExtractor numEx(wordSeq);
	numEx.PerformFullExtraction();
	for (int i = 0; unsigned(i) < unsigned(numEx.getListOfVectorStringExtractedNumber().size()); i++)
	{
		std::cout << "\"" << wordSeq[i] << "\" is result in: \n ";
		if (numEx.getListOfVectorStringExtractedNumber()[i].size() == 0)
		{
			cout_with_color(GREEN, "No numbers extracted!");
		}
		bool success = false;

		string testString = "";
		for (int k = 0; unsigned(k) < unsigned(numEx.getListOfVectorStringExtractedNumber()[i].size()); k++)
		{
			testString = testString + " and " + numEx.getListOfVectorStringExtractedString()[i][k];
		}

		NumberExtractor newNumEx = testForIntNumber(testString, expectNumberToRead[i], success, true);

		for (int f = 0; unsigned(f) < unsigned(numEx.getListOfVectorStringExtractedNumber()[i].size()); f++)
		{
			if (success)
			{
				cout_with_color(GREEN, numEx.getListOfVectorStringExtractedNumber()[i][f] + "  ");
			}
			else
			{
				cout_with_color(RED, numEx.getListOfVectorStringExtractedNumber()[i][f] + "  ");
			}
		}
		std::cout << std::endl;
	}
}

void ReadUtterancesAnOutputNumbers_WithExpected(string url)
{
	ReadAtCoCommand atco1 = ReadAtCoCommand(url);
	cout << "Number from utterances of file: '" << url << "':\n";
	vector<string> wordSeqFromAtco1 = {};
	for (int i = 0; i < atco1.getOutputAtcoCommand().getDynAtcoCommands().getSize(); i++)
	{
		if (atco1.getOutputAtcoCommand().getDynAtcoCommands().getElementArray(i).getWordSequence().length() > 1)
		{
			wordSeqFromAtco1.push_back(atco1.getOutputAtcoCommand().getDynAtcoCommands().getElementArray(i).getWordSequence());
		}
	}

	vector<vector<int>> expectToRead = {{52, 120}, {1767, 100}, {61, 120}, {52}, {52, 160}, {60}, {}, {34}, {34}, {34, 1016}, {9}};
	Perform_Number_Extractor_And_Output(wordSeqFromAtco1, expectToRead);
}

void ReadUtterancesAnOutputNumbers(string url)
{
	ReadAtCoCommand atco1 = ReadAtCoCommand(url);
	cout << "Number from utterances of file: '" << url << "':\n";
	vector<string> wordSeqFromAtco1 = {};
	for (int i = 0; i < atco1.getOutputAtcoCommand().getDynAtcoCommands().getSize(); i++)
	{
		if (atco1.getOutputAtcoCommand().getDynAtcoCommands().getElementArray(i).getWordSequence().length() > 1)
		{
			wordSeqFromAtco1.push_back(atco1.getOutputAtcoCommand().getDynAtcoCommands().getElementArray(i).getWordSequence());
		}
	}

	Perform_Number_Extractor_And_Output(wordSeqFromAtco1);
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

	string wordSeq6 = "on qnh one zero zero nine";
	vector<int> expNumbers6 = {1009};
	bool b_success6 = true;
	NumberExtractor numEx6 =
		testForIntNumber(wordSeq6, expNumbers6, b_success6, true);

	string wordSeq7 = "ils two four hour and descend five thousand feet qnh one zero one two ";
	vector<int> expNumbers7 = {24, 5000, 1012};
	bool b_success7 = true;
	NumberExtractor numEx7 =
		testForIntNumber(wordSeq7, expNumbers7, b_success7, true);

	string wordSeq8 = "on qnh two hundred four";
	vector<int> expNumbers8 = {204};
	bool b_success8 = true;
	NumberExtractor numEx8 =
		testForIntNumber(wordSeq8, expNumbers8, b_success8, true);

	return b_success && b_success2 && b_success3 && b_success4 && b_success5 && b_success6 && b_success7 && b_success8;
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
	//Test
	std::cout << "Test start! " << std::endl;
	std::cout << "		Test 0: " << ((test0()) ? "true" : "false") << std::endl;
	std::cout << "		TestExtractDecimalNumber: " << ((testExtractDecimalNumber()) ? "true" : "false") << std::endl;
	std::cout << "		TestExtractNumberThousand: " << ((testExtractNumberThousand()) ? "true" : "false") << std::endl;
	std::cout << "Test end! \n"
			  << std::endl;

	vector<string> testSeq = {
		"one zero zero one hundred",
	};
	Perform_Number_Extractor_And_Output(testSeq);
	std::cout << "\n<==============devider=============>\n\n";

	vector<string>
		wordSeq = {
			"dobry den sky_travel five eight juliert ruzyne radar radar contact"
			" on present heading descend four thousand feet qnh one zero two two",
			"jet_execute five two seven turn right heading three five zero vectoring for "
			"ils approach runway two four hour and descend five thousand feet qnh one zero one two ",
			" good day vueling eight six five two praha radar radar contact "
			"descend flight level one zero zero current information is quebec and speed "
			"two seventy or less",

			"oscar kilo victor india kilo roger descend three thousand five hundred feet"
			"squawk seven thousand",

			"csa six six nine descend flight level one hundred turn left"
			"heading zero six five",

			"snow cab two hundred one descend eight thousand feet",
			"snow cab two hundred twenty one descend eight thousand six hundred feet",
			"snow cab two hundred twenty four",
			"descend eight thousand six hundred twenty one feet",

			"austrian three nine two papa descend altitude one zero thousand "
			"qnh one zero zero three ",

			"contact director one one nine dummy eight goodbye"};

	vector<string> wordSeq2 = {
		"snow cab two hundred on descend eight thousand feet",
		"snow cab two hundred twenty one descend eight thousand six hundred feet",
		"snow cab two hundred twenty four descend eight thousand six hundred twenty one feet",
		"austrian three nine two papa descend altitude one zero thousand qnh one zero zero three",
		"contact director one one nine dummy eight goodbye"};

	Perform_Number_Extractor_And_Output(wordSeq);
	cout_with_color(PINK, "\n<==============devider=============>\n\n");
	Perform_Number_Extractor_And_Output(wordSeq2);
	cout_with_color(PINK, "\n<==============devider=============>\n\n");
	ReadUtterancesAnOutputNumbers("./AtcoCommand/longTest.txt");
	cout_with_color(PINK, "\n<==============devider=============>\n\n");
	ReadUtterancesAnOutputNumbers_WithExpected("./AtcoCommand/longTest.txt");
}