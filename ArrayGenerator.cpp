#include "ArrayGenerator.h"
#include <algorithm>
#include <ctime>
#include <stdexcept>

void ArrayGenerator::InitializeRng() {
    rng_.seed(static_cast<unsigned>(std::time(nullptr)));
}

void ArrayGenerator::ShuffleArray(std::vector<int> &array, int swaps) {
    std::uniform_int_distribution<int> dist(0, static_cast<int>(array.size() - 1));
    for (int i = 0; i < swaps; ++i) {
        int idx1 = dist(rng_);
        int idx2 = dist(rng_);
        std::swap(array[idx1], array[idx2]);
    }
}

void ArrayGenerator::CacheSubarrays() {
    for (int size = 500; size <= max_size_; size += 100) {
        std::uniform_int_distribution<int> offset_dist(0, size);
        int offset = offset_dist(rng_);
        cached_random_arrays_[size] = std::vector<int>(full_random_array_.begin() + offset, full_random_array_.begin() + offset + size);
        cached_reversed_arrays_[size] = std::vector<int>(full_reversed_array_.begin() + offset, full_reversed_array_.begin() + offset + size);
        cached_nearly_sorted_arrays_[size] = std::vector<int>(full_nearly_sorted_array_.begin() + offset, full_nearly_sorted_array_.begin() + offset + size);
    }
}

ArrayGenerator::ArrayGenerator() {
    InitializeRng();

    std::uniform_int_distribution<int> dist(range_min_, range_max_);
    for (int i = 0; i < max_size_; ++i) {
        full_random_array_.push_back(dist(rng_));
    }

    full_reversed_array_ = full_random_array_;
    std::sort(full_reversed_array_.rbegin(), full_reversed_array_.rend());

    full_nearly_sorted_array_ = full_reversed_array_;
    std::reverse(full_nearly_sorted_array_.begin(), full_nearly_sorted_array_.end());
    ShuffleArray(full_nearly_sorted_array_, max_size_ / 10);

    CacheSubarrays();
}

const std::vector<int>& ArrayGenerator::GetRandomArray(int size) {
    if (cached_random_arrays_.find(size) == cached_random_arrays_.end()) {
        throw std::invalid_argument("Invalid size for random array");
    }
    return cached_random_arrays_[size];
}

const std::vector<int>& ArrayGenerator::GetReversedArray(int size) {
    if (cached_reversed_arrays_.find(size) == cached_reversed_arrays_.end()) {
        throw std::invalid_argument("Invalid size for reversed array");
    }
    return cached_reversed_arrays_[size];
}

const std::vector<int>& ArrayGenerator::GetNearlySortedArray(int size) {
    if (cached_nearly_sorted_arrays_.find(size) == cached_nearly_sorted_arrays_.end()) {
        throw std::invalid_argument("Invalid size for nearly sorted array");
    }
    return cached_nearly_sorted_arrays_[size];
}
