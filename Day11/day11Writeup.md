# Day 11 Writeup:
## Languages Used: `Java` and `C`
## Part 1:
After reading the problem once, I initially presumed that it would be a good idea to attempt this in Java, since I can easily use the String functions to check and see if the length is even or not, and thus, began the crafting process to make a program using `Iterators()`, `ArrayLists()` and String functions.

There was initally not much restriction, so I just made the method transpose the list into a new list:
```
    static ArrayList<Long> modifyingList(ArrayList<Long> list)
    {
        ArrayList<Long> temp = new ArrayList<>();
        Iterator<Long> trav = list.iterator();
        while(trav.hasNext())
        {
            long n = trav.next();
            if(n == 0)
            {
                temp.add(1L);
            }
            else if((Long.toString(n)).length()% 2 == 0)
            {
                int len = Long.toString(n).length();
                int pow = (int)Math.pow(10, len/2);
                long n1 = n/pow;
                long n2 = n%pow;
                temp.add(n1);
                temp.add(n2);
            }
            else{
                temp.add(n * 2024);
            }
        }
        return temp;
    }
```

With this, I easily got the answer, since the number of blinks were quite less.

## Part 2:
and then came part 2...

OKay, I clearly underestimated how much time it would take to brute force this entire problem...
Because it ended up causing me issues like this:
```
Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
        at java.base/java.util.Arrays.copyOf(Arrays.java:3512)
        at java.base/java.util.Arrays.copyOf(Arrays.java:3481)
        at java.base/java.util.ArrayList.grow(ArrayList.java:238)
        at java.base/java.util.ArrayList.grow(ArrayList.java:245)
        at java.base/java.util.ArrayList.add(ArrayList.java:484)
        at java.base/java.util.ArrayList.add(ArrayList.java:497)
        at moreBlinking.modifyingList(moreBlinking.java:64)
        at moreBlinking.main(moreBlinking.java:39)
```

and I just thought that increasing the JVM's heap size would help in solving the problem...<br>
However, funny things happen:
```
java -Xmx7G moreBlinking
Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
        at java.base/java.util.Arrays.copyOf(Arrays.java:3512)
        at java.base/java.util.Arrays.copyOf(Arrays.java:3481)
        at java.base/java.util.ArrayList.grow(ArrayList.java:238)
        at java.base/java.util.ArrayList.grow(ArrayList.java:245)
        at java.base/java.util.ArrayList.add(ArrayList.java:484)
        at java.base/java.util.ArrayList.add(ArrayList.java:497)
        at moreBlinking.modifyingList(moreBlinking.java:65)
        at moreBlinking.main(moreBlinking.java:39)
```
```
java -Xmx8G moreBlinking
Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
        at java.base/java.util.Arrays.copyOf(Arrays.java:3512)
        at java.base/java.util.Arrays.copyOf(Arrays.java:3481)
        at java.base/java.util.ArrayList.grow(ArrayList.java:238)
        at java.base/java.util.ArrayList.grow(ArrayList.java:245)
        at java.base/java.util.ArrayList.add(ArrayList.java:484)
        at java.base/java.util.ArrayList.add(ArrayList.java:497)
        at moreBlinking.modifyingList(moreBlinking.java:64)
        at moreBlinking.main(moreBlinking.java:39)
```
```
java -Xmx9G moreBlinking
Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
        at java.base/java.util.Arrays.copyOf(Arrays.java:3512)
        at java.base/java.util.Arrays.copyOf(Arrays.java:3481)
        at java.base/java.util.ArrayList.grow(ArrayList.java:238)
        at java.base/java.util.ArrayList.grow(ArrayList.java:245)
        at java.base/java.util.ArrayList.add(ArrayList.java:484)
        at java.base/java.util.ArrayList.add(ArrayList.java:497)
        at moreBlinking.modifyingList(moreBlinking.java:64)
        at moreBlinking.main(moreBlinking.java:39)
```
```
java -Xmx10G moreBlinking
Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
        at java.base/java.util.Arrays.copyOf(Arrays.java:3512)
        at java.base/java.util.Arrays.copyOf(Arrays.java:3481)
        at java.base/java.util.ArrayList.grow(ArrayList.java:238)
        at java.base/java.util.ArrayList.grow(ArrayList.java:245)
        at java.base/java.util.ArrayList.add(ArrayList.java:484)
        at java.base/java.util.ArrayList.add(ArrayList.java:497)
        at moreBlinking.modifyingList(moreBlinking.java:65)
        at moreBlinking.main(moreBlinking.java:39)
```

because apparently even 10 gigabytes of heap space was not enough to run this program. That really hurt a lot.

Thus, began my process to convert the entire program into C to try and see if that would work.

