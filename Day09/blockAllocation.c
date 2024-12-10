#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct{
    int* nums;
    int len;
}Data;

typedef struct s{
    int num;
    struct s* next;
}Node;

typedef struct b{
    int len;
    Node* head;
    struct b* next;
    struct b* prev;
}Block;

void printBlocks(Block* bs)
{
    Block* b = bs;
    while(b != NULL)
    {
        if(b->len == 0)
        {
            printf(" || ");
            b = b->next;
            continue;
        }
        Node* n = b->head;
        while(n->next != NULL)
        {
            printf("%d-> " , n->num);
            n = n->next;
        }
        printf("%d ", n->num);
        printf(" || ");
        b = b->next;
    }
    printf("\n");
}

void printArray(int* arr, int size)
{
    for(int i = 0; i< size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

long long checksum(Data* d)
{
    long long sum = 0;
    printArray(d->nums, d->len);
    for(int i = 0; i< d->len; i++)
    {
        if(d->nums[i] != 0)
        {
            sum += (d->nums[i]-1)*i;
        }
        else{
            sum += 0;
        }
    }
    return sum;
}

void insertNode(Node** head, int num)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = NULL;
    if(*head == NULL)
    {
        *head = newNode;
        return;
    }
    else{
        Node* n = *head;
        while(n->next != NULL)
        {
            n = n->next;
        }
        n->next = newNode;
    }
}

void insertBlock(Block** b, int len)
{
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->len = len;
    newBlock->head = NULL;
    newBlock->next = NULL;
    newBlock->prev = NULL;
    if(*b == NULL)
    {
        *b = newBlock;
    }
    else{
        Block* n = *b;
        while(n->next != NULL)
        {
            n = n->next;
        }
        n->next = newBlock;
        newBlock->prev = n;
    }
    return;
}

void freeBlocks(Block* b) {
    while (b) {
        Block* temp = b;
        b = b->next;
        Node* n = temp->head;
        while (n != NULL) {
            Node* tempNode = n;
            n = n->next;
            free(tempNode);
        }
        free(temp);
    }
}

Block* convertBlocks(char* str, int len)
{
    Block* head = NULL;
    int count = 1;
    for(int i = 0; i < len; i++)
    {
        int size = str[i] - '0';
        insertBlock(&head, size);
        if(size == 0)
        {
            continue;
        }
        Block* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->head = NULL;
        for(int j = 0; j < size; j++)
        {
            if(i % 2 == 0)
            {
                insertNode(&temp->head, count);
            }
            else{
                insertNode(&temp->head, 0);
            }
        }
        if(i % 2 == 0)
            count++;
    }
    return head;
}

void sortBlocks(Block* bs)
{
    Block* end = bs;
    while(end->next != NULL)
    {
        end = end->next;
    }
    while(end->prev != NULL)
    {
        Block* space = bs;
        // printBlocks(bs);
        while(end->prev != NULL && (end->head == NULL || end->head->num == 0 ))
        {
            end = end->prev;
        }
        if(end->len == 0)
        {
            end = end->prev;
            continue;
        }
        Block* temp = end;
        while(space != temp && space)
        {
            space = space->next;
            if(space->head && space ->head->num == 0 && space->len >= temp->len)
            {
                break;
            }
        }
        if(space == temp)
        { 
            end = end->prev;
            continue;
        }
        if(space->len == temp->len)
        {
            end = end->prev;
            if(space != temp->prev)
            {
                if(space->prev)
                    space->prev->next = temp;
                if(space->next)
                    space->next->prev = temp;
                if(temp->prev)
                    temp->prev->next = space;
                if(temp->next)
                    temp->next->prev = space;
                Block* t = temp->next;
                temp->next = space->next;
                space->next = t;
                t = temp->prev;
                temp->prev = space->prev;
                space->prev = t;            
            }
            else{
                if(space->prev)
                    space->prev->next = temp;
                if(temp->next)
                    temp->next->prev = space;
                Block* t = temp->next;
                temp->next = space;
                space->next = t;
                t = space->prev;
                space->prev = temp;
                temp->prev = t;
            }   
        }
        else if (space->len > temp->len)
        {
            if(space->next != temp)
            {   
                end = end->prev;
                int diff = space->len - temp->len;
                Block* madeSpace = (Block*)malloc(sizeof(Block));
                madeSpace->len = diff;
                madeSpace->head = NULL;
                for(int i = 0; i< diff; i++)
                {
                    insertNode(&madeSpace->head,0);
                }
                madeSpace->next = space->next;
                madeSpace->prev = temp;
                Block* endSpace = (Block*)malloc(sizeof(Block));
                endSpace->len = temp->len;
                endSpace->head = NULL;
                for(int i = 0; i< endSpace->len; i++)
                {
                    insertNode(&endSpace->head, 0);
                }
                endSpace->prev = temp->prev;
                endSpace->next = temp->next;
                temp->prev->next = endSpace;
                if(space->prev)
                    space->prev->next = temp;
                if(space->next)
                    space->next->prev = madeSpace;
                temp->prev = space->prev;
                temp->next = madeSpace;
                free(space);
                space = NULL;
            }
            else{
                end = end->prev;
                int diff = space->len - temp->len;
                Block* madeSpace = (Block*)malloc(sizeof(Block));
                madeSpace->len = diff;
                madeSpace->head = NULL;
                for(int i = 0; i< diff; i++)
                {
                    insertNode(&madeSpace->head,0);
                }
                Block* endSpace = (Block*)malloc(sizeof(Block));
                endSpace->len = temp->len;
                endSpace->head = NULL;            
                temp->prev->next = endSpace;
                for(int i = 0; i< endSpace->len; i++)
                {
                    insertNode(&endSpace->head, 0);
                }
                endSpace->prev = madeSpace;
                endSpace->next = temp->next;
                madeSpace->next = endSpace;
                madeSpace->prev = temp;
                space->prev->next = temp;
                temp->next->prev = endSpace;
                temp->prev - space->prev;
                temp->next = madeSpace;
                free(space);
            }
        }
        // printBlocks(bs);
    }
    return;
}

Data* convertBack(Block* b, char* str)
{
    Data* d = (Data*)malloc(sizeof(Data));
    d->len = 0;
    int len = strlen(str);
    for(int i = 0; i< len; i++)
    {
        d->len += (str[i] - '0');
    }
    d->nums = (int*)calloc(d->len,sizeof(int));
    int j = 0;
    while(b)
    {
        Node* n = b->head;
        if(b->len == 0)
        {
            b = b->next;
            continue;
        }
        while(n)
        {
            d->nums[j++] = n->num;
            n = n->next;
        }
        b = b->next;
    }
    return d;
}

Data* changingArray(char* str, int len)
{
    Block* bs = convertBlocks(str, len);
    sortBlocks(bs);
    Data* d = convertBack(bs, str);
    freeBlocks(bs);
    return d;
}

int main()
{
    char filename[] = "input9.txt";
    // char filename[] = "test9.txt";
    FILE* file = fopen(filename, "r");
    if(!file)
    {
        printf("An error has occured");
        exit(0);
    }
    char buffer[40000];
    Data* d;
    while(fgets(buffer,sizeof(buffer),file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Read buffer: %s\n", buffer);
        int a = strlen(buffer);
        // printf("%d\n",a);
        d = changingArray(buffer,a);
        long long cs = checksum(d);
        printf("%d\n", d->len);
        printf("Checksum: %lld", cs);
    }    
    free(d);
    fclose(file);
    return EXIT_SUCCESS;
}