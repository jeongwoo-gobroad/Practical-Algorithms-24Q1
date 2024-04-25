// KNU CSE 2021114026 Jeongwoo Kim
// AX3.1. Binary Search Operation w/Recursive call
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binSearchOperate(int& call, int value, vector<int> target, int left, int right) {
    int mid;
    call++;
    if (left > right) {
        return 0;
    }

    mid = (left + right) / 2;

    if (target[mid] == value) {
        return mid;
    }
    else if (target[mid] >= value) {
        return binSearchOperate(call, value, target, left, mid - 1);
    }
    else {
        return binSearchOperate(call, value, target, mid + 1, right);
    }
}

int main(void) {
    int arrCount, targetCount;
    int input;
    int rtn_callCount = 0;
    vector<int> field;

    cin >> arrCount >> targetCount;

    field.resize(arrCount + 1);

    for (int i = 1; i <= arrCount; i++) {
        cin >> field[i];
    }

    sort(field.begin() + 1, field.end());

    for (int i = 0; i < targetCount; i++) {
        if (i == targetCount - 1) {
            cin >> input;
            input = binSearchOperate(rtn_callCount, input, field, 1, arrCount);
            //cout << rtn_callCount << " " << input;
            printf("%d %d", rtn_callCount, input);
        }
        else {
            cin >> input;
            input = binSearchOperate(rtn_callCount, input, field, 1, arrCount);
            //cout << rtn_callCount << " " << input << "\n";
            printf("%d %d\n", rtn_callCount, input);
        }
        rtn_callCount = 0;
    }

    return 0;
}