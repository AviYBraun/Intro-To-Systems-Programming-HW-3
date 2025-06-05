#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    struct Node{
        T value = T();
        Node* next = nullptr;
    };

    template <typename T>
    class SortedList {
        //begin with int version, test and then change everything to T
        // use dummy head, same as with blockchain
        Node<T>* head = nullptr;
        unsigned int length = 0;

    public:
        //default c'tor to list with dummy cell
        SortedList() {
            head = new Node<T>;
            head->next = nullptr;
            length = 0;
        };
        //copy c'tor
        SortedList(const SortedList& toCopy){
            //create dummy pointer
            head = new Node<T>;
            head -> next = nullptr;
            length = 0;

            Node<T>* source = toCopy.head->next;
            Node<T>* tail = head;

            while(source){
                Node<T>* newNode = new Node<T>;
                newNode->value = source->value;
                tail->next = newNode;
                tail = newNode;
                source = source->next;
                ++length;
            }
            }



        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template <class T>
    class SortedList<T>::ConstIterator {
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
}

