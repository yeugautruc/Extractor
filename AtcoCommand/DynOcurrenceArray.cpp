#include "DynOcurrenceArray.h"

DynOcurrenceArray::DynOcurrenceArray()
{
    this->size = 1;
    this->array = new Ocurrence[1];
};

DynOcurrenceArray::DynOcurrenceArray(int size)
{
    this->size = size;
    this->array = new Ocurrence[size];
};

DynOcurrenceArray::~DynOcurrenceArray(){
    delete[] array;
};

DynOcurrenceArray::DynOcurrenceArray(const DynOcurrenceArray &d2)
{
    size = d2.size;
    array = new Ocurrence[size];
    for (int i = 0; i < size; ++i)
    {
        array[i] = d2.array[i];
    }
};

DynOcurrenceArray &DynOcurrenceArray::operator=(const DynOcurrenceArray &d2)
{
    if (this != &d2)
    {
        Ocurrence *tmp = new Ocurrence[d2.size];
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

void DynOcurrenceArray::add(Ocurrence v)
{
    int newSize = size + 1;
    resizeOcurrence(array, size, newSize);
    array[size - 1] = v;
    size++;
};

bool DynOcurrenceArray::istElem(Ocurrence *v) const
{
    if (v->getValue() == "")
    {
        return false;
    }
    return true;
};

const int DynOcurrenceArray::getSize()
{
    return size;
};

Ocurrence *DynOcurrenceArray::getArray()
{
    return array;
};

Ocurrence DynOcurrenceArray::getElementArray(int index)
{
    return array[index];
};

void DynOcurrenceArray::resizeOcurrence(Ocurrence *&inputArray, int &oldSize, int &newSize)
{
    Ocurrence *temp = new Ocurrence[oldSize];
    for (int i = 0; i < oldSize; i++)
    {
        temp[i] = inputArray[i];
    }
    delete[] inputArray;

    inputArray = new Ocurrence[newSize];
    for (int i = 0; i < oldSize; i++)
    {
        inputArray[i] = temp[i];
    }
    delete[] temp;
};