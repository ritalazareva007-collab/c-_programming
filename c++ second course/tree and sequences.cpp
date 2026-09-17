#include <iostream>
#include <cmath>
#include <fstream>
#include <format>
using namespace std;

template <typename T>
struct Complex{
    T Re;
    T Im;
    // перегрузка оператора - для комплексных чисел
    Complex operator-() const {
        return {-Re, -Im};
    }
    // перегрузка оператора умножения = f(z) = z^2
    Complex operator*(const Complex& z) const {
        return{
            z.Re * z.Re - z.Im * z.Im,
            2 * z.Re * z.Im
                };
    }
    // конструктор для инициализации полей
    Complex(T Re, T Im): Re(Re), Im(Im){}
};


// функция взятия модуля комплексного числа
template <typename T>
double ABS(const Complex<T>& z) {
    return sqrt(z.Re * z.Re + z.Im * z.Im);
}


// функция возведения комплексного числа в квадрат
// template <typename T>
// Complex<T> Square(Complex<T>& z) {
//     return{
//     z.Re * z.Re - z.Im * z.Im,
//     2 * z.Re * z.Im
//         };
// }

// функция вывода последовательности на экран
template <typename T>
void print(int iterations, Complex<T>& z, std::ofstream& Out) {
    for (int i = 0; i < iterations; ++i) {
        Out << "iteration: " << "{" << i << "} " << "|f(z)| = " << ABS(z * z) << endl;
        z = z * z ;
    }
}





// функция извлечения корня из комплексного числа
template <typename T>
Complex<T> ComplexSqrt(Complex<T>& z) {
    double a = z.Re;
    double b = z.Im;
    auto sgn = [](double b) -> double {
        if (b == 0) return 0.0;
        return b > 0 ? 1.0 : -1.0;
    };
    double x = sqrt((ABS(z) + a )/ 2.0);
    double y = sgn(b) * sqrt((ABS(z) - a) / 2.0);
    return Complex<T>{x, y};

}

// структура узла дерева
template <typename T>
struct Node {
    Complex<T> data;
    Node<T>* left;
    Node<T>* right;

    Node(Complex<T> value) : data(value), left(nullptr), right(nullptr) {}
};


// класс, описывающий само дерево
template <typename T>
class TREE {
private:
    Node<T>* root; // указатель на начальный - корневой узел от которого будет строится дерево
    int height; // высота дерева

    void BuildTree(Node<T>* node, int level) {
        if (level > height) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            Complex<T> z = ComplexSqrt<T>(node->data);
            node->left = new Node<T>(-z);
            node->right = new Node<T>(z);
        }
        BuildTree(node->left, level + 1);
        BuildTree(node->right, level + 1);
    }


    void DestroyTree(Node<T>* node) {
        if (node == nullptr) {
            cout << "Tree is empty" << endl;
        }
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }



    void printTree(Node<T>* node, string prefix, bool isLeft) const {
        if (node == nullptr) {
            return;
        }
        // Печатаем текущий узел
        cout << prefix;
        cout << (isLeft ? "|-- " : "|__ ");

        char sign = (node->data.Im >= 0) ? '+' : '-';
        cout << node->data.Re << " " << sign << " "
             << "i" << abs(node->data.Im) << "\n";

        string newPrefix = prefix + (isLeft ? "|   " : "    ");
        printTree(node->left, newPrefix, true);
        printTree(node->right, newPrefix, false);
    }


public:
    // конструктор принимает значение комплексного числа, от которого будет строится само дерево
    // и высоту, до которой дерево будет строится
    TREE(Complex<T> value, int heightTree) {
        root = new Node<T>(value);
        height = heightTree;
        BuildTree(root, 1);
    }
    // деструктор - очищает дерево, начиная с заданной вершины
    ~TREE() {
        DestroyTree(root);
    }

    void print() {
        printTree(root, "", false);
    }
};



int main() {
    std::ofstream OutFile("sequences.txt");
    if (!OutFile.is_open()) {
        cerr << "Error out. File didn't open.";
        return 1;
    }

    Complex<double> z_0(1.0, 0.0);
    print(15, z_0, OutFile);
    OutFile << "--------------------------------------------------------------------" << endl;
    OutFile << "Complex value in circle" << endl;
    Complex<double> z_1(0.4, 0.7);
    print(15, z_1, OutFile);
    OutFile << "--------------------------------------------------------------------" << endl;
    OutFile << "Complex value out of circle" << endl;
    Complex<double> z_2(2.0, 4.0);
    print(15, z_2, OutFile);

    OutFile.close();
    cout << "File was write successfully" << endl;


    Complex<double> z(4.0, 2.3);
    int height = 4;

    TREE<double> tree(z, height);

    tree.print();
}




