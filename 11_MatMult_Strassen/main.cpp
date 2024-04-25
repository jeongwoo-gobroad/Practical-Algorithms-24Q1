// KNU CSE 2021114026 Jeongwoo Kim
// AX04, Problem 01; Strassen's Matrix Multiplication
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int threshold = 0;
static int counter = 0;
typedef vector<vector<int>> matrix;
typedef int debug_feature;

debug_feature printMat(string text, const matrix& target) {
    cout << "---------------------" << endl;

    for (const auto& row: target) {
        for (const auto& col: row) {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << "Well Operated till: " << text << endl;

    return 0;
}

unsigned int checkSizeAndRemap(unsigned int rowColNum) {
    unsigned int temp = 0;
    int cnter = 0;
    
    temp = rowColNum;
    for (; temp; cnter++, temp = temp >> 1);
    // bit shift until temp becomes zero.
    cnter--;

    if (1 << cnter == rowColNum) {
        return rowColNum;
    }

    // if lg(num) != integer
    return 1 << (cnter + 1);
}

matrix justMulti(const matrix& u, const matrix& v) {
    matrix result(u.size(), vector<int>(v[0].size(), 0));

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < u[0].size(); j++) {
            for (int k = 0; k < result[0].size(); k++) {
                result[i][k] += u[i][j] * v[j][k];
            }
        }
    }

    //printMat("justMulti", result);

    return result;
}

matrix justAdd_or_sub(const matrix& u, const matrix& v, int flag) {
    // flag := 0 | add
    // flag := 1 | sub
    matrix result(u.size(), vector<int>(v.size(), 0));

    if (flag) {
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                result[i][j] = u[i][j] - v[i][j];
            }
        }
    }
    else {
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                result[i][j] = u[i][j] + v[i][j];
            }
        }
    }
    
    //printMat("justAdd_or_Sub", result);

    return result;
}

void mat_copy(const matrix& from, matrix& to, int det) {
    /* Det Value
     *      | 1 | 2 |
     *      | 3 | 4 |
    */
    int newRow = 0, newCol = 0;
    int oldRowStt, oldRowEnd; int oldColStt, oldColEnd;

    to.resize(from.size() / 2, vector<int>(from.size() / 2, 0));

    switch (det) {
        case 1:
            oldRowStt = oldColStt = 0;
            oldRowEnd = oldColEnd = from.size() / 2;
            break;
        case 2:
            oldRowStt = 0; oldRowEnd = from.size() / 2;
            oldColStt = from.size() / 2; oldColEnd = from.size();
            break;
        case 3:
            oldRowStt = from.size() / 2; oldRowEnd = from.size();
            oldColStt = 0; oldColEnd = from.size() / 2;
            break;
        case 4:
            oldRowStt = from.size() / 2; oldRowEnd = from.size();
            oldColStt = from.size() / 2; oldColEnd = from.size();
            break;
        default:
            fprintf(stderr, "Error: mat_copy usage: det[1, 2, 3, 4]\n");
            exit(1);
    }

    for (int row = oldRowStt; row < oldRowEnd; row++, newRow++) {
        newCol = 0;
        for (int col = oldColStt; col < oldColEnd; col++, newCol++) {
            to[newRow][newCol] = from[row][col];
        }
    }

    //printMat("mat_copy", to);

    return;
}

matrix mat_merge(const matrix& ul, const matrix& ur, const matrix& ll, const matrix& lr) {
    int num = ul.size() * 2;
    int temp = 0, temp_temp = 0;
    matrix result(num, vector<int>(num, 0));

    // UPPER LEFT
    for (int i = 0; i < ul.size(); i++) {
        for (int j = 0; j < ul.size(); j++) {
            result[i][j] = ul[i][j];
        }
    }
    // UPPER RIGHT
    for (int i = 0; i < ur.size(); i++) {
        temp = 0;
        for (int j = ur.size(); j < num; j++, temp++) {
            result[i][j] = ur[i][temp];
        }
    }
    // LOWER LEFT
    temp = 0;
    for (int i = ll.size(); i < num; i++, temp++) {
        for (int j = 0; j < ll.size(); j++) {
            result[i][j] = ll[temp][j];
        }
    }
    // LOWER RIGHT
    for (int i = lr.size(); i < num; i++, temp_temp++) {
        temp = 0;
        for (int j = lr.size(); j < num; j++, temp++) {
            result[i][j] = lr[temp_temp][temp];
        }
    }

    //printMat("mat_merge", result);

    return result;
}

matrix longLiveStrassen(matrix u, matrix v) {
    matrix u11, u12, u21, u22, v11, v12, v21, v22;
    matrix m1, m2, m3, m4, m5, m6, m7;

    //printMat("longLiveStrassen, mat: u", u);
    //printMat("longLiveStrassen, mat: v", v);

    counter++;
    if (u.size() <= threshold) {
        return justMulti(u, v);
    }

    /* divide (copy) */
    /* Det Value
     *      | 1 | 2 |
     *      | 3 | 4 |
    */
    mat_copy(u, u11, 1); mat_copy(v, v11, 1);
    mat_copy(u, u12, 2); mat_copy(v, v12, 2);
    mat_copy(u, u21, 3); mat_copy(v, v21, 3);
    mat_copy(u, u22, 4); mat_copy(v, v22, 4);

    /* divide (recursive call) */
    // flag := 0 | add
    // flag := 1 | sub
    m1 = longLiveStrassen(justAdd_or_sub(u11, u22, 0), justAdd_or_sub(v11, v22, 0));
    m2 = longLiveStrassen(justAdd_or_sub(u21, u22, 0), v11);
    m3 = longLiveStrassen(u11, justAdd_or_sub(v12, v22, 1));
    m4 = longLiveStrassen(u22, justAdd_or_sub(v21, v11, 1));
    m5 = longLiveStrassen(justAdd_or_sub(u11, u12, 0), v22);
    m6 = longLiveStrassen(justAdd_or_sub(u21, u11, 1), justAdd_or_sub(v11, v12, 0));
    m7 = longLiveStrassen(justAdd_or_sub(u12, u22, 1), justAdd_or_sub(v21, v22, 0));

    return { // do not play this at home...
        mat_merge(
            justAdd_or_sub(
                justAdd_or_sub(
                    m1, m7, 0
                ),
                justAdd_or_sub(
                    m4, m5, 1
                ), 0
            ),
            justAdd_or_sub(
                m3, m5, 0
            ),
            justAdd_or_sub(
                m2, m4, 0
            ),
            justAdd_or_sub(
                justAdd_or_sub(
                    m1, m6, 0
                ),
                justAdd_or_sub(
                    m3, m2, 1
                ), 0
            )
        )
    };
}

int main(void) {
    unsigned int n, size;
    matrix a, b, result;

    cin >> n >> threshold;

    size = checkSizeAndRemap(n);
    a.resize(size, vector<int>(size, 0));
    b.resize(size, vector<int>(size, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    result = longLiveStrassen(a, b);

    cout << counter << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j];
            if (j != n - 1) {
            cout << " ";
            }
        }
        if (i != n - 1) {
            cout << "\n";
        }
    }

    return 0;
}