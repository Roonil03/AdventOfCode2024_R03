# Day 14 Writeup:
## Languages Used: `C` and `Python`
## Part 1:
I had to think about it for a while, before I really think of an easier solution. I originally thought of using stacks to store each position in the grid, and then realized that it would be a waste of space.

Instead I would just use the struct and using that I would change the positions for each of the robots manually to get my score.

And thus, this was the method that I made:
```
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
```

This dealt with all the position moving and then I also added a score calculating method:
```
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
```
This really worked well, and I got my answer pretty fast.

## Part 2:
This took me a while to figure out. I realized that it was not at all going to be easy to do this problem in C, so I opted to switch languages which would make it easier for me to solve this question.

This question also took me a while to figure out what they are exactly asking.
I had to find what a christmas tree was, and make sure that the number of seconds it took to make that christmas tree is the answer...<br>
For that I drew this baseline condition:
To find if there are more than one robots occupying the same position...<br>
If all of them aren't, then to print it and to check and see if the christmas tree is printed or not.

Thus, I used `numpy` in python for this problem:
```
def isDistinctPattern(robots):
    grid = np.zeros((Y, X), dtype=int)
    for robot in robots:
        grid[robot.posY, robot.posX] += 1
    return np.all(grid <= 1)
```

Thus, with this, each time I could check and see if the pattern is printed or not, and then get the number of seconds it took to achieve that pattern.

With that I concluded the `Day 14` of the `Advent of Code 2024`...<br>
Awaiting the next day!