// KNU CSE 2021114026 Jeongwoo Kim
// AX06 P03: Longest Common Substring Problem
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef vector<vector<int>> matrix;

int getMax(const int& a, const int& b) {
    if (a > b) {
        return a;
    }

    return b;
}
int getPath(const int& b, const int& a) {
    /*
        Access Modifier Number Definition
        |   1   |  2(a) |
        |  3(b) |  src  | && when 2 OR 3 then 4 
    */
    if (a > b) {
        return 2;
    }
    else if (a < b) {
        return 3;
    }

    return 4;
}

/*                        string A         string B   opt.value  opt.path  */
void get_LCS_Length(const string& a, const string& b, matrix& v, matrix& s) {
    /*
        Access Modifier Number Definition
        |   1   |   2   |
        |   3   |  src  | && when 2 OR 3 then 4 
    */
    for (int a_idx = 1; a_idx < a.size(); a_idx++) {
        for (int b_idx = 1; b_idx < b.size(); b_idx++) {
            if (a[a_idx] == b[b_idx]) {
                /* Should refer to previous index of both A and B */
                /* This week's main topic: Optimal Solution w/ restricted path access */
                v[a_idx][b_idx] = v[a_idx - 1][b_idx - 1] + 1; // +1 means new char match has found.
                s[a_idx][b_idx] = 1;
            }
            else {
                v[a_idx][b_idx] = getMax(v[a_idx][b_idx - 1], v[a_idx - 1][b_idx]);
                s[a_idx][b_idx] = getPath(v[a_idx][b_idx - 1], v[a_idx - 1][b_idx]);
            }
        }
    }

    return;
}

/*                        focused on index of str A; iA := idx_A, iB := idx_B */
void print_All_LCS_Path(const matrix& p, stack<char> sol, int iA, int iB, const string& str) {
    switch (p[iA][iB]) {
        case 0:         // exit condition && printing
            while (!sol.empty()) {
                cout << sol.top() << " ";
                sol.pop();
            }
            cout << endl;

            break;
        case 1:
            sol.push(str[iA]);
            print_All_LCS_Path(p, sol, iA - 1, iB - 1, str);

            break;
        case 2:
            print_All_LCS_Path(p, sol, iA - 1, iB, str);
            
            break;
        case 3:
            print_All_LCS_Path(p, sol, iA, iB - 1, str);

            break;
        case 4:
            print_All_LCS_Path(p, sol, iA - 1, iB, str);
            print_All_LCS_Path(p, sol, iA, iB - 1, str);

            break;
        default:
            break;
    }

    return;
}

/*                        focused on index of str A; iA := idx_A, iB := idx_B */
void print_Only_One_Path(const matrix& p, stack<char> sol, int iA, int iB, const string& str) {
    switch (p[iA][iB]) {
        case 0:         // exit condition && printing
            while (!sol.empty()) {
                cout << sol.top();
                sol.pop();
            }

            break;
        case 1:
            sol.push(str[iA]);
            print_Only_One_Path(p, sol, iA - 1, iB - 1, str);

            break;
        case 2: case 4:
            print_Only_One_Path(p, sol, iA - 1, iB, str);
            
            break;
        case 3:
            print_Only_One_Path(p, sol, iA, iB - 1, str);

            break;
        default:
            break;
    }

    return;
}

int main(void) {
    string str_A, str_B;
    string input;
    matrix op_val;
    matrix op_sol;
    stack<char> temp;

    // + 1 for dummy operation
    str_A.push_back(' ');
    str_B.push_back(' ');
    
    cin >> input;
    str_A.append(input);
    cin >> input;
    str_B.append(input);

    // + 1 for dummy operation; when row - 1 OR col - 1 is operated when row := ROWSTT OR col := COLSTT
    op_val.resize(str_A.size(), vector<int>(str_B.size(), 0));
    op_sol.resize(str_A.size(), vector<int>(str_B.size(), 0));

    get_LCS_Length(str_A, str_B, op_val, op_sol);
    cout << op_val[str_A.size() - 1][str_B.size() - 1];
    if (op_val[str_A.size() - 1][str_B.size() - 1] != 0) cout << "\n";

    //print_All_LCS_Path(op_sol, temp, str_A.size() - 1, str_B.size() - 1, str_A);
    print_Only_One_Path(op_sol, temp, str_A.size() - 1, str_B.size() - 1, str_A);

    return 0;
}