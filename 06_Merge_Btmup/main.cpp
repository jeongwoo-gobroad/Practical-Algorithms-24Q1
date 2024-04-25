// KNU CSE 2021114026 Jeongwoo Kim
// AX3.2. Merge Sort w/ S(n) = 2n operation
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Variables to Measure Additional Memory Usage */
static int storage = 0; // for S(n) = 2n func.
static int alter_storage = 0; // for S(n) = n func.

/* Variable to Count How Many Basic Operations have done */
static int comp_count = 0;

void mergeOps(int size_chk1, int size_chk2, vector<int> chk1, vector<int> chk2, vector<int>& target) {
    int leftCur = 1; int rightCur = 1; int targetCur = 1;

    while (leftCur <= size_chk1 && rightCur <= size_chk2) {
        if (chk1[leftCur] < chk2[rightCur]) {
            target[targetCur++] = chk1[leftCur++];
        }
        else {
            target[targetCur++] = chk2[rightCur++];
        }
    }
    
    if (leftCur <= size_chk1) {
        while (leftCur <= size_chk1) {
            target[targetCur++] = chk1[leftCur++];
        }
    }
    else {
        while (rightCur <= size_chk2) {
            target[targetCur++] = chk2[rightCur++];
        }
    }

    return;
}

void mergeSort(int eleCnt, vector<int>& target) {
    if (eleCnt == 1) {
        cout << "end of recursive call" << endl;
        return;
    }
    /* 1 2 3 4 5 6 7 */
    int size_chk_left = eleCnt / 2; // 1 2 3 => 3
    int size_chk_right = eleCnt - size_chk_left; // 4 5 6 7 => 4

    /* copying memory */
    vector<int> chk_left(size_chk_left + 1);
    vector<int> chk_right(size_chk_right + 1);
    for (int i = 1; i <= size_chk_left; i++) {
        chk_left[i] = target[i];
    }
    
    storage += (size_chk_left + size_chk_right);
    cout << "added " << size_chk_left + size_chk_right << endl;

    /* Divide */
    mergeSort(size_chk_left, chk_left);
    for (int i = 1; i <= size_chk_right; i++) {
        chk_right[i] = target[i + size_chk_left]; // 1 + 3 = 4
    }
    mergeSort(size_chk_right, chk_right);
    /* Conquer */
    mergeOps(size_chk_left, size_chk_right, chk_left, chk_right, target);

    return;
}

int main(void) {
    vector<int> input;
    int term;

    cin >> term;
    input.resize(term + 1, 0);
    for (int i = 1; i <= term; i++) {
        cin >> input[i];
    }

    mergeSort(term, input);

    cout << "Result of S(n) = 2n function" << endl;

    for (int i = 1; i < term; i++) {
        cout << input[i] << " ";
    }
    cout << input[term] << "\n";

    cout << "Additional Memory Allocated: " << storage;

    return 0;
}