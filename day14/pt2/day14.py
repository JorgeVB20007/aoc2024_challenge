import math
from operator import itemgetter

file = open("day14/input.txt", "r")
text = file.read()
file.close()





board_x = 101
board_y = 103
seconds = 0

def determine_quadrant(loc: dict) -> int:
	if loc['x'] == math.floor(board_x / 2) or loc['y'] == math.floor(board_y / 2):
		return -1
	x = 0 if loc['x'] < math.floor(board_x / 2) else 1
	y = 0 if loc['y'] < math.floor(board_y / 2) else 1
	return y * 2 + x


def print_map(locations: list):
	map: str = ""
	for y in range(0, board_y):
		for x in range(0, board_x):
			test = [x, y]
			if test in locations:
				map = map + '#'
			else:
				map = map + '.'
		map = map + '\n'

	print(map)




lines = text.split('\n')
robots = []
for line in lines:
	line = line.split(" ")
	line = [x[2:] for x in line]
	line_p = line[0].split(',')
	line_v = line[1].split(',')
	new_info = {}
	new_info['p'] = {}
	new_info['v'] = {}
	new_info['p']['x'] = int(line_p[0])
	new_info['p']['y'] = int(line_p[1])
	new_info['v']['x'] = int(line_v[0])
	new_info['v']['y'] = int(line_v[1])
	robots.append(new_info)


while True:
	randomness_score = 0
	locations = []
	for robot in robots:
		newlocation = []
		newlocation.append((robot['p']['x'] + robot['v']['x'] * seconds) % board_x)
		newlocation.append((robot['p']['y'] + robot['v']['y'] * seconds) % board_y)
		locations.append(newlocation)

	locations = sorted(locations, key=itemgetter(1))
	locations = sorted(locations, key=itemgetter(0))
	for idx in range(0, len(locations) - 1):
		if locations[idx][1] + 1 == locations[idx + 1][1]:
			randomness_score += 1

	locations = sorted(locations, key=itemgetter(0))
	locations = sorted(locations, key=itemgetter(1))
	for idx in range(0, len(locations) - 1):
		if locations[idx][0] + 1 == locations[idx + 1][0]:
			randomness_score += 1
	if randomness_score > 500:		# 500 is a hardcoded number, I tried several values and this is the first that got me a tree.
		print_map(locations)
		print(">>>", seconds)
		break
	seconds += 1


