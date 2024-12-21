package main

import (
	"bufio"
	"fmt"
	"os"
)

type Point complex128

func manhattanDist(a, b Point) int {
	dx := int(real(a) - real(b))
	dy := int(imag(a) - imag(b))
	if dx < 0 {
		dx = -dx
	}
	if dy < 0 {
		dy = -dy
	}
	return dx + dy
}

func bfs(grid map[Point]rune, start Point) map[Point]int {
	dist := map[Point]int{start: 0}
	todo := []Point{start}
	for len(todo) > 0 {
		pos := todo[0]
		todo = todo[1:]
		for _, d := range []Point{-1, 1, -1i, 1i} {
			newPos := pos + d
			if _, ok := grid[newPos]; ok {
				if _, visited := dist[newPos]; !visited {
					dist[newPos] = dist[pos] + 1
					todo = append(todo, newPos)
				}
			}
		}
	}
	return dist
}

func main() {
	filename := "Day20/input20.txt"
	// filename := "Day20/test20.txt"
	f, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer f.Close()
	grid := make(map[Point]rune)
	var start Point
	sc := bufio.NewScanner(f)
	for y := 0; sc.Scan(); y++ {
		line := sc.Text()
		for x, char := range line {
			if char != '#' {
				pos := Point(complex(float64(x), float64(y)))
				grid[pos] = char
				if char == 'S' {
					start = pos
				}
			}
		}
	}
	if err := sc.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
	dist := bfs(grid, start)
	a := 0
	for p1, i := range dist {
		for p2, j := range dist {
			if p1 != p2 {
				d := manhattanDist(p1, p2)
				if d < 21 && j-i-d >= 100 {
					a++
				}
			}
		}
	}
	fmt.Println(a)
}
