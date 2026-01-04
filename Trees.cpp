#include <iostream>
#include <algorithm> // Needed for std::max in height()

using namespace std;

// ==========================================
// 1. Custom Node Class (Slide 36/38)
// ==========================================
template <typename Type>
class Node {
public:
    Type element;
    Node *next_node;

    Node(Type const &e = Type(), Node *n = nullptr)
        : element(e), next_node(n) {}

    Type retrieve() const { return element; }
    Node *next() const { return next_node; }
};

// ==========================================
// 2. Custom LinkedList Class
// ==========================================
template <typename Type>
class LinkedList {
private:
    Node<Type> *list_head;
    Node<Type> *list_tail;
    int count;

public:
    LinkedList() : list_head(nullptr), list_tail(nullptr), count(0) {}

    ~LinkedList() {
        while (list_head != nullptr) {
            Node<Type> *temp = list_head;
            list_head = list_head->next_node;
            delete temp;
        }
    }

    Node<Type> *head() const { return list_head; }
    Node<Type> *tail() const { return list_tail; } // Added for completeness

    bool empty() const { return list_head == nullptr; }
    int size() const { return count; }

    void push_back(Type const &obj) {
        Node<Type> *new_node = new Node<Type>(obj);
        if (list_tail == nullptr) {
            list_head = new_node;
        } else {
            list_tail->next_node = new_node;
        }
        list_tail = new_node;
        count++;
    }

    Type pop_front() {
        if (list_head == nullptr) return Type(); 
        Node<Type> *temp = list_head;
        Type val = temp->retrieve();
        list_head = list_head->next_node;
        if (list_head == nullptr) list_tail = nullptr;
        delete temp;
        count--;
        return val;
    }

    void erase(Type const &obj) {
        if (list_head == nullptr) return;
        if (list_head->retrieve() == obj) {
            pop_front();
            return;
        }
        Node<Type> *ptr = list_head;
        while (ptr->next_node != nullptr && ptr->next_node->retrieve() != obj) {
            ptr = ptr->next_node;
        }
        if (ptr->next_node != nullptr) {
            Node<Type> *victim = ptr->next_node;
            ptr->next_node = victim->next_node;
            if (victim == list_tail) list_tail = ptr;
            delete victim;
            count--;
        }
    }
};

// ==========================================
// 3. Custom Queue Class (Lecture 15, Slide 232)
// ==========================================
template <typename Type>
class Queue {
private:
    LinkedList<Type> list; 
public:
    void push(Type const &obj) { list.push_back(obj); }
    Type pop() { return list.pop_front(); } // Slide specific: Returns value
    bool empty() const { return list.empty(); }
};

// ==========================================
// 4. Complete Simple_tree Class
// ==========================================
template <typename Type>
class Simple_tree {
private:
    Type node_value;
    Simple_tree *parent_node;
    LinkedList<Simple_tree *> children; // Slide 68

public:
    // --- Constructor (Slide 70, 86) ---
    Simple_tree(Type const &obj = Type(), Simple_tree *p = nullptr)
        : node_value(obj), parent_node(nullptr) {
        if (p != nullptr) {
            p->attach(this);
        }
    }

    // --- Accessors (Slide 71-76) ---
    Type retrieve() const { return node_value; }
    Simple_tree *parent() const { return parent_node; }
    
    // Slide 106
    int degree() const { return children.size(); } 
    
    // Slide 102
    bool is_root() const { return parent_node == nullptr; } 
    
    // Slide 110
    bool is_leaf() const { return degree() == 0; } 

    // --- Accessing specific child (Slide 116) ---
    // Handles Edge Case: n out of bounds [cite: 117]
    Simple_tree *child(int n) const {
        if (n < 0 || n >= degree()) {
            return nullptr; 
        }

        Node<Simple_tree*> *ptr = children.head();
        // Skip first n children (Slide 122 logic adapted for 0-based index)
        for (int i = 0; i < n; ++i) {
            ptr = ptr->next();
        }
        return ptr->retrieve();
    }

