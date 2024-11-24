#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>
#include <map>
#include <random>

class ArrayGenerator {
private:
  std::vector<int> full_random_array_;
  std::vector<int> full_reversed_array_;
  std::vector<int> full_nearly_sorted_array_;

  const int max_size_ = 10000;
  const int range_min_ = 0;
  const int range_max_ = 6000;

  std::map<int, std::vector<int>> cached_random_arrays_;
  std::map<int, std::vector<int>> cached_reversed_arrays_;
  std::map<int, std::vector<int>> cached_nearly_sorted_arrays_;

  std::mt19937 rng_;

  void InitializeRng();
  void ShuffleArray(std::vector<int> &array, int swaps);
  void CacheSubarrays();

public:
  ArrayGenerator();

  const std::vector<int>& GetRandomArray(int size);
  const std::vector<int>& GetReversedArray(int size);
  const std::vector<int>& GetNearlySortedArray(int size);
};

#endif // ARRAY_GENERATOR_H
