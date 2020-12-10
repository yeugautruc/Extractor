#include "DynCommandArray.h"

DynCommandArray::DynCommandArray(){
    this->size = 1;
    this->array = new Command[1];
};

DynCommandArray::DynCommandArray(int size)
{
    this->size = size;
    this->array = new Command[size];
};

DynCommandArray::DynCommandArray(const DynCommandArray &d2)
{
    size = d2.size;
    array = new Command[size];
    for (int i = 0; i < size; ++i)
    {
        array[i] = d2.array[i];
    }
}

DynCommandArray &DynCommandArray::operator=(const DynCommandArray &d2)
{
    if (this != &d2)
    {
        Command *tmp = new Command[d2.size];
        for (int i = 0; i < d2.size; ++i)
        {
            tmp[i] = d2.array[i];
        }
        // Make memory free
        delete[] array;

        array = nullptr;
        size = d2.size;

        // change pointer
        array = tmp;
    }
    return *this;
}

void DynCommandArray::add(Command v)
{
    int newSize = size + 1;
    resizeCommand(array, size, newSize);
    array[size - 1] = v;
    size++;
};

const int DynCommandArray::getSize()
{
    return size;
};

Command *DynCommandArray::getArray()
{
    return array;
};
Command DynCommandArray::getElementArray(int index)
{
    return array[index];
};

bool DynCommandArray::istElem(Command *v) const
{
    if (v->getCommands() == "")
    {
        return false;
    }
    return true;
};

DynCommandArray::~DynCommandArray(){
    delete[] array;
};

void DynCommandArray::resizeCommand(Command *&inputArray, int &oldSize, int &newSize)
{
    Command *temp = new Command[oldSize];
    for (int i = 0; i < oldSize; i++)
    {
        temp[i] = inputArray[i];
    }
    delete[] inputArray;

    inputArray = new Command[newSize];
    for (int i = 0; i < oldSize; i++)
    {
        inputArray[i] = temp[i];
    }
    delete[] temp;
};