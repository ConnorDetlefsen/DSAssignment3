#include "GenStack.h"
#include "FileReader.h"
#include <stack>

using namespace std;

int main(int argc, char **argv){
  string filename = argv[1];

  FileReader counter;
  GenStack<char> myStack(counter.delimCount(filename));  //initializes stack to the count of how many delimiters are in the file
  myStack.delimFill(filename); //checks for missing delimiters
  myStack.delimCheck(); //last check, if opening delimiter left = error, if stack isEmpty = no errors

  string runAgain;
  while(true){
    cout << "do you want to test another file? enter YES or NO, in all capitals" << endl;
    cin >> runAgain;
    if(runAgain == "NO"){
      break;
    }
    else if (runAgain == "YES"){
      cout << "enter filename" << endl;
      cin >> filename;
      GenStack<char> myStack(counter.delimCount(filename));  //initializes stack to the count of how many delimiters are in the file
      myStack.delimFill(filename); //checks for missing delimiters
      myStack.delimCheck(); //last check, if opening delimiter left = error, if stack isEmpty = no errors
    }
    else{
      cout << "enter valid input" << endl;
    }
  }







 //delete myStack;
  return 0;
}
