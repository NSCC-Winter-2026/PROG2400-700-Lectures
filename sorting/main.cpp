#include <chrono>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <span>
#include "sorting.h"

using clk = std::chrono::high_resolution_clock;

void track_time(auto desc, void (*sort)(std::span<int>), std::span<int> nums) {
    // get the current time
    auto t = clk::now();
    // sort numbers
    sort(nums);
    // get the difference between current and previous time
    const std::chrono::duration<double> span = clk::now() - t;
    // output the time difference
    std::cout << std::setw(15) << desc << ": ";
    std::cout << "time " << span.count() << " s" << std::endl;
}

void fill_array(std::span<int> nums) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<size_t> dist(1, nums.size());
    std::generate(nums.begin(), nums.end(), [&]() {
        return dist(rng);
    });
}

bool is_sorted(std::span<int> nums) {
    for (auto i = 0; i < nums.size() - 1; i++) {
        if (nums[i] > nums[i + 1]) return false;
    }
    return true;
}

void dump_array(const std::span<int> nums) {
    for (const auto num : nums) {
        std::cout << std::setw(3) << num;
    }
    std::cout << std::endl;
}

void test_algorithms() {
    for (auto len = 10uz; len <= 10000000uz; len *= 10uz) {
        std::cout << "len = " << len << std::endl;

        auto nums = new int[len];

        // fill_array({nums, len});
        // track_time("bubble sort", bubble_sort, {nums, len});
        //
        // fill_array({nums, len});
        // track_time("selection sort", selection_sort, {nums, len});
        //
        // fill_array({nums, len});
        // track_time("insertion sort", insertion_sort, {nums, len});

        fill_array({nums, len});
        track_time("shell sort", shell_sort, {nums, len});

        fill_array({nums, len});
        track_time("quick sort", quick_sort, {nums, len});

        fill_array({nums, len});
        track_time("heap sort", heap_sort, {nums, len});

        if (is_sorted({nums, len})) {
            std::cout << "SUCCESS!" << std::endl;
        } else {
            std::cout << "FAILURE!" << std::endl;
        }

        delete [] nums;
    }
}

std::ostream& operator<<(std::ostream& os, const std::span<int> nums) {
    if (nums.empty()) return os;
    auto i = 0;
    for (; i < nums.size() - 1; i++) {
        os << nums[i] << ", ";
    }
    os << nums[i];
    return os;
}

std::ostream& operator<<(std::ostream& os, std::queue<int> queue) {
    if (queue.empty()) return os;
    while (queue.size() > 1) {
        const auto num = queue.front();
        queue.pop();
        os << num << ", ";
    }
    os << queue.front();
    return os;
}

void split(std::queue<int>& in, std::queue<int>& out1, std::queue<int>& out2) {
    auto num_subfiles = 0;

    // keep splitting while there are records to read
    auto prev = -1;
    while (!in.empty()) {
        // read a record
        auto curr = in.front();
        in.pop();

        // am I still in the same sublist?
        if (curr < prev) num_subfiles++;

        // write out in an odds/evens fashion
        if (num_subfiles % 2 == 0) {
            out1.push(curr);
        } else {
            out2.push(curr);
        }

        prev = curr;
    }
}

bool elements_in_sublist(std::queue<int> first, std::queue<int> second, const int last) {
    return !first.empty() && (first.front() >= last);
}

bool elements_in_column(std::queue<int> first, std::queue<int> second, const int last) {
    return !first.empty() && (first.front() >= last) &&
            (second.empty() || (second.front() < last) || (first.front() < second.front()));
}

bool elements_not_in_current_list(std::queue<int> first, std::queue<int> second, const int last) {
    return first.empty() || !second.empty() &&
    ((first.front() < last) ||
        ((first.front() > last) && (second.front() < first.front())));
}

auto merge(std::queue<int>& out, std::queue<int>& in1, std::queue<int>& in2) {
    auto num_subfiles = 0;

    // who starts the process
    auto& first = in2.empty() || (in1.front() < in2.front()) ? in1 : in2;
    auto& second = first == in1 ? in2 : in1;

    // keep merging while there are records in either file
    while (!in1.empty() || !in2.empty()) {
        auto last = -1;

        // keep reading records that are in order
        while (elements_in_sublist(first, second, last)) {
            // take records from file while they are in order
            do {
                last = first.front();
                first.pop();
                out.push(last);
            } while (elements_in_column(first, second, last));

            // done taking elements, now switch to other file
            if (elements_not_in_current_list(first, second, last)) {
                std::swap(first, second);
            }
        }

        // move to a new sublist
        num_subfiles++;
    }

    return num_subfiles;
}

void merge_sort(std::span<int> nums) {
    // copy array to queue (think of queue as a file)
    std::queue<int> merged;
    for (auto num : nums) {
        merged.push(num);
    }

    // sorting goes here
    std::queue<int> split1, split2;
    auto subfiles = 0;
    do {
        split(merged, split1, split2);

        std::cout << "Split" << std::endl;
        std::cout << split1 << std::endl;
        std::cout << split2 << std::endl;

        subfiles = merge(merged, split1, split2);

        std::cout << "Merge" << std::endl;
        std::cout << merged << std::endl;
    } while (subfiles != 1);

    // copy queue (a.k.a file) back to array
    auto i = 0;
    while (!merged.empty()) {
        nums[i++] = merged.front();
        merged.pop();
    }
}

int main() {
    auto array = std::to_array({3, 6, 8, 10, 5, 9, 4, 1, 2, 7});

    std::cout << "Unsorted" << std::endl;
    std::cout << array << std::endl;

    merge_sort(array);

    std::cout << "Sorted" << std::endl;
    std::cout << array << std::endl;

    return 0;
}
