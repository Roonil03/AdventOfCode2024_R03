# Day 6 Writeup:
## Languages Used: `Java`
## Part 1:
This was a barrier problem that seemed quite simple, just give certain positions, and allow rotation to take place.<br>
At the same time, keep in mind that as soon as the character exists, the method should return count.

Thus, this was the code snippet that I created:
```
    static int distinctPositions(char[][]mat)
    {
        int m = mat.length;
        int n = mat[0].length;
        boolean touched[][] = new boolean[m][n];
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        int count = 0;
        int posX = 0, posY = 0;
        for(int i = 0; i< m; i++){
            for(int j = 0; j< n; j++)
            {
                if(mat[i][j] == '^')
                {
                    posY = i;
                    posX = j;
                    break;
                }
            }
        }
        touched[posY][posX] = true;
        count++;
        int ind = 0;
        while(validCoords(posX, posY, m, n))
        {
            if(!validCoords(posY+dy[ind], posX+dx[ind], m,n))
            {
                return count;
            }
            else if(mat[posY+dy[ind]][posX+dx[ind]] == '#')
            {
                ind = (ind+1)%4;
            }
            else{
                mat[posY][posX] = '.';
                posX += dx[ind];
                posY += dy[ind];
                mat[posY][posX] = '^';
                if(!(touched[posY][posX]))
                {
                    count++;
                    touched[posY][posX] = true;
                }
            }
        }
        return -1;
    }
```
This didn't take me long to give me the answer for both the test case as well as the given challenge input.

## Part 2:
This was where the fun really began. We couldn't really brute force it, since bruteforcing it would have taken me close to 3~4 hours to give me the output for the challenge input.<br>
Therefore, this was what I opted for, I changed the boolean matrix for a int matrix to check how many times the character had visited that certain position. 

Then to make sure that the character is actually looping in that position, I changed the condition to return only if the tile has a large number <i> (such as 5000) </i>and then only returns true.

Thus with this, I was able to find out how many positions putting the extra obstable would cause me to get:
```
    static boolean distinctPositions(char[][]mat)
    {
        int m = mat.length;
        int n = mat[0].length;
        int times[][] = new int[m][n];
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        int posX = 0, posY = 0;
        for(int i = 0; i< m; i++){
            for(int j = 0; j< n; j++)
            {
                if(mat[i][j] == '^')
                {
                    posY = i;
                    posX = j;
                    break;
                }
            }
        }
        times[posY][posX]++;
        int ind = 0;
        while(times[posX][posY] <= 5551)
        {;
            if(!validCoords(posY+dy[ind], posX+dx[ind], m,n))
            {
                return false;
            }
            else if(mat[posY+dy[ind]][posX+dx[ind]] == '#' || mat[posY + dy[ind]][posX+dx[ind]] == 'O')
            {
                ind = (ind+1)%4;
                times[posX][posY]++;
            }
            else{
                posX += dx[ind];
                posY += dy[ind];
                times[posY][posX]++;
            }
        }
        return true;
    }
```
And to store the number of times the obstacle positions will be kept, I made this seperate method to maintain that:
```
    static int loopsFormed(char[][] mat)
    {
        int count = 0;
        int m = mat.length;
        int n = mat[0].length;
        for(int i = 0; i< m; i++)
        {
            for(int j = 0; j< n; j++)
            {
                if(mat[i][j] == '.')
                {
                    mat[i][j] = 'O';
                    if(distinctPositions(mat))
                    {
                        count++;
                    }
                    mat[i][j] = '.';
                }
            }
        }
        return count;
    }
```

Key points that I noted was that arrays are still objects since we are creating an instance from the class, therefore it was important that I was maintaining the same input matrix and not changing that.

Well, that was certainly a really fun challenge!

Another two problems done, and I completed the `Day 6` of the `Advent of Code 2024`...<br>
Onto the next challenge!
