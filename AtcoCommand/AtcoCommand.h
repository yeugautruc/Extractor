#pragma once
#include <string>
#include "FileName.h"
#include "Command.h"
#include "DynCommandArray.h"

class AtcoCommand
{
private:
    /* data */
    std::string fileName;
    std::string wordSequence;
    DynCommandArray commands;
    std::string date;
    std::string time;
    DateTime formattedDateTime;

public:
    AtcoCommand();

    AtcoCommand(std::string fileNameInput, std::string wordSequenceInput, std::string commandsInput);

    AtcoCommand(const AtcoCommand &copy);

    AtcoCommand &operator=(const AtcoCommand &input);

    void readCommands(std::string commandsInput);

    void readDateTime(std::string input);

    std::string toString();

    const std::string getWordSequence();

    Command getElementFromCommandArray(int k);
    
    DynCommandArray getDynCommands();

    const int getSizeCommands();

    const std::string getDate();

    const std::string getTime();

    DateTime getFormattedDateTime();

    ~AtcoCommand();
};