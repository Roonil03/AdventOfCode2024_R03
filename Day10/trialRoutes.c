#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s{
    int num;
    int x, y;
    struct s* next;
}Node;

typedef struct{
    Node* rear;
    Node* front;
    int size;
}Queue;

void initQueue(Queue* q)
{
    q->front = q->rear = NULL;
    q->size = 0;
    return;
}

void enqueue(Queue* q, int a, int x, int y)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num = a;
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    if(q->size == 0)
    {
        q->rear = q->front = newNode;
        q->size++;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
        q->size++;
    }

    return;
}

Node* dequeue(Queue* q)
{
    Node* temp = q->front;
    q->size--;
    if(q->size == 0)
    {
        q->front = q->rear = NULL;       
    }
    else{
        q->front = temp->next;
        temp->next = NULL;
    }
    return temp;
}

int isEmpty(Queue* q)
{
    return q->size == 0;
}

typedef struct{
    int** mat;
    int col;
    int rows;
}Matrix;

void insertNode(Node** head, int x, int y)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->num = 9;
    newNode->x = x;
    newNode->y = y;
    if(*head == NULL)
    {
        *head = newNode;
    }
    else{
        Node* n = *head;
        while(n->next)
        {
            n = n->next;
        }
        n->next = newNode;
    }
}

int isInList(Node* head, int x, int y)
{
    Node* n = head;
    while(n)
    {
        if(n->x == x && n->y == y)
        {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void freeList(Node* head)
{
    while(head)
    {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return;
}

int pathsPresent(Matrix* mat, int x, int y)
{
    Queue q;
    initQueue(&q);
    int dx[] = {0, 0 ,-1, 1};
    int dy[] = {-1, 1, 0, 0};
    int count = 0;
    Node* headList = NULL;
    enqueue(&q,0,x,y);
    while(!isEmpty(&q))
    {
        Node* n = dequeue(&q);
        if(n->num == 9)
        {   if(!isInList(headList, n->x, n->y))
            {
                insertNode(&headList, n->x, n->y);
                count++;
            }
            continue;
        }
        for(int i = 0; i< 4; i++)
        {
            int a = n->y+dy[i];
            int b = n->x + dx[i];
            if(a>=0 && a < mat->rows && b >= 0 && b < mat->col)
            {
                if(mat->mat[a][b] == n->num+1)
                {
                    enqueue(&q, n->num+1,n->x+dx[i], n->y+dy[i]);
                }
            }
            // if(mat->mat[n->y+dy[i]][n->x + dx[i]] == n->num+1)
            // {
            //     enqueue(&q, n->num+1,n->x+dx[i], n->y+dy[i]);
            // }
        }
    }
    free(headList);
    return count;
}

int trailHeads(Matrix* mat)
{
    int sum = 0;
    for(int i = 0; i< mat->rows; i++)
    {
        for(int j =0; j< mat->col;j++)
        {
            if(mat->mat[i][j] == 0)
            {
                sum += (pathsPresent(mat, j, i));
            }
        }
    }
    return sum;
}

int main()
{
    FILE* file;
    // char filename[] = "test10.txt";
    char filename[] = "input10.txt";
    char buffer[128];
    file = fopen(filename, "r");
    Matrix mat;
    fgets(buffer, sizeof(buffer), file);
    mat.col = strlen(buffer)-1;
    fclose(file);
    file = fopen(filename, "r");
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file))
    {
        count++;
    }
    mat.rows = count;
    fclose(file);
    file = fopen(filename, "r");
    mat.mat = (int**)malloc(sizeof(int*)*mat.rows);
    for(int i = 0; i< mat.rows; i++)
    {
        mat.mat[i] = (int*)malloc(sizeof(int)*mat.col);
    }
    count = 0;
    while(fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer,"\n")] = '\0';
        for(int i = 0; i< mat.col; i++)
        {
            mat.mat[count][i] = buffer[i] - '0';
        }
        count++;
    }
    printf("Printing matrix:\n");
    for(int i = 0; i< mat.rows; i++)
    {
        for(int j = 0; j< mat.col; j++)
        {
            printf("%d ", mat.mat[i][j]);
        }
        printf("\n");
    }
    printf("There are trail heads: %d", trailHeads(&mat));
    return EXIT_SUCCESS;
}