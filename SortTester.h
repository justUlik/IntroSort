#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "ArrayGenerator.h"

class SortTester {
private:
  ArrayGenerator generator_;
  int num_tests_;

  long double MeasureSortTime(const std::function<void(std::vector<int>&)>& sort_function, std::vector<int> array) const;

public:
  explicit SortTester(int num_tests = 10);

  void TestSort(const std::function<void(std::vector<int>&)>& sort_function, const std::string& array_type);
};

#endif // SORT_TESTER_H
