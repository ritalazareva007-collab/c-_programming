#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        Node (T value): data(value), next(nullptr), prev(nullptr){}

    };
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    // конструктор по умолчанию
    Queue() = default;

    // деструктор
    ~Queue() {
        while (!empty()) {
            pop();
        }
    }
    // проверка на пустоту очереди
    bool empty() {
        return head == nullptr;
    }
    // добавление нового элемента в конец очереди
    void push(T value) {
        Node *newNode = new Node(value);
        if (empty()) {
             head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Added a new node with value: " << value << endl;
    }

    // вывод и удаление первого в очереди элемента
    void pop() {
        if (empty()) {
            throw out_of_range("Queue is empty");
        }
        cout << "deleted element:" << head->data << endl;
        Node *temp = head;
        head = head->next;


        // если не осталось ни одного элемента - зануляем хвост
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else{
            tail = nullptr;
        }
        delete temp;
    }

    // добавление узла на n-ую позицию в очередь
    void insert(int position, T value) {
        if (position == 0) {
            Node *newNode = new Node(value);
            if (empty()) {
                head = tail = newNode;
            }
            else {
                head->prev = newNode;
                newNode->next = head;
                head = newNode;
            }
            return;
        }

        Node *current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        if (current == nullptr) {
            push(value);
            return;
        }

        Node *newNode = new Node(value);
        newNode->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
        current->next = newNode;
        newNode->prev = current;
        cout << "Added a new node with value: " << value << endl;
    }
};

int main() {
    Queue<int> q;
    try {
        q.push(4);
        q.push(5);
        q.pop();
        q.push(7);
        q.push(9);
        q.push(10);
        q.pop();
        q.pop();
        q.pop();

        q.insert(1, 25);
    }catch (const exception& e) {
        cerr << e.what() << endl;
    }
}