#include <iostream>
#include <fstream> //file streams

using namespace std;

class FileReader{
  public:


    int delimCount(string fileName);

    GenStack<char> delimStack;

};

int FileReader::delimCount(string fileName){  //counts delims in file, used to make first stack
  int curved = 0;
  int curly = 0;
  int rectangled = 0;
  int count = 0;

  ifstream fin; //creation of ifstream class object
  string line = "";

  fin.open(fileName);
    while (fin) {     //reads in input from text file given from user
      getline(fin, line);
      for(int i = 0; i < line.length(); ++i){   //finds count of each letter
        char c = line[i];
        if(c == '('){
          curved++;
        }
        else if(c == ')'){
          curved++;
        }
        else if(c == '[')
          rectangled++;
        else if(c == ']')
          rectangled++;
        else if(c == '{')
          curly++;
        else if(c == '}')
          curly++;
        }
      }
    fin.close();
    count = curved + curly + rectangled;

    return count;
}
