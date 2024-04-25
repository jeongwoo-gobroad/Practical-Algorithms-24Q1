// KNU CSE 2021114026 Jeongwoo Kim
// Chapter 06. Problem No. 1: "Prim's Minimum Spanning tree"
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>

#define INF 9999999

using namespace std;

typedef vector<vector<int>> mat;
typedef vector<int> tab;
typedef queue<tuple<int, int, int>> span;
typedef void debug_feature;

debug_feature printArr(const tab& a, int from, int to) {
    for (int i = from; i < to; i++) {
        cout << a[i];
        if (i != to - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    return;
}

void prim_MST(const mat& t, tab& opt_sol, tab& opt_val, span& tree) {
    int eleCnt = t.size();
    int localOptVal = INF;
    int localOptSol = 1;

    for (int i = 1; i < eleCnt; i++) {
        opt_val[i] = t[1][i]; // starting from 1st vertex!
        opt_sol[i] = 1;
    }
    printArr(opt_sol, 2, opt_sol.size());

    for (int x = 1; x < eleCnt - 1; x++) { // looping for n-1 times!
        int localOptVal = INF;
        for (int i = 2; i < eleCnt; i++) { // starting from 2 to avoid pointing itself at start
            /*  Not Visited    AND  optimal(smaller) than prev value */
            if (opt_val[i] >= 0 && opt_val[i] < localOptVal) {
                localOptVal = opt_val[i];
                localOptSol = i;
            }
        }

        /* inserting local optimal solution */
        tree.push(make_tuple(localOptSol, opt_sol[localOptSol], localOptVal));
        /* then make it visited */
        opt_val[localOptSol] = -1;

        /* updating accumulated local optimal sol, val */
        for (int i = 2; i < eleCnt; i++) {
            if (opt_val[i] >= 0 && opt_val[i] > t[localOptSol][i]) {
                opt_val[i] = t[localOptSol][i];
                // opt_sol acts like somewhat "to-able indexes"
                opt_sol[i] = localOptSol;
            }
        }

        printArr(opt_sol, 2, opt_sol.size());
    }

    return;
}

void initMat(mat& t) {
    for (int i = 0; i < t.size(); i++) {
        t[i][i] = 0;
    }

    return;
}

int main(void) {
    int vertexNum, edgeNum;
    int tempFrom, tempTo, weight;
    mat adj;
    tab greedTable; tab toAbles;
    span global_opt_sol;

    cin >> vertexNum >> edgeNum;

    adj.resize(vertexNum + 1, vector<int>(vertexNum + 1, INF));
    initMat(adj);
    greedTable.resize(vertexNum + 1);
    toAbles.resize(vertexNum + 1);

    for (int i = 0; i < edgeNum; i++) {
        cin >> tempFrom >> tempTo >> weight;
        adj[tempFrom][tempTo] = weight;
        adj[tempTo][tempFrom] = weight; // undirected!
    }

    prim_MST(adj, greedTable, toAbles, global_opt_sol);

    while (!global_opt_sol.empty()) {
        cout << get<0>(global_opt_sol.front()) << " " << get<1>(global_opt_sol.front()) << " " << 
            get<2>(global_opt_sol.front());
        global_opt_sol.pop();
        if (!global_opt_sol.empty()) {
            cout << "\n";
        }
    }

    return 0;
}