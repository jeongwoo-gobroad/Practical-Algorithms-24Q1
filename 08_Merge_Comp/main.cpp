// KNU CSE 2021114026 Jeongwoo Kim
// AX3.3.0. Merge Sort w/ Comparison between [S(n) = 2n, S(n) = n]
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Variables to Measure Additional Memory Usage */
/* Note that we will count the worst-case scenario */
static int storage = 0; // for S(n) = 2n func.
static bool deepFlag = 0; // This will used for depth search
static int alter_storage = 0; // for S(n) = n func.

/* parameters stand for: sttPos of chunk A, endPos of chunk B, and so on. */
void slimMergeOps(int sA, int eA, int sB, int eB, vector<int>& target) {
    int temp_sA = sA; int temp_sB = sB; 
    vector<int> tempCpyTgt(eB - sA + 2);
    int tempCur = 1;

    /* Worst-Case Additional Memory Usage */
    if (alter_storage < (eB - sA + 1)) {
        alter_storage = (eB - sA + 1);
        cout << "Worst-Case Additional Memory Usage Updated: " << alter_storage << endl;

    }
    /* ---------------------------------- */

    while (temp_sA <= eA && temp_sB <= eB) {
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
    if (eleCnt == 1) {
        /* To check it has reached the end of recursive call depth */
        deepFlag = 1;
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
    for (int i = 1; i <= size_chk_right; i++) {
        chk_right[i] = target[i + size_chk_left]; // 1 + 3 = 4
    }

    if (!deepFlag) {
        storage += (size_chk_left + size_chk_right);
        cout << "Additional Memory " << (size_chk_left + size_chk_right) << " added\n";
    }

    /* Divide */
    mergeSort(size_chk_left, chk_left);
    mergeSort(size_chk_right, chk_right);
    /* Conquer */
    mergeOps(size_chk_left, size_chk_right, chk_left, chk_right, target);

    return;
}

int main(void) {
    vector<int> input;
    vector<int> input2;
    int term;

    cin >> term;
    input.resize(term + 1, 0);
    for (int i = 1; i <= term; i++) {
        cin >> input[i];
    }
    input2 = input;

    cout << "Fat Merge [S(n) = 2n]" << endl;
    mergeSort(term, input);
    for (int i = 1; i <= term; i++) {
        cout << input[i] << " ";
    } cout << endl;
    cout << "---------------Worst Case Additional Memory Total: " << storage << endl;

    cout << endl << endl << "Slim Merge [S(n) = n]" << endl;
    slimMerge(1, term, input2);
    for (int i = 1; i <= term; i++) {
        cout << input2[i] << " ";
    } cout << endl;
    cout << "---------------Worst Case Additional Memory Total: " << alter_storage << endl;

    return 0;
}