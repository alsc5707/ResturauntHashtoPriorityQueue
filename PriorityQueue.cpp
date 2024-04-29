#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    //DONE
    //swap variables
    ReviewInfo *temp = a;
    a = b;
    b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    //DONE
    currentSize = 0;
    capacity = cap;
    heapArr = new ReviewInfo[cap];
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete[] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    //DONE
    return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    //DONE
    return ((2 * index) + 1);
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    //DONE
    return ((2 * index) + 2);
}

void PriorityQ::peek()
{
    //DONE
    ReviewInfo rw = heapArr[0];
    if(currentSize == 0){
        cout << "no record found" << endl;
    } else {
        cout << "------------------" << endl;
        cout << "Resturaunt: " << rw.restaurantName << endl;
        cout << "Customer: " << rw.customer << endl;
        cout << "Review: " << rw.review << endl;
        cout << "Time: " << rw.time << endl;
    }
}

void PriorityQ::heapify(int i)
{
    //DONE
    bool heap = true;
    
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < currentSize && heapArr[left].time > heapArr[largest].time){
        largest = left;
    }
    if (right < currentSize && heapArr[right].time > heapArr[largest].time){
        largest = right;
    }
    //recursive set the largest to first node
    if(largest != i){
        swap(heapArr[i], heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    //DONE
    //49 is max index (size 50 array)
    if(currentSize == 49){
        cout << "Maximum heap size reached. Cannot insert anymore. " << endl;
    } else {
        heapArr[currentSize] = restaurant;
        currentSize +=1;
        heapify(0);
        
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    //DONE
    for (int i =0; i < currentSize; i++){
        cout << "------------------" << endl;
        cout << "Customer: " << heapArr[i].customer << endl;
        cout << "Review: " << heapArr[i].review << endl;
        cout << "Time: " << heapArr[i].time << endl;
        
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    if (currentSize <= 0){
        cout << "Priority Queue is empty" << endl;
    } else if(currentSize == 1){
        currentSize--;
        return;
    }
    //front becomes back
    heapArr[0] = heapArr[currentSize-1];
    //disregard the last element
    currentSize --;
    //heapify
    heapify(0);
    
}
