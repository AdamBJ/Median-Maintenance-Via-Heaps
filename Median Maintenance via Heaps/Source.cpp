#include "Heap.h"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;
const string FILE_NAME("order.txt");

int main(){

	//Creates an instance of ofstream, and opens example.txt
	ofstream a_file("order.txt");
	// Outputs to example.txt through a_file
	for (int i = 1; i <= 10000; i++){
		a_file << i << endl;
	}
	// Close the file stream explicitly
	a_file.close();

	//create two heaps, a min heap and a max heap. The "maxHeap" is just a normal heap except that every value is multiplied by -1 before it is inserted.
	//the min heap stores the largest half of the elements, which means the roots is the smallest of the largest elements. The max heap stores the
	//smallest half of the elements, which means the root is the largest of the smallest elements.
	Heap minHeap(5000), maxHeap(5000);

	//initialize our integer "stream" (in fact it is just a file we read in entry by entry)
	ifstream integersToBeRead(FILE_NAME);

	if (integersToBeRead.is_open()){
		cout << "File opened successfully. Reading..." << endl;

		int i, sumOfMedians = 0, intsReadIn = 0, testSum = 0;
		vector<int> testSeq, testMedians, Medians;
		testSeq.reserve(10000);
		//initialize the heap. there needs to be one element in minHeap so that minHeap.Peek_Min() has something to return when we call it for the first time below
		integersToBeRead >> i;
		intsReadIn++;
		minHeap.Insert(HeapEntry(intsReadIn, i));
		sumOfMedians += i;
	
		//
		testMedians.push_back(i);
		Medians.push_back(i);
		testSum += i;
		testSeq.push_back(i);
		//
		
		while (integersToBeRead >> i){
			//if the integer we just read in is less than or equal to the minHeap's root ( aka <= smallest of the largest elements), insert it in maxHeap.
			//If it isn't, it belongs in the maxHeap (root of maxHeap is the largest of the smallest elements, i is one of the smallest elements).
			intsReadIn++;
			int sss = testMedians.size();
			int qqq = minHeap.Size();

			//
			testSeq.push_back(i);
			//

			if (testSeq.size() % 2 != 0) {
				testSum += testSeq[testSeq.size() / 2];
				testMedians.push_back(testSeq[testSeq.size() / 2]);
			}
			else {
				testSum += testSeq[testSeq.size() / 2 - 1]; 
				testMedians.push_back(testSeq[testSeq.size() / 2 - 1]);

			}

			if (i < minHeap.Peek_Min()){
				maxHeap.Insert(HeapEntry(intsReadIn, i*-1));

				//rebalance heaps if neccesary so the ints we read in are equally distributed amongst the two heaps
				if (maxHeap.Get_Rear() > minHeap.Get_Rear() + 1){
					//int y = maxHeap.Peek_Min();
					HeapEntry toBeShifted = maxHeap.Delete_Min();
					toBeShifted.key *= -1;
					minHeap.Insert(toBeShifted);
				}
			}
			else { //insert into minHeap
				minHeap.Insert(HeapEntry(intsReadIn, i));

				//rebalance heaps if neccesary so the ints we read in are equally distributed amongst the two heaps
				if (minHeap.Get_Rear() > maxHeap.Get_Rear() + 1){
					HeapEntry toBeShifted = minHeap.Delete_Min();
					toBeShifted.key *= -1;
					maxHeap.Insert(toBeShifted);
				}
			}

			//calculate median of sequence read in so far
			if (minHeap.Get_Rear() > maxHeap.Get_Rear()) {
				//we've read in an odd number of integers and there are more integers in minHeap. Take median from minHeap.
				sumOfMedians += minHeap.Peek_Min();

				//
				Medians.push_back(minHeap.Peek_Min());
				//
			}
			else if (maxHeap.Get_Rear() > minHeap.Get_Rear()){
				//odd number and there are more integers in maxHeap...
				sumOfMedians += maxHeap.Peek_Min() * -1;
				
				//
				Medians.push_back(maxHeap.Peek_Min()*-1);
				//
			}
			else{
				//if the sizes are the same then it doesn't matter which heap we take the median from. Take it from the lower side of the "median line".
				sumOfMedians += maxHeap.Peek_Min() * -1;
				
				//
				Medians.push_back(maxHeap.Peek_Min()*-1);
				//
			}
		}
		cout << "Processesing finished." <<endl<< "Result is " << sumOfMedians % 10000 << ". " << testSum % 10000;
	}
	else{
		cout << "Unable to open file.";
		return 0;
	}
	return 0;
}