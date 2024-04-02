#include "linkedlist.hpp"

int main() {
    auto list = new LinkedList<int>();

    for (int i = 0; i < 1000; i++) 
        list->push(new int(i));

    std::cout << "should be 0: " << *list->getHead() << ", should be 999: " << *list->getTail() << std::endl;

    list->swap(0, 999);
    std::cout << "swapping head and tail" << std::endl;
    std::cout << "0: " << *list->get(0) << ", 4: " << *list->getTail() << std::endl;

    std::cout << "size: " << list->len() << std::endl;

    list->remove(list->len() - 1);
    list->remove(0);
    list->remove(555);

    list->pop();
    list->pop();
    list->pop();

    std::cout << "size: " << list->len() << std::endl;

    return 0;
}