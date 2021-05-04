#ifndef HEAP_HXX
#define HEAP_HXX

#include <vector>
#include <iostream>
template<class T>
class Heap {


    private:

        int size_;
        int capacity;
        std::pair<T, int>* array;

        void heapify(int i) {                           // maintains heap structure
            int smallest = i;
            int root = smallest;
            int lChild = root * 2 + 1;
            int rChild = root * 2 + 2;

            if (lChild < size_ && array[smallest].second > array[lChild].second) {

                smallest = lChild;
            }

            if (rChild < size_ && array[rChild].second < array[smallest].second) {

                smallest = rChild;
            }

            if (smallest != root) {

                swap(smallest, root);
                heapify(smallest);
            }

        }
        
    public:

        Heap(unsigned int heapSize) 
            : size_(0)
            , capacity(heapSize)
            , array(new std::pair<T, int>[heapSize]) {}

        Heap() 
            : size_(0) 
            , capacity(0)
            , array(new std::pair<T, int>[0]) {}

        ~Heap() {

            delete[] array;
        }

        void build(const std::vector<std::pair<T, int>>& vec) {
            size_ = 0;
            delete[] array;
            array = new std::pair<T, int>[vec.size()];

            for (unsigned int j = 0; j < vec.size(); ++j) {
                array[j] = vec[j];
                ++size_;
            }
            // std::cout << array[0] << "\n";

            for (int i = size_ - 1; i >= 0; --i) {

                heapify(i);
            }

        }


        void push(std::pair<T, int> x) {                    

            if (size_ == capacity) {

                capacity = size_ + (size_ / 2);
                std::pair<T, int>* newArray = new std::pair<T, int>[capacity];


                for (int i = 0; i < size_; ++i) {

                    newArray[i] = array[i]; 
                }

                newArray[size_] = x;
                delete[] array;
                array = newArray;
            } else {

                array[size_] = x;
            }


            for (int i = size_; array[(i - 1) / 2].second > array[i].second; i = (i - 1) / 2) {

                swap(i, (i - 1) / 2);
            }


            ++size_;
        }

        std::pair<T, int> pop() {                            

            std::pair<T, int> temp = array[0];
            array[0] = array[size_ - 1];
            array[size_ - 1] = std::pair<T, int>();
            --size_;

            for (int i = 0; array[i].second < array[i * 2 + 1].second
                || array[i].second < array[i * 2 + 2].second;) {

                if (array[i * 2 + 1].second < array[i * 2 + 2].second) {

                    swap(i * 2 + 1, i);
                    i = i * 2 + 1;
                } else {

                    swap(i * 2 + 2, i);
                    i = i * 2 + 2; 

                }

            }

            return temp;
        }
        std::pair<T, int> rootElement() {                            

            return size_ != 0 ? array[0] : std::pair<T, int>();
        }
        int size() {                            

            return size_;
        }
        bool empty() {                           

            return size_ == 0;
        }
        bool check() {                           // checks if heap has heap structure 

            for (int i = 0; i < size_ / 2; ++i) {

                if (array[i].second > array[i * 2 + 1].second 
                    || ((i * 2 + 2) < size_ && array[i].second > array[i * 2 + 2].second)) {

                    return false;
                }

            }

            return true;
        }

        void swap(int a, int b) {

            std::pair<T, int> temp = array[a];

            array[a] = array[b];
            array[b] = temp;
        }

        void printHeap() {

            for (int i = 0; i < size_; ++i) {

                std::cout << array[i].second << " ";
            }

            std::cout << "\n";
        }


        void checkAndDecrease(std::pair<T, int> e, int priority) {

            int numberOfDecreasedPriorities = 0;


            for (int i = 0; i < size_; ++i) {

                if (array[i].second == e.second && array[i].first.compare(e.first) == 0) {

                    std::cout << e.first << " " << e.second << "\n";
                    array[i].second = priority;
                    numberOfDecreasedPriorities++;
                }
            }

            if (numberOfDecreasedPriorities != 0 && !check()) {

                for (int i = size_ - 1; i >= 0; --i) {

                    heapify(i);
                }
            }
        }


};

#endif