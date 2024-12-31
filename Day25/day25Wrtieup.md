# Day 25 Writeup:
## Languages Used: `Python`
## Part 1:
The last stretch begins. After so many days of just solving coding puzzles after coding puzzles, this was the final challenge.

And a simple one at that, all we needed to do was figure out the method to calculate which are keys, which are not keys, and then see if the sum of the two is less than the required limit or not.

With file reading and all the skills that I developed during the course of this one event, it was nice break from the other challenging ones.

This was the method I was using to segregate between the two:
```
def classifyGrids(grids, rawGrids):
    locks = []
    keys = []
    for idx, grid in enumerate(grids):
        if all(c == '#' for c in rawGrids[idx][0]):
            locks.append((idx, grid))
        if all(c == '#' for c in rawGrids[idx][-1]): 
            keys.append((idx, grid))
    print("Locks:", locks)  
    print("Keys:", keys)   
    return locks, keys
```

After that, it was just simple permutation and combination to check and see which all fit in which others.

## Part 2:
This one only activates if you have all the other stars in the challenge.

Since I was always getting both the stars for the specific days, I easily cleared it.

After that, it was just the advent calendar lighting up and the conclusion to the story between us and the Historians.

Thus, with all 50 stars collected...<br>
I can finally state this:

    > I conlude the `Advent of Code 2024`!

