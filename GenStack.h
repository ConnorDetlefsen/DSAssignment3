#include <iostream>
#include <stack>
#include <exception>

using namespace std;

template <class X>
class GenStack{
  public:
    GenStack();
    GenStack(int maxSize);
    ~GenStack(); //destructor

    void push(X data); //insert an item
    X pop();  //removes top item
    X peek(); //returns item at top of stack
    int size(); //returns number items in stack
    bool isEmpty(); //returns if stack is empty
    bool isFull(); //returns if full
    int maxSize(); //returns max size of stack

    void expand();

    int mSize;
    int top;

    X *myArray;
    X *tempStack;
};

//default constructor
template <class X>
GenStack<X>::GenStack(){
  myArray = new X[128];
  mSize = 128;
  top = -1;
}

template <class X>
GenStack<X>::GenStack(int maxSize){
  myArray = new X[maxSize];
  mSize = maxSize;
  top = -1;
}
//destructor
template <class X>
GenStack<X>::~GenStack(){
  cout << "object deleted" << endl;
  delete myArray;
}

template <class X>
void GenStack<X>::push(X data){
  if(isFull() == true){   //check if full before attempting to push /insert
    expand(); //expands stack by 10
  }
  myArray[++top] = data;
}

template <class X>
X GenStack<X>::pop(){
  if(isEmpty() == true){ //check if  empty before attempting to remove
    throw runtime_error("error: can't pop because stack is empty");
  }
  else{
    return myArray[top--];
  }
}

template <class X>
X GenStack<X>::peek(){ //returns item at top of stack without removing
  return myArray[top];
}

template <class X>
int GenStack<X>::size(){ //returns number of items in stack, not the max size of the stack
  return top+1;
}

template <class X>
bool GenStack<X>::isEmpty(){ //returns true if empty
  return(top == -1);
}

template <class X>
bool GenStack<X>::isFull(){ //returns true if full
  return(top == mSize-1);
}

template <class X>
void GenStack<X>::expand(){ //expands stack by 10 slots, uses temporary array
  tempStack = new X[mSize + 10];
  for (int i = 0; i < mSize; ++i){
    tempStack[i] = myArray[i];
  }
  mSize += 10;
  myArray = tempStack;
  delete[] tempStack;
}

template <class X>
int GenStack<X>::maxSize(){
  return mSize;
}
