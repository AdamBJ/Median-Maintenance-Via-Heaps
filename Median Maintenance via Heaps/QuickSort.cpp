#include <vector>
#include <fstream>
#include <iostream>

using std::vector;

#define SELECT_FIRST_ELEM 1
#define SELECT_LAST_ELEM 2
#define SELECT_MEDIAN_ELEM 3

int MODE = SELECT_MEDIAN_ELEM;


int FindMedian(int a, int b, int c){
	if (a < b && b < c)return 1;
	else if (a < b && b > c) {
		if (a < c) return 2;
		else return 0;
	}
	else if (a > b && b > c) return 1;
	else if (a > b && b < c){
		if (a > c) return 2;
		else return 0;
	}
}
int Partition(vector<int>& input, int pivotIndex, int first, int last){
	/*Swap partition elem with the first element. Compare each of the remaining n-1 elements with the partition element.
	Put in < partition and > partition buckets according to their value.*/

	int temp = input[first];
	input[first] = input[pivotIndex];
	input[pivotIndex] = temp;

	/*i tracks the boundary of the <pivot element bucket (ith item is first >pivot item), j the boundary between the bucketed items and the unsorted items.*/
	int i, j, pivot;
	i = j = first + 1;
	pivot = input[first];

	for (j; j <= last; j++){
		if (input[j] < pivot){
			//swap
			temp = input[j];
			input[j] = input[i];
			input[i] = temp;
			i++;
		}
	}
	//insert pivot in between the buckets
	temp = input[first];
	input[first] = input[i - 1];
	input[i - 1] = temp;
	return i - 1;

}
int ChoosePivot(vector<int>& input, int first, int last){
	//ChoosePartition selects the element in the unpartitioned array to serve as the partition according to the partition selection strategy and returns its index.
	//It does *not* return the final position of the partition element in the partitioned array.
	int pIndex;

	if (MODE == SELECT_FIRST_ELEM) pIndex = first;
	else if (MODE == SELECT_LAST_ELEM) pIndex = last;
	else {//SELECT_MEDIAN_ELEM
		int midVal = (last + first) / 2;
		int rslt = FindMedian(input[first], input[midVal], input[last]);
		if (rslt == 0) pIndex = first;
		else if (rslt == 1) pIndex = midVal;
		else pIndex = last;
	}
	return pIndex;
}

void QuickSort(vector<int>& input, int first, int last) {
	//base case: return array when partion is of length 1 or less
	if (last - first < 1) return;

	int pIndex = Partition(input, ChoosePivot(input, first, last), first, last);//pIndex is the index of the partition element in the partitioned array.

	int p1 = (pIndex - first) - 1;
	int p2 = (last - pIndex) - 1;
	
	std::size_t const half_size = pIndex;
	QuickSort(input, first, pIndex - 1);
	QuickSort(input, pIndex + 1, last);

}

