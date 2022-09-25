#include <iostream>
#include <locale>
#include "header.h"


using namespace std;

string in_command = "";
string in_second_command = "";
string in_third_command = "";
string first_word = "";
string second_word = "";


int main() {

	setlocale(LC_ALL, "Russian");

	while (true) {
		cout << "1. Разбор слова.\n2. Приставки.\n3. Корни.\n4. Окончания. \n5. Выход.\n\n";
		cin >> in_command;

		// Разбор слова
		if (in_command == "1") {

			cout << "\tВведите слово(\"1\" чтобы вернуться):\n\t";
			cin >> in_second_command;
			if (in_second_command != "1") {
				vector<string> pars = wordParsing(in_second_command);
				cout << "\t\tРазбор слова:\n";
				cout << "\t\t\t приставка: " << pars[0];
				cout << "\n\t\t\t корень: " << pars[1];
				cout << "\n\t\t\t окончание: " << pars[2];
				cout << "\n\n";
			}
			continue;
		}

		// Приставки
		if (in_command == "2" || in_command == "3" || in_command == "4") {

			if (in_command == "2") { first_word = "приставки"; second_word = "приставку"; }
			if (in_command == "3") { first_word = "корни"; second_word = "корень"; }
			if (in_command == "4") { first_word = "окончания"; second_word = "окончание"; }
			while (true) {

				cout << "\t1. Посмотреть имеющиеся " + first_word + ".\n\t2. Добавить " + second_word + ". \n\t3. Удалить " + second_word + ". \n\t4. Вернуться.\n\t";
				cin >> in_second_command;

				// Вывод всех приставок.
				if (in_second_command == "1") {
					vector <string> vect = getFromFile(in_command);

					cout << "\n";
					for (string x : vect)
						cout << "\t\t" << x << endl;

					cout << "\n";
				}

				// Добавление
				if (in_second_command == "2") {
					cout << "\t\tВведите приставку для добавления:\n\t\t\t";
					cin >> in_third_command;
					addInFile(in_command, in_third_command);
					cout << "\n\t\t\t*добавлена*\n\n";
				}

				// Удаление
				if (in_second_command == "3") {
					cout << "\t\tВведите приставку для удаления:\n\t\t\t";
					cin >> in_third_command;
					deleteFromFile(in_command, in_third_command);
					cout << "\n\t\t\t*удалена*\n\n";
				}

				// Выход
				if (in_second_command == "4") {
					break;
				}
			}
			continue;
		}

		// Выход из программы
		if (in_command == "5"){
			break;
		}
	}

	return 0;
}