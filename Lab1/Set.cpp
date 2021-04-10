#include "Set.hpp"

template<typename T>
void print(Set<T> set, std::string name) {

    std::cout << name << ": ";
    set.print();
}

template<typename T>
void testUnion(Set<T> set1, Set<T> set2) {

    Set<std::string> unionSet = Set<std::string>::Union(set1, set2);
    print<std::string>(unionSet, "Union");
}

template<typename T>
void testIntersection(Set<T> set1, Set<T> set2) {

    Set<std::string> intersectionSet = Set<std::string>::Intersection(set1, set2);
    print<std::string>(intersectionSet, "Intersection");

}

template<typename T>
void testDifference(Set<T> set1, Set<T> set2) {

    Set<std::string> differenceSet = Set<std::string>::Difference(set1, set2);
    print<std::string>(differenceSet, "Differnece");

}


int main() {

    // Set<std::string> set;

    // set.Insert(1);
    // set.Insert(3);
    // set.print();

    Set<std::string> set1;
    Set<std::string> set2;


    set1.Insert("Ala");
    set1.Insert("2");
    set1.Insert("Ma");
    set1.Insert("4");
    set1.Insert("Kota");

    set2.Insert("Ala");
    set2.Insert("Ala");
    set2.Insert("ma");
    set2.Insert("4");
    set2.Insert("Psa");
    
    print<std::string>(set1, "set1");
    print<std::string>(set2, "set2");
    testUnion<std::string>(set1, set2);
    testIntersection<std::string>(set1, set2);
    testDifference<std::string>(set1, set2);
}