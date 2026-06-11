#include <chrono>
#include <iostream>
using namespace std;
enum colors{RED, BLACK};
class TREE {
public:
    int data;
    colors color;
    TREE *left, *right, *parent;
    TREE (): data(0), color(RED), left(nullptr), right(nullptr), parent(nullptr){}
    explicit TREE(int data): data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr){}
    ~TREE()  {delete left; delete right; left = nullptr; right = nullptr;};

    // левый поворот
    void left_turn(TREE* x, TREE** root) {
        TREE* y = x -> right;
        x -> right = y -> left;

        if (y -> left != nullptr) {
            y -> left -> parent = x;
        }
        y -> parent = x -> parent;

        if (x->parent == nullptr) {
            *root = y;
        } else if (x == x -> parent -> left) {
            x-> parent -> left = y;
        } else {
            x-> parent-> right = y;
        }

        y -> left = x;
        x -> parent = y;
    }
    // правый поворот
    void right_turn(TREE* x, TREE** root) {
        TREE* y = x->left;
        x->left = y->right;

        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;

        if (x->parent == nullptr) {
            *root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }
    void balance(TREE ** root, TREE * node) {
        // пока есть дисбаланс
        while (node -> parent != nullptr && node -> parent -> color == RED) {
            TREE *prev = node -> parent;
            TREE *last_parent = prev -> parent;
            if (prev == last_parent -> left) {
                TREE * prev_2 = last_parent -> right;
                // если второй потомок красный - перекрашиваем
                if (prev_2 != nullptr && prev_2 -> color == RED ) {
                    prev -> color = BLACK;
                    prev_2 -> color = BLACK;
                    last_parent -> color = RED;
                    node = last_parent; // поднимаемся выше
                }// если второй потомок - черный
                else {
                    // если узел - правый потомок - делаем левый поворот
                   if (node == prev -> right) {
                       left_turn(prev, root);
                       node = prev;
                       prev = node -> parent;
                   }// правый поворот вокруг предыдущего потомка
                    prev -> color = BLACK;
                    last_parent -> color = RED;
                    right_turn(last_parent, root);
                    break;
                }
            }
            else {
                TREE * prev_2 = last_parent -> left;
                if (prev_2 != nullptr && prev_2 -> color == RED ) {
                    prev -> color = BLACK;
                    prev_2 -> color = BLACK;
                    last_parent -> color = RED;
                    node = last_parent; // поднимаемся выше
                }// если потомок - черный
                else {
                    // если узел - левый потомок - делаем правый поворот
                    if (node == prev -> left) {
                        right_turn(prev, root);
                        node = prev;
                        prev = node -> parent;
                    }// левый поворот вокруг предыдущего потомка
                    prev -> color = BLACK;
                    last_parent -> color = RED;
                    left_turn(last_parent, root);
                }
            }
        }
        (*root) -> color = BLACK;
    }
    // заполнение дерева значениями
    void insert(int value, TREE ** root) {
        if (*root == nullptr) {
            *root = new TREE(value);
            (*root) -> color = BLACK; // корень всегда черный
            return;
        }
        TREE * current = * root;
        TREE * previous = nullptr;
        while (current != nullptr) {
            previous = current;
            if (value < current -> data) {
                current = current -> left;
            }
            else if (value > current -> data) {
                current = current -> right;
            }
            else {
                return;
            }
        }
        TREE * temp = new TREE(value);
        temp -> parent = previous;
        if (value < previous -> data) {
            previous -> left = temp;
        }
        else {
            previous -> right = temp;
        }
        balance(root, temp);
    }
    // вывод дерева на экран
    void print(TREE *root) {
        if (root == nullptr)
            return;
        print(root -> left);
        cout << root -> data << " - " << (root -> color == RED ? "RED" : "BLACK") << endl;
        print(root -> right);
    }


    void delete_element(TREE ** root, int value) {
        if (*root == nullptr) {
            return;
        }
        TREE * current = * root;
        // поиск удаляемого элемента в дереве
        while (current -> data != value) {
            if (value < current -> data) {
                current = current -> left;
            }
            else{
                current = current -> right;
            }
        }

        // если у удаляемого нет потомков и это корень
        if (current -> left == nullptr && current -> right == nullptr && current == *root) {
            *root = nullptr;
            delete current;
            return;
        }

        // если у удаляемого узла нет потомков
        if (current -> left == nullptr && current -> right == nullptr) {
            if (current -> parent -> left == current) {
                current -> parent -> left = nullptr;
            }
            else {
                current -> parent -> right = nullptr;
            }
            delete current;
        }
        // если у удаляемого узла один потомок - левый
        else if (current -> left != nullptr && current -> right == nullptr) {
            if (current == *root) {
                *root = current -> left;
                (*root) -> parent = nullptr;
                (*root) -> color = BLACK;
                delete (* root) -> left;
                return;
            }
            if (current -> parent -> left == current) {
                TREE * temp = current -> left;
                current -> data = temp -> data;
                current -> color = temp -> color;
                current -> left = nullptr;
                delete temp;
                balance(root, current);
            }
            else {
                TREE * temp = current -> left;
                current -> data = temp -> data;
                current -> color = temp -> color;
                current -> left = nullptr;
                delete temp;
                balance(root, current);
            }
        }
        // если у удаляемого узла один потомок - правый
        else if (current -> left == nullptr && current -> right != nullptr) {
            if (current == *root) {
                *root = current -> right;
                (*root) -> parent = nullptr;
                (*root) -> color = BLACK;
                delete (* root) -> right;
                return;
            }
            if (current -> parent -> left == current) {
                TREE * temp = current -> right;
                current -> data = temp -> data;
                current -> color = temp -> color;
                current -> right = nullptr;
                delete temp;
                balance(root, current);
            }
            else {
                TREE * temp = current -> right;
                current -> data = temp -> data;
                current -> color = temp -> color;
                current -> right = nullptr;
                delete temp;
                balance(root, current);
            }
        }
        // если у удаляемого узла есть оба потомка
        else {
            bool current_color = current -> color == BLACK;// запоминаем цвет удаляемой вершины
            // находим самую левую вершину правого поддерева и перемещаем её на место удаленной
            TREE * temp = current -> right;
            while (temp -> left != nullptr) {
                temp = temp -> left;
            }
            // перемещаем наименьший из правого поддерева на место удаляемого
            current -> data = temp -> data;
            current -> color = temp -> color;
            // связываем новый узел с правым поддеревом и удаляем temp
            if (current -> right != temp) {
                temp -> parent -> left = nullptr;
            }
            else {
                current -> right = nullptr;
            }
            TREE * node = current;
            delete temp;

            if (current_color == true) {
                //если текущая вершина - корень, ничего не делаем
                if (node -> parent == nullptr) {
                    return;
                }
                // если текущая вершина - левая
                if (node -> parent -> left == node) {
                    TREE * brother = node -> parent -> right;
                    // если брат красный
                    if (brother -> color == RED) {
                        left_turn(node -> parent , root);
                        brother -> color = BLACK;
                        brother -> left -> color = RED;
                    }
                    // если брат чёрный
                    else {
                        // если у брата два черных потомка
                        if  ((brother -> left == nullptr || brother -> left -> color == BLACK) &&
                            (brother -> right == nullptr || brother -> right -> color == BLACK))  {
                            brother -> color = RED;
                            node -> parent -> color = BLACK;
                            }
                        // у брата правый потомок - черный, а левый - красный
                        if ((brother -> left != nullptr || brother -> left -> color == RED) &&
                            brother -> right == nullptr && brother -> right -> color == BLACK) {
                            brother -> color = RED;
                            brother -> left -> color = BLACK;
                            right_turn(brother, root);
                            brother = node -> parent -> right;
                            }
                        // если у брата правый потомок красный, а левый любой
                        if (brother -> right != nullptr && brother -> right -> color == RED){
                            brother -> color = node -> parent -> color;
                            brother -> right -> color = BLACK;
                            brother -> parent -> color = BLACK;
                            left_turn(node -> parent, root);
                        }
                    }
                }
                // если текущая вершина - правая
                if (node -> parent -> right == node) {
                    TREE* brother = node -> parent -> left;
                    // если брат красный
                    if (brother -> color == RED) {
                        right_turn(node -> parent, root);
                        brother -> color = BLACK;
                        brother -> right -> color = RED;
                    }
                    // если брат чёрный
                    else {
                        // если у брата два черных потомка
                        if ((brother -> left == nullptr || brother -> left -> color == BLACK) &&
                            (brother -> right == nullptr || brother -> right -> color == BLACK)) {
                            brother -> color = RED;
                            node -> parent -> color = BLACK;
                            }
                        // у брата левый потомок - красный, а правый - чёрный
                        if (brother -> left != nullptr && brother -> left -> color == RED &&
                            (brother -> right == nullptr || brother -> right -> color == BLACK)) {
                            brother -> color = RED;
                            brother -> right -> color = BLACK;
                            left_turn(brother, root);
                            brother = node->parent->left;
                            }
                        // у брата левый потомок - красный
                        if (brother -> left != nullptr && brother -> left -> color == RED) {
                            brother -> color = node -> parent -> color;
                            brother -> left -> color = BLACK;
                            brother -> parent -> color = BLACK;
                            right_turn(node -> parent, root);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    TREE tree;
    TREE * root = nullptr;

    // Вставляем числа
    int numbers[] = {7, 3, 9, 10, 22, 8, 11, 26, 2, 6, 13};
    //int numbers[] = {7, 3, 9, 10, 22};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    for (int i{0}; i < n; i++) {
        tree.insert(numbers[i], &root);
    }
    cout << "delete element: " << endl;
    int value;
    cin >> value;
    tree.delete_element(&root, value);
    cout << " TREE IS: " << endl;
    tree.print(root);
    cout << endl;
    cout << "ROOT IS: " <<  root -> data << endl;

    // Очистка памяти
    delete root;
    return 0;
}
