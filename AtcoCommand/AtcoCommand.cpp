#include "AtcoCommand.h"
#include "FileName.h"
#include "Command.h"
#include <string>
#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>

AtcoCommand::AtcoCommand()
{
}

AtcoCommand::AtcoCommand(std::string fileNameInput, std::string wordSequenceInput, std::string commandsInput)
{
    readDateTime(fileNameInput);
    formattedDateTime = DateTime(date, time);
    fileName += date + "__" + time + formattedDateTime.toString();
    wordSequence = wordSequenceInput;
    readCommands(commandsInput);
}

AtcoCommand::AtcoCommand(const AtcoCommand &copy)
{
    this->commands = copy.commands; // type DynCommandArray have their own assignment operator
    this->date = copy.date;
    this->time = copy.time;
    this->fileName = copy.fileName;
    this->wordSequence = copy.wordSequence;
    this->formattedDateTime = copy.formattedDateTime; // type DateTime have their own assignment operator
};

AtcoCommand &AtcoCommand::operator=(const AtcoCommand &input)
{
    if (this != &input)
    {
        this->commands = input.commands; // type DynCommandArray have their own assignment operator
        this->date = input.date;
        this->time = input.time;
        this->fileName = input.fileName;
        this->wordSequence = input.wordSequence;
        this->formattedDateTime = input.formattedDateTime; // type DateTime have their own assignment operator
    };

    return *this;
};

void AtcoCommand::readCommands(std::string commandsInput)
{
    commands = DynCommandArray(1);

    std::istringstream f(commandsInput);
    std::string line;
    while (getline(f, line))
    {
        Command cmd = Command(line);
        commands.add(cmd);
    }
}

void AtcoCommand::readDateTime(std::string input)
{
    date = input.substr(0, input.find("__"));
    time = input.substr(input.find("__") + 2, input.length()).substr(0, input.substr(input.find("__") + 2, input.length()).find(":"));
}

std::string AtcoCommand::toString()
{
    std::string output = fileName + " \n" + wordSequence + " :\n", command = "";
    for (int i = 0; i < commands.getSize(); i++)
    {
        if (commands.getElementArray(i).getCommands().length() > 10)
        {
            command += commands.getElementArray(i).getCommands() + ";";
        }
    }
    output += command;

    return output;
}

const std::string AtcoCommand::getWordSequence()
{
    return wordSequence;
}

AtcoCommand::~AtcoCommand()
{
}

const std::string AtcoCommand::getDate()
{
    return date;
}
const std::string AtcoCommand::getTime()
{
    return time;
}
Command AtcoCommand::getElementFromCommandArray(int k)
{
    return commands.getElementArray(k);
};

DynCommandArray AtcoCommand::getDynCommands()
{
    return commands;
};

const int AtcoCommand::getSizeCommands()
{
    return commands.getSize();
};

DateTime AtcoCommand::getFormattedDateTime()
{
    return formattedDateTime;
}