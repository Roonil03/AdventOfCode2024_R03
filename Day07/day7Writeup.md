# Day 7 Writeup:
## Languages Used: `C`
## Part 1:
This was a full permutation and combination type problem. It would all depend on the various permutations of the operators that are possible, making the entire thing have `no of operators`^`no of spaces`.

There were two operators that were present in this part: `+` and `*`...

I opted to use two different methods, one that deals with the calculation and the other that deals with the ordering of the various operators:
```
int possibleCalc(char* str, long long total)
{
    long long n1 = 0, n2=0;
    int i = 0;
    int len = strlen(str);
    while(isdigit(str[i]))
    {
         n1 = parseNumber(n1,str[i++]);
    }
    while(i< len)
    {
        char op = str[i++];
        n2 = 0;
        while(isdigit(str[i]))
        {
            n2 = parseNumber(n2, str[i++]);
        }
        switch(op)
        {
            case '+':
            if (n1 > LLONG_MAX - n2) {
                fprintf(stderr, "Addition overflow detected!\n");
                exit(EXIT_FAILURE);
            }
            n1 += n2;
            break;
            case '*':
            if (n2 != 0 && n1 > LLONG_MAX / n2)
            {
                fprintf(stderr, "Addition overflow detected!\n");
                exit(EXIT_FAILURE);
            }
            n1 *= n2;
            break;
        }
    }
    return (n1 == total);
}
```

I had to set up the error statements to make sure that I didn't get errors while dealing with the integers. I also converted everything from `int` to `long long` to prevent any overflow errors from taking place.

<i>All because when I originally did it, I kept getting random answers from the output, and I realized it was probably because there is some sort of overflow that is taking place.</i> And that's why I converted it all.

Then I used this method to deal with the permutations of the entire equation:
```
int permutations(char* str)
{
    long long total = 0;
    int i = 0;
    while(isdigit(str[i]))
    {
        total = parseNumber(total, str[i++]);
    }
    i++;
    int caclStr = strlen(str) - i;
    int spaces = 0;
    char* exp = (char*)malloc(sizeof(char)* caclStr);
    exp[caclStr-1] = '\0';
    int j = 0;
    i++;
    while(str[i] != '\0')
    {
        if(str[i] == ' ')
            spaces++;
        exp[j++] = str[i++];
    }
    int* spPos = (int*)malloc(sizeof(int)*spaces);
    j = 0;
    i = 0;
    while(j<caclStr){
        if(exp[j++] == ' ')
        {
            spPos[i++] = j-1;
        }
    }int pposCombin = (1 << spaces);
    int* order = (int*)malloc(sizeof(int)*spaces);
    memset(order, 0, sizeof(int) * spaces);
    char ops[] = {'+','*'};
    int count = 0;
    while(count < pposCombin)
    {
        for(int a = 0; a < spaces; a++)
        {
            exp[spPos[a]] = ops[(count >> a) & 1];
        }
        if(possibleCalc(exp, total))
        {
            free(exp);
            free(spPos);
            free(order);
            return 1;
        }
        count++;
    }    
    free(exp);
    free(spPos);
    free(order);
    return 0;
}
```

Originally I tried with the manipulation of order's array to store which all operators should change and which should not, but then that wasn't working,so I opted to switch to the bitwise version of this, since we are still only dealing with two operators.<br>
This made it work very very efficiently and quite well. Having to deal with only 2 made it also faster to operate with, since it's closest to binary.

## Part 2:
This is where the real trouble began. We went from just 2 operators, to now 3... Making it that the total combinations possible becomes `3^ no of spaces`.

That was certainly troubling, as I had to create a new function that dealt with the added concatenation function as well as deal with how I am going to be ordering the combinations.

After tinkering with it for a while, I decided that I am going to be using the temporary int to deal with the ordering that will correctly place it in the position by finding out what position it is at, find the remainder when divided by 3 and see if it needs to be going to which index, and then divide the temp by 3. It restarts in the next iteration by storing the value of the count it is on.

Thus, these were the changes that I made:
```
        case '|':
            {
                long long multiplier = 1;
                long long temp_n2 = n2;
                while (temp_n2 > 0) {
                    multiplier *= 10;
                    temp_n2 /= 10;
                }
                if (n1 > LLONG_MAX / multiplier) {
                    fprintf(stderr, "Concatenation overflow detected!\n");
                    exit(EXIT_FAILURE);
                }
                n1 = n1 * multiplier + n2;
                break;
            }
```
```
int pposCombin = pow(3, spaces);
    char ops[] = {'+', '*', '|'};    
    for (int count = 0; count < pposCombin; count++) {
        int temp = count;
        for (int s = 0; s < spaces; s++) {
            exp[spPos[s]] = ops[temp % 3];
            temp /= 3;
        }
        if (possibleCalc(exp, total)) {
            printf("%s", exp);
            free(exp);
            free(spPos);
            return 1;
        }
    }    
    free(exp);
    free(spPos);
    return 0;
}
```

This certainly took some time to figure out, but it was actually really fun, and I can use this program for some other fun combinations, as I generalize this to account for more operators and more functions.

Thus, with this,I completed the two problems of the day and I can conclude `Day 7` of the `Advent of Cyber 2024`...<br>
Awaiting the next challenge.