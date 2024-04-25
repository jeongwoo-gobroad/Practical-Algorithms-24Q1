// KNU CSE 2021114026 Jeongwoo Kim
// AX04, Problem 02; A Big Integer Multiplication Problem
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int threshold = 0;
static int counter = 0;
typedef vector<int> intString;
typedef vector<intString> catString;
typedef int debug_feature;


debug_feature printCurrentString(intString& target) {
    for (int i = target.size() - 1; i >= 0; i--) {
        cout << target[i];
    }
    cout << endl << "Current Size of IntString: " << target.size() << endl;
    cout << endl;
}

void rmZeros(intString& target) {
    int freeCnter = 0;

    for (int i = target.size() - 1; i >= 0; i--) {
        if (target[i] == 0) freeCnter++;
        else break;
    }
    if (freeCnter) {
        if (freeCnter == target.size()) {
            target.resize(1, 0);
        }
        else {
            target.resize(target.size() - freeCnter);
        }
    }

    return;
}

void carryString(intString& target) {
    int freeCnter = 0;

    for (int i = 0; i < target.size(); i++) { // note that no target.size() - 1
        target[i + 1] += target[i] / 10;
        target[i] = target[i] % 10;
    }

    rmZeros(target);
    //cout << "Carried" << endl;
    //printCurrentString(target);
    return;
}

intString justMulti(intString a, intString b) {
    intString result(a.size() + b.size(), 0);
    
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) { // new digits are represented as a sum of both index!
            result[i + j] += a[i] * b[j]; // should be able to add
        }
    }

    carryString(result);
    rmZeros(result);

    return result;
}

intString justAdd(intString a, intString b) {
    if (a.size() > b.size()) { // not creating any longer than longer one's digit + 1
        //a.resize(a.size() + 1);
        a.push_back(0); //much safer!
        for (int i = 0; i < b.size(); i++) {
            a[i] += b[i];
        }
        //cout << "Added" << endl;
        carryString(a);

        return a;
    }
    else {
        //b.resize(b.size() + 1);
        b.push_back(0); //much safer!
        for (int i = 0; i < a.size(); i++) {
            b[i] += a[i];
        }
        //cout << "Added" << endl;
        carryString(b);

        return b;
    }
}

/* uncarry used for justSub function */
intString uncarry(intString target, int index) {
    target[index + 1] -= 1;

    return target;
}
/* to remove minus values */
intString subCarry(intString target, int index) {
    if (target[index] < 0) {
        target[index] += 10;
        target = uncarry(target, index);
    }

    return target;
}

/* This function can only return positive values */
/** Important: from > sub
 *      just performing uncarry() during subtraction lead us to critical error:
 *          if 10000000000 - 99 has done, -1 value can be appeared in from vector.
 *          so that it means removing (-) values should be ALSO done AFTER all subtraction has finished.
*/
intString justSub(intString from, intString sub) {
    //cout << "from" << endl;
    //printCurrentString(from);
    //cout << "subtracting" << endl;
    //printCurrentString(sub);

    for (int i = 0; i < sub.size(); i++) {
        if (from[i] < sub[i]) {
            from[i] = from[i] + 10 - sub[i];
            from = uncarry(from, i); // Not recommended
        }
        else {
            from[i] = from[i] - sub[i];
        }
    }

    for (int i = sub.size(); i < from.size() - 1; i++) {
        from = subCarry(from, i);
    }

    rmZeros(from);

    //cout << "sub result: " << endl;
    //printCurrentString(from);

    return from;
}

intString catWithPow(intString target, int powNum) { // cat with meow
    target.resize(target.size() + powNum);

    //cout << target.size() << " " << powNum << endl;

    for (int i = target.size() - 1; i >= powNum; i--) {
        target[i] = target[i - powNum];
    }
    for (int i = 0; i < powNum; i++) {
        target[i] = 0;
    }
    //cout << "CatByPow" << endl;
    //printCurrentString(target);
    return target;
}

intString divByPow(intString target, int powNum) { // pownum := sttidx
    if (target.size() <= powNum) {
        return vector<int>(1, 0);
    }

    for (int i = powNum; i < target.size(); i++) {
        target[i - powNum] = target[i];
    }

    target.resize(target.size() - powNum);
    rmZeros(target);
    //cout << "DivByPow" << endl;
    //printCurrentString(target);
    return target;
}

