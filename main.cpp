#include "GenStack.h"
#include "FileReader.h"
#include <stack>

using namespace std;

int main(int argc, char **argv){

  FileReader counter;








  GenStack<char> myStack(counter.delimCount("GenStack.h"));

  myStack.delimFill("GenStack.h");

  if(myStack.isEmpty()){
    cout << "syntax is good" << endl;
  }
  cout << myStack.size() << endl;

  for(int i = 0; i < 100; ++i){
    cout << myStack.pop() << endl;
  }

   cout << myStack.size() << endl;





 //delete myStack;
  return 0;
}
