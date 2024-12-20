# Day 20 Writeup:
## Languages Used: `Go`
## Part 1:
I did not get much time to solve this question, so as usual I approached my senior <a href="https://github.com/Kirit0me">Kirit0me</a> for help since he ahd already solved the problem for the day I just wanted the algorithm that was required for this problem.

What he suggested was that I read up what <a href="https://xlinux.nist.gov/dads/HTML/manhattanDistance.html">Manhattan Distance</a> was and use that with BFS to figure out the answer.

Therefore it was time to do some digging. I knew that I was already late for this problem, and therefore wanted to try something that was going to be fast and efficient.

I tried some basics codes in Python to see if they would work. I got the first answer <i>(almost)</i>... but it was not working as perfectly as I hoped that it would.

I tried switching to Go to see if there would be something that I could do, so I started to scower the net for clues adnd answers.

Until, I came across <a href="https://topaz.github.io/paste/#XQAAAQBSAgAAAAAAAAAzHIoib6p4r/McpYgEEgWhHoa5LSRMkVi92ASWXgRJn/53WGzJcK4Rqxq0Qyar4BS5DQgYAN35Y8lJcqTY+yjGI8MFLEoYjkrWJOsXQQ76MnCrK/WCLaI4AeJ+YeerS9G3+hr3o9ifx4duubAP4Uk7sw2hyDhgCcbW0Kj9z7VbVmnYfwHz6XYc2QRIo37Uo15C8fWKXBhNKJs2HZ5bp42hQRrBbrt4W+sXf4DqcOSilRg2vmZ8y5kveBOUhixvHzC7WsdlMHWeWs6cY7TPAjPj8vhxVHH5JSlH3Twzs0Dc6xtNZOcdvYt/Vrd6WAJ7h3U9yacAfRUO0phuHaej8oocFxiTf6cp/kZqnE0goF1tuXyF2umof2jgL0oZb6XNcuXlnBs9D9CaTlsxHGvfWSqxAK7Ig5THSUVuZzHPsvHcj2gU2ly4sOehOnTAhoeSDS9UB0T0MvLB6pzIgTYP//TV5gs=">this</a>.

All I tried is tried to implement this into Go, with a method dealing with Manhattan Distance:
```
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
```
One with the regular BFS:
```
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
```
And then there was the main method... In the end, it was very simple to calculate the answer.

## Part 2:
With the previous solution, all that we needed to do was to change from this:
```

				if d == 2 && j-i-d >= 100 {
```
To this:
```

				if d < 21> && j-i-d >= 100 {
```

And that gave us the answer for the second part.

Since I was running late, and I had unfortunately other things to attend to, I couldn't place much time into solving this problem. Nevertheless, I really learnt a lot by solving this problem, which I am pleased with and another two problems have been solved with that.

Thus, with that, I have completed `Day 20` of the `Advent of Code 2024`...<br>
Awaiting for the next day!
