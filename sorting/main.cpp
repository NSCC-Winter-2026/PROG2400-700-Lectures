#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <span>

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

int main() {
    for (auto len = 10uz; len <= 100000uz; len *= 10uz) {
        std::cout << "len = " << len << std::endl;

        auto nums = new int[len];

        //fill_array({nums, len});
        //track_time("bubble sort", bubble_sort, {nums, len});

        fill_array({nums, len});
        track_time("selection sort", selection_sort, {nums, len});

        fill_array({nums, len});
        track_time("insertion sort", insertion_sort, {nums, len});

        if (is_sorted({nums, len})) {
            std::cout << "SUCCESS!" << std::endl;
        } else {
            std::cout << "FAILURE!" << std::endl;
        }

        delete [] nums;
    }

    return 0;
}
