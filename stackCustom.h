#ifndef STACKCUSTOM_H
#define STACKCUSTOM_H

template <class Type>
class stackCustom
{
    public:
        stackCustom(int stackSize = 100);
        ~stackCustom();
        const stackCustom<Type>& operator=(const stackCustom<Type>&);
        void initializeStack();
        bool isEmptyStack() const;
        bool isFullStack() const;
        void push(const Type& newItem);
        Type top() const;
        void pop();
        void printStack();
        int getStackTop();

    private:
        int maxStackSize;
        int stackTop; //variable to point at the top of the stack
        Type* list; //pointer to the array that holds the stack elemnts

        void copyStack(const stackCustom<Type>& otherStack);
};

#endif // STACKCUSTOM_H
