// KNU CSE 2021114026 Jeongwoo Kim
// Chapter 06. Problem No. 3: "Dijkstra's Single Source All Path with selectable starting point"
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>

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

void dijk_Path(const mat& t, tab& opt_sol, tab& opt_val, span& tree) {
    int eleCnt = t.size();
    int localOptVal = INF;
    int localOptSol = 1;
    vector<int> isVisited(eleCnt, 0);

    isVisited[1] = 1;
    for (int i = 1; i < eleCnt; i++) {
        opt_val[i] = t[1][i]; // starting from 1st vertex!
        opt_sol[i] = 1;
    }
    printArr(opt_sol, 2, opt_sol.size());

    for (int x = 1; x < eleCnt - 1; x++) { // looping for n-1 times!
        int localOptVal = INF;
        for (int i = 2; i < eleCnt; i++) { // starting from 2 to avoid pointing itself at start
            /*  Not Visited    AND  optimal(smaller) than prev value */
            if (!isVisited[i] && opt_val[i] < localOptVal) {
                localOptVal = opt_val[i];
                localOptSol = i;
            }
        }

        /* inserting local optimal solution: (from -> to | weight) */
        tree.push(make_tuple(opt_sol[localOptSol], localOptSol, t[opt_sol[localOptSol]][localOptSol]));
        /* then make it visited */
        isVisited[localOptSol] = 1;

        /* updating accumulated local optimal sol, val */
        for (int i = 2; i < eleCnt; i++) {
            if (!isVisited[i] && opt_val[i] > t[localOptSol][i] + localOptVal) { 
                opt_val[i] = t[localOptSol][i] + localOptVal;
                // opt_sol acts like somewhat "previous-path indexes what can be used recursively."
                opt_sol[i] = localOptSol;
            }
        }

        printArr(opt_sol, 2, opt_sol.size());
    }

    return;
}

void anyStt_dijkPath(const int& sttPoint, const mat& t, tab& opt_sol, tab& opt_val, span& tree) {
    int eleCnt = t.size();
    int localOptVal = INF;
    int localOptSol = 1;
    vector<int> isVisited(eleCnt, 0);

    /** Algorithm:
     *      1. opt_val is a "Greedy table", which stands for algorithmic table for feasibility check.
     *      2. opt_sol is a "Greedy Refresher", which stand for somewhat "Via-able" vertex number.
    */
    for (int i = 1; i < eleCnt; i++) {
        opt_sol[i] = sttPoint;
        opt_val[i] = t[sttPoint][i];
    }
    isVisited[sttPoint] = 1;

    for (int i = 1; i < eleCnt; i++) {
        if (i == sttPoint) {
            continue;
        }
        localOptVal = INF;
        for (int j = 1; j < eleCnt; j++) {
            if (!isVisited[j] && opt_val[j] < localOptVal) {
                localOptSol = j;
                localOptVal = opt_val[j];
            }
        }

        isVisited[localOptSol] = 1;
        /* inserting local optimal solution: (from -> to | weight) */
        tree.push(make_tuple(opt_sol[localOptSol], localOptSol, t[opt_sol[localOptSol]][localOptSol]));

        /* update greedy table */
        for (int j = 1; j < eleCnt; j++) {
             if (!isVisited[j] && opt_val[j] > localOptVal + t[localOptSol][j]) {
                opt_val[j] = localOptVal + opt_val[localOptSol];
                opt_sol[j] = localOptSol;
            }
        }

        printArr(opt_sol, 1, opt_sol.size());
    }
    return;
}

void getPath(const tab& opt_sol, int target) {
    stack<int> path;

    do {
        path.push(target);
        target = opt_sol[target];
    } while (path.top() != 1); // assume that every path starts from 1.

    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) {
            cout << " ";
        }
    }

    return;
}

void new_getPath(const int& stt, const tab& opt_sol, int target) {
    stack<int> path;

    do {
        path.push(target);
        target = opt_sol[target];
    } while (path.top() != stt); // configuable

    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) {
            cout << " ";
        }
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
    int cnt;
    queue<int> seek;
    mat adj;
    tab greedTable; tab toAbles;
    span global_opt_sol;
    int tmp;

    cin >> vertexNum >> edgeNum;

    adj.resize(vertexNum + 1, vector<int>(vertexNum + 1, INF));
    initMat(adj);
    greedTable.resize(vertexNum + 1);
    toAbles.resize(vertexNum + 1);

    for (int i = 0; i < edgeNum; i++) {
        cin >> tempFrom >> tempTo >> weight;
        adj[tempFrom][tempTo] = weight; // directed!
    }

    cin >> cnt; // get counter of endpoints to seek

    for (int i = 0; i < cnt; i++) {
        cin >> vertexNum;
        seek.push(vertexNum);
    }

    cout << "Starting index: ";
    cin >> tmp;

    anyStt_dijkPath(tmp, adj, greedTable, toAbles, global_opt_sol);

    while (!global_opt_sol.empty()) {
        cout << get<0>(global_opt_sol.front()) << " " << get<1>(global_opt_sol.front()) << " " << 
            get<2>(global_opt_sol.front());
        global_opt_sol.pop();

        cout << "\n";
    }

    while (!seek.empty()) {
        //getPath(greedTable, seek.front());
        new_getPath(tmp, greedTable, seek.front());
        seek.pop();
        if (!seek.empty()) {
            cout << "\n";
        }
    }

    cout << endl << "Path weight trace: " << endl;
    for (int i = 1; i < toAbles.size(); i++) {
        if (toAbles[i] == INF) {
            cout << "NO_PATH ";
        }
        else {
            cout << toAbles[i] << " ";
        }
    }
    cout << endl;

    return 0;
}