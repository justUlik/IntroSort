#include <iostream>
#include <vector>
#include <random>

#include "SortTester.h"

std::mt19937 rng(std::random_device{}());

int Partition(std::vector<int>& arr, int low, int high) {
  std::uniform_int_distribution<int> dist(low, high);
  int randomIndex = dist(rng);

  std::swap(arr[randomIndex], arr[high]);

  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (arr[j] <= pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

void QuickSort(std::vector<int>& arr, int low, int high) {
  if (low < high) {
    int pivotIndex = Partition(arr, low, high);
    QuickSort(arr, low, pivotIndex - 1);
    QuickSort(arr, pivotIndex + 1, high);
  }
}

void QuickSortWrapper(std::vector<int>& arr) {
  QuickSort(arr, 0, arr.size() - 1);
}

int main() {
  std::cout << "Quicksort" << std::endl;
  SortTester tester(10);
  std::vector<int> arr;
  tester.TestSort(QuickSortWrapper, "NearlySorted");
}