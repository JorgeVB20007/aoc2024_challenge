import math

file = open("day21/input.txt", "r")
text = file.read()
file.close()

lines = text.split("\n")

# print(lines)

middle_robots = 26

def get_num_coords(c: str) -> tuple:
	if c == 'A':
		return (2, 0)
	elif c == '0':
		return (1, 0)
	c = int(c)

	y = math.ceil(c / 3)
	x = ((c - 1) % 3)
	return (x, y)

def get_dir_coords(c: str) ->tuple:
	if c == 'A' or c == '^':
		y = 1
	else:
		y = 0
	if c == '<':
		x = 0
	elif (c == '^' or c == 'v'):
		x = 1
	else:
		x = 2
	return (x, y)


def goes_through(dirs: str, curr: tuple, eval: tuple) -> bool:
	x = curr[0]
	y = curr[1]

	for dir in dirs:
		if dir == '^':
			y += 1
		elif dir == '>':
			x += 1
		elif dir == 'v':
			y -= 1
		elif dir == '<':
			x -= 1
		if (x, y) == eval:
			return True
	return False



def numeric_path(curr: tuple, next: tuple) -> list:
	x = next[0] - curr[0]
	y = next[1] - curr[1]
	result = ""

	while x > 0:
		result = result + ">"
		x -= 1
	while y > 0:
		result = result + "^"
		y -= 1
	while x < 0:
		result = result + "<"
		x += 1
	while y < 0:
		result = result + "v"
		y += 1
	# result = result + 'A'
	if (result == result[::-1] or goes_through(result[::-1], curr, (0, 0))):
		return [result + 'A']
	return [result + 'A', result[::-1] + 'A']





def direction_path(curr: tuple, next: tuple) -> list:
	x = next[0] - curr[0]
	y = next[1] - curr[1]
	result = ""

	while x > 0:
		result = result + ">"
		x -= 1
	while y < 0:
		result = result + "v"
		y += 1
	while x < 0:
		result = result + "<"
		x += 1
	while y > 0:
		result = result + "^"
		y -= 1
	# result = result + 'A'
	if (result == result[::-1] or goes_through(result[::-1], curr, (0, 1))):
		return [result + 'A']
	# print(curr, "->", result, "- doesn't go through", (0, 1))
	return [result + 'A', result[::-1] + 'A']


cache = [{} for _ in range(middle_robots)]

def try_path(path: str, level: int) -> str:
	# print(level)
	if level == 0:
		return path
	if path in cache[level]:
		return cache[level][path]
	curr_key = (2, 1)
	all_steps = []
	for char in path:
		next_key = get_dir_coords(char)
		all_steps.append(direction_path(curr_key, next_key))
		curr_key = next_key
	final_result = ""
	for steps in all_steps:
		options = []
		for option in steps:
			options.append(try_path(option, level - 1))
		final_result = final_result + min(options, key=len)
	cache[level][path] = final_result
	print("CACHED in level", level, "for", path, "size", len(final_result))
	return final_result


cache_num = [{} for _ in range(middle_robots)]

def try_path_num(path: str, level: int) -> int:
	# print(level)
	if level == 0:
		return len(path)
	if path in cache[level]:
		return cache[level][path]
	curr_key = (2, 1)
	all_steps = []
	for char in path:
		next_key = get_dir_coords(char)
		all_steps.append(direction_path(curr_key, next_key))
		curr_key = next_key
	final_result = 0
	for steps in all_steps:
		options = []
		for option in steps:
			options.append(try_path_num(option, level - 1))
		final_result += min(options)
	cache[level][path] = final_result
	# print("CACHED in level", level, "for", path, "size", final_result)
	return final_result
		
the_result = 0

for line in lines:
	curr_num_location = (2, 0)
	num_combination = []
	for num in line:
		next_num_location = get_num_coords(num)
		num_combination.append(numeric_path(curr_num_location, next_num_location))
		curr_num_location = next_num_location
	# print(num_combination)

	result = 0
	for combs in num_combination:
		# print(">", combs)
		options = []
		for option in combs:
			# print(">>", option)
			options.append(try_path_num(option, middle_robots - 1))
		result += min(options)
	the_result += result * int(line[:-1])

# print(cache)
print(">>>", the_result)





