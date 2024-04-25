// KNU CSE 2021114026 Jeongwoo Kim
// AX2.7, Advanced Hanoi
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

int ax_i = 0;
int ax_j = 0;
int isFound = 0;

bool isNumberValid(int plate_num, int count) {
    return count <= ((int)pow(2, plate_num)) - 1;
}

void advancedHanoi(pair<char, char>& answer, int& callCount, int plate, int& tgCount, char from, char via, char to) {
    ax_i++;
    if (plate == 1) {
        // cout << "Current: " << from << "->" << to << endl;
        if (ax_j == tgCount - 1 && !isFound) {
            // cout << "Target Approched: " << from << "->" << to << endl;
            answer = make_pair(from, to);
            isFound = 1;
        }
        else {
            ax_j++;
        }
        return;
    }
    advancedHanoi(answer, callCount, plate - 1, tgCount, from, to, via);
    advancedHanoi(answer, callCount, 1, tgCount, from, via, to);
    advancedHanoi(answer, callCount, plate - 1, tgCount, via, from, to);
}

void advanced_Hanoi(pair<char, char>& answer, int& callCount, int plate, int& tgCount, char from, char via, char to) {
    ax_i++;
    if (plate == 1) {
        // cout << "Current: " << from << "->" << to << endl;
        if (ax_j == tgCount - 1 && !isFound) {
            // cout << "Target Approched: " << from << "->" << to << endl;
            answer = make_pair(from, to);
            isFound = 1;
        }
        else {
            ax_j++;
        }
        return;
    }
    advancedHanoi(answer, callCount, plate - 1, tgCount, from, to, via);
    advancedHanoi(answer, callCount, 1, tgCount, from, via, to);
    advancedHanoi(answer, callCount, plate - 1, tgCount, via, from, to);
}

void hni_cnt(ll n, ll k, char from, char via, char to) {
    //if (n == 1) return;
    if (k == 0) {
        cout << from << "->" << to << endl;
        return;
    }
    else {
        
        if (k < (ll)pow((double)2, (double)(n - 1))) {
            hni_cnt(n - 1, k - 1, from, to, via);
            hni_cnt(1, k - 1, from, via, to);
            hni_cnt(n - 1, k - 1, via, from, to);
        }
        else {
            //hni_cnt((ll)pow((double)2, (double)(n - 1)), k, from, via, to);

            hni_cnt(n - 1, k - (ll)pow((double)2, (double)n - 1) - 1, from, to, via);
            hni_cnt(1, k - 1, from, via, to);
            hni_cnt(n - 1, k - (ll)pow((double)2, (double)n - 1) - 1, via, from, to);
        }
    }

    return;
}

ll mv_cnt;

void hnii_cnt(ll n, char from, char via, char to) {
    mv_cnt--;
    if (n == 1) return;
    if (mv_cnt == 0) {
        cout << from << "->" << via << endl;
        return;
    }
    else {
        hnii_cnt(n - 1, from, to, via);
        hnii_cnt(1, from, via, to);
        hnii_cnt(n - 1, via, from, to);
    }
}

int main(void) {
    int plate_num, mv_count;
    int ans = 0;
    pair<char, char> path;

    cin >> plate_num >> mv_cnt;

    if (!isNumberValid(plate_num, mv_count)) {
        cout << "Invaild input.\n";
        exit(1);
    }

    //advancedHanoi(path, ans, plate_num, mv_count, 'A', 'B', 'C');
    hni_cnt((ll)plate_num, mv_cnt, 'A', 'B', 'C');

    return 0;
}