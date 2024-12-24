# Day 24 Writeup:
## Part 1:
``In the words of OpenAI's ChatGPT talking from a first person's perspective:``
<i>In the above Go program, I parse input from a file to evaluate bitwise expressions involving variables. The parseInput function reads lines, categorizing them into either variable-value pairs or expressions with operations like "`AND`", "`OR`", and "`XOR`". I store these in two maps: one for direct values and the other for expressions. The evaluate function recursively computes the result of an expression, resolving each variable until it reaches a base value. The program then identifies variables starting with '`z`' and sorts them, as shown in this snippet:
```
var zVars []string
for key := range expressions {
    if strings.HasPrefix(key, "z") {
        zVars = append(zVars, key)
    }
}
```
It constructs a binary string from the results of evaluating these '`z`' variables, reverses the string, and converts it to an integer. Finally, the program prints the binary string and its corresponding integer value:
```
binaryStr = reverseString(binaryStr)
result, err := strconv.ParseInt(binaryStr, 2, 64)
```
</i>

## Part 2:
``Similarly for this one:``<br>
<i>
In the Go program above, I parse input from a file to evaluate bitwise expressions, with a focus on determining swapped wires. The parseInput function reads lines of input and categorizes them into direct variable assignments and operations involving "`AND`", "`OR`", and "`XOR`". These are stored in two maps: one for values and another for expressions. The getSwappedWires function identifies and swaps variables based on a carry propagation logic. The swapped wires are sorted and printed:
```
swapped := getSwappedWires(exp, vals)
sort.Strings(swapped)
fmt.Println("Swapped wires:")
for _, sw := range swapped {
    fmt.Print(sw, ", ")
}
```
The program then evaluates the values of '`z`' variables, constructs a binary string, and reverses it to compute the final result. This is done through the evaluate function, which recursively resolves expressions:
```
bit := evaluate(exp, vals, zVar)
bStr.WriteString(strconv.Itoa(bit))
```
Finally, the binary string is converted to a number, and both the binary string and the result are printed.</i>

And thus, with being tired, I have completed yet another two challenges for this day.

With that, i have done ``Day 24`` of the ``Advent of Code 2024``...<br>
Now time to wait for the last day...




