#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    LinkedList<int> list;
    
    setlocale(LC_ALL, "RUSSIAN");

    string command;
    while (true) {
        cout << "0. Вывести список.\n1. Добавить элемент в начало списка.\n2. Добавить элемент в конец списка.\n3. Добавить элемент в позицию n.\n4. Удалить элемент.\n.5. Сохранить список в файл.\n6. Загрузить список из файла.\n7. Переставить элементы местами.\n8. Выход.\n";
        cin >> command;
        if (command == "0") {
            cout << "\n" << list << "\n";
        }
        else if (command == "1") {
            cout << "\tВведите элемент ";
            int a;
            cin >> a;
            list.PushFront(a);
        }
        else if (command == "2") {
            cout << "\tВведите элемент ";
            int a;
            cin >> a;
            list.PushBack(a);
        }
        else if (command == "3") {
            cout << "\tВведите элемент ";
            int a;
            cin >> a;
            cout << "\tВведите позицию ";
            int b;
            cin >> b;
            list.Insert(a, b);
        }
        else if (command == "4") {
            cout << "\tВведите элемент, который хотите удалить ";
            int b;
            cin >> b;
            list.Remove(b);
        }
        else if (command == "5") {
            // save
            cout << "\tВведите адресс файла ";
            string b;
            cin >> b;
            ofstream fout(b);
            fout << list;
            fout.close();
        }
        else if (command == "6") {
            //load
            cout << "\tВведите адресс файла ";
            string b;
            cin >> b;
            ifstream fin(b);
            fin >> list;
            fin.close();
        }
        else if (command == "7") {
            cout << "\tВведите позицию первого элементa ";
            int a;
            cin >> a;
            cout << "\tВведите позицию второго элемента ";
            int b;
            cin >> b;
            list.Swap(a, b);
        }
        else if (command == "8") {
            break;
        }
        else { cout << "неверная команда"; }

    }
    
}
