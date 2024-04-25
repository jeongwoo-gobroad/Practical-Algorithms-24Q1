// KNU CSE 2021114026 Jeongwoo Kim
// Jumpgame: an algospot problem
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
typedef vector<vector<long>> mat;

/**
 * Recursive D&Q:
 *      func solve() {
 *          solve(n, RIGHT)
 *          solve(n, DOWN)
 *      }
*/
mat pth;
mat val;
mat sol;

void setMat(const int& size) {
    pth.resize(size + 1, vector<long>(size + 1, 0));
    val.resize(size + 1, vector<long>(size + 1, -1));
    sol.resize(size + 1, vector<long>(size + 1, 0));

    return;
}

void solve(const int& size) {
    int temp = pth[1][1];
    val[1][1] = temp;
    val[size][size] = -1;
    unsigned long long pthcnt = 0;

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (i == size && j == size) break;

            if (val[i][j] != -1) {
                if (i + val[i][j] <= size) {
                    val[i + val[i][j]][j] = pth[i + val[i][j]][j];
                    if (i + val[i][j] == size && j == size) pthcnt++;
                    //cout << "from " << "(" << i << ", " << j << ")" << endl;
                    //cout << "Moving to " << "(" << i + val[i][j] << ", " << j << ")" << endl;
                } else {}

                if (j + val[i][j] <= size) {
                    val[i][j + val[i][j]] = pth[i][j + val[i][j]];
                    if (i == size && j + val[i][j] == size) pthcnt++;
                    //cout << "from " << "(" << i << ", " << j << ")" << endl;
                    //cout << "Moving to " << "(" << i << ", " << j + val[i][j] << ")" << endl;
                } else {}
            }
        }
    }
    /*
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (val[i][j] != -1) {
                cout << val[i][j] << " ";
            }
            else {
                cout << "  ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
    */
    /*
    if (val[size][size] != 0) {
        cout << "NO";
    }
    else {
        cout << "YES";
    }
    cout << "\n";
    */

    cout << pthcnt;
    return;
}

int main() {
    int cnt, size;

    //cin >> cnt;

    //for (int i = 0; i < cnt; i++) {
        cin >> size;
        setMat(size);
        for (int j = 1; j <= size; j++) {
            for (int k = 1; k <= size; k++) {
                cin >> pth[j][k];
            }
        }
        solve(size);
   // }

    return 0;
}