// Refs & ppl discussed with
// b09902011 b09902100
// 鮑鈺文
// Kang, Xiyu & Wang, Yiqi & Hu, Yanrui. (2019). Research on Different Heuristics for Minimax Algorithm Insight from Connect-4 Game
#include "connect4.h"
using std::cerr;
using std::vector;
using std::pair;
struct board {
    vector<vector<int>> mp;
};

board BD;
const int DEPTH = 4;
const int MYMAX = 10000;
const int MYMIN = -MYMAX;
const int THREE = 10;
const int TWO = 0;
const int MAGIC[7][6] = {
    { 3,  4,  5,  5,  4,  3},
    { 4,  6,  8,  8,  6,  4},
    { 5,  8, 12, 12,  8,  5},
    { 7, 10, 14, 14, 10,  7},
    { 5,  8, 12, 12,  8,  5},
    { 4,  6,  9,  9,  6,  4},
    { 3,  5,  6,  6,  5,  3}
};

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

void initBoard(board &bd) {
    bd.mp.clear();
    bd.mp.resize(7);
    fill(bd.mp.begin(), bd.mp.end(), vector<int>(6, 0));
}

board makeMove(board bd, int col, int color) {
    for (int i=0; i<6; i++) {
        if (bd.mp[col][i] == 0) {
            bd.mp[col][i] = color;
            break;
        }
    }
    return bd;
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

int detect3(board &bd) {
    int total = 0;//, three_val = 10, two_val = 1;
    // col
    for (int i=0; i<7; ++i) {
        for (int j=0; (j+3)<6; ++j) {
            int tmp=0;
            for (int t=0; t<4; t++) {
                tmp+=bd.mp[i][j+t];
            }
            switch (tmp) {
                case 3: total += THREE; break;
                case -3: total -= THREE; break;
                case 2: total += TWO; break;
                case -2: total -= TWO; break;
            }
            // if (tmp == 3)
            //     total += THREE;
            // else if (tmp == -3)
            //     total -= THREE;
        }
    }
    // row
    for (int j=0; j<6; ++j) {
        for (int i=0; (i+3)<7; ++i) {
            int tmp=0;
            for (int t=0; t<4; t++) {
                tmp+=bd.mp[i+t][j];
            }
            switch (tmp) {
                case 3: total += THREE; break;
                case -3: total -= THREE; break;
                case 2: total += TWO; break;
                case -2: total -= TWO; break;
            }
            // if (tmp == 3)
            //     total += THREE;
            // else if (tmp == -3)
            //     total -= THREE;
        }
    }
    // diagnal (x+y=k)
    for (int k=3; k<=8; ++k) {
        int x, y, prev=0, streak=1;
        for (x=std::max(0, k-5); (x+3)<7 && (k-x)>=0; ++x) {
            y = k-x;
            int tmp=0;
            for (int t=0; t<4; t++) {
                tmp+=bd.mp[x+t][y+t];
            }
            switch (tmp) {
                case 3: total += THREE; break;
                case -3: total -= THREE; break;
                case 2: total += TWO; break;
                case -2: total -= TWO; break;
            }
            // if (tmp == 3)
            //     total += THREE;
            // else if (tmp == -3)
            //     total -= THREE;
        }
    }
    // diagnoal (x-y=k)
    for (int k=-2; k<=3; ++k) {
        int x, y, prev=0, streak=1;
        for (x=std::max(0, -k); (x+3)<7 && (y+3)<6; ++x) {
            y = k+x;
            int tmp=0;
            for (int t=0; t<4; t++) {
                tmp+=bd.mp[x+t][y+t];
            }
            switch (tmp) {
                case 3: total += THREE; break;
                case -3: total -= THREE; break;
                case 2: total += TWO; break;
                case -2: total -= TWO; break;
            }
            // if (tmp == 3)
            //     total += THREE;
            // else if (tmp == -3)
            //     total -= THREE;
        }
    }
    return total;
}

int eval(board &bd) {
    // int magic[7][6] = {
    //     { 3,  4,  6,  6,  4,  3},
    //     { 4,  6,  9,  9,  6,  4},
    //     { 6,  9, 12, 12,  9,  5},
    //     { 8, 11, 14, 14, 11,  7},
    //     { 6,  9, 12, 12,  9,  5},
    //     { 4,  6,  9,  9,  6,  4},
    //     { 3,  4,  6,  6,  4,  3}
    // };
    int score=0;
    int winner = detect4(bd);
    // cerr << "winner " << winner << "\n";
    if (winner != 0) {
        return (winner == 1) ? MYMAX : MYMIN;
    }
    // return detect3(bd);
    for (int i=0; i<7; ++i) {
        for (int j=0; j<6; ++j) {
            score += bd.mp[i][j]*MAGIC[i][j];
        }
    }
    return score + detect3(bd);
}

bool isFull(board &bd) {
    for (int i=0; i<7; ++i)
        if(bd.mp[i][5] == 0)
            return false;
    return true;
}

pair<int, int> minimax(board bd, int color, int depth, int alpha, int beta) {
    pair<int, int> rt; // best move, val
    if (depth == 0) {
        rt.first = -1;
        rt.second = eval(bd);
        return rt;
    }
    bool full = isFull(bd);
    // cerr << "full: " << full << "\n";
    if (color == 1) { // alpha player (maximizing)
        rt.first = -1; rt.second = MYMIN;
        if (full) {
            rt.second = eval(bd);
            return rt;
        }
        for (int i=0; i<7; ++i) {
            if (bd.mp[i][5] != 0) // column is full
                continue;
            board new_bd = makeMove(bd, i, color);
            int winner = detect4(new_bd);
            pair<int, int> mm_rt = minimax(new_bd, -color, depth-1, alpha, beta);
            if (winner != 0) mm_rt.second = (winner == 1) ? MYMAX : MYMIN;
            if (mm_rt.second > rt.second || (mm_rt.second == rt.second && std::abs(mm_rt.first-3) <= std::abs(rt.first-3))) { // better move
                rt.second = mm_rt.second;
                rt.first = i;
            }
            // alpha = (alpha >= rt.second) ? alpha : rt.second;
            // if (beta <= alpha) {
            //     break;
            // }
        }
    } else { // beta player (minimizing)
        rt.first = -1; rt.second = MYMAX;
        if (full) {
            rt.second = eval(bd);
            return rt;
        }
        for (int i=0; i<7; ++i) {
            if (bd.mp[i][5] != 0) // column is full
                continue;
            board new_bd = makeMove(bd, i, color);
            pair<int, int> mm_rt = minimax(new_bd, -color, depth-1, alpha, beta);
            int winner = detect4(new_bd);

            // printBoard(new_bd);
            if (winner != 0) {
                mm_rt.second = (winner == 1) ? MYMAX : MYMIN;
            }
            if (mm_rt.second <= rt.second) { // better move
                rt.second = mm_rt.second;
                rt.first = i;
            }
            // beta =  (beta <= rt.second) ? beta : rt.second;
            // if (beta <= alpha) {
            //     break;
            // }
        }
    }
    return rt;
}



// The columns are numbered from 0 to 6
int decide(int yp_move) {
    if (yp_move == -1) {
        // A new game starts
        // TODO: Please remember to reset everything here (if needed)
        initBoard(BD);
    }
    else {
        // YP placed his piece at column `yp_move` 
        BD = makeMove(BD, yp_move, -1);
    }
    // printBoard(BD);
    pair<int, int> rt = minimax(BD, 1, DEPTH, MYMIN-10, MYMAX+10);
    // cerr << "here\n";
    // cerr << "return: " << rt.first  << "," << rt.second << "\n";
    BD = makeMove(BD, rt.first, 1);
    return rt.first;
    // return 6; // always place at the rightmost column
}
