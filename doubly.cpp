#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node* next_node;
    Node* prev_node;

public:
    Node(int val = 0, Node* prev = nullptr, Node* next = nullptr)
        : data(val), prev_node(prev), next_node(next) {}

    int retrieve() const { return data; }
    Node* next() const { return next_node; }
    Node* prev() const { return prev_node; }

    void set_next(Node* next) { next_node = next; }
    void set_prev(Node* prev) { prev_node = prev; }

    friend class List;
};

class List {
private:
    Node* head_node;
    Node* tail_node;

public:
    List() : head_node(nullptr), tail_node(nullptr) {}

    ~List() {
        for (; !empty(); ) {
            pop_front();
        }
    }

    bool empty() const { return head_node == nullptr; }

    int size() const {
        int count = 0;
        for (Node* ptr = head_node; ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    int front() const {
        if (empty()) {
            cerr << "Error: List is empty.\n";
            return -1;
        }
        return head_node->retrieve();
    }

    int end() const {
        if (empty()) {
            cerr << "Error: List is empty.\n";
            return -1;
        }
        return tail_node->retrieve();
    }

    Node* head() const { return head_node; }
    Node* tail() const { return tail_node; }

    int count(int val) const {
        int c = 0;
        for (Node* ptr = head_node; ptr != nullptr; ptr = ptr->next())
            if (ptr->retrieve() == val)
                ++c;
        return c;
    }

    void push_front(int val) {
        Node* newNode = new Node(val, nullptr, head_node);
        if (empty()) {
            tail_node = newNode;
        } else {
            head_node->set_prev(newNode);
        }
        head_node = newNode;
    }

    void push_end(int val) {
        Node* newNode = new Node(val, tail_node, nullptr);
        if (empty()) {
            head_node = newNode;
        } else {
            tail_node->set_next(newNode);
        }
        tail_node = newNode;
    }

    int pop_front() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return -1;
        }
        Node* temp = head_node;
        int val = temp->retrieve();
        head_node = head_node->next();
        if (head_node)
            head_node->set_prev(nullptr);
        else
            tail_node = nullptr;
        delete temp;
        return val;
    }

    int pop_end() {
        if (empty()) {
            cerr << "Error: Cannot pop from empty list.\n";
            return -1;
        }
        Node* temp = tail_node;
        int val = temp->retrieve();
        tail_node = tail_node->prev();
        if (tail_node)
            tail_node->set_next(nullptr);
        else
            head_node = nullptr;
        delete temp;
        return val;
    }

    int erase(int val) {
        if (empty()) return 0;
        int removed = 0;

        for (Node* ptr = head_node; ptr != nullptr; ) {
            if (ptr->retrieve() == val) {
                Node* temp = ptr;
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
        for (Node* ptr = head_node; ptr != nullptr; ptr = ptr->next())
            cout << ptr->retrieve() << " ";
        cout << "]\n";
    }

    void display_reverse() const {
        cout << "[ ";
        for (Node* ptr = tail_node; ptr != nullptr; ptr = ptr->prev())
            cout << ptr->retrieve() << " ";
        cout << "]\n";
    }
};

int main() {
    List l;
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
