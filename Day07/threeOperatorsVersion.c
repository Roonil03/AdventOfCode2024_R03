#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

long long parseNumber(long long n, char c) {
    // if (n > LLONG_MAX / 10) {
    //     fprintf(stderr, "Overflow detected during parsing!\n");
    //     exit(EXIT_FAILURE);
    // }
    return n * 10 + (c - '0');
}

int possibleCalc(char *str, long long total) {
    long long n1 = 0, n2 = 0;
    int i = 0, len = strlen(str);
    while (isdigit(str[i])) {
        n1 = parseNumber(n1, str[i++]);
    }
    while (i < len) {
        char op = str[i++];
        n2 = 0;
        while (isdigit(str[i])) {
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
            if (n2 != 0 && n1 > LLONG_MAX / n2) {
                fprintf(stderr, "Multiplication overflow detected!\n");
                exit(EXIT_FAILURE);
            }
            n1 *= n2;
            break;
        case '|':
            {
                // long long temp = 0;
                // while(n2!=0)
                // {
                //     temp = temp*10 + n2%10;
                //     n2 /= 10;
                // }
                // while(temp!=0)
                // {
                //     char t = temp%10 +'0';
                //     n1 = parseNumber(n1, t);
                //     temp /= 10;
                // }
                // break;
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
        }
    }
    return (n1 == total);
}

int permutations(char *str) {
    long long total = 0;
    int i = 0;
    while (isdigit(str[i])) {
        total = parseNumber(total, str[i++]);
    }
    i++;
    i++;    
    char *exp = strdup(str + i);
    int len = strlen(exp);
    int spaces = 0;
    for (int j = 0; j < len; j++) {
        if (exp[j] == ' ')
            spaces++;
    }
    int *spPos = malloc(spaces * sizeof(int));
    int idx = 0;
    for (int j = 0; j < len; j++) {
        if (exp[j] == ' ')
            spPos[idx++] = j;
    }    
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

int main() {
    FILE *file;
    char filename[] = "input7.txt";    
    // char filename[] = "test7.txt";
    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    long long sum = 0;
    char buffer[512];
    int count = 1;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (permutations(buffer)) {
            long long n = 0;
            int i = 0;
            while (isdigit(buffer[i])) {
                n = parseNumber(n, buffer[i++]);
            }
            printf("\n%d\t%lld\n", count, n);
            sum += n;
        }
        count++;
    }
    fclose(file);
    printf("\nWith %d present, the sum is: %lld\n", count - 1, sum);
    return EXIT_SUCCESS;
}