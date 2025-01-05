file = open("day24/input.txt", "r")
text = file.read()
file.close()

values_and_ops = text.split("\n\n")
initial_values_lines = values_and_ops[0].split("\n")
initial_ops_lines = values_and_ops[1].split("\n")

ops_list = []

for op in initial_ops_lines:
	splitop = op.split(" ")
	op_dict = {}
	op_dict["first"] = splitop[0]
	op_dict["operation"] = splitop[1]
	op_dict["second"] = splitop[2]
	op_dict["result"] = splitop[4]
	ops_list.append(op_dict)


def get_full_operations_by_operands(operand: str) -> list:
	result = []
	for curr in ops_list:
		if curr["first"] == operand or curr["second"] == operand:
			result.append(curr)
	return result


def find_sus_operations():
	result = []
	for op in ops_list:
		if op["result"][0] == 'z':
			if op["operation"] != 'XOR' and op["result"][1:] != '45':
				result.append(op["result"])
		elif not (op["first"][0] == 'x' or op["first"][0] == 'y'):
			if op["operation"] == "XOR":
				result.append(op["result"])
		elif op["operation"] == "XOR" and op["first"] != 'x00' and op["first"] != 'y00':
			next_options = get_full_operations_by_operands(op["result"])
			possible = False
			for optn in next_options:
				if optn["operation"] == "XOR":
					possible = True
			if not possible:
				result.append(op["result"])
		elif op["operation"] == "AND" and op["first"] != 'x00' and op["first"] != 'y00':
			next_options = get_full_operations_by_operands(op["result"])
			possible = False
			for optn in next_options:
				if optn["operation"] == "OR":
					possible = True
			if not possible:
				result.append(op["result"])


	result.sort()
	resultstr = ""
	for x in result:
		resultstr = resultstr + x + ','
	resultstr = resultstr[:-1]
	print(">>>", resultstr)

find_sus_operations()