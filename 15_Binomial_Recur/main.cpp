// KNU CSE 2021114026 Jeongwoo Kim
// AX05. P04_v1: Binomial Combination Constant
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef void debug_feature;
typedef vector<vector<int>> matrix;

static int cnter = 0;

int binomial(int n, int k, matrix& c) {
    cnter++;

    if (k == 0 || n == k) {
        c[n][k] = 1;
    }
    else if (c[n][k] == -1) {
        c[n][k] = (binomial(n - 1, k, c) + binomial(n - 1, k - 1, c)) % 10007;
    }
    
    return c[n][k];
}

int main(void) {
    matrix target;
    int n, k;

    cin >> n >> k;

    target.resize(n + 1, vector<int>(n + 1, -1));

    cout << binomial(n, k, target) << endl;

    cout << cnter;

    return 0;
}