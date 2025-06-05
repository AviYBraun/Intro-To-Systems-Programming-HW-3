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
        ~SortedList() {
            Node<T>* current = head;
            while(current){
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
        }
        //assignment operator - returns reference
        SortedList& operator =(const SortedList& toCopy){
            //avoid self-assignment
            if (this == &toCopy){
                return *this;
            }
            //delete info from current - loop through and delete
            Node<T>* current = head;
            while(current){
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
            //new dummy pointer
            head = new Node<T>;
            head -> next = nullptr;
            length = 0;
            //now actually copy everything
            Node<T>* source = toCopy.head->next;
            Node<T>* tail = head;
            while(source){
                Node<T>* newNode = new Node<T>;
                newNode->value = source->value;
                newNode->next = nullptr;
                //tail is a pointer to a node - the following command sends head's pointer to
                //newNode, and then tail itself goes to point to that next object
                tail->next = newNode;
                tail = newNode;

                source = source->next;
                ++length;
            }
        return *this;
        }
        void Insert(const T& x){
            //deal with empty lists
            if(!head->next){
                Node<T>* newNode = new Node<T>;
                newNode->value = x;
                newNode->next = nullptr;
                head->next = newNode;
                ++length;
                return;
            }
            //traverse the list until you find an element smaller than it
            Node<T>* iterator = head->next;
            while(iterator->next){
                if(x > iterator->value){
                    //create new node with smaller value, which points at iterator->next
                    Node<T>* newNode = new Node<T>;
                    newNode->value = iterator->value;
                    newNode->next = iterator->next;
                    //change current node value to x
                    iterator->value = x;
                    iterator->next = newNode;
                    ++length;
                    return;
                }
                //keep moving along the list
                iterator = iterator->next;
            }
            //we've gotten to the end of the list - check > for last list node
            if(x > iterator->value){
                Node<T>* newNode = new Node<T>;
                newNode->value = iterator->value;
                newNode->next = iterator->next;
                //change current node value to x
                iterator->value = x;
                iterator->next = newNode;
            } else{
                Node<T>* newNode = new Node<T>;
                newNode->value = x;
                newNode->next = nullptr;
                iterator->next = newNode;
            }
            ++length;
        }
        class ConstIterator;
        void Remove(ConstIterator iterator){
            //this function assumes for the existence of the iterator class and specifically the
            //() method that allows us to access any term in the list

            //if the iterator is the end, there is nothing to remove
            if(iterator == end()){
                return;
            }

            unsigned int index = iterator.index;
            if(index >= length){
                throw std::out_of_range("Iterator out of range");
            }
            //deal with removing first term
            if(index == 0){
                Node<T>* toDelete = head->next;
                head->next = toDelete->next;
                delete toDelete;
                --length;
                return;
            }
            Node<T>* previous = head->next;
            //move to node right before one we want to remove
            for (unsigned int i = 0; i < index; ++i){
                previous = previous.next;
            }
            Node<T>* toDelete = previous->next;
            previous->next = toDelete->next;
            delete toDelete;
            --length;

        }


        //begin and end iterator methods for sortedlist
        ConstIterator begin(){
            return ConstIterator(head->next, 0);
        }
        ConstIterator end(){
            return ConstIterator(nullptr, length);
        }
        ConstIterator begin() const{
            return ConstIterator(head->next, 0);
        }
        ConstIterator end() const{
            return ConstIterator(nullptr, length);
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
        //body of the class - iterator has a pointer to a SortedList, and an integer denoting index
        const SortedList* list;
        unsigned int index;
        Node<T>* current;

        //c'tor - this one needs to be in private so only sorted list can call it
        ConstIterator(Node<T>* nodePointer, unsigned int index){

        }
        //allow set to call the c'tor
        friend class SortedList;

    public:
        //copy c'tor
        ConstIterator(ConstIterator& toCopy){


        }
        //assignment operator
        ConstIterator& operator=(const ConstIterator& toCopy){

        }
        //d'tor
        ~ConstIterator(){

        }
        //returns element iterator points to
        const T& operator*() const{

        }
        //moves the pointer up one
        ConstIterator& operator++(){

        }
        //returns true if the iterators are not the same
        bool operator !=(const ConstIterator& toCompare){

        }



    };
}

