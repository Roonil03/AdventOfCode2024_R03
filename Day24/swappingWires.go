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

func getSwappedWires(exp map[string]node, vals map[string]int) []string {
	swapped := []string{}
	carry := ""
	returns := func(a, b, op string) string {
		for key, e := range exp {
			if ((e.left == a && e.right == b) || (e.left == b && e.right == a)) && e.op == op {
				return key
			}
		}
		return ""
	}
	countZ := 0
	for key := range exp {
		if strings.HasPrefix(key, "z") {
			countZ++
		}
	}

	for i := 0; i < countZ-1; i++ {
		sum := returns(fmt.Sprintf("x%02d", i), fmt.Sprintf("y%02d", i), "XOR")
		carry1 := returns(fmt.Sprintf("x%02d", i), fmt.Sprintf("y%02d", i), "AND")
		var sum2 string
		if carry != "" {
			carry2 := returns(carry, sum, "AND")
			if carry2 == "" {
				sum, carry1 = carry1, sum
				swapped = append(swapped, sum, carry1)
				carry2 = returns(carry, sum, "AND")
			}
			sum2 = returns(carry, sum, "XOR")
			if sum != "" && strings.HasPrefix(sum, "z") {
				sum, sum2 = sum2, sum
				swapped = append(swapped, sum, sum2)
			}
			if carry1 != "" && strings.HasPrefix(carry1, "z") {
				carry1, sum2 = sum2, carry1
				swapped = append(swapped, carry1, sum2)
			}
			if carry2 != "" && strings.HasPrefix(carry2, "z") {
				carry2, sum2 = sum2, carry2
				swapped = append(swapped, carry2, sum2)
			}
			carry = returns(carry2, carry1, "OR")
		} else {
			carry = carry1
		}
		if carry != "" && strings.HasPrefix(carry, "z") && carry != fmt.Sprintf("z%02d", countZ-1) {
			carry, sum2 = sum2, carry
			swapped = append(swapped, carry, sum2)
		}
	}
	return swapped
}

func evaluate(exp map[string]node, vals map[string]int, varName string) int {
	if val, exists := vals[varName]; exists {
		return val
	}
	e, exists := exp[varName]
	if !exists {
		panic("Undefined variable: " + varName)
	}
	left := evaluate(exp, vals, e.left)
	right := evaluate(exp, vals, e.right)
	var result int
	switch e.op {
	case "AND":
		result = left & right
	case "OR":
		result = left | right
	case "XOR":
		result = left ^ right
	default:
		panic("Unknown operator: " + e.op)
	}
	vals[varName] = result
	return result
}

func main() {
	// filename := "day24/test24.txt"
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
	vals, exp := parseInput(lines)
	swapped := getSwappedWires(exp, vals)
	sort.Strings(swapped)
	fmt.Println("Swapped wires:")
	for _, sw := range swapped {
		fmt.Print(sw, ", ")
	}
	var bStr strings.Builder
	fmt.Println("\nz Variables (sorted) and their Values:")
	for _, zVar := range swapped {
		bit := evaluate(exp, vals, zVar)
		fmt.Printf("%s: %d\n", zVar, bit)
		bStr.WriteString(strconv.Itoa(bit))
	}
	binaryStr := bStr.String()
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
