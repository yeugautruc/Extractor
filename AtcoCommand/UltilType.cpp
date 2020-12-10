#include "UltilType.h"
#include "DynAtcoCommandArray.h"
#include "DynOcurrenceArray.h"
#include <string>
#include "map"
#include <vector>
#include <algorithm>

UltilType::UltilType()
{
	DynAtcoCommands = DynAtcoCommandArray(1);
	DynOcurrences = DynOcurrenceArray(1);
};

// Constructor to get AtcoCommand from
UltilType::UltilType(DynAtcoCommandArray &arr, std::map<std::string, int> &w, std::map<std::string, int> &c, std::string &u)
{
	int sizeA = 1;
	int sizeO = 1;
	DynAtcoCommands = DynAtcoCommandArray(sizeA);
	DynOcurrences = DynOcurrenceArray(sizeO);

	DynAtcoCommands = arr;

	// Itterator command map into Occurrence dynamic array
	std::map<std::string, int>::iterator it = c.begin();
	for (std::pair<std::string, int> element : c)
	{
		// Accessing KEY from element
		std::string word = element.first;
		// Accessing VALUE from element.
		int count = element.second;

		// Keep occurence in to dynamic array
		Ocurrence ocur = Ocurrence(word, count);
		DynOcurrences.add(ocur);
	};

	lengthArray = arr.getSize();
	wordsMap = w;
	commandsMap = c;
	url = u;
};

// Get top commands
std::string UltilType::getTopCommands(int amount)
{
	return topCommands(commandsMap, amount, url);
};

// Get top word sequence
std::string UltilType::getTopWords()
{
	return topWords(wordsMap);
};

// Print method
void UltilType::print()
{
	for (int i = 0; i < lengthArray; i++)
	{
		if (DynAtcoCommands.getElementArray(i).toString().length() > 10)
		{
			std::cout << DynAtcoCommands.getElementArray(i).toString() << std::endl;
		}
	}
	std::cout << topWords(wordsMap) << std::endl;
	std::cout << topCommands(commandsMap, 20, url) << std::endl;
};

// Comparator use in sort method (Z -> A)
bool cmp(std::pair<std::string, int> &a,
		 std::pair<std::string, int> &b)
{
	return a.second != b.second ? a.second > b.second : a.first > b.first;
};

// Get top word sequence
std::string UltilType::topWords(std::map<std::string, int> &M)
{
	std::string output = "";
	std::vector<std::pair<std::string, int>> A;
	size_t sizeB = 0;
	for (auto &it : M)
	{
		A.push_back(it);
	}
	std::sort(A.begin(), A.end(), cmp);
	if (A.size() > 10)
	{
		sizeB = 10;
	}
	else
	{
		sizeB = A.size();
	}
	std::vector<std::pair<std::string, int>> B(A.begin(), A.begin() + sizeB);
	output += "The top 10 occurences\n";
	int counter = 1;
	for (auto &it : B)
	{
		if (counter < 4)
		{
			output += "" + std::to_string(counter) + ".";
			for (size_t i = 0; i < 20 - it.first.length(); i++)
			{
				output += " ";
			}
			output += it.first + ":   " + std::to_string(it.second) + "\n";
			counter++;
		}
		else
		{
			for (size_t i = 0; i < 22 - it.first.length(); i++)
			{
				output += " ";
			}
			output += it.first + ":   " + std::to_string(it.second) + "\n";
		}
	}
	return output;
};

// Get top commands
std::string UltilType::topCommands(std::map<std::string, int> &M, int amount, std::string fileName)
{
	std::string output = "";
	std::vector<std::pair<std::string, int>> A;
	size_t sizeB = 0;
	for (auto &it : M)
	{
		A.push_back(it);
	}
	sort(A.begin(), A.end(), cmp);
	if (A.size() > unsigned(amount))
	{
		sizeB = amount;
	}
	else
	{
		sizeB = A.size();
	}
	std::vector<std::pair<std::string, int>> B(A.begin(), A.begin() + sizeB);
	output += "The top" + std::to_string(amount) + " type occurences specified in " + fileName + "\n";
	int counter = 1;
	for (auto &it : B)
	{
		if (counter < 2)
		{
			output += "" + std::to_string(counter) + ".";
			for (size_t i = 0; i < 20 - it.first.length(); i++)
			{
				output += " ";
			}
			output += it.first + ":   " + std::to_string(it.second) + "\n";
			counter++;
		}
		else
		{
			for (size_t i = 0; i < 22 - it.first.length(); i++)
			{
				output += " ";
			}
			output += it.first + ":   " + std::to_string(it.second) + "\n";
		}
	}
	return output;
};

DynAtcoCommandArray UltilType::getDynAtcoCommands()
{
	return DynAtcoCommands;
};
DynOcurrenceArray UltilType::getDynOcurrences()
{
	return DynOcurrences;
};

UltilType::~UltilType(){

};