#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 20000

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

int main()
{
    FILE* file;
    //char filename[] = "test3_1.txt";
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