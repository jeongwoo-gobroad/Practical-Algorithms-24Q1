// KNU CSE 2021114026 Jeongwoo Kim
// AX04, Problem 03; A Tromino Problem
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define UPPER_LEFT 1
#define UPPER_RIGHT 2
#define LOWER_LEFT 3
#define LOWER_RIGHT 4
/*
* Standard Point: Upper Left Area
* Pre-Filled Area Determination:
*         |  1  |  2  |
*         |  3  |  4  |
*/

typedef vector<vector<int>> matrix;

static int globalCounter = 0;

void justFill (matrix& target, int xPos, int yPos) {
    ++globalCounter;

    for (int i = xPos; i < xPos + 2; i++) {
        for (int j = yPos; j < yPos + 2; j++) {
            if (!target[i][j]) {
                target[i][j] = globalCounter;
            }
        }
    }
}

void fill (matrix& target, int xPos, int yPos, int preFill) {
    ++globalCounter;
    switch (preFill) {
        case UPPER_LEFT:
            target[xPos + 1][yPos] = target[xPos + 1][yPos + 1] = target[xPos][yPos + 1] = globalCounter;
            break;
        case UPPER_RIGHT:
            target[xPos + 1][yPos] = target[xPos + 1][yPos + 1] = target[xPos][yPos] = globalCounter;
            break;
        case LOWER_LEFT:
            target[xPos][yPos] = target[xPos][yPos + 1] = target[xPos + 1][yPos + 1] = globalCounter;
            break;
        case LOWER_RIGHT:
            target[xPos][yPos] = target[xPos][yPos + 1] = target[xPos + 1][yPos] = globalCounter;
            break;
        default:
            fprintf(stderr, "Error\n");
            break;
    }

    return;
}

/*
int getPreFilledArea(const matrix& target, int xPos, int yPos, int prevPreFilledArea, int determinent) {
    if (target[xPos][yPos]) {
        switch (determinent) {
        case UPPER_LEFT:
            return LOWER_RIGHT;
            break;
        case UPPER_RIGHT:
            return LOWER_LEFT;
            break;
        case LOWER_LEFT:
            return UPPER_RIGHT;
            break;
        case LOWER_RIGHT:
            return UPPER_LEFT;
            break;
        default:
            fprintf(stderr, "Error\n");
            break;
        }
    }
    else {
        return prevPreFilledArea;
    }
}
*/

int blankedPlace(const matrix& target, int xPos, int yPos, int preX, int preY) {
    int retVal;
    if (preX <= xPos && preY <= yPos) {
        retVal = UPPER_LEFT;
    }
    else if (preX <= xPos && preY > yPos) {
        retVal = UPPER_RIGHT;
    }
    else if (preX > xPos && preY <= yPos) {
        retVal = LOWER_LEFT;
    }
    else {
        retVal = LOWER_RIGHT;
    }

    return retVal;
}

void tromino(matrix& target, int xPos, int yPos, int size, int preX, int preY) {
    int new_x_upper = xPos - size / 2;
    int new_y_left = yPos - size / 2;
    int new_x_lower = xPos + size / 2;
    int new_y_right = yPos + size / 2;

    // Debugging feature
    // printf("Current Pos: (%d, %d)\n", xPos, yPos);
    // printf("Current Size: %d\n", size);
    // printf("(%d, %d) | (%d, %d)\n(%d, %d) | (%d, %d)\n", new_x_upper, new_y_left, new_x_upper, new_y_right, new_x_lower, new_y_left, new_x_lower, new_y_right);
    // for (const auto& row: target) {
    //    for (const auto& col: row) {
    //        cout << col << " ";
    //    }
    //    cout << "\n";
    // }
    // cout << "\n\n";

    if (size == 1) {
        justFill(target, xPos, yPos);
        return;
    }
    else {
        fill(target, xPos, yPos, blankedPlace(target, xPos, yPos, preX, preY));

        if (!target[xPos][yPos]) { // UPPER LEFT
            tromino(target, new_x_upper, new_y_left, size / 2, preX, preY);
        }
        else {
            tromino(target, new_x_upper, new_y_left, size / 2, xPos, yPos);
        }
        if (!target[xPos][yPos + 1]) { // UPPER RIGHT
            tromino(target, new_x_upper, new_y_right, size / 2, preX, preY);
        }
        else {
            tromino(target, new_x_upper, new_y_right, size / 2, xPos, yPos + 1);
        }
        if (!target[xPos + 1][yPos]) { // LOWER LEFT
            tromino(target, new_x_lower, new_y_left, size / 2, preX, preY);
        }
        else {
            tromino(target, new_x_lower, new_y_left, size / 2, xPos + 1, yPos);
        }
        if (!target[xPos + 1][yPos + 1]) { // LOWER RIGHT
            tromino(target, new_x_lower, new_y_right, size / 2, preX, preY);
        }
        else {
            tromino(target, new_x_lower, new_y_right, size / 2, xPos + 1, yPos + 1);
        }
    }
}

int main(void) {
    matrix board;
    int n;
    int x, y; // initial blank

    cin >> n >> x >> y;

    board.resize(n, vector<int>(n, 0));
    board[x][y] = -1;

    tromino(board, (n - 1) / 2, (n - 1) / 2, n / 2, x, y);

    board[x][y] = 0;

    /*
    for (const auto& row: board) {
        for (const auto& col: row) {
            printf("%3d ", col);
        }
        cout << "\n";
    }
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cout << board[i][j] << " ";
        }
        cout << board[i][n - 1];
        if (i != n - 1) {
            cout << "\n";
        }
    }
    return 0;
}