// KNU CSE 2021114026 Jeongwoo Kim
// AX3.5. Power of Matrix!!!
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> matrix;

matrix matrixMultiplication(matrix A, matrix B) {
    matrix rtn;
    if (A[0].size() != B.size()) {
        cout << "Error: Cannot multiply given matrices." << endl;
        exit(1);
    }

    rtn.resize(A.size(), vector<int>(B[0].size(), 0));

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < A[0].size(); k++) {
                // rtn[i][j] += (A[i][k] * B[k][j]) % 1000;
                rtn[i][j] = (rtn[i][j] + A[i][k] * B[k][j]) % 1000;
            }
        }
    }

    return rtn;
}

matrix modMult_Recursive(matrix target, int pow) {
    if (pow == 1) return target;
    matrix temp;

    /* Odd Power (I feel strange) */
    if ((pow % 2)) {
        temp = modMult_Recursive(target, (pow - 1) / 2);
        return matrixMultiplication(target, matrixMultiplication(temp, temp));
    }
    /* Even Power */
    else {
        temp = modMult_Recursive(target, pow / 2);
        return matrixMultiplication(temp, temp);
    }
}

int main(void) {
    int size; int powerNum;
    matrix mat;

    cin >> size >> powerNum;

    mat.resize(size, vector<int>(size, 0));

    for (auto& row: mat) {
        for (auto& col: row) {
            cin >> col;
        }
    }

    mat = modMult_Recursive(mat, powerNum);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == size - 1) {
                cout << mat[i][j];
            }
            else {
                cout << mat[i][j] << " ";
            }
        }
        if (i == size - 1) {
                break;
        }
        else {
            cout << "\n";
        }
    }

    return 0;
}