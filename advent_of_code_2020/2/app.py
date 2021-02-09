from collections import Counter

def read_file():
    with open("input.txt") as infile:
        for line in infile:
            yield line

def parse_line(line):
    split = line.split(":")
    assert len(split) == 2
    policy, password = split
    split = policy.split(" ")
    assert len(split) == 2
    low_high, key = split
    split = low_high.split("-")
    assert len(split) == 2
    low, high = split
    return (int(low), int(high), key, password.strip())

def evaluate_password_counts(low, high, key, password):
    counts = Counter(password)
    return counts[key] >= low and counts[key] <= high

def evaluate_password_positions(low, high, key, password):
    return ((password[low-1] == key) != (password[high-1] == key))



resultA = 0
for line in read_file():
    resultA += evaluate_password_counts(*parse_line(line))
  
print(resultA)

resultB = 0
for line in read_file():
    resultB += evaluate_password_positions(*parse_line(line))

print(resultB)

