// KNU CSE 2021114026 Jeongwoo Kim
// AX06 P01: Optimized Sequence of Matrix Multiplication
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> matrix;

int getMultCount(const vector<int>& dim, int i, int j, int k) {
    // dim[] is defined as col num of given matrices except for dim[0]
    return dim[i - 1] * dim[j] * dim[k];
}

int chooseFittestVia(matrix& target, const vector<int>& dim, int from, int to) {
    int optPoint;
    int val;

    for (int via = from; via <= to - 1; via++) {
        val = target[from][via] + target[via + 1][to] + getMultCount(dim, from, via, to);
        if (!target[from][to]) {
            target[from][to] = val;
            optPoint = via;
        }
        else {
            if (target[from][to] > val) {
                target[from][to] = val;
                optPoint = via;
            }
        }
    }

    return optPoint;
}

void matMultiOptimalCount(matrix& target, matrix& save, const vector<int>& dim) {
    int to;
    int optPath;

    for (int cnt = 1; cnt <= target.size() - 2; cnt++) {
        /*
            *Core Part: To get diagonal matrix access
                1 2     1 3     1 4     1 5     1 6
                2 3     2 4     2 5     2 6
                3 4     3 5     3 6
                4 5     4 6
                5 6

                Diff Between two indexes increases.
                Range of [from] lessens.
                So, highest for loop should be the diff,
                iterative [from] loop should affected bt diff.
        */
        for (int from = 1; from <= (target.size() - 1) - cnt; from++) {
            to = from + cnt;
            save[from][to] = chooseFittestVia(target, dim, from, to);
        }    
    }
}

void printDiagonal(const matrix& t) {
    for (int i = 1; i < t.size(); i++) {
        for (int j = i; j < t.size(); j++) {
            cout << t[i][j];
            if (j != t.size() - 1) {
                cout << " ";
            }
        }
        if (i != t.size() - 1) {
            cout << "\n";
        }
    }

    return;
}

void print_withParanthesis(const matrix& t, int from, int to) {
    int via = t[from][to];

    if (!via) { // if itself, exit condition := 0
        cout << "A" << from;
        return;
    }

    cout << "(";
    print_withParanthesis(t, from, via);
    cout << ")(";
    print_withParanthesis(t, via + 1, to);
    cout << ")";

    return;
}

int main(void) {
    int cnt, input;
    matrix table;
    matrix path;
    vector<int> dim;

    cin >> cnt;

    dim.resize(cnt + 1, 0);
    table.resize(cnt + 1, vector<int>(cnt + 1, 0));
    path.resize(cnt + 1, vector<int>(cnt + 1, 0));

    for (int i = 0; i <= cnt; i++) { // d0 exists.
        cin >> dim[i];
    }

    matMultiOptimalCount(table, path, dim);

    printDiagonal(table);
    cout << "\n";
    printDiagonal(path);
    cout << "\n";

    cout << table[1][cnt] << "\n";
    cout << "(";
    print_withParanthesis(path, 1, cnt);
    cout << ")";

    return 0;
}