#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template <typename T>
    class SortedList {

        struct Node {
            T value;
            Node* next;
            explicit Node(const T& value) : value(value), next(nullptr) {}
        };

        Node* head;
        Node* tail;
        int size;

    public:
        SortedList() : head(nullptr), tail(nullptr), size(0) {}
        void insert(const T& value)  {
            Node* newNode = new Node(value);
            if (!head) { // empty
                head = tail = newNode;
                size = 1;
                return;
            }
            if (value > head->value) { // bigger than head
                newNode->next = head;
                head = newNode;
                size++;
                return;
            }
            Node* current = head;
            while (current->next && current->next->value > value)
                current = current->next;

            newNode->next = current->next;
            current->next = newNode;
            if (!newNode->next)
                tail = newNode;
            size++;
        }

        SortedList(const SortedList& other) : head(nullptr), tail(nullptr), size(0) {
            const Node* current = other.head;
            while (current) {
                insert(current->value);   // reuse insert to preserve sorted order
                current = current->next;
            }
        }

        SortedList& operator=(const SortedList& other) {
            if (this == &other)return *this;
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = nullptr;
            size = 0;
            const Node* current = other.head;
            while (current) {
                insert(current->value);
                current = current->next;
            }
            return *this;
        }
        ~SortedList() {
            Node* current = head;
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        class ConstIterator;
        ConstIterator begin() const { return ConstIterator(head); }
        ConstIterator end() const { return ConstIterator(nullptr); }
        class ConstIterator {
            const Node* current;
            friend class SortedList<T>;

        public:
            ConstIterator() : current(nullptr) {}
            explicit ConstIterator(const Node* node) : current(node) {}

            ConstIterator& operator++() {
                if (!current) throw std::out_of_range("Iterator reached end");
                current = current->next;
                return *this;
            }

            const T& operator*() const {
                if (!current) throw std::out_of_range("Dereferencing end()");
                return current->value;
            }

            const T* operator->() const {                       // ✅ added
                if (!current) throw std::out_of_range("Dereferencing end()");
                return &(current->value);
            }

            bool operator!=(const ConstIterator& other) const { return current != other.current; }
            bool operator==(const ConstIterator& other) const { return current == other.current; }
        };


        void remove(ConstIterator it) {
            if (it == end() || !it.current) {  // Check for end iterator
                return;  // Just return, don't throw
            }

            if (it.current == head) {
                Node* temp = head;
                head = head->next;
                if (temp == tail) {
                    tail = nullptr;
                }
                delete temp;
                size--;
                return;
            }

            Node* prev = head;
            while (prev && prev->next != it.current)
                prev = prev->next;

            if (!prev || !prev->next)
                throw std::out_of_range("Iterator does not belong to this list");

            Node* target = prev->next;
            prev->next = target->next;
            if (target == tail)
                tail = prev;

            delete target;
            size--;
        }

         int length() const{return size;}
        SortedList<T> filter(bool (*predicate)(const T&)) const {
            SortedList<T> filtered;
            for (ConstIterator it = begin(); it != end(); ++it) {
                if (predicate(*it)) {
                    filtered.insert(*it);
                }
            }
            return filtered;
        }

        SortedList<T> apply(T (*operation)(const T&)) const {
            SortedList<T> applied;
            for (ConstIterator it = begin(); it != end(); ++it) {
                applied.insert(operation(*it));
            }
            return applied;
        }
        T& getMutable(const ConstIterator& it) {
            return const_cast<T&>(*it);
        }

    };

};