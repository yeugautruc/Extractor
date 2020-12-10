#include "Ocurrence.h"
#include <string>

Ocurrence::Ocurrence()
{
    value = "";
    amount = 0;
};

Ocurrence::Ocurrence(std::string v, int a)
{
    value = v;
    amount = a;
};

Ocurrence::Ocurrence(const Ocurrence &c)
{
    this->value = c.value;
    this->amount = c.amount;
};

Ocurrence &Ocurrence::operator=(const Ocurrence &c)
{
    if (this != &c)
    {
        this->amount = c.amount;
        this->value = c.value;
    };
    return *this;
};

void Ocurrence::setValue(std::string v)
{
    value = v;
};

void Ocurrence::setAmount(int a)
{
    amount = a;
};

const std::string Ocurrence::getValue()
{
    return value;
};

const int Ocurrence::getAmount()
{
    return amount;
};

std::string Ocurrence::toString(){
    return "Value: " + value + "\nAmount: "+ std::to_string(amount);
};

Ocurrence::~Ocurrence(){};