#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s{
    int n;
    struct s* next;
}Node;

Node* insertNode(int num)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->n = num;
    newNode->next = NULL;
    return newNode;
}

void insert(Node** root, char* str)
{
    Node* n = *root;
    int i = 0, len = strlen(str);
    while(i<len)
    {
        int num = 0;
        while(i<len && str[i] != ' ' && str[i] != '\n')
        {
            num = num*10 + (str[i] - '0');
            i++;
        }
        if(n == NULL)
        {
            *root = insertNode(num);
            n = *root;
        }
        else{
            n->next = insertNode(num);
            n = n->next;
        }
        i++;
    }
}

int isLevelSafe(Node* head) {
    Node* n = head;
    int asc = (n->n < n->next->n);
    int des = (n->n > n->next->n);
    while (n->next != NULL) {
        int diff = abs(n->next->n - n->n);
        if (diff < 1 || diff > 3 || (asc && n->n >= n->next->n) || (des && n->n <= n->next->n)) {
            return 0;
        }
        n = n->next;
    }
    return 1;
}

int levelPossible(Node* head) {
    if (isLevelSafe(head)) {
        return 1;
    }
    Node* prev = NULL;
    Node* current = head;
    while (current != NULL) {
        if (prev) {
            prev->next = current->next;
        } else {
            head = current->next;
        }

        int isSafe = isLevelSafe(head);
        if (prev) {
            prev->next = current;
        } else {
            head = current;
        }
        if (isSafe) {
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void printList(Node* head)
{
    Node* n = head;
    while(n -> next!=NULL)
    {
        printf("%d -> ", n->n);
        n = n->next;
    }
    printf("%d\n", n->n);
}

void freeList(Node* head)
{
    while(head!=NULL)
    {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}
int main()
{
    FILE* file;
    //char filename[] = "test2.txt";
    char filename[] = "input2.txt";

    char buffer[1000];
    file = fopen(filename,"r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file))
    {
        Node* head = NULL;
        insert(&head, buffer);
        printList(head);
        if(levelPossible(head))
        {
            count++;
        }
        freeList(head);
    }
    fclose(file);
    printf("\n\n%d", count);
}