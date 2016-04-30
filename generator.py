#!/usr/bin/env python3

# just some helpful generators for cpp code

import sys
positions = []
for pos in range(0,36):
  positions.append([])

# horizontal wins
i = 0
for row in range(0,6):
  for start_col in range(0,2):
    for col in range(start_col, start_col+5):
      print("Add %d at %d,%d" % (i, row, col))
      positions[row*6+col].append(str(i))
    i = i+1

# vertical wins
for col in range(0,6):
  for start_row in range(0,2):
    for row in range(start_row, start_row+5):
      print("Add %d at %d,%d" % (i, row, col))
      positions[row*6+col].append(str(i))
    i = i+1

# \ wins
for start_pos in [0,1,6,7]:
  for x in range(0,5):
    positions[start_pos+x*7].append(str(i))
  i = i+1

# / wins
for start_pos in [4,5,10,11]:
  for x in range(0,5):
    positions[start_pos+x*5].append(str(i))
  i = i+1

print("i=%d" % i)
wins = []
for pos in range(0,i):
  wins.append([])
for x in range(0,36):
  for win in positions[x]:
    wins[int(win)].append(str(x))

print("const int wins_by_position[36][7] = {")
for x in range(0,36):
  sys.stdout.write("  {%s}" % ",".join(positions[x]))
  if x < 35:
    sys.stdout.write(",")
  sys.stdout.write("\n")
print("};")

print("const int positions_by_win[%d][6] = {" % i)
for x in range(0,i):
  sys.stdout.write("  {%s}" % ",".join(wins[x]))
  if x < 35:
    sys.stdout.write(",")
  sys.stdout.write("\n")
print("};")

print("const int16_t heuristic_value[1024] = {")
for x in range(0, 1024):
  if x > 0:
    sys.stdout.write(",")
    if x % 16 == 0:
      sys.stdout.write("\n")
  xes = 0
  oes = 0
  for p in range(0, 5):
    piece = (x >> (p * 2)) & 0x3
    if piece == 1:
      oes = oes + 1
    elif piece == 2:
      xes = xes + 1
  value = 0
  if xes > 0 and oes > 0:
    # unwinnable by order
    value = -1
  else:
    count_value = [0,1,2,4,6,1024]
    value = count_value[xes+oes]
  sys.stdout.write("%5d" % value)
print("\n};")