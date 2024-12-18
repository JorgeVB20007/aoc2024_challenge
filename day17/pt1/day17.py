import math

file = open("day17/input.txt", "r")
text = file.read()
file.close()

all_lines = text.split('\n')

print(all_lines)
reg_a = int(all_lines[0][12:])
reg_b = int(all_lines[1][12:])
reg_c = int(all_lines[2][12:])
output = ""

program = [int(x) for x in all_lines[4][9:].split(',')]

print(reg_a)
print(reg_b)
print(reg_c)
print(program)

def adv(reg_a, combo):
	return int(reg_a / (math.pow(2, combo)))

def bxl(reg_b, literal):
	return (reg_b ^ literal)

def bst(combo):
	return (combo % 8)

def jnz(reg_a, literal):
	if reg_a == 0:
		return -1
	else:
		return literal

def bxc(reg_b, reg_c):
	return (reg_b ^reg_c)

def out(combo):
	return (combo % 8)

def bdv(reg_a, combo):
	return int(reg_a / (math.pow(2, combo)))

def cdv(reg_a, combo):
	return int(reg_a / (math.pow(2, combo)))

def get_combo_value(combo):
	literal = combo
	if literal == 4:
		literal = reg_a
	elif literal == 5:
		literal = reg_b
	elif literal == 6:
		literal = reg_c
	return literal

idx = 0
while (idx < len(program)):
	print("idx:", idx, "| ins:", program[idx])
	if program[idx] == 0:		#? adv
		literal = get_combo_value(program[idx + 1])
		reg_a = adv(reg_a, literal)
		idx += 2
	elif program[idx] == 1:		#? bxl
		reg_b = bxl(reg_b, program[idx + 1])
		idx += 2
	elif program[idx] == 2:		#? bst
		reg_b = bst(get_combo_value(program[idx + 1]))
		idx += 2
	elif program[idx] == 3:		#? jnz
		if jnz(reg_a, program[idx + 1]) >= 0:
			idx = jnz(reg_a, program[idx + 1])
		else:
			idx += 2
	elif program[idx] == 4:		#? bxc
		reg_b = bxc(reg_b, reg_c)
		idx += 2
	elif program[idx] == 5:		#? out
		literal = get_combo_value(program[idx + 1])
		if len(output) > 0:
			output = output + ','
		output = output + str(out(literal))
		idx += 2
	elif program[idx] == 6:		#? bdv
		literal = get_combo_value(program[idx + 1])
		reg_b = bdv(reg_a, literal)
		idx += 2
	elif program[idx] == 7:		#? cdv
		literal = get_combo_value(program[idx + 1])
		reg_c = bdv(reg_a, literal)
		idx += 2
	print("A:", reg_a, "| B:", reg_b, "| C:", reg_c, "| OUT:", output)

print(">>>", output)





