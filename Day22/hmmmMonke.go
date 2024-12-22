package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func readLinesToList(filename string) []int {
	var lines []int
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return nil
	}
	defer file.Close()
	sc := bufio.NewScanner(file)
	for sc.Scan() {
		line := strings.TrimSpace(sc.Text())
		if num, err := strconv.Atoi(line); err == nil {
			lines = append(lines, num)
		}
	}
	if err := sc.Err(); err != nil {
		fmt.Println("Error reading file:", err)
	}
	return lines
}

func mix(value, secret int) int {
	return value ^ secret
}

func prune(secret int) int {
	return secret % 16777216
}

func evolve(secret int) int {
	s1 := secret * 64
	s1 = mix(s1, secret)
	s1 = prune(s1)
	s2 := s1 / 32
	s2 = mix(s1, s2)
	s2 = prune(s2)
	s3 := s2 * 2048
	s3 = mix(s2, s3)
	s3 = prune(s3)
	return s3
}

func monke(filename string) {
	lines := readLinesToList(filename)
	var seqs []map[[4]int]int
	for _, line := range lines {
		prices := []int{}
		curr := line
		for i := 0; i < 2000; i++ {
			prices = append(prices, curr%10)
			curr = evolve(curr)
		}
		del := []int{}
		for i := 1; i < len(prices); i++ {
			a := prices[i-1]
			b := prices[i]
			del = append(del, b-a)
		}
		sqs := make(map[[4]int]int)
		for i := 4; i < len(del); i++ {
			changes := [4]int{del[i-4], del[i-3], del[i-2], del[i-1]}
			if _, exists := sqs[changes]; !exists {
				sqs[changes] = prices[i]
			}
		}
		seqs = append(seqs, sqs)
	}
	toTest := []map[[4]int]int{}
	for _, seq := range seqs {
		for k := range seq {
			toTest = append(toTest, map[[4]int]int{k: seq[k]})
		}
	}
	bestScore := 0
	for _, sequence := range toTest {
		for candidate := range sequence {
			total := 0
			for _, seq := range seqs {
				if price, exists := seq[candidate]; exists {
					total += price
				}
			}
			if total > bestScore {
				bestScore = total
			}
		}
	}
	fmt.Printf("Best Score: %d\n", bestScore)
}

func main() {
	filename := "Day22/input22.txt"
	// filename := "Day22/test22.txt"
	monke(filename)
}
