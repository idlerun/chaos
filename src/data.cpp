#include <assert.h>
#include "data.h"

// implementation for all of the data.h functions other than heuristic()

uint16_t fromChar(const char c) {
    if (c == 'X'){
        return PIECE_X;
    } else if (c == 'O') {
        return PIECE_O;
    } else {
        return 0;
    }
}

char toChar(uint16_t bits) {
    assert(bits <= 3);
    if (bits == PIECE_O) {
        return 'O';
    } else if (bits == PIECE_X){
        return 'X';
    } else {
        return ' ';
    }
}

board_t::board_t(const char* asString){
    for(int i=0;i<36;i++){
        data[i] = fromChar(asString[i]);
    }
    turn = asString[36] == 'o' ? 0 : 1;
}

std::string board_t::toString() const {
    char d[38];
    d[37] = '\0';
    for(int i=0;i<36;i++){
        d[i] = toChar(data[i]);
    }
    d[36] = turn ? 'c' : 'o';
    return std::string(d);
}

bool board_t::is_order_turn() const {
    return turn == 0;
}
void board_t::flip_turn() {
    turn = 1-turn;
}

uint8_t board_t::valueAt(size_t position) const {
    return data[position];
}

void board_t::play(size_t position, uint8_t piece) {
    data[position] = piece;
}

void board_t::undo(size_t position) {
    data[position] = 0;
}

size_t board_t::count_empty() const {
    size_t count = 0;
    for(size_t i=0; i<36; i++) {
        if (data[i] == 0) {
            count++;
        }
    }
    return count;
}

std::string move_t::toString() const {
    char d[4];
    d[0] = toChar(piece);
    d[1] = '0' + position / 10;
    d[2] = '0' + position % 10;
    d[3] = '\0';
    return std::string(d);
}