file = open("day19/input.txt", "r")
text = file.read()
file.close()

text_parsing = text.split("\n\n")

towels = text_parsing[0].split(", ")
patterns = text_parsing[1].split('\n')



def try_pattern(attempt: str, pattern: str) -> bool:
	# print(">", attempt, "/", pattern)
	if len(attempt) > len(pattern) or (len(attempt) == len(pattern) and attempt != pattern):
		return False
	elif attempt != pattern[:len(attempt)]:
		return False
	elif attempt == pattern:
		return True
	for towel in towels:
		if try_pattern(attempt + towel, pattern):
			return True
	return False

result = 0
for pattern in patterns:
	result += try_pattern("", pattern)


print(">>>", result)