    // --- Statistics (Slide 161, 177) ---
    
    // Recursive Size (Slide 161)
    // Edge Case: Checks if 'this' is nullptr [cite: 162]
    int size() const {
        if (this == nullptr) return 0;

        int tree_size = 1;
        // Manual Loop (Slide 166)
        for (Node<Simple_tree*> *ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
            tree_size += ptr->retrieve()->size();
        }
        return tree_size;
    }

    // Recursive Height (Slide 177)
    // Edge Case: Empty tree is -1 [cite: 178]
    int height() const {
        if (this == nullptr) return -1;

        int tree_height = 0; // Leaf is 0
        // Manual Loop (Slide 182)
        for (Node<Simple_tree*> *ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
            tree_height = std::max(tree_height, 1 + ptr->retrieve()->height());
        }
        return tree_height;
    }

    // --- Modifiers (Slide 130, 138, 149) ---

    // Slide 130
    void insert(Type const &obj) {
        attach(new Simple_tree(obj));
    }

    // Slide 149: Attach existing tree
    // Edge Case: Detaches if tree is already a child [cite: 150]
    void attach(Simple_tree *tree) {
        if (tree == nullptr) return;
        if (!tree->is_root()) {
            tree->detach();
        }
        tree->parent_node = this;
        children.push_back(tree);
    }

    // Slide 138: Detach from parent
    // Edge Case: Do nothing if already root [cite: 139]
    void detach() {
        if (is_root()) return;
        parent_node->children.erase(this);
        parent_node = nullptr;
    }

    // --- Traversals (Lecture 15) ---

    // BFS (Slide 232)
    void breadth_first_traversal() {
        Queue<Simple_tree*> q;
        q.push(this);

        while (!q.empty()) {
            Simple_tree* p = q.pop(); 
            cout << p->retrieve() << " "; 

            for (Node<Simple_tree*> *ptr = p->children.head(); ptr != nullptr; ptr = ptr->next()) {
                q.push(ptr->retrieve());
            }
        }
        cout << endl;
    }

    // DFS (Slide 244)
    void depth_first_traversal() const {
        cout << retrieve() << " "; 
        for (Node<Simple_tree*> *ptr = children.head(); ptr != nullptr; ptr = ptr->next()) {
            ptr->retrieve()->depth_first_traversal();
        }
    }
};

// ==========================================
// 5. Test Main (Covering Edge Cases)
// ==========================================
int main() {
    // 1. Create Root
    Simple_tree<char> *root = new Simple_tree<char>('A');

    // 2. Build Tree
    //       A
    //     /   \
    //    B     H
    //   / \   / \
    //  C   E I   M
    Simple_tree<char> *B = new Simple_tree<char>('B');
    Simple_tree<char> *H = new Simple_tree<char>('H');
    root->attach(B);
    root->attach(H);
    B->insert('C');
    B->insert('E');
    H->insert('I');
    H->insert('M');

    // 3. Test Statistics (Missing from previous code)
    cout << "Tree Size (Should be 7): " << root->size() << endl; // A,B,C,E,H,I,M
    cout << "Tree Height (Should be 2): " << root->height() << endl; // A->B->C
    cout << "Is H a leaf? (0): " << H->is_leaf() << endl;
    
    // 4. Test Access child(n)
    Simple_tree<char> *second_child = root->child(1); // 0=B, 1=H
    if (second_child) cout << "Child 1 of Root is: " << second_child->retrieve() << endl;

    // 5. Edge Case: Access invalid child
    if (root->child(10) == nullptr) cout << "Edge Case Handled: Child 10 is nullptr" << endl;

    // 6. Traversals
    cout << "DFS: "; root->depth_first_traversal(); cout << endl;
    cout << "BFS: "; root->breadth_first_traversal(); 

    return 0;
}
