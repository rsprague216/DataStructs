#include <iostream>

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };
    Node* left;
    Node* right;;
    int dim;

public:
    Deque() : left(nullptr), right(nullptr), dim(0) {}

    void pushLeft(T data) {
        Node* newNode = new Node(data);
        if (empty()) {
            left = newNode;
            right = left;
        } else {
            newNode->next = left;
            left->prev = newNode;
            left = newNode;
        }
        dim++;
    }

    void pushRight(T data) {
        Node* newNode = new Node(data);
        if (empty()) {
            left = newNode;
            right = left;
        } else {
            newNode->prev = right;
            right->next = newNode;
            right = newNode;
        }
        dim++;
    }

    T popLeft() {
        if (empty()) throw std::out_of_range("Deque is empty");
        Node* toDelete = left;
        T returnVal = toDelete->data;
        if (dim == 1) {
            left = nullptr;
            right = left;
        } else {
            left = left->next;
            left->prev = nullptr;
        }
        delete toDelete;
        dim--;
        return returnVal;
    }

    T popRight() {
        if (empty()) throw std::out_of_range("Deque is empty");
        Node* toDelete = right;
        T returnVal = toDelete->data;
        if (dim == 1) {
            left = nullptr;
            right = left;
        } else {
            right = right->prev;
            right->next = nullptr;
        }
        delete toDelete;
        dim--;
        return returnVal;
    }

    int size() {
        return dim;
    }

    bool empty() {
        return left == nullptr;
    }

    ~Deque() {
        Node* temp = left;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    Deque<int> dq;

    // Initial state
    std::cout << "Deque empty? " << (dq.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Initial size: " << dq.size() << std::endl;

    // Pushing elements to both ends
    std::cout << "\nPushing elements:" << std::endl;
    std::cout << "  pushLeft(10)" << std::endl;
    dq.pushLeft(10);  // Deque: [10]
    std::cout << "  Size after pushLeft(10): " << dq.size() << std::endl;
    
    std::cout << "  pushRight(20)" << std::endl;
    dq.pushRight(20); // Deque: [10, 20]
    std::cout << "  Size after pushRight(20): " << dq.size() << std::endl;
    
    std::cout << "  pushLeft(5)" << std::endl;
    dq.pushLeft(5);   // Deque: [5, 10, 20]
    std::cout << "  Size after pushLeft(5): " << dq.size() << std::endl;
    
    std::cout << "  pushRight(30)" << std::endl;
    dq.pushRight(30); // Deque: [5, 10, 20, 30]
    std::cout << "  Size after pushRight(30): " << dq.size() << std::endl;

    // Popping elements from both ends and checking size
    std::cout << "\nPopping elements:" << std::endl;
    int leftElem = dq.popLeft();  // Should remove 5
    std::cout << "  popLeft(): " << leftElem << " (expected 5)" << std::endl;
    std::cout << "  Size after popLeft(): " << dq.size() << std::endl;
    
    int rightElem = dq.popRight(); // Should remove 30
    std::cout << "  popRight(): " << rightElem << " (expected 30)" << std::endl;
    std::cout << "  Size after popRight(): " << dq.size() << std::endl;
    
    leftElem = dq.popLeft();  // Should remove 10
    std::cout << "  popLeft(): " << leftElem << " (expected 10)" << std::endl;
    std::cout << "  Size after popLeft(): " << dq.size() << std::endl;
    
    rightElem = dq.popRight(); // Should remove 20
    std::cout << "  popRight(): " << rightElem << " (expected 20)" << std::endl;
    std::cout << "  Size after popRight(): " << dq.size() << std::endl;

    // Check if deque is empty
    std::cout << "\nDeque empty after pops? " << (dq.empty() ? "Yes" : "No") << std::endl;

    // Attempt to pop from empty deque to test exception handling.
    try {
        dq.popLeft();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught on popLeft: " << e.what() << std::endl;
    }

    try {
        dq.popRight();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught on popRight: " << e.what() << std::endl;
    }
    
    return 0;
}