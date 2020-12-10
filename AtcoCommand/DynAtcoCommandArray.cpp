#include "DynAtcoCommandArray.h"

DynAtcoCommandArray::DynAtcoCommandArray()
{
    this->size = 1;
    this->array = new AtcoCommand[1];
};

DynAtcoCommandArray::DynAtcoCommandArray(int size)
{
    this->size = size;
    this->array = new AtcoCommand[size];
};

DynAtcoCommandArray::~DynAtcoCommandArray(){
    delete[] array;
};

DynAtcoCommandArray::DynAtcoCommandArray(const DynAtcoCommandArray &d2)
{
    size = d2.size;
    array = new AtcoCommand[size];
    for (int i = 0; i < size; ++i)
    {
        array[i] = d2.array[i];
    }
};

DynAtcoCommandArray &DynAtcoCommandArray::operator=(const DynAtcoCommandArray &d2)
{
    if (this != &d2)
    {
        AtcoCommand *tmp = new AtcoCommand[d2.size];
        for (int i = 0; i < d2.size; ++i)
        {
            tmp[i] = d2.array[i];
        }
        // Make memory free
        delete[] array;
        
        size = d2.size;

        // change pointer
        array = tmp;
    }
    return *this;
};

void DynAtcoCommandArray::add(AtcoCommand v)
{
    int newSize = size + 1;
    resizeAtcoCommand(array, size, newSize);
    array[size - 1] = v;
    size++;
};

bool DynAtcoCommandArray::istElem(AtcoCommand *v) const
{
    if (v->getDynCommands().getSize() == 0)
    {
        return false;
    }
    return true;
};

const int DynAtcoCommandArray::getSize()
{
    return size;
};

AtcoCommand *DynAtcoCommandArray::getArray()
{
    return array;
};

AtcoCommand DynAtcoCommandArray::getElementArray(int index)
{
    return array[index];
};

void DynAtcoCommandArray::resizeAtcoCommand(AtcoCommand *&inputArray, int &oldSize, int &newSize)
{
    AtcoCommand *temp = new AtcoCommand[oldSize];
    for (int i = 0; i < oldSize; i++)
    {
        temp[i] = inputArray[i];
    }
    delete[] inputArray;

    inputArray = new AtcoCommand[newSize];
    for (int i = 0; i < oldSize; i++)
    {
        inputArray[i] = temp[i];
    }
    delete[] temp;
};