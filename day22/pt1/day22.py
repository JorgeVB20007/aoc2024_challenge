import math

file = open("day22/input.txt", "r")
text = file.read()
file.close()

lines = [int(x) for x in text.split("\n")]

# print(lines)

def mix(secnum1: int, secnum2: int):
	return secnum1 ^ secnum2

def prune(secnum: int):
	return secnum % 16777216


result = 0
for line in lines:
	secnum = line
	for turn in range(2000):
		secnum = prune(mix(secnum, secnum * 64))
		secnum = prune(mix(secnum, math.floor(secnum / 32)))
		secnum = prune(mix(secnum, secnum * 2048))
	result += secnum
	# print(str(line) + ":", secnum)
print(">>>", result)
		
