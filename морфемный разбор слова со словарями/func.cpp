#include "header.h"



vector<string> getFromFile(string in_command) {

	vector <string> vect;

	ifstream fin(in_command + ".txt", ios::binary);

	char l;
	string res;
	
	// если открылся файл
	if (fin) {
		while (fin >> l) {

			// если встретили разделитель
			if (l == '%') {
				vect.push_back(res);
				res = "";
			}
			else res += l;
		}
	}

	if (res != "") vect.push_back(res);

	return vect;
}


void addInFile(string in_command, string in_third_command) {
	ofstream fout(in_command + ".txt", ios::binary | ios::app);
	fout << "%"<< in_third_command;
	fout.close();
}

void deleteFromFile(string in_command, string in_third_command) {
	vector <string> wordArr = getFromFile(in_command);

	vector<string>::iterator index = find(wordArr.begin(), wordArr.end(), in_third_command);

	if (index - wordArr.begin() != wordArr.size()) {
		wordArr.erase(index);
	}

	ofstream fout(in_command + ".txt", ios::binary | ios::out);
	fout << wordArr[0];
	for (auto i = wordArr.begin() + 1; i < wordArr.end(); i ++) {
		fout << "%" << wordArr[i - wordArr.begin()];
	}
	fout.close();
}

vector<string> wordParsing(string in_second_command) {
	
	vector<string> prefixes = getFromFile("2");
	vector<string> roots	= getFromFile("3");
	vector<string> endings  = getFromFile("4");
	vector<string> result = {"1", "2", "3"};
	
	// сортируем, чтобы проще было ориентироваться
	sort(prefixes.begin(), prefixes.end());
	sort(roots.begin(), roots.end());
	sort(endings.begin(), endings.end());

	string pref = "";
	string root = "";
	string ending = "";

	int wordSize = in_second_command.length();

	for (int i = 0; i < wordSize; i++) {
		vector<string>::iterator pref_iter = find(prefixes.begin(), prefixes.end(), in_second_command.substr(0, i + 1));
		if (pref_iter - prefixes.begin() != prefixes.size()) {
			pref = prefixes[pref_iter - prefixes.begin()];

			// если после приставки еще осталось место
			if (i + 1 < wordSize) {
				
				for (int j = i + 1; j < wordSize; j++) {
					vector<string>::iterator root_iter = find(roots.begin(), roots.end(), in_second_command.substr(i + 1, j - i));
				
					if (root_iter - roots.begin() != roots.size()) {
						root = roots[root_iter - roots.begin()];

						// если после корня еще есть место
						if (j + 1 < wordSize) {
							for (int k = j + 1; k < wordSize; k++) {
								vector<string>::iterator ending_iter = find(endings.begin(), endings.end(), in_second_command.substr(j + 1, k - j));

								if (ending_iter - endings.begin() != endings.size()) {
									ending = endings[ending_iter - endings.begin()];
								}
							}
						}
					}

				}
			}
			
		}
	}

	result[0] = pref;
	result[1] = root;
	result[2] = ending;
	return result;
}