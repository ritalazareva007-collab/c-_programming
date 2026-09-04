// пример создания односвязного списка
// с помощью умных указателей

#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class ForwardList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& value, std::unique_ptr<Node>(nxt)):
        data(value), next(std::move(nxt)){}
    };
    std::unique_ptr<Node> head;

public:
    // добавление вперед нового элемента
    void push_front(const T& value) {
        head = std::make_unique<Node>(value, std::move(head));
    }
    // удаление элементак спереди
    void pop_front() {
        head = std::move(head->next);
    }
    // вывод первого элемента
    const T& front() {
        return head->data;
    }
    // проверка на пустоту
    bool empty() {
        return head == nullptr;
    }

    ForwardList() = default;

    ~ForwardList() {
        while (!empty()) {
            pop_front();
        }
        cout << "All nodes was deleted" << endl;
    }
};

int main() {
    ForwardList<int> list;
    list.push_front(7);
    list.push_front(8);
    list.push_front(9);
    int el1 = list.front();
    list.pop_front();
    int el2 = list.front();
    list.pop_front();
    int el3 = list.front();
    cout << el1 << " " << el2 << " " << el3 << endl;
}
