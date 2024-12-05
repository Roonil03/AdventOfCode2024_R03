# Day 2 Writeup:
## Languages Used = `C`
## Part 1:
This problem also required the use of a linked list, but here, I needed to be careful of the inputs, as the different inputs were on different lines.<br>
Therefore, while taking in the text input, I decided to take the input as a string, rather than different integers and then modified the <i>insert</i> method to make sure that I can insert just the numbers into the list.
```
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
```
Now, what I needed to do was to figure out a method to check if the level was safe or not, which was pretty simple.
All we needed to determine whether the enitre list is ascending or descending and then use that to determine if they follow the restrictions or not.<br>
Which made the snippet look like this:
```
int levelPossbile(Node* head)
{
    Node* n = head;
    int asc = 0, des = 0;
    if(n->next != NULL && n->n < n->next->n)
    {
        asc = 1;
    }
    else
    {
        des = 1;
    }
        while (n->next != NULL) {
        int diff = abs(n->next->n - n->n);
        if (diff < 1 || diff > 3 || (asc && n->n >= n->next->n) || (des && n->n <= n->next->n)) {
            return 0;
        }
        n = n->next;
    }
    return 1;
}
```
Thus, this works in an efficient manner, making the time complexity of the entire problem to be O(n).

## Part 2:
Now there was an issue with this statement.
At first, I just took the condition if the code was working even if the first node should never be deleted ie <i> I forgot to take the condition where we could delete the first node to make the entire level safe...</i><br>
Which made the method that I was using this:
```
int levelPossbile(Node* head)
{
    Node* n = head;
    int asc = 0, des = 0;
    if(n->next != NULL && n->n < n->next->n)
    {
        asc = 1;
    }
    else
    {
        des = 1;
    }
    int tol = 0;
    Node* ahead = n->next;
    while (ahead != NULL) {
        int n1 = n->n;
        int n2 = ahead->n;
        int diff = abs(n1-n2);
        if ((diff < 1 || diff > 3 || (asc && n1 >= n2) || (des && n1 <= n2)) && tol == 0) {
            ahead = ahead->next;
            tol++;
        }
        else if((diff < 1 || diff > 3 || (asc && n1 >= n2) || (des && n1 <= n2)) && tol == 1)
        {
            return 0;
        }
        else{
            n = ahead;
            ahead = ahead -> next;
        }
    }
    return 1;
}
```

This worked for the test case, because it didn't have the `"first node deletion type"` testcase, so I tried, but got the wrong answer.

So I had to somewhat re-write the entire method from scratch to make sure that I account for those cases where I have to delete the head node.
```
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
```
with this, I made sure that the code works, while also reusing the same method.

Thus, another two problems for the day is done, I conclude `Day 2` of the `Advent of Code 2024`...<br>
Onto the next challenge!