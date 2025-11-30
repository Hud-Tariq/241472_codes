#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
    T data;
    Node<T>* next_node;

public:
    Node(T val = T(), Node<T>* next = nullptr)
        : data(val), next_node(next) {}

    T retrieve() const { return data; }
    Node<T>* next() const { return next_node; }

    void set_next(Node<T>* next) { next_node = next; }

    template <typename U>
    friend class List;
};

template <typename T>
class List {
private:
    Node<T>* list_head;

public:
    List() : list_head(nullptr) {}

    ~List() {
        while (!empty()) {
            pop_front();
        }
    }

    bool empty() const { return list_head == nullptr; }

    int size() const {
        int count = 0;
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    T front() const {
        if (empty()) {
            cerr << "Error: List is empty.\n";
            return T();
        }
        return list_head->retrieve();
    }

    T end() const {
        if (empty()) {
            cerr << "Error: List is empty.\n";
            return T();
        }
        Node<T>* ptr;
        for (ptr = list_head; ptr->next() != nullptr; ptr = ptr->next());
        return ptr->retrieve();
    }

    Node<T>* head() const { return list_head; }

    int count(T val) const {
        int c = 0;
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            if (ptr->retrieve() == val)
                ++c;
        return c;
    }

    void push_front(T val) {
        Node<T>* newNode = new Node<T>(val, list_head);
        list_head = newNode;
    }

    void push_end(T val) {
        Node<T>* newNode = new Node<T>(val, nullptr);
        if (empty()) {
            list_head = newNode;
            return;
        }
        Node<T>* ptr;
        for (ptr = list_head; ptr->next() != nullptr; ptr = ptr->next());
        ptr->set_next(newNode);
    }

    T pop_front() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return T();
        }
        Node<T>* temp = list_head;
        T val = temp->retrieve();
        list_head = list_head->next();
        delete temp;
        return val;
    }

    T pop_end() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return T();
        }
        if (list_head->next() == nullptr) {
            T val = list_head->retrieve();
            delete list_head;
            list_head = nullptr;
            return val;
        }
        Node<T>* ptr;
        for (ptr = list_head; ptr->next()->next() != nullptr; ptr = ptr->next());
        T val = ptr->next()->retrieve();
        delete ptr->next();
        ptr->set_next(nullptr);
        return val;
    }

    int erase(T val) {
        if (empty()) return 0;
        int removed = 0;

        while (list_head && list_head->retrieve() == val) {
            Node<T>* temp = list_head;
            list_head = list_head->next();
            delete temp;
            ++removed;
        }

        for (Node<T>* ptr = list_head; ptr && ptr->next(); ) {
            if (ptr->next()->retrieve() == val) {
                Node<T>* temp = ptr->next();
                ptr->set_next(temp->next());
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
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next())
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
}
