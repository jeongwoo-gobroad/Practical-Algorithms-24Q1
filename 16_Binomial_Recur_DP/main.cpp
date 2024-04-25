// KNU CSE 2021114026 Jeongwoo Kim
// AX05. P04_v2: Binomial Combination Constant #2
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef void debug_feature;

int binomial_bottom_up(int n, int k, vector<int>& c) {
    c[0] = 1;

    /*
        i: value of n of a row.
        i + 1: max index of elements in a n row. 
    */
    for (int i = 1; i <= n; i++) {
        c.push_back(1);

        for (int j = 1; j <= i / 2; j++) {
            if ((!(i % 2)) && j == i / 2) {
                c[j] = 2 * c[j] % 10007; // if n is even, then middle value can be achieved by simply doubling.
                break;
            }
            c[j] = (c[j] + c[(i - 1) - (j - 1)]) % 10007; // i - 1 is important
        }

        for (int j = i; j > i / 2; j--) {
            c[j] = c[i - j];
        }
    }

    return c[k];
}

int main(void) {
    vector<int> target;
    int n, k;

    cin >> n >> k;

    target.resize(1);

    cout << binomial_bottom_up(n, k, target);

    return 0;
}