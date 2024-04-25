// KNU CSE 2021114026 Jeongwoo Kim
// AX2.5, Collatz Conjecture
#include <iostream>

using namespace std;

typedef unsigned long long ultLong;

void printCollatz(ultLong target) {
    if (target == 1) {
        cout << target;
        return;
    }
    else {
        cout << target << " ";
    }

    if (!(target % 2)) {
        printCollatz(target / 2);
    }
    else {
        printCollatz(target * 3 + 1);
    }
}

int main(void) {
    ultLong run;

    cin >> run;

    printCollatz(run);

    return 0;
}