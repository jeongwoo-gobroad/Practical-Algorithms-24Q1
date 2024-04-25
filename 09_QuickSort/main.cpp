// KNU CSE 2021114026 Jeongwoo Kim
// AX3.4. Quick Sort with specialized pivot based swapping
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int swapCounter = 0;

int adjustPivot(int stt, int end, vector<int>& target) {
    int pivot = stt; int seekCur = stt + 1; int lastSwapCur = pivot;
    /* How It Works */
    /* 
    *   1.  Remind that all we have to do is to replace any smaller(or larger)
            integers than pivot to designated index.
        2.  That means, "in-chunk(one of the two parts that is created by pivot)
            integer order does not matter"
        3.  So, seekCur seeks value. lastSwapCur points at the very place swap has been done.
        4.  At the moment in which seekCur has traveled all the index, 
            lastSwapCur remembers last index where swap has been done.
        5.  Pivot <-> lastSwapCur SWAP; Then all elements should be in the designated index!
    */
    for (; seekCur <= end; seekCur++) {
        if (target[pivot] > target[seekCur]) {
            lastSwapCur += 1;
            swap(target[lastSwapCur], target[seekCur]); /* SWAP */ swapCounter++;
        }
    }
    
    swap(target[lastSwapCur], target[pivot]); /* SWAP */ swapCounter++;
    pivot = lastSwapCur;

    return pivot;
}

void quickSort(int stt, int end, vector<int>& target) {
    if (stt >= end) return;

    int pivotCur = adjustPivot(stt, end, target);
    quickSort(stt, pivotCur - 1, target);
    quickSort(pivotCur + 1, end, target);

    return;
}

int main(void) {
    int term;
    vector<int> arr;

    cin >> term;

    arr.resize(term + 1, 0);

    for (int i = 1; i <= term; i++) {
        cin >> arr[i];
    }

    quickSort(1, term, arr);

    for (int i = 1; i < term; i++) {
        cout << arr[i] << " ";
    }
    cout << arr[term] << "\n";
    cout << swapCounter;

    return 0;
}