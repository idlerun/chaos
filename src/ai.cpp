#include "ai.h"

#define INFINITY 10000
#define NEG_INFINITY -INFINITY

/*
   0  1  2  3  4  5
   6  7  8  9 10 11
  12 13 14 15 16 17
  18 19 20 21 22 23
  24 25 26 27 28 29
  30 31 32 33 34 35
 */
// spiral out from the middle
size_t position_order[36] = {
    14,15,21,20,19,13,7,8,9,10,16,22,28,27,26,25,24,18,12,6,0,1,2,3,4,5,11,17,23,29,35,34,33,32,31,30
};

int alphabeta(board_t& board, const size_t depth, int alpha, int beta);

// return true if cutoff
bool playAlpha(board_t& board, int& alpha, const int beta,
               const size_t depth, const size_t position, const uint8_t piece) {
    board.play(position, piece);
    int c = alphabeta(board, depth-1, alpha, beta);
    if (c > alpha) {
        alpha = c;
        return beta <= alpha;
    } else {
        return false;
    }
}

// return true if cutoff
bool playBeta(board_t& board, const int alpha, int& beta,
               const size_t depth, const size_t position, const uint8_t piece) {
    board.play(position, piece);
    int c = alphabeta(board, depth-1, alpha, beta);
    if (c < beta) {
        beta = c;
        return beta <= alpha;
    } else {
        return false;
    }
}

int alphabeta(board_t& board, const size_t depth, int alpha, int beta) {
    if (depth == 0) {
        return board.heuristic();
    }
    if (board.is_order_turn()) {
        board.flip_turn();
        bool done = false; // switched to indicate ab cutoff
        for(size_t i=0; i<36 && !done; i++) {
            const size_t p = position_order[i];
            if (board.valueAt(p) == 0) {
                // try both X and O before resetting board
                done =
                    playAlpha(board, alpha, beta, depth, p, PIECE_X) ||
                    playAlpha(board, alpha, beta, depth, p, PIECE_O);
                board.undo(p);
            }
        }
        board.flip_turn();
        return alpha;
    } else {
        board.flip_turn();
        bool done = false; // switched to indicate ab cutoff
        for(size_t i=0; i<36 && !done; i++) {
            const size_t p = position_order[i];
            if (board.valueAt(p) == 0) {
                // try both X and O before resetting board
                done =
                    playBeta(board, alpha, beta, depth, p, PIECE_X) ||
                    playBeta(board, alpha, beta, depth, p, PIECE_O);
                board.undo(p);
            }
        }
        board.flip_turn();
        return beta;
    }
}

move_t ab_move(board_t& board, size_t depth) {
    if (depth > board.count_empty()) {
        depth = board.count_empty();
    }
    move_t result;
    if (depth == 0) {
        result.ended = true;
        return result;
    }
    bool resultSet = false;
    
    // copy of alphabeta but recording move position instead of value for return
    int alpha = NEG_INFINITY;
    int beta = INFINITY;
    if (board.is_order_turn()) {
        board.flip_turn();
        result.value = NEG_INFINITY;
        for(size_t i=0; i<36; i++) {
            const size_t p = position_order[i];
            if (board.valueAt(p) == 0) {
                if (!resultSet) {
                    // force result to be SOME valid value
                    resultSet = true;
                    result.position = p;
                    result.piece = PIECE_X;
                }
                // try both X and O before resetting board
                playAlpha(board, alpha, beta, depth, p, PIECE_X);
                if (alpha > result.value) {
                    result.position = p;
                    result.piece = PIECE_X;
                    result.value = alpha;
                }
                playAlpha(board, alpha, beta, depth, p, PIECE_O);
                if (alpha > result.value) {
                    result.position = p;
                    result.piece = PIECE_O;
                    result.value = alpha;
                }
                board.undo(p);
            }
        }
    } else {
        result.value = INFINITY;
        board.flip_turn();
        for(size_t i=0; i<36; i++) {
            const size_t p = position_order[i];
            if (board.valueAt(p) == 0) {
                if (!resultSet) {
                    // force result to be SOME valid value
                    resultSet = true;
                    result.position = p;
                    result.piece = PIECE_X;
                }
                // try both X and O before resetting board
                playBeta(board, alpha, beta, depth, p, PIECE_X);
                if (beta < result.value) {
                    result.position = p;
                    result.piece = PIECE_X;
                    result.value = beta;
                }
                playBeta(board, alpha, beta, depth, p, PIECE_O);
                if (beta < result.value) {
                    result.position = p;
                    result.piece = PIECE_O;
                    result.value = beta;
                }
                board.undo(p);
            }
        }
    }
    board.flip_turn();
    return result;
}