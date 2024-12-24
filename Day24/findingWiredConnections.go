package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

type node struct {
	op    string
	left  string
	right string
}

func parseInput(lines []string) (map[string]int, map[string]node) {
	vals := make(map[string]int)
	exp := make(map[string]node)
	for _, line := range lines {
		parts := strings.Split(line, " ")
		if len(parts) == 2 {
			key := strings.TrimSuffix(parts[0], ":")
			val, _ := strconv.Atoi(parts[1])
			vals[key] = val
		} else if len(parts) == 5 {
			exp[parts[4]] = node{op: parts[1], left: parts[0], right: parts[2]}
		}
	}
	return vals, exp
}

func evaluate(exprs map[string]node, values map[string]int, varName string) int {
	if val, exists := values[varName]; exists {
		return val
	}
	expr, exists := exprs[varName]
	if !exists {
		panic("Undefined variable: " + varName)
	}
	left := evaluate(exprs, values, expr.left)
	right := evaluate(exprs, values, expr.right)
	var result int
	switch expr.op {
	case "AND":
		result = left & right
	case "OR":
		result = left | right
	case "XOR":
		result = left ^ right
	default:
		panic("Unknown operator: " + expr.op)
	}
	values[varName] = result
	return result
}

func main() {
	// filename := "Day24/test24.txt"
	filename := "day24/input24.txt"
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
	defer file.Close()
	sc := bufio.NewScanner(file)
	var lines []string
	for sc.Scan() {
		lines = append(lines, sc.Text())
	}
	values, expressions := parseInput(lines)
	var zVars []string
	for key := range expressions {
		if strings.HasPrefix(key, "z") {
			zVars = append(zVars, key)
		}
	}
	sort.Slice(zVars, func(i, j int) bool {
		zi, _ := strconv.Atoi(strings.TrimPrefix(zVars[i], "z"))
		zj, _ := strconv.Atoi(strings.TrimPrefix(zVars[j], "z"))
		return zi < zj
	})
	var binaryString strings.Builder
	fmt.Println("z Variables (sorted) and their Values:")
	for _, zVar := range zVars {
		bit := evaluate(expressions, values, zVar)
		fmt.Printf("%s: %d\n", zVar, bit)
		binaryString.WriteString(strconv.Itoa(bit))
	}
	binaryStr := binaryString.String()
	binaryStr = reverseString(binaryStr)
	result, err := strconv.ParseInt(binaryStr, 2, 64)
	if err != nil {
		fmt.Println("Error converting binary to number:", err)
		return
	}
	fmt.Println("Binary String:", binaryStr)
	fmt.Println("Result:", result)
}

func reverseString(s string) string {
	runes := []rune(s)
	n := len(runes)
	for i := 0; i < n/2; i++ {
		runes[i], runes[n-1-i] = runes[n-1-i], runes[i]
	}
	return string(runes)
}
