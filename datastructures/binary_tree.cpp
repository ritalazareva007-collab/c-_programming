#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
using namespace std;

class TREE {
public:
    string word;
    int count;
    TREE * left;
    TREE * right;
    TREE() : word(""), count(0), left(nullptr), right(nullptr) {}
    TREE(string& word): word(word), count(1), left(nullptr), right(nullptr) {}

    // заполнение дерева словами, создание новых узлов
    void insert(string& the_word) {
 // сравнение слова в строке со словом в узле
        if (the_word == word) {
            count++;
        }
        else if (the_word < word) {
            if (left == nullptr) {
                left = new TREE(the_word);
            }
            else {
                left -> insert(the_word); // рекурсивно вызываем левое поддерево
            }
        }
        else {
            if (right == nullptr) {
                right = new TREE(the_word);
            }
            else {
                right -> insert(the_word); // рекурсивно вызываем правое поддерево
            }
        }
    }
//  рекурсивный вывод всех элементов дерева
    void print() {
        if (left != nullptr) {
            left -> print();
        }
        cout << word << ": " << "count = " << count << endl;
        if (right != nullptr) {
            right -> print();
        }
    }
// рекурсивное очищение дерева
    void clear() {
        if (left != nullptr) {
            left -> clear();
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            right -> clear();
            delete right;
            right = nullptr;
        }
    }
    // считываем файл и разбиваем строки на слова
    void read_file(const string& file, TREE ** root) {
        ifstream in(file);
        if (!in) {
            cerr << "file wasn't open" << endl;
            return;
        }
        // считывает слова из строки и удаляет знаки пунктуации
        string line;
        while (in >> line) {
            line.erase(std::remove_if(line.begin(), line.end(),
    [](char c) { return ispunct(static_cast<unsigned char>(c)); }),
    line.end());

            if (*root == nullptr) {
                *root = new TREE(line);
            }
            else {
                (*root) -> insert(line);
            }
        }
        in.close();
    }
    TREE *  del_elements(TREE * root, string& the_word) {
        if (root == nullptr) { // если дерево пустое возвращаем NULL
            cout << "root is NULL" << endl;
            return nullptr;
        }
        // поиск узла со значением для удаления
        if (the_word < root -> word) {
            root -> left = del_elements(root -> left, the_word);
            return root;
        }
        if (the_word > root -> word) {
            root -> right = del_elements(root -> right, the_word);
            return root;
        }
        // если слово встречалось в дереве несколько раз - уменьшаем счетчик
        if (root -> count > 1) {
            root -> count--;
            return root;
        }
        // если мы удаляем лист - узел не имеющий потомков, то просто удаляем этот узел
        if (root -> left == nullptr && root -> right == nullptr) {
            delete root;
            cout << "list has been deleted" << endl;
            return nullptr;
        }
        // если узел имеет только левого потомка, то левый потомок встает на место удаляемого родителя
        if (root -> left != nullptr && root -> right == nullptr) {
            TREE * temp = root -> left;
            delete root;
            return temp;
        }
        // если узел имеет только правого потомка, то правый потомок встанет на место удаляемого родителя
        if (root -> left == nullptr && root -> right != nullptr) {
            TREE * temp = root -> right;
            delete right;
            return temp;
        }
        // если узел имеет и правого и левого потомка, то ищется минимальный элемент из правого поддерева
        // и этот элемент становится на место удаляемого, таким образом сохраняется нужная нам структура,
        // где все элементы меньшие текущего находятся слева, а большие - справа
        if (root -> left != nullptr && root -> right != nullptr) {
            TREE * temp = root -> right;
            TREE * parent_temp = root;
            bool marker = true; // если маркер остается true, значит мы не ни разу не зашли в цикл и нужно удалить parent_temp -> right, иначе parent_temp -> left
            while (temp -> left != nullptr) {
                parent_temp = temp;
                temp = temp -> left;
                marker = false;
            }
            // заменяем значения удаляемого узла на значения минимального из правого поддерева
            root -> word = temp -> word;
            root -> count = temp -> count;
            if (marker == true) {
                parent_temp -> right = nullptr;
            }
            else {
                parent_temp -> left = nullptr;
            }
            delete temp;
            return root;
        }
    }
    int height(TREE * root) {
        if (root == nullptr) {
            return 0;
        }
        int left_height = height(root -> left);
        if (left_height == -1) {
            return -1;
        }
        int right_height = height(root -> right);
        if (right_height == -1) {
            return -1;
        }
        if (abs(left_height - right_height) > 1) {
            return -1;
        }
        return 1 + max(left_height, right_height);
    }
    void balanced(TREE * root) {
        if (height(root) != -1) {
            cout << "TREE IS BALANCED" << endl;
        }else {
            cout << "TREE IS NOT BALANCED" << endl;
        }
    }

};


int main() {
    TREE tree;
    TREE * root = nullptr;
    const string filename = "tree.txt";
    tree.read_file(filename, &root);
    if (root != nullptr) {
        root -> print();
    }
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    cout << " enter the word if you want delete some kind of word: ";
    string some_word;
    cin >> some_word;
    tree.del_elements(root, some_word);
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    tree.balanced(root);
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    if (root != nullptr) {
        root -> print();
        root -> clear();
        delete root;
        root = nullptr;
    }
    else {
        cout << "tree is empty" << endl;
    }
    return 0;
}


