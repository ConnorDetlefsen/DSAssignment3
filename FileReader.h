#include <iostream>
#include <fstream> //file streams


using namespace std;

class FileReader{
  public:


    int delimCount(string fileName);

    GenStack<char> delimStack();
};


int FileReader::delimCount(string fileName){  //checks if syntax adds up
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
          delimStack.push(c);
        }
        else if(c == ')'){
          delimStack.push(c);
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

    cout << "rectangle : " << rectangled  << endl;   //count works but for some reason output of true or false is weird
    cout << "curly: " << curly << endl;
    cout << "curved : " << curved << endl;

    count = curved + curly + rectangled;

    return count;
}
