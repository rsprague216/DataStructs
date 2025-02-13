#include <iostream>

template <typename T>
class DynamicArray {
    private:
        T* arr;
        int size;
        int capacity;
    public:
        DynamicArray(int capacity) : capacity(capacity), size(0) {
            arr = new T[capacity];
        }

        int get(int idx) {
            if (size == 0 || idx >= size)
                return -1;
            return arr[idx];
        }

        bool set(int idx, int val) {
            if (idx >= size || idx < 0)
                return false;
            arr[idx] = val;
            return true;
        }

        void pushback(int val) {
            if (size == capacity)
                resize();
            arr[size++] = val;
        }

        void resize() {
            T* newArr = new T[capacity *= 2];
            for (int i = 0; i < size; i++)
                newArr[i] = arr[i];
            delete[] arr;
            arr = newArr;
        }

        int pop() {
            if (size == 0)
                return -1;
            size--;
            int val = arr[size];
            arr[size] = 0;
            return val;
        }

        int getSize() {
            return size;
        }

        int getCapacity() {
            return capacity;
        }

        ~DynamicArray() {
            delete[] arr;
        }
};

int main() {
    int size = 0;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    DynamicArray<int> arr(size);
    
    std::cout << "array size: " << arr.getSize() << " || array capacity: " << arr.getCapacity() << std::endl << std::endl;
    for (int i = 0; i < size + 1; i++)
        arr.pushback(i);

    for (int i = 0; i < arr.getSize(); i++)
        std::cout << arr.get(i) << " ";
    
    std::cout << std::endl << std::endl << "array size: " << arr.getSize() << " || array capacity: " << arr.getCapacity() << std::endl << std::endl;

    std::cout << "popping element " << arr.pop() << std::endl;
    
    std::cout << "array size: " << arr.getSize() << " || array capacity: " << arr.getCapacity() << std::endl;
    
    return 0;
}