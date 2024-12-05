#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 20000

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

int main()
{
    FILE* file;
    //char filename[] = "test3_2.txt";
    char filename[] = "input3.txt";
    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char str[MAX];
    while(fgets(str, sizeof(str),file))
    {
        long result = calculation(str);
        printf("\nThe result is: %ld\n", result);
    }
    fclose(file);
    return EXIT_SUCCESS;
}