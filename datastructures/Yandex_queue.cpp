#include <iostream>
#include <stack>
#include <sstream>

// реализация очереди через два стека
// из левого стека вынимаются элементы пока он не опустеет,
// в правый стек добавляются элементы.
// когда левый стек опустеет, все элементы из правого переходят в левый


class Queue {
private:
    std::stack<int> left;
    std::stack<int> right;
public:
    // добавление элемента со сзначением n
    void push(int n) {
        right.push(n);
        std::cout << "ok" << std::endl;
    }
    // удаление и вывод на экран
    void pop() {
        if (left.empty() && right.empty()) {
            std::cout << "error" << std::endl;
            return;
        }
        if (left.empty()) {
            while (!right.empty()) {
                left.push(right.top());
                right.pop();
            }
        }
        std::cout << left.top() << std::endl;
        left.pop();
    }
    // вывод первого в очереди элемента, без удаления
    void front() {
        if (left.empty() && right.empty()) {
            std::cout << "error" << std::endl;
            return;
        }
        if (left.empty()) {
            while (!right.empty()) {
                left.push(right.top());
                right.pop();
            }
        }
        std::cout << left.top() << std::endl;
    }
    // размер всей очереди
    void size() {
        std::cout << left.size() + right.size() << std::endl;
    }
    // очищение очереди
    void clear() {
        while (!left.empty()) {
            left.pop();
        }
        while (!right.empty()) {
            right.pop();
        }
        std::cout << "ok" << std::endl;
    }
    // завершение программы
    void exit() {
        std::cout << "bye" << std::endl;
    }

};


int main() {
    Queue q;

    std::string command;
    while (std::cin >> command) {
        if (command == "push") {
            int value;
            std::cin >> value;
            q.push(value);
        }
        if (command == "pop") {
            q.pop();
        }
        if (command == "front") {
            q.front();
        }
        if (command == "size") {
            q.size();
        }
        if (command == "clear") {
            q.clear();
        }
        if (command == "exit") {
            q.exit();
            break;
        }
    }
    return 0;
}