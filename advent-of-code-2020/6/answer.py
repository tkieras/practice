from collections import Counter

def read_file(filepath):
    with open(filepath) as infile:
        data = infile.read()
    return data

def parse_groups(data):

    return [list(filter(lambda m: len(m) > 0, g.split("\n"))) for g in data.split("\n\n")]

def count_group_answers(group):
    answers = Counter()
    for member in group:
        answers.update(member)

    unanimous = 0
    for key in answers:
        if answers[key] == len(group):
            unanimous += 1

    return len(answers), unanimous

total_group = total_unanimous = 0
groups = parse_groups(read_file("input.txt"))
for group in groups:
    g, u = count_group_answers(group)
    total_group += g
    total_unanimous += u

print("part 1: {}".format(total_group))
print("part 2 : {}".format(total_unanimous))


