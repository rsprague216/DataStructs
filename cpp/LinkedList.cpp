#include <iostream>
#include <vector>

template <typename T>
class LinkedList {
    private:
        template <typename U>
        class ListNode {
            public:
                U data;
                ListNode* next;
        
                ListNode(U data) : data(data), next(nullptr) {}
        };

        ListNode<T>* head;
        ListNode<T>* tail;
    public:
        LinkedList() {
            this->head = nullptr;
            this->tail = head;   // make this circular by having tail->next = head
        }

        void add(T data) {
            ListNode<T>* temp = new ListNode<T>(data);
            if (head == nullptr) {
                head = temp;
                tail = head;
            }
            else {
                tail->next = temp;
                tail = temp;
            }
        }

        void insert(int index, T data) {
            ListNode<T>* newNode = new ListNode<T>(data);
            ListNode<T>* temp = head;
            if (index == 0 && head == nullptr) { // inserting into empty list
                head = newNode;
                tail = head;
                return;
            } else if (index == 0) { // inserting at the beginning
                newNode->next = head;
                head = newNode;
                return;
            }
            int idx = 0;
            while (temp != nullptr) {
                if (idx == index - 1) {
                    newNode->next = temp->next;
                    temp->next = newNode;
                    return;
                }
                temp = temp->next;
                idx++;
            }
        }

        T get(int index) {
            ListNode<T>* temp = head;
            int idx = 0;
            while (temp != nullptr) {
                if (idx == index) return temp->data;
                temp = temp->next;
                idx++;
            }
            return -1;
        }

        bool remove(int index) {
            if (head == nullptr) return false;

            ListNode<T>* temp = head;
            if (index == 0) {
                head = head->next;
                delete temp;
                return true;
            }
            int idx = 0;
            while (temp != nullptr) {
                if (idx == index - 1) {
                    ListNode<T>* toDelete = temp->next;
                    temp->next = toDelete->next;
                    delete toDelete;
                    return true;
                }
                temp = temp->next;
                idx++;
            }
            return false;
        }

        bool empty() {
            return head == nullptr;
        }

        std::vector<T> getValues() {
            std::vector<T> values;
            ListNode<T>* temp = head;
            while (temp != nullptr) {
                values.push_back(temp->data);
                temp = temp->next;
            }
            return values;
        }

        ~LinkedList() {
            ListNode<T>* temp = head;
            while (temp != nullptr) {
                ListNode<T>* next = temp->next;
                delete temp;
                temp = next;
            }
        }
};

int main() {
    LinkedList<char> list;
    std::vector<char> values;

    // Test 1: Check if the list is empty initially.
    std::cout << "Test 1: Check empty list\n";
    std::cout << (list.empty() ? "List is Empty" : "List is Not Empty") << "\n\n";

    // Test 2: Add elements 'a', 'b', 'c', 'd', 'e'.
    char data[] = {'a', 'b', 'c', 'd', 'e'};
    for (char c : data) {
        list.add(c);
    }
    std::cout << "Test 2: After adding elements: ";
    values = list.getValues();
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 3: Use get() method for valid and invalid indices.
    std::cout << "Test 3: Get elements by index\n";
    for (int i = 0; i < 7; i++) {
        char elem = list.get(i);
        if (i >= values.size())
            std::cout << "Index " << i << " out of bounds: " << (int)elem << "\n";
        else
            std::cout << "Element at index " << i << ": " << elem << "\n";
    }
    std::cout << "\n";

    // Test 4: Insert 'z' at the beginning (index 0).
    std::cout << "Test 4: Insert 'z' at index 0\n";
    list.insert(0, 'z');
    values = list.getValues();
    std::cout << "After insertion at beginning: ";
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 5: Insert 'x' in the middle (index 3).
    std::cout << "Test 5: Insert 'x' at index 3\n";
    list.insert(3, 'x');
    values = list.getValues();
    std::cout << "After insertion in middle: ";
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 6: Try to insert 'y' at an out-of-bound index.
    std::cout << "Test 6: Insert 'y' at index 100 (out-of-bound)\n";
    list.insert(100, 'y');
    values = list.getValues();
    std::cout << "After attempting out-of-bound insertion: ";
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 7: Remove the head element (index 0).
    std::cout << "Test 7: Remove head (index 0)\n";
    list.remove(0);
    values = list.getValues();
    std::cout << "After removing head: ";
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 8: Remove an element in the middle (index 2).
    std::cout << "Test 8: Remove element at index 2\n";
    list.remove(2);
    values = list.getValues();
    std::cout << "After removing middle element: ";
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 9: Remove the tail element.
    std::cout << "Test 9: Remove tail element (last index)\n";
    int size = values.size();
    list.remove(size - 1);
    values = list.getValues();
    std::cout << "After removing tail element: ";
    for (char c : values)
        std::cout << c << " ";
    std::cout << "\n\n";

    // Test 10: Attempt to remove an element at an out-of-bound index.
    std::cout << "Test 10: Attempt to remove element at index 100\n";
    bool removed = list.remove(100);
    std::cout << (removed ? "Removal succeeded" : "Removal failed (index out-of-bound)") << "\n\n";
    
    // Test 11: Remove all elements one by one.
    std::cout << "Test 11: Remove all elements\n";
    while (!list.empty()) {
        list.remove(0);
    }
    std::cout << (list.empty() ? "List is now empty" : "List is not empty") << "\n";

    return 0;
}