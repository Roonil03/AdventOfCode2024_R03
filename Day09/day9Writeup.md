# Day 9 Writeup:
## Languages Used: `C`
## Part 1:
Main takeaway from this problem was that there was array manipulation that was meant to be done. So the first thing that I ended up doing was creating a string and an integer array that would be passed around as pointers that would deal with these manipulations. 

It took me sometime and the help of my senior <a href="https://github.com/Kirit0me">Kirit0me</a> to figure out that the problem wasn't cycling back the characters, and they were dealing with full numbers taking up a single slot.

The main focus of this program was the `changingArray()` method which was dealing with the swapping of the elements and performing the necessary functions to finish the problem:
```
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
```

After the swapping took place, I just had to calculate the checksum, which was very simple to do, and thus, with that, the first part got over.


## Part 2:
This part really made me question my ability to manipulate pointers.

This time, instead of just manipulating everything with just a character array and a integer array, I opted to break the entire array into different blocks that were connected in the form of a linked list and a double linked list to manipulate the entire list of characters.

For the checksum calculation, I opted to change the integer array into a struct that would store the array as well as how many characters are present in that array:
```
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
```

Then came to changing the logic of the `changingArray()` method, that was originally just swapping the characters around, now I had to make sure that they were properly changing the entire blocks around:
```
Data* changingArray(char* str, int len)
{
    Block* bs = convertBlocks(str, len);
    sortBlocks(bs);
    Data* d = convertBack(bs, str);
    freeBlocks(bs);
    return d;
}
```

Out of these, the main method that was dealing with the swapping is as the name suggests, `sortBlocks()` which was swapping the blocks properly and making sure that they were working properly.
```
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
```

There were mainly four conditions that I needed to take care of:
- When the spaces block is present just before the block to swap for both cases, when the size is same and when spaces is larger
- When the size of the block is 0, to make sure that the manipulation can take place
- When the size of the block is larger than the spaces provided
- When the pointer reaches the end.

I had to sit with a book to make sure that I was not going to be making an error while connecting the different pointers, as that would lead me to get a segmentation fault <i>(which I did end up getting on numerous occasions)</i>. But in the end, I did manage to get the program running, to get the answer that I desired.

And thus, that concludes this day's two challenges. I can definitely see that the problems are spiking in level.

With this, I conclude the `Day 9` of the `Advent of Code 2024`!<br>
Looking forward to the next day!