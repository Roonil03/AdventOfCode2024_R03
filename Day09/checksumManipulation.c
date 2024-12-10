#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void swap(char* a, char* b, int* x, int* y)
{
    char temp = *a;
    *a = *b;
    *b = temp;
    int t = *x;
    *x = *y;
    *y = t;
}

void printArray(char* ar)
{
    int len = strlen(ar);
    for(int i = 0; i< len; i++)
    {
        printf("%c ", ar[i]);
    }
    printf("\n");
}

void print(int* n, int size)
{
    for(int i = 0; i< size; i++)
    {
        printf("%d ", n[i]);
    }
    printf("\n");
}

void changingArray(char* str, int* nums)
{
    int start = 0, end = strlen(str)-1;
    int len = end+1;
    int i = 0;
    while(start<end)
    {
        while(start < end && str[start]!='.')
        {
            start++;
        }
        if(start == len)
            break;
        while(end > start && str[end] == '.')
        {
            end--;
        }
        if(end == -1)
            break;
        swap(&str[start],&str[end], &nums[start],&nums[end]);
        printf("\n%d\t%d\n",start,end);
        // printArray(str);
        // print(nums, len);
    }
    return;
}

long long checksum(char* str, int* nums)
{
    long long sum = 0;
    int i = 0;
    while(str[i] != '.')
    {
        sum += ((long long)i * nums[i]);
        i++;
        printf("%lld\n",sum);
    }
    return sum;
}

char* message(char* str)
{
    int len = strlen(str);
    int num = 0;
    int newLen = 0;
    for(int i = 0; i < len; i++)
    {
        newLen += (str[i] - '0');
    }
    // printArray(str);
    char* mess = (char*)malloc(sizeof(char)*(newLen+1));
    mess[newLen] = '\0';
    int a = 0;
    for(int i = 0; i< len; i++)
    {
        if(i%2 == 0)
        {
            int count = 0;
            while(a<newLen && count < str[i]-'0')
            {
                mess[a++] = i%4?'0':'2';
                count++;
            }
        }
        else{
            int count = 0;
            while(a < newLen && count < str[i]-'0')
            {
                mess[a++] = '.';
                count++;
            }
        }
    }
    // printArray(mess);
    return mess;
}

int* applyNums(char* str)
{
    int len = strlen(str);
    int* nums = (int*)calloc(len,sizeof(int));
    int count = 0; 
    int i = 0;
    char current = '2';
    while(i < len)
    {
        if(isdigit(str[i]))
        {
            while(isdigit(str[i]) && str[i] == current)
            {
                nums[i++] = count;
            }
            count++;
            current = !(count %2) ?'2':'0';
            i--;
        }
        i++;
    }
    // print(nums,len);
    return nums;
}

int main()
{
    // char filename[] = "input9.txt";
    char filename[] = "test9.txt";
    FILE* file = fopen(filename, "r");
    if(!file)
    {
        printf("An error has occured");
        exit(0);
    }
    // char* buffer = (char*)calloc(INT_MAX-1, sizeof(char));
    char buffer[40000];
    char* msg;
    int* nums;
    while(fgets(buffer,sizeof(buffer),file))
    {
        buffer[strcspn(buffer,"\n")] = '\0';
        msg = message(buffer);
        nums = applyNums(msg);
        changingArray(msg,nums);
        long long cs = checksum(msg,nums);
        printf("%d\n", strlen(msg));
        printf("Checksum: %lld", cs);
    }    
    free(msg);
    free(nums);
    fclose(file);
    return EXIT_SUCCESS;
}