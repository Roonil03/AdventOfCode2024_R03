#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define HASH 100

typedef struct{
    int arr[MAX];
    int hash[HASH];   
}HashSet;

typedef struct s{
    int n1,n2;
    struct s* next;
}Node;

Node* newOne(int n1, int n2)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->n1 = n1;
    newNode->n2 = n2;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, char* str)
{
    Node* n = *head;
    int n1 = 0, n2 = 0;
    int len = strlen(str);
    int i = 0;
        while(isdigit(str[i]))
        {
            n1 = n1*10 + (str[i] - '0');
            i++;
        }
        i++;
        while(i<len && isdigit(str[i]))
        {
            n2 = n2*10 + (str[i] - '0');
            i++;
        }
    if(n == NULL)
    {
        *head = newOne(n1,n2);
        return;
    }
    else{
        while(n->next != NULL)
        {
            n = n->next;
        }
        n->next = newOne(n1,n2);
    }
}

void printArray(int* arr, int size)
{
    for(int i = 0; i< size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int middle(int* arr, int size)
{
    printf("%d\n",arr[(size+1)/2 - 1]);
    return arr[(size+1)/2 - 1];
}

int checkOrder(Node* head, char* str)
{
    HashSet h1 = {0};
    memset(h1.hash, 0, sizeof(h1.hash));
    //Node* n;
    int i = 0,j=0, len = strlen(str);
    while(i<len)
    {
        int num = 0;
        while(i<len && isdigit(str[i]))
        {
            num = num*10 + (str[i++]-'0');
        }
        h1.arr[j++] = num;
        i++;
    }
    printArray(h1.arr, j);
    // i = 0;
    // while(i<j)
    // {
    //     n = head;
    //     int s = 0;
    //     while(s<j)
    //     {
    //         if(s == i){
    //             s++;
    //             continue;
    //         }
    //         while(n != NULL)
    //         {
    //             if(n->n1 == h1.arr[s] && n->n2 == h1.arr[i])
    //             {
    //                 if((h1.hash[h1.arr[s]]))
    //                 {
    //                     break;
    //                 }
    //                 else{
    //                     return 0;
    //                 }
    //             }
    //             else if(n->n1 == h1.arr[i] && n->n2 == h1.arr[s])
    //             {
    //                 h1.hash[h1.arr[i]] = 1;
    //                 break;
    //             }
    //             n = n->next;
    //         }
    //         if(n == NULL)
    //         {
    //             return 0;
    //         }
    //     }
    //     i++;
    // }
    for (int i = 0; i < j; i++) {
        for (int k = 0; k < j; k++) {
            if (i == k) 
                continue;
            Node* temp = head;
            while (temp) {
                if (temp->n1 == h1.arr[k] && temp->n2 == h1.arr[i]) {
                    if (h1.hash[h1.arr[k]]) 
                        break;
                    else 
                        return 0;
                }
                else if(temp->n1 == h1.arr[i] && temp->n2 == h1.arr[k])
                {
                    h1.hash[h1.arr[i]] = 1;
                }
                temp = temp->next;
            }
        }
        //h1.hash[h1.arr[i]] = 1;
    }
    return middle(h1.arr,j);
}

int main()
{
    FILE* file1; 
    FILE* file2;
    char filename1[] = "input5.txt";
    char filename2[] = "input5_list.txt";
    // char filename1[] = "test5.txt";
    // char filename2[] = "test5_list.txt";
    file1 = fopen(filename1,"r");
    file2 = fopen(filename2, "r");
    if(!file1 || !file2)
    {
        perror("There was an error");
        exit(0);
    }
    char line[128];
    Node* head = NULL;
    while(fgets(line, sizeof(line), file1))
    {
        insertNode(&head, line);
    }
    int sum = 0;
    while(fgets(line, sizeof(line), file2))
    {
        sum += checkOrder(head, line);
    }
    printf("\n%d", sum);
    fclose(file1);
    fclose(file2);
}