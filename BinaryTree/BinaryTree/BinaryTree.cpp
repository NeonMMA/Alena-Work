#include "BinaryTree.h"

int main()
{
	BinaryTree<int> tree;
	setlocale(LC_ALL, "RUSSIAN");

	tree.Insert(5);
	tree.Insert(7);
	tree.Insert(3);
	tree.Insert(2);
	tree.Insert(4);
	tree.Insert(1);
	tree.Output();
	cout << "\n";
	tree.FormingData();

	string command;
	while (true) {
		cout << "0. Вывести дерево.\n1. Добавить вершину.\n2. Удалить вершину.\n3. Сохранить дерево в файл.\n4. Загрузить дерево из файла.\n5. Обход дерева в глубину.\n6. Обход дерева в ширину.\n7. Сортировка с помощью дерева по возрастанию.\n8. Сортировка с помощью дерева по убыванию.\n9. Выход.\n";
		cin >> command;
		if (command == "0") {
			if (tree.Empty()) cout << "";
			else
				tree.Output();
		}
		else if (command == "1") {
			cout << "\tВведите элемент ";
			int a;
			cin >> a;
			tree.Insert(a);
		}
		else if (command == "2") {
			cout << "\tВведите элемент ";
			int a;
			cin >> a;
			tree.Remove(a);
		}
		else if (command == "3") {
			// save
			cout << "\tВведите адресс файла ";
			string b;
			cin >> b;
			ofstream fout(b);
			fout << tree;
			fout.close();
		}
		else if (command == "4") {
			//load
			cout << "\tВведите адресс файла ";
			string b;
			cin >> b;
			ifstream fin(b);
			fin >> tree;
			fin.close();
		}
		else if (command == "5") {
			cout << "\n";
			tree.DeepOut();
			cout << "\n";
		}
		else if (command == "6") {
			cout << "\n";
			tree.WideOut();
			cout << "\n";
		}
		else if (command == "7") {
			vector<int> tt = tree.RoundLrootR();
			cout << "\n";
			for (int i = 0; i < tt.size(); ++i) {
				cout << tt[i] << " ";
			}
			cout << "\n";
		}
		else if (command == "8") {
			vector<int> tt = tree.RoundRrootL();
			cout << "\n";
			for (int i = 0; i < tt.size(); ++i) {
				cout << tt[i] << " ";
			}
			cout << "\n";
		}
		else if (command == "9") {
			break;
		}
		else { cout << "неверная команда"; }
	}

}
