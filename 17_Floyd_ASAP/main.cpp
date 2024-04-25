// KNU CSE 2021114026 Jeongwoo Kim
// AX05. P03: Floyd's Optimal Route
// Key Algorithm: Sums of Subproblems equals to the big problem.
/*
    Description:
        1. Since we don't have any information about how to optimally dividing the given problem,
           We just add up tiny results until we approach to the given problem.
        2. Since partial optimal solution can be achieved during the calculation of optimal value,
           We store them, and backtrack from the final Weight.
        3. Each subproblems should be PARTIAL WEIGHT; If else, we cannot assmue the optimal path
           that lead us to the optimal value.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define INF 999

using namespace std;

typedef void debug_feature;
typedef vector<vector<int>> matrix;
typedef vector<pair<int, int>> direction;

void initAdjMat(matrix& target, int vertexNum) {
    target.resize(vertexNum, vector<int>(vertexNum));
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (i == j) {
                target[i][j] = 0;
            }
            else {
                target[i][j] = INF;
            }
        }
    }

    return;
}

int isPath(int from, int to, const matrix& update) {
    return update[from][to]; 
}

void depthFirstPrint(int from, int to, const matrix& update) {
    vector<int> fromStack;
    vector<int> toStack;
    int temp;

    toStack.push_back(to);
    fromStack.push_back(from);

    while (!toStack.empty()) {
        while ((temp = isPath(fromStack.back(), toStack.back(), update)) != 0) {
            toStack.push_back(temp);
        }
        fromStack.push_back(toStack.back());
        toStack.pop_back();
    }

    for (int i = 0; i < fromStack.size() - 1; i++) {
        cout << fromStack[i] << " ";
    }
    cout << fromStack[fromStack.size() - 1];

    return;
}

void printPath(int from, int to, const matrix& update, const matrix& weight) {
    vector<int> pathStack;
    int temp = to;

    if (weight[from][to] >= INF) {
        cout << "NONE";
        return;
    }
    /*  
        Key algorithm:
            1. if i->j route exists, check [update] to find out if there's a node to visit.
            2. if node x1 exists, then do
                2.1. i->x1; goto 1.
                2.2. x1->j; goto 1.
               until update[an][bn] == 0
            3. Pseudo Codes:
                3.1. Simple Recursive Form
                    func print(a, b)
                        if (up[a][b]) print(a, up[a][b]);
                        stdout->up[a][b]
                        if (up[a][b]) print(up[a][b], b);
                3.2. Iterative Form
                    above
    */
    depthFirstPrint(from, to, update);

    return;
}

void printMat(const matrix& target) {
    for (int i = 1; i < target.size(); i++) {
        for (int j = 1; j < target.size(); j++) {
            cout << target[i][j];
            if (j != target.size() - 1) {
                cout << " ";
            }
        }
        if (i != target.size() - 1) {
                cout << "\n";
            }
    }
}

void getFloyded(const matrix& target, matrix& dist, matrix& update) {
    for (int dimension = 1; dimension < target.size(); dimension++) {
        for (int from = 1; from < target.size(); from++) {
            if (dimension == from) { // n - 1
                continue;
            }
            for (int to = 1; to < target.size(); to++) {
                if (from == to || dimension == to) { // n - 2
                    continue;
                }

                /* Key Algorithm */
                // ">=" means that if the weight is the same, let the path to be the longest one.
                if (dist[from][to] > dist[from][dimension] + dist[dimension][to]) {
                    dist[from][to] = dist[from][dimension] + dist[dimension][to];
                    update[from][to] = dimension;
                }
            }
        }
    }
}

int main(void) {
    int from, to, weight;
    matrix adj;
    matrix dist;
    matrix lastVisit;
    direction list;
    int vertexNum;
    int edgeNum;
    int input;

    cin >> vertexNum >> edgeNum;

    initAdjMat(adj, vertexNum + 1);
    lastVisit.resize(vertexNum + 1, vector<int>(vertexNum + 1, 0));

    for (int i = 0; i < edgeNum; i++) {
        cin >> from >> to >> weight;
        adj[from][to] = weight;
    }
    dist = adj;

    cin >> input;
    list.resize(input, pair<int, int>{0, 0});
    for (int i = 0; i < input; i++) {
        cin >> list[i].first >> list[i].second;
    }

    getFloyded(adj, dist, lastVisit);
    printMat(dist);
    cout << "\n";
    printMat(lastVisit);

    for (int i = 0; i < input; i++) {
        cout << "\n";
        printPath(list[i].first, list[i].second, lastVisit, dist);
    }

    return 0;
}