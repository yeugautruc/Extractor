#pragma once
#include "DynAtcoCommandArray.h"
#include "DynOcurrenceArray.h"
#include <string>
#include "map"

class UltilType
{
public:
    UltilType();
    UltilType(DynAtcoCommandArray &arr, std::map<std::string, int> &w, std::map<std::string, int> &c, std::string &u);
    std::string getTopCommands(int amount);
    std::string getTopWords();
    std::string topCommands(std::map<std::string, int> &M, int amount, std::string url);
    std::string topWords(std::map<std::string, int> &M);
    DynAtcoCommandArray getDynAtcoCommands();
    DynOcurrenceArray getDynOcurrences();
    void print();
    ~UltilType();

private:
    std::string url;
    std::map<std::string, int> wordsMap;
    std::map<std::string, int> commandsMap;
    // Two dynamic array to save Occurence and AtcoCommand
    DynOcurrenceArray DynOcurrences;
    DynAtcoCommandArray DynAtcoCommands;
    int lengthArray{};
};