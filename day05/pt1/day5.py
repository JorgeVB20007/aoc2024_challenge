import math

file = open("day5/input.txt", "r")
text = file.read()
file.close()

parts = text.split("\n\n")

rulelines = parts[0].split("\n")
rules = {}

for rule in rulelines:
    ruleparts = [int(x) for x in rule.split("|")]
    if ruleparts[0] in rules:
        rules[ruleparts[0]].append(ruleparts[1])
    else:
        rules[ruleparts[0]] = [ruleparts[1]]

instructionlines = parts[1].split("\n")
instructions = []

for instruction in instructionlines:
    instructions.append([int(x) for x in instruction.split(",")])

print(instructions)
print()
print(rules)

result = 0

for ins in instructions:
    good = True
    for ref_idx in range(0, len(ins)):
        for comp_idx in range(ref_idx + 1, len(ins)):
            if ins[comp_idx] in rules.keys() and ins[ref_idx] in rules[ins[comp_idx]]:
                good = False
    if good:
        result += ins[math.floor(len(ins) / 2)]

print(">>>", result)




