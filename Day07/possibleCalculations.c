#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

long long parseNumber (long long n, char c)
{
    if (n > LLONG_MAX / 10) {
        fprintf(stderr, "Overflow detected during parsing!\n");
        exit(EXIT_FAILURE);
    }
    return (long long )(n*10 + (c-'0'));
}

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
    }
    // if(i != spaces){
    //     printf("There is some error");
    //     return -1;
    // }
    // else{
    //     printf("%d\t\n%s\n", total, exp);
    //     for(int a = 0; a < spaces; a++)
    //     {
    //         printf("%d ", spPos[a]);
    //     }
    //     printf("\n");
    // }
    int pposCombin = (1 << spaces);
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
        //printf("%s\n",exp);
        if(possibleCalc(exp, total))
        {
            //printf("%s\n",exp);
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

int main()
{
    FILE* file;
    // char filename[] = "test7.txt";
    char filename[] = "input7.txt";    
    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    long long sum = 0;
    char buffer[512];
    int count = 1;
    while(fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        if(permutations(buffer))
        {
            long long n = 0;
            int i = 0;
            while(isdigit(buffer[i]))
            {
                n = parseNumber(n, buffer[i++]);
            }
            printf("\n%d\t%lld",count, n);
            sum += n;
        }
        count++;
    }
    fclose(file);
    printf("\nWith %d present, the sum is: %lld", count, sum);
}