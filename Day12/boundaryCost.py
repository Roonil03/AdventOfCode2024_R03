from collections import deque

def calcFencePrice(map):
    rows = len(map)
    cols = len(map[0])
    visited = set()
    total = 0
    dir = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    def bfs(x, y):
        q = deque([(x, y)])
        visited.add((x, y))
        plant = map[x][y]
        area = 0
        peri = 0
        while q:
            cx, cy = q.popleft()
            area += 1
            for dx, dy in dir:
                nx, ny = cx + dx, cy + dy
                if 0 <= nx < rows and 0 <= ny < cols:
                    if map[nx][ny] == plant and (nx, ny) not in visited:
                        visited.add((nx, ny))
                        q.append((nx, ny))
                    elif map[nx][ny] != plant:
                        peri += 1
                else:
                    peri += 1
        return area, peri
    for i in range(rows):
        for j in range(cols):
            if (i, j) not in visited:
                area, peri = bfs(i, j)
                total += area * peri
    return total

def readMap(filename):
    with open(filename, 'r') as file:
        map = [list(line.strip()) for line in file.readlines()]
    return map

filename = 'Day12/input12.txt'
# filename = 'Day12/test12.txt'
map = readMap(filename)
print("Total price of fencing:", calcFencePrice(map))
