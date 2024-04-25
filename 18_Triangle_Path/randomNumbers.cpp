#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

int main(void) {
    int n;
    int c = 0;

    cin >> n;

    random_device rnd;

    mt19937 gen(time(NULL));
    uniform_int_distribution<int> dist(0, 99);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << dist(gen);
            if (j != n) cout << " ";
            c++;
        }
        cout << endl;
    }
    cout << c;

    return 0;
}