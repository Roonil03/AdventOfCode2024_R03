# Day 8 Writeup:
## Languages Used: `Java`
## Part 1:
This problem actually held me for a while, thinking about how to solve it.<br>
I landed with two solutions to solve this problem.
1. To convert the entire thing into cartesian and solve it using that logic, practically brute forcing the entire solution
2.  Use the frequency of characters to determine the position, and the frequency of how many times it has been visited, basically optimzing this sort of brute force attempt.

I spent a lot of time converting the entire graph into a cartesian graph that I could use for line manipulation, but that took way too long, so I ended up focussing on the second part.

Which is why I ended up with this:
```
    static void antiNodes(int[][] map, int[][][] freqs) {
        for (int i = 0; i < 62; i++) {
            if (freqs[i][0][0] != -1) {
                for (int j = 0; freqs[i][j][0] != -1; j++) {
                    for (int k = 0; freqs[i][k][0] != -1; k++) {
                        if (j == k) continue;
                        int dx = freqs[i][j][1] * 2 - freqs[i][k][1];
                        int dy = freqs[i][j][0] * 2 - freqs[i][k][0];
                        if (dx >= 0 && dx < map[0].length && dy >= 0 && dy < map.length) {
                            map[dy][dx]++;
                        }
                    }
                }
            }
        }
        int count = 0;
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[0].length; j++) {
                if (map[i][j] > 0) {
                    count++;
                }
            }
        }
        System.out.println("Part 1: " + count);
    }
```
Here, instead of taking the absolute distance, it is matching with the relative distance to find the distance from one another to find the final answer.

Thus, this made the entire approach much more direct compared to the first method, and I quickly managed to get my answer.

## Part 2:
They somehow managed to make an already irritating problem even more irritating with this statement.<br>
I had to basically change the frequency to make sure that we have to account for the duplication factor as well.

I could have stuck with the Cartesian method, but that would have ended up taking even more long, as I have arleady spent a lot of time on this question, and therefore I stuck to making the program like this:
```
    static void uselessT(int[][] map, int[][][] freqs) {
        for (int i = 0; i < 62; i++) {
            if (freqs[i][0][0] != -1) {
                for (int j = 0; freqs[i][j][0] != -1; j++) {
                    for (int k = 0; freqs[i][k][0] != -1; k++) {
                        if (j == k) continue;
                        int X = freqs[i][j][1];
                        int Y = freqs[i][j][0];
                        int deltaX = X - freqs[i][k][1];
                        int deltaY = Y - freqs[i][k][0];
                        while (X >= 0 && X < map[0].length && Y >= 0 && Y < map.length) {
                            map[Y][X]++;
                            X += deltaX;
                            Y += deltaY;
                        }
                    }
                }
            }
        }
        int count = 0;
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[0].length; j++) {
                if (map[i][j] > 0) {
                    count++;
                }
            }
        }
        System.out.println("Part 2: " + count);
    }
```
Since this worked on updating multiple positions, it updated the entire line at the different `X` or `Y` lines. Instead of marking just a single point, it marks multiple points in a straight line between the starting position and the new position generated by the shift. 

This took care of the multiple antinodes issues and thus, allowed me to get the answer.

This program also helped me understand the importance of having a different reader method, since it makes it easier to deal with reading, I can just copy paste the entire method somewhere, or create a reader class that can just help me take the file reading inputs whenever required.

This was also the first time I dealt with 3D arrays, as I needed to store the positions as well as the frequency. I could have done it with a boolean matrix as well, but with this, I can easily attach a point with a singular position, thus decreasing the memory space that it takes.