from functools import lru_cache

def gettingInput(filename):
    with open(filename) as f:
        seqs, towels = f.read().split("\n\n")
    return frozenset(seqs.split(", ")), towels.split()

def forward(pre, seq):
    return seq[len(pre):]

@lru_cache(maxsize=None)
def isPossible(t, seqs):
    if not t:
        return True
    return sum(
        isPossible(forward(s,t), (seqs)) 
        for s in seqs
        if t.startswith(s)
    )

def numberPossible(towels, seq):
    return sum(isPossible(t, (seqs)) > 0 for t in towels)

filename = "Day19/input19.txt"
# filename = "Day19/test19.txt"
seqs, towels = gettingInput(filename)
print(numberPossible(towels, seqs))
