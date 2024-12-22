import math

file = open("day21/input.txt", "r")
text = file.read()
file.close()

lines = text.split("\n")

print(lines)


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

def make_comb(comb: str, level: int) -> list:
	loc = (2, 1)
	levelresult = []
	if level == 0:
		return [comb]
	for dir in comb:
		nextloc = get_dir_coords(dir)
		next_paths = []
		for pth in direction_path(loc, nextloc):
			next_paths.append(make_comb(pth, level - 1))
		levelresult.append(next_paths)
		loc = nextloc

	return levelresult

def get_shortest(options: list, level: int) -> str:
	if level == 0:
		# print("T", options[0])
		return options[0]
	strings = []
	# print("=")
	for item in options:
		do_once = get_shortest(item, level - 1)
		strings.append(do_once)
	# print(strings)

	result = ""
	if level % 2 == 1:
		result = min(strings, key=len)
		print("x Between", strings, "chose", result)
	else:
		for string in strings:
			result = result + string
		print("x Appended", strings, "to", result)
	return result




middle_robots = 2
curr_num_location = (2, 0)
curr_dir_location = [(2, 1)] * middle_robots
step_options = [[]] * 3
result = 0

for line in lines:
	line_path = ""
	for num in line:
		next_num = get_num_coords(num)
		step_options[0] = numeric_path(curr_num_location, next_num)
		curr_num_location = next_num

		print(step_options[0])

		final_paths = []
		for options in step_options[0]:
			final_paths.append(make_comb(options, middle_robots))
		
		path = get_shortest(final_paths, (middle_robots) * 2 + 1)
		line_path = line_path + path
	# print(">>", line + ":", line_path, len(line_path))
	result += int(line[:-1]) * len(line_path)
	print("----")

print(">>>", result)

# for line in lines:
# 	str_attempt = [[]] * 3
# 	for num in line:
# 		next_num = get_num_coords(num)
# 		step_options = numeric_path(curr_num_location, next_num)
# 		str_attempt[0] = str_attempt[0] + 
# 		curr_num_location = next_num
# 	print(line + ":", str_attempt[0], "-->", len(str_attempt[middle_robots]))
	
# 	for n in range(1, 1 + middle_robots):
# 		for char_attempt in str_attempt[n - 1]:
# 			next_dir = get_dir_coords(char_attempt)
# 			str_attempt[n] = str_attempt[n] + direction_path(curr_dir_location[n - 1], next_dir)
# 			curr_dir_location[n - 1] = next_dir
# 		print(line + ":", str_attempt[n], "-->", len(str_attempt[n]))
		





