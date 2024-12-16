package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"math"
	"os"
)

type Point struct {
	x, y int
}

type Move struct {
	point Point
	dir   int
}

type PriorityQueue []Move

func (pq *PriorityQueue) Len() int {
	return len(*pq)
}

func (pq *PriorityQueue) Less(i, j int) bool {
	return dist[(*pq)[i].point.y][(*pq)[i].point.x] < dist[(*pq)[j].point.y][(*pq)[j].point.x]
}

func (pq *PriorityQueue) Swap(i, j int) {
	(*pq)[i], (*pq)[j] = (*pq)[j], (*pq)[i]
}

func (pq *PriorityQueue) Push(x interface{}) {
	*pq = append(*pq, x.(Move))
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}

var directions = []Point{
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1},
}

var dist [][]int
var prev [][]Point

const INF = math.MaxInt

func readMaze(filename string) ([][]rune, Point, Point, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, Point{}, Point{}, err
	}
	defer file.Close()
	var maze [][]rune
	var start, end Point
	sc := bufio.NewScanner(file)
	for y := 0; sc.Scan(); y++ {
		line := sc.Text()
		maze = append(maze, []rune(line))
		for x, c := range line {
			if c == 'S' {
				start = Point{x, y}
			} else if c == 'E' {
				end = Point{x, y}
			}
		}
	}
	if err := sc.Err(); err != nil {
		return nil, Point{}, Point{}, err
	}
	return maze, start, end, nil
}

func isValid(maze [][]rune, p Point) bool {
	return p.y >= 0 && p.y < len(maze) && p.x >= 0 && p.x < len(maze[0]) && maze[p.y][p.x] != '#'
}

func dijkstra(maze [][]rune, start, end Point) int {
	rows, cols := len(maze), len(maze[0])
	dist = make([][]int, rows)
	prev = make([][]Point, rows)
	for i := range dist {
		dist[i] = make([]int, cols)
		prev[i] = make([]Point, cols)
		for j := range dist[i] {
			dist[i][j] = INF
		}
	}
	dist[start.y][start.x] = 0
	pq := &PriorityQueue{}
	heap.Push(pq, Move{point: start, dir: -1})
	for pq.Len() > 0 {
		curMove := heap.Pop(pq).(Move)
		curPoint, curDir := curMove.point, curMove.dir
		if curPoint == end {
			printPath(end)
			return dist[curPoint.y][curPoint.x]
		}
		for newDir, direction := range directions {
			newPoint := Point{curPoint.x + direction.x, curPoint.y + direction.y}
			if !isValid(maze, newPoint) {
				continue
			}
			turnCost := 0
			if curDir != -1 && newDir != curDir {
				turnCost = 1000
			}
			newDist := dist[curPoint.y][curPoint.x] + 1 + turnCost
			if newDist < dist[newPoint.y][newPoint.x] {
				dist[newPoint.y][newPoint.x] = newDist
				prev[newPoint.y][newPoint.x] = curPoint
				heap.Push(pq, Move{point: newPoint, dir: newDir})
			}
		}
	}
	return -1
}

func printPath(end Point) {
	path := []Point{}
	for p := end; p != (Point{}); p = prev[p.y][p.x] {
		path = append([]Point{p}, path...)
	}
	fmt.Println("Path taken:")
	for _, p := range path {
		fmt.Printf("(%d, %d) -> ", p.x, p.y)
	}
	fmt.Println("End")
}

func main() {
	filename := "Day16/input16.txt"
	// filename := "Day16/test16.txt"
	maze, start, end, err := readMaze(filename)
	if err != nil {
		fmt.Println("Error reading maze:", err)
		return
	}

	result := dijkstra(maze, start, end)
	if result == -1 {
		fmt.Println("No path found")
	} else {
		fmt.Printf("The lowest score to reach the end is: %d\n", (result + 1000))
	}
}
