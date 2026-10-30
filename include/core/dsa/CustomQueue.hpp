#ifndef CUSTOM_QUEUE_HPP
#define CUSTOM_QUEUE_HPP

#include <stdexcept>
#include <cstddef>

/**
 * @brief Custom FIFO Queue implementation using a singly linked list.
 * Phục vụ nghiệp vụ: Hàng đợi khám bệnh theo thứ tự đến trước khám trước (FIFO).
 */
template <typename T>
class CustomQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    size_t count;

public:
    CustomQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~CustomQueue() {
        clear();
    }

    // Disable copy for simplicity or implement deep copy
    CustomQueue(const CustomQueue& other) : frontNode(nullptr), rearNode(nullptr), count(0) {
        Node* curr = other.frontNode;
        while (curr) {
            push(curr->data);
            curr = curr->next;
        }
    }

    CustomQueue& operator=(const CustomQueue& other) {
        if (this != &other) {
            clear();
            Node* curr = other.frontNode;
            while (curr) {
                push(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    void push(const T& val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        count--;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
    }

    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        return frontNode->data;
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        return frontNode->data;
    }

    bool isEmpty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif // CUSTOM_QUEUE_HPP
