// определить является ли полиндромом односвязный список

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node {
private:
    T _value;
    Node* _next;

public:

    Node()
    {
        _value = T();
        _next = nullptr;
    }

    Node(T value)
    {
        _value = value;
        _next = this;
    }

    Node(T value, Node* next)
    {
        _value = value;
        _next = next;
    }

    ~Node()
    {
        _next = nullptr;
        _value = T();
    }

    T GetValue()
    {
        return _value;
    }

    Node* GetNext()
    {
        return _next;
    }

    void SetValue(T value)
    {
        _value = value;
    }

    void SetNext(Node* next)
    {
        _next = next;
    }

};

template <typename T>
class OneLinkedList {
private:

    friend class Node<T>;

public:
    OneLinkedList()
    {
        _tail = _head = new Node<T>(T(), nullptr);
        size = 0;
    }

    ~OneLinkedList()
    {
        while (size > 0)
        {  
            this->Delete(0);
        }
        delete(_head);
        _head = _tail = nullptr;
    }

    void PushBack(T value) 
    {
        Node<T>* temp = new Node<T>(value);
        _tail->SetNext(temp);
        _tail = temp;
        size++;
    }

    void PushFront(T value)
    {
        Node<T>* temp = new Node<T>(value, _head->GetNext());
        _head->SetNext(temp);
        size++;
    }

    void Insert(T value, size_t num)
    {
        if (num == 0) {
            this->PushFront(value);
            return;
        }
        if (num == size) {
            this->PushBack(value);
            return;
        }
        if (num > size) return;

        Node<T>* iter = _head;
        for (int i = 0; i < num; ++i) {
            iter = iter->GetNext();
        }
        Node<T>* temp = new Node<T>(value, iter->GetNext());
        iter->SetNext(temp);
        size++;
    }

    void Delete(int num)
    {
        if (num > size) return;

        Node<T>* iter = _head;
        for (int i = 0; i < num; ++i) {
            iter = iter->GetNext();
        }
        Node<T>* temp = iter->GetNext();
        iter->SetNext((temp == nullptr)? nullptr : temp->GetNext());
        delete(temp);
        size--;
    }

    void Swap(int first, int sec)
    {
        Node<T>* iterF = _head;
        Node<T>* iterS = _head;
        for (int i = 0; i <= first; ++i) {
            iterF = iterF->GetNext();
        }
        for (int i = 0; i <= sec; ++i) {
            iterS = iterS->GetNext();
        }
        T f = iterF->GetValue();
        T s = iterS->GetValue();
        iterF->SetValue(s);
        iterS->SetValue(f);
    }

    Node<T>* GetHead() { return _head; }
    Node<T>* GetTail() { return _tail; }
    int GetSize() { return size; }

private:
    Node<T>* _head = nullptr;
    Node<T>* _tail = nullptr;
    int size = 0;
};

template <typename T>
ostream& operator<<(ostream& out, OneLinkedList<T>& other)
{
    Node<T>* iter = other.GetHead();
    while (iter != other.GetTail()) {
        iter = iter->GetNext();
        out << iter->GetValue() << " ";
    }

    return out;
}

template <typename T>
ofstream& operator<<(ofstream& fout, OneLinkedList<T>& other)
{
    Node<T>* iter = other.GetHead();
    fout << other.GetSize() << "\n";
    while (iter != other.GetTail()) {
        iter = iter->GetNext();
        fout << iter->GetValue() << "\n";
    }

    return fout;
}

template <typename T>
ifstream& operator>>(ifstream& in, OneLinkedList<T>& other)
{
    int n;
    in >> n;

    while (other.GetSize() > 0) {
        other.Delete(0);
    }
    T tt;
    for (size_t i = 0; i < n; ++i) {
        in >> tt;
        other.PushBack(tt);
    }
    return in;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    OneLinkedList<int> LL;
    string command;
    while (true) {
        cout << "0. Вывести список.\n1. Добавить элемент в начало списка.\n2. Добавить элемент в конец списка.\n3. Добавить элемент в позицию n.\n4. Удалить элемент.\n.5. Сохранить список в файл.\n6. Загрузить список из файла.\n7. Переставить элементы местами.\n8. Выход.\n";
        cin >> command;
        if (command == "0") {
            cout << "\n" << LL << "\n";
        }
        else if (command == "1") {
            cout << "\tВведите элемент ";
            int a;
            cin >> a;
            LL.PushFront(a);
        }
        else if (command == "2") {
            cout << "\tВведите элемент ";
            int a;
            cin >> a;
            LL.PushBack(a);
        }
        else if (command == "3") {
            cout << "\tВведите элемент ";
            int a;
            cin >> a;
            cout << "\tВведите позицию ";
            int b;
            cin >> b;
            LL.Insert(a, b);
        }
        else if (command == "4") {
            cout << "\tВведите позицию ";
            int b;
            cin >> b;
            LL.Delete(b);
        }
        else if (command == "5") {
            // save
            cout << "\tВведите адресс файла ";
            string b;
            cin >> b;
            ofstream fout(b);
            fout << LL;
            fout.close();
        }
        else if (command == "6") {
            //load
            cout << "\tВведите адресс файла ";
            string b;
            cin >> b;
            ifstream fin(b);
            fin >> LL;
            fin.close();
        }
        else if (command == "7") {
            cout << "\tВведите позицию первого элементa ";
            int a;
            cin >> a;
            cout << "\tВведите позицию второго элемента ";
            int b;
            cin >> b;
            LL.Swap(a, b);
        }
        else if (command == "8") {
            break;
        }
        else { cout << "неверная команда"; }

    }

}


