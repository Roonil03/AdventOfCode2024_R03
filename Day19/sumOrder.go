package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func parseInput(filename string) (map[string]struct{}, []string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return nil, nil
	}
	defer file.Close()
	var seqs map[string]struct{}
	var towels []string
	seqs = make(map[string]struct{})
	sc := bufio.NewScanner(file)
	readingSeqs := true
	for sc.Scan() {
		line := sc.Text()
		if line == "" {
			readingSeqs = false
			continue
		}
		if readingSeqs {
			seqsSlice := strings.Split(line, ", ")
			for _, seq := range seqsSlice {
				seqs[seq] = struct{}{}
			}
		} else {
			towels = append(towels, line)
		}
	}
	if err := sc.Err(); err != nil {
		fmt.Println("Error reading file:", err)
	}
	return seqs, towels
}

func forward(prefix, word string) string {
	if strings.HasPrefix(word, prefix) {
		return word[len(prefix):]
	}
	return word
}

func checkTowel(t string, seqs map[string]struct{}, memo map[string]int) int {
	if len(t) == 0 {
		return 1
	}
	if val, found := memo[t]; found {
		return val
	}
	res := 0
	for seq := range seqs {
		if strings.HasPrefix(t, seq) {
			res += checkTowel(forward(seq, t), seqs, memo)
		}
	}
	memo[t] = res
	return res
}

func desiredPatterns(towels []string, seqs map[string]struct{}) int {
	memo := make(map[string]int)
	count := 0
	for _, t := range towels {
		count += checkTowel(t, seqs, memo)
	}
	return count
}

func main() {
	// filename := "Day19/test19.txt"
	filename := "day19/input19.txt"
	seqs, towels := parseInput(filename)
	fmt.Println(desiredPatterns(towels, seqs))
}
