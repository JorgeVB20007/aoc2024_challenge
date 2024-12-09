


file = open("day2/input.txt", "r")
text = file.read()
file.close()

lines = text.split("\n")
result = 0
for line in lines:
    nums = line.split(" ")
    fullnums = nums
    for attempt in range(0, 3):
        increasing = True
        if (int(nums[0]) > int(nums[1])):
            increasing = False
        prevnum  = int(nums[0])
        wrong = False
        error_allowed = (attempt == 0)
        for num in nums[1:]:
            dont_advance = False
            if ((prevnum < int(num)) != increasing):
                if error_allowed:
                    error_allowed = False
                    dont_advance = True
                else:
                    wrong = True
            elif (abs(prevnum - int(num)) < 1 or abs(prevnum - int(num)) > 3):
                if error_allowed:
                    error_allowed = False
                    dont_advance = True
                else:
                    wrong = True
            if not dont_advance:
                prevnum = int(num)
        if not wrong:
            result += 1
            break
        else:
            if attempt == 0:
                nums = nums[1:]
            elif attempt == 1:
                nums = fullnums
                nums.pop(1)

print(">>>>", result)




