#include "NumberExtractor.h"
#include "fstream"
#include "iostream"
using namespace std;

int main()
{
	string utter = " six hundred"
				   "one two thre point eight servus";
	std::cout << utter;
	// string output, line;
	// ifstream myfile("testText.txt");
	// if (myfile.is_open())
	// {
	// 	while (getline(myfile, line))
	// 	{
	// 		output += line + "\n";
	// 	}
	// 	myfile.close();
	// }

	// NumberExtractor n = NumberExtractor(output, 1);

	// for (int i = 0; i < n.getListOfNumberExtracted().size(); ++i)
	// {
	// 	std::cout << n.getListOfNumberExtracted()[i] << ' ';
	// }

	// ifstream myfile2("testText.txt");
	// int i = 0;
	// if (myfile2.is_open())
	// {
	// 	while (getline(myfile2, line))
	// 	{
	// 		std::cout << line << std::endl;
	// 		if (i < n.getListOfNumberExtracted().size())
	// 		{
	// 			std::cout << n.getListOfNumberExtracted()[i++] << std::endl;
	// 		}
	// 	}
	// 	myfile2.close();
	// }
}