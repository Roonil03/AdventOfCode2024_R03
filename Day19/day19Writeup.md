# Day 19 Writeup:
## Languages Used: `Python` and `Go`
## Part 1:
It took a little while to figure that today's problem was simpler to do with recurssion. I opted to do this part in python since I haven't explored it.

Therefore, this was the main function that I was using for the recursion:
```
def isPossible(t, seqs):
    if not t:
        return True
    return sum(
        isPossible(forward(s,t), (seqs)) 
        for s in seqs
        if t.startswith(s)
    )
```

Text reading by now, it is something that I have gotten a hang of. Apart from all that, when I initially tried it, I kept getting 0 as the answer.

After spending a while trying to debug and understand why it was not at all working, I came across<a href="https://docs.python.org/3/library/functools.html#functools.lru_cache"> this</a>.

With this I coud recall the last function, which fixed the issue that I was having and thus I got the answer.

## Part 2:
This part wanted me to get all the permuations and combinations of the towels that were possible and then wanted me to add them all up.
Therefore, I would need to change the recurssive function slightly going from this:
```
def numberPossible(towels, seq):
    return sum(isPossible(t, (seqs)) > 0 for t in towels)
```
that was implemented in Python, to this:
```
func desiredPatterns(towels []string, seqs map[string]struct{}) int {
	memo := make(map[string]int)
	count := 0
	for _, t := range towels {
		count += checkTowel(t, seqs, memo)
	}
	return count
}
```
That I did in Go.<br>
Yep, I changed the langugages and converted the entire previous code to Go for practice.

Thus, with that, i ended up getting a really massive answer, which ended up being correct.

With that, I conclude `Day 19` of the `Advent of Code 2024`...<br>
Looking forward to the next day!