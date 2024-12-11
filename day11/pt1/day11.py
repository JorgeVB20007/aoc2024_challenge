file = open("day11/input.txt", "r")
text = file.read()
file.close()

stones = text.split(" ")
stoneslist = []

for tolist in stones:
	stoneslist.append([tolist])

print(stoneslist)

times = 75

while times > 0:
	for stone in stoneslist:
		if (int(stone[0]) == 0):
			stone[0] = '1'
		elif len(stone[0]) % 2 == 0:
			half = int(len(stone[0]) / 2)
			stone.append(str(int(stone[0][half:])))
			stone[0] = str(int(stone[0][:half]))
		else:
			stone[0] = str(int(stone[0]) * 2024)
	newlist = []
	for stone in stoneslist:
		for substone in stone:
			newlist.append([substone])
	stoneslist = newlist
	print(times)
	times -= 1


# print(stoneslist)

print(">>>", len(stoneslist))
