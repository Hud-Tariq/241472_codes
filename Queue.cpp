#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T val, Node<T>* nxt = nullptr)
        : data(val), next(nxt) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() const { return head == nullptr; }

    void push_back(T val) {
        Node<T>* n = new Node<T>(val);
        if (empty()) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }

    T front() const {
        if (empty()) throw underflow_error("Queue underflow");
        return head->data;
    }

    T pop_front() {
        if (empty()) throw underflow_error("Queue underflow");
        Node<T>* temp = head;
        T val = head->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        return val;
    }
};


template <typename T>
class Queue {
private:
    List<T> l;

public:
    bool empty() const { return l.empty(); }

    T front() const {
        if (empty()) throw underflow_error("Queue underflow");
        return l.front();
    }

    void push(T obj) {
        l.push_back(obj);
    }

    T pop() {
        if (empty()) throw underflow_error("Queue underflow");
        return l.pop_front();
    }
};


int main() {
    Queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << q.front() << endl;   // 10
    cout << q.pop() << endl;     // 10
    cout << q.pop() << endl;     // 20

    q.push(40);
    cout << q.pop() << endl;     // 30

    cout << q.front() << endl;   // 40
}
