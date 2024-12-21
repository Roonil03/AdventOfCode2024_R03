# Day 21 Writeup:
## Languages Used: `Python`
## Part 1:
This problem was definintely one of the hardest ones to understand code. It  took me a while to understand how to change the BFS and make sure that it would work. At first, I was thinking of using regualr BFS on the matrix to calculate the sequence order, and try to calculate it that way. However, with multiple failled attempts, I realized that it was not working because of one condition that we were taking into consideration, and that was it should not be touching the ' ' character in the matrix at all to reach it's goals.

Marking it as visited for the BFS was also not working, so I was told to use either np arrays or convert it entirely into a 1D array for the calculation. 
So, that's what I did.

I had to also make sure that I make it recursive to make sure that I could change the number of robots as well, if I encounter multiple robots. <i>(This was warned to me by my seniors who were also solving it and have had prior experience with such types of questons)</i>

With that I began my journey to decrypt everything and make the entire program recursive.

## Part 2:
Since I had made the program recursive, all it needed me to do was change one value in the program to turn the entire thing to go through 26 robots worth of sucessions. 

Thus, with that, I have completed another 2 challenges...

And therefore, I can conclude the `Day 21` of the `Advent of Code 2024`...<br>
Awaiting for the problems of the next day!