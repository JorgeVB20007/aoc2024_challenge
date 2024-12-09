import math

def turn_to_ternary(number: int, min_len: int) -> str:
	result = ""
	thelen = 0
	while (number > 0):
		result = str(number % 3) + result
		# result = "{0}{1}".format(str(number % 3), result)
		number = math.floor(number / 3)
		thelen += 1
	while (thelen < min_len):
		result = '0' + result
		thelen += 1
	return result

def join_when_required(lines_items: list, attempt: str) -> list:
	result: list = []

	result.append(lines_items[0])
	for idx in range(0, len(attempt)):
		if attempt[idx] == '2':
			result[-1] *= math.pow(10, math.floor(math.log10(lines_items[idx + 1])) + 1)
			result[-1] += lines_items[idx + 1]
		else:
			result.append(lines_items[idx + 1])
	return result



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
	if not (key % 10):
		print(key, "/", len(lines_idxs))
	found: bool = False
	operations: int = len(lines_itms[key]) - 1
	for attempt in range(0, int(math.pow(3, operations))):
		attempt = turn_to_ternary(attempt, operations)
		tempresult: int = lines_itms[key][0]
		for turn in range(0, operations):
			if attempt[turn] == '0':
				tempresult += lines_itms[key][turn + 1]
			elif attempt[turn] == '1':
				tempresult *= lines_itms[key][turn + 1]
			else:
				tempresult *= math.pow(10, math.floor(math.log10(lines_itms[key][turn + 1])) + 1)
				tempresult += lines_itms[key][turn + 1]
			if tempresult > lines_idxs[key]:
				break
		if tempresult == lines_idxs[key]:
			result += lines_idxs[key]
			found = True
			break

print(">>>", result)


