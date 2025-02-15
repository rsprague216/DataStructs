#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class DoubleLinkedList {
private:
    struct ListNode {
        T data;
        ListNode* prev;
        ListNode* next;
        
        ListNode(T data) : data(data), prev(nullptr), next(nullptr) {}
    };

    ListNode* head;
    ListNode* tail;
    
public:
    DoubleLinkedList() : head(nullptr), tail(head) {}
    
    void insertHead(T data) {
        if (empty()) {
            head = new ListNode(data);
            tail = head;
        } else {
            ListNode* newNode = new ListNode(data);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void insertTail(T data) {
        if (empty()) {
            head = new ListNode(data);
            tail = head;
        } else {
            ListNode* newNode = new ListNode(data);
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    void insertAt(int index, T data) {
        if (index == 0) {
            insertHead(data);
            return;
        }
        if (index < 0) {
            return;
        }
        
        int idx = 0;
        ListNode* curr = head;
        
        while (curr && idx != index) { // traverse list
            idx++;
            curr = curr->next;
        }
        if (curr) { // if curr isn't null, then we're at the index
            if (!curr->next) {  // we're at the tail
                insertTail(data);
            } else {
                ListNode* newNode = new ListNode(data);
                
                newNode->prev = curr->prev;
                newNode->next = curr;
                curr->prev->next = newNode;
                curr->prev = newNode;
            }
        }
    }
    
    void removeHead() {
        ListNode* toDelete = head;
        head = head->next;
        head->prev = nullptr;
        delete toDelete;
    }
    
    void removeTail() {
        ListNode* toDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete toDelete;
    }
    
    void removeAt(int index) {
        if (empty()) return;
        if (index == 0) {   // removing the head
            removeHead();
            return;
        } else if (index < 0) return;
        
        ListNode* curr = head;
        int idx = 0;
        while (curr && idx != index) {  // traverse linked list
            curr = curr->next;
            idx++;
        }
        
        if (curr) {
            if (!curr->next) {
                removeTail();
            } else {
                ListNode* toDelete = curr;
                curr->prev->next = toDelete->next;
                curr->next->prev = toDelete->prev;
                delete toDelete;
            }
        }
    }
    
    bool updateAt(int index, T data) {
        if (index < 0) return false;
        
        int idx = 0;
        ListNode* curr = head;
        while (curr && idx != index) {
            curr = curr->next;
            idx++;
        }
        if (curr) curr->data = data;
        return curr != nullptr;
    }
    
    T front() {
        return head->data;
    }
    
    T back() {
        return tail->data;
    }
    
    T get(int index) {
        if (empty()) throw std::out_of_range("List is empty");
        if (index < 0) return head->data;
        
        int idx = 0;
        ListNode* curr = head;
        while (curr && idx != index) {
            curr = curr->next;
            idx++;
        }
        
        if (curr) return curr->data;
        return tail->data;
    }
    
    bool empty() {
        return head == nullptr;
    }
    
    vector<T> getList() {
        vector<T> list_arr = {};
        ListNode* temp = head;
        while (temp) {
            list_arr.push_back(temp->data);
            temp = temp->next;
        }
        return list_arr;
    }
    
    vector<T> getReversedList() {
        vector<T> list_arr = {};
        ListNode* temp = tail;
        while (temp) {
            list_arr.push_back(temp->data);
            temp = temp->prev;
        }
        return list_arr;
    }
    
    ~DoubleLinkedList() {
        ListNode* temp = head;
        while (temp) {
            ListNode* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};


int main() {
    DoubleLinkedList<int> list;
    
    // list.insertHead(3);
    // list.insertHead(5);
    // list.insertHead(2);
    // list.insertHead(9);
    
    list.insertTail(3);
    list.insertTail(5);
    list.insertTail(2);
    list.insertTail(9);
    
    list.insertAt(2, 7);
    
    cout << list.front() << " || " << list.back() << " || " << list.get(2) << endl;
    
    vector<int> list_arr = list.getList();
    vector<int> list_rev = list.getReversedList();
    
    
    for (auto num : list_arr) {
        cout << num << " ";
    }
    cout << endl;
    for (auto num : list_rev) {
        cout << num << " ";
    }
    cout << endl;
    
    int upd_indx = 3;
    cout << (list.updateAt(upd_indx, 6) ? "Updated" : "Not Updated") << endl;
    // int rem_idx = 1;
    // cout << endl << "Removing Head..." << endl;
    // list.removeHead();
    // cout << "Removing Tail..." << endl;
    // list.removeTail();
    // cout << "Removing Index " << rem_idx << endl << endl;
    // list.removeAt(rem_idx);
    
    list_arr = list.getList();
    list_rev = list.getReversedList();
    
    // cout << list.front() << " || " << list.back() << endl;
    
    for (auto num : list_arr) {
        cout << num << " ";
    }
    cout << endl;
    for (auto num : list_rev) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}