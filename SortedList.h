#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    struct Node{
        T value;
        Node* next = nullptr;
    };

    template <typename T>
    class SortedList {
        // use dummy head, same as with blockchain
        Node<T>* head = nullptr;
        unsigned int size = 0;

    public:
        //default c'tor to list with dummy cell
        SortedList() {
            head = new Node<T>;
            head->next = nullptr;
            size = 0;
        };
        //copy c'tor
        SortedList(const SortedList& toCopy){
            //create dummy pointer
            head = new Node<T>;
            head -> next = nullptr;
            size = 0;

            Node<T>* source = toCopy.head->next;
            Node<T>* tail = head;

            while(source){
                Node<T>* newNode = new Node<T>;
                newNode->value = source->value;
                tail->next = newNode;
                tail = newNode;
                source = source->next;
                ++size;
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
            size = 0;
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
                ++size;
            }
        return *this;
        }
        void insert(const T& x){
            //deal with empty lists
            if(!head->next){
                Node<T>* newNode = new Node<T>;
                newNode->value = x;
                newNode->next = nullptr;
                head->next = newNode;
                ++size;
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
                    ++size;
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
            ++size;
        }
        class ConstIterator;
        void remove(ConstIterator iterator){
            //this function assumes for the existence of the iterator class and specifically the
            //() method that allows us to access any term in the list

            //if the iterator is the end, there is nothing to remove
            if(!(iterator != end())){
                return;
            }

            unsigned int index = iterator.index;
            if(index >= size){
                throw std::out_of_range("Iterator out of range");
            }
            //deal with removing first term
            if(index == 0){
                Node<T>* toDelete = head->next;
                head->next = toDelete->next;
                delete toDelete;
                --size;
                return;
            }
            Node<T>* previous = head;
            //move to node right before one we want to remove
            for (unsigned int i = 0; i < index; ++i){
                previous = previous->next;
            }
            Node<T>* toDelete = previous->next;
            previous->next = toDelete->next;
            delete toDelete;
            --size;

        }
        unsigned int length(){
            return size;
        }


        //begin and end iterator methods for sortedlist
        ConstIterator begin() const{
            return ConstIterator(head->next, 0);
        }
        ConstIterator end() const{
            return ConstIterator(nullptr, size);
        }
    };

    template <class T>
    class SortedList<T>::ConstIterator
    {
        //body of the class - iterator wil point to a node
        unsigned int index;
        const Node<T>* current;

        //c'tor - receives a node and an index
        ConstIterator(const Node<T>* node, unsigned int givenIndex){
            index = givenIndex;
            current = node;
        }
        //allow set to call the c'tor
        friend class SortedList;

    public:
        //copy c'tor
        ConstIterator(const ConstIterator& toCopy) = default;
        //assignment operator
        ConstIterator& operator=(const ConstIterator& toCopy) = default;
        //d'tor
        ~ConstIterator() = default;
        //returns element iterator points to - this can be entirely const, since we don't want the
        //user to be able to change anything
        const T& operator*() const{
            return current->value;
        }
        //moves the pointer up one
        ConstIterator& operator++(){
            //check whether or not we are at end() iterator. if not, even if current-> next
            //= nullptr, we can move the iterator there, essentially making it end()
            if(current == nullptr){
                throw std::out_of_range("Out of Bounds!");
            }
            ++index;
            current = current->next;
            return *this;
        }
        //returns true if the iterators are not the same
        bool operator !=(const ConstIterator& toCompare) const{
            return (!(current == toCompare.current));
        }
    };
}