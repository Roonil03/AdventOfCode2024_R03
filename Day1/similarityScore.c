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

int similarityScoreMethod(Node* left, Node* right)
{
    int score = 0;
    Node* t1 = left;
    while (t1 != NULL) {
        long num = t1->number;
        int counterL = 0;
        int counterR = 0;
        Node* temp1 = t1;
        while (temp1 != NULL && temp1->number == num) {
            counterL++;
            temp1 = temp1->next;
        }
        Node* t2 = right;
        while (t2 != NULL) {
            if (t2->number == num) {
                counterR++;
            }
            t2 = t2->next;
        }
        score += num * counterL * counterR;
        t1 = temp1;
    }
    return score;
}

int main()
{
    Node* left = NULL;
    Node* right = NULL;
    FILE *file;
    //char filename[] = "test.txt";
    char filename[] = "inputs.txt";
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
    printf("\n%d\n",similarityScoreMethod(left,right));
    freeList(left);
    freeList(right);
    return EXIT_SUCCESS;
}