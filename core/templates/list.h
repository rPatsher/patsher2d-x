#ifndef LIST_H
#define LIST_H

#include <list>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

public:
    // Custom iterator class for the List
    class Iterator {
    private:
        Node* current;

    public:
        // Constructor
        Iterator(Node* node) : current(node) {}

        // Dereference operator
        T& operator*() const {
            return current->data;
        }

        // Increment operator (pre-increment)
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        // Equality operator
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        // Inequality operator
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

private:
    Node* head;

public:
    // Constructor
    List() : head(nullptr) {}

    // Destructor
    ~List() {
        clear();
    }

    // Function to add an element to the back of the list
    void push_back(const T& element) {
        if (head == nullptr) {
            head = new Node(element);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(element);
        }
    }

    // Function to add an element to the front of the list
    void push_front(const T& element) {
        Node* newHead = new Node(element);
        newHead->next = head;
        head = newHead;
    }

    // Function to add an element to the back of the list using emplace_back
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (head == nullptr) {
            head = new Node(std::forward<Args>(args)...);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(std::forward<Args>(args)...);
        }
    }

    // Function to remove an element from the list
    void removeElement(const T& element) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->data != element) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
        }
    }

    // Function to remove an element at a specific position in the list
    void remove_at(size_t position) {
        if (position == 0 && head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* current = head;
            Node* previous = nullptr;
            size_t index = 0;

            while (current != nullptr && index < position) {
                previous = current;
                current = current->next;
                index++;
            }

            if (current != nullptr) {
                previous->next = current->next;
                delete current;
            }
        }
    }

    // Function to duplicate an element at a specific position in the list
    void duplicate_at(size_t position) {
        Node* current = head;
        size_t index = 0;

        while (current != nullptr && index < position) {
            current = current->next;
            index++;
        }

        if (current != nullptr) {
            Node* newNode = new Node(current->data);
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Function to get the data at a specific position in the list
    T get(size_t position) const {
        Node* current = head;
        size_t index = 0;

        while (current != nullptr && index < position) {
            current = current->next;
            index++;
        }

        if (current != nullptr) {
            return current->data;
        }

        // You might want to handle an error case here (e.g., throw an exception).
        // For simplicity, I'm returning a default-constructed T when position is out of bounds.
        return T();
    }

    // Function to set the data at a specific position in the list
    void set(size_t position, const T& value) {
        Node* current = head;
        size_t index = 0;

        while (current != nullptr && index < position) {
            current = current->next;
            index++;
        }

        if (current != nullptr) {
            current->data =current->data = value;
    }

    // Function to find the index of the first occurrence of a value
    size_t find(const T& value) const {
        Node* current = head;
        size_t index = 0;

        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }

        // Return a special value (e.g., std::numeric_limits<size_t>::max()) to indicate not found.
        return std::numeric_limits<size_t>::max();
    }

    // Function to find the index of the last occurrence of a value
    size_t rfind(const T& value) const {
        Node* current = head;
        size_t index = 0;
        size_t lastOccurrence = std::numeric_limits<size_t>::max();

        while (current != nullptr) {
            if (current->data == value) {
                lastOccurrence = index;
            }
            current = current->next;
            index++;
        }

        return lastOccurrence;
    }

    // Function to return the end iterator
    Iterator end() {
        return Iterator(nullptr);
    }

    // Function to find and return the local minimum element in the list
    T local() const {
        if (head == nullptr) {
            // Return a default-constructed T for an empty list.
            return T();
        }

        Node* current = head;
        T localMin = current->data;

        while (current != nullptr && current->next != nullptr) {
            if (current->data < current->next->data) {
                localMin = current->data;
            }
            current = current->next;
        }

        return localMin;
    }

    // Function to get the size of the list
    size_t getSize() const {
        size_t size = 0;
        Node* current = head;

        while (current != nullptr) {
            size++;
            current = current->next;
        }

        return size;
    }

    // Function to check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Function to clear the list
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Operator overloading: subscript operator []
    T& operator[](size_t index) {
        Node* current = head;
        size_t currentIndex = 0;

        while (current != nullptr && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }

        if (current != nullptr) {
            return current->data;
        }

        // You might want to handle an error case here (e.g., throw an exception).
        // For simplicity, I'm returning a reference to a default-constructed T when index is out of bounds.
        return (current->data);
    }

    // Operator overloading: equality operator ==
    bool operator==(const List& other) const {
        Node* currentThis = head;
        Node* currentOther = other.head;

        while (currentThis != nullptr && currentOther != nullptr) {
            if (currentThis->data != currentOther->data) {
                return false;
            }
            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }

        // Lists are equal only if they have the same number of elements and corresponding elements are equal.
        return currentThis == nullptr && currentOther == nullptr;
    }

    // Operator overloading: inequality operator !=
    bool operator!=(const List& other) const {
        return !(*this == other);
    }

    // Operator overloading: assignment operator =
    List& operator=(const List& other) {
        if (this != &other) {
            // Clear current list
            clear();

            // Copy elements from other list
            Node* currentOther = other.head;
            while (currentOther != nullptr) {
                push_back(currentOther->data);
                currentOther = currentOther->next;
            }
        }

        return *this;
    }

    // Function to insert an element at a specific position in the list
    Iterator insert(const Iterator& position, const T& value) {
        if (position.current == nullptr) {
            push_back(value);
            return Iterator(nullptr);
        }

        Node* newNode = new Node(value);
        newNode->next = position.current->next;
        position.current->next = newNode;

        return Iterator(newNode);
    }

    // Function to erase an element at a specific position in the list
    Iterator erase(const Iterator& position) {
        if (position.current == nullptr || head == nullptr) {
            return Iterator(nullptr);
        }

        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current != position.current) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous !=nullptr) {
                previous->next = current->next;
                delete current;
                return Iterator(previous->next);
            } else {
                head = current->next;
                delete current;
                return Iterator(head);
            }
        }

        return Iterator(nullptr);
    }

    // Function to push an element to the front of the list using emplace_front
    template<typename... Args>
    void emplace_front(Args&&... args) {
        Node* newHead = new Node(std::forward<Args>(args)...);
        newHead->next = head;
        head = newHead;
    }

    // Function to pop an element from the front of the list
    void pop_front() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to pop an element from the back of the list
    void pop_back() {
        if (head == nullptr) {
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
    }

    // Function to get the front element of the list
    T& front() {
        if (head != nullptr) {
            return head->data;
        }

        // You might want to handle an error case here (e.g., throw an exception).
        // For simplicity, I'm returning a reference to a default-constructed T for an empty list.
        return (head->data);
    }

    // Function to get the const front element of the list
    const T& front() const {
        if (head != nullptr) {
            return head->data;
        }

        // You might want to handle an error case here (e.g., throw an exception).
        // For simplicity, I'm returning a reference to a default-constructed T for an empty list.
        return (head->data);
    }

    // Function to get the back element of the list
    T& back() {
        if (head == nullptr) {
            // You might want to handle an error case here (e.g., throw an exception).
            // For simplicity, I'm returning a reference to a default-constructed T for an empty list.
            return (head->data);
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        return current->data;
    }

    // Function to get the const back element of the list
    const T& back() const {
        if (head == nullptr) {
            // You might want to handle an error case here (e.g., throw an exception).
            // For simplicity, I'm returning a reference to a default-constructed T for an empty list.
            return (head->data);
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        return current->data;
    }
};

};
#endif // LIST_H
