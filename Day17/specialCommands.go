package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Computer struct {
	regA   int
	regB   int
	regC   int
	ip     int
	output []string
}

func (c *Computer) execute(program []int) {
	for c.ip < len(program) {
		opcode := program[c.ip]
		operand := program[c.ip+1]

		switch opcode {
		case 0: // adv
			denominator := intPow(2, c.getComboOperand(operand))
			if denominator != 0 {
				c.regA = c.regA / denominator
			}
		case 1: // bxl
			c.regB = c.regB ^ operand
		case 2: // bst
			c.regB = c.getComboOperand(operand) % 8
		case 3: // jnz
			if c.regA != 0 {
				c.ip = operand
				continue
			}
		case 4: // bxc
			c.regB = c.regB ^ c.regC
		case 5: // out
			outVal := c.getComboOperand(operand) % 8
			c.output = append(c.output, strconv.Itoa(outVal))
		case 6: // bdv
			denominator := intPow(2, c.getComboOperand(operand))
			if denominator != 0 {
				c.regB = c.regA / denominator
			}
		case 7: // cdv
			denominator := intPow(2, c.getComboOperand(operand))
			if denominator != 0 {
				c.regC = c.regA / denominator
			}
		default:
			return
		}
		c.ip += 2
	}
}

func (c *Computer) getComboOperand(operand int) int {
	switch operand {
	case 4:
		return c.regA
	case 5:
		return c.regB
	case 6:
		return c.regC
	default:
		return operand
	}
}

func intPow(base, exp int) int {
	result := 1
	for i := 0; i < exp; i++ {
		result *= base
	}
	return result
}

func readInputFile(filename string) (int, int, int, []int) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		os.Exit(1)
	}
	defer file.Close()
	var regA, regB, regC int
	var program []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if strings.HasPrefix(line, "Register A:") {
			regA = parseRegisterValue(line)
		} else if strings.HasPrefix(line, "Register B:") {
			regB = parseRegisterValue(line)
		} else if strings.HasPrefix(line, "Register C:") {
			regC = parseRegisterValue(line)
		} else if strings.HasPrefix(line, "Program:") {
			program = parseProgram(line)
		}
	}
	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		os.Exit(1)
	}

	return regA, regB, regC, program
}

func parseRegisterValue(line string) int {
	parts := strings.Split(line, ":")
	value, err := strconv.Atoi(strings.TrimSpace(parts[1]))
	if err != nil {
		fmt.Println("Error parsing register value:", err)
		os.Exit(1)
	}
	return value
}

func parseProgram(line string) []int {
	parts := strings.Split(line, ":")
	numStrs := strings.Split(strings.TrimSpace(parts[1]), ",")
	var program []int
	for _, numStr := range numStrs {
		num, err := strconv.Atoi(strings.TrimSpace(numStr))
		if err != nil {
			fmt.Println("Error parsing program value:", err)
			os.Exit(1)
		}
		program = append(program, num)
	}
	return program
}

func main() {
	// filename := "Day17/test17.txt"
	filename := "Day17/input17.txt"
	regA, regB, regC, program := readInputFile(filename)
	computer := &Computer{
		regA: regA,
		regB: regB,
		regC: regC,
		ip:   0,
	}
	computer.execute(program)
	fmt.Println(strings.Join(computer.output, ","))
}
