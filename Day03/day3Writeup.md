# Day 3 Writeup
## Languages Used: `C`
## Part 1:
This problem required simple string matching and similar to the previous problem, it required us to be converting the string input into numbers.<br>
In the first instance of the problem, I attempted to brute force it and find and see if it was possible to just complete the entire thing just using <i>if-else</i> nested.

That in turn allowed me to make this abomination:
```
long calculation(char* str)
{
    long res = 0;
    int len = strlen(str);
    int i = 0;
    while(i<len)
    {
        if(i<len && str[i] == 'm')
        {
            if(++i<len && str[i] == 'u')
            {
                if(++i < len && str[i] == 'l')
                {
                    if(++i < len && str[i] == '(')
                    {
                        int n1 = 0, n2 = 0;
                        while(++i<len && isdigit(str[i]))
                        {
                            n1 = n1*10 + (str[i] - '0');
                        }
                        if(str[i] == ',')
                        {
                            while(++i<len && isdigit(str[i]))
                            {
                                n2 = n2*10 + (str[i] - '0');
                            }
                            if(str[i] == ')')
                            {
                                int product = n1*n2;
                                printf("%d x %d = %d\t", n1,n2,product);
                                res += product;
                                printf("%ld\n", res);
                            }
                        }
                    }
                }
            }
        }
        i++;
    }
    return res;
}
```
I decided to store the sum in a long, as I realized that there were much bigger, and I didn't want to exceed the integer threshold, so I stuck with long for the storing of the result.

This made the code efficient, but it was a nightmare to read the entire thing as a developer, so I opted to change it for the second part of the problem.

## Part 2:
As previously stated, I chose to redo the checking function by making another function instead of using the nested <i>if-else</i> to check and see if there was a `do()` or a `don't()` condition.<br>
I ended up making a common substring checker function to help me implement this because it was not properly working with the `strncmp()` function that is inbuilt.

This ended up being the code snippet that I used for the code:
```
int match(char* s1, char* s2, int ind)
{
    for(int i = 0; i<ind; i++)
    {
        if(s1[i] != s2[i])
            return 0;
    }
    return 1;
}

long calculation(char* str)
{
    long res = 0;
    int len = strlen(str);
    int i = 0;
    int enabled = 1;
    while(i<len)
    {
        if((i+3)<len && match(&str[i],"mul(",4))
        {
            i += 3;
            int n1 = 0, n2 = 0;
            while(++i<len && isdigit(str[i]))
            {
                n1 = n1*10 + (str[i] - '0');
            }
            if(str[i] == ',')
            {
                while(++i<len && isdigit(str[i]))
                {
                    n2 = n2*10 + (str[i] - '0');
                }
                if(str[i] == ')' && enabled)
                {
                    int product = n1*n2;
                    printf("%d x %d = %d\t", n1,n2,product);
                    res += product;
                    printf("%d\n", res);
                }
            }
        }
        if((i+3)<len && match(&str[i],"do()",4))
        {
            enabled = 1;
            i += 3;
        }
        if((i+6)<len && match(&str[i],"don't()",7))
        {
            enabled = 0;
             i += 6;
        }
        i++;
    }
    return res;
}
```
This ended up making the code far more easier to read for a normal person, thus increasing it's readability.

With this, I got the two stars required for today!<br>

And I conclude `Day 3` of the `Advent of Code 2024`...<br>
Onto the next challenge!