#include "stackCustom.h"
#include <iostream>
#include <assert.h>

using namespace std;

template <class Type>
stackCustom<Type>::stackCustom(int stackSize)
{
    if (stackSize <= 0)
    {
        cout<<"Size of the Stack must be positive. Stack size is set to 100 "<<endl;
        maxStackSize = 100;
    }
    else
        maxStackSize = stackSize;

    stackTop = 0;
    list = new Type[maxStackSize]; //list to hold the stack elements
}

template <class Type>
stackCustom<Type>::~stackCustom()
{
    delete [] list; //delete the list containing stack elements
}

template <class Type>
const stackCustom<Type>& stackCustom<Type>::operator=(const stackCustom<Type>& otherStack)
{
    if (this != &otherStack)
        copyStack(otherStack);

    return *this;
}

template <class Type>
void stackCustom<Type>::copyStack(const stackCustom<Type>& otherStack)
{
    delete [] list;
    maxStackSize = otherStack.maxStackSize;
    stackTop = otherStack.stackTop;
}

template <class Type>
void stackCustom<Type>::initializeStack()
{
    stackTop = 0;
}

template <class Type>
bool stackCustom<Type>::isEmptyStack() const
{
    return (stackTop == 0);
}


template <class Type>
bool stackCustom<Type>::isFullStack() const
{
    return (stackTop == maxStackSize);
}

template <class Type>
void stackCustom<Type>::push(const Type& newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = newItem;
        stackTop++;
    }
    else
        cout<< "The stack is full."<<endl;
}

template <class Type>
Type stackCustom<Type>::top() const
{

    assert(stackTop != 0);

    return list[stackTop - 1];
}

template <class Type>
void stackCustom<Type>::pop()
{
    if (!isEmptyStack())
        stackTop--;
    else
        cout<< "Cannot remove from an empty Stack"<<endl;
}

template <class Type>
void stackCustom<Type>::printStack()
{

    int top1 = stackTop;
    while (!isEmptyStack())
    {
        cout << top() << " ";
        pop();
    }
    stackTop = top1;

}

template <class Type>
int stackCustom<Type>::getStackTop()
{
    return stackTop;
}
