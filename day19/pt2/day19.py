file = open("day19/input3.txt", "r")
text = file.read()
file.close()

text_parsing = text.split("\n\n")

towels = text_parsing[0].split(", ")
patterns = text_parsing[1].split('\n')



def try_pattern(attempt: str, pattern: str, attempt_lst: list) -> int:
	# print(">", attempt, "/", pattern)
	working_patterns = 0
	if len(attempt) > len(pattern) or (len(attempt) == len(pattern) and attempt != pattern):
		return 0
	elif attempt != pattern[:len(attempt)]:
		return 0
	elif attempt == pattern:
		return 1
	for towel in towels:
		listed_attempt = attempt_lst.copy()
		listed_attempt.append(towel)
		pattern_tried = try_pattern(attempt + towel, pattern, listed_attempt)
		if pattern_tried > 0:
			working_patterns += pattern_tried
	print(working_patterns, attempt_lst)
	return working_patterns

result = 0
for pattern in patterns:
	result += try_pattern("", pattern, [])
	print(result)


print(">>>", result)
