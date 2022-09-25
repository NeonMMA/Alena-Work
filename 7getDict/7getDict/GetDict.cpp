#include "GetDict.h"

map<string, int> GetDict(string fileName)
{
    map<string, int> myMap;
    ifstream fin(fileName);
    string temp = "";
    char tt;
    while (fin.get(tt)) {
        if (tt == ' ') {
            myMap[temp] += 1;
            temp = "";
        }
        if (tt == '\n') tt = '.';
        if (tt == '.' || tt == ',' || tt == ':' || tt == ';' || tt == '-') continue;
        else {
            temp += tt;
        }
    }
    myMap[temp] += 1;
    fin.close();

    return myMap;
}