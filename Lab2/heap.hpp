#ifndef HEAP_HXX
#define HEAP_HXX

#include <vector>
#include <iostream>
template<class T>
class Heap {


    private:

        int size_;
        std::pair<T, int>* array;

        void heapify(int i) {                           // maintains heap structure
            int largest = i;
            int root = largest;
            int lChild = root * 2 + 1;
            int rChild = root * 2 + 2;

            if (lChild < size_ && array[largest].second < array[lChild].second) {

                largest = lChild;
            }

            if (rChild < size_ && array[rChild].second > array[largest].second) {

                largest = rChild;
            }

            if (largest != root) {

                swap(largest, root);
                heapify(largest);
            }

        }
        
    public:

        Heap(unsigned int heapSize) 
            : size_(0)
            , array(new std::pair<T, int>[heapSize]) {}

        Heap() 
            : size_(0) 
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

            std::pair<T, int>* newArray = new std::pair<T, int>[size_ + 1];

            for (int i = 0; i < size_; ++i) {

                newArray[i] = array[i]; 
            }

            newArray[size_] = x;

            delete[] array;

            array = newArray;

            for (int i = size_; array[(i - 1) / 2].second < array[i].second; i = (i - 1) / 2) {

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

                if (array[i * 2 + 1].second > array[i * 2 + 2].second) {

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

                if (array[i].second < array[i * 2 + 1].second 
                    || ((i * 2 + 2) < size_ && array[i].second < array[i * 2 + 2].second)) {

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

        // compare element e wtih element of the array on position index
        // if the same increase priority of this element by 1
        // if at least one element's priority was increased, heapify all heap in order to 
        // maintain heap structure
        void checkAndIncrease(std::pair<T, int> e, int priority) {

            int numberOfIncreasedPriorities = 0;


            for (int i = 0; i < size_; ++i) {

                if (array[i].second == e.second && array[i].first.compare(e.first) == 0) {

                    std::cout << e.first << " " << e.second << "\n";
                    array[i].second = priority;
                    numberOfIncreasedPriorities++;
                }
            }

            if (numberOfIncreasedPriorities != 0 && !check()) {

                for (int i = size_ - 1; i >= 0; --i) {

                    heapify(i);
                }
            }
        }


};

#endif