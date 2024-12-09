



file = open("input.txt", "r")
text = file.read()
file.close()

rows = text.split("\n")
columns = [[], []]
for row in rows:
	values = row.split("   ")
	columns[0].append(int(values[0]))
	columns[1].append(int(values[1]))

left_list = columns[0]
right_list = {}

for value in columns[1]:
	if value in right_list:
		right_list[value] += 1
	else:
		right_list[value] = 1

result = 0

for value in left_list:
	if value in right_list:
		result += value * right_list[value]

print(">>>", result)
