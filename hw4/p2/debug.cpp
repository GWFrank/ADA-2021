#include<bits/stdc++.h>
// #include <iostream>
// #include <vector>
using namespace std;

struct board {
    vector<vector<int>> mp;
};

void initBoard(board &bd) {
    bd.mp.clear();
    bd.mp.resize(7);
    fill(bd.mp.begin(), bd.mp.end(), vector<int>(6, 0));
}

void printBoard(board &bd) {
    cerr << "-------\n";
    for (int i=5; i>=0; --i) {
        for (int j=0; j<7; j++) {
            if (bd.mp[j][i] == 1)
                cerr << "O";
            else if (bd.mp[j][i] == -1)
                cerr << "X";
            else
                cerr << " ";
        }
        cerr << "\n";
    }
    cerr << "-------\n";
}

int detect4(board &bd) {
    // 4 in col
    for (int i=0; i<7; ++i) {
        int prev=0, streak=1;
        for (int j=0; j<6; ++j) {
            if (bd.mp[i][j] == prev) {
                ++streak;
                if (streak >= 4 && prev != 0) {
                    return prev;
                }
            } else {
                prev = bd.mp[i][j];
                streak = 1;
            }
        }
    }
    // 4 in row
    for (int j=0; j<6; ++j) {
        int prev=0, streak=1;
        for (int i=0; i<7; ++i) {
            if (bd.mp[i][j] == prev) {
                ++streak;
                if (streak >= 4 && prev != 0)
                    return prev;
            } else {
                prev = bd.mp[i][j];
                streak = 1;
            }
        }
    }
    // diagnal (x+y=k)
    for (int k=3; k<=8; ++k) {
        int x, y, prev=0, streak=1;
        for (x=0; x<7; ++x) {
            y = k-x;
            if (y>=6)
                continue;
            else if (y<0)
                break;
            if (bd.mp[x][y] == prev) {
                ++streak;
                if (streak >= 4 && prev != 0)
                    return prev;
            } else {
                prev = bd.mp[x][y];
                streak = 1;
            }
        }
    }
    // diagnoal (x-y=k)
    for (int k=-2; k<=3; ++k) {
        int x, y, prev=0, streak=1;
        for (x=0; x<7; ++x) {
            y = k+x;
            if (y>=6)
                break;
            else if (y<0)
                continue;
            if (bd.mp[x][y] == prev) {
                ++streak;
                if (streak >= 4 && prev != 0)
                    return prev;
            } else {
                prev = bd.mp[x][y];
                streak = 1;
            }
        }
    }
    return 0;
}

int main() {
    char mp[6][8] = {
        "   O   ",
        " O O   ",
        " XOX   ",
        " OXO   ",
        " XOX   ",
        "OXXOXX "
    };
    board bd;
    initBoard(bd);
    for (int i=0; i<7; i++) {
        for (int j=0; j<6; j++) {
            switch (mp[5-j][i]) {
                case 'O':
                    bd.mp[i][j] = 1;
                    break;
                case 'X':
                    bd.mp[i][j] = -1;
                    break;
                case ' ':
                    bd.mp[i][j] = 0;
                    break;
            }
            
        }
    }
    printBoard(bd);
    int winner = detect4(bd);
    cout << "winner: "<< winner << "\n";
    return 0;
}