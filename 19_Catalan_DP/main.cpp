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
typedef unsigned long long ultLong;

void getCatalan(vector<ultLong>& t, int n) {
    int rtnVal = 0;

    t.resize(n + 1, 0);
    t[0] = 3;

    for (int i = 1; i <= n; i++) {
        for (int x = 0; x < i; x++) {
            t[i] += t[x] * t[(i - 1) - x];
            //printf("Comp %d += %d x %d\n", i, x, (i - 1) - x);
            // 0 0 0 0
            // 0 1 1 0 1 0 0 1
            t[i] %= 10007;
        }
        //t[i] %= 10007;
        //t[i] *= 2;
    } 

    for (int i = 0; i <= n; i++) {
        cout << i << "th: " << t[i] << endl;
    }

    cout << t[n] << endl;

    return;
}

void getFastCatalan(int n) {

}

int main(void) {
    vector<ultLong> tgt;
    int num;

    cin >> num;

    getCatalan(tgt, num);

    return 0;
}