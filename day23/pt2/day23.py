from functools import reduce
import string
from tokenize import group
from unittest import result


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




def find_commons(first: list, second: list) -> list:
	result = []
	for fst in first:
		for scnd in second:
			if fst == scnd:
				result.append(fst)
	result.sort()
	return result


def reduce_list(whoami: list, commons: list, minimum: int, mistakes_allowed: int) -> list:
	result = []
	curr_commons = find_commons(commons, whoami)
	# if curr_commons == commons:
	# 	print("WTF     ", sorted(commons), " ", sorted(whoami), curr_commons == whoami)

	if len(curr_commons) + 1 < minimum:
		return None
	if minimum == 1:
		# print("FOUND:", curr_commons, commons)
		return curr_commons
	for check in curr_commons:
		result = reduce_list(pairs[check], curr_commons, minimum - 1, mistakes_allowed)
		if result:
			result.append(check)
			return result
		else:
			mistakes_allowed -= 1
			if mistakes_allowed < 0:
				return None


max_len = max([len(pairs[pair]) for pair in pairs]) + 1
# print(max_len)

best_group = []

for groupsize in reversed(range(3, max_len + 1)):
	print("Testing for groups of", groupsize)
	ctr = 0
	for first in pairs:
		ctr += 1
		# if groupsize == 12 and ctr % 10 == 0:
		# 	print(ctr)
		commons = pairs[first]
		# print(">>", commons)
		if len(commons) + 1 < groupsize:
			break
		for second in range(len(pairs[first])):
			# print("> (", first, pairs[first][second], ")  Commons between", commons, "and", pairs[pairs[first][second]], ":", find_commons(commons, pairs[pairs[first][second]]))
			commons = find_commons(pairs[first], pairs[pairs[first][second]])
			# print("(B)", commons,  groupsize)
			if len(commons) + 2 < groupsize:
				break
			to_check_list = pairs[first].copy()
			to_check_list.pop(second)
			# print("Passing", to_check_list, commons, groupsize - 2)
			commons = reduce_list(to_check_list, commons, groupsize - 2, max_len - groupsize)
			if commons:
				commons.append(first)
				commons.append(pairs[first][second])
				commons.sort()
				stringresult = ""
				for x in commons:
					stringresult = stringresult + x
					stringresult = stringresult + ','
				print(">>>", stringresult[:-1])
				exit(0)
	print("  Group of size", groupsize, "not found.")





# for groupsize in reversed(range(3, max_len + 1)):
# 	allowed_errors = max_len - groupsize
# 	banned_pcs = []
# 	for pair in pairs:
# 		errors_made = 0
# 		found = [pair]
# 		for subpair in range(len(pairs[pair]) - 1):
# 			if pairs[pair][subpair + 1] not in pairs[pairs[pair][subpair]]:
# 				print(pair + ':', pairs[pair][subpair + 1], "not in", pairs[pair][subpair], pairs[pairs[pair][subpair]])
# 				errors_made += 1
# 			else:
# 				found.append(subpair)
# 			if errors_made > allowed_errors:
# 				break
# 		print(errors_made, allowed_errors)
# 		if errors_made > allowed_errors:
# 			banned_pcs.append(pair)
# 			print("BANNED", pair)
# 		else:
# 			print("Found a group of size", str(groupsize) + ':', found)


# 	print(">", groupsize)



