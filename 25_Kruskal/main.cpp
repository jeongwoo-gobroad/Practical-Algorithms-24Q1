// KNU CSE 2021114026 Jeongwoo Kim
// Chapter 06. Problem No. 2: "Kruskal's Minimum Spanning tree"
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>

#define INF 9999999

using namespace std;

typedef vector<vector<int>> mat;
typedef vector<int> tab;
/*            from to   weight*/
typedef tuple<int, int, int> edge;
typedef queue<edge> span;
typedef void debug_feature;

struct myCompare {
    bool operator()(edge a, edge b) {
        return get<2>(a) > get<2>(b);
    }
};
typedef priority_queue<edge, vector<edge>, myCompare> edgeHeap;

class uniFind {
private:
    tab set;
public:
    // constructor
    uniFind(int elementNum) {
        (this->set).resize(elementNum + 1);

        for (int i = 0 ; i < (this->set).size(); i++) {
            (this->set)[i] = i;
        }
    }
    // functions
    void merge(int what_to, int where_to) {
        // important: we have to MERGE each other's root. else it will lead us to error.
        (this->set)[find(what_to)] = find(where_to);

        return;
    }
    int find(int what) {
        if ((this->set)[what] != what) {
            (this->set)[what] = find((this->set)[what]); // optimizing
        }
        return (this->set)[what];
    }
    void print(void) {
        for (const auto& i: (this->set)) {
            cout << i << " ";
        }
        cout << endl;
    }
    bool isSameSet(int a, int b) {
        return find(a) == find(b);
    }
};

void kruskal_MST(edgeHeap& target, span& sol, const int& vtx) {
    edge temp;
    uniFind sets(vtx);

    while (sol.size() != vtx - 1) {
        if (target.empty()) {
            fprintf(stderr, "Not enough vertexes\n");
            exit(1);
        }
        temp = target.top();
        target.pop();

        // if (i, j), attach j->i!
        if (!sets.isSameSet(get<0>(temp), get<1>(temp))) {
            sol.push(temp);
            sets.merge(get<1>(temp), get<0>(temp));
        }

        sets.print();
    }

    return;
}

int main(void) {
    int vertexNum, edgeNum;
    int tempFrom, tempTo, weight;
    edgeHeap input;
    span global_opt_sol;

    cin >> vertexNum >> edgeNum;

    for (int i = 0; i < edgeNum; i++) {
        cin >> tempFrom >> tempTo >> weight;
        input.push(make_tuple(tempFrom, tempTo, weight));
    }

    kruskal_MST(input, global_opt_sol, vertexNum);

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