# Day 10 Writeup:
## Languages Used: `C`
## Part 1:
This was a simple problem, to the point the toughest part was actually converting the file into a proper matrix.

I used the queue structure to iterate through and see if it would reach a particular path.<br>
Also used a LinkedList to make sure that I am not counting nodes that I have already counted, so it would be the same.
```
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

typedef struct{
    int** mat;
    int col;
    int rows;
}Matrix;
```
Therefore, I made two methods, one to check and see if there was `0` at `[x,y]`, and also to  go through the paths, appropriately enqueuing and dequeue the nodes.

```
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
```
```
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
```
Thus, within the first attempt, I could see that the matrix is output correctly and the node has been counted properly.

## Part 2:
This part was somehow much easier, as I just needed to delete the method from the previous code:
```
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
```
That checks and sees if the point is present in this list or not.

However, since rating does not require this condition, all I need to do is to remove those conditions and viola, the program outputs the answer properly!

And with this, another two simple challenges are done for the day.

With this, I conclude the `Day 10` of the `Advent of Code 2024`...<br>
Waiting for the next challenge!