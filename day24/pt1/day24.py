file = open("day24/input.txt", "r")
text = file.read()
file.close()

values_and_ops = text.split("\n\n")
initial_values_lines = values_and_ops[0].split("\n")
initial_ops_lines = values_and_ops[1].split("\n")




values_dict = {}
for value in initial_values_lines:
	splitvalue = value.split(": ")
	values_dict[splitvalue[0]] = int(splitvalue[1])


ops_list = []

for op in initial_ops_lines:
	splitop = op.split(" ")
	op_dict = {}
	op_dict["first"] = splitop[0]
	op_dict["operation"] = splitop[1]
	op_dict["second"] = splitop[2]
	op_dict["result"] = splitop[4]
	ops_list.append(op_dict)
# print(ops_list)

everything_solved = False
while not everything_solved:
	everything_solved = True
	for op in ops_list:
		if op["first"] in values_dict and op["second"] in values_dict:
			this_result = 0
			if op["operation"] == 'AND':
				result = int(bool(values_dict[op["first"]]) and bool(values_dict[op["second"]]))
			elif op["operation"] == 'XOR':
				result = int(values_dict[op["first"]] != values_dict[op["second"]])
			else:
				result = int(bool(values_dict[op["first"]]) or bool(values_dict[op["second"]]))
			values_dict[op["result"]] = result
		else:
			everything_solved = False

# print(values_dict)


final_zs = []
for idx in values_dict:
	if idx[0] == 'z':
		final_zs.append((idx, values_dict[idx]))

final_zs.sort()
final_zs.reverse()


result = 0
for idx in final_zs:
	result *= 2
	result += idx[1]


print(">>>", result)








