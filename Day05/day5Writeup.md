# Day 5 Writeup:
## Languages Used: `C`
## Part 1:
This was a little bit tough. I didn't expect to spend this much time on this challenge, but here we are, finishing up the challenge.<br>
At a glance, it seemed that it was a simple linkedlist problem that required a little bit of string manipulation once you have read the buffer from the file, but it took some time to clear this challenge.

The first approach that I tried was this:
```
int checkOrder(Node* head, char* str)
{
    HashSet h1 = {0};
    memset(h1.hash, 0, sizeof(h1.hash));
    i = 0;
    while(i<j)
    {
        n = head;
        int s = 0;
        while(s<j)
        {
            if(s == i){
                s++;
                continue;
            }
            while(n != NULL)
            {
                if(n->n1 == h1.arr[s] && n->n2 == h1.arr[i])
                {
                    if((h1.hash[h1.arr[s]]))
                    {
                        break;
                    }
                    else{
                        return 0;
                    }
                }
                else if(n->n1 == h1.arr[i] && n->n2 == h1.arr[s])
                {
                    h1.hash[h1.arr[i]] = 1;
                    break;
                }
                n = n->next;
            }
            if(n == NULL)
            {
                return 0;
            }
        }
        i++;
    }
    return middle(h1.arr,j);
}
```

Which was very clunky and it really did not work at all, so I changed my approach and went with a simple `two` for loops one which checked and saw if the entire order was correct or not.
```
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
```

## Part 2:
This one took me way longer than I had anticipated. At first I thought the first one was hard to solve, as I had to pretty much bruteforce my way and check and see if it was possible. <br>
Here, I found an approach very fast and wanted to use that approach, but it was using recurssion and I didn't want to use recursion until it was the last option that was remaininf for me to use.

Therefore, I tried using various data structures like graphs, queues, priority queues, hashsets, hashmaps, etc. in hopes of solving this question properly. 

However, all these different approaches were not working at all.
Ranging from raging mandness and frustrated mental brain, I decided to stick with my gut and basically copy pasted the code from before with some minor changes to fit the new scheme.
```
int correctOrder(Node* head, int* arr, int size) {
    HashSet h1 = {0};
    memset(h1.hash, 0, sizeof(h1.hash));
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            if (i == k) 
                continue;
            Node* temp = head;
            while (temp) {
                if (temp->n1 == arr[k] && temp->n2 == arr[i]) {
                    if (h1.hash[arr[k]]) 
                        break;
                    else 
                        swap(&arr[k], &arr[i]);
                        printArray(arr, size);
                        return correctOrder(head, arr, size);
                }
                else if(temp->n1 == arr[i] && temp->n2 == arr[k])
                {
                    h1.hash[arr[i]] = 1;
                }
                temp = temp->next;
            }
        }        
    }
    return middle(arr,size);
}
```

With this, I managed to complete this challenge.
I will admit, it really took out a lot of time, and it helped me learn a lot of things, but this challenge was definitely more on the challenging side of things.

With that, I conclude the `Day 5` of the `Advent of Cyber 2024`...<br>
Bring on the next challenge!