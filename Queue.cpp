#include <iostream>
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
        head->prev = nullptr;

        // если не осталось ни одного элемента - зануляем хвост
        if (head == nullptr) {
            tail = nullptr;;
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
        }

        Node *current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }

        Node *newNode = new Node(value);
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
        newNode->prev = current;
    }
};

int main() {
    Queue<int> q;
    q.push(4);
    q.push(5);
    q.pop();
    q.push(7);
    q.push(9);
    q.push(10);
    q.insert(3, 25);
}