#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
    T data;
    Node<T>* next_node;
    Node<T>* prev_node;

public:
    Node(T val = T(), Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : data(val), prev_node(prev), next_node(next) {}

    T retrieve() const { return data; }
    Node<T>* next() const { return next_node; }
    Node<T>* prev() const { return prev_node; }

    void set_next(Node<T>* next) { next_node = next; }
    void set_prev(Node<T>* prev) { prev_node = prev; }

    template <typename U>
    friend class List;
};

template <typename T>
class List {
private:
    Node<T>* head_node;
    Node<T>* tail_node;

public:
    List() : head_node(nullptr), tail_node(nullptr) {}

    ~List() {
        while (!empty()) {
            pop_front();
        }
    }

    bool empty() const { return head_node == nullptr; }

    int size() const {
        int count = 0;
        for (Node<T>* ptr = head_node; ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    T front() const {
        if (empty()) {
            cerr << "Error: List is empty.\n";
            return T();
        }
        return head_node->retrieve();
    }

    T end() const {
        if (empty()) {
            cerr << "Error: List is empty.\n";
            return T();
        }
        return tail_node->retrieve();
    }

    Node<T>* head() const { return head_node; }
    Node<T>* tail() const { return tail_node; }

    int count(T val) const {
        int c = 0;
        for (Node<T>* ptr = head_node; ptr != nullptr; ptr = ptr->next())
            if (ptr->retrieve() == val)
                ++c;
        return c;
    }

    void push_front(T val) {
        Node<T>* newNode = new Node<T>(val, nullptr, head_node);
        if (empty()) {
            tail_node = newNode;
        } else {
            head_node->set_prev(newNode);
        }
        head_node = newNode;
    }

    void push_end(T val) {
        Node<T>* newNode = new Node<T>(val, tail_node, nullptr);
        if (empty()) {
            head_node = newNode;
        } else {
            tail_node->set_next(newNode);
        }
        tail_node = newNode;
    }

    T pop_front() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return T();
        }
        Node<T>* temp = head_node;
        T val = temp->retrieve();
        head_node = head_node->next();

        if (head_node)
            head_node->set_prev(nullptr);
        else
            tail_node = nullptr;

        delete temp;
        return val;
    }

    T pop_end() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return T();
        }
        Node<T>* temp = tail_node;
        T val = temp->retrieve();
        tail_node = tail_node->prev();

        if (tail_node)
            tail_node->set_next(nullptr);
        else
            head_node = nullptr;

        delete temp;
        return val;
    }

    int erase(T val) {
        if (empty()) return 0;
        int removed = 0;

        for (Node<T>* ptr = head_node; ptr != nullptr; ) {
            if (ptr->retrieve() == val) {
                Node<T>* temp = ptr;

                if (ptr->prev())
                    ptr->prev()->set_next(ptr->next());
                else
                    head_node = ptr->next();

                if (ptr->next())
                    ptr->next()->set_prev(ptr->prev());
                else
                    tail_node = ptr->prev();

                ptr = ptr->next();
                delete temp;
                ++removed;
            } else {
                ptr = ptr->next();
            }
        }
        return removed;
    }

    void display() const {
        cout << "[ ";
        for (Node<T>* ptr = head_node; ptr != nullptr; ptr = ptr->next())
            cout << ptr->retrieve() << " ";
        cout << "]\n";
    }

    void display_reverse() const {
        cout << "[ ";
        for (Node<T>* ptr = tail_node; ptr != nullptr; ptr = ptr->prev())
            cout << ptr->retrieve() << " ";
        cout << "]\n";
    }
};

int main() {
    List<int> l;
    l.push_front(10);
    l.push_end(20);
    l.push_end(30);
    l.display();

    cout << "Front: " << l.front() << endl;
    cout << "End: " << l.end() << endl;
    cout << "Size: " << l.size() << endl;

    l.pop_front();
    l.display();

    l.push_front(40);
    l.push_end(20);
    l.display();

    cout << "Count(20): " << l.count(20) << endl;

    l.erase(20);
    l.display();

    cout << "Pop end: " << l.pop_end() << endl;
    l.display();

    cout << "Reverse display: ";
    l.display_reverse();

    return 0;
}
