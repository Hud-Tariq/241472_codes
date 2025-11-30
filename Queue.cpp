#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val, Node* nxt = nullptr)
        : data(val), next(nxt) {}
};

class List {
private:
    Node* head;
    Node* tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() const { return head == nullptr; }

    void push_back(int val) {
        Node* n = new Node(val);
        if (empty()) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }

    int front() const {
        if (empty()) throw underflow_error("Queue underflow");
        return head->data;
    }

    int pop_front() {
        if (empty()) throw underflow_error("Queue underflow");
        Node* temp = head;
        int val = head->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        return val;
    }
};

class Queue {
private:
    List l;

public:
    bool empty() const { return l.empty(); }

    int front() const {
        if (empty()) throw underflow_error("Queue underflow");
        return l.front();
    }

    void push(int obj) {
        l.push_back(obj);
    }

    int pop() {
        if (empty()) throw underflow_error("Queue underflow");
        return l.pop_front();
    }
};

int main() {
    Queue q;

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
