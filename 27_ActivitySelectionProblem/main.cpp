// KNU CSE 2021114026 Jeongwoo Kim
// Chapter 06. Problem No. 4: "Activity Selection Problem"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/*           stt  end        */
typedef pair<int, int> meeting;
typedef queue<meeting> occupied;

void assign(occupied target, occupied& opt_sol, int& opt_val) {
    meeting temp;

    temp = target.front();
    opt_val++;
    target.pop();
    opt_sol.push(temp);

    while (!target.empty()) {
        if (target.front().first >= temp.second) {
            temp.second = target.front().second;
            opt_sol.push(target.front());
            opt_val++;
        }
        target.pop();
    }

    return;
}

int main(void) {
    int cnt;
    int ans = 0;
    int stt, end;
    occupied input, greedy_table;

    cin >> cnt;

    for (int i = 0; i < cnt; i++) {
        cin >> stt >> end;
        input.push(make_pair(stt, end));
    }

    assign(input, greedy_table, ans);

    cout << ans << "\n";

    while (!greedy_table.empty()) {
        cout << greedy_table.front().first << " " << greedy_table.front().second;
        greedy_table.pop();
        if (!greedy_table.empty()) {
            cout << "\n";
        }
    }

    return 0;
}