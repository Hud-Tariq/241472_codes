#include <iostream>
using namespace std;

class Node {
private:
    int value;
    Node* next_node;

public:
    Node(int val = 0, Node* next = nullptr)
        : value(val), next_node(next) {
    }

    int retrieve() const { return value; }
    Node* next() const { return next_node; }
    void set_next(Node* next) { next_node = next; }

    friend class List;
    friend class Stack;
};

class List {
private:
    Node* list_head;

public:
    List() : list_head(nullptr) {}

    ~List() {
        while (!empty())
            pop_front();
    }

    bool empty() const {
        return (list_head == nullptr);
    }

    int size() const {
        int count = 0;
        Node* ptr = list_head;
        while (ptr != nullptr) {
            ++count;
            ptr = ptr->next();
        }
        return count;
    }

    int front() const {
        if (empty()) {
            cerr << "List is empty! Cannot access front element.\n";
            return -1;
        }
        return list_head->retrieve();
    }

    void push_front(int n) {
        Node* new_node = new Node(n, list_head);
        list_head = new_node;
    }

    int pop_front() {
        if (empty()) {
            cerr << "List is empty! Cannot pop front.\n";
            return -1;
        }

        int value = list_head->retrieve();
        Node* temp = list_head;
        list_head = list_head->next();
        delete temp;
        return value;
    }

    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        Node* ptr = list_head;
        while (ptr != nullptr) {
            cout << ptr->retrieve() << " -> ";
            ptr = ptr->next();
        }
        cout << "nullptr\n";
    }

    friend class Stack;
};

class Stack {
private:
    List l;

public:
    Stack() {}

    bool empty() const {
        return l.empty();
    }

    int size() const {
        return l.size();
    }

    int peek() const {
        if (empty()) {
            cerr << "Stack is empty! Cannot peek.\n";
            return -1;
        }
        return l.front();
    }

    void push(int n) {
        l.push_front(n);
        cout << "Pushed " << n << " onto the stack.\n";
    }

    int pop() {
        if (empty()) {
            cerr << "Stack is empty! Cannot pop.\n";
            return -1;
        }
        return l.pop_front();
    }

    void display() const {
        if (empty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack (top to bottom):\n";
        cout << "TOP\n";
        cout << " |\n";

        Node* ptr = l.list_head;
        while (ptr != nullptr) {
            cout << " " << ptr->retrieve() << "\n";
            if (ptr->next() != nullptr)
                cout << " |\n";
            ptr = ptr->next();
        }
        cout << "BOTTOM\n";
    }

    void clear() {
        while (!empty())
            pop();
        cout << "Stack cleared.\n";
    }
};

int main() {
    Stack stk;

    cout << "=== Stack Operations Demo (Linked List Implementation) ===\n\n";

    cout << "Checking if stack is empty: " << (stk.empty() ? "Yes" : "No") << "\n\n";

    cout << "Pushing elements 10, 20, 30, 40, 50 onto the stack:\n";
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    cout << "\n";

    stk.display();
    cout << "\nStack size: " << stk.size() << "\n\n";

    cout << "Peek at top element: " << stk.peek() << "\n\n";

    cout << "Popping element: " << stk.pop() << "\n";
    cout << "Popping element: " << stk.pop() << "\n\n";

    stk.display();
    cout << "\nStack size after popping: " << stk.size() << "\n\n";

    cout << "Pushing 60 and 70:\n";
    stk.push(60);
    stk.push(70);
    cout << "\n";

    stk.display();
    cout << "\n";

    cout << "Clearing the entire stack:\n";
    stk.clear();
    cout << "\n";

    cout << "Is stack empty now? " << (stk.empty() ? "Yes" : "No") << "\n\n";

    cout << "Attempting to pop from empty stack:\n";
    stk.pop();
    cout << "\n";

    cout << "Attempting to peek at empty stack:\n";
    stk.peek();
    cout << "\n";

    cout << "Program finished successfully.\n";

    return 0;
}