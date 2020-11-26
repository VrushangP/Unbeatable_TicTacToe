#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

void init_boards() {
    int i;
    for ( i = 0; i < HSIZE; i++) {
        htable[i].init = 0;
    }
}

int depth( Board board ) {
    int i, depth = 0;
    for ( i = 0; i < 9; i++) {
        if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') {
            depth++;
        }
    }
    return depth;
}

char winner( Board board ) {
    int i;
    if (depth(board) == 9) {
        return '-';
    }
    for ( i = 0; i < 8; i++) {
        if (board[pos2idx[WINS[i][0]]] == 'X' && board[pos2idx[WINS[i][1]]] == 'X' && board[pos2idx[WINS[i][2]]] == 'X') {
            return 'X';
        } else if (board[pos2idx[WINS[i][0]]] == 'O' && board[pos2idx[WINS[i][1]]] == 'O' && board[pos2idx[WINS[i][2]]] == 'O') {
            return 'O';
        }
    }
    return '?';
}

char turn( Board board ) {
    if (depth(board) == 9 || winner(board) == 'O' || winner(board) == 'X') {
        return '-';
    }
    if (depth(board) % 2) {
        return 'O';
    } else {
        return 'X';
    }
}
void init_board( Board board ) {
    htable[board_hash(board)].init = 1;
    htable[board_hash(board)].depth = depth(board);
    htable[board_hash(board)].winner = winner(board);
    htable[board_hash(board)].turn = turn(board);
    strcpy(htable[board_hash(board)].board, board);
}

void join_graph( Board board ) {
    int i;
    if (winner(board) == 'O' || winner(board) == 'X') {
        for ( i = 0; i < 9; i++) {
            htable[board_hash(board)].move[i] = -1;
        }
    } else {
        for ( i = 0; i < 9; i++) {
            if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') {
                htable[board_hash(board)].move[i] = -1;
            } else {
                char new[BSIZE];
                strcpy(new, board);
                if (turn(board) == 'X') {
                    new[pos2idx[i]] = 'X';
                } else {
                    new[pos2idx[i]] = 'O';            
                }
                htable[board_hash(board)].move[i] = board_hash(new);
                if (htable[board_hash(new)].init == 0) {
                    init_board(new);
                    join_graph(new);
                }
            }
        }
    }
}

void score (Board board) {
    int i;
    if (winner(htable[board_hash(board)].board) == 'O') {
        htable[board_hash(board)].score = -1;
    } else if (winner(htable[board_hash(board)].board) == 'X') {
        htable[board_hash(board)].score = 1;
    }  else if(winner(htable[board_hash(board)].board) == '-') {
        htable[board_hash(board)].score = 0;
    } else { 
        int out;
        if (htable[board_hash(board)].turn == 'X') {
            out = -1;
            for (i = 0; i < 9; i++) {
                if (htable[board_hash(board)].move[i] != -1) {
                    score(htable[htable[board_hash(board)].move[i]].board);
                    if (htable[htable[board_hash(board)].move[i]].score > out)
                    out = htable[htable[board_hash(board)].move[i]].score;
                }
            }
        } else {
            out = 1;
            for (i = 0; i < 9; i++) {
                if (htable[board_hash(board)].move[i] != -1) {
                    score(htable[htable[board_hash(board)].move[i]].board);
                    if (htable[htable[board_hash(board)].move[i]].score < out)
                    out = htable[htable[board_hash(board)].move[i]].score;
                }
            }
        }
        htable[board_hash(board)].score = out;
    }
}

void compute_score() {
    score(START_BOARD);
}

int best_move( int board ) {
    int i, out, bestMove;
    if (htable[board].turn == 'X') {
        out = -1;
        for (i = 0; i < 9; i++) {
            if (htable[board].move[i] != -1) {
                if (htable[htable[board].move[i]].score > out){
                    out = htable[htable[board].move[i]].score;
                    bestMove = i;
                }
            }
        }
    } else {
        out = 1;
        for (i = 0; i < 9; i++) {
            if (htable[board].move[i] != -1) {
                if (htable[htable[board].move[i]].score < out) {
                    out = htable[htable[board].move[i]].score;
                    bestMove = i;
                }
            }
        }
    }
    return bestMove;
}