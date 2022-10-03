# Nonogram Solver
Nonogram, also known as Paint by Numbers, Picross, Griddlers, Pic-a-Pix, and various other names, is a logic puzzle in which cells in a grid must be painted according to the given row clues and column clues. Players are requested to paint each grid cell into either “white” or “black”, such that the segments consisting of consecutive black cells in each row or column matches the corresponding row clue and column clue. The clues or numbers are a form of discrete tomography that measures the numbers of consecutive painted cells in any given row or column. For example, a clue of “4 8 3” would mean that there are sets of four, eight, and three filled (black) cells, in that order, with at least one blank (white) cell between successive sets. Moreover, solving nonogram puzzles is proved to be a NP-complete problem, which roughly means that no known algorithm can solve the puzzles eﬀiciently in general. See Figure 1 for an example.

If you are interested in this puzzle game, you can play the simple version (link) or download similar games to your smartphone.



Now given the height and width of the nonogram puzzle, denoted as N and M, and clues of each row and column, please put together a program to solve this puzzle and draw it.
## Input
The first line of the input contains two integers N and M, representing the number of rows and the columns of the nonogram puzzle.

Next N + M lines are the clues. The first N lines represent the clues of the N rows while the rest M lines represent the clues of the M columns. Each clue line starts with an integer n, representing the number of segments of consecutive black cells the row or column contains. The next n integers represent the numbers of consecutive black cells in the segments. For row clues, the numbers are marked from left to right, and, for column clues, the numbers are marked from top to bottom.

The puzzle size N × M is no more than 25, meaning that a brute-force algorithm with little optimization should be able to solve the puzzle within reasonable time. However, if you are interested in better solutions, try out other approaches (e.g., develop new algorithms or improve pruning mechanisms) and see if you can solve larger puzzles.
## Output
Output the puzzle in N lines; each of them should contain M cells. Print 'o' if the corresponding cell is black; otherwise print '_'. In some tasks, there might be multiple valid solutions. Please output any one of them. Also, we guarantee that there will be at least one valid solution for each task.

## Sample Cases
### Sample Input 1
4 4 \
2 1 1 \
2 1 1 \
2 1 1 \
1 4 \
2 1 2\
2 1 1 \
2 1 2\
2 1 1
### Sample Output 1
o_o_

_o_o

o_o_

oooo

### Sample Input 2
5 5  \
1 4 \
1 2 \
1 3 \
1 2 \
1 4 \
2 1 1\
2 3 1 \
3 1 1 1\
2 1 3 \
2 1 1
### Sample Output 2
_oooo

oo___

_ooo_

___oo

oooo_
