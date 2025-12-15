#include <iostream>
#include <queue>
#include <algorithm> 
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T>* next_node;
    Node<T>* prev_node;

    Node(T val = T(), Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : data(val), prev_node(prev), next_node(next) {
    }
};

template <typename T>
class List
{
private:
    Node<T>* head_node;
    Node<T>* tail_node;

public:
    List() : head_node(nullptr), tail_node(nullptr) {}

    ~List()
    {
        while (head_node != nullptr)
        {
            Node<T>* temp = head_node;
            head_node = head_node->next_node;
            delete temp;
        }
    }

    bool empty() const { return head_node == nullptr; }

    Node<T>* head() const { return head_node; }

    void push_back(T val)
    {
        Node<T>* n = new Node<T>(val, tail_node, nullptr);
        if (empty())
        {
            head_node = tail_node = n;
        }
        else
        {
            tail_node->next_node = n;
            tail_node = n;
        }
    }
};

template <typename T>
class Simple_tree
{
private:
    T obj;
    Simple_tree<T>* parent_node;

public:
    List<Simple_tree<T>*> children;

    Simple_tree(T e = T(), Simple_tree<T>* p = nullptr)
        : obj(e), parent_node(p) {
    }

    T& value() { return obj; }

    Simple_tree<T>* parent() const { return parent_node; }

    bool is_root() const { return parent_node == nullptr; }

    bool is_leaf() const { return children.empty(); }

    void add_child(Simple_tree<T>* child)
    {
        child->parent_node = this;
        children.push_back(child);
    }

    int degree() const
    {
        int count = 0;
        for (Node<Simple_tree<T>*>* ptr = children.head();
            ptr != nullptr; ptr = ptr->next_node)
            count++;
        return count;
    }

    int size() const
    {
        int count = 1;
        for (Node<Simple_tree<T>*>* ptr = children.head();
            ptr != nullptr; ptr = ptr->next_node)
            count += ptr->data->size();
        return count;
    }

    int height() const
    {
        if (is_leaf())
            return 0;

        int max_h = 0;
        for (Node<Simple_tree<T>*>* ptr = children.head();
            ptr != nullptr; ptr = ptr->next_node)
        {
            max_h = max(max_h, ptr->data->height());
        }
        return max_h + 1;
    }
};

template <typename T>
void preorder(Simple_tree<T>* root)
{
    if (!root)
        return;

    cout << root->value() << " ";

    for (Node<Simple_tree<T>*>* ptr = root->children.head();
        ptr != nullptr; ptr = ptr->next_node)
        preorder(ptr->data);
}

template <typename T>
void postorder(Simple_tree<T>* root)
{
    if (!root)
        return;

    for (Node<Simple_tree<T>*>* ptr = root->children.head();
        ptr != nullptr; ptr = ptr->next_node)
        postorder(ptr->data);

    cout << root->value() << " ";
}

template <typename T>
void levelorder(Simple_tree<T>* root)
{
    if (!root)
        return;

    queue<Simple_tree<T>*> q;
    q.push(root);

    while (!q.empty())
    {
        Simple_tree<T>* cur = q.front();
        q.pop();

        cout << cur->value() << " ";

        for (Node<Simple_tree<T>*>* ptr = cur->children.head();
            ptr != nullptr; ptr = ptr->next_node)
            q.push(ptr->data);
    }
}

int main()
{
    Simple_tree<char>* a = new Simple_tree<char>('H');
    Simple_tree<char>* b = new Simple_tree<char>('U');
    Simple_tree<char>* c = new Simple_tree<char>('D');
    Simple_tree<char>* d = new Simple_tree<char>('T');
    Simple_tree<char>* e = new Simple_tree<char>('A');
    Simple_tree<char>* f = new Simple_tree<char>('R');
    Simple_tree<char>* g = new Simple_tree<char>('I');
    Simple_tree<char>* h = new Simple_tree<char>('Q');
    a->add_child(b);
    a->add_child(c);
    b->add_child(d);
    b->add_child(e);
    c->add_child(f);
    c->add_child(g);
    d->add_child(h);
    cout << "DFS (Preorder): ";
    preorder(a);
    cout << endl;

    cout << "BFS (Level Order): ";
    levelorder(a);
    cout << endl;

    cout << "Height of tree" << endl;
    cout << a->height() << endl;

    cout << "Degree of tree" << endl;
    cout << a->degree() << endl;
    return 0;
}
