
#include <iostream>
#include <map>
#include <fstream>
#include <iterator>
#include "GetDict.h"

using namespace std;

int main()
{
    map<string, int> myMap;
    myMap = GetDict("text.txt");
    auto iter = myMap.begin();
    for (iter; iter != myMap.end(); ++iter) {
        cout << iter->first << ": " << iter->second << "\n";
    }
}

