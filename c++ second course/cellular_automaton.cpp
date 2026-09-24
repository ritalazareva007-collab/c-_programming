#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
// задание на реализацию клеточного автомата по правилу 104

int Rule_104(int data) {
    if (data == 0){return 0;}
    if (data == 1){return 0;}
    if (data == 10){return 0;}
    if (data == 11){return 1;}
    if (data == 100){return 0;}
    if (data == 101){return 1;}
    if (data == 110){return 1;}
    if (data == 111){return 0;}
}

void Print(const std::vector<int>& states) {
    for (int state : states) {
        if (state == 1) {
            std::cout << "*";
        }else {
            std::cout << " ";
        }
    }
    // для перехода курсора в начало строки
    std::cout << "\r" << std::flush;
    // задержка для эффекта анимации
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Insert(std::vector<int>& states, std::vector<int>& new_states, int length) {
    for (int i = 0; i < length; ++i) {
        int left = (i == 0) ? states.back() : states[i - 1];
        int center = states[i];
        int right = (i == length - 1) ? states.front() : states[i + 1];

        int data = left * 100 + center * 10 + right;

        new_states[i] = Rule_104(data);
    }
}

int main() {
    // задаем длину
    int length = 120;
    int steps = 50;
    std::vector<int> states(length);
    std::vector<int> new_states(length);

    // источник случайности - случайный генератор
    std::random_device rd;
    // сам генератор псевдослучайных чисел
    std::mt19937 gen(rd());
    // указываем, что нам нужны только числа 0 и 1
    std::uniform_int_distribution<> distribut(0, 1);

    for (int i = 0; i < length; ++i) {
        states[i] = distribut(gen); // добавляем случайное число в вектор
    }

    Print(states);
    for (int i = 0; i < steps; ++i) {
        if (i % 2 == 0) {
            Insert(states, new_states, length);
            Print(new_states);
        }
        else {
            Insert(new_states, states, length);
            Print(new_states);
        }
    }
    return 0;
}