import math

file = open("day22/input.txt", "r")
text = file.read()
file.close()

lines = [int(x) for x in text.split("\n")]

# print(lines)

def to_index(value: int) -> int:
	return value + 9

def is_valid_comb(comb: tuple) -> bool:
	tempresult = 0
	tempresults = []
	for idx in comb:
		tempresult += idx
		tempresults.append(tempresult)
		if tempresult < -9 or tempresult > 9:
			break 
	if tempresult >= -9 and tempresult <= 9 and max(tempresults) - min(tempresults) <= 9:
		return True
	return False

def generate_combs() -> dict:
	result = {}
	for idx1 in range(-9, 10):
		for idx2 in range(-9, 10):
			for idx3 in range(-9, 10):
				for idx4 in range(-9, 10):
					newindex = (idx1, idx2, idx3, idx4)
					if is_valid_comb(newindex):
						result[newindex] = 0
	return result



def mix(secnum1: int, secnum2: int):
	return secnum1 ^ secnum2

def prune(secnum: int):
	return secnum % 16777216


result = 0
combs = generate_combs()
ctr = 0
for line in lines:
	secnum = line
	lineresults = []
	linediffs = []
	for turn in range(2000):
		secnum = prune(mix(secnum, secnum * 64))
		secnum = prune(mix(secnum, math.floor(secnum / 32)))
		secnum = prune(mix(secnum, secnum * 2048))
		if turn > 0:
			linediffs.append(secnum % 10 - lineresults[-1])
		else:
			linediffs.append(-10)
		lineresults.append(secnum % 10)
	
	already_checked = []
	for turn in range(4, 2000):
		tocheck = (*linediffs[turn - 3:turn + 1],)
		if tocheck not in already_checked:
			combs[tocheck] += lineresults[turn]
			already_checked.append(tocheck)
	ctr += 1
	if not ctr % 100:
		print(ctr, "/", len(lines), "(" + str(round(100 * ctr / len(lines))) + "%)")

print(len(lines), "/", len(lines), "(100%)")

print(">", list(combs.keys())[list(combs.values()).index(max(combs.values()))])
print(">>>", max(combs.values()))
		
