# Day 15 Writeup:
## Languages Used: `Java`
## Part 1:
As soon as the question dropped, I began my work to craft the solution.

Initially my approach was to try to use stacks for each of movements and while there is a empty space or a box in front to move the entire thing... or at least I thought it would work properly like that. I didn't know where I messed up, but even after changing the position of the fish/robot, I was really confused as to why it kept duplicating.

Therefore, I started to brainstorm for another approach, until I decided to just test and see if swapping was properly working or not, and then swapping the entire list together.

This is what I went with:
```
for (char dir : commands.toCharArray()) {
    int d = findDir(dir); 
    int nRow = row, nCol = col;
    do {
        nRow += dRow[d];
        nCol += dCol[d];
    } while (board.get(nRow)[nCol] == 'O');    
    if (board.get(nRow)[nCol] == '#') continue; 
    do {
        swap(board, nRow, nCol, nRow - dRow[d], nCol - dCol[d]);
        nRow -= dRow[d];
        nCol -= dCol[d];
    } while (row != nRow || col != nCol);
    row += dRow[d];
    col += dCol[d];
}
```
where it moves until the edge...

Then there's the final calculation method, which is a very simple method:
```
int res = 0;
for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
        if (board.get(r)[c] == 'O') {
            res += 100 * r + c;
        }
    }
}
System.out.println(res);
```

## Part 2:
And then we come to part 2, which causes more issues than it's previous problem since now we have boxes that are twice their original length and walls have also become twice as thick as before.

I had to really modify the box swapping algorithm as well as the entire movement of boxes:
```
static boolean moveBoxes(int[] startBox) {
    boolean canMove = true;
    Queue<int[]> toCheck = new LinkedList<>();
    List<int[]> toMove = new ArrayList<>();
    toCheck.add(startBox);

    while (!toCheck.isEmpty()) {
        int[] box = toCheck.poll();
        if (toMove.contains(box)) continue;

        int nBX = box[0] + dR, nBY = box[1] + dC;
        if (hitsWall(nBX, nBY) || hitsWall(nBX, nBY + 1)) {
            canMove = false;
            break;
        }

        toMove.add(box);
        for (int[] other : boxes) {
            if (!toMove.contains(other) && nBX == other[0] && Math.abs(nBY - other[1]) <= 1) {
                toCheck.add(other);
            }
        }
    }

    if (canMove) {
        for (int[] box : toMove) {
            box[0] += dR;
            box[1] += dC;
        }
    }
    return canMove;
}
```

This returns if the boxes can even move, and then we just move the boxes, iteratively to complete the instructions given.

With that, the two challenges for the day are done.

With that, I conclude the `Day 15` of the `Advent of Code 2024`...<br>
Waiting for the next day!