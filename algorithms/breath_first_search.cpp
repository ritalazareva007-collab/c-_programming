#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
// Алгоритм поиска в ширину по книге грокаем алгоритмы
// Осуществляем поиск продавца манго мреди контактов друзей социальной сети

//фукция проверки является ли человек продавцом манго, глупая, но для быстрой проверки алгоритма пойдет
bool is_seller(std::string name) {
    if (!name.empty() && name.back() == 'r') {
        return true;
    }
    return false;
}
// поиск в ширину 
bool search(const std::string& name, const std::unordered_map<std::string, std::vector<std::string>>& graph) {
    std::queue<std::string> q;
    q.push(name);
    std::unordered_map<std::string, bool> s;
    s[name] = true;

    while (!q.empty()) {
        std::string person = q.front();
        q.pop();
        if (is_seller(person)) {
            std::cout << person << " is seller mango!" << std::endl;
            return true;
        }
        if (graph.count(person)){
            for (const std::string& friend_name : graph.at(person)) {
                if (!s[friend_name]) {
                    s.insert({friend_name, true});
                    q.push(friend_name);
                }
            }
        }
    }
    std::cout << "No mango seller found." << std::endl;
    return false;
}

int main() {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    graph["Alice"] = {"Peggi"};
    graph["You"] = {"Alice", "Kler", "Bob"};
    graph["Bob"] = {"Anuge"};
    graph["Kler"] = {"Tom", "Jhon"};
    graph["Anuge"] = {};
    graph["Tom"] = {};
    graph["Jhon"] = {};
    graph["Peggi"] = {};

    std::cout << search("You", graph) << std::endl;
}
