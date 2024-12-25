from tokenize import Triple


file = open("day25/input.txt", "r")
text = file.read()
file.close()

blocks = text.split("\n\n")
all_locks = []
all_keys = []

for block in blocks:
	blocklines = block.split("\n")
	is_lock = True
	heights = []
	for char in blocklines[0]:
		heights.append(-1)
	if blocklines[0][0] == "#":
		is_lock = True
	else:
		is_lock = False

	for line in blocklines:
		for char in range(len(line)):
			if line[char] == '#':
				heights[char] += 1
	if is_lock:
		all_locks.append(heights)
	else:
		all_keys.append(heights)

# print(all_locks)
# print(all_keys)

result = 0
for lock in all_locks:
	for keys in all_keys:
		valid = True
		for idx in range(len(lock)):
			if lock[idx] + keys[idx] > 5:
				valid = False
				break
		if valid:
			result += 1

print(">>>", result)




