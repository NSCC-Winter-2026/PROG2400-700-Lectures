#ifndef SORTING_H
#define SORTING_H

#include <span>

void bubble_sort(std::span<int> nums);
void selection_sort(std::span<int> nums);
void insertion_sort(std::span<int> nums);
void shell_sort(std::span<int> nums);
auto split(std::span<int> nums);
void quick_sort(std::span<int> nums);
void heapify(std::span<int> nums, size_t i);
void heap_sort(std::span<int> nums);

#endif
