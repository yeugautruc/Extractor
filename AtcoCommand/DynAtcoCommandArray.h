#pragma once
#include "AtcoCommand.h"

class DynAtcoCommandArray
{
public:
    DynAtcoCommandArray();
    DynAtcoCommandArray(int size);
    ~DynAtcoCommandArray();
    DynAtcoCommandArray(const DynAtcoCommandArray &);
    DynAtcoCommandArray &operator=(const DynAtcoCommandArray &d2);
    void add(AtcoCommand v);
    bool istElem(AtcoCommand *v) const;
    const int getSize();
    AtcoCommand *getArray();
    AtcoCommand getElementArray(int index);

private:
    void resizeAtcoCommand(AtcoCommand *&inputArray, int &oldSize, int &newSize);
    AtcoCommand *array;
    int size;
};
