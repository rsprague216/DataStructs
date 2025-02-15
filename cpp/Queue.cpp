#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int dim;

public:
    Queue() : head(nullptr), tail(nullptr), dim(0) {}

    void push(T data) {
        if (empty()) {
            head = new Node(data);
            tail = head;
        } else {
            Node* newNode = new Node(data);
            tail->next = newNode;
            tail = newNode;
        }
        dim++;
    }

    T pop() {
        if (empty()) throw std::out_of_range("Queue is empty");
        Node* toDelete = head;
        T data = toDelete->data;
        if (dim == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
        }
        delete toDelete;
        dim--;
        return data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        return dim;
    }

    ~Queue() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    Queue<int> q;

    // Check if the queue is initially empty
    std::cout << "Queue empty? " << (q.empty() ? "Yes" : "No") << std::endl;

    // Push elements into the queue
    std::cout << "Pushing elements: 10, 20, 30, 40" << std::endl;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    std::cout << "Queue size after pushes: " << q.size() << std::endl;

    // Pop one element and display it
    int popped = q.pop();
    std::cout << "Popped element: " << popped << std::endl;
    std::cout << "Queue size after one pop: " << q.size() << std::endl;

    // Pop and print the rest of the elements
    std::cout << "Popping remaining elements:" << std::endl;
    while (!q.empty()) {
        std::cout << q.pop() << " ";
    }
    std::cout << std::endl;

    // Attempt to pop from an empty queue to test exception handling
    try {
        q.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}