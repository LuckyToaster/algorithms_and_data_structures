#include "linkedlist.hpp"


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


template <typename T> LinkedList<T>::LinkedList() {
    size = 0;
    head = nullptr;
    tail = nullptr;
    circular = false;
}


template <typename T> LinkedList<T>::~LinkedList() {
    //Node<T>* current = head;
    auto* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr; 
    tail = nullptr; 
    circular = false;
    size = 0; 
}


template <typename T> bool LinkedList<T>::push(T* elem) {
    Node<T>* node = new Node(elem);
    if (node == nullptr) return false;
    if (size == 0) {
        head = node;
        tail = node;
        size = 1;
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
        Node<T>* tailptr = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tailptr;
    }
    size--;
    return true;
}


// CHATGPT GENERATED
template <typename T> bool LinkedList<T>::swap(size_t a, size_t b) {
    if (a > size - 1 || b > size - 1 || a == b) return false;
    if (a > b) std::swap(a, b);

    Node<T>* prev1 = nullptr;
    Node<T>* prev2 = nullptr;
    Node<T>* curr1 = head;
    Node<T>* curr2 = head;

    for (size_t i = 0; i < a; ++i) {
        prev1 = curr1;
        curr1 = curr1->next;
    }
    for (size_t i = 0; i < b; ++i) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (prev1) prev1->next = curr2;
    else head = curr2;
    if (prev2) prev2->next = curr1;
    else head = curr1;

    std::swap(curr1->next, curr2->next);
    std::swap(curr1->prev, curr2->prev);

    return true;
}


template <typename T> bool LinkedList<T>::insert(T* elem, size_t idx) {
    if (idx > size - 1) return false;

    Node<T>* newnode = new Node(elem);

    if (idx == 0) {
        head->prev = newnode;
        newnode->next = head;
        head = newnode;
    } else if (idx == size - 1) {
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    } else {
        Node<T>* current = head;
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


template <typename T> bool LinkedList<T>::remove(size_t idx) {
    if (idx > size - 1) return false;
    Node<T>* current = head;
    for (size_t i = 0; i < idx - 1; i++) current = current->next;
    delete current->next;
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


template <typename T> T* LinkedList<T>::get(size_t idx) {
    if (size == 0 || idx > size - 1 ) return nullptr;
    if (idx == 0) return head->data;
    if (idx == size - 1) return tail->data;
    Node<T>* current = head;
    for (size_t i = 0; i < idx - 1; i++) current = current->next;
    return current->next->data;
}


template <typename T> size_t LinkedList<T>::len() {
    return size;
}


template <typename T> bool LinkedList<T>::isCircular() {
    return circular;
}


template <typename T> bool LinkedList<T>::makeCircular(bool circular) {
    if (size < 2) return false;
    if ((circular && this->circular) || (!circular && !this->circular)) return true;

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
