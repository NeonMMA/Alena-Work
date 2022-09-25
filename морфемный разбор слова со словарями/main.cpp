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
		cout << "1. ������ �����.\n2. ���������.\n3. �����.\n4. ���������. \n5. �����.\n\n";
		cin >> in_command;

		// ������ �����
		if (in_command == "1") {

			cout << "\t������� �����(\"1\" ����� ���������):\n\t";
			cin >> in_second_command;
			if (in_second_command != "1") {
				vector<string> pars = wordParsing(in_second_command);
				cout << "\t\t������ �����:\n";
				cout << "\t\t\t ���������: " << pars[0];
				cout << "\n\t\t\t ������: " << pars[1];
				cout << "\n\t\t\t ���������: " << pars[2];
				cout << "\n\n";
			}
			continue;
		}

		// ���������
		if (in_command == "2" || in_command == "3" || in_command == "4") {

			if (in_command == "2") { first_word = "���������"; second_word = "���������"; }
			if (in_command == "3") { first_word = "�����"; second_word = "������"; }
			if (in_command == "4") { first_word = "���������"; second_word = "���������"; }
			while (true) {

				cout << "\t1. ���������� ��������� " + first_word + ".\n\t2. �������� " + second_word + ". \n\t3. ������� " + second_word + ". \n\t4. ���������.\n\t";
				cin >> in_second_command;

				// ����� ���� ���������.
				if (in_second_command == "1") {
					vector <string> vect = getFromFile(in_command);

					cout << "\n";
					for (string x : vect)
						cout << "\t\t" << x << endl;

					cout << "\n";
				}

				// ����������
				if (in_second_command == "2") {
					cout << "\t\t������� ��������� ��� ����������:\n\t\t\t";
					cin >> in_third_command;
					addInFile(in_command, in_third_command);
					cout << "\n\t\t\t*���������*\n\n";
				}

				// ��������
				if (in_second_command == "3") {
					cout << "\t\t������� ��������� ��� ��������:\n\t\t\t";
					cin >> in_third_command;
					deleteFromFile(in_command, in_third_command);
					cout << "\n\t\t\t*�������*\n\n";
				}

				// �����
				if (in_second_command == "4") {
					break;
				}
			}
			continue;
		}

		// ����� �� ���������
		if (in_command == "5"){
			break;
		}
	}

	return 0;
}