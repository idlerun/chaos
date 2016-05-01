# Order and Chaos AI

This is a basic AI for the game Order and Chaos.

## Game Rules
I heard about the game Order and Chaos from [Tom Scott's youtube video](https://www.youtube.com/watch?v=qsjVfJur1ac)

The basics of the game are as follows:

* Two players have a role assigned, one is ORDER, the other is CHAOS
* The game board is a 6x6 grid
* The players alternate playing. Either player plays either an X or an O
* The ORDER player wins if there is a horizontal, vertical, or diagonal set of five Xes OR five Oes
* The CHAOS player wins by denying the ORDER playing such a set of five Xes or Oes until the game ends

## AI
Simple AI with alpha-beta pruning

### Heuristic
There are 32 possible sets of 5 positions which can be a WIN for the ORDER player.

* 12 horizontal
* 12 vertical
* 4 diagonal \
* 4 diagonal /

The heuristic evaluates each of those 32 lines and assigns it a value.

* If there is a combination of Xes and Oes, then the value is -1 since order cannot win that line.
* Otherwise the score is positive and depends on the number of filled spaces in the line (XXX is valued higher than XX)

The overall heuristic is a sum of all 32 line heuristics

To quickly lookup the line heuristic. I used a simple Python script 
([generator.py](https://github.com/idlerun/chaos/blob/master/generator.py))
which generates a 1024 element lookup table. The 5 positions in a line are converted to 
a 10 bit value (2 bits per position). That value can be instantly converted to a value by indexing into
the lookup table.

## [play.js](https://github.com/idlerun/chaos/blob/master/play.js)
This is a simple NodeJS script which plays two AIs against each other.
It requires the AI to accept the current board state as an argument and writes out a move to stdout

It will play the AIs back and forth until one of them is determined to be the winner
