import math

file = open("day17/input.txt", "r")
text = file.read()
file.close()

all_lines = text.split('\n')

reg_a = int(all_lines[0][12:])
reg_b = int(all_lines[1][12:])
reg_c = int(all_lines[2][12:])
output = []

program = [int(x) for x in all_lines[4][9:].split(',')]

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

result = 0
is_first = True

for currprogram_idx in range(1, len(program) + 1):
	currprogram = program[-currprogram_idx:]
	for currnum in range(0, 9):
		output = []
		if is_first:
			currnum += 3
		reg_a = currnum + result * 8
		reg_b = 0
		reg_c = 0
		idx = 0
		is_first = False
		while (idx < len(program)):
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
					break
			elif program[idx] == 4:		#? bxc
				reg_b = bxc(reg_b, reg_c)
				idx += 2
			elif program[idx] == 5:		#? out
				literal = get_combo_value(program[idx + 1])
				output.append(out(literal))
				idx += 2
			elif program[idx] == 6:		#? bdv
				literal = get_combo_value(program[idx + 1])
				reg_b = bdv(reg_a, literal)
				idx += 2
			elif program[idx] == 7:		#? cdv
				literal = get_combo_value(program[idx + 1])
				reg_c = bdv(reg_a, literal)
				idx += 2
		if (currprogram == output):
			result = result * 8 + currnum
			break


print(">>>", result)





