#pragma once
#include "_ns.h"
#include "allocator.h"
#include "traits.h"

// Pending improval.
// Basic linkedlist.
_SYS_NS
template <typename T>
class linked_list {
public:
    struct Node {
        T data;
        Node* next;


        Node(const T& value) : data(value), next(nullptr) {
        
        }
    };
private:

    Node* head;
    size_t list_size;
    sys::alloc* alloca;
public:
    linked_list() : head(NULL), list_size(0), alloca(NULL){

    }
    linked_list(sys::alloc* alloca) : head(nullptr), list_size(0), alloca(alloca) {}

    ~linked_list() {
        clear();
    }

    linked_list(const linked_list& other) : head(nullptr), list_size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    linked_list& operator=(const linked_list& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    linked_list(linked_list&& other) noexcept : head(other.head), list_size(other.list_size) {
        other.head = nullptr;
        other.list_size = 0;
    }

    linked_list& operator=(linked_list&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            list_size = other.list_size;
            other.head = nullptr;
            other.list_size = 0;
        }
        return *this;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        list_size++;
    }

    void push_back(const T& value) {
        Node* newNode = alloca->malloc<Node>();

        if (sys::is_fundamental<T>::value)
            *newNode = value;
        else
            new (newNode)Node(value);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        list_size++;
    }
    const T& front() {
        __expect(head!=NULL);
        return head->data;
    }
    void pop_front() {
        if (head == nullptr) return;
        __expect(alloca != NULL);
        Node* temp = head;
        head = head->next;
        alloca->unsafe_free(temp);
        typed_destructor<Node>(temp);
        list_size--;
    }

    void clear() {
        __expect(alloca != NULL);

        while (head != nullptr) {
            pop_front();
        }
    }

    size_t size() const {
        return list_size;
    }

    bool empty() const {
        return head == nullptr;
    }
};

_SYS_ENS