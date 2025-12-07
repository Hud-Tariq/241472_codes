#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class ArrayList {
private:
    T* arr;
    int capacity;
    int length;

    void expand() {
        int new_capacity = capacity * 2;
        T* new_arr = new T[new_capacity];

        for (int i = 0; i < length; i++)
            new_arr[i] = arr[i];

        delete[] arr;
        arr = new_arr;
        capacity = new_capacity;
    }

public:
    ArrayList(int cap = 4)
        : capacity(cap), length(0), arr(new T[cap]) {}

    ~ArrayList() {
        delete[] arr;
    }

    bool empty() const { return length == 0; }

    int size() const { return length; }

    T& operator[](int i) { return arr[i]; }

    void push_back(T val) {
        if (length == capacity)
            expand();
        arr[length++] = val;
    }
};

template <typename T>
class Simple_tree {
private:
    T obj;
    Simple_tree<T>* parent_node;

public:
    ArrayList<Simple_tree<T>*> children;

    Simple_tree(T e = T(), Simple_tree<T>* p = nullptr)
        : obj(e), parent_node(p) {}

    T& value() { return obj; }

    Simple_tree<T>* parent() const { return parent_node; }

    bool is_leaf() const { return children.empty(); }

    void add_child(Simple_tree<T>* child) {
        child->parent_node = this;
        children.push_back(child);
    }

    int depth() const {
        if (parent_node == nullptr)
            return 0;
        return parent_node->depth() + 1;
    }
};

template <typename T>
void preorder(Simple_tree<T>* root) {
    if (!root) return;

    cout << root->value() << " ";
    for (int i = 0; i < root->children.size(); i++)
        preorder(root->children[i]);
}

template <typename T>
void postorder(Simple_tree<T>* root) {
    if (!root) return;

    for (int i = 0; i < root->children.size(); i++)
        postorder(root->children[i]);

    cout << root->value() << " ";
}

template <typename T>
void levelorder(Simple_tree<T>* root) {
    if (!root) return;

    queue<Simple_tree<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Simple_tree<T>* cur = q.front();
        q.pop();

        cout << cur->value() << " ";

        for (int i = 0; i < cur->children.size(); i++)
            q.push(cur->children[i]);
    }
}


int main() {
    Simple_tree<int>* root = new Simple_tree<int>(1);

    auto c1 = new Simple_tree<int>(2);
    auto c2 = new Simple_tree<int>(3);
    auto c3 = new Simple_tree<int>(4);

    root->add_child(c1);
    root->add_child(c2);
    root->add_child(c3);

    c1->add_child(new Simple_tree<int>(5));
    c1->add_child(new Simple_tree<int>(6));

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    cout << "Level-order: ";
    levelorder(root);
    cout << endl;

    return 0;
}
