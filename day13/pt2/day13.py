file = open("day13/input.txt", "r")
text = file.read()
file.close()

text_equations = text.split("\n\n")
all_equations = []

for equation in text_equations:
	splitted_equation = equation.split("\n")
	newequation = {}
	newequation['a'] = {}
	splitted_line = splitted_equation[0].split(" ")
	newequation["a"]["x"] = float(splitted_line[2][2:-1])
	newequation["a"]["y"] = float(splitted_line[3][2:])

	newequation['b'] = {}
	splitted_line = splitted_equation[1].split(" ")
	newequation["b"]["x"] = float(splitted_line[2][2:-1])
	newequation["b"]["y"] = float(splitted_line[3][2:])

	newequation['prize'] = {}
	splitted_line = splitted_equation[2].split(" ")
	newequation["prize"]["x"] = float(splitted_line[1][2:-1]) + 10000000000000
	newequation["prize"]["y"] = float(splitted_line[2][2:]) + 10000000000000

	all_equations.append(newequation)

result: int = 0


for equation in all_equations:
	reduced_equation = {}
	reduced_equation['a'] = {}
	reduced_equation['b'] = {}
	reduced_equation['prize'] = {}

	reduced_equation['a']['x'] = equation['a']['x'] * equation['a']['y']
	reduced_equation['a']['y'] = equation['a']['y'] * equation['a']['x']

	reduced_equation['b']['x'] = equation['b']['x'] * equation['a']['y']
	reduced_equation['b']['y'] = equation['b']['y'] * equation['a']['x']

	reduced_equation['prize']['x'] = equation['prize']['x'] * equation['a']['y']
	reduced_equation['prize']['y'] = equation['prize']['y'] * equation['a']['x']

	reduced_equation['total'] = {}
	reduced_equation['total']['b'] = reduced_equation['b']['x'] - reduced_equation['b']['y']
	reduced_equation['total']['prize'] = reduced_equation['prize']['x'] - reduced_equation['prize']['y']

	b = reduced_equation['total']['prize'] / reduced_equation['total']['b']
	a = (equation['prize']['x'] - (equation['b']['x'] * b)) / equation['a']['x']
	# print(equation, "A:", a, "| B:", b)
	if (a.is_integer() and b.is_integer()):
		result += int(3 * a + b)

print(">>>", result)
