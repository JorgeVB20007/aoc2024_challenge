file = open("day19/input.txt", "r")
text = file.read()
file.close()

text_parsing = text.split("\n\n")

towels = text_parsing[0].split(", ")
patterns = text_parsing[1].split('\n')


def try_pattern(attempt: str, pattern: str) -> bool:
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
	if (not try_pattern("", pattern)):
		continue
	coincidences = [[] for _ in range(len(pattern))]
	for towel in towels:
		idx = 0
		while True:
			idx = pattern.find(towel, idx)
			if idx < 0:
				break
			coincidences[idx].append({"towel": towel, "starts": idx, "ends": idx + len(towel)})
			idx += 1

	probs_per_len = [0 for _ in range(len(pattern) + 1)]
	probs_per_len[len(pattern)] = 1
	for idx in reversed(range(0, len(pattern))):
		for towel in coincidences[idx]:
			probs_per_len[idx] += probs_per_len[towel["ends"]]



	result += probs_per_len[0]


print(">>>", result)
