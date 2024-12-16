# Day 16 Writeup:
## Languages Used: `Go`
## Part 1:
I could see that this was a simple Djikstra's algorithm. Therefore, I decided to do today's problems in a new language that I am trying to learn.

Using the help of the net for information on different strcutures and such, I created the rough layout script of how the Djikstra's algorithm would work:
```
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
```
When I tried out the test, it was coming a 1000 less than the actual answer.

After running the second test, I realized that it was infact not accounting for a singular turn. Thus to make sure that I account for that one turn, I just simply added that to the result before printing it...

## Part 2:
Here, I could see that we will need to use a combination of a graph traversal to check and see all the shortest paths that are present as well as we need to keep marking those points which are part of the shortest path and to make sure to remove those which are part of the path.

Thus, I chose to stick with BFS, since I have done previous challenges in this event in BFS as well and this is what I went with:
```
for len(q) > 0 {
    c := rem()
    dist := d[c.row][c.col][c.dir]
    add(Coord{c.row + dRow[c.dir], c.col + dCol[c.dir], c.dir}, dist+1, c.dir)
    add(Coord{c.row, c.col, (c.dir + 1) % dirs}, dist+1000, c.dir)
    add(Coord{c.row, c.col, (c.dir + dirs - 1) % dirs}, dist+1000, c.dir)
}
```
With that, I ran the tests to see if the results were coming appropriately and giving me the answer... which I did, completing the two challenges for the day.

Thus, with this I conclude ``Day 16`` of the ``Advent of Code 2024``...<br>
Looking to the next day's challenge!