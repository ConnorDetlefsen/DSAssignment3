#include "GenStack.h"
#include "FileReader.h"
#include <stack>

using namespace std;

int main(int argc, char **argv){

  GenStack<char> myStack(3);
  GenStack<int> myIntStack(5);

  /*myStack.push('c');
  myStack.push('o');
  myStack.push('n');
  cout << myStack.maxSize() << endl; */

  FileReader test;
//  cout << test.delimCount("test.txt") << endl;

  GenStack<char> testStack(test.delimCount("test.txt")); //creates stack to size of count of delims
  cout << testStack.maxSize() << endl;




 //delete myStack;
  return 0;
}
