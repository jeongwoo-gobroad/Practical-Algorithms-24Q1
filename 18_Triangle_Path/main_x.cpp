// KNU CSE 2021114026 Jeongwoo Kim
// AX05. P04_v2: Longest Path on the Triangle
// Key Algorithm: Sums of Subproblems equals to the big problem.
/*
    Description:
        1. Since we don't have any information about how to optimally dividing the given problem,
           We just add up tiny results until we approach to the given problem.
        2. Since optimal solution can't be achieved during the calculation of optimal value,
           We backtrack from the final Weight.
        3. Each subproblems should be PARTIAL WEIGHT; If else, we cannot assmue the optimal path
           that lead us to the optimal value.
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef void debug_feature;
typedef vector<vector<int>> matrix;

int getMax(int a, int b) { 
    if (a < b) return a;

    return b;
}

debug_feature printPathTable(const matrix& path) {
    for (int i = 0; i < path.size(); i++) {
        for (int j = 0; j <= i; j++) {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }

    return;
}

void print_bfsPath(stack<int>& index, const matrix& target) {
    for (int i = 0; !index.empty(); i++) {
        cout << target[i][index.top()] << "->";
        //cout << i << " " << index.top() << endl;
        index.pop();
    }
    cout << "End of Path" << endl;

    return;
}

int bfsPath_recur(int cnter, stack<int> index, int row, int col, const matrix& weight, const matrix& target) {
    if (row < 1) {
        index.push(col);
        print_bfsPath(index, target);
        cnter = 1;
    }
    else {
        if (col == 0) {
            index.push(0);
            cnter = bfsPath_recur(cnter, index, row - 1, col, weight, target);
        }
        else if (col <= row) {
            index.push(col);
            if (weight[row - 1][col] == weight[row - 1][col - 1]) {
                // Right-shifted priority
                cnter = bfsPath_recur(cnter, index, row - 1, col, weight, target);
                cnter += bfsPath_recur(cnter, index, row - 1, col - 1, weight, target);
                // Counting Method is Important!
            }
            else {
                if (weight[row - 1][col] < weight[row - 1][col - 1]) {
                    cnter = bfsPath_recur(cnter, index, row - 1, col, weight, target);
                }
                else {
                    cnter = bfsPath_recur(cnter, index, row - 1, col - 1, weight, target);
                }
            }
        }
        else {
            index.push(col - 1);
            cnter = bfsPath_recur(cnter, index, row - 1, col - 1, weight, target);
        }
    }

    return cnter;
}

void printAllPath(const matrix& target, const matrix& weight) {
    int maxValue = weight[target.size() - 1][0];
    stack<int> pathStack;
    int pathCnter = 0;
    stack<int> temp;

    pathStack.push(0);

    for (int i = 1; i < target[0].size(); i++) {
        if (weight[target[0].size() - 1][i] < maxValue) {
            maxValue = weight[target[0].size() - 1][i];
            // pop everything!
            while (!pathStack.empty()) pathStack.pop();
            pathStack.push(i);
        }
        else if (weight[target[0].size() - 1][i] == maxValue) {
            pathStack.push(i);
        }
    }

    while (!pathStack.empty()) {
        pathCnter += bfsPath_recur(0, temp, target.size() - 1, pathStack.top(), weight, target);
        pathStack.pop();
        //cout << temp.empty() << endl;
    }

    cout << "All path counted: " << pathCnter << endl;

    return;
}

void printLongestPath(const matrix& target, const matrix& weight) {
    int maxValue = weight[target.size() - 1][0];
    int maxIndex = 0;
    vector<int> pathStack;

    for (int i = 1; i < target[0].size(); i++) {
        if (weight[target[0].size() - 1][i] < maxValue) {
            maxValue = weight[target[0].size() - 1][i];
            maxIndex = i;
        }
    }

    pathStack.push_back(maxIndex);
    for (int i = target.size() - 2; i >= 0; i--) {
        if (maxIndex <= i && weight[i][maxIndex] <= weight[i][maxIndex - 1]) {
            pathStack.push_back(maxIndex);
        }
        else {
            if (maxIndex) {
                maxIndex--;
            }
            pathStack.push_back(maxIndex);
            
        }
    }

    cout << maxValue << "\n";
    for (int i = 0; i < target.size(); i++) {
        cout << target[i][pathStack.back()];
        if (i != target.size() - 1) {
            cout << " ";
        }
        pathStack.pop_back();
    }

    return;
}

void getWeight(const matrix& target, matrix& weightedGraph) {
    weightedGraph[0][0] = target[0][0];

    for (int i = 0; i < target.size() - 1; i++) {
        for (int j = 0; j <= i + 1; j++) {
            if (j == 0) {
                weightedGraph[i + 1][j] = target[i + 1][j] + weightedGraph[i][j];
            }
            else if (j == i + 1) {
                weightedGraph[i + 1][j] = target[i + 1][j] + weightedGraph[i][j - 1];
            }
            else {
                weightedGraph[i + 1][j] = target[i + 1][j] + min(weightedGraph[i][j], weightedGraph[i][j - 1]);
            }
        }
    }

    printPathTable(weightedGraph);

    return;
}

int main(void) {
    int height;
    matrix input;
    matrix weight;
    vector<int> up; // representing bottom-up result
    
    cin >> height;

    if (height == 0) {
        cout << "0\n0";
        return 0;
    }

    input.resize(height, vector<int>(height, 0));
    weight.resize(height, vector<int>(height, -1));


    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> input[i][j];
        }
    }
    weight = input;

    getWeight(input, weight);

    printLongestPath(input, weight);
    cout << endl;

    printAllPath(input, weight);

    return 0;
}