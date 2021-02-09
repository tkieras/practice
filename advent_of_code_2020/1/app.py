TOTAL = 2020


def read_dataset():
	data = set()

	with open("input.txt") as infile:
		for line in infile:
			expense = int(line)	
			assert expense not in data	
			data.add(expense)

	return data

def find_paired_expenses(dataset, total):
	for a in dataset:
		b = total - a
		if b in dataset:
			return (a, b)

	return (None, None)

def find_triplet(dataset, total):
	for a in dataset:
		complement = total - a
		b, c = find_paired_expenses(dataset, complement)
		if b and c:
			return (a, b, c)

	return (None, None, None)


a, b = find_paired_expenses(read_dataset(), TOTAL)
print("{} + {} = {}".format(a, b, a+b))
print(a*b)

a, b, c = find_triplet(read_dataset(), TOTAL)
print("{} + {} + {} = {}".format(a, b, c, a+b+c))
print(a*b*c)