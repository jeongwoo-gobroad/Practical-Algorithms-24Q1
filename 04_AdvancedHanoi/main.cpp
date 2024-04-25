// KNU CSE 2021114026 Jeongwoo Kim
// AX2.7, Hanoi operation w/ recursive features
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<int> poles(3, 0);
vector<stack<int>> pole_info(3);

int moveTarget = 0;

void hanoiPlateInit(int plate) {
    poles[0] = plate;
    for (int i = plate; i >= 1; i--) {
        pole_info[0].push(i);
    }
    pole_info[1].push(0); pole_info[1].pop();
    pole_info[2].push(0); pole_info[2].pop();

    return;
}

void hanoiPlateCount(char from, char to) {
    //poles[from - 65]--;
    //poles[to - 65]++;
    pole_info[to - 65].push(pole_info[from - 65].top());
    pole_info[from - 65].pop();

    cout << "Current Pole Status: \n";
    //cout << poles[0] << " " << poles[1] << " " << poles[2] << "\n";
    cout << pole_info[0].size() << " " << pole_info[1].size() << " " << pole_info[2].size() << "\n";
    for (int i = 0; i < 3; i++) {
        if (!pole_info[i].empty()) {
            cout << "Top of pole " << i << ": " << pole_info[i].top() << "\n";
        }
        else {
            cout << "Top of pole " << i << ": none\n";
        }
    }

    return;
}

void hanoi(int& callCount, int& count, pair<char, char>& answer, int plate, char from, char via, char to) {
    callCount++;
    
    if (plate == 1) {
        if (count != -1) {
            count--;
        }
        hanoiPlateCount(from, to);
        if (!count) {
            // cout << from << " to " << to << " Has saved.\n";
            answer.first = from;
            answer.second = to;
            count = -1;
        }
        return;
    }

    hanoi(callCount, count, answer, plate - 1, from, to, via);
    hanoi(callCount, count, answer, 1, from, via, to);
    hanoi(callCount, count, answer, plate - 1, via, from, to);
}

int main(void) {
    pair<char, char> data;
    int plate, count;
    int callNum = 0;

    cin >> plate >> count;

    hanoiPlateInit(plate);
    moveTarget = plate;

    hanoi(callNum, count, data, plate, 'A', 'B', 'C');

    cout << data.first << " -> " << data.second << "\n";
    cout << callNum;

    return 0;
}