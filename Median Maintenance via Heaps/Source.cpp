#include "Heap.h"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;
const string FILE_NAME("Median.txt");

int main(){
	//create two heaps, a min heap and a max heap. The "maxHeap" is just a normal heap except that every entry is multiplied by -1 before it is inserted.
	//the min heap stores the largest half of the elements, which means the roots is the smallest of the largest elements. The max heap stores the
	//smallest half of the elements, which means the root is the largest of the smallest elements.
	
	Heap minHeap(5000), maxHeap(5000);//10000 integers to read in

	//initialize our integer "stream" (in fact it is just a file we read in entry by entry)
	ifstream integersToBeRead(FILE_NAME);

	if (integersToBeRead.is_open()){
		cout << "File opened successfully. Reading..." << endl;

		int i, sumOfMedians = 0, intsReadIn = 0;
		//initialize the heap. there needs to be one element in minHeap so that minHeap.Peek_Min() has something to return when we call it for the first time below
		integersToBeRead >> i;
		intsReadIn++;
		minHeap.Insert(HeapEntry(intsReadIn, i));
		sumOfMedians += i;
		
		while (integersToBeRead >> i){
			intsReadIn++;						

			//if the integer we just read in is less than the minHeap's root ( aka < smallest of the largest elements), insert it in maxHeap.
			if (i < minHeap.Peek_Min()){
				maxHeap.Insert(HeapEntry(intsReadIn, i*-1));

				//rebalance heaps if neccesary so the ints we have read in are equally distributed amongst the two heaps
				if (maxHeap.Get_Rear() > minHeap.Get_Rear() + 1){
					HeapEntry toBeShifted = maxHeap.Delete_Min();
					toBeShifted.key *= -1;
					minHeap.Insert(toBeShifted);
				}
			}
			else { //insert into minHeap
				minHeap.Insert(HeapEntry(intsReadIn, i));

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
			}
			else if (maxHeap.Get_Rear() > minHeap.Get_Rear()){
				//odd number and there are more integers in maxHeap...
				sumOfMedians += maxHeap.Peek_Min() * -1;			
			}
			else{
				//if the sizes are the same then it doesn't matter which heap we take the median from. Take it from the lower side of the "median line".
				sumOfMedians += maxHeap.Peek_Min() * -1;
			}
		}
		cout << "Processesing finished." << endl << "Result is " << sumOfMedians % 10000 << ".";
	}
	else{
		cout << "Unable to open file.";
		return 0;
	}
	return 0;
}