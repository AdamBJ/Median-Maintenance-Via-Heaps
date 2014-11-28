The problem is to maintain the median of a sequence of values we read in. The median can (and in all likelihood will) change as we read 
in more values from the sequence. Our job is to find the median for a given sequence, add it to a sum, add another value to our sequence,
find the median... until all values have been read in.

 From the question statement:

"The goal of this problem is to implement the "Median Maintenance" algorithm (covered in the Week 5 lecture on heap applications). 
The text file contains a list of the integers from 1 to 10000 in unsorted order; you should treat this as a stream of numbers, arriving one by one.
Letting xi denote the ith number of the file, the kth median mk is defined as the median of the numbers x1,…,xk.
 (So, if k is odd, then mk is ((k+1)/2)th smallest number among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)

In the box below you should type the sum of these 10000 medians, modulo 10000 (i.e., only the last 4 digits). 
That is, you should compute (m1+m2+m3+⋯+m10000)mod10000."

The median is maintained using two heaps, a min heap (root is smallest element in the heap) and a max heap (root is largest element element in the heap).
The smallest n/2 elements of the sequence are stored in the max heap while the largest n/2 elements are stored in the min heap (minHeap is "smallest of the largest elements",
maxHeap is "largest of the smallest elements").

By maintaining the above invariant, we can be assured the the roots of the
tree are adjacent to each other in terms of ordering (i.e root of min is ith number, root of max is ith+1). It is possible that the "even split"
invariant will be upset (consider min root =2 max root = 4 and we read in 1,1,1). To maintain the invariant, after each insertion we check that the sizes
of the two heaps are within +-1 of each other. If they aren't, pop the root of whichever tree has more elems and insert it into the tree with less.

When we want to find the median of the sequence that has been read in so far, all we have to do is look at the roots. If the number of integers we have
read in is odd we simply take the root of the larger heap (the "extra element" is our median). If num ints we have read in is even
we can take the root of either heap as the median (consider 1 2 3 4: median is 2 or 3).