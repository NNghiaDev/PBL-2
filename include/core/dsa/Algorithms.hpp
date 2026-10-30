#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <functional>

namespace DSA {

/**
 * @brief QuickSort implementation for sorting dynamic collections.
 */
template <typename T, typename Compare>
int partition(std::vector<T>& arr, int low, int high, Compare comp) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (comp(arr[j], pivot)) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T, typename Compare>
void quickSortHelper(std::vector<T>& arr, int low, int high, Compare comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSortHelper(arr, low, pi - 1, comp);
        quickSortHelper(arr, pi + 1, high, comp);
    }
}

template <typename T, typename Compare = std::less<T>>
void quickSort(std::vector<T>& arr, Compare comp = Compare()) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, static_cast<int>(arr.size() - 1), comp);
    }
}

/**
 * @brief Binary Search implementation on sorted vector.
 * Returns index if found, or -1 if not found.
 */
template <typename T, typename Key, typename KeyExtractor>
int binarySearch(const std::vector<T>& arr, const Key& targetKey, KeyExtractor getKey) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        Key midKey = getKey(arr[mid]);

        if (midKey == targetKey) {
            return mid;
        }
        if (midKey < targetKey) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

} // namespace DSA

#endif // ALGORITHMS_HPP
