# Day 18 Writeup:
## Languages Used: `Go`
## Part 1:
This problem really made me think about how easy sometimes problems can be. It was a pathfinding algorithm that required us to find the shortest path to a particular end point. So I just used BFS to find the shortest path after all the points had to been put down:
```
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
```
With this, I easily got the number of tiles that it was covering and the answer came.

## Part 2:
This part took me some time to just understand how the question works. After that, it was just a case of altering the BFS to make sure to find the point where the path to the exit is just completely just blocked.<br>
Since there were limited graph space, I thought might as well try and brute force using BFS, and that easily got me the answer as well for this question.
This time, I tried to spice things up by using a different approach, and went with the image package.

Thus, with that, I have completed two more challenges for the day...

With that I conclude `Day 18` of the `Advent of Code 2024`...<br>
Waiting for the next day's challenge!