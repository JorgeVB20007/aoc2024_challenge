file = open("day11/input.txt", "r")
text = file.read()
file.close()

stones = {}
for stone in text.split(" "):
	if int(stone) in stones:
		stones[int(stone)] += 1
	else:
		stones[int(stone)] = 1

times = 25

while (times > 0):
	stones_next = {}
	if 0 in stones:
		stones_next[1] = stones[0]
	for idx in stones:
		length = int(len(str(idx)))
		if idx == 0:
			continue
		elif length % 2 == 0:
			first = int(str(idx)[: int(length / 2)])
			second = int(str(idx)[int(length / 2) :])
			if first in stones_next:
				stones_next[first] += stones[idx]
			else:
				stones_next[first] = stones[idx]
			if second in stones_next:
				stones_next[second] += stones[idx]
			else:
				stones_next[second] = stones[idx]
		else:
			if int(idx * 2024) in stones_next:
				stones_next[int(idx * 2024)] += stones[idx]
			else:
				stones_next[int(idx * 2024)] = stones[idx]

	stones = stones_next
	times -= 1

result = 0

for idx in stones:
	result += stones[idx]


print(">>>", result)
