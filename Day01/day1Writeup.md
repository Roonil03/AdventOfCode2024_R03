# Day 1 Writeup:
## Languages Used = `C`
## Part 1:
This problem was a simple case of using a Linked List. 
Since there were a 1000 numbers that were going to be stored in each list, it made sense to sort them as we are storing them into the linked list.<br>
Firstly, I created three different text files, one with the day 1 inputs, one with the inputs and an additional space at the end <i>(since it was messing with the inputting into the terminal at times)</i>, and finally a textfile of the example test case that was provided to us.

Then I started to program the code.<br>
The goal was simple. We just had to find the distance between each of the two elements and do the summation of all the different distances.

Therefore, I approached the program with this simple approach:
```
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
```

Simply put, it was an efficient method that ran with O(n) time complexity.

## Part 2:
The second part was a little more tricky as I needed to find out the number of times one element was present in another list.
I still took the approach to store the numbers in the sorted list manner, which definitely cut down the time in finding the total count of that particular number present.

Therefore, for calculating the similarity score, I used this approach:
```
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
```
I tried working it out with fewer variables, but that ended up causing more issues, so I made an extra variable while traversing the left list <i>(stored as temp)</i>.

Thus with these two problems done for the day, I conclude the `Day 1` of the `Advent of Code 2024` with a good start...<br>
Looking forward to the challenge!
