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
    friend class CircularList;
};

template <typename T>
class CircularList {
private:
    Node<T>* head_node;

public:
    CircularList() : head_node(nullptr) {}

    ~CircularList() {
        if (empty()) return;
        Node<T>* ptr = head_node->next();
        while (ptr != head_node) {
            Node<T>* temp = ptr;
            ptr = ptr->next();
            delete temp;
        }
        delete head_node;
    }

    bool empty() const { return head_node == nullptr; }

    int size() const {
        if (empty()) return 0;
        int count = 0;
        for (Node<T>* ptr = head_node;; ptr = ptr->next()) {
            ++count;
            if (ptr->next() == head_node) break;
        }
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
        return head_node->prev()->retrieve();
    }

    void push_front(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (empty()) {
            newNode->set_next(newNode);
            newNode->set_prev(newNode);
            head_node = newNode;
        } else {
            Node<T>* tail = head_node->prev();
            newNode->set_next(head_node);
            newNode->set_prev(tail);
            tail->set_next(newNode);
            head_node->set_prev(newNode);
            head_node = newNode;
        }
    }

    void push_end(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (empty()) {
            newNode->set_next(newNode);
            newNode->set_prev(newNode);
            head_node = newNode;
        } else {
            Node<T>* tail = head_node->prev();
            newNode->set_next(head_node);
            newNode->set_prev(tail);
            tail->set_next(newNode);
            head_node->set_prev(newNode);
        }
    }

    T pop_front() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return T();
        }
        T val = head_node->retrieve();
        if (head_node->next() == head_node) {
            delete head_node;
            head_node = nullptr;
        } else {
            Node<T>* tail = head_node->prev();
            Node<T>* temp = head_node;
            head_node = head_node->next();
            tail->set_next(head_node);
            head_node->set_prev(tail);
            delete temp;
        }
        return val;
    }

    T pop_end() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return T();
        }
        Node<T>* tail = head_node->prev();
        T val = tail->retrieve();

        if (tail == head_node) {
            delete head_node;
            head_node = nullptr;
        } else {
            Node<T>* new_tail = tail->prev();
            new_tail->set_next(head_node);
            head_node->set_prev(new_tail);
            delete tail;
        }
        return val;
    }

    int erase(T val) {
        if (empty()) return 0;

        int removed = 0;
        Node<T>* ptr = head_node;

        do {
            if (ptr->retrieve() == val) {
                Node<T>* temp = ptr;
                Node<T>* prev = ptr->prev();
                Node<T>* next = ptr->next();

                prev->set_next(next);
                next->set_prev(prev);

                if (ptr == head_node)
                    head_node = (next != ptr ? next : nullptr);

                ptr = next;
                delete temp;
                ++removed;

                if (empty()) break;
            } else {
                ptr = ptr->next();
            }
        } while (ptr != head_node);

        return removed;
    }

    void display() const {
        if (empty()) {
            cout << "[]\n";
            return;
        }
        cout << "[ ";
        Node<T>* ptr = head_node;
        do {
            cout << ptr->retrieve() << " ";
            ptr = ptr->next();
        } while (ptr != head_node);
        cout << "]\n";
    }

    void display_reverse() const {
        if (empty()) {
            cout << "[]\n";
            return;
        }
        cout << "[ ";
        Node<T>* ptr = head_node->prev();
        do {
            cout << ptr->retrieve() << " ";
            ptr = ptr->prev();
        } while (ptr->next() != head_node);
        cout << "]\n";
    }
};

int main() {
    CircularList<int> l;
    l.push_front(10);
    l.push_end(20);
    l.push_end(30);
    l.display();
}
