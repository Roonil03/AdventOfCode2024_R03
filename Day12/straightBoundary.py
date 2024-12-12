from collections import deque

class Grid:
    def __init__(self, gridData):
        self.grid = [list(row) for row in gridData]
        self.gridHeight = len(self.grid)
        self.gridWidth = len(self.grid[0])

    @classmethod
    def fromText(cls, values):
        return cls(values)

    def cellRange(self):
        for row in range(self.gridHeight):
            for col in range(self.gridWidth):
                yield (col, row)

    def getNeighbors(self, startPoint=(0, 0)):
        col, row = startPoint
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        return [
            (col + dCol, row + dRow)
            for dCol, dRow in directions
            if 0 <= col + dCol < self.gridWidth and 0 <= row + dRow < self.gridHeight
        ]

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

def readFile(fileName):
    with open(fileName, 'r') as file:
        return [line.strip() for line in file.readlines()]


# filename = 'Day12/test12.txt'
filename = 'Day12/input12.txt'
garden = readFile(filename)
print('The total price is:', calculate(garden))
