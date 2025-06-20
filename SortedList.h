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
/**
 * @brief template Class for Sorted List
 */
    template <typename T>
    class SortedList {
        Node<T>* head = nullptr;
        int size = 0;

    public:
        /**
    * @brief default constructor
    */
        SortedList() = default;
        /**
    * @brief copy constructor
    *
    * @param toCopy reference to the list we want to copy
    */
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
        /**
    * @brief basic destructor
    */
        ~SortedList() {
            Node<T>* current = head;
            while(current){
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
        }
        /**
    * @brief assignment operator overload
    *
    * @param toCopy reference to the list we want to copy
    * @return reference to the newly assigned list
    */
        SortedList& operator =(const SortedList& toCopy){
            if (this == &toCopy){
                return *this;
            }
            Node<T>* current = head;
            while(current){
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            size = 0;
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
        /**
    * @brief insert method
    *
    * @param x type determined variable to add to list
    */
        void insert(const T& x) {
            Node<T>** current = &head;

            while (*current && !(x > (*current)->value)) {
                current = &((*current)->next);
            }

            Node<T>* newNode = new Node<T>(x);
            newNode->next = *current;
            *current = newNode;
            ++size;
        }

        class ConstIterator;
        /**
    * @brief remove method to remove items based on iterator entry
    *
    * @param iterator points to index of item we want removed
    */
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
        /**
    * @brief method returning length of the list
    */
        int length() const {
            return size;
        }
        /**
    * @brief method which creates a new list based on filter through old list
    *
    * @param predicate bool function we will use to filter through list
    * @return filtered list
    */
        SortedList filter(bool(*predicate)(const T&)) {
            SortedList filtered;
            for (ConstIterator it = begin(); it != end(); ++it) {
                if (predicate(*it)) {
                    filtered.insert(*it);
                }
            }
            return filtered;
        }
        /**
    * @brief method which applies an operation to items in list
    *
    * @param operation operation function which we will use to operate on terms
    * @return applied list
    */
        SortedList apply(T(*operation)(const T&)) {
            SortedList applied;
            for (ConstIterator it = begin(); it != end(); ++it) {
                applied.insert(operation(*it));
            }
            return applied;
        }
        /**
    * @brief returns begin iterator
    */
        ConstIterator begin() const{
            return ConstIterator(head, 0);
        }
        /**
    * @brief returns end iterator
    */
        ConstIterator end() const{
            return ConstIterator(nullptr, size);
        }
    };
    /**
        * @brief subclass ConstIterator
        *
        */
    template <class T>
    /**
    * @brief basic format of iterator, including index member
    */
    class SortedList<T>::ConstIterator
    {
        int index;
        const Node<T>* current;
        /**
    * @brief constructor - inside private to ensure it cannot be used outside of class
    *
    * @param node pointer to node iterator points to
    * @param givenIndex index of the given node
    */
        ConstIterator(const Node<T>* node, int givenIndex) : index(givenIndex), current(node) {}
        friend class SortedList;

    public:
        /**
    * @brief default copy c'tor
    */
        ConstIterator(const ConstIterator& toCopy) = default;
        /**
    * @brief default assignment operator
    */
        ConstIterator& operator=(const ConstIterator& toCopy) = default;
        /**
    * @brief default d'tor
    */
        ~ConstIterator() = default;
        /**
    * @brief * operator for referencing
    */
        const T& operator*() const{
            return current->value;
        }
        /**
    * @brief ++ increment operator
    */
        ConstIterator& operator++(){
            if(current == nullptr){
                throw std::out_of_range("Out of Bounds!");
            }
            ++index;
            current = current->next;
            return *this;
        }
        /**
    * @brief != operator
    */
        bool operator !=(const ConstIterator& toCompare) const{
            return (!(current == toCompare.current));
        }
    };
}