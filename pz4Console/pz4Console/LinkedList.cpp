#include <iostream>
#include "LinkedList.h"
#include <vector>

using namespace std;

template<typename It>
std::vector<typename It::value_type> merge(const It begin, const It mid, const It end)
{
    std::vector<typename It::value_type> v;
    It it_l{ begin }, it_r{ mid };
    const It it_mid{ mid }, it_end{ end };

    while (it_l != it_mid && it_r != it_end)
    {
        v.push_back((*it_l <= *it_r) ? *it_l++ : *it_r++);
    }

    v.insert(v.end(), it_l, it_mid);
    v.insert(v.end(), it_r, it_end);

    return std::move(v);
}

template<typename It>
void merge_sort(It begin, It end)
{
    auto size = std::distance(begin, end);
    if (size < 2)
        return;

    auto mid = std::next(begin, size / 2);
    merge_sort(begin, mid);
    merge_sort(mid, end);

    auto&& v = merge(begin, mid, end);
    std::move(v.cbegin(), v.cend(), begin);
}

int main()
{
    LinkedList<int> list;
    
    setlocale(LC_ALL, "RUSSIAN");

    string command;
    while (true) {
        cout << "0. Вывести список.\n1. Добавить элемент в начало списка.\n2. Добавить элемент в конец списка.\n3. Добавить элемент в позицию n.\n4. Удалить элемент.\n.5. Сохранить список в файл.\n6. Загрузить список из файла.\n7. Переставить элементы местами.\n8. Merge Sort.\n9. Выход.\n";
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
            merge_sort(list.begin(), list.end());
        }
        else if (command == "9") {
            break;
        }
        else { cout << "неверная команда"; }

    }
    
}
