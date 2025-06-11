#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    struct Node{
        T value;
        Node* next = nullptr;
        Node(const T& val) : value(val), next(nullptr) {}
    };

    template <typename T>
    class SortedList {
        // use dummy head, same as with blockchain
        Node<T>* head = nullptr;
        int size = 0;

    public:
        //default c'tor to list with dummy cell
        SortedList() = default;
        //copy c'tor
        SortedList(const SortedList& toCopy) : head(nullptr), size(0){
            Node<T>* source = toCopy.head;
            Node<T>** tail = &head;
            while (source) {
                *tail = new Node<T>(source->value);
                tail = &((*tail)->next);
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
            head = nullptr;
            size = 0;
            //now actually copy everything
            Node<T>* source = toCopy.head;
            Node<T>** tail = &head;
            while(source){
                *tail = new Node<T>(source->value);
                tail = &((*tail)->next);
                source = source->next;
                ++size;
            }
        return *this;
        }
        void insert(const T& x) {
            Node<T>** current = &head;
            while (*current && x <= (*current)->value) {
                current = &((*current)->next);
            }
            Node<T>* newNode = new Node<T>(x);
            newNode->next = *current;
            *current = newNode;
            ++size;
        }
        class ConstIterator;
        void remove(ConstIterator iterator) {
            if (!(iterator != end())) return;
            int index = iterator.index;
            if (index >= size) {
                throw std::out_of_range("Iterator out of range");
            }
            Node<T>** current = &head;
            for (int i = 0; i < index; ++i) {
                current = &((*current)->next);
            }
            Node<T>* toDelete = *current;
            *current = toDelete->next;
            delete toDelete;
            --size;
        }
        int length() const {
            return size;
        }
        SortedList filter(bool(*predicate)(const T&)) {
            SortedList filtered;
            for (ConstIterator it = begin(); it != end(); ++it) {
                if (predicate(*it)) {
                    filtered.insert(*it);
                }
            }
            return filtered;
        }
        SortedList apply(T(*operation)(const T&)) {
            SortedList applied;
            for (ConstIterator it = begin(); it != end(); ++it) {
                applied.insert(operation(*it));
            }
            return applied;
        }
        //begin and end iterator methods for sortedlist
        ConstIterator begin() const{
            return ConstIterator(head, 0);
        }
        ConstIterator end() const{
            return ConstIterator(nullptr, size);
        }
    };

    template <class T>
    class SortedList<T>::ConstIterator
    {
        //body of the class - iterator wil point to a node
        int index;
        const Node<T>* current;

        //c'tor - receives a node and an index
        ConstIterator(const Node<T>* node, int givenIndex) : current(node), index(givenIndex) {}
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