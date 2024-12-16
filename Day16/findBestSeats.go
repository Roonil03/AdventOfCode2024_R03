package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

const dirs = 4

var dRow = []int{-1, 0, 1, 0}

var dCol = []int{0, -1, 0, 1}

var oo = math.MaxInt / 4

type Coord struct {
	row, col, dir int
}

var q []Coord

var maze [][]rune

var d, p [][][]int

var vis [][]int

var start, end Coord

func add(v Coord, dist, prev int) {
	if maze[v.row][v.col] == '#' {
		return
	}
	if d[v.row][v.col][v.dir] > dist {
		q = append(q, v)
		d[v.row][v.col][v.dir] = dist
		p[v.row][v.col][v.dir] = 0
	}
	if d[v.row][v.col][v.dir] == dist {
		p[v.row][v.col][v.dir] |= 1 << prev
	}
}

func rem() Coord {
	v := q[0]
	q = q[1:]
	return v
}

func add2(v Coord) {
	if vis[v.row][v.col]&(1<<v.dir) > 0 {
		return
	}
	vis[v.row][v.col] |= 1 << v.dir
	q = append(q, v)
}

func main() {
	filename := "Day16/input16.txt"
	// filename := "Day16/test16.txt"
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
	defer file.Close()
	sc := bufio.NewScanner(file)
	for row := 0; sc.Scan(); row++ {
		line := sc.Text()
		maze = append(maze, []rune(line))
		for col, c := range line {
			if c == 'S' {
				start = Coord{row, col, 3}
				maze[row][col] = '.'
			}
			if c == 'E' {
				end = Coord{row, col, dirs}
				maze[row][col] = '.'
			}
		}
	}
	d = make([][][]int, len(maze))
	p = make([][][]int, len(maze))
	for i := range d {
		d[i] = make([][]int, len(maze[i]))
		p[i] = make([][]int, len(maze[i]))
		for j := range d[i] {
			d[i][j] = make([]int, dirs)
			p[i][j] = make([]int, dirs)
			for k := range d[i][j] {
				d[i][j][k] = oo
			}
		}
	}
	add(start, 0, dirs)
	for len(q) > 0 {
		c := rem()
		dist := d[c.row][c.col][c.dir]
		add(Coord{c.row + dRow[c.dir], c.col + dCol[c.dir], c.dir}, dist+1, c.dir)
		add(Coord{c.row, c.col, (c.dir + 1) % dirs}, dist+1000, c.dir)
		add(Coord{c.row, c.col, (c.dir + dirs - 1) % dirs}, dist+1000, c.dir)
	}
	vis = make([][]int, len(maze))
	for i := range vis {
		vis[i] = make([]int, len(maze[i]))
	}
	best := oo
	for dir := 0; dir < dirs; dir++ {
		if d[end.row][end.col][dir] < best {
			best = d[end.row][end.col][dir]
		}
	}
	for dir := 0; dir < dirs; dir++ {
		if d[end.row][end.col][dir] == best {
			add2(Coord{end.row, end.col, dir})
		}
	}
	for len(q) > 0 {
		c := rem()
		for dir := 0; dir < dirs; dir++ {
			if p[c.row][c.col][c.dir]&(1<<dir) > 0 {
				add2(Coord{c.row - dRow[dir], c.col - dCol[dir], dir})
			}
		}
	}
	count := 0
	for i := 0; i < len(maze); i++ {
		for j := 0; j < len(maze[i]); j++ {
			if vis[i][j] > 0 {
				count++
			}
		}
	}
	fmt.Printf("The number of tiles is: %d\n", (count - 1))
}
