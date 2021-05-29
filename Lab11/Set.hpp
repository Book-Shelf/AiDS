#ifndef SET_HPP
#define SET_HPP

#include <vector>
#include <iostream>

template<class T>
class Set {

    private:
    int _size;
    std::vector<T> set;


    typename std::vector<T>::iterator isMember(T x) {

        for (typename std::vector<T>::iterator it = set.begin(); it < set.end(); ++it) {

            if (*it == x) return it;
        }

        return set.end();
    }


    public:
    Set() : _size(0) {}

    ~Set() {}


    int size() {

        return _size;
    }


    void Insert(T value) {

        if (isMember(value) != set.end()) {

            return ;
        }

        set.push_back(value);
        _size++;
    }


    T Pop(T x) {

        typename std::vector<T>::iterator it;
        T erasedVal;

        if ((it = isMember(x)) != set.end()) {
            std::cerr << "There is no such element in Set\n";
            return -1;
        }

        erasedVal = *it;
        set.erase(it);
        return erasedVal;
    }


    bool IsMember(T x) {
        
        return isMember(x) != set.end();
    }


    static Set<T> Union(Set<T> set1, Set<T> set2) {

        Set<T> newSet;

        for (int i = 0; i < set1.size(); ++i) {

            newSet.Insert(set1.set.at(i));
        }
        
        for (int i = 0; i < set2.size(); ++i) {

            newSet.Insert(set2.set.at(i));
        }

        return newSet;
    }


    static Set<T> Intersection(Set<T> set1, Set<T> set2) {

        Set<T> newSet;

        for (int i = 0; i < set2.size(); i++) {
            if (set1.isMember(set2.set.at(i)) != set1.set.end()) {

                newSet.Insert(set2.set.at(i));
            }
        }

        return newSet;
    }


    static Set<T> Difference(Set<T> set1, Set<T> set2) {

        Set<T> newSet;
        for (int i = 0; i < set1.size(); i++) {

            if (set2.isMember(set1.set.at(i)) == set2.set.end()) {

                newSet.Insert(set1.set.at(i));
            }
        }

        return newSet;
    }


    void print() {

        std::cout << "{";

        for(T x : set) {
            std::cout << x << ", "; 
        }

        std::cout << (_size != 0 ? "\b\b}\n" : "}\n");
    }

};


#endif