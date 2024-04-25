// KNU CSE 2021114026 Jeongwoo Kim
// Catalan
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define INF 999

using namespace std;

typedef void debug_feature;
typedef vector<vector<int>> matrix;

int isCollatzCycle(vector<int>& v, int n) {
    if (n == 1) {
        return 1;
    }
    else if (v[n] == 1) {
        return 0;
    }
    else {
        v[n] = 1;
        if (n % 2) {
            isCollatzCycle(v, 3 * n - 1);
        }
        else {
            isCollatzCycle(v, n / 2);
        }
    }
}

int main(void) {
    vector<int> temp;
    int n;
    int cnt = 0;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        temp.resize(1000000, 0);
        if (isCollatzCycle(temp, i) == 0) {
            cout << i << "is making cycle" << endl;
            cnt++;
        }
        temp.clear();
    }
    cout << "count: " << cnt << endl;

    return 0;
}