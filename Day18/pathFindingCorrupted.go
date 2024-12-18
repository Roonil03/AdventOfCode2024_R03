package main

import (
	"bufio"
	"container/list"
	"fmt"
	"os"
	"strings"
)

func main() {
	gridSize := 71
	endX, endY := 70, 70
	corruptedTaken := 1024
	corrupted := make(map[[2]int]bool)
	// filename := "Day18/test18.txt"
	filename := "Day18/input18.txt"
	file, _ := os.Open(filename)
	defer file.Close()
	sc := bufio.NewScanner(file)
	count := 0

	for sc.Scan() && count < corruptedTaken {
		line := strings.Split(sc.Text(), ",")
		x := atoi(line[0])
		y := atoi(line[1])
		corrupted[[2]int{x, y}] = true
		count++
	}

	dir := [][2]int{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
	queue := list.New()
	queue.PushBack([2]int{0, 0})
	visited := make(map[[2]int]bool)
	visited[[2]int{0, 0}] = true
	dist := 0

	for queue.Len() > 0 {
		size := queue.Len()
		for i := 0; i < size; i++ {
			curr := queue.Remove(queue.Front()).([2]int)
			x, y := curr[0], curr[1]
			if x == endX && y == endY {
				fmt.Println(dist)
				return
			}
			for _, d := range dir {
				newX, newY := x+d[0], y+d[1]
				if newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize && !corrupted[[2]int{newX, newY}] && !visited[[2]int{newX, newY}] {
					visited[[2]int{newX, newY}] = true
					queue.PushBack([2]int{newX, newY})
				}
			}
		}
		dist++
	}

	fmt.Println(-1)
}

func atoi(s string) int {
	result := 0
	for i := 0; i < len(s); i++ {
		result = result*10 + int(s[i]-'0')
	}
	return result
}
