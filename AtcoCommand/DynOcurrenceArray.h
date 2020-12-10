#pragma once
#include "Ocurrence.h"

class DynOcurrenceArray
{
public:
    DynOcurrenceArray();
    DynOcurrenceArray(int size);
    ~DynOcurrenceArray();
    DynOcurrenceArray(const DynOcurrenceArray &);
    DynOcurrenceArray &operator=(const DynOcurrenceArray &d2);
    void add(Ocurrence v);
    bool istElem(Ocurrence *v) const;
    const int getSize();
    Ocurrence *getArray();
    Ocurrence getElementArray(int index);

private:
    void resizeOcurrence(Ocurrence *&inputArray, int &oldSize, int &newSize);
    Ocurrence *array;
    int size;
};
