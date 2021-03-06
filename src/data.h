#ifndef data_h
#define data_h

#include <string>
#include <stdint.h>

// used as arguments for "uint8_t piece" calls
#define PIECE_X 1
#define PIECE_O 2

class board_t {
public:
    board_t(const char* asString);
    std::string toString() const;
    bool is_order_turn() const;
    void flip_turn();
    uint8_t valueAt(size_t position) const;
    void play(size_t position, uint8_t piece);
    void undo(size_t position);
    size_t count_empty() const;
    
    int heuristic() const;
private:
    // 0==' '  1=='X'  2=='O'
    uint16_t data[36];
    // 0 for chaos, 1 for order
    uint8_t turn;
};

class move_t {
public:
    // indicates that game is over
    bool ended;
    // 0-35 position of play
    size_t position;
    // PIECE_X or PIECE_O
    uint8_t piece;
    // heuristic value
    int value;
    std::string toString() const;
    
    move_t(): ended(false), position(0), piece(0), value(0) {}
};

#endif /* data_h */
