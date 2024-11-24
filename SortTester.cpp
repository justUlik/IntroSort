#include "SortTester.h"
#include <chrono>
#include <numeric>
#include <stdexcept>

SortTester::SortTester(int num_tests) : num_tests_(num_tests) {}

long double SortTester::MeasureSortTime(const std::function<void(std::vector<int>&)>& sort_function, std::vector<int> array) const {
  std::vector<int64_t> times;
  for (int i = 0; i < num_tests_; ++i) {
    auto array_copy = array;

    auto start = std::chrono::high_resolution_clock::now();
    sort_function(array_copy);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    int64_t usec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    times.push_back(usec);
  }
  return std::accumulate(times.begin(), times.end(), 0LL) / static_cast<long double>(times.size());
}

void SortTester::TestSort(const std::function<void(std::vector<int>&)>& sort_function, const std::string& array_type) {
  std::vector<int> sizes;
  for (int test_size = 500; test_size <= 10000; test_size += 100) {
    sizes.push_back(test_size);
  }

  for (int size : sizes) {
    std::vector<int> test_array;

    if (array_type == "Random") {
      test_array = generator_.GetRandomArray(size);
    } else if (array_type == "Reversed") {
      test_array = generator_.GetReversedArray(size);
    } else if (array_type == "NearlySorted") {
      test_array = generator_.GetNearlySortedArray(size);
    } else {
      throw std::invalid_argument("Invalid array type. Choose from Random, Reversed, or NearlySorted.");
    }

    long double average_time = MeasureSortTime(sort_function, test_array);
    std::cout << average_time << "\n";
  }
}
