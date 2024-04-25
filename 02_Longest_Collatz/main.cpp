// KNU CSE 2021114026 Jeongwoo Kim
// AX2.6, Collatz Conjecture w/ advanced iterative counting
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ultLong;

vector<ultLong> createCollatz(ultLong target, int& length) {
    vector<ultLong> trigger;

    while (target != 1) {
        trigger.push_back(target);
        length++;
        if (!(target % 2)) {
            target /= 2;
        }
        else {
            target = 3 * target + 1;
        }
    }
    trigger.push_back(1);

    return trigger;
}

void chooseCollatz(ultLong from, ultLong to) {
    vector<ultLong> mem;
    vector<ultLong> save;
    int longest = 0;
    pair<ultLong, int> final_data(0, 0);
    
    for (ultLong in = from; in <= to; in++) {
        mem = createCollatz(in, longest);
        if (longest >= final_data.second) {
            final_data = make_pair(in, longest);
            save = mem;
        }
        longest = 0;
    }

    cout << final_data.first << " " << final_data.second << "\n";

    for (ultLong i: save) {
        if (i == 1) {
            cout << i;
        }
        else {
            cout << i << " ";
        }
    }

    return;
}

int main(void) {
    ultLong from, to;

    cin >> from >> to;

    chooseCollatz(from, to);

    return 0;
}