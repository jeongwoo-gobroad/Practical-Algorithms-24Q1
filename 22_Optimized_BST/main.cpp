// KNU CSE 2021114026 Jeongwoo Kim
// AX06 P02: Optimized BST
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> matrix;

int getCdf(const matrix& t, int from, int to) {
    int cumulated = 0;

    for (; from <= to; from++) {
        cumulated += t[from][from];
    }

    return cumulated;
}

int getOptRoot(matrix& weighted, int from, int to) {
    int opRoot;
    int tempSum;

    for (int tempRoot = from; tempRoot <= to; tempRoot++) {
        tempSum = weighted[from][tempRoot - 1] + weighted[tempRoot + 1][to] + getCdf(weighted, from, to);
        if (!weighted[from][to]) {
            weighted[from][to] = tempSum;
            opRoot = tempRoot;
        }
        else {
            if (weighted[from][to] > tempSum) {
                weighted[from][to] = tempSum;
                opRoot = tempRoot;
            }
        }
    }

    return opRoot;
}

void getOptBST(matrix& weighted, matrix& pathtbl, const int& size) {
    int to;

    for (int gapSize = 1; gapSize <= size - 1; gapSize++) {
        for (int from = 1; from <= size - gapSize; from++) {
            to = from + gapSize;
            pathtbl[from][to] = getOptRoot(weighted, from, to);
        }
    }

    return;
}

void printDiagonal(const matrix& t) {
    for (int i = 1; i < t.size(); i++) {
        for (int j = i - 1; j < t.size() - 1; j++) {
            cout << t[i][j];
            if (j != t.size() - 2) {
                cout << " ";
            }
        }
        if (i != t.size() - 1) {
            cout << "\n";
        }
    }

    return;
}

void printKey(const vector<int>& v) {
    for (int i = 0; i <= v.size() - 1; i++) {
        cout << v[i];
        if (i != v.size() - 1) {
            cout << " ";
        }
    }

    return;
}

void getPreorder(const matrix& p, int from, int to, const vector<int>& key, vector<int>& stk) {
    // preorder: VLR visit
    int root;

    if (from > to) { // exit condition
        return;
    }

    root = p[from][to];

    /* Core Part */
    stk.push_back(key[root]);
    getPreorder(p, from, root - 1, key, stk);
    getPreorder(p, root + 1, to, key, stk);

    return;
}

void getInorder(const matrix& p, int from, int to, const vector<int>& key, vector<int>& stk) {
    // inorder: LVR visit
    int root;

    if (from > to) { // exit condition
        return;
    }

    root = p[from][to];

    /* Core Part */
    getInorder(p, from, root - 1, key, stk);
    stk.push_back(key[root]);
    getInorder(p, root + 1, to, key, stk);

    return;
}

int main(void) {
    int keyNum;
    vector<int> keyVal;
    matrix weight;
    matrix path;

    vector<int> tr_res; // traversal result

    /*Input seq #1*/
    cin >> keyNum;
    keyVal.resize(keyNum + 1, 0);
    tr_res.resize(0);
    weight.resize(keyNum + 2, vector<int>(keyNum + 2, 0)); // additional matrix size just for ease
    path.resize(keyNum + 2, vector<int>(keyNum + 2, 0)); // additional matrix size just for ease
    
    /*Input seq #2*/
    for (int i = 1; i <= keyNum; i++) {
        cin >> keyVal[i];
    }
    for (int i = 1; i <= keyNum; i++) {
        cin >> weight[i][i];
        path[i][i] = i;
    }

    getOptBST(weight, path, keyNum);

    /* print matrix */
    printDiagonal(weight);
    cout << "\n";
    printDiagonal(path);
    cout << "\n";
    cout << weight[1][keyNum] << "\n";

    /* print tree */
    getPreorder(path, 1, keyNum, keyVal, tr_res);
    printKey(tr_res);
    cout << "\n";
    tr_res.resize(0);
    getInorder(path, 1, keyNum, keyVal, tr_res);
    printKey(tr_res);

    return 0;
}