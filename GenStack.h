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
    void delimFill(string fileName); //main error check
    void delimCheck();  //final error check
    void exitProgram();

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
  cout << "stack deleted" << endl;
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
                            //looking back on it, having both of these is kinda unnecessary
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
void GenStack<X>::delimFill(string fileName){  //this is main check function for missing delimiters
  int firstQuote = 0;
  int endQuote = 0;

  ifstream fin; //creation of ifstream class object
  string line = "";
  int lineCount = 0;

  fin.open(fileName);
    while (fin) {     //reads in input from text file given from user
      getline(fin, line);
      lineCount++;
      for(int i = 0; i < line.length(); ++i){   //for each letter in file line
        /*
        if(line[i] == '/' && line[i+1] == '/')    //makes sure the delimiter isnt in quotes or a comment
          break;                                      //this was messing it up so i took it ou
        if(line[i] == '\'' || line[i] == '\"'){
          firstQuote = i;
          for(int f = firstQuote+1; f < line.length(); ++f){
            if(line[f] == '\'' || line[f] == '\"'){
              endQuote = f;
          }
        }
      }
        if(i <= endQuote && i >= firstQuote)
          continue; */
        //else{
          if(isFull() == true){   //check if full before attempting to push /insert
            expand(); //expands stack by 10
          }
          char c = line[i];
          char previous = peek();
          if((c == '(') || (c == ')') || (c == '[') || (c == ']') || (c == '{') || (c == '}')){
            if((peek() == '(') && (c == ')')){
              pop();
            }
            else if((peek() == '[') && (c == ']')){
              pop();
            }
            else if((peek() == '{') && (c == '}')){
              pop();
            }
            else if((peek() == '(') && ((c == ']') || (c == '}'))) {
              cout << "error missing ')' on line: " << lineCount << endl;
              exitProgram();
              break;
            }
            else if((peek() == '[') && ((c == ')') || (c == '}'))){
              cout << "error missing ']' on line: " << lineCount << endl;
              exitProgram();
              break;
            }
            else if((peek() == '{') && ((c == ')') || (c == ']')))  {
              cout << "error missing '}' on line: " << lineCount << endl;
              exitProgram();
              break;
            }
            else if((isEmpty() == true) && ((c == ')') || (c == ']') || (c == '}'))) {
              cout << "error on line: " << lineCount << " extra " << c << endl;
              exitProgram();
              break;
            }
            else if((c == '(') || (c == '[') || (c == '{')){
              push(c);
              }
          //  } //closing delim for quote check part
          }
        }
    }
    fin.close();
}

template <class X>
void GenStack<X>::delimCheck(){  //final check after file has been run through,
  if(isEmpty() == false){
    char previous = peek();
    cout << "missing matching pair for " << previous << endl;
  }
  if(isEmpty() == true){
    cout << "no syntax errors" << endl;
  }
}

template <class X>  //exits program, used for when an error is found
void GenStack<X>::exitProgram(){
  exit(0);
}
