file = open("day23/input.txt", "r")
text = file.read()
file.close()

lines = [x.split("-") for x in text.split("\n")]
pairs = {}

for pair in lines:
	for side in range(0, 2):
		if pair[side] in pairs:
			pairs[pair[side]].append(pair[int(not side)])
		else:
			pairs[pair[side]] = [pair[int(not side)]]

trios = []

for pair in pairs:
	for others in range(len(pairs[pair])):
		for last in range(others + 1, len(pairs[pair])):
			if pairs[pair][last] in pairs[pairs[pair][others]]:
				newtrio = [pair, pairs[pair][others], pairs[pair][last]]
				newtrio.sort()
				if newtrio not in trios:
					trios.append(newtrio)


t_counter = 0

for trio in trios:
	for pc in trio:
		if pc[0] == 't':
			t_counter += 1
			break


# print(trios)
print(">>>", t_counter)

