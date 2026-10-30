#ifndef CUSTOM_PRIORITY_QUEUE_HPP
#define CUSTOM_PRIORITY_QUEUE_HPP

#include <vector>
#include <stdexcept>
#include <functional>

/**
 * @brief Custom Priority Queue implementation based on a Binary Heap.
 * Phục vụ nghiệp vụ: Phân loại bệnh nhân cấp cứu (Triage) - mức ưu tiên cao hơn được xử lý trước.
 */
template <typename T, typename Compare = std::less<T>>
class CustomPriorityQueue {
private:
    std::vector<T> heap;
    Compare comp;

    void siftUp(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (comp(heap[parent], heap[index])) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void siftDown(size_t index) {
        size_t size = heap.size();
        while (true) {
            size_t largest = index;
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;

            if (left < size && comp(heap[largest], heap[left])) {
                largest = left;
            }
            if (right < size && comp(heap[largest], heap[right])) {
                largest = right;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    CustomPriorityQueue() = default;

    void push(const T& value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Priority Queue is empty!");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            siftDown(0);
        }
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Priority Queue is empty!");
        }
        return heap[0];
    }

    bool isEmpty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    void clear() {
        heap.clear();
    }

    const std::vector<T>& getElements() const {
        return heap;
    }
};

#endif // CUSTOM_PRIORITY_QUEUE_HPP
