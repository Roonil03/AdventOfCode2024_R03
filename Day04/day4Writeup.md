# Day 4 Writeup:
## Languages Used: `Java`
## Part 1:
As evident as the sun is hot, we need to apply a word search algorithm for this puzzle to be solved.<br>
Unlike previous attempts, where I could just figure it out along the way, i actually didn't know if there was an efficient way to solve the word search, I went to google to search up some algorithms which might work.

With that, the first algorithm that I checked out was from <a href="https://www.geeksforgeeks.org/search-a-word-in-a-2d-grid-of-characters/">GeeksForGeeks</a>. After that I went to <a href="https://www.javatpoint.com/word-search-problem-in-java">JavaTPoint</a> to find something out.

This initial reading was definitely required, as I was switching my languages from `C` to `Java` for this problem.

Therefore, I used a slightly modified version of the iterative appraoch that was given on the site to account for the fact that `X` can be a starting position for multiple different `"XMAS"`-es. 

These were the methods that I decided to use:
```
    static boolean findWord(char[][] grid, int x, int y, int dirX, int dirY) {
        int m = grid.length;
        int n = grid[0].length;
        for (int i = 0; i < word.length(); i++) {
            if (!validCoord(x, y, m, n) || grid[x][y] != word.charAt(i)) {
                return false;
            }
            x += dirX;
            y += dirY;
        }
        return true;
    }
```
```
    static int searchWord(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int count = 0;
        int[] x = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int[] y = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 8; k++) {
                    if (findWord(grid, i, j, x[k], y[k])) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
```

This type of word searching algorithms are definitely long, especially when considering that it can be a starting position for multiple different `"XMAS"`-es. Thus making the time complexity O(4 <i>(length of the word <b>"XMAS"</b>)</i> * 8 <i>(number of directions to check)</i> * m * n).

## Part 2:
Initially I thought that this was going to be a very irritating problem to solve, but after rechecking the problem again, I realized that all I needed to do was checking the center condition and then I can check for the 6 possible combinations <i>(4C2)</i> for where `'M'` and `'S'` can be present to make sure that the program works properly.

Therefore, the first thing I did is change the method to check for coordinates are in the grid to make it that if '`A`''s position is one padding within the grid or not.
```
    static boolean valid(int x, int y, int m, int n) {
        return (x >= 1 && x < m-1 && y >= 1 && y < n-1);
    }
```
Then I had directional conditions to check and see if they were present in the grid or not, making sure that I get my answer...
```
    static int searchWord(char[][] grid)
    {
        int count = 0;
        int m = grid.length;
        int n = grid[0].length;
        for(int i = 0; i<m; i++)
        {
            for(int j = 0; j<n;j++)
            {
                if(grid[i][j] == 'A' && isTwitter(grid,i,j))
                {
                    count++;
                }
            }
        }
        return count;
    }
```
```
    static boolean isTwitter(char[][] grid, int x, int y) {
        int m = grid.length;
        int n = grid[0].length;
        if (valid(x, y, m, n)) {
            return (checkDirection(grid, x, y, -1, -1) && checkDirection(grid, x, y, -1, 1)|| 
                    checkDirection(grid, x, y, -1, 1) && checkDirection(grid, x, y, 1, -1)||
                    checkDirection(grid, x, y, 1, -1) && checkDirection(grid, x, y, 1, 1)||
                    checkDirection(grid, x, y, 1, 1) && checkDirection(grid, x, y, -1, -1) ||
                    checkDirection(grid, x, y, -1, -1) && checkDirection(grid, x, y, 1, -1) ||
                    checkDirection(grid, x, y, -1, 1) && checkDirection(grid, x, y, 1, 1)
                    );
        return false;
    }

    static boolean checkDirection(char[][] grid, int x, int y, int dirX, int dirY) {
        if (grid[x + dirX][y + dirY] == 'M' && grid[x][y] == 'A' && grid[x - dirX][y - dirY] == 'S') {
            return true;
        }
        return false;
    }
```

That took some time to clear and get the final answer, but it was a fun challenge to do.

Thus, with these two problems solved, I have completed the challenges for the day and therefore, conclude `Day 4` of the `Advent of Code 2024`...<br>
Looking forward to the next challenge!