The brute force approach that was originally using in first part was clearly not working even with `C`....<br>
So, I opted to check out something that was different.

I finally went to the subreddit to help guide me into the right direction, and the first <a href="https://www.reddit.com/r/adventofcode/comments/1hbmu6q/2024_day_11_we_knew_it_would_happen/">post over there</a> was talking about this exact thing.<br>
![s18092412112024](https://a.okmd.dev/md/675987ffdfa33.png)

Luckily some of the comments were very nice in providing directions from which I could easily find the solution.

One of these approaches was to store it in a regular `long long` map and solve the program like that.
However, I don't know where I went wrong with the code, because I ended up getting less attempts solved with that method than I did with the LinekdList brute force attempt.

I was actually very confused on where I should take this program, until I went further down and found <a href="https://www.reddit.com/r/adventofcode/comments/1hbmu6q/comment/m1ho8t1/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button">this comment</a>:<br>
<i>"Is memoized recursion a bruteforce?

Idk. But it ran in 40 ms, so who cares."</i>

And that put me into another direction to think about.
Then, I started looking into websites and articles that would guide me into this approach to solve the problem:
- <a href="https://dev.to/ionabrabender/memoization-and-recursion-228f">Memoization and Recursion</a>
- <a href="https://www.geeksforgeeks.org/memoization-1d-2d-and-3d/">Memoization (1D, 2D and 3D)</a>
- <a href="https://medium.com/swlh/understanding-recursion-memoization-and-dynamic-programming-3-sides-of-the-same-coin-8c1f57ee5604">Understanding recursion, memoization, and dynamic programming: 3 sides of the same coin</a>
- <a href="https://stackoverflow.com/questions/12133754/whats-the-difference-between-recursion-memoization-dynamic-programming">StackOverflow Doubt someone had</a>
- <a href="https://www.geeksforgeeks.org/what-is-memoization-a-complete-tutorial/">Memoization</a>
- <a href="https://dzone.com/articles/memoization-make-recursive-algorithms-efficient">Memoization: Make Recursive Algorithms Efficient</a>
- <a href="https://medium.com/@nagarjun_nagesh/memoization-with-lambda-functions-in-java-4c7e4f780522#:~:text=4.1.-,Recursive%20Algorithms,calculations%20can%20benefit%20from%20memoization.&text=In%20this%20example%2C%20we%20use,the%20factorial%20of%20a%20number.">Memoization with Lambda Functions in Java</a>

With this, it was time to get to work and learn to do it in C:<br>

- I made the structure that would be used in the recursion to maintain the numbers and the blinks that are ongoing:
    ```
    typedef struct {
        long long num;
        int blinks;
        long long res;
    } Memo;
    ```

- Then it was time to create the part where I have to add the memo to the table:
    ```
    void addMemo(long long num, int blinks, long long res) {
        if (memoSize == memCap)
        {
            memCap *= 2;
            mt = (Memo *)realloc(mt, sizeof(Memo) * memCap);
        }
        mt[memoSize].num = num;
        mt[memoSize].blinks = blinks;
        mt[memoSize].res = res;
        memoSize++;
    }
    ```

- Then there was a method to get the result back:
    ```
    long long getMemo(long long num, int blinks) {
        for (int i = 0; i < memoSize; i++)
        {
            if (mt[i].num == num && mt[i].blinks == blinks)
            {
                return mt[i].res;
            }
        }
        return -1;
    }
    ```

- And then finally there was the method to count the number of stones that are present after the set number of blinks that was mainly handling the recursion of this problem:
    ```
    long long countStones(long long num, int blinks) {
        if (blinks == 0)
        {
            return 1;
        }
        long long memoResult = getMemo(num, blinks);
        if (memoResult != -1)
        {
            return memoResult;
        }
        long long res = 0;
        if (num == 0)
        {
            res = countStones(1, blinks - 1);
        }
        else if ((int)log10(num) % 2 == 1) 
        {
            int len = (int)log10(num) + 1;
            long long power = pow(10, len / 2);
            long long left = num / power;
            long long right = num % power;
            res = countStones(left, blinks - 1) + countStones(right, blinks - 1);
        }
        else {
            res = countStones(num * 2024, blinks - 1);
        }
        addMemo(num, blinks, res);
        return res;
    }
    ```

With these methods, I was able to do the memoization recurssion to get me my output in about `~22500` ms

And with that, this was the first day that managed to achieve two things:
1. I had to finally use two different languages to complete this day's problem
2. I had to reach out to the subreddit to get some guidance on how to solve this problem.

And thus, with these two challenges that were done for the day, I conclude the `Day 11` of the `Advent of Code 2024`...<br>
Onto the next challenge.