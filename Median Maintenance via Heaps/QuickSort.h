#ifndef QUICKSORT_H
#define QUICKSORT_H
	
#include <vector>
#include <fstream>
#include <iostream>

using std::vector;

void QuickSort(vector<int>& input, int first, int last);
int ChoosePivot(vector<int>& input, int first, int last);
int Partition(vector<int>& input, int partitionIndex, int first, int last);
int FindMedian(int a, int b, int c);

#endif