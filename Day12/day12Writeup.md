# Day 12 Writeup:
## Languages Used: `Python`
## Part 1:
Looking at the question for a while, it was a simple modification of Breadth First Search, since all we had to do was figure out the positions where it is present and mark them that they have an edge.

Therefore, I started writing the script for it in python:
```
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
```

This properly did the BFS and gave the answer in the end.

## Part 2:
This was a little tricky.<br>
Originally what I attempted to do was to extend the matrix to check whether or not it had boundaries present or not. This approach worked, but I wanted to find a solution where I could use less space. I was fortunate enough to get a small input, and I did not want yesterday's situation to take place again, therefore I decided to try finding a more space efficient solution.

Then I thought of this solution:
```
def calculate(values):
    grid = Grid.fromText(values)
    regions = []
    for cell in grid.cellRange():
        if grid.grid[cell[1]][cell[0]] != "#":
            currentValue = grid.grid[cell[1]][cell[0]]
            grid.grid[cell[1]][cell[0]] = "#"
            regions.append(set([cell]))
            processingQueue = deque([cell])
            while processingQueue:
                currentCell = processingQueue.popleft()
                for neighbor in grid.getNeighbors(startPoint=currentCell):
                    if grid.grid[neighbor[1]][neighbor[0]] == currentValue:
                        grid.grid[neighbor[1]][neighbor[0]] = "#"
                        processingQueue.append(neighbor)
                        regions[-1].add(neighbor)
    totalValue = 0
    for region in regions:
        sideCount = 0
        for offset in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            regionSides = set()
            for cell in region:
                adjacentCell = (cell[0] + offset[0], cell[1] + offset[1])
                if adjacentCell not in region:
                    regionSides.add(adjacentCell)
            removable = set()
            for side in regionSides:
                linked = (side[0] + offset[1], side[1] + offset[0])
                while linked in regionSides:
                    removable.add(linked)
                    linked = (linked[0] + offset[1], linked[1] + offset[0])
            sideCount += len(regionSides) - len(removable)
        totalValue += len(region) * sideCount
    return totalValue
```
Over here, the calculate method:
- Identifies distinct regions in the grid, calculates their properties, and computes a result based on the mode.
- Uses a BFS approach with a queue to traverse connected cells of the same value.
- Computes the area * side count.


Thus with these two questions done with the help of BFS, I conclude the `Day 12` of the `Advent of Code 2024`...<br>
Looking forward to the next day's problems!