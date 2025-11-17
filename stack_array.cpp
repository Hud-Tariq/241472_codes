#include <iostream>
using namespace std;

class StackArray {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int stack_top;

public:
    StackArray() : stack_top(-1) {}

    bool empty() const {
        return (stack_top == -1);
    }

    bool full() const {
        return (stack_top == MAX_SIZE - 1);
    }

    int size() const {
        return stack_top + 1;
    }

    int peek() const {
        if (empty()) {
            cerr << "Stack is empty! Cannot peek.\n";
            return -1;
        }
        return arr[stack_top];
    }

    void push(int n) {
        if (full()) {
            cerr << "Stack is full! Cannot push " << n << ".\n";
            return;
        }
        arr[++stack_top] = n;
        cout << "Pushed " << n << " onto the stack.\n";
    }

    int pop() {
        if (empty()) {
            cerr << "Stack is empty! Cannot pop.\n";
            return -1;
        }
        return arr[stack_top--];
    }

    void display() const {
        if (empty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack (top to bottom):\n";
        cout << "TOP\n";
        cout << " |\n";
        int i = stack_top;
        while (i >= 0) {
            cout << " " << arr[i] << "\n";
            if (i > 0)
                cout << " |\n";
            i--;
        }
        cout << "BOTTOM\n";
    }

    void clear() {
        stack_top = -1;
        cout << "Stack cleared.\n";
    }

    int capacity() const {
        return MAX_SIZE;
    }
};

int main() {
    StackArray stk;

    cout << "=== Stack Operations Demo (Array Implementation) ===\n\n";

    cout << "Stack capacity: " << stk.capacity() << "\n";
    cout << "Checking if stack is empty: " << (stk.empty() ? "Yes" : "No") << "\n\n";

    cout << "Pushing elements 10, 20, 30, 40, 50 onto the stack:\n";
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    cout << "\n";

    stk.display();
    cout << "\nStack size: " << stk.size() << "\n";
    cout << "Is stack full? " << (stk.full() ? "Yes" : "No") << "\n\n";

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

    cout << "Testing stack overflow - pushing elements until full:\n";
    int i = 1;
    while (i <= 5) {
        stk.push(i * 10);
        i++;
    }
    cout << "\nStack size: " << stk.size() << "\n";
    cout << "Program finished successfully.\n";

    return 0;
}