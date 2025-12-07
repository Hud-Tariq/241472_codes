#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next_node;
    Node<T>* prev_node;

    Node(T val = T(), Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : data(val), prev_node(prev), next_node(next) {}
};

template <typename T>
class List {
private:
    Node<T>* head_node;
    Node<T>* tail_node;

public:
    List() : head_node(nullptr), tail_node(nullptr) {}

    ~List() {
        while (head_node != nullptr) {
            Node<T>* temp = head_node;
            head_node = head_node->next_node;
            delete temp;
        }
    }

    bool empty() const { return head_node == nullptr; }

    Node<T>* head() const { return head_node; }

    void push_back(T val) {
        Node<T>* n = new Node<T>(val, tail_node, nullptr);
        if (empty()) {
            head_node = tail_node = n;
        } else {
            tail_node->next_node = n;
            tail_node = n;
        }
    }
};


template <typename T>
class Simple_tree {
private:
    T obj;
    Simple_tree<T>* parent_node;

public:
    List<Simple_tree<T>*> children;

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

    for (Node<Simple_tree<T>*>* ptr = root->children.head();
         ptr != nullptr; ptr = ptr->next_node)
        preorder(ptr->data);
}

template <typename T>
void postorder(Simple_tree<T>* root) {
    if (!root) return;

    for (Node<Simple_tree<T>*>* ptr = root->children.head();
         ptr != nullptr; ptr = ptr->next_node)
        postorder(ptr->data);

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

        for (Node<Simple_tree<T>*>* ptr = cur->children.head();
             ptr != nullptr; ptr = ptr->next_node)
            q.push(ptr->data);
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
