#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


vector<string> getFromFile(string in_command);

void addInFile(string in_command, string in_third_command);

void deleteFromFile(string in_command, string in_third_command);

vector<string> wordParsing(string in_second_command);
