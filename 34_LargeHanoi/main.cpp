// KNU CSE 2021114026 Jeongwoo Kim
// AX2.7, Advanced Hanoi
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

void largeHanoi(ll plate, ll cnt, char from, char via, char to) {
    /**
     * Instruction:
     *      1. hanoi requires 2^n - 1 operation to move completely.
     *      2. Counting very large number of plates cannot be done in modern computers;
     *      3. So, we perform Binary search; keep dividing trial (2^n - 1) by 2.
    */
    cnt--;
    if (cnt == powl((long double)2, (long double) plate)) {
        cout << from << "->" << to << endl;
        return;
    }
    else {
        if (cnt > powl((long double)2, (long double) plate)) {
            largeHanoi(plate, cnt, from, via, to);
            largeHanoi(plate, cnt - powl((long double)2, (long double) plate), from, via, to);
        }
        else {
            largeHanoi(plate - 1, cnt, from, to, via);
            largeHanoi(1, cnt, from, via, to);
            largeHanoi(plate - 1, cnt, via, from, to);
        }
        return;
    }
}

int main(void) {
    ll plate, cnt;

    cin >> plate >> cnt;

    largeHanoi(plate, cnt, 'A', 'B', 'C');

    return 0;
}