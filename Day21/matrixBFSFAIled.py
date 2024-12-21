from collections import deque

def bfs(mat, start, target, op):
    rows, cols = len(mat), len(mat[0])
    dirs = ['^', 'v', '<', '>']
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)] 
    q = deque([(start, '')])
    visited = set()
    visited.add(start)
    # visited.add((3,0) if op == 1 else (0,0))    
    while q:
        (curRow, curCol), path = q.popleft()
        if (curRow, curCol) == target:
            return path        
        for i, (dr, dc) in enumerate(moves):
            newRow, newCol = curRow + dr, curCol + dc            
            if 0 <= newRow < rows and 0 <= newCol < cols and (newRow, newCol) not in visited:
                visited.add((newRow, newCol))
                newPath = path + dirs[i]
                q.append(((newRow, newCol), newPath))
    
    return ''

def findPath(mat, seq, op):
    dirs = []
    pos = {
        'A': (3, 2) if op == 1 else (0, 2),
        '0': (3, 1),
        '2': (2, 1),
        '9': (0, 2),
        '^': (0, 1),
        '<': (1, 0),
        'v': (1, 1),
        '>': (1, 2),
        '1': (2, 0),
        '3': (2, 2),
        '4': (1, 0),
        '5': (1, 1),
        '6': (1, 2),
        '7': (0, 0),
        '8': (0, 1)
    }
    path = list('A' + seq)
    for i in range(len(path) - 1):
        curChar = path[i]
        nextChar = path[i + 1]        
        curPos = pos[curChar]
        nextPos = pos[nextChar]
        bfsPath = bfs(mat, curPos, nextPos, op)
        dirs.append(bfsPath + 'A') 
    
    return ''.join(dirs)

mat = [
    [7, 8, 9],
    [4, 5, 6],
    [1, 2, 3],
    [' ', 0, 'A']
]
keypad = [
    [' ', '^', 'A'],
    ['<', 'v', '>']
]

filename = 'Day21/test21.txt'
# filename = 'Day21/input21.txt'
with open(filename, 'r') as f:
    lines = [line.strip() for line in f]

total = 0
for line in lines:
    sub = line[:-1]
    mul = len(findPath(keypad, findPath(keypad, findPath(mat, line, 1), 0), 0))
    total += int(sub) * mul
    print(line, mul, total)
print(total)
