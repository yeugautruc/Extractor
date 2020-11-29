#include "NumberExtractor.h"
#include "fstream"
#include "iostream"
using namespace std;

int main()
{
	string output, line;
	ifstream myfile("testText.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			output += line + "\n";
		}
		myfile.close();
	}

	NumberExtractor n = NumberExtractor(output, 1);
	for (int i = 0; i < n.getListOfNumberExtracted().size(); ++i)
	{
		std::cout << n.getListOfNumberExtracted()[i] << ' ';
	}
}