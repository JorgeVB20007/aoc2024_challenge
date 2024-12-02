


file = open("day2/input.txt", "r")
text = file.read()

lines = text.split("\n")
result = 0
for line in lines:
    nums = line.split(" ")
    increasing = True
    if (int(nums[0]) > int(nums[1])):
        increasing = False
    prevnum  = int(nums[0])
    wrong = False
    for num in nums[1:]:
        if ((prevnum < int(num)) != increasing):
            wrong = True
        elif (abs(prevnum - int(num)) < 1 or abs(prevnum - int(num)) > 3):
            wrong = True
        prevnum = int(num)
    if not wrong:
        result += 1

print(">>>>", result)




