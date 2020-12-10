#pragma once
#include <string>
#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>

class Command
{
public:
    Command();
    Command(std::string input);
    const std::string getCommands();
    const std::string getMainCommands();
    Command(const Command &copy);
    Command &operator=(const Command &c);
    ~Command();

private:
    std::string commands;
    std::string mainCommands;
    std::string readMainCommand(std::string input);
};


