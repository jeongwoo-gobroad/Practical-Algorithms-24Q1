// KNU CSE 2021114026 Jeongwoo Kim
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ultLong;
typedef vector<ultLong> arr;

ultLong iterFib(int n) {
    arr v;
    v.resize(n + 1, 0);

    v[0] = 1;
    v[1] = 1;
    v[2] = 2;

    for (int i = 3; i <= n; i++) {
        //cout << v[i - 1] << " " << v[i - 2] << endl;
        v[i] = (v[i - 1] + v[i - 2] + v[i - 3]) % 10007;
    }

    return v[n];
}

int main(void) {
    int n;

    cin >> n;

    cout << iterFib(n);

    return 0;
}