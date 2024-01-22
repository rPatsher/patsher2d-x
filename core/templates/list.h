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
    

   /**
 * @brief Removes all elements from the list.
 */
	template <typename T>
	void List<T>::clear();

/**
 * @brief Checks if the list is empty.
 * @return True if the list is empty, false otherwise.
 */
	template <typename T>
	bool List<T>::empty() const;

/**
 * @brief Adds an element to the front of the list.
 * @param value The value to be added to the front of the list.
 */
	template <typename T>
	void List<T>::pushFront(const T& value);

/**
 * @brief Removes the first element from the list.
 */
	template <typename T>
	void List<T>::popFront();

/**
 * @brief Removes consecutive duplicate elements from the list.
 */
	template <typename T>
	void List<T>::unique();

/**
 * @brief Sorts the list using a provided comparison function.
 * @param compare The comparison function defining the order of elements.
 */
	template <typename T>
	void List<T>::sort(std::function<bool(const T&, const T&)> compare);

/**
 * @brief Resizes the list to contain a specified number of elements.
 * @param newSize The new size of the list.
 * @param value The value to initialize new elements with (default is T()).
 */
	template <typename T>
	void List<T>::resize(std::size_t newSize, const T& value = T());

/**
 * @brief Swaps the contents of two lists.
 * @param otherList The list to swap with.
 */
	template <typename T>
	void List<T>::swap(List<T>& otherList);

/**
 * @brief Returns an iterator pointing to the first element of the list.
 * @return Iterator pointing to the first element.
 */
	template <typename T>
	typename List<T>::iterator List<T>::begin();
	
// Iterator class for List
template <typename T>
class List<T>::iterator {
private:
    Node* current;

public:
    iterator(Node* node) : current(node) {}

    T& operator*() const {
        return current->data;
    }

    iterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }

    bool operator!=(const iterator& other) const {
        return current != other.current;
    }

/**
 * @brief Returns an iterator pointing one past the last element of the list.
 * @return Iterator pointing one past the last element.
 */
	template <typename T>
	typename List<T>::iterator List<T>::end();
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



template <typename T>
void List<T>::merge(List<T>& otherList, std::function<bool(const T&, const T&)> compare) {
    if (&otherList == this) {
        return;  // Merging with itself
    }

    // Assumes both lists are sorted
    Node* thisCurrent = head;
    Node* otherCurrent = otherList.head;
    Node* prev = nullptr;

    while (thisCurrent && otherCurrent) {
        if (compare(thisCurrent->data, otherCurrent->data)) {
            prev = thisCurrent;
            thisCurrent = thisCurrent->next;
        } else {
            if (prev) {
                prev->next = otherCurrent;
            } else {
                head = otherCurrent;
            }

            Node* temp = otherCurrent->next;
            otherCurrent->next = thisCurrent;
            otherCurrent = temp;
            size += otherList.size;
            otherList.size = 0;
        }
    }
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    if (!pos.current) {
        return end();  // Invalid iterator
    }

    Node* toDelete = pos.current;
    iterator nextIter(toDelete->next);

    if (toDelete == head) {
        head = toDelete->next;
    } else {
        Node* prev = head;
        while (prev && prev->next != toDelete) {
            prev = prev->next;
        }
        if (prev) {
            prev->next = toDelete->next;
        }
    }

    delete toDelete;
    size--;

    return nextIter;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator first, iterator last) {
    iterator current = first;
    while (current != last) {
        current = erase(current);
    }
    return last;
}

template <typename T>
void List<T>::splice(iterator pos, List<T>& otherList) {
    if (pos.current == nullptr || &otherList == this) {
        return;  // Invalid iterator or attempting to splice with itself
    }

    if (otherList.head == nullptr) {
        return;  // Nothing to splice
    }

    if (pos.current == head) {
        head = otherList.head;
        otherList.head = nullptr;
    } else {
        Node* prev = head;
        while (prev && prev->next != pos.current) {
            prev = prev->next;
        }
        if (prev) {
            prev->next = otherList.head;
            otherList.head = nullptr;
        }
    }

    while (otherList.size > 0) {
        size++;
        otherList.size--;
    }
}
#endif // LIST_H
