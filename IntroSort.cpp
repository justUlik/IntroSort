#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "SortTester.h"

std::mt19937 rng(std::random_device{}());

void InsertionSort(std::vector<int> &arr, int low, int high) {
  for (int i = low + 1; i <= high; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= low && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

int Partition(std::vector<int> &arr, int low, int high) {
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

void Heapify(std::vector<int> &arr, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    Heapify(arr, n, largest);
  }
}

void HeapSort(std::vector<int> &arr) {
  int n = arr.size();

  for (int i = n / 2 - 1; i >= 0; --i)
    Heapify(arr, n, i);

  for (int i = n - 1; i >= 0; --i) {
    std::swap(arr[0], arr[i]);
    Heapify(arr, i, 0);
  }
}

void IntrosortUtil(std::vector<int> &arr, int low, int high, int depthLimit) {
  int size = high - low + 1;

  if (size < 16) {
    InsertionSort(arr, low, high);
    return;
  }

  if (depthLimit == 0) {
    std::vector<int> subArray(arr.begin() + low, arr.begin() + high + 1);
    HeapSort(subArray);
    std::copy(subArray.begin(), subArray.end(), arr.begin() + low);
    return;
  }

  int pivotIndex = Partition(arr, low, high);
  IntrosortUtil(arr, low, pivotIndex - 1, depthLimit - 1);
  IntrosortUtil(arr, pivotIndex + 1, high, depthLimit - 1);
}

void Introsort(std::vector<int> &arr) {
  int depthLimit = 2 * std::log(arr.size());
  IntrosortUtil(arr, 0, arr.size() - 1, depthLimit);
}

int main() {
  SortTester tester(10);
  std::vector<int> arr;
  tester.TestSort(Introsort, "NearlySorted");

  return 0;
}
