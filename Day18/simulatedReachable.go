package main

import (
	"fmt"
	"image"
	"os"
	"strings"
)

func main() {
	gridSize := 70
	inputData, _ := os.ReadFile("Day18/input18.txt")
	corruptedPoints := parseCorruptedPoints(inputData)
	grid := createGrid(gridSize)
	processCorruptedSpots(grid, corruptedPoints, gridSize)
}

func parseCorruptedPoints(data []byte) []image.Point {
	var points []image.Point
	for _, entry := range strings.Fields(string(data)) {
		var x, y int
		fmt.Sscanf(entry, "%d,%d", &x, &y)
		points = append(points, image.Point{x, y})
	}
	return points
}

func createGrid(size int) map[image.Point]bool {
	grid := make(map[image.Point]bool)
	for y := 0; y <= size; y++ {
		for x := 0; x <= size; x++ {
			grid[image.Point{x, y}] = true
		}
	}
	return grid
}

func processCorruptedSpots(grid map[image.Point]bool, corruptedPoints []image.Point, gridSize int) {
loop:
	for b := range corruptedPoints {
		grid[corruptedPoints[b]] = false
		queue := []image.Point{{0, 0}}
		distances := map[image.Point]int{{0, 0}: 0}

		for len(queue) > 0 {
			current := queue[0]
			queue = queue[1:]
			if current == (image.Point{gridSize, gridSize}) {
				continue loop
			}
			for _, direction := range []image.Point{{0, -1}, {1, 0}, {0, 1}, {-1, 0}} {
				next := current.Add(direction)
				if _, visited := distances[next]; !visited && grid[next] {
					queue = append(queue, next)
					distances[next] = distances[current] + 1
				}
			}
		}
		fmt.Printf("%d,%d\n", corruptedPoints[b].X, corruptedPoints[b].Y)
		break
	}
}
