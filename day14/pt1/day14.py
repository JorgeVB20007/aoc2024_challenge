import math

file = open("day14/input.txt", "r")
text = file.read()
file.close()





board_x = 101
board_y = 103
seconds = 100

def determine_quadrant(loc: dict) -> int:
	if loc['x'] == math.floor(board_x / 2) or loc['y'] == math.floor(board_y / 2):
		return -1
	x = 0 if loc['x'] < math.floor(board_x / 2) else 1
	y = 0 if loc['y'] < math.floor(board_y / 2) else 1
	return y * 2 + x





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

locations = []
for robot in robots:
	newlocation = {}
	newlocation['x'] = (robot['p']['x'] + robot['v']['x'] * seconds) % board_x
	newlocation['y'] = (robot['p']['y'] + robot['v']['y'] * seconds) % board_y
	locations.append(newlocation)

quarters = [0] * 4

for loc in locations:
	quadrant = determine_quadrant(loc)
	if quadrant != -1:
		quarters[quadrant] += 1

print(quarters)


result = 1
for a in quarters:
	result *= a

print(">>>", result)

