import math

file = open("day7/input.txt", "r")
text = file.read()
file.close()

full_lines: list = text.split("\n")
lines_idxs: list = []
lines_itms: list = []
for line in full_lines:
	line = line.replace(':', '')
	splitted_line = [int(x) for x in line.split(" ")]
	lines_idxs.append(splitted_line[0])
	lines_itms.append(splitted_line[1:])


result: int = 0

for key in range(0, len(lines_idxs)):
	found: bool = False
	operations: int = len(lines_itms[key]) - 1
	for attempt in range(0, int(math.pow(2, operations))):
		attempt = format(attempt, '0{0}b'.format(operations))
		tempresult: int = lines_itms[key][0]
		for turn in range(0, operations):
			if attempt[turn] == '1':
				tempresult *= lines_itms[key][turn + 1]
			else:
				tempresult += lines_itms[key][turn + 1]
			if tempresult > lines_idxs[key]:
				break
		if tempresult == lines_idxs[key]:
			result += lines_idxs[key]
			found = True
			break

print(">>>", result)


