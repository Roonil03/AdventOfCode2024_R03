#include <stdio.h>
#include <stdlib.h>

typedef struct s{
    long number;
    struct s* next;
    struct s* prev;
}Node;

void insertSorted(Node** head, long num)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->number = num;
    newNode->next = newNode->prev = NULL;
    if(*head == NULL)
    {
        *head = newNode;
    }
    else{
        Node* n = *head;
        while(n != NULL && n->number < num)
        {
            n = n->next;
        }
        if(n == *head)
        {
            newNode->next = n;
            n->prev = newNode;
            *head = newNode;
        }
        else if(n == NULL)
        {
           Node* tail = *head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
        }
        else{
            newNode->prev = n->prev;
            newNode->next = n;
            n->prev->next = newNode;
            n->prev = newNode;
        }
    }
    return;
}

int distanceForLocation(Node* left, Node* right)
{
    Node* t1 = left;
    Node* t2 = right;
    int sum = 0;
    while(t1!=NULL)
    {
        sum += abs(t1->number - t2->number);
        t1 = t1->next;
        t2 = t2->next;
    }
    return sum;
}

void printLists(Node* head)
{
    Node* n = head;
    while(n->next != NULL)
    {
        printf("%ld -> ",n->number);
        n = n->next;
    }
    printf("%ld", n->number);
}

void freeList(Node* head)
{
    while(head != NULL)
    {
        Node* n = head;
        head = head->next;
        free(n);
    }
}

int main()
{
    Node* left = NULL;
    Node* right = NULL;
    FILE *file;
    char filename[] = "test.txt";
    //char filename[] = "inputs.txt";
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    while(1){
        long leftNum, rightNum;
        fscanf(file, "%ld %ld", &leftNum, &rightNum);
        if(leftNum != -1)
        {
            insertSorted(&left, leftNum);
            insertSorted(&right, rightNum);
        }
        else{
            break;
        }
    }
    printLists(left);
    printf("\n");
    printLists(right);
    printf("\n%d", distanceForLocation(left, right));
    freeList(left);
    freeList(right);
    return EXIT_SUCCESS;
}