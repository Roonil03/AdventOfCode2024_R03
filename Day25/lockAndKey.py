def parseFile(filePath):
    with open(filePath, "r") as f:
        data = f.read().strip().split("\n\n")
    grids = []
    for block in data:
        rows = block.split("\n")
        grid = [sum(1 for row in rows if row[i] == '#') for i in range(len(rows[0]))]
        grids.append(grid)
    print("Parsed grids:", grids)
    return grids

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

def checkFit(lock, key):
    for i in range(len(lock)):
        if lock[i] + key[i] > 7:
            return False
    return True

def findPairs(locks, keys):
    pairs = []
    for lId, lock in locks:
        for kId, key in keys:
            if checkFit(lock, key):
                pairs.append((lId, kId))
    print("Pairs:", pairs)
    return pairs

# filePath = "Day25/test25.txt"
filePath = "Day25/input25.txt"
grids = parseFile(filePath)
rawGrids = []
with open(filePath, "r") as f:
    data = f.read().strip().split("\n\n")
    for block in data:
        rawGrids.append(block.split("\n"))    
locks, keys = classifyGrids(grids, rawGrids)
pairs = findPairs(locks, keys)
count = 1
for lId, kId in pairs:
    print(f"{count}. Lock {lId} and Key {kId} fit!")
    count += 1
print(count-1)

