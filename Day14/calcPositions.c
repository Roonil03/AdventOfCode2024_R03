#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Y 103 //tall
#define X 101 //width

typedef struct{
    int posX;
    int posY;
    int speedX;
    int speedY;
}Robot;

typedef struct s{
    Robot s;
    struct s* next;
}Node;

Node* createNode(Robot* s)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->s.posX = s->posX;
    newNode->s.posY = s->posY;
    newNode->s.speedX = s->speedX;
    newNode->s.speedY = s->speedY;
    newNode->next = NULL;
    return newNode;
}

void convertInput(char *input, int *posX, int *posY, int *speedX, int *speedY) {
    sscanf(input, "p=%d,%d v=%d,%d", posX, posY, speedX, speedY);
}

Node* addingToList()
{
    char filename[] = "input14.txt";
    // char filename[] = "test14.txt";
    FILE* file = fopen(filename, "r");
    char buffer[128];
    Node* head = NULL;
    Node* n = head;
    while(fgets(buffer, sizeof(buffer), file))
    {

        int posX, posY, speedX, speedY;
        convertInput(buffer, &posX, &posY, &speedX, &speedY);
        Robot temp;
        temp.posX = posX;
        temp.posY = posY;
        temp.speedX = speedX;
        temp.speedY = speedY;
        if(head == NULL)
        {
            head = createNode(&temp);
            n = head;
        }
        else{
            n->next = createNode(&temp);
            n = n->next;
        }
    }
    fclose(file);
    return head;
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

void movePositions(Node* head)
{
    Node* n = head;
    while(n)
    {
        n->s.posX = (n->s.posX + n->s.speedX + X)%X;
        n->s.posY = (n->s.posY + n->s.speedY + Y)%Y;
        // printf("%d, %d\n", n->s.posX, n->s.posY);
        n = n->next;
    }
    // printf("\n");
}

int score(Node* head)
{
    int quad[4] = {0};
    Node* n = head;
    int midX = (X)/2;
    int midY = (Y)/2;
    while(n)
    {
        if(n->s.posX > midX && n->s.posY > midY)
        {
            quad[0]++;
        }
        else if(n->s.posX < midX && n->s.posY > midY)
        {
            quad[1]++;
        }
        else if(n->s.posX < midX && n->s.posY < midY)
        {
            quad[2]++;
        }
        else if(n->s.posX > midX && n->s.posY < midY)
        {
            quad[3]++;
        }
        n = n->next;
    }
    int score = 1;
    for(int i = 0; i< 4; i++)
    {
        printf("%d\t", quad[i]);
        score *= quad[i];
    }
    return score;
}

int main()
{
    Node* head = addingToList();
    int times = 100;
    for(int i = 0; i< times; i++)
    {
        movePositions(head);
    }
    printf("The score is: %d", score(head));
    free(head);
    return EXIT_SUCCESS;
}

