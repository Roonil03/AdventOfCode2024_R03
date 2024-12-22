package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	// filename := "Day22/test22.txt"
	filename := "Day22/input22.txt"
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()
	var secrets []uint64
	sc := bufio.NewScanner(file)
	for sc.Scan() {
		line := strings.TrimSpace(sc.Text())
		if num, err := strconv.Atoi(line); err == nil {
			secrets = append(secrets, uint64(num))
		}
	}
	if err := sc.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
	var total uint64 = 0
	for _, s := range secrets {
		for i := 0; i < 2000; i++ {
			s = (s * 64) ^ s
			s = s % 16777216
			s = (s / 32) ^ s
			s = s % 16777216
			s = (s * 2048) ^ s
			s = s % 16777216
		}
		total += s
		//fmt.Println(s)
	}
	fmt.Println(total)
}
