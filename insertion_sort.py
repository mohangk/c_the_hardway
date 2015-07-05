import sys

numbers = [int(number) for number in sys.argv[1:]]

print numbers

for count in range(1,len(numbers)):
  inner_count = count

  while (numbers[inner_count] < numbers[inner_count - 1]) and inner_count > 0:
    temp = numbers[inner_count]
    numbers[inner_count] = numbers[inner_count - 1]
    numbers[inner_count - 1] = temp
    inner_count = inner_count - 1

print numbers
