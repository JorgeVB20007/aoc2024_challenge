



file = open("input.txt", "r")
text = file.read()
rows = text.split("\n")
columns = [[], []]
for row in rows:
	values = row.split("   ")
	columns[0].append(int(values[0]))
	columns[1].append(int(values[1]))

for col in columns:
	col.sort()

result = 0


for idx in range(0, len(columns[0])):
	result += abs(columns[0][idx] - columns[1][idx])

print(">>>", result)
