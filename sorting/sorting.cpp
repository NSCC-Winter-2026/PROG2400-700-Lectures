#include "sorting.h"

void bubble_sort(std::span<int> nums) {
    for (auto i = 0; i < nums.size() - 1; i++) {
        for (auto j = 0; j < nums.size() - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
            }
        }
    }
}

void selection_sort(std::span<int> nums) {
    for (auto i = 0; i < nums.size() - 1; i++) {
        // find the smallest number
        auto lowest = i;
        for (auto j = i + 1; j < nums.size(); j++) {
            if (nums[j] < nums[lowest]) {
                lowest = j;
            }
        }
        // put the lowest in the correct position
        if (nums[lowest] < nums[i]) {
            std::swap(nums[lowest], nums[i]);
        }
    }
}

void insertion_sort(std::span<int> nums) {
    for (auto i = 1; i < nums.size(); i++) {
        // pull out a card to examine
        const auto temp = nums[i];
        // shuffle any elements needed out of the way for the insert
        auto j = i;
        for (; j > 0 && temp < nums[j - 1]; --j) {
            nums[j] = nums[j - 1];
        }
        // perform the insert
        nums[j] = temp;
    }
}

void shell_sort(std::span<int> nums) {
    // create gaps, starting with half the array size
    for (auto gap = nums.size() / 2; gap > 0; gap /= 2) {
        // select smaller (sub-array) array to sort
        for (auto start = 0; start < gap; start++) {
            // apply insertion sort on the sub-array
            for (auto i = start + gap; i < nums.size(); i += gap) {
                // pull out a card to examine
                const auto temp = nums[i];
                // shuffle any elements needed out of the way for the insert
                auto j = i;
                for (; j >= gap && temp < nums[j - gap]; j -= gap) {
                    nums[j] = nums[j - gap];
                }
                // perform the insert
                nums[j] = temp;
            }
        }
    }
}

auto split(std::span<int> nums) {
    // pick the pivot point
    auto pivot = nums[0];

    // start searching for numbers less than/greater than the pivot
    auto left = 0;
    auto right = nums.size() - 1;

    while (left < right) {
        // search for an element less than the pivot
        while (right > 0 && pivot < nums[right]) right--;
        // search for an element greater than the pivot
        while (left < right && pivot >= nums[left]) left++;

        // if two were found out of place, swap them
        if (left < right && nums[left] != nums[right]) {
            std::swap(nums[left], nums[right]);
        }
    }

    // now move the pivot between the less thans and the greater thans
    nums[0] = nums[right];
    nums[right] = pivot;

    return right;
}

void quick_sort(std::span<int> nums) {
    // the array is sorted when it only has zero or one elements in it
    if (nums.size() <= 1) return;

    // pick a pivot point and split into less than/greater thans
    auto pivot = split(nums);

    // sort the less thans
    quick_sort(nums.subspan(0, pivot));

    // sort the greater thans
    quick_sort(nums.subspan(pivot + 1, nums.size() - pivot - 1));
}

void heapify(std::span<int> nums, size_t i) {
    // assume the parent is the largest number
    auto largest = i;
    auto left = i * 2 + 1;
    auto right = i * 2 + 2;

    // is the left child larger than the parent?
    if (left < nums.size() && nums[left] > nums[largest]) {
        largest = left;
    }
    // is the right child larger than the parent or the left child
    if (right < nums.size() && nums[right] > nums[largest]) {
        largest = right;
    }

    // if the largest is not the parent, swap
    if (largest != i) {
        std::swap(nums[largest], nums[i]);
        heapify(nums, largest);
    }
}

void heap_sort(std::span<int> nums) {
    // make initial max-heap structure
    for (auto i = nums.size() / 2; i > 0; i--) {
        // swap larger children with parent
        heapify(nums, i - 1);
    }

    // one by one extract the elements in order (swap, shrink, sink)
    for (auto i = nums.size() - 1; i > 0; i--) {
        std::swap(nums[0], nums[i]);
        heapify(nums.subspan(0, i), 0);
    }
}
