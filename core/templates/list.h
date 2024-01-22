#ifndef LIST_H
#define LIST_H

#include <cstddef>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    std::size_t size;

public:
    List() : head(nullptr), size(0) {}
    ~List();

    void push_back(const T& value);
    void popBack();
    void insert(std::size_t index, const T& value);
    void erase(std::size_t index);
    T get(std::size_t index) const;
    void set(std::size_t index, const T& value);
    std::size_t getSize() const;
    // Add other methods as needed
};

template <typename T>
List<T>::~List() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template <typename T>
void List<T>::popBack() {
    if (!head) {
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
    } else {
        Node* current = head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}

template <typename T>
void List<T>::insert(std::size_t index, const T& value) {
    if (index > size) {
        return;  // Invalid index
    }
    Node* newNode = new Node(value);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        for (std::size_t i = 1; i < index; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    size++;
}

template <typename T>
void List<T>::erase(std::size_t index) {
    if (index >= size || !head) {
        return;  // Invalid index or empty list
    }
    Node* temp;
    if (index == 0) {
        temp = head;
        head = head->next;
    } else {
        Node* current = head;
        for (std::size_t i = 1; i < index; ++i) {
            current = current->next;
        }
        temp = current->next;
        current->next = current->next->next;
    }
    delete temp;
    size--;
}

template <typename T>
T List<T>::get(std::size_t index) const {
    if (index >= size || !head) {
        // Handle error, such as returning a default value or throwing an exception
        return T();
    }
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void List<T>::set(std::size_t index, const T& value) {
    if (index >= size || !head) {
        return;  // Invalid index or empty list
    }
    Node* current = head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    current->data = value;
}

template <typename T>
std::size_t List<T>::getSize() const {
    return size;
}

#endif // LIST_H
