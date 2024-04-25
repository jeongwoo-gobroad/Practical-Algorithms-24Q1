// KNU CSE 2021114026 Jeongwoo Kim
// AX3.3. Merge Sort w/ S(n) = n operation
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Variables to Measure Additional Memory Usage */
static int storage = 0; // for S(n) = 2n func.
static int alter_storage = 0; // for S(n) = n func.

/* Variable to Count How Many Basic Operations have done */
static int comp_count = 0;

/* parameters stand for: sttPos of chunk A, endPos of chunk B, and so on. */
void slimMergeOps(int sA, int eA, int sB, int eB, vector<int>& target) {
    int temp_sA = sA; int temp_sB = sB; 
    vector<int> tempCpyTgt(eB - sA + 2);
    int tempCur = 1;
    alter_storage += (eB - sA + 1);

    cout << "added " << eB - sA + 1 << endl;

    while (temp_sA <= eA && temp_sB <= eB) {
        /* comp count */
        comp_count++;

        if (target[temp_sA] < target[temp_sB]) {
            tempCpyTgt[tempCur++] = target[temp_sA++];
        }
        else {
            tempCpyTgt[tempCur++] = target[temp_sB++];
        }
    }

    if (temp_sA <= eA) {
        while (temp_sA <= eA) {
            tempCpyTgt[tempCur++] = target[temp_sA++];
        }
    }
    else {
        while (temp_sB <= eB) {
            tempCpyTgt[tempCur++] = target[temp_sB++];
        }
    }

    /* copying to original array */
    for (; eB >= sA; eB--) {
        target[eB] = tempCpyTgt[--tempCur];
    }

    return;
}

void slimMerge(int sttCur, int endCur, vector<int>& target) {
    if (sttCur >= endCur) {
        cout << "end of recursive call" << endl;
        return;
    }

    int mid = (sttCur + endCur) / 2;
    slimMerge(sttCur, mid, target);
    slimMerge(mid + 1, endCur, target);
    slimMergeOps(sttCur, mid, mid + 1, endCur, target);

    return;
}

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
    if (eleCnt == 1) return;

    /* 1 2 3 4 5 6 7 */
    int size_chk_left = eleCnt / 2; // 1 2 3 => 3
    int size_chk_right = eleCnt - size_chk_left; // 4 5 6 7 => 4

    /* copying memory */
    vector<int> chk_left(size_chk_left + 1);
    vector<int> chk_right(size_chk_right + 1);
    for (int i = 1; i <= size_chk_left; i++) {
        chk_left[i] = target[i];
    }
    for (int i = 1; i <= size_chk_right; i++) {
        chk_right[i] = target[i + size_chk_left]; // 1 + 3 = 4
    }
    storage += (size_chk_left + size_chk_right);

    /* Divide */
    mergeSort(size_chk_left, chk_left);
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

    slimMerge(1, term, input);

    cout << "Result of S(n) = n function" << endl;

    for (int i = 1; i < term; i++) {
        cout << input[i] << " ";
    }
    cout << input[term] << "\n";

    // cout << alter_storage << " " << comp_count << endl;
    cout << "Additional Memory Allocated: " << alter_storage;

    return 0;
}