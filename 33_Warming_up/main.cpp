// KNU CSE 2021114026 Jeongwoo Kim
// Boj no. 25418
#include <iostream>
#include <vector>

#define MAX 1000

using namespace std;

typedef vector<vector<int>> mat;

void solve(const int& from, const int& to) {
    int tempi, isFound = 0;
    int temp;
    mat t;
    t.resize(MAX + 1, vector<int>(MAX + 1, 0));

    t[0][0] = from;
    for (int i = 1; i <= MAX; i++) {
        t[i][0] = from + i;
        t[0][i] = from * 2 * i;
    }

    for (int gap = 2; gap <= MAX; gap++) {
        for (int i = 1; i < gap; i++) {
            tempi = gap - i;
            t[i][tempi] = t[i - 1][tempi - 1] + (i - 1) + t[i - 1][tempi - 1] * 2 * (tempi - 1);
            if (t[i][tempi] == to) {
                isFound = tempi + i;
                break;
            }
        }
        if (isFound) {
            break;
        }
    }

    cout << isFound;

    return;
}

int main(void) {
    int from, to;

    cin >> from >> to;

    solve(from, to);

    return 0;
}