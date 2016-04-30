#include <iostream>
#include <string.h>
#include "ai.h"

int main(int argc, const char * argv[]) {
    // set arguments with  command shift ,
    // example: "XO                                  c"
    if (argc <= 1) {
        std::cerr << "ERR: board is required" << std::endl;
        return 1;
    }
    if (strlen(argv[1]) != 37) {
        std::cerr << "ERR: board must be exactly 37 characters" << std::endl;
        return 1;
    }
    board_t board(argv[1]);
    std::cerr << "Input board is: '" << board.toString() << "'" << std::endl;
    std::cerr << "Heuristic value: " << board.heuristic() << std::endl;
    move_t m = ab_move(board, 5);
    std::cout << m.toString() << std::endl;
    board.flip_turn();
    board.play(m.position, m.piece);
    std::cerr << "Final board: '" << board.toString() << "'" << std::endl;
    return 0;
}
