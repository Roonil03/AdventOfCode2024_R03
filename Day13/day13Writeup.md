# Day 13 Writeup:
## Languages Used: `Java`
## Part 1:
It was evident that there were two ways to approach this problem. Either to use mathematics and do it via linear algebra or to just brute force it, since we can only do 100 button presses for the output.

Since I was lazy, I didn't feel like trying to form the equation, since I would have to write a complicated script just to get the numbers in a proper format for me to manipulate.

Therefore, this was the brute force method that I took up:
```
    static long totalCost(int Ax, int Ay, int Bx, int By, int posX, int posY)
    {
        long minCost = Long.MAX_VALUE;
        for(int i = 0; i<= 1000; i++)
        {
            for(int j = 0; j<= 1000; j++)
            {
                if(i*Ax + Bx*j == posX && j*By + Ay*i == posY)
                {
                    System.out.println(i + " " + j + ": " + posX + " " + posY);
                    if(minCost > i*3 + j)
                    {
                        minCost = i*3 + j;
                    }
                }
            }
        }
        return minCost == Long.MAX_VALUE?0:minCost;
    }
```

With this, I would always iterate `10000` times to check and see if the correct order was present. If not, just return the 0.

## Part 2:
This part added a delta <i>(that being `10000000000000`)</i> as well as removing the 100 limit. This made it that I had to actually think of an equation to solve this, otherwise it would not work, and the loop would remain infinite.

I sat down with a pen and paper and then formed the following equations:
```
a = X*by - Y*bx    /   ax*by -  ay*bx
b = Y*ax - X*ay    /   ax*by -  ay*bx
```
And thus, I converted the method to do the following:
```
    static long totalCost(int Ax, int Ay, int Bx, int By, long posX, long posY)
    {
        long minCost = 0;
        double a = ((double)posX* By - (double)posY * Bx)/ ((double)Ax*By - (double)Ay*Bx);
        double b = ((double)posY*Ax - (double)posX*Ay) / ((double)Ax*By - (double)Ay*Bx);
        if(a == (long)a && b == (long)b)
            minCost += (long)(3*a + b);
        return minCost;
    }
```

Thus with that problem out of the way, I solved another two challenges for the day.
Thus, with that I concluded the `Day 13` of the `Advent of Code 2024`...<br>
Waiting for the next day!