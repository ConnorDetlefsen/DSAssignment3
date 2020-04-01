#include <iostream>
#include <stack>
#include <exception>
#include <fstream> //file streams


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

    void expand(); //expands stack if it gets full
    void delimFill(string fileName); //fills stack with delimiters
    void delimCheck(char c, int lineCount);
    void runThrough(char c, int lineCount);
    void error(char c);


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

template <class X>
void GenStack<X>::delimFill(string fileName){
  int count = 0;
  int firstQuote = 0;
  int endQuote = 0;

  ifstream fin; //creation of ifstream class object
  string line = "";
  int lineCount = 0;

  fin.open(fileName);
    while (fin) {     //reads in input from text file given from user
      getline(fin, line);
      ++lineCount;
      for(int i = 0; i < line.length(); ++i){   //finds count of each letter
        if(line[i] == '/' && line[i+1] == '/')
          break;
        if(line[i] == '\'' || line[i] == '\"'){
          firstQuote = i;
          for(int i = 0; i < line.length(); ++i){
            if(line[i] == '\'' || line[i] == '\"'){
              endQuote = i;
          }
        }
      }
        if(i <= endQuote && i >= firstQuote)
          continue;
        else{
          if(isFull() == true){   //check if full before attempting to push /insert
            expand(); //expands stack by 10
          }
          char c = line[i];
          if(c == '('){
            //myArray[++top] = c;
            delimCheck(c, lineCount);
          }
          else if(c == ')'){
            delimCheck(c, lineCount);
          }
          else if(c == '['){
            delimCheck(c, lineCount);
          }
          else if(c == ']'){
            delimCheck(c, lineCount);
          }
          else if(c == '{'){
            delimCheck(c, lineCount);
          }
          else if(c == '}'){
            delimCheck(c, lineCount);
          }
        }
      }
    }
    fin.close();
}

template <class X>
void GenStack<X>::delimCheck(char c, int lineCount){  //sorts through stack, if pair pops it
  while (true){
    char previous = myArray[top];
    if (isEmpty() == true){
      runThrough(c, lineCount);
      myArray[++top] = c;
    //  cout << "test" << endl;
      break;
    }
    if(c == ')'){
      if(previous == '('){
        pop();
      //  cout << "(test)" << endl;
        break;
      }
      else{
        runThrough(c, lineCount);
        break;
      }
    }
    if(c == ']'){
      if(previous == '['){
        pop();
      //  cout << "[test]" << endl;
        break;
      }
      else{
        runThrough(c, lineCount);
        break;
      }
    }
    if(c == '}'){
      if(previous == '{'){
        pop();
      //  cout << "{test}" << endl;
        break;
      }
      else{
        runThrough(c, lineCount);
        break;
      }
    }
    myArray[++top] = c;
    break;
  }
}

template <class X>
void GenStack<X>::runThrough(char c, int lineCount){
  //int count = 0;
  for(int i = 0; i < size(); ++i){
    bool check = false;
      if(c == ')'){
        for(int i = 0; i < size(); ++i){
          if(myArray[i] == '('){
            check = true;
            break;
          }
        }
        if(check!=true){
          cout << "error no match found for ) on line" << lineCount << endl;
          error(c);
          break;
        }
      }
      if(c == ']'){
        for(int i = 0; i < size(); ++i){
          if(myArray[i] == '['){
            check = true;
            break;
          }
        }
        if(check!=true){
          cout << "error no match found for ] on line" << lineCount << endl;
          error(c);
          break;
        }
      }
      if(c == '}'){
        for(int i = 0; i < size(); ++i){
          if(myArray[i] == '{'){
            check = true;
            break;
          }
        }
        if(check!=true){
          cout << "error no match found for } on line" << lineCount << endl;
          error(c);
          break;
        }
      }
  }
}

template <class X>
void GenStack<X>::error(char c){
  cout << "no match found for " << c << endl;
  exit(0);
}
