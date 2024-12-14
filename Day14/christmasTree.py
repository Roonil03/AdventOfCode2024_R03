import numpy as np

Y = 103
X = 101

class Robot:
    def __init__(self, posX, posY, speedX, speedY):
        self.posX = posX
        self.posY = posY
        self.speedX = speedX
        self.speedY = speedY

def convertInput(inputStr):
    parts = inputStr.strip().split()
    posX, posY = map(int, parts[0].split('=')[1].split(','))
    speedX, speedY = map(int, parts[1].split('=')[1].split(','))
    return Robot(posX, posY, speedX, speedY)

def addingToList(filename="Day14/input14.txt"):
    robots = []
    with open(filename, 'r') as file:
        for line in file:
            robots.append(convertInput(line))
    return robots

def movePositions(robots):
    for robot in robots:
        robot.posX = (robot.posX + robot.speedX + X) % X
        robot.posY = (robot.posY + robot.speedY + Y) % Y

def printGrid(robots):
    grid = np.full((Y, X), '.', dtype=str)
    for robot in robots:
        grid[robot.posY, robot.posX] = '#'
    for row in grid:
        print(''.join(row))
    print("\n")

def isDistinctPattern(robots):
    grid = np.zeros((Y, X), dtype=int)
    for robot in robots:
        grid[robot.posY, robot.posX] += 1
    return np.all(grid <= 1)

robots = addingToList()
seconds = 1
notCorrectTree = True
while notCorrectTree:
    movePositions(robots)
    if isDistinctPattern(robots):
        print(f"Distinct pattern detected after {seconds} seconds!")
        printGrid(robots)
        if (int)(input("Correct?:")) == 1:
            notCorrectTree = False
    seconds += 1
