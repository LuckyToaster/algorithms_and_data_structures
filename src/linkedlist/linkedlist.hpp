#include <cstddef>
#include <iostream>

template <typename T> class Node {
    public: 
        T* data;
        Node* prev;
        Node* next;
        Node(T* data);
        ~Node();
};


template <typename T> class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
        bool circular;
        Node<T>* getNodeAt(size_t idx);
    public:
        LinkedList();
        ~LinkedList();
        bool push(T* elem);
        bool pop();
        bool swap(size_t a, size_t b); 
        bool insert(T* elem, size_t idx); 
        bool isCircular(); 
        bool makeCircular(bool circular);
        bool remove(size_t idx); 
        T* getHead(); 
        T* getTail(); 
        T* get(size_t idx);
        size_t len();
};


// ===========================
// NODE METHODS IMPLEMENTATION
// ===========================

template <typename T> Node<T>::Node(T* data) {
    this->data = data;
    next = nullptr;
    prev = nullptr;
}


template <typename T> Node<T>::~Node() {
    delete data; 
    prev = nullptr;
    next = nullptr;
}


// =================================
// LINKEDLIST METHODS IMPLEMENTATION
// =================================

template <typename T> LinkedList<T>::LinkedList() {
    size = 0;
    head = nullptr;
    tail = nullptr;
    circular = false;
}


template <typename T> LinkedList<T>::~LinkedList() {
    auto current = head;
    while (current != nullptr) {
        auto next = current->next;
        delete current;
        current = next;
    }
    head = nullptr; 
    tail = nullptr; 
    circular = false;
    size = 0; 
}


template <typename T> bool LinkedList<T>::push(T* elem) {
    auto node = new Node(elem);
    if (node == nullptr) return false;
    if (size == 0) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    size++;
    return true;
}


template <typename T> bool LinkedList<T>::pop() {
    if (size == 0) return false;
    if (size == 1) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else {
        auto tailptr = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tailptr;
    }
    size--;
    return true;
}


template <typename T> bool LinkedList<T>::insert(T* elem, size_t idx) {
    if (idx > size - 1) return false;

    auto newnode = new Node(elem);

    if (idx == 0) { // if pushing to head
        head->prev = newnode;
        newnode->next = head;
        head = newnode;
    } else if (idx == size - 1) { // if pushing to tail
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    } else { // if inserting anywhere else
        auto current = head;
        for (size_t i = 0; i < idx - 1; i++) current = current->next;
        newnode->next = current->next;
        newnode->prev = current;
        current->next = newnode;
        newnode->next->prev = newnode;
    }

    if (circular) {
        head->prev = tail;
        tail->next = head;
    }

    return true;
}


template <typename T> bool LinkedList<T>::swap(size_t a, size_t b) {
    if (a > size - 1 || b > size - 1) return false;
    if (a == b) return true;
    if (a > b) std::swap(a, b);
    
    auto a_node = head;
    for (size_t i = 0; i < a; i++) 
        a_node = a_node->next;

    auto b_node = a_node;
    for (size_t i = 0, dst = b - a; i < dst; i++) 
        b_node = b_node->next;

    std::swap(a_node->data, b_node->data);

    return true;
}


template <typename T> bool LinkedList<T>::remove(size_t idx) {
    if (idx > size - 1) return false;
    if (idx == size - 1) return pop(); 

    if (idx == 0) {
        auto nextNode = head->next;
        delete head;
        head = nextNode;
        circular ? head->prev = tail : head->prev = nullptr;
    } else {
        auto current = getNodeAt(idx);
        auto next = current->next;
        auto prev = current->prev;
        next->prev = prev;
        prev->next = next;
        delete current;
    }

    size--;
    return true;
}


template <typename T> T* LinkedList<T>::getHead() {
    if (size == 0) return nullptr;
    return head->data;
}


template <typename T> T* LinkedList<T>::getTail() {
    if (size == 0) return nullptr;
    return tail->data;
}


template <typename T> size_t LinkedList<T>::len() {
    return size;
}


template <typename T> bool LinkedList<T>::isCircular() {
    return circular;
}


template <typename T> T* LinkedList<T>::get(size_t idx) {
    if (size == 0 || idx > size - 1 ) return nullptr;
    if (idx == 0) return head->data;
    if (idx == size - 1) return tail->data;

    auto node = getNodeAt(idx);
    return node->data;
}


template <typename T> bool LinkedList<T>::makeCircular(bool yayornay) {
    if (size < 2) return false;
    if ((yayornay && circular) || (!yayornay && !circular)) return true;

    if (circular) {
        head->prev = tail; 
        tail->next = head;
        circular = true;
    } else {
        head->prev = nullptr;
        tail->next = nullptr;
        circular = false;
    }
}


template <typename T> inline 
Node<T>* LinkedList<T>::getNodeAt(size_t idx) {
    auto node = head;
    for (int i = 0; i < idx; i++) 
        node = node->next;
    return node;
}