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


expected_result = 0

xs = []
ys = []
for xy in values_dict:
	if xy[0] == 'x':
		xs.append((xy, values_dict[xy]))
	elif xy[0] == 'y':
		ys.append((xy, values_dict[xy]))
xs.sort()
xs.reverse()
ys.sort()
ys.reverse()

xval = 0
for x in xs:
	xval *= 2
	xval += x[1]
yval = 0
for y in ys:
	yval *= 2
	yval += y[1]

print(xval)
print(yval)
zval = xval + yval
print(zval)

zval_bin = []
while zval > 0:
	zval_bin.insert(0, zval % 2)
	zval = int((zval - zval % 2) / 2)

expected_zs = {}
for idx in range(0, len(zval_bin)):
	expected_zs["z{:0>2}".format(idx)] = zval_bin[len(zval_bin) - idx - 1]



print(expected_zs)


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

for z in range(len(final_zs)):
	print(str(z) + ':', final_zs[z], expected_zs["z{:0>2}".format(z)])
final_zs.reverse()

result = 0
for idx in final_zs:
	result *= 2
	result += idx[1]


print(">>>", result)








