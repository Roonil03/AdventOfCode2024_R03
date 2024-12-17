import copy

with open('Day17/input17.txt') as f:
    registers_data, instructions_data = f.read().split('\n\n')

initial_registers = {
    line.split(': ')[0].split()[1]: int(line.split(': ')[1]) 
    for line in registers_data.splitlines()
}

instructions = [
    int(value) for value in instructions_data.replace('\n', '').split()[1].split(',')
]

def get_operand_value(operand, registers):
    if operand <= 3:
        return operand
    elif operand == 4:
        return registers['A']
    elif operand == 5:
        return registers['B']
    elif operand == 6:
        return registers['C']

def divide_register_a(operand, registers, pointer, outputs):
    registers['A'] //= (2 ** get_operand_value(operand, registers))
    return registers, pointer + 2, outputs

def xor_register_b_with_constant(operand, registers, pointer, outputs):
    registers['B'] ^= operand
    return registers, pointer + 2, outputs

def mod_register_b(operand, registers, pointer, outputs):
    registers['B'] = get_operand_value(operand, registers) % 8
    return registers, pointer + 2, outputs

def jump_if_not_zero(operand, registers, pointer, outputs):
    if registers['A'] == 0:
        return registers, pointer + 2, outputs
    else:
        return registers, operand, outputs

def xor_register_b_with_c(operand, registers, pointer, outputs):
    registers['B'] ^= registers['C']
    return registers, pointer + 2, outputs

def add_output(operand, registers, pointer, outputs):
    outputs.append(get_operand_value(operand, registers) % 8)
    return registers, pointer + 2, outputs

def divide_register_b_by_a(operand, registers, pointer, outputs):
    registers['B'] = registers['A'] // (2 ** get_operand_value(operand, registers))
    return registers, pointer + 2, outputs

def divide_register_c_by_a(operand, registers, pointer, outputs):
    registers['C'] = registers['A'] // (2 ** get_operand_value(operand, registers))
    return registers, pointer + 2, outputs

def simulate_program(start_value):
    outputs = []
    registers = copy.deepcopy(initial_registers)
    registers['A'] = start_value
    instruction_pointer = 0
    program_length = len(instructions)

    while instruction_pointer in range(program_length):
        opcode = instructions[instruction_pointer]
        operation = [
            divide_register_a, xor_register_b_with_constant, mod_register_b, 
            jump_if_not_zero, xor_register_b_with_c, add_output, 
            divide_register_b_by_a, divide_register_c_by_a
        ][opcode]
        operand = instructions[instruction_pointer + 1]
        registers, instruction_pointer, outputs = operation(operand, registers, instruction_pointer, outputs)
    return outputs

valid_values = [0]
for instruction_length in range(1, len(instructions) + 1):
    previous_valid_values = valid_values
    valid_values = []
    for base_value in previous_valid_values:
        for offset in range(8):
            candidate_value = 8 * base_value + offset
            if simulate_program(candidate_value) == instructions[-instruction_length:]:
                valid_values.append(candidate_value)

result = min(valid_values)
print(result)
