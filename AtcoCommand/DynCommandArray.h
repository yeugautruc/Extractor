#pragma once
#include "Command.h"

class DynCommandArray
{
public:
    DynCommandArray();
    DynCommandArray(int size);
    ~DynCommandArray();
    DynCommandArray(const DynCommandArray &d2);
    DynCommandArray &operator=(const DynCommandArray &d2);
    void add(Command v);
    bool istElem(Command *v) const;
    const int getSize();
    Command* getArray();
    Command getElementArray(int index);

private:
    void resizeCommand(Command *&inputArray, int &oldSize, int &newSize);
    Command *array;
    int size;
};