intString modByPow(intString target, int powNum) {
    if (target.size() <= powNum) {
        return target;
    }
    target.resize(powNum);
    rmZeros(target);
    //cout << "ModByPow" << endl;
    //printCurrentString(target);
    return target;
}

intString big_integer_prod(intString a, intString b) {
    /* for a           for b */
    /* x*10^n + y      u*10^n + v */
    intString x, y; intString u, v;
    intString xu, xv, yu, yv;
    intString krt;
    int powNum;
    counter++;

    // Exit Condition #1: Being zero
    if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
        return vector<int>(1, 0); // zero
    }
    
    if (a.size() > b.size()) {
        powNum = a.size() / 2;
    }
    else {
        powNum = b.size() / 2;
    }

    // Exit Condition #2: Equations being simple
    if (a.size() <= threshold && b.size() <= threshold) {
        // just multi, then return
        return justMulti(a, b);
    }
    /* Optimizations
    else if (a.size() <= threshold && b.size() > threshold) {
        // only D&Q b
        // u = div of b 10^powNum
        u = divByPow(b, powNum);
        // v = mod of b 10^powNum
        v = modByPow(b, powNum);

        return justAdd(catWithPow(big_integer_prod(u, a), powNum), big_integer_prod(v, a));
    }
    else if (a.size() > threshold && b.size() <= threshold) {
        // only D&Q a
        // x = div of a 10^powNum
        x = divByPow(a, powNum);
        // y = mod of a 10^powNum
        y = modByPow(a, powNum);

        return justAdd(catWithPow(big_integer_prod(x, b), powNum), big_integer_prod(y, b));
    }
    */
    // Exit Condition #3: Still Need to D&Q
    else {
        // x = div of a 10^powNum
        x = divByPow(a, powNum);
        // y = mod of a 10^powNum
        y = modByPow(a, powNum);
        // u = div of b 10^powNum
        u = divByPow(b, powNum);
        // v = mod of b 10^powNum
        v = modByPow(b, powNum);

        
        /* traditional 
        // multi xu, xu*10^2powNum
        xu = catWithPow(big_integer_prod(x, u), 2 * powNum);
        // multi xv + multi yu, then *10^powNum
        xv = catWithPow(big_integer_prod(x, v), powNum);
        yu = catWithPow(big_integer_prod(y, u), powNum);
        // multi yv
        yv = big_integer_prod(y, v);
        // then add it all to result!
        */

        /* karatsuba method */
        krt = big_integer_prod(justAdd(x, y), justAdd(u, v));
        /* then... */
        xu = big_integer_prod(x, u); // power later...
        yv = big_integer_prod(y, v);
        krt = catWithPow(justSub(justSub(krt, xu), yv), powNum);
        xu = catWithPow(xu, 2 * powNum); // we have to achieve krt first 

        /* traditional return
        return justAdd(justAdd(xu, xv), justAdd(yu, yv));
        */
        /* karatsuba return */
        return justAdd(justAdd(xu, yv), krt);
    }
}

void printCurrentIntArr(const intString& t) {
    for (int i = t.size() - 1; i >= 0; i--) {
        cout << t[i];
    }
    cout << endl;

    return;
}

void getLongCatalan(catString& t, int n) {
    int rtnVal = 0;

    t.resize(n + 1, vector<int>(0));
    /* Initial value here */
    t[0].push_back(1);

    for (int i = 1; i <= n; i++) {
        for (int x = 0; x < i; x++) {
            t[i] = justAdd(t[i], big_integer_prod(t[x], t[(i - 1) - x]));
            //printf("Comp %d += %d x %d\n", i, x, (i - 1) - x);
            // 0 0 0 0
            // 0 1 1 0 1 0 0 1
        }
        cout << i << "th: ";
        printCurrentIntArr(t[i]);
    } 

    for (int i = 0; i <= n; i++) {
        cout << i << "th: ";
        printCurrentIntArr(t[i]);
    }

    cout << "ans :";
    printCurrentIntArr(t[n]);

    return;
}

int main(void) {
    catString tgt;
    int num;
    threshold = 5;
    cin >> num;

    getLongCatalan(tgt, num);

    return 0;
